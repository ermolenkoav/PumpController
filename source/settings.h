#pragma once
#include "common.h"

class Settings {
	OdoratorModel* odoratorModel = nullptr;
	MainWindow* odoratorView = nullptr;

	std::wstring DisplayJSONValue(web::json::value v);
	std::wstring loadJSONValue(web::json::value v);

	std::array<int, 2> windowPos = {1600,170};

public:
	Settings(OdoratorModel* _odoratorModel, MainWindow* _odoratorView);

	void saveWorkspace();
	void loadWorkspace();
	void saveCurrentData();
};