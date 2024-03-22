#include "controller.h"

#include <thread>

#include "mainwindow.h"
#include "settings.h"
#include "model.h"

#define SIXTH_COMMAND_LENGTH 5
#define S_COMMAND_LENGTH 2

Controller::Controller(MainWindow* pView) : pumpControllerView{ pView } {
	pumpControllerModel = std::make_shared<PumpControllerModel>();
	settings = std::make_unique<Settings>(pumpControllerModel, pView);
	pSerialPort = std::make_unique<QSerialPort>();
	log = std::make_unique<csvLog>();
	settings->loadWorkspace();
}
double Controller::getStartValue(int index) {
	return pumpControllerModel->getValue(index);
}
bool Controller::serialPortInitialization(const QString& selectedDevice) {
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
		pumpControllerView->errorMessage("Com port is open");
	}
	return state;
}
void Controller::cleaningAirSystem() {
	pumpControllerModel->clearBuffer();
	pumpControllerModel->cleaningAirSystem();
	sendCommand(2, 6);
}
void Controller::sendCommand(int length, int times) {
	for (auto it = 0; it < times; ++it) {
		if (pumpControllerModel->sendCommandData.empty()) {
			break;
		}
		if (pSerialPort->isOpen()) {
			QByteArray sendBuffer;
			sendBuffer.reserve(length);
			for (auto jt = 0; jt < length; ++jt) {
				sendBuffer[jt] = pumpControllerModel->sendCommandData.front();
				pumpControllerModel->sendCommandData.pop_front();
			}
			if ('S' == sendBuffer[1]) {
				log->logEvent(sendBuffer[0]);
			}
			if ('6' == sendBuffer[1]) {
				pumpControllerView->changeCartridgeView(sendBuffer[0] - 'A', true);
			}
			pSerialPort->write(sendBuffer);
			pSerialPort->waitForBytesWritten(150);
			std::this_thread::sleep_for(std::chrono::milliseconds(700));
			pumpControllerView->changeCartridgeView(sendBuffer[0] - 'A', false);
		}
	}
}
void Controller::prepareTheGasAirMixture() {
	pumpControllerModel->calculatePrepareTheGasAirMixture();
	sendCommand(SIXTH_COMMAND_LENGTH, 6);
	settings->saveWorkspace();
}
void Controller::changeGasSupplyTime(int time) {
	pumpControllerModel->gasSupplyTime(time);
	sendCommand(3, 6);
}
void Controller::startUpShuffleAirDelivery() {
	if (isReady()) {
		if (!pumpControllerModel->isBufferClear()) {
			clearBuffer();
		}
	pumpControllerModel->randomGasAirDelivery();
	sendCommand(S_COMMAND_LENGTH, 1);
	}
}
void Controller::startUpSequenceAirDelivery() {
	if (isReady()) {
		if (!pumpControllerModel->isBufferClear()) {
			clearBuffer();
		}
	pumpControllerModel->sequenceGasAirDelivery();
	sendCommand(S_COMMAND_LENGTH, 1);
	}
}
void Controller::stopAirDelivery() {
	if (isReady()) {
		if (!pumpControllerModel->isBufferClear()) {
			clearBuffer();
		}
	pumpControllerModel->stopAirSystem();
	sendCommand(S_COMMAND_LENGTH, 1);
	}
}
void Controller::valveCloseCommand(char valve = 'A') {
	if (isReady()) {
		pumpControllerModel->valveCloseCommand(valve);
		sendCommand(S_COMMAND_LENGTH, 1);
	}
}
void Controller::manualSetting(const std::string& command) {
	pumpControllerModel->addCustomCommand(command);
	sendCommand(static_cast<int>(command.length()), 1);
}
void Controller::clearBuffer() {
	pumpControllerModel->sendCommandData.clear();
}
void Controller::setStartValue(const double _value, const int _iter) {
		pumpControllerModel->setValue(_value, _iter);
}
void Controller::setStartValue(const int _value, const int _iter) {
	pumpControllerModel->setValue(_value, _iter);
}
bool Controller::isReady() const {
	return readyToGo;
}
void Controller::setReadyToGo(bool _readyToGo) {
	readyToGo = _readyToGo;
}
int Controller::getSupplyTime() const {
	return pumpControllerModel->getSupplyTime();
}
bool Controller::setSupplyTime(int temp) {
	return pumpControllerModel->setSupplyTime(temp);
}
int Controller::getDelayTime() const {
	return pumpControllerModel->getDelayTime();
}
bool Controller::setDelayTime(int temp) {
	return pumpControllerModel->setDelayTime(temp);
}
void Controller::saveCurrentWorkSpace() {
	settings->saveWorkspace();
}
void Controller::setComPortName(const std::string& name) {
	pumpControllerModel->setComPortName(name);
}
std::string Controller::getComPortName() const {
	return pumpControllerModel->getComPortName();
}
void Controller::setWorkingVolume(int vol) {
	pumpControllerModel->setWorkingVolume(vol);
}
int Controller::getWorkingVolume() const {
	return pumpControllerModel->getWorkingVolume();
}
bool Controller::isBufferClear() {
	return pumpControllerModel->isBufferClear();
}