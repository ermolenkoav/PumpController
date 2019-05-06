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

	bool readyToGo = false;

	void sendCommand(int, int);
	void loadValveValues();
public:	
	Controller(MainWindow* _odoratorView);
	~Controller();

	bool serialPortInitialization(QString);
	void prepareTheGasAirMixture();
	void changeGasSupplyTime(char time);
	void startUpShuffleAirMixture();
	void startUpSequenceAirMixture();
	void cleaningAirSystem();
	void clearBuffer();
	void setStartValue(const double, const int);
	double getStartValue(int);
	bool isReady();
	void setReadyToGo(bool);

};
