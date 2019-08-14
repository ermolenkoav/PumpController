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
	supplyTime = 3;
	delayTime = 15000;
	timer->setInterval(delayTime);
    // Signals: 
	connect(pcmdSearch,				&QPushButton::clicked, this, &MainWindow::searchButtonClicked);
	connect(pcmdSend,				&QPushButton::clicked, this, &MainWindow::prepareTheGasAirMixtureButtonClicked);
	connect(pcmdShuffleStart,		&QPushButton::clicked, this, &MainWindow::shuffleStartButtonClicked);
	connect(pcmdSequenceStart,		&QPushButton::clicked, this, &MainWindow::sequenceStartButtonClicked);
	connect(pcmdStop,				&QPushButton::clicked, this, &MainWindow::stopButtonClicked);
	connect(pcmdCleaningAirSystem,	&QPushButton::clicked, this, &MainWindow::cleaningAirSystemButtonClicked);
	connect(pcmdSendSP,				&QPushButton::clicked, this, &MainWindow::manualSettingClicked);
	connect(timer,					&QTimer::timeout,	   this, &MainWindow::timeOutSlot);
	connect(pspbSupplyTime,			QOverload<int>::of(&QSpinBox::valueChanged), [=]() {
				setSypplyTime(pspbSupplyTime->value()); controller->changeGasSupplyTime(MainWindow::supplyTime); });
	connect(pspbDelayTime,			QOverload<int>::of(&QSpinBox::valueChanged), [=]() { setDalayTime(); });
	connect(pchbGCm3,				&QPushButton::clicked, this, &MainWindow::changeViewClicked);
	connect(pchbTimes,				&QPushButton::toggled, this, &MainWindow::changeViewClicked);
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

	pcmdSend = new QPushButton("Set Up", pgbSetOfAllValves);
	ploSetOfAllValves->addWidget(pcmdSend);

	pgbSetOfAllValves->setLayout(ploSetOfAllValves);
	return pgbSetOfAllValves;
}
QGroupBox* MainWindow::createExecuteLayout() {
	auto pgbExecuteLayout = new QGroupBox(tr("Execute sequence"), this);
	auto ploExecuteLayout = new QGridLayout(this);

	pcmdSequenceStart = new QPushButton("Sequence Start", this);
	ploExecuteLayout->addWidget(pcmdSequenceStart, 0, 1);
	pcmdShuffleStart = new QPushButton("Shuffle Start", this);
	ploExecuteLayout->addWidget(pcmdShuffleStart, 0, 0);

	pcmdStop = new QPushButton("Stop", this);
	ploExecuteLayout->addWidget(pcmdStop, 1, 1);
	pcmdCleaningAirSystem = new QPushButton("Cleaning Air System", this);
	ploExecuteLayout->addWidget(pcmdCleaningAirSystem, 1, 0);

	auto plblSupplyTime = new QLabel("Supply Time, s", this);
	ploExecuteLayout->addWidget(plblSupplyTime, 2, 0, Qt::AlignCenter);
	pspbSupplyTime = new QSpinBox(this);
	pspbSupplyTime->setMinimum(1);
	pspbSupplyTime->setMaximum(9);
	pspbSupplyTime->setValue(3);
	ploExecuteLayout->addWidget(pspbSupplyTime, 2, 1);

	auto plblDelayTime = new QLabel("Delay Time, s", this);
	ploExecuteLayout->addWidget(plblDelayTime, 3, 0, Qt::AlignCenter);
	pspbDelayTime = new QSpinBox(this);
	pspbDelayTime->setMinimum(1);
	pspbDelayTime->setMaximum(60);
	pspbDelayTime->setValue(delayTime/1000);
	ploExecuteLayout->addWidget(pspbDelayTime, 3, 1);

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

	pcmdChangeView = new QPushButton("Change View", this);
	ploManualSettingLayout->addWidget(pcmdChangeView, 1, 0);

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
	for (auto iterate = 0; iterate < NumValves; ++iterate) {
		auto stTimes = ptxtConcentration[iterate]->text();
		controller->setStartValue(stTimes.toDouble(), iterate);
	}
	controller->prepareTheGasAirMixture();
}
void MainWindow::shuffleStartButtonClicked() {
	controller->setReadyToGo(true);
	controller->startUpShuffleAirMixture();
	timer->start(supplyTime);
}
void MainWindow::sequenceStartButtonClicked() {
	controller->setReadyToGo(true);
	controller->startUpSequenceAirMixture();
	timer->start(supplyTime);
}
void MainWindow::cleaningAirSystemButtonClicked() {
	controller->cleaningAirSystem();
}
void MainWindow::stopButtonClicked() {
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
	else if (pchbGCm3->isChecked()) {
		for (auto i : plblTimes) {
			i->setText("Concentrations, g/cm^3");
		}
		
	}
}