#include "mainwindow.h"
#include "version.h"

MainWindow::~MainWindow() {
	delete controller;
	qDebug() << "Delete Main Window.";
} 
MainWindow::MainWindow(QWidget *parent) : QWidget(parent = nullptr) {
	setWindowIcon(QIcon(":APPLICATION_LOGO"));
	setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
	setWindowTitle(APPLICATION_NAME);
	controller = new Controller(this);

	timer = new QTimer(this);
	timer->setInterval(controller->getDelayTime() * 1000);

	createMainWindowLayout();
	loadSettings();

    // Signals:
	connect(pcmdSend,				&QPushButton::clicked, this, &MainWindow::prepareTheGasAirMixtureButtonClicked);
	connect(pcmdCleaningAirSystem,	&QPushButton::clicked, this, &MainWindow::cleaningAirSystemButtonClicked);
	connect(pcmdSendSP,				&QPushButton::clicked, this, &MainWindow::manualSettingClicked);
	connect(pcmdSearch,				&QPushButton::clicked, this, &MainWindow::searchButtonClicked);
	connect(pcmdStart,				&QPushButton::clicked, this, &MainWindow::startButtonClicked);
	connect(pcmdPause,				&QPushButton::clicked, this, &MainWindow::pauseButtonClicked);
	connect(pcmdStop,				&QPushButton::clicked, this, &MainWindow::stopButtonClicked);
	connect(pchbGCm3,				&QPushButton::clicked, this, &MainWindow::changeViewClicked);
	connect(pchbTimes,				&QPushButton::clicked, this, &MainWindow::changeViewClicked);
	connect(timer,					&QTimer::timeout,	   this, &MainWindow::timeOutSlot);
	connect(pspbSupplyTime,			QOverload<int>::of(&QSpinBox::valueChanged), 
		[=]() {
		setSypplyTime(pspbSupplyTime->value()); 
		});
	connect(pspbDelayTime,			QOverload<int>::of(&QSpinBox::valueChanged), 
		[=]() { 
		setDalayTime(pspbDelayTime->value());
		});
}
/************************************LOAD LAST SETTINGS************************************/
void MainWindow::loadSettings() {
	for (auto iterate = 0; iterate < NumValves; ++iterate) {  // All previous concentrations
		ptxtConcentration[iterate]->setText(QString::number(controller->getStartValue(iterate)));
	}
	pspbDelayTime->setValue(controller->getDelayTime());
}
std::pair<int, int> MainWindow::getWindowPos() {
	auto windowPosPoint = pos();
	std::pair<int, int> winPos(windowPosPoint.x(), windowPosPoint.y());
	return winPos;
}
void MainWindow::setWindowPos(std::array<int, 2> windowPos) {
	move(windowPos[0], windowPos[1]);
}
std::wstring MainWindow::getComPortName() {
	return comPortName;
}
void MainWindow::setComPortName(std::wstring &_comPortName) {
	comPortName = _comPortName;
}
void MainWindow::autoConnectToComPort(const QString& text) {
	if (!comPortName.empty()) {
		connectEvent(text);
	}
}
void MainWindow::connectEvent(const QString& text) {
	if (controller->serialPortInitialization(text)) {
		comPortName = text.toStdWString();
		pcmdSearch->setText("Connected");
		pcmdSearch->setCheckable(false);
		std::this_thread::sleep_for(std::chrono::seconds(3));
		controller->cleaningAirSystem();
	}
}
std::wstring MainWindow::saveDelayTime() {
	return pspbDelayTime->text().toStdWString();
}
void MainWindow::setSypplyTime(int time) {
	if (!controller->setSupplyTime(time)) {
		errorMessage("An error has occured !");
	}
	controller->changeGasSupplyTime(controller->getSupplyTime());
}
void MainWindow::setDalayTime(int time) {
	if (!controller->setDelayTime(time)) {
		errorMessage("An error has occured !");
	}

	timer->setInterval(time * 1000);
	// To Do : Commant tp change time
}
/************************************CREATE VIEW LAYOUT************************************/
void MainWindow::createMainWindowLayout() {
	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(createConnectionLayout());
	mainLayout->addWidget(createSetUpLayout());
	mainLayout->addWidget(createExecuteLayout());
	mainLayout->addWidget(createManualSettingLayout());
	setLayout(mainLayout);
}
QGroupBox* MainWindow::createConnectionLayout() {
	auto pgbConnectionLayout = new QGroupBox(tr("Connection"), this);
	auto ploConnectionLayout = new QGridLayout(this);

	pcmdSearch = new QPushButton("Search", this);
	ploConnectionLayout->addWidget(pcmdSearch);

	pgbConnectionLayout->setLayout(ploConnectionLayout);
	return pgbConnectionLayout;
}
QGroupBox* MainWindow::createSetUpLayout() {
	pgbSetOfAllValves = new QGroupBox(tr("Set up"), this);
	ploSetOfAllValves = new QGridLayout(pgbSetOfAllValves);

	auto ploViewSetUp = new QHBoxLayout(this);;
	pchbGCm3 = new QRadioButton("g/cm^3", this);
	pchbGCm3->setChecked(true);
	pchbTimes = new QRadioButton("Times to mix", this);
	ploViewSetUp->addWidget(pchbGCm3);
	ploViewSetUp->addWidget(pchbTimes);
	ploSetOfAllValves->addLayout(ploViewSetUp, 0, 0);
	

	QGroupBox* pgbValveSetUp[NumValves];
	QHBoxLayout* ploValveLayout[NumValves];
	
	for (auto iter = 0; iter < NumValves; ++iter) {
		pgbValveSetUp[iter] = new QGroupBox(tr("Cartridge %1").arg(iter + 1), pgbSetOfAllValves);
		ploValveLayout[iter] = new QHBoxLayout(pgbSetOfAllValves);

		plblTimes[iter] = new QLabel("Concentrations, g/cm^3", pgbSetOfAllValves);
		ploValveLayout[iter]->addWidget(plblTimes[iter]);

		ptxtConcentration[iter] = new QLineEdit(pgbSetOfAllValves);
		ploValveLayout[iter]->addWidget(ptxtConcentration[iter]);

		pgbValveSetUp[iter]->setLayout(ploValveLayout[iter]);
		ploSetOfAllValves->addWidget(pgbValveSetUp[iter]);
	}

	pcmdSend = new QPushButton("Prepare a gas air mixture", pgbSetOfAllValves);
	ploSetOfAllValves->addWidget(pcmdSend);

	pgbSetOfAllValves->setLayout(ploSetOfAllValves);
	return pgbSetOfAllValves;
}
QGroupBox* MainWindow::createExecuteLayout() {
	auto pgbExecuteLayout = new QGroupBox(tr("Execute sequence"), this);
	auto ploExecuteLayout = new QGridLayout(this);

	auto plblSupplyTime = new QLabel("Supply Time, s", this);
	ploExecuteLayout->addWidget(plblSupplyTime, 0, 0, Qt::AlignCenter);
	pspbSupplyTime = new QSpinBox(this);
	pspbSupplyTime->setMinimum(SupplyTimeMin);
	pspbSupplyTime->setMaximum(SupplyTimeMax);
	pspbSupplyTime->setValue(controller->getSupplyTime());
	ploExecuteLayout->addWidget(pspbSupplyTime, 0, 1);

	auto plblDelayTime = new QLabel("Delay Time, s", this);
	ploExecuteLayout->addWidget(plblDelayTime, 1, 0, Qt::AlignCenter);
	pspbDelayTime = new QSpinBox(this);
	pspbDelayTime->setMinimum(DelayTimeMin);
	pspbDelayTime->setMaximum(DelayTimeMax);
	pspbDelayTime->setValue(controller->getDelayTime());
	ploExecuteLayout->addWidget(pspbDelayTime, 1, 1);

	prbtSequenceStart = new QRadioButton("Sequence Start", this);
	ploExecuteLayout->addWidget(prbtSequenceStart, 2, 0);
	prbtSequenceStart->setChecked(true);
	prbtShuffleStart = new QRadioButton("Shuffle Start", this);
	ploExecuteLayout->addWidget(prbtShuffleStart, 2, 1);

	pcmdStart = new QPushButton("Start", this);
	ploExecuteLayout->addWidget(pcmdStart, 3, 0);

	pcmdStop = new QPushButton("Stop", this);
	ploExecuteLayout->addWidget(pcmdStop, 3, 1);

	pcmdPause = new QPushButton("Pause", this);
	ploExecuteLayout->addWidget(pcmdPause, 4, 0);

	pcmdCleaningAirSystem = new QPushButton("Cleaning Air System", this);
	ploExecuteLayout->addWidget(pcmdCleaningAirSystem, 4, 1);

	pgbExecuteLayout->setLayout(ploExecuteLayout);
	return pgbExecuteLayout;
}
QGroupBox* MainWindow::createManualSettingLayout() {
	auto pgbManualSettingLayout = new QGroupBox(tr("Manual setting"), this);
	auto ploManualSettingLayout = new QGridLayout(this);

	ptxtSerialPort = new QLineEdit(this);
	ploManualSettingLayout->addWidget(ptxtSerialPort, 0, 0);

	pcmdSendSP = new QPushButton("Send", this);
	ploManualSettingLayout->addWidget(pcmdSendSP, 0, 1);

	//pcmdChangeView = new QPushButton("Change View", this);
	//ploManualSettingLayout->addWidget(pcmdChangeView, 1, 0);

	pgbManualSettingLayout->setLayout(ploManualSettingLayout);
	return pgbManualSettingLayout;
}
/********************************RESPOND EVENTS AND SIGNALS********************************/
void MainWindow::searchButtonClicked() {
 	auto pcmbListOfPorts = new QComboBox(pcmdSearch);
	auto serialPortInfos = QSerialPortInfo::availablePorts();
	for (auto serialPortInfo : serialPortInfos) {
		pcmbListOfPorts->addItem(serialPortInfo.portName());
	}
	pcmbListOfPorts->show();
	connect(pcmbListOfPorts, QOverload<const QString &>::of(&QComboBox::activated),
		[=](const QString &text) {
			connectEvent(text);
			pcmbListOfPorts->hide();
			pcmbListOfPorts->clear();
	});
}
void MainWindow::prepareTheGasAirMixtureButtonClicked() {
	if (pchbGCm3->isChecked()) {
		for (auto iterate = 0; iterate < NumValves; ++iterate) {
			auto stTimes = ptxtConcentration[iterate]->text();
			controller->setStartValue(stTimes.toDouble(), iterate);
		}
		controller->prepareTheGasAirMixture();
	}
	if (pchbTimes->isChecked()) {
		for (auto iterate = 0; iterate < NumValves; ++iterate) {
			auto stTimes = ptxtConcentration[iterate]->text();
			controller->setStartValue(stTimes.toInt(), iterate);
		}
		controller->prepareTheGasAirMixture();
	}
}
void MainWindow::startButtonClicked() {
	controller->setReadyToGo(true);
	if (prbtSequenceStart->isChecked()) {
		controller->startUpSequenceAirMixture();
	}
	if (prbtShuffleStart->isChecked()) {
		controller->startUpShuffleAirMixture();
	}
	timer->start(controller->getSupplyTime());
}
void MainWindow::cleaningAirSystemButtonClicked() {
	controller->cleaningAirSystem();
}
void MainWindow::stopButtonClicked() {
	controller->setReadyToGo(false);
	timer->stop();
	controller->clearBuffer();
}
void MainWindow::pauseButtonClicked() {
	controller->setReadyToGo(false);
	timer->stop();
}
void MainWindow::timeOutSlot() {
	if (true) { controller->startUpSequenceAirMixture(); }
	else { controller->startUpShuffleAirMixture(); }
	
}
void MainWindow::manualSettingClicked() {
	auto command = ptxtSerialPort->text();
	controller->manualSetting(command.toStdString());
}
void MainWindow::changeViewClicked() {
	if (pchbTimes->isChecked()) {
		for (auto i : plblTimes) {
			i->setText("Times to mix");
		}
		
	}
	if (pchbGCm3->isChecked()) {
		for (auto i : plblTimes) {
			i->setText("Concentrations, g/cm^3");
		}
		
	}
}
void MainWindow::errorMessage(const QString& errorMsg) {
	QMessageBox messageBox;
	messageBox.critical(0, "Error", errorMsg);
	messageBox.setFixedSize(500, 200);
}