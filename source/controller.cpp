#include "Controller.h"


Controller::~Controller() {
	pSerialPort->close();
}

Controller::Controller() {
	pSerialPort = new QSerialPort();
}

int Controller::CalculateValue(double initialValue) {
	auto times = log(initialValue/_finalValue) / log(_vesselVolume/10);
	return (int)times;
}

bool Controller::devisesActivated(QString selectedDevice) {
	
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
	}
	else {
		//QMessageBox::warning(this, "warning", "com port is open", QMessageBox::Ok);
		
	}
	return false;
}

void Controller::setStartValue(double _startValue[]) {
	
}

void Controller::setStartTimes(int _startTimes[]) {
	
}