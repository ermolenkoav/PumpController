#pragma once
#include "common.h"

class Settings {
	OdoratorModel* odoratorModel = nullptr;

public:
	Settings(OdoratorModel* _odoratorModel);

	void saveWorkspace();
	void loadWorkspace();
	void saveCurrentData();
};