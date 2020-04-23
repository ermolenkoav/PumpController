#include "settings.h"

Settings::Settings(std::shared_ptr<OdoratorModel> pModel, MainWindow* pView)
		 : odoratorModel{ pModel }, odoratorView { pView } {
	//TO DO: pointer to class is mast be const
}
void Settings::saveWorkspace() {
	if (std::ofstream settingFile(settingsFileName); settingFile.is_open()) {
		Json::Value concentration, delayTimes, supplyTimes, geometry, comPort, settings, workingVolume;
		// Window geometry:
		auto windowPos = odoratorView->getWindowPos();
		geometry[cstrGeometry]["0"] = windowPos.first;
		geometry[cstrGeometry]["1"] = windowPos.second;
		// Working Volume
		workingVolume[cstrWorkingVolume] = (odoratorModel->getWorkingVolume());
		// Last com port:
		comPort[cstrComPort] = (odoratorModel->getComPortName());
		// Execute sequence:
		delayTimes[cstrDelayTimes] = (odoratorModel->getDelayTime());
		supplyTimes[cstrSupplyTimes] = (odoratorModel->getSupplyTime());
		// Valves value:
		for (auto it = 0; it < NumValves; it++) {
			concentration[cstrConcentration][std::to_string(it)] = odoratorModel->getValue(it);
		}
		// Compile all application settings:
		settings[cstrSettings] =  concentration, delayTimes, supplyTimes, geometry, comPort, workingVolume ;
		Json::StyledWriter styled;
		settingFile << styled.write(settings);
	}
}
void Settings::loadWorkspace() {
	if (std::ifstream settingFile(settingsFileName); settingFile.is_open()) {
		Json::Value val;
		settingFile >> val;
		loadJSONValue(val);
	}
	odoratorView->setWindowPos(windowPos);
}
std::string Settings::loadJSONValue(Json::Value jValue) {
	odoratorModel->setComPortName(jValue[cstrComPort].asString());
	odoratorModel->setSupplyTime(jValue[cstrSupplyTimes].asInt());
	odoratorModel->setDelayTime(jValue[cstrDelayTimes].asInt());
	odoratorModel->setWorkingVolume(jValue[cstrWorkingVolume].asInt());
	
	
/*
windowPos[std::stoi(str)] = jValue[cstrGeometry].asInt();
odoratorModel->setValue(jValue.asDouble(), std::stoi(str));
	for (size_t index = 0; index < v.as_array().size(); ++index) {
		const web::json::value& value = v.as_array().at(index);
		ss << loadJSONValue(value);
	}
	
	parentName = str;
	ss << loadJSONValue(value);
*/
	return "";
}
void Settings::saveCurrentData() {
	if(std::ifstream settingFile(logFileName); settingFile.is_open()) {}
}
