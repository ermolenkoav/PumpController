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
void OdoratorModel::gasSupplyTime(int seconds) {
	if ((seconds >= 0) || (seconds <= 9)) {
		auto timeChar = '0' + seconds;
		sendCommandData.clear();
		for (auto it = 0; it < NumValves; it++) {
			if (0 == startValueDouble[it]) {
				continue;
			}
			sendCommandData.push_back(cartridgeName[it]);
			sendCommandData.push_back('T');
			sendCommandData.push_back(seconds);
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
		sendCommandData.push_back('2');
		auto times = calculateValue(startValueDouble[it], 20);
		if (times <= 9) {
			sendCommandData.push_back('0');
		}
		sendCommandData.push_back(times + '0');
	}
}
void OdoratorModel::checkStatus() {
	while (!sendCommandData.empty()) {
		sendCommandData.push_back(cartridgeName[5]);
		sendCommandData.push_back('Y');
	}
}
void OdoratorModel::randomGasAirSequence() {
	int sequence[] = { 0,1,2,3,4,5 };
	shuffleValves(sequence, NumValves);

	for (auto it = 0; it < NumValves; it++) {
		if (0 == startValueDouble[it]) {
			continue;
		}
		sendCommandData.push_back(cartridgeName[sequence[it]]);
		sendCommandData.push_back('S');
	}
}
void OdoratorModel::sequenceGasAirSequence() {
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
	startValueDouble[_iter] = _value;
}
void OdoratorModel::setValue(const int _value, const int _iter) {
	startValueInt[_iter] = _value;
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