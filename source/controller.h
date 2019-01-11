#pragma once
#include "pch.h"
#include "common.h"

class QSerialPort;

class Controller {
	// variable:
	std::list<char> sendCommandData;
	const std::array<char, NumValves> cartridgeName = { 'A', 'B', 'C', 'D', 'E', 'F' };

	QSerialPort *pSerialPort{};

	double _startValue[NumValves] = {};
	int _startTimes[NumValves] = {};

public:
	Controller();
	~Controller();

	int calculateValue(const double, int) const;
	bool devisesActivated(QString);
	void setStartValue(const double, const int);
	void setTimes(const int, const int);
	void calculateData();
	void sendCommand();
	void clearBuffer();
};
