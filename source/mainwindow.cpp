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
	timer->setInterval(controller->getDelayTime());

	createMainWindowLayout();
	loadSettings();
	//autoConnectToComPort();

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
	//connect(qApp,					SIGNAL(aboutToQuit()), this, SLOT(closeEvent()));
	//connect(exitAction,			&QAction::triggered,   this, &QApplication::quit);
	connect(timer,					&QTimer::timeout,	   this, &MainWindow::timeOutSlot);
	connect(pspbWorkingVolume,			QOverload<int>::of(&QSpinBox::valueChanged),
		[=]() {
		controller->setWorkingVolume(pspbWorkingVolume->value());
		});
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
	pspbDelayTime->setValue(controller->getDelayTime() / 1000);
	pspbSupplyTime->setValue(controller->getSupplyTime());
}
std::pair<int, int> MainWindow::getWindowPos() {
	auto windowPosPoint = pos();
	std::pair<int, int> winPos(windowPosPoint.x(), windowPosPoint.y());
	return winPos;
}
void MainWindow::setWindowPos(std::array<int, 2> windowPos) {
	move(windowPos[0], windowPos[1]);
}
void MainWindow::autoConnectToComPort() {
	if (!controller->getComPortName().empty()) 
	{
		connectEvent(toQString(controller->getComPortName()));
	}
}
void MainWindow::connectEvent(const QString& text) {
	if (controller->serialPortInitialization(text)) {
		controller->setComPortName(text.toStdWString());
		pcmdSearch->setText("Connected");
		pcmdSearch->setCheckable(false);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		//controller->cleaningAirSystem();
	}
}
void MainWindow::setSypplyTime(int time) {
	if (!controller->setSupplyTime(time)) {
		errorMessage(L"An error has occured!");
	}
	controller->changeGasSupplyTime(time);
}
void MainWindow::setDalayTime(int time) {
	if (!controller->setDelayTime(time)) {
		errorMessage(L"An error has occured!");
	}
	timer->setInterval(controller->getDelayTime());
}
void MainWindow::closeEvent(QCloseEvent *event) {
	QMessageBox::StandardButton resBtn = QMessageBox::question(this, APPLICATION_NAME,
		tr("Save privious session?\n"), QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
			QMessageBox::Yes);
	if (resBtn == QMessageBox::Cancel) {
		event->ignore();
	}
	if (resBtn == QMessageBox::Yes) {
		controller->saveCurrentWorkSpace();
	}
	event->accept();
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

	auto row = 0;

	auto plblWorkingVolume = new QLabel("Working Volume, %", this);
	ploExecuteLayout->addWidget(plblWorkingVolume, row, 0, Qt::AlignCenter);
	pspbWorkingVolume = new QSpinBox(this);
	pspbWorkingVolume->setMinimum(WorkingVolumeMin);
	pspbWorkingVolume->setMaximum(WorkingVolumeMax);
	ploExecuteLayout->addWidget(pspbWorkingVolume, row++, 1);

	auto plblSupplyTime = new QLabel("Supply Time, max 9s", this);
	ploExecuteLayout->addWidget(plblSupplyTime, row, 0, Qt::AlignCenter);
	pspbSupplyTime = new QSpinBox(this);
	pspbSupplyTime->setMinimum(SupplyTimeMin);
	pspbSupplyTime->setMaximum(SupplyTimeMax);
	ploExecuteLayout->addWidget(pspbSupplyTime, row++, 1);

	auto plblDelayTime = new QLabel("Delay Time, max 100s", this);
	ploExecuteLayout->addWidget(plblDelayTime, row, 0, Qt::AlignCenter);
	pspbDelayTime = new QSpinBox(this);
	pspbDelayTime->setMinimum(DelayTimeMin);
	pspbDelayTime->setMaximum(DelayTimeMax);
	ploExecuteLayout->addWidget(pspbDelayTime, row++, 1);

	prbtSequenceStart = new QRadioButton("Sequence Start", this);
	ploExecuteLayout->addWidget(prbtSequenceStart, row, 0);
	prbtSequenceStart->setChecked(true);
	prbtShuffleStart = new QRadioButton("Shuffle Start", this);
	ploExecuteLayout->addWidget(prbtShuffleStart, row, 1);

	pcmdStart = new QPushButton("Start", this);
	ploExecuteLayout->addWidget(pcmdStart, row, 0);

	pcmdStop = new QPushButton("Stop", this);
	ploExecuteLayout->addWidget(pcmdStop, row++, 1);

	pcmdPause = new QPushButton("Pause", this);
	ploExecuteLayout->addWidget(pcmdPause, row, 0);

	pcmdCleaningAirSystem = new QPushButton("Cleaning Air System", this);
	ploExecuteLayout->addWidget(pcmdCleaningAirSystem, row++, 1);

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

	pgbManualSettingLayout->setLayout(ploManualSettingLayout);
	return pgbManualSettingLayout;
}
/********************************RESPOND EVENTS AND SIGNALS********************************/
void MainWindow::cleaningAirSystemButtonClicked() {
	controller->cleaningAirSystem();
}
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
	controller->clearBuffer();
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
	controller->setReadyToGo(true);
}
void MainWindow::startButtonClicked() {
	timeOutSlot();
	timer->start(controller->getDelayTime());
}
void MainWindow::timeOutSlot() {
	if (prbtSequenceStart->isChecked()) {
		controller->startUpSequenceAirDelivery();
	}
	if (prbtShuffleStart->isChecked()) {
		controller->startUpShuffleAirDelivery();
	}
}
void MainWindow::stopButtonClicked() {
	controller->setReadyToGo(false);
	timer->stop();
	controller->clearBuffer();
}
void MainWindow::pauseButtonClicked() {
	timer->stop();
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
void MainWindow::errorMessage(const std::wstring& errorMsg) {
	QMessageBox messageBox;
	messageBox.critical(0, "Error", toQString(errorMsg));
	messageBox.setFixedSize(500, 200);
}
QString& MainWindow::toQString(const std::wstring& str) {
	QString qstr = QString::fromStdWString(str);
	return qstr;
}