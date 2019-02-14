#pragma once
#include "common.h"

class Settings {
	OdoratorModel* odoratorModel = nullptr;

	std::wstring DisplayJSONValue(web::json::value v);
	std::wstring loadJSONValue(web::json::value v);


public:
	Settings(OdoratorModel* _odoratorModel);

	void saveWorkspace();
	void loadWorkspace();

	
	
	void saveCurrentData();
};