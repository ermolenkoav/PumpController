#pragma once
#include "pch.h"
#include "csvLog.h"

class OdoratorModel;
class Settings;
class MainWindow;
class csvLog;

class Controller {

	std::shared_ptr<OdoratorModel> odoratorModel;
	std::unique_ptr<Settings> settings;
	std::unique_ptr<QSerialPort> pSerialPort;
	std::unique_ptr<csvLog> log;
	MainWindow* odoratorView;
	bool readyToGo = false;

	void sendCommand(int, int);

public:

	Controller(MainWindow*);
	~Controller();

	void valveCloseCommand(char);
	void stopAirDelivery();
	bool serialPortInitialization(QString);
	void prepareTheGasAirMixture();
	void changeGasSupplyTime(int time);
	void startUpShuffleAirDelivery();
	void startUpSequenceAirDelivery();
	void manualSetting(std::string command);
	void cleaningAirSystem();
	bool isBufferClear();
	void clearBuffer();
	void setStartValue(const double, const int);
	void setStartValue(const int, const int);
	double getStartValue(int);
	bool isReady() const;
	void setReadyToGo(bool);
	int getSupplyTime() const;
	bool setSupplyTime(int);
	int getDelayTime() const;
	bool setDelayTime(int);
	void saveCurrentWorkSpace();
	void setComPortName(const std::string&);
	std::string getComPortName() const;
	void setWorkingVolume(int);
	int getWorkingVolume() const;

};