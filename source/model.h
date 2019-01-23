#pragma once
#include "common.h"

class OdoratorModel {
public:
	std::list<char> sendCommandData;
	const std::array<char, NumValves> cartridgeName = { 'A', 'B', 'C', 'D', 'E', 'F' };
};