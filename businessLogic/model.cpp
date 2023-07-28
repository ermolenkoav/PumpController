#include "model.h"

void PumpControllerModel::addCustomCommand(const std::string& command) {
	for (const char & it : command) {
		sendCommandData.push_back(it);
	}
}
void PumpControllerModel::cleaningAirSystem() {
	for (auto it = 0; it < NumValves; it++) {
		sendCommandData.push_back(cartridgeName[it]);
		sendCommandData.push_back('A');
	}
}
void PumpControllerModel::stopAirSystem() {
		sendCommandData.push_back('A');
		sendCommandData.push_back('P');
}
void PumpControllerModel::valveCloseCommand(char valve) {
	sendCommandData.push_back(valve);
	sendCommandData.push_back('L');
}
void PumpControllerModel::gasSupplyTime(int seconds) {
	if ((seconds >= 0) && (seconds <= 9)) {
		for (auto it = 0; it < NumValves; it++) {
			if (0 == startValueDouble[it]) {
				continue;
			}
			sendCommandData.push_back(cartridgeName[it]);
			sendCommandData.push_back('T');
			sendCommandData.push_back('0' + seconds);
		}
	}
}
void PumpControllerModel::calculatePrepareTheGasAirMixture() {
	for (auto it = 0; it < NumValves; it++) {
		if (0 == startValueDouble[it]) {
			continue;
		}
		sendCommandData.push_back(cartridgeName[it]);
		sendCommandData.push_back('6');
		sendCommandData.push_back(workingVolume);
		auto iworkingVolume = static_cast<int>(workingVolume - '0') * 10;
		auto times = calculateValue(startValueDouble[it], iworkingVolume);
		if ( (0 <= times) && (20 >= times) ) {
			sendCommandData.push_back('0');
			sendCommandData.push_back((char)('0' + times));
		}
		else if ( (10 <= times) && (20 >= times) ) {
			sendCommandData.push_back('1');
			times -= 10;
			sendCommandData.push_back('0' + times);
		}
	}
}
bool PumpControllerModel::setSupplyTime(int temp) {
	if ((SupplyTimeMin <= temp) && (SupplyTimeMax >= temp)) {
		supplyTime = temp;
	}
	else {
		supplyTime = 3;
		return false;
	}
	return true;
}
bool PumpControllerModel::setDelayTime(int temp) {
	if ((DelayTimeMin <= temp) && (DelayTimeMax >= temp)) {
		delayTime = temp;
	}
	else {
		delayTime = 25;
		return false;
	}
	return true;
}
/*
void PumpControllerModel::checkStatus() {
	while (!sendCommandData.empty()) {
		sendCommandData.push_back(cartridgeName[5]);
		sendCommandData.push_back('Y');
	}
}*/
void PumpControllerModel::randomGasAirDelivery() {
	int sequence[] = { 0,1,2,3,4,5 }; // ToDo: from 0 to NumValves
	shuffleValves(sequence, NumValves);

	for (auto it = 0; it < NumValves; it++) {
		if (0 == startValueDouble[it]) {
			continue;
		}
		sendCommandData.push_back(cartridgeName[sequence[it]]);
		sendCommandData.push_back('S');
	}
}
void PumpControllerModel::sequenceGasAirDelivery() {
	for (auto it = 0; it < NumValves; it++) {
		if (0 == startValueDouble[it]) {
			continue;
		}
		sendCommandData.push_back(cartridgeName[it]);
		sendCommandData.push_back('S');
	}
}
int PumpControllerModel::calculateValue(const double _initialValue, int _startVolume = 10) const {
	return static_cast<int>(std::round(log(_initialValue / _finalValue) / log(_vesselVolume / _startVolume)));
}
void PumpControllerModel::shuffleValves(int *arr, size_t n) {
	if (n > 1) {
		size_t i;
		srand(time(nullptr));
		for (i = 0; i < n - 1; i++) {
			size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
			int t = arr[j];
			arr[j] = arr[i];
			arr[i] = t;
		}
	}
}
void PumpControllerModel::setValue(const double _value, const int _iter) {
	//if ((_finalValue <= _value) || (0 > _value)) 
	{
		startValueDouble[_iter] = _value;
	}
}
void PumpControllerModel::setValue(const int _value, const int _iter) {
	if ((_value >= 0) && (_value <= 10)) {
		startValueInt[_iter] = _value;
	}
}
double PumpControllerModel::getValue(int index) const {
	return startValueDouble[index];
}
void PumpControllerModel::clearBuffer() {
	sendCommandData.clear();
}
bool PumpControllerModel::isBufferClear() {
	return sendCommandData.empty();
}
int PumpControllerModel::getSupplyTime() const {
	return supplyTime;
}
int PumpControllerModel::getDelayTime() const {
	return delayTime;
}
void PumpControllerModel::setComPortName(const std::string& name) {
	comPortName = name;
}
std::string PumpControllerModel::getComPortName() const {
	return comPortName;
}
int PumpControllerModel::getWorkingVolume() const {
	return static_cast<int>(workingVolume - '0');
}
void PumpControllerModel::setWorkingVolume(int vol) {
	workingVolume = static_cast<char>(vol + '0');
}