#include "settings.h"
#include "mainwindow.h"
#include "model.h"
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Stringifier.h>

Settings::Settings(std::shared_ptr<OdoratorModel> pModel, MainWindow* pView)
		 : odoratorModel{std::move( pModel )}, odoratorView { pView } {}

void Settings::saveWorkspace() {
	if (std::ofstream settingFile(settingsFileName); settingFile.is_open()) {
		// Window geometry:
        Poco::JSON::Array::Ptr geometry = new Poco::JSON::Array();
        geometry->set(0, odoratorView->getWindowPos().first);
        geometry->set(1, odoratorView->getWindowPos().second);
		// Valves value:
        Poco::JSON::Array::Ptr concentration = new Poco::JSON::Array();
		for (auto it = 0; it < NumValves; it++) {
            concentration->set(it, odoratorModel->getValue(it));
		}

        Poco::JSON::Object::Ptr settings = new Poco::JSON::Object();
		settings->set(cstrWorkingVolume, odoratorModel->getWorkingVolume());
        settings->set(cstrSupplyTimes, odoratorModel->getSupplyTime());
        settings->set(cstrDelayTimes, odoratorModel->getDelayTime());
        settings->set(cstrComPort, odoratorModel->getComPortName());
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

			odoratorModel->setComPortName(object->getValue<std::string>(cstrComPort));
			odoratorModel->setSupplyTime(object->getValue<int>(cstrSupplyTimes));
			odoratorModel->setDelayTime(object->getValue<int>(cstrDelayTimes));
			odoratorModel->setWorkingVolume(object->getValue<int>(cstrWorkingVolume));

			auto concentration = object->getArray(cstrConcentration);
			for (auto i = 0; i < NumValves; ++i) {
				odoratorModel->setValue(concentration->getElement<double>(i), i);
			}

			auto geometry = object->getArray(cstrGeometry);
			for(auto it = 0; it < 2; ++it) {
				windowPos[it] = geometry->getElement<int>(it);
			}
			odoratorView->setWindowPos(windowPos);
		}
		catch(...) {}
	}
}