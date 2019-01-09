   #include <source/controller.h>

Controller::~Controller() {
	pSerialPort->close();
}

Controller::Controller(): _startValue{0}, _startTimes{1} {
	// commands and cartridge
	pSerialPort = new QSerialPort();
}

void Controller::sendCommand() { /////////////////////////
	for (auto it = 0; it < NumValves; it++) {
		if (pSerialPort->isOpen()) {
			QByteArray buffer;
			for (auto jt = 0; jt < 4; ++jt) {
				if (0 == sendCommandData.size()) {
					break;
				}
				buffer.append(sendCommandData.front());
				sendCommandData.pop_front();
				std::this_thread::sleep_for(std::chrono::seconds(2));
			}
			pSerialPort->write(buffer);
			pSerialPort->waitForBytesWritten(1000);
		}
	}
}

void Controller::calculateData() {
	sendCommandData.clear();
	for (auto iter = 0; iter < NumValves; iter++) {
		if (0 == _startValue[iter]) {
			continue;
		}
		sendCommandData.push_back(cartridgeName[iter]);
		sendCommandData.push_back('6');
		sendCommandData.push_back('2');
		sendCommandData.push_back(calculateValue(_startValue[iter], 20));
	}
}

int Controller::calculateValue(const double _initialValue, int _startVolume = 10) const {
	return static_cast<int>(log(_initialValue / _finalValue) / log(_vesselVolume / _startVolume));
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

void Controller::setStartValue(const double _value, const int _iter) {
	_startValue[_iter] = _value;
}

void Controller::setTimes(const int _times, const int _iter) {
	_startTimes[_iter] = _times;
}