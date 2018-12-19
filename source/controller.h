#pragma once
#include "pch.h"
#include "common.h"

class QSerialPort;

class Controller {
	double _initialValue = 0;

	QSerialPort *pSerialPort;
	double _startValue[NumValves] = {};
	int StartTimes[NumValves] = {};

public:
	Controller();
	~Controller();

	int CalculateValue(double initialValue);
	bool devisesActivated(QString);
	void setStartValue(double _startValue[]);
	void setStartTimes(int _startTimes[]);
};
