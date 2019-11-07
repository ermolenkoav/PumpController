#pragma once
#include "common.h"

class OdoratorModel {
	double startValueDouble[NumValves] = { 0 };
	int startValueInt[NumValves] = { 0 };

	const std::array<char, NumValves> cartridgeName = { 'A', 'B', 'C', 'D', 'E', 'F' };

	void shuffleValves(int *arr, size_t n);
	int calculateValue(const double, int) const;

public:
	std::list<char> sendCommandData;
	// control commands:
	void calculatePrepareTheGasAirMixture();
	void randomGasAirSequence();
	void sequenceGasAirSequence();
	void addCustomCommand(std::string command);
	void cleaningAirSystem();
	bool isBufferClear();
	void gasSupplyTime(int seconds);
	void gasDalayTime(int seconds);
	void checkStatus();

	void setValue(const double, const int);
	double getValue(int index) const;
	void setValue(const int, const int);
	void clearBuffer();
};