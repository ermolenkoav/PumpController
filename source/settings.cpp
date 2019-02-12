#include "settings.h"
using namespace web;

Settings::Settings(OdoratorModel* _odoratorModel) {
	odoratorModel = _odoratorModel;
}

void Settings::saveWorkspace() {
	if (std::wofstream settingFile(settingsFileName); settingFile.is_open()) {
		json::value putValue;
		for (auto it = 0; it < NumValves; it++) {
			std::wstring valveIndex = std::to_wstring(it);
			putValue[valveIndex] = json::value(odoratorModel->getValue(it));
		}
		settingFile << putValue.serialize().c_str();
	}
}

void Settings::loadWorkspace() {
	if (std::wifstream settingFile(settingsFileName); settingFile.is_open()) {

		std::wstringstream sstr;
		sstr << settingFile.rdbuf();
		
		auto json = json::value::parse(sstr);

		for (auto iter = json.as_object().cbegin(); iter != json.as_object().cend(); ++iter) {
			auto k = iter->first;
			auto v = iter->second;
			static auto it = 0;
			odoratorModel->setValue(v.as_double(), it++);

			qDebug() << k << "=" << v.as_double();
		}
		settingFile.close();
	}  
}

void Settings::saveCurrentData() {
	if(std::wifstream settingFile(logFileName); settingFile.is_open()) {}
}
