#pragma once
#include "common.h"

class SetUpController {
	double _startValue[NumValves] = {};
	int _startTimes[NumValves] = {};

	QSerialPort *pSerialPort = nullptr;
	OdoratorModel *odoratorModel = nullptr;
public:
	~SetUpController();
	SetUpController(QSerialPort *_pSerialPort, OdoratorModel *_odoratorModel);

	int calculateValue(const double, int) const;
	bool devisesActivated(QString);
	void setStartValue(const double, const int);
	void setTimes(const int, const int);
	void calculateData();
	void sendCommand();
	void clearBuffer();
};
