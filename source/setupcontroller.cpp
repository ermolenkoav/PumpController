#include "setupcontroller.h"
#include "setupcontroller.h"

SetUpController::~SetUpController() {

}

SetUpController::SetUpController(QSerialPort *_pSerialPort) : _startValue{0}, _startTimes{1} {
	// commands and cartridge
	pSerialPort = _pSerialPort;
}

void SetUpController::sendCommand() {
	for (auto it = 0; it < NumValves; ++it) {
		if (sendCommandData.empty()) {
			break;
		}
		if (pSerialPort->isOpen()) {
			QByteArray sentData;
			sentData.reserve(8);
			for (auto jt = 0; jt < 4; ++jt) {
				sentData[jt] = sendCommandData.front();
				sendCommandData.pop_front();
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
	   sendCommandData.clear();
}

void SetUpController::calculateData() {
	sendCommandData.clear();
	for (auto it = 0; it < NumValves; it++) {
		if (0 == _startValue[it]) {
			continue;
		}
		sendCommandData.push_back(cartridgeName[it]);
		sendCommandData.push_back('6');
		sendCommandData.push_back('2');
		auto aChar = '0';
		sendCommandData.push_back(aChar + calculateValue(_startValue[it], 20));
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