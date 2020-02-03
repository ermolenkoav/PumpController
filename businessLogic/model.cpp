#include "model.h"

void OdoratorModel::addCustomCommand(std::string command) {
	for (auto it = 0; it < command.length(); it++) {
		sendCommandData.push_back(command[it]);
	}
}
void OdoratorModel::cleaningAirSystem() {
	for (auto it = 0; it < NumValves; it++) {
		sendCommandData.push_back(cartridgeName[it]);
		sendCommandData.push_back('A');
	}
}
void OdoratorModel::stopAirSystem() {
		sendCommandData.push_back('A');
		sendCommandData.push_back('P');
}
void OdoratorModel::valveCloseCommand(char valve) {
	sendCommandData.push_back(valve);
	sendCommandData.push_back('L');
}
void OdoratorModel::gasSupplyTime(int seconds) {
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
void OdoratorModel::calculatePrepareTheGasAirMixture() {
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
bool OdoratorModel::setSupplyTime(int temp) {
	if ((SupplyTimeMin <= temp) && (SupplyTimeMax >= temp)) {
		supplyTime = temp;
	}
	else {
		supplyTime = 3;
		return false;
	}
	return true;
}
bool OdoratorModel::setDelayTime(int temp) {
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
void OdoratorModel::checkStatus() {
	while (!sendCommandData.empty()) {
		sendCommandData.push_back(cartridgeName[5]);
		sendCommandData.push_back('Y');
	}
}*/
void OdoratorModel::randomGasAirDelivery() {
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
void OdoratorModel::sequenceGasAirDelivery() {
	for (auto it = 0; it < NumValves; it++) {
		if (0 == startValueDouble[it]) {
			continue;
		}
		sendCommandData.push_back(cartridgeName[it]);
		sendCommandData.push_back('S');
	}
}
int OdoratorModel::calculateValue(const double _initialValue, int _startVolume = 10) const {
	return static_cast<int>(std::round(log(_initialValue / _finalValue) / log(_vesselVolume / _startVolume)));
}
void OdoratorModel::shuffleValves(int *arr, size_t n) {
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
void OdoratorModel::setValue(const double _value, const int _iter) {
	//if ((_finalValue <= _value) || (0 > _value)) 
	{
		startValueDouble[_iter] = _value;
	}
}
void OdoratorModel::setValue(const int _value, const int _iter) {
	if ((_value >= 0) && (_value <= 10)) {
		startValueInt[_iter] = _value;
	}
}
double OdoratorModel::getValue(int index) const {
	return startValueDouble[index];
}
void OdoratorModel::clearBuffer() {
	sendCommandData.clear();
}
bool OdoratorModel::isBufferClear() {
	return sendCommandData.empty();
}
int OdoratorModel::getSupplyTime() const {
	return supplyTime;
}
int OdoratorModel::getDelayTime() const {
	return delayTime * 1000;
}
void OdoratorModel::setComPortName(const utility::string_t& name) {
	comPortName = name;
}
utility::string_t OdoratorModel::getComPortName() const {
	return comPortName;
}
int OdoratorModel::getWorkingVolume() const {
	return static_cast<int>(workingVolume - '0');
}
void OdoratorModel::setWorkingVolume(int vol) {
	workingVolume = static_cast<char>(vol + '0');
}