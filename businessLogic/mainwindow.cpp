#include "mainwindow.h"
#include "version.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent = nullptr) {
	setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
	setWindowTitle(APPLICATION_NAME);

	controller = std::make_unique<Controller>(this);

	createMainWindowLayout();
	loadSettings();

	timer = new QTimer(this);
	setTimerInterval();

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
	connect(timer,					&QTimer::timeout,	   this, &MainWindow::timeOutSlot);
	connect(pspbWorkingVolume,			QOverload<int>::of(&QSpinBox::valueChanged),
		[this]() { controller->setWorkingVolume(pspbWorkingVolume->value()); });
	connect(pspbSupplyTime,			QOverload<int>::of(&QSpinBox::valueChanged), 
		[this]() { setSupplyTime(pspbSupplyTime->value()); });
	connect(pspbDelayTime,			QOverload<int>::of(&QSpinBox::valueChanged), 
		[this]() { setDelayTime(pspbDelayTime->value()); });
}
/************************************LOAD LAST SETTINGS************************************/
void MainWindow::loadSettings() {
	for (auto iterate = 0; iterate < NumValves; ++iterate) {  // All previous concentrations
		ptxtConcentration[iterate]->setText(QString::number(controller->getStartValue(iterate)));
	}
	pspbDelayTime->setValue(controller->getDelayTime());
	pspbSupplyTime->setValue(controller->getSupplyTime());
	pspbWorkingVolume->setValue(controller->getWorkingVolume());
}
std::pair<int, int> MainWindow::getWindowPos() {
	auto windowPosPoint = pos();
	std::pair<int, int> winPos(windowPosPoint.x(), windowPosPoint.y());
	return winPos;
}
void MainWindow::setWindowPos(std::array<int, 2> windowPos) {
	move(windowPos[0], windowPos[1]);
}

[[maybe_unused]] void MainWindow::autoConnectToComPort() {
	if (!controller->getComPortName().empty())  {
		connectEvent(toQString(controller->getComPortName()));
	}
}
void MainWindow::connectEvent(const QString& text) {
	if (controller->serialPortInitialization(text)) {
		controller->setComPortName(text.toStdString());
		pcmdSearch->setText("Connected");
		pcmdSearch->setCheckable(false);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
void MainWindow::setSupplyTime(int time) {
	if (!controller->setSupplyTime(time)) {
		errorMessage("An error has occurred!");
	}
	controller->changeGasSupplyTime(time);
}
void MainWindow::setDelayTime(int time) {
	if (!controller->setDelayTime(time)) {
		errorMessage("An error has occurred!");
	}
	setTimerInterval();
}
void MainWindow::closeEvent(QCloseEvent *event) {
	QMessageBox::StandardButton resBtn = QMessageBox::question(this, APPLICATION_NAME,
		tr("Save previous session?\n"), QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
			QMessageBox::Yes);
	if (resBtn == QMessageBox::Cancel) {
		event->ignore();
		return;
	}
	if (resBtn == QMessageBox::Yes) {
		saveConcentrationValue();
		controller->saveCurrentWorkSpace();
	}
	event->accept();
}
/************************************CREATE VIEW LAYOUT************************************/
void MainWindow::createMainWindowLayout() {
    pGridLayout = new QGridLayout(this);
	pGridLayout->addWidget(createConnectionLayout());
	pGridLayout->addWidget(createSetUpLayout());
	pGridLayout->addWidget(createExecuteLayout());
	pGridLayout->addWidget(createManualSettingLayout());
    setLayout(pGridLayout);
}
QGroupBox* MainWindow::createConnectionLayout() {
	auto pgbConnectionLayout = new QGroupBox(tr("Connection"), this);
	auto ploConnectionLayout = new QGridLayout(pgbConnectionLayout);

	pcmdSearch = new QPushButton("Search", pgbConnectionLayout);
	ploConnectionLayout->addWidget(pcmdSearch);

	pgbConnectionLayout->setLayout(ploConnectionLayout);
	return pgbConnectionLayout;
}
QGroupBox* MainWindow::createSetUpLayout() {
	pgbSetOfAllValves = new QGroupBox(tr("Set up"), this);
	ploSetOfAllValves = new QGridLayout(pgbSetOfAllValves);

	auto ploConcentration = new QHBoxLayout();
	auto plblWorkingVolume = new QLabel("Working Volume, %", pgbSetOfAllValves);
	ploConcentration->addWidget(plblWorkingVolume);

	pspbWorkingVolume = new QSpinBox(pgbSetOfAllValves);
	pspbWorkingVolume->setMinimum(WorkingVolumeMin);
	pspbWorkingVolume->setMaximum(WorkingVolumeMax);

	ploConcentration->addWidget(pspbWorkingVolume);
	ploSetOfAllValves->addLayout(ploConcentration, 0, 0);

	auto ploViewSetUp = new QHBoxLayout();
	pchbGCm3 = new QRadioButton("g/cm^3", pgbSetOfAllValves);
	pchbGCm3->setChecked(true);
	pchbTimes = new QRadioButton("Times to mix", pgbSetOfAllValves);
	ploViewSetUp->addWidget(pchbGCm3);
	ploViewSetUp->addWidget(pchbTimes);
	ploSetOfAllValves->addLayout(ploViewSetUp, 1, 0);

	QGroupBox* pgbValveSetUp[NumValves];
	QHBoxLayout* ploValveLayout[NumValves];
	
	for (auto iter = 0; iter < NumValves; ++iter) {
		pgbValveSetUp[iter] = new QGroupBox(tr("Cartridge %1").arg(iter + 1), this);
		ploValveLayout[iter] = new QHBoxLayout();

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
void MainWindow::changeCartridgeView(int catridge, bool state) {
	if (state) { 
		plblTimes[catridge]->setStyleSheet("QLabel { color : red; }");
	}
	else {
		plblTimes[catridge]->setStyleSheet("QLabel { color : black; }");
	}
}
QGroupBox* MainWindow::createExecuteLayout() {
	auto pgbExecuteLayout = new QGroupBox(tr("Execute sequence"), this);
	auto ploExecuteLayout = new QGridLayout(pgbExecuteLayout);
	auto row = 0;

	auto plblTimesOfInnings = new QLabel("number of innings, pcs", pgbExecuteLayout);
	ploExecuteLayout->addWidget(plblTimesOfInnings, row, 0, Qt::AlignCenter);
	pspbTimesofInnings = new QSpinBox(pgbExecuteLayout);
	pspbTimesofInnings->setMinimum(TimesofInningsMin);
	pspbTimesofInnings->setMaximum(TimesofInningsMax);
	ploExecuteLayout->addWidget(pspbTimesofInnings, row++, 1);

	auto plblSupplyTime = new QLabel("Supply Time, max 9s", pgbExecuteLayout);
	ploExecuteLayout->addWidget(plblSupplyTime, row, 0, Qt::AlignCenter);
	pspbSupplyTime = new QSpinBox(pgbExecuteLayout);
	pspbSupplyTime->setMinimum(SupplyTimeMin);
	pspbSupplyTime->setMaximum(SupplyTimeMax);
	ploExecuteLayout->addWidget(pspbSupplyTime, row++, 1);

	auto plblDelayTime = new QLabel("Delay Time, max 100s", pgbExecuteLayout);
	ploExecuteLayout->addWidget(plblDelayTime, row, 0, Qt::AlignCenter);
	pspbDelayTime = new QSpinBox(pgbExecuteLayout);
	pspbDelayTime->setMinimum(DelayTimeMin);
	pspbDelayTime->setMaximum(DelayTimeMax);
	ploExecuteLayout->addWidget(pspbDelayTime, row++, 1);

	prbtSequenceStart = new QRadioButton("Sequence Start", pgbExecuteLayout);
	ploExecuteLayout->addWidget(prbtSequenceStart, row, 0);
	prbtSequenceStart->setChecked(true);
	prbtShuffleStart = new QRadioButton("Shuffle Start", pgbExecuteLayout);
	ploExecuteLayout->addWidget(prbtShuffleStart, row, 1);

	pcmdStart = new QPushButton("Start", pgbExecuteLayout);
	ploExecuteLayout->addWidget(pcmdStart, row, 0);

	pcmdPause = new QPushButton("Pause", pgbExecuteLayout);
	ploExecuteLayout->addWidget(pcmdPause, row++, 1);

	pcmdStop = new QPushButton("Stop", pgbExecuteLayout);
	ploExecuteLayout->addWidget(pcmdStop, row, 0);

	pcmdCleaningAirSystem = new QPushButton("Cleaning Air System", pgbExecuteLayout);
	ploExecuteLayout->addWidget(pcmdCleaningAirSystem, row++, 1);

	pgbExecuteLayout->setLayout(ploExecuteLayout);
	return pgbExecuteLayout;
}
QGroupBox* MainWindow::createManualSettingLayout() {
	auto pgbManualSettingLayout = new QGroupBox(tr("Manual setting"), this);
	auto ploManualSettingLayout = new QGridLayout(pgbManualSettingLayout);

	ptxtSerialPort = new QLineEdit(pgbManualSettingLayout);
	ploManualSettingLayout->addWidget(ptxtSerialPort, 0, 0);

	pcmdSendSP = new QPushButton("Send", pgbManualSettingLayout);
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
	connect(pcmbListOfPorts, QOverload<const QString &>::of(&QComboBox::textActivated),
		[=](const QString &text) {
			connectEvent(text);
			pcmbListOfPorts->hide();
			pcmbListOfPorts->clear();
	});
}
void MainWindow::saveConcentrationValue() {
	for (auto iterate = 0; iterate < NumValves; ++iterate) {
		controller->setStartValue(ptxtConcentration[iterate]->text().toDouble(), iterate);
	}
}
void MainWindow::setTimerInterval() {
	timer->setInterval(controller->getDelayTime() * 1000);
}
void MainWindow::prepareTheGasAirMixtureButtonClicked() {
	if (pchbGCm3->isChecked()) {
		saveConcentrationValue();
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
	controller->valveCloseCommand('A');
	timer->start(controller->getDelayTime()); 
}
void MainWindow::timeOutSlot() {
	auto count = pspbTimesofInnings->value();
	if (0 <= count) {
		count--;
		pspbTimesofInnings->setValue(count);
		if (prbtSequenceStart->isChecked()) {
			controller->startUpSequenceAirDelivery();
		}
		if (prbtShuffleStart->isChecked()) {
			controller->startUpShuffleAirDelivery();
		}
		if (0 == count) {
			std::this_thread::sleep_for(std::chrono::milliseconds(controller->getDelayTime()));
			stopButtonClicked();
		}
	}
}
void MainWindow::stopButtonClicked() {
	//controller->setReadyToGo(false);
	timer->stop();
	controller->stopAirDelivery();
}
void MainWindow::pauseButtonClicked() {
	static bool times;
	if (times) {
		timer->stop();
	}
	else {
		timer->start();
	}
	times ^= times;
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
void MainWindow::errorMessage(const std::string& errorMsg) {
	QMessageBox messageBox;
	messageBox.critical(0, "Error", toQString(errorMsg));
	messageBox.setFixedSize(500, 200);
}
QString MainWindow::toQString(const std::wstring& str) {
	return QString::fromStdWString(str);
}
QString MainWindow::toQString(const std::string& str) {
    return QString::fromStdString(str);
}