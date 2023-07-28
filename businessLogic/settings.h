#pragma once
#include "pch.h"

class PumpControllerModel;
class MainWindow;

class Settings {

	std::shared_ptr<PumpControllerModel> pumpControllerModel;
	MainWindow* pumpControllerView;

	std::array<int, 2> windowPos = {1600,170};
	std::string comPortName;

	std::string settingsFileName = ( "settings.json" );
	std::string logFileName = ("logs.json");

	std::string cstrConcentration = ("Consentration");
	std::string cstrGeometry = ("Geometry");
	std::string cstrComPort = ("Com Port");
	std::string cstrSettings = ("Settings");
	std::string cstrSupplyTimes = ("Supply Times");
	std::string cstrDelayTimes = ("Delay Times");
	std::string cstrWorkingVolume = ("Working Volume");

public:

	Settings(std::shared_ptr<PumpControllerModel>, MainWindow*);

	void saveWorkspace();
	void loadWorkspace();

};