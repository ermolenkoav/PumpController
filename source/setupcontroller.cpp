#include "setupcontroller.h"

SetUpController::~SetUpController() {}

SetUpController::SetUpController(QSerialPort *_pSerialPort, OdoratorModel *_odoratorModel) {
	pSerialPort = _pSerialPort;
	odoratorModel = _odoratorModel;
}

void SetUpController::sendCommand() {
	for (auto it = 0; it < NumValves; ++it) {
		if (odoratorModel->sendCommandData.empty()) {
			break;
		}
		if (pSerialPort->isOpen()) {
			QByteArray sentData;
			sentData.reserve(8);
			for (auto jt = 0; jt < 4; ++jt) {
				sentData[jt] = odoratorModel->sendCommandData.front();
				odoratorModel->sendCommandData.pop_front();
			}
			for (auto jt = 4; jt < 8; ++jt) {
				sentData[jt] = 0;
			}
			for (auto jt = 0; jt < 8; ++jt) {
				qDebug() << sentData[jt];
			}
			pSerialPort->write(sentData);
			pSerialPort->waitForBytesWritten(100);
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
	}
}

void SetUpController::clearBuffer() {
	odoratorModel->sendCommandData.clear();
}

void SetUpController::calculateData() {
	odoratorModel->sendCommandData.clear();
	for (auto it = 0; it < NumValves; it++) {
		if (0 == _startValue[it]) {
			continue;
		}
		odoratorModel->sendCommandData.push_back(odoratorModel->cartridgeName[it]);
		odoratorModel->sendCommandData.push_back('6');
		odoratorModel->sendCommandData.push_back('2');
		auto aChar = '0';
		auto times = calculateValue(_startValue[it], 20);
		if (9 >= times) {
			times = 9;
		}
		odoratorModel->sendCommandData.push_back(aChar + times);
	}
}

int SetUpController::calculateValue(const double _initialValue, int _startVolume = 10) const {
	return static_cast<int>(log(_initialValue / _finalValue) / log(_vesselVolume / _startVolume));
}

bool SetUpController::devisesActivated(QString selectedDevice) {
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

void SetUpController::setStartValue(const double _value, const int _iter) {
	_startValue[_iter] = _value;
}

void SetUpController::setTimes(const int _times, const int _iter) {
	_startTimes[_iter] = _times;
}