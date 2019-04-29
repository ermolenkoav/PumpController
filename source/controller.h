#pragma once
#include "common.h"

class OdoratorModel;
class Settings;
class MainWindow;

class Controller {
	QSerialPort *pSerialPort = nullptr;
	OdoratorModel *odoratorModel = nullptr;
	Settings* settings = nullptr;
	MainWindow* odoratorView = nullptr;

	void sendCommand(int, int);
	void loadValveValues();
public:	
	Controller(MainWindow* _odoratorView);
	~Controller();

	bool serialPortInitialization(QString);
	void prepareTheGasAirMixture();
	void startUpShuffleAirMixture();
	void startUpSequenceAirMixture();
	void cleaningAirSystem();
	void clearBuffer();

	void setStartValue(const double, const int);
	void setTimes(const int, const int);

	double getStartValue(int);
	int getStartTimes(int);

	bool isReady();
	
};
