#include "controller.h"

#define SIXTH_COMMAND_LENGTH 5
#define S_COMMAND_LENGTH 2

Controller::~Controller() {}
Controller::Controller(MainWindow* pView) : odoratorView{ pView } {
	odoratorModel = std::make_shared<OdoratorModel>();
	settings = std::make_unique<Settings>(odoratorModel, pView);
	pSerialPort = std::make_unique<QSerialPort>();
	log = std::make_unique<csvLog>();
	settings->loadWorkspace();
}
double Controller::getStartValue(int index) {
	return odoratorModel->getValue(index);
}
bool Controller::serialPortInitialization(QString selectedDevice) {
	bool state;
	if (!pSerialPort->isOpen()) {
		pSerialPort->setPortName(selectedDevice);
		pSerialPort->setBaudRate(QSerialPort::Baud115200);
		pSerialPort->setDataBits(QSerialPort::Data8);
		pSerialPort->setParity(QSerialPort::NoParity);
		pSerialPort->setStopBits(QSerialPort::OneStop);
		pSerialPort->setFlowControl(QSerialPort::NoFlowControl);
		pSerialPort->open(QIODevice::ReadWrite);
		state = true;
	} else {
		state = false;
		odoratorView->errorMessage("Com port is open");
	}
	return state;
}
void Controller::cleaningAirSystem() {
	odoratorModel->clearBuffer();
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
			if ('S' == sendBuffer[1]) {
				log->logEvent(sendBuffer[0]);
			}
			if ('6' == sendBuffer[1]) {
				odoratorView->changeCartridgeView(sendBuffer[0] - 'A', true);
			}
			pSerialPort->write(sendBuffer);
			pSerialPort->waitForBytesWritten(150);
			std::this_thread::sleep_for(std::chrono::milliseconds(700));
			odoratorView->changeCartridgeView(sendBuffer[0] - 'A', false);
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
void Controller::startUpShuffleAirDelivery() {
	if (isReady()) {
		if (!odoratorModel->isBufferClear()) {
			clearBuffer();
		}
	odoratorModel->randomGasAirDelivery();
	sendCommand(S_COMMAND_LENGTH, 1);
	}
}
void Controller::startUpSequenceAirDelivery() {
	if (isReady()) {
		if (!odoratorModel->isBufferClear()) {
			clearBuffer();
		}
	odoratorModel->sequenceGasAirDelivery();
	sendCommand(S_COMMAND_LENGTH, 1);
	}
}
void Controller::stopAirDelivery() {
	if (isReady()) {
		if (!odoratorModel->isBufferClear()) {
			clearBuffer();
		}
	odoratorModel->stopAirSystem();
	sendCommand(S_COMMAND_LENGTH, 1);
	}
}
void Controller::valveCloseCommand(char valve = 'A') {
	if (isReady()) {
		odoratorModel->valveCloseCommand(valve);
		sendCommand(S_COMMAND_LENGTH, 1);
	}
}
void Controller::manualSetting(std::string command) {
	odoratorModel->addCustomCommand(command);
	sendCommand(static_cast<int>(command.length()), 1);
}
void Controller::clearBuffer() {
	odoratorModel->sendCommandData.clear();
}
void Controller::setStartValue(const double _value, const int _iter) {
		odoratorModel->setValue(_value, _iter);
}
void Controller::setStartValue(const int _value, const int _iter) {
	odoratorModel->setValue(_value, _iter);
}
bool Controller::isReady() const {
	return readyToGo;
}
void Controller::setReadyToGo(bool _readyToGo) {
	readyToGo = _readyToGo;
}
int Controller::getSupplyTime() const {
	return odoratorModel->getSupplyTime();
}
bool Controller::setSupplyTime(int temp) {
	return odoratorModel->setSupplyTime(temp);
}
int Controller::getDelayTime() const {
	return odoratorModel->getDelayTime();
}
bool Controller::setDelayTime(int temp) {
	return odoratorModel->setDelayTime(temp);
}
void Controller::saveCurrentWorkSpace() {
	settings->saveWorkspace();
}
void Controller::setComPortName(const std::string& name) {
	odoratorModel->setComPortName(name);
}
std::string Controller::getComPortName() const {
	return odoratorModel->getComPortName();
}
void Controller::setWorkingVolume(int vol) {
	odoratorModel->setWorkingVolume(vol);
}
int Controller::getWorkingVolume() const {
	return odoratorModel->getWorkingVolume();
}
bool Controller::isBufferClear() {
	return odoratorModel->isBufferClear();
}