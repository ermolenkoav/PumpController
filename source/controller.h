#pragma once
#include "common.h"

class OdoratorModel;
class Settings;
class Controller {
	QSerialPort *pSerialPort = nullptr;
	OdoratorModel *odoratorModel = nullptr;
	Settings* settings = nullptr;

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


	void feedbackConnection();
	
};
