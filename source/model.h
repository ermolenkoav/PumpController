#pragma once
#include "common.h"

class OdoratorModel {
	double startValueDouble[NumValves] = { 0 };
	int startValueInt[NumValves] = { 0 };

	const std::array<char, NumValves> cartridgeName = { 'A', 'B', 'C', 'D', 'E', 'F' };

	void shuffleValves(int *arr, size_t n);
	int calculateValue(const double, int) const;

	// variables:
	int supplyTime = {};
	int delayTime = {};
	char workingVolume = '2';
	std::wstring comPortName;

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
	void setComPortName(const std::wstring&);
	std::wstring getComPortName() const;
	void setWorkingVolume(int);
	int getWorkingVolume() const;
};