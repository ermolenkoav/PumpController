#pragma once
#include "pch.h"
#include "common.h"

class Settings {
	OdoratorModel* odoratorModel = nullptr;
	MainWindow* odoratorView = nullptr;

	std::wstring DisplayJSONValue(web::json::value v);
	std::wstring loadJSONValue(web::json::value v);

	std::array<int, 2> windowPos = {1600,170};
	std::wstring comPortName;

	 utility::string_t settingsFileName = _XPLATSTR("settings.json");
	 utility::string_t logFileName = _XPLATSTR("logs.json");

	 utility::string_t cstrConcentration = _XPLATSTR("Consentration");
	 utility::string_t cstrGeometry = _XPLATSTR("Geometry");
	 utility::string_t cstrComPort = _XPLATSTR("Com Port");
	 utility::string_t cstrSettings = _XPLATSTR("Settings");
	 utility::string_t cstrSupplyTimes = _XPLATSTR("Supply Times");
	 utility::string_t cstrDelayTimes = _XPLATSTR("Delay Times");
	 utility::string_t cstrWorkingVolume = _XPLATSTR("Working Volume");

public:
	Settings(OdoratorModel* _odoratorModel, MainWindow* _odoratorView);

	void saveWorkspace();
	void loadWorkspace();
	void saveCurrentData();
};