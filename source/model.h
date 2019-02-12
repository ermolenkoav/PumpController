#pragma once
#include "common.h"

class OdoratorModel {
	double startValue[NumValves] = { 0 };
	int startTimes[NumValves] = { 0 };

	const std::array<char, NumValves> cartridgeName = { 'A', 'B', 'C', 'D', 'E', 'F' };

	void shuffleValves(int *arr, size_t n);
	int calculateValue(const double, int) const;

public:
	std::list<char> sendCommandData;
	// control commands:
	void calculatePrepareTheGasAirMixture();
	void randomGasAirSequence();
	void sequenceGasAirSequence();
	void cleaningAirSystem();
	void checkStatus();

	void setValue(const double, const int);
	double getValue(int index) const;

	void setTimes(const int, const int);
	int getTimes(int) const;
};