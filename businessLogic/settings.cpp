#include "settings.h"

Settings::Settings(std::shared_ptr<OdoratorModel> pModel, MainWindow* pView)
		 : odoratorModel{ pModel }, odoratorView { pView } {
	//TO DO: pointer to class is mast be const
}
void Settings::saveWorkspace() {
	if (std::ofstream settingFile(settingsFileName); settingFile.is_open()) {
		Json::Value settings;
		// Window geometry:
		settings[cstrSettings][cstrGeometry]["0"] = odoratorView->getWindowPos().first;
		settings[cstrSettings][cstrGeometry]["1"] = odoratorView->getWindowPos().second;
		// Working Volume
		settings[cstrSettings][cstrWorkingVolume] = odoratorModel->getWorkingVolume();
		// Last com port:
		settings[cstrSettings][cstrComPort] = odoratorModel->getComPortName();
		// Execute sequence:
		settings[cstrSettings][cstrDelayTimes] = odoratorModel->getDelayTime();
		settings[cstrSettings][cstrSupplyTimes] = odoratorModel->getSupplyTime();
		// Valves value:
		for (auto it = 0; it < NumValves; it++) {
			settings[cstrSettings][cstrConcentration][std::to_string(it)] = odoratorModel->getValue(it);
		}
		Json::StyledWriter styled;
		settingFile << styled.write(settings);
	}
}
void Settings::loadWorkspace() {
	if (std::ifstream settingFile(settingsFileName); settingFile.is_open()) {
		Json::Value jValue;
		settingFile >> jValue;
		odoratorModel->setComPortName(jValue[cstrSettings][cstrComPort].asString());
		odoratorModel->setSupplyTime(jValue[cstrSettings][cstrSupplyTimes].asInt());
		odoratorModel->setDelayTime(jValue[cstrSettings][cstrDelayTimes].asInt());
		odoratorModel->setWorkingVolume(jValue[cstrSettings][cstrWorkingVolume].asInt());
		for (auto it = jValue[cstrSettings][cstrConcentration].begin(); it != jValue[cstrSettings][cstrConcentration].end(); ++it) {
			odoratorModel->setValue(it->asDouble(), std::stoi(it.memberName()));
		}
		for (auto it = jValue[cstrSettings][cstrGeometry].begin(); it != jValue[cstrSettings][cstrGeometry].end(); ++it) {
			windowPos[std::stoi(it.memberName())] = it->asInt();
		}
	}
	odoratorView->setWindowPos(windowPos);
}