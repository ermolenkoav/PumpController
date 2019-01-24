#include "controller.h"

Controller::~Controller() {
	pSerialPort->close();
	delete odoratorModel;
}

Controller::Controller() {
	odoratorModel = new OdoratorModel;
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
	odoratorModel->cleaningAirSystem();
	sendCommand(2);
}

void Controller::prepareTheGasAirMixture() {
	odoratorModel->calculatePrepareTheGasAirMixture();
	sendCommand(4);
}

void Controller::startUpTheGasAirMixture() {
	odoratorModel->randomGasAirSequence();
	sendCommand(2);
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
			QByteArray sentData;
			sentData.reserve(8);
			for (auto jt = 0; jt < length; ++jt) {
				sentData[jt] = odoratorModel->sendCommandData.front();
				odoratorModel->sendCommandData.pop_front();
			}
			pSerialPort->write(sentData);
			pSerialPort->waitForBytesWritten(100);
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
	}
	qDebug() << "Set Up is over";
}

void Controller::setStartValue(const double _value, const int _iter) {
	odoratorModel->setStartValue(_value, _iter);
}

void Controller::setTimes(const int _times, const int _iter) {
	odoratorModel->setTimes(_times, _iter);
}