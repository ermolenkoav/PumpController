#pragma once
#include "pch.h"
#include "common.h"

class OdoratorModel {
	void shuffleValves(int* arr, size_t n);
	int calculateValue(const double, int) const;

	// variables:
	const std::array<char, NumValves> cartridgeName = { 'A', 'B', 'C', 'D', 'E', 'F' };
	double startValueDouble[NumValves] = { 0 };
	int startValueInt[NumValves] = { 0 };
	char workingVolume = '2';
    utility::string_t comPortName = {};
	int supplyTime = {};
	int delayTime = {};

public:
	std::list<char> sendCommandData;
	// control commands:
	void calculatePrepareTheGasAirMixture();
	void randomGasAirDelivery();
	void sequenceGasAirDelivery();
	void addCustomCommand(std::string command);
	void cleaningAirSystem();
	bool isBufferClear();
	void gasSupplyTime(int seconds);

	void setValue(const double, const int);
	double getValue(int index) const;
	void setValue(const int, const int);
	void clearBuffer();

	int getSupplyTime() const;
	bool setSupplyTime(int);
	int getDelayTime() const;
	bool setDelayTime(int);
	void setComPortName(const utility::string_t&);
    utility::string_t getComPortName() const;
	void setWorkingVolume(int);
	int getWorkingVolume() const;
};