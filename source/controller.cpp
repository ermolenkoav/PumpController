#include "controller.h"

Controller::~Controller() {
	pSerialPort->close();
	delete odoratorModel;
}

Controller::Controller() {
	odoratorModel = new OdoratorModel;
	settings = new Settings(odoratorModel);
	pSerialPort = new QSerialPort;
}

bool Controller::serialPortInitialization(QString selectedDevice) {
	if (!pSerialPort->isOpen()) {
		qDebug() << selectedDevice;
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
	//odoratorModel->cleaningAirSystem();
	//sendCommand(2);
	qDebug() << "Aerate is over";
}

void Controller::prepareTheGasAirMixture() {
	odoratorModel->calculatePrepareTheGasAirMixture();
	qDebug() << "calculatePrepareTheGasAirMixture() is over";
	sendCommand(4);
	settings->saveWorkspace();
	qDebug() << "Set Up is over";
}

void Controller::startUpTheGasAirMixture() {
	for (auto i = 0; i < 5; i++) {
		odoratorModel->randomGasAirSequence();
		sendCommand(2);
		std::this_thread::sleep_for(std::chrono::seconds(16));
	}
}

void Controller::clearBuffer() {
	odoratorModel->sendCommandData.clear();
}

void Controller::sendCommand(int length) {
	for (auto it = 0; it < NumValves; ++it) {
		if (odoratorModel->sendCommandData.empty()) {
			break;
		}
		if (pSerialPort->isOpen()) {
			QByteArray sendBuffer;
			sendBuffer.reserve(8);
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

void Controller::setStartValue(const double _value, const int _iter) {
	odoratorModel->setStartValue(_value, _iter);
}

void Controller::setTimes(const int _times, const int _iter) {
	odoratorModel->setTimes(_times, _iter);
}

void Controller::feedbackConnection() {
	pSerialPort->waitForReadyRead(50);
	auto readBuffer = pSerialPort->readAll();
	qDebug() << readBuffer;
}