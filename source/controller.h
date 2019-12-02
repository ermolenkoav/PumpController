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
	void loadWorkspace();

public:	
	Controller(MainWindow* _odoratorView);
	~Controller();

	bool serialPortInitialization(QString);
	void prepareTheGasAirMixture();
	void changeGasSupplyTime(int time);
	void startUpShuffleAirDelivery();
	void startUpSequenceAirDelivery();
	void manualSetting(std::string command);
	void cleaningAirSystem();
	void clearBuffer();
	void setStartValue(const double, const int);
	void setStartValue(const int, const int);
	double getStartValue(int);
	bool isReady();
	void setReadyToGo(bool);
	int getSupplyTime();
	bool setSupplyTime(int);
	int getDelayTime();
	bool setDelayTime(int);
	void saveCurrentWorkSpace();
	void setComPortName(const std::wstring&);
	const std::wstring& getComPortName();
};
