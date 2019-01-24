#pragma once
#include "common.h"

class OdoratorModel;
class Controller {
	QSerialPort *pSerialPort = nullptr;
	OdoratorModel *odoratorModel = nullptr;

	void sendCommand(int);
public:	
	Controller();
	~Controller();

	bool serialPortInitialization(QString);
	void prepareTheGasAirMixture();
	void startUpTheGasAirMixture();
	void cleaningAirSystem();
	void clearBuffer();

	void setStartValue(const double, const int);
	void setTimes(const int, const int);
	
};
