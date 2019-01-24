#pragma once
#include "common.h"

class OdoratorModel {
	double startValue[NumValves] = {};
	int startTimes[NumValves] = {};

	void shuffleValves(int *arr, size_t n);
	int calculateValue(const double, int) const;

public:
	std::list<char> sendCommandData;
	const std::array<char, NumValves> cartridgeName = { 'A', 'B', 'C', 'D', 'E', 'F' };

	void calculatePrepareTheGasAirMixture();
	void randomGasAirSequence();

	void setStartValue(const double, const int);
	void setTimes(const int, const int);
	void cleaningAirSystem();
};