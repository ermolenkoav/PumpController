#include "settings.h"
#include "cpprest/json.h" // https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Objects/JSON

using namespace web;


Settings::Settings(OdoratorModel* _odoratorModel) {
	odoratorModel = _odoratorModel;
}

void Settings::saveWorkspace() {
	std::wofstream settingFile(fileName);
	auto putvalue = json::value::object();

	for (auto it = 0; it < NumValves; it++) {
		putvalue[L"Valves values"] = json::value(odoratorModel->getValue(it));
		settingFile << putvalue.serialize().c_str() << std::endl;
	}
}

void Settings::loadWorkspace() {
	std::wifstream settingFile(fileName);
	auto getValue = json::value::object();

	for (auto it = 0; it < NumValves; it++) {

	}
}

void Settings::saveCurrentData() {

}
