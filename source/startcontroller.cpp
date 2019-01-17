#include "startcontroller.h"

StartController::~StartController() {
}

StartController::StartController(QSerialPort *_pSerialPort) {
	pSerialPort = _pSerialPort;
}

void StartController::getStartSequence() {
	shuffle(_startSequence, NumValves);
}

void StartController::setStartSequence(int value, int pos) {
	if (pos < 6) {
		_startSequence[pos] = value;
	}
}

void StartController::startOperations() {

}

void StartController::shuffle(int *arr, size_t n) {
	if (n > 1) {
		size_t i;
		srand(time(NULL));
		for (i = 0; i < n - 1; i++) {
			size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
			int t = arr[j];
			arr[j] = arr[i];
			arr[i] = t;
		}
	}
}