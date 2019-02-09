#include "settings.h"

using namespace web;


Settings::Settings(OdoratorModel* _odoratorModel) {
	odoratorModel = _odoratorModel;
}

void Settings::saveWorkspace() {
	std::wofstream settingFile(settingsFile);
	if (settingFile.is_open()) {
		auto putValue = json::value::object();

		for (auto it = 0; it < NumValves; it++) {
			putValue[L"Valves values"] = json::value(odoratorModel->getValue(it));
			settingFile << putValue.serialize().c_str() << std::endl;
		}
	}
}

void Settings::loadWorkspace() {
	std::wifstream settingFile(settingsFile);
	std::wstringstream sstr;

	if (settingFile.is_open()) {
		sstr << settingFile.rdbuf();
		
		//auto getValue = json::value::parse(sstr);

		//settingFile.close();
		//qDebug << sstr.str();
	}  

	for (auto it = 0; it < NumValves; it++) {
		odoratorModel->setValue(1e-10, it);
	}
	 
	for (auto it = 0; it < NumValves; it++) {
		odoratorModel->setTimes(1, it);
	}
}

void Settings::saveCurrentData() {
	std::wifstream settingFile(logFile);
}
