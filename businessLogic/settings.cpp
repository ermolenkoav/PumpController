#include "settings.h"
#include "mainwindow.h"
#include "model.h"
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Stringifier.h>

Settings::Settings(std::shared_ptr<PumpControllerModel> pModel, MainWindow* pView)
		 : pumpControllerModel{std::move( pModel )}, pumpControllerView { pView } {}

void Settings::saveWorkspace() {
	if (std::ofstream settingFile(settingsFileName); settingFile.is_open()) {
		// Window geometry:
        Poco::JSON::Array::Ptr geometry = new Poco::JSON::Array();
        geometry->set(0, pumpControllerView->getWindowPos().first);
        geometry->set(1, pumpControllerView->getWindowPos().second);
		// Valves value:
        Poco::JSON::Array::Ptr concentration = new Poco::JSON::Array();
		for (auto it = 0; it < NumValves; it++) {
            concentration->set(it, pumpControllerModel->getValue(it));
		}

        Poco::JSON::Object::Ptr settings = new Poco::JSON::Object();
		settings->set(cstrWorkingVolume, pumpControllerModel->getWorkingVolume());
        settings->set(cstrSupplyTimes, pumpControllerModel->getSupplyTime());
        settings->set(cstrDelayTimes, pumpControllerModel->getDelayTime());
        settings->set(cstrComPort, pumpControllerModel->getComPortName());
        settings->set(cstrConcentration, concentration);
        settings->set(cstrGeometry, geometry);

		std::ostringstream oss;
		Poco::JSON::Stringifier::stringify(settings, oss, 4);
		settingFile << oss.str();
	}
}
void Settings::loadWorkspace() {
	if (std::ifstream settingFile(settingsFileName); settingFile.is_open()) {
		std::string jsonData((std::istreambuf_iterator<char>(settingFile)),
							  std::istreambuf_iterator<char>());
		Poco::JSON::Parser parser;
		try {
			auto result = parser.parse(jsonData);
			auto object = result.extract<Poco::JSON::Object::Ptr>();

			pumpControllerModel->setComPortName(object->getValue<std::string>(cstrComPort));
			pumpControllerModel->setSupplyTime(object->getValue<int>(cstrSupplyTimes));
			pumpControllerModel->setDelayTime(object->getValue<int>(cstrDelayTimes));
			pumpControllerModel->setWorkingVolume(object->getValue<int>(cstrWorkingVolume));

			auto concentration = object->getArray(cstrConcentration);
			for (auto i = 0; i < NumValves; ++i) {
				pumpControllerModel->setValue(concentration->getElement<double>(i), i);
			}

			auto geometry = object->getArray(cstrGeometry);
			for(auto it = 0; it < 2; ++it) {
				windowPos[it] = geometry->getElement<int>(it);
			}
			pumpControllerView->setWindowPos(windowPos);
		}
		catch(...) {}
	}
}