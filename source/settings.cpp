#include "settings.h"

using namespace web;

Settings::Settings(OdoratorModel* _odoratorModel, MainWindow* _odoratorView) {
	odoratorModel = _odoratorModel;
	odoratorView = _odoratorView;
}

static auto strConcentration = L"Consentration";
static auto strTimes = L"Times";
static auto strExecuteSequence = L"Execute sequence";
static auto strGeometry = L"Geometry";
static auto strComPort = L"Com Port";
static auto strSettings = L"Settings";

void Settings::saveWorkspace() {
	if (std::wofstream settingFile(settingsFileName); settingFile.is_open()) {
		json::value concentration, times, geometry, executeSequence, comPort, settings;
		// Valves value:
		for (auto it = 0; it < NumValves; it++) {
			concentration[strConcentration][std::to_wstring(it)] = json::value(odoratorModel->getValue(it));
			times[strTimes][std::to_wstring(it)] = json::value(odoratorModel->getTimes(it));
		}
		// Window geometry:
		auto windowPos = odoratorView->getWindowPos();
		geometry[strGeometry][L"0"] = json::value(windowPos.first);
		geometry[strGeometry][L"1"] = json::value(windowPos.second);
		// Last com port:
		comPort[strComPort] = json::value::string(odoratorView->getComPortName());
		// Execute sequence:
		executeSequence[strExecuteSequence] = json::value(odoratorView->getExecuteSequence());
		// Compile all application settings:
		settings[strSettings] = json::value::array({ concentration, times, executeSequence, geometry, comPort });
		settingFile << settings.serialize().c_str();
	}
}

void Settings::loadWorkspace() {
	if (std::wifstream settingFile(settingsFileName); settingFile.is_open()) {
		std::wstringstream sstr;
		sstr << settingFile.rdbuf();
		loadJSONValue(json::value::parse(sstr));
	}
	odoratorView->setWindowPos(windowPos);
}

std::wstring Settings::loadJSONValue(web::json::value v) {
	std::wstringstream ss;
	try {
		if (!v.is_null()) {
			if (v.is_object()) {
				for (auto iter = v.as_object().cbegin(); iter != v.as_object().cend(); ++iter) {
					const auto& str = iter->first;
					const auto& value = iter->second;
					static auto parentName = iter->first;

					if (value.is_object() || value.is_array()) {
						parentName = str;
						ss << loadJSONValue(value);
					}
					else {
						if (!parentName.compare(strConcentration)) {
							odoratorModel->setValue(value.as_double(), std::stoi(str));
						}
						if (!parentName.compare(strTimes)) {
							odoratorModel->setTimes(value.as_integer(), std::stoi(str));
						}
						if (!parentName.compare(strGeometry)) {
							windowPos[std::stoi(str)] = value.as_integer();
						}
						if (!parentName.compare(strComPort)) {
							odoratorView->setComPortName(value.to_string());
						}
						if (!parentName.compare(strExecuteSequence)) {
							odoratorView->setExecuteSequence(value.to_string());
						}
					}
				}
			}
			else if (v.is_array()) {
				for (size_t index = 0; index < v.as_array().size(); ++index) {
					const web::json::value& value = v.as_array().at(index);
					ss << loadJSONValue(value);
				}
			}
		}
	}
	catch (const std::exception & e) {
		qDebug() << endl << e.what() << endl;
	}

	return ss.str();
}


std::wstring Settings::DisplayJSONValue(web::json::value v) {
	std::wstringstream ss;
	try {
		if (!v.is_null()) {
			if (v.is_object()) {
				// Loop over each element in the object
				for (auto iter = v.as_object().cbegin(); iter != v.as_object().cend(); ++iter) {
					// It is necessary to make sure that you get the value as const reference
					// in order to avoid copying the whole JSON value recursively (too expensive for nested objects)
					const utility::string_t& str = iter->first;
					const web::json::value& value = iter->second;

					if (value.is_object() || value.is_array()) {
						ss << "Parent: " << str << std::endl;
						ss << DisplayJSONValue(value);
						ss << "End of Parent: " << str << std::endl;
					}
					else {
						ss << "str: " << str << ", Value: " << value.serialize() << std::endl;
					}
				}
			}
			else if (v.is_array()) {
				// Loop over each element in the array
				for (size_t index = 0; index < v.as_array().size(); ++index) {
					const web::json::value& value = v.as_array().at(index);

					ss << "Array: " << index << std::endl;
					ss << DisplayJSONValue(value);
				}
			}
			else {
				ss << "Value: " << v.serialize() << std::endl;
			}
		}
	}
	catch (const std::exception & e) {
		qDebug() << endl << e.what() << endl;
		ss << "Value: " << v.serialize() << std::endl;
	}

	return ss.str();
}

void Settings::saveCurrentData() {
	if(std::wifstream settingFile(logFileName); settingFile.is_open()) {}
}
