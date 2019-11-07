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
	createMainWindowLayout();
	controller = new Controller(this);
	loadSettings();

	timer = new QTimer(this);
	supplyTime = 20000;
	delayTime = 25000;
	timer->setInterval(delayTime);
    // Signals: 
	connect(pcmdSearch,				&QPushButton::clicked, this, &MainWindow::searchButtonClicked);
	connect(pcmdSend,				&QPushButton::clicked, this, &MainWindow::prepareTheGasAirMixtureButtonClicked);
	connect(pcmdStart,				&QPushButton::clicked, this, &MainWindow::startButtonClicked);
	connect(pcmdStop,				&QPushButton::clicked, this, &MainWindow::stopButtonClicked);
	connect(pcmdPause,				&QPushButton::clicked, this, &MainWindow::pauseButtonClicked);
	connect(pcmdCleaningAirSystem,	&QPushButton::clicked, this, &MainWindow::cleaningAirSystemButtonClicked);
	connect(pcmdSendSP,				&QPushButton::clicked, this, &MainWindow::manualSettingClicked);
	connect(timer,					&QTimer::timeout,	   this, &MainWindow::timeOutSlot);
	connect(pspbSupplyTime,			QOverload<int>::of(&QSpinBox::valueChanged), 
		[=]() {
		setSypplyTime(pspbSupplyTime->value()); 
		controller->changeGasSupplyTime(MainWindow::supplyTime); 
		});
	connect(pspbDelayTime,			QOverload<int>::of(&QSpinBox::valueChanged), 
		[=]() { 
		setDalayTime(); 
		});
	connect(pchbGCm3,				&QPushButton::clicked, this, &MainWindow::changeViewClicked);
	connect(pchbTimes,				&QPushButton::clicked, this, &MainWindow::changeViewClicked);
}
/************************************LOAD LAST SETTINGS************************************/
void MainWindow::loadSettings() {
	for (auto iterate = 0; iterate < NumValves; ++iterate) {
		ptxtConcentration[iterate]->setText(QString::number(controller->getStartValue(iterate)));
	}
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
void MainWindow::setExecuteSequence(std::wstring &text) {
	pspbDelayTime->setValue(QString::fromStdWString(text).toInt());
}
std::wstring MainWindow::getExecuteSequence() {
	return pspbDelayTime->text().toStdWString();
}
void MainWindow::setSypplyTime(int time) {
	supplyTime = time;
}
void MainWindow::setDalayTime() {
	auto time = pspbDelayTime->value() * 1000;
	timer->setInterval(time);
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
	pspbSupplyTime->setMinimum(1);
	pspbSupplyTime->setMaximum(9);
	pspbSupplyTime->setValue(3);
	ploExecuteLayout->addWidget(pspbSupplyTime, 0, 1);

	auto plblDelayTime = new QLabel("Delay Time, s", this);
	ploExecuteLayout->addWidget(plblDelayTime, 1, 0, Qt::AlignCenter);
	pspbDelayTime = new QSpinBox(this);
	pspbDelayTime->setMinimum(1);
	pspbDelayTime->setMaximum(60);
	pspbDelayTime->setValue(delayTime / 1000);
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
	timer->start(supplyTime);
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