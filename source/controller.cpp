#include "controller.h"

#define AIR_GAS_DELAY 13
#define SIXTH_COMMAND_LENGTH 5
#define S_COMMAND_LENGTH 2

Controller::~Controller() {
	pSerialPort->close();
	delete odoratorModel;
	delete settings;
	delete pSerialPort;
}
Controller::Controller(MainWindow* _odoratorView) {
	odoratorView = _odoratorView;
	odoratorModel = new OdoratorModel;
	settings = new Settings(odoratorModel, odoratorView);
	pSerialPort = new QSerialPort;
	loadWorkspace();
}
void Controller::loadWorkspace() {
	settings->loadWorkspace();
}
double Controller::getStartValue(int index) {
	return odoratorModel->getValue(index);
}
bool Controller::serialPortInitialization(QString selectedDevice) {
	if (!pSerialPort->isOpen()) {
		pSerialPort->setPortName(selectedDevice);
		pSerialPort->setBaudRate(QSerialPort::Baud115200);
		pSerialPort->setDataBits(QSerialPort::Data8);
		pSerialPort->setParity(QSerialPort::NoParity);
		pSerialPort->setStopBits(QSerialPort::OneStop);
		pSerialPort->setFlowControl(QSerialPort::NoFlowControl);
		pSerialPort->open(QIODevice::ReadWrite);
		return true;
	} else {
		//QMessageBox::warning(this, "warning", "com port is open", QMessageBox::Ok);
	}
	return false;
}
void Controller::cleaningAirSystem() {
	odoratorModel->cleaningAirSystem();
	sendCommand(2, 6);
}

void Controller::sendCommand(int length, int times) {
	for (auto it = 0; it < times; ++it) {
		if (odoratorModel->sendCommandData.empty()) {
			break;
		}
		if (pSerialPort->isOpen()) {
			QByteArray sendBuffer;
			sendBuffer.reserve(length);
			for (auto jt = 0; jt < length; ++jt) {
				sendBuffer[jt] = odoratorModel->sendCommandData.front();
				odoratorModel->sendCommandData.pop_front();
			}
			pSerialPort->write(sendBuffer);
			pSerialPort->waitForBytesWritten(100);
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
	}
}
void Controller::prepareTheGasAirMixture() {
	odoratorModel->calculatePrepareTheGasAirMixture();
	sendCommand(SIXTH_COMMAND_LENGTH, 6);
	settings->saveWorkspace();
}
void Controller::changeGasSupplyTime(int time) {
	odoratorModel->gasSupplyTime(time);
	sendCommand(3, 6);
}
void Controller::startUpShuffleAirMixture() {
	if (isReady()) {
		odoratorModel->randomGasAirSequence();
		if (odoratorModel->isBufferClear()) {
			odoratorModel->sequenceGasAirSequence();
		}
		sendCommand(S_COMMAND_LENGTH, 1);
		settings->saveCurrentData();
	}
}

void Controller::startUpSequenceAirMixture() {
	if (isReady()) {
		odoratorModel->sequenceGasAirSequence();
		if (odoratorModel->isBufferClear()) {
			odoratorModel->sequenceGasAirSequence();
		}
		sendCommand(S_COMMAND_LENGTH, 1);
		settings->saveCurrentData();
	}
}
void Controller::manualSetting(std::string command) {
	odoratorModel->addCustomCommand(command);
	sendCommand(command.length(), 1);
}
void Controller::clearBuffer() {
	odoratorModel->sendCommandData.clear();
}

void Controller::setStartValue(const double _value, const int _iter) {
	if (_value <= _finalValue) {
		odoratorModel->setValue(_value, _iter);
	}
}
void Controller::setStartValue(const int _value, const int _iter) {
	if ((_value >= 0) && (_value <= 10)) {
		odoratorModel->setValue(_value, _iter);
	}
}
bool Controller::isReady() {
	return readyToGo;
}
void Controller::setReadyToGo(bool _readyToGo) {
	readyToGo = _readyToGo;
}
int Controller::getSupplyTime() {
	return odoratorModel->getSupplyTime();
}
bool Controller::setSupplyTime(int temp) {
	return odoratorModel->setSupplyTime(temp);
}
int Controller::getDelayTime() {
	return odoratorModel->getDelayTime();
}
bool Controller::setDelayTime(int temp) {
	return odoratorModel->setDelayTime(temp);
}
void Controller::saveCurrentWorkSpace() {
	settings->saveWorkspace();
}