#include "settings.h"

using namespace web;

Settings::Settings(OdoratorModel* _odoratorModel, MainWindow* _odoratorView) {
	//TO DO: pointer to class is mast be const
	odoratorModel = _odoratorModel;
	odoratorView = _odoratorView;
}

static auto cstrConcentration = L"Consentration";
static auto cstrGeometry = L"Geometry";
static auto cstrComPort = L"Com Port";
static auto cstrSettings = L"Settings";
static std::wstring cstrSupplyTimes = L"Supply Times";
static std::wstring cstrDelayTimes = L"Delay Times";
static std::wstring cstrWorkingVolume = L"Working Volume";

void Settings::saveWorkspace() {
	if (std::wofstream settingFile(settingsFileName); settingFile.is_open()) {
		json::value concentration, delayTimes, supplyTimes, geometry, comPort, settings, workingVolume;
		// Window geometry:
		auto windowPos = odoratorView->getWindowPos();
		geometry[cstrGeometry][L"0"] = json::value(windowPos.first);
		geometry[cstrGeometry][L"1"] = json::value(windowPos.second);
		// Working Volume
		workingVolume[cstrWorkingVolume] = json::value(odoratorModel->getWorkingVolume());
		// Last com port:
		comPort[cstrComPort] = json::value::string(odoratorModel->getComPortName());
		// Execute sequence:
		delayTimes[cstrDelayTimes] = json::value(odoratorModel->getDelayTime());
		supplyTimes[cstrSupplyTimes] = json::value(odoratorModel->getSupplyTime());
		// Valves value:
		for (auto it = 0; it < NumValves; it++) {
			concentration[cstrConcentration][std::to_wstring(it)] = json::value(odoratorModel->getValue(it));
		}
		// Compile all application settings:
		settings[cstrSettings] = json::value::array({ concentration, delayTimes, supplyTimes, geometry, comPort });
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

					if (!str.compare(cstrSupplyTimes)) {
						odoratorModel->setSupplyTime(value.as_integer());
						continue;
					}
					if (!str.compare(cstrDelayTimes)) {
						odoratorModel->setDelayTime(value.as_integer());
						continue;
					}
					if (!str.compare(cstrComPort)) {
						odoratorModel->setComPortName(value.as_string());
						continue;
					}
					if (!str.compare(cstrWorkingVolume)) {
						odoratorModel->setWorkingVolume(value.as_integer());
						continue;
					}

					if (value.is_object() || value.is_array()) {
						parentName = str;
						ss << loadJSONValue(value);
					}
					else {
						if (!parentName.compare(cstrConcentration)) {
							odoratorModel->setValue(value.as_double(), std::stoi(str));
						}
						if (!parentName.compare(cstrGeometry)) {
							windowPos[std::stoi(str)] = value.as_integer();
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
