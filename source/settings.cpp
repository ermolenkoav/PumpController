#include "settings.h"
using namespace web;

Settings::Settings(OdoratorModel* _odoratorModel) {
	odoratorModel = _odoratorModel;
}

auto strConcentration = L"Consentration";
auto strTimes = L"Times";
auto strExecuteSequence = L"Execute sequence";
auto strGeometry = L"Geometry";
auto strComPort = L"Com Port";
auto strSettings = L"Settings";

void Settings::saveWorkspace() {
	if (std::wofstream settingFile(settingsFileName); settingFile.is_open()) {
		json::value concentration, times, geometry, executeSequence, comPort, settings;
		for (auto it = 0; it < NumValves; it++) {
			std::wstring valveIndex = std::to_wstring(it);
			concentration[strConcentration][valveIndex] = json::value(odoratorModel->getValue(it));
			times[strTimes][valveIndex] = json::value(odoratorModel->getTimes(it));
		}
		executeSequence[strExecuteSequence] = json::value(0);
		geometry[strGeometry] = json::value(0);
		comPort[strComPort] = json::value::string(L"COM3");
		settings[strSettings] = json::value::array({ concentration, times, executeSequence, geometry, comPort });
		settingFile << settings.serialize().c_str();
	}
}

void Settings::loadWorkspace() {
	if (std::wifstream settingFile(settingsFileName); settingFile.is_open()) {
		std::wstringstream sstr;
		sstr << settingFile.rdbuf();
		auto jSettings = json::value::parse(sstr);
		
		qDebug() << endl << DisplayJSONValue(jSettings);
		qDebug() << loadJSONValue(jSettings) << endl;

		settingFile.close();
	}  
}

std::wstring Settings::loadJSONValue(web::json::value v) {
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
					static utility::string_t parentName;

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
					}
				}
			}
			else if (v.is_array()) {
				// Loop over each element in the array
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
			else if (v.is_array()){
				// Loop over each element in the array
				for (size_t index = 0; index < v.as_array().size(); ++index){
					const web::json::value& value = v.as_array().at(index);

					ss << "Array: " << index << std::endl;
					ss << DisplayJSONValue(value);
				}
			}
			else{
				ss << "Value: " << v.serialize() << std::endl;
			}
		}
	}
	catch (const std::exception & e){
		qDebug() << endl << e.what() << endl;
		ss << "Value: " << v.serialize() << std::endl;
	}

	return ss.str();
}

void Settings::saveCurrentData() {
	if(std::wifstream settingFile(logFileName); settingFile.is_open()) {}
}
