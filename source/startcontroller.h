#pragma once
#include "pch.h"
#include "common.h"

class StartController {
	void shuffle(int * arr, size_t n);

	QSerialPort *pSerialPort = nullptr;
	OdoratorModel *odoratorModel = nullptr;

	int _startSequence[NumValves] = { 0, 1, 2, 3, 4, 5 };
public:
	StartController(QSerialPort *_pSerialPort, OdoratorModel *_odoratorModel);
	~StartController();

	void getStartSequence();
	void setStartSequence(int value, int pos);
	void startOperations();
	
};