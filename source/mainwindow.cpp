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
	timer->setInterval(time);
    // Signals:
	connect(pcmdSearch,				SIGNAL(clicked()), this, SLOT(searchButtonClicked()));
    connect(pcmdSend,				SIGNAL(clicked()), this, SLOT(prepareTheGasAirMixtureButtonClicked()));
	connect(pcmdShuffleStart,		SIGNAL(clicked()), this, SLOT(shuffleStartButtonClicked()));
	connect(pcmdSequenceStart,		SIGNAL(clicked()), this, SLOT(sequenceStartButtonClicked()));
	connect(pcmdStop,				SIGNAL(clicked()), this, SLOT(stopButtonClicked()));
	connect(pcmd—leaningAirSystem,	SIGNAL(clicked()), this, SLOT(cleaningAirSystemButtonClicked()));
	connect(timer,					SIGNAL(timeout()), this, SLOT(timeOutSlot()));
	connect(pspbSupplyTime, QOverload<int>::of(&QSpinBox::valueChanged), [=]() {
		controller->changeGasSupplyTime(MainWindow::time); });
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
void MainWindow::setTime(int _time) {
	time = _time * 1000;
}
/************************************CREATE VIEW LAYOUT************************************/
void MainWindow::createMainWindowLayout() {
	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(createConnectionLayout());
	mainLayout->addWidget(createSetUpLayout());
	mainLayout->addWidget(createExecuteLayout());
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
	auto pgbSetOfAllValves = new QGroupBox(tr("Set up"), this);
	auto ploSetOfAllValves = new QGridLayout(this);

	QGroupBox* pgbValveSetUp[NumValves];
	QHBoxLayout* ploValveLayout[NumValves];
	QLabel* plblTimes[NumValves];

	for (auto iter = 0; iter < NumValves; ++iter) {
		pgbValveSetUp[iter] = new QGroupBox(tr("Cartridge %1").arg(iter + 1), this);
		ploValveLayout[iter] = new QHBoxLayout(this);

		plblTimes[iter] = new QLabel("Concentrations", this);
		ploValveLayout[iter]->addWidget(plblTimes[iter]);

		ptxtConcentration[iter] = new QLineEdit(this);
		ploValveLayout[iter]->addWidget(ptxtConcentration[iter]);

		pgbValveSetUp[iter]->setLayout(ploValveLayout[iter]);
		ploSetOfAllValves->addWidget(pgbValveSetUp[iter]);
	}

	pcmdSend = new QPushButton("Set Up", this);
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
	pcmd—leaningAirSystem = new QPushButton("Cleaning Air System", this);
	ploExecuteLayout->addWidget(pcmd—leaningAirSystem, 1, 0);

	auto plblSupplyTime = new QLabel("Supply Time", this);
	ploExecuteLayout->addWidget(plblSupplyTime, 2, 0, Qt::AlignCenter);
	pspbSupplyTime = new QSpinBox(this);
	pspbSupplyTime->setMinimum(1);
	pspbSupplyTime->setMaximum(9);
	pspbSupplyTime->setValue(3);
	ploExecuteLayout->addWidget(pspbSupplyTime, 2, 1);

	auto plblDelayTime = new QLabel("Delay Time", this);
	ploExecuteLayout->addWidget(plblDelayTime, 3, 0, Qt::AlignCenter);
	pspbDelayTime = new QSpinBox(this);
	pspbDelayTime->setMinimum(1);
	pspbDelayTime->setMaximum(60);
	pspbDelayTime->setValue(15);
	ploExecuteLayout->addWidget(pspbDelayTime, 3, 1);

	pgbExecuteLayout->setLayout(ploExecuteLayout);
	return pgbExecuteLayout;
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
	controller->startUpShuffleAirMixture();
	controller->setReadyToGo(true);
	timer->start(time);
}
void MainWindow::sequenceStartButtonClicked() {
	controller->startUpSequenceAirMixture();
	controller->setReadyToGo(true);
	timer->start(time);
}
void MainWindow::cleaningAirSystemButtonClicked() {
	controller->cleaningAirSystem();
}
void MainWindow::stopButtonClicked() {
	controller->setReadyToGo(false);
	timer->stop();
}
void MainWindow::timeOutSlot() {
	controller->startUpSequenceAirMixture();
}
void MainWindow::sequenceValueChanged() {

}
