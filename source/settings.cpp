#include "settings.h"
#include "cpprest/json.h"
 
Settings::Settings(OdoratorModel* _odoratorModel) {
	odoratorModel = _odoratorModel;
}

void Settings::saveWorkspace() {
	std::wofstream settingFile(L"settings.json");
	web::json::value output;

	for (auto it = 0; it < NumValves; it++) {
		output[L"Valves-list"][L"valve"] =
			web::json::value(odoratorModel->getStartValue(it));

		settingFile << output.serialize().c_str() << std::endl;
	}
}

void Settings::loadWorkspace() {

}

void Settings::saveCurrentData() {

}
