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
	loadValveValues ();
}

void Controller::loadValveValues() {
	settings->loadWorkspace();
}

double Controller::getStartValue(int index) {
	return odoratorModel->getValue(index);
}

int Controller::getStartTimes(int index) {
	return odoratorModel->getTimes(index);
}

bool Controller::serialPortInitialization(QString selectedDevice) {
	if (!pSerialPort->isOpen()) {
		pSerialPort->setPortName(selectedDevice);
		pSerialPort->setBaudRate(QSerialPort::Baud9600);
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
#ifndef _DEBUG
	odoratorModel->cleaningAirSystem();
	sendCommand(2);
#endif//_DEBUG
}

void Controller::prepareTheGasAirMixture() {
	odoratorModel->calculatePrepareTheGasAirMixture();
	sendCommand(SIXTH_COMMAND_LENGTH, 6);
	settings->saveWorkspace();
}

void Controller::startUpShuffleAirMixture() {
	// full piece of shit
	//if (isReady()) 
	{
		while (true)
		{
			odoratorModel->randomGasAirSequence();
			sendCommand(S_COMMAND_LENGTH, 1);
			std::this_thread::sleep_for(std::chrono::seconds(AIR_GAS_DELAY));
		}
		settings->saveCurrentData();
	}
}

void Controller::startUpSequenceAirMixture() {
	// full piece of shit
	//if (isReady()) 
	{
		odoratorModel->sequenceGasAirSequence();
		while(true)
		{
			if (odoratorModel->isBufferClear()) {
				odoratorModel->sequenceGasAirSequence();
			}
			sendCommand(S_COMMAND_LENGTH, 1);
			std::this_thread::sleep_for(std::chrono::seconds(AIR_GAS_DELAY));
		}
		settings->saveCurrentData();
	}
}

void Controller::clearBuffer() {
	odoratorModel->sendCommandData.clear();
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
			pSerialPort->waitForBytesWritten(50);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
}

void Controller::setStartValue(const double _value, const int _iter) {
	odoratorModel->setValue(_value, _iter);
}

void Controller::setTimes(const int _times, const int _iter) {
	odoratorModel->setTimes(_times, _iter);
}

bool Controller::isReady() {
	auto isReady = true;
	pSerialPort->waitForReadyRead(50);
	auto readBuffer = pSerialPort->readAll();
	qDebug() << readBuffer;

	if (isReady) {
		return true;
	} 
	else {
		return false;
	}
}