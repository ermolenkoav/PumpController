#pragma once
#include "pch.h"
#include "common.h"

class StartController {
	void shuffle(int * arr, size_t n);

	QSerialPort *pSerialPort = nullptr;

	std::list<char> sendCommandData;
	int _startSequence[NumValves] = { 65, 66, 67, 68, 69, 70 };
	
public:
	StartController(QSerialPort *_pSerialPort);
	~StartController();

	void getStartSequence();
	void setStartSequence(int value, int pos);
	void startOperations();
	
};