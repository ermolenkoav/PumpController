#include "controller.h"

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
#ifdef NDEBUG
	odoratorModel->cleaningAirSystem();
	sendCommand(2);
#endif//NDEBUG
}

void Controller::prepareTheGasAirMixture() {
	odoratorModel->calculatePrepareTheGasAirMixture();
	sendCommand(4);
	settings->saveWorkspace();
}

void Controller::startUpShuffleGasAirMixture() {
	// full piece of shit
	//if (isReady()) 
	{
		for (auto i = 0; i < NumValves; i++) {
			odoratorModel->randomGasAirSequence();
			sendCommand(2);
			std::this_thread::sleep_for(std::chrono::seconds(30));
		}
		settings->saveCurrentData();
	}
}

void Controller::startUpSequenceGasAirMixture() {
	// full piece of shit
	//if (isReady()) 
	{
		for (auto i = 0; i < NumValves; i++) {
			odoratorModel->sequenceGasAirSequence();
			sendCommand(2);
			std::this_thread::sleep_for(std::chrono::seconds(30));
		}
		settings->saveCurrentData();
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
			std::this_thread::sleep_for(std::chrono::seconds(7));
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