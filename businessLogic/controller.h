#pragma once
#include <QString>
#include <QSerialPort>

#include "csvLog.h"
#include "settings.h"

class Controller {

	std::shared_ptr<PumpControllerModel> pumpControllerModel;
	std::unique_ptr<Settings> settings;
	std::unique_ptr<QSerialPort> pSerialPort;
	std::unique_ptr<csvLog> log;
	MainWindow* pumpControllerView;
	bool readyToGo = false;

	void sendCommand(int, int);

public:

	explicit Controller(MainWindow*);
	~Controller() = default;

	void valveCloseCommand(char);
	void stopAirDelivery();
	bool serialPortInitialization(const QString&);
	void prepareTheGasAirMixture();
	void changeGasSupplyTime(int time);
	void startUpShuffleAirDelivery();
	void startUpSequenceAirDelivery();
	void manualSetting(const std::string& command);
	void cleaningAirSystem();
	bool isBufferClear();
	void clearBuffer();
	void setStartValue(double, int);
	void setStartValue(int, int);
	double getStartValue(int);
	bool isReady() const;
	void setReadyToGo(bool);
	int getSupplyTime() const;
	bool setSupplyTime(int);
	int getDelayTime() const;
	bool setDelayTime(int);
	void saveCurrentWorkSpace();
	void setComPortName(const std::string&);
	[[nodiscard]] std::string getComPortName() const;
	void setWorkingVolume(int);
	[[nodiscard]] int getWorkingVolume() const;

};
