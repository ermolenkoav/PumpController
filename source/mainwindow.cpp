#include "mainwindow.h"

MainWindow::~MainWindow() {
	delete controller;
} 

MainWindow::MainWindow(QWidget *parent) : QWidget(parent = nullptr) {
	setWindowIcon(QIcon(":logo.ico"));
	setWindowTitle("Odorizer");
	resize(300, 120);
	controller = new Controller;
	
	createMainWindowLayout();
	loadValveValues();

    // Signals:
	connect(pcmdSearch,			SIGNAL(clicked()), this, SLOT(searchButtonClicked()));
    connect(pcmdSend,			SIGNAL(clicked()), this, SLOT(prepareTheGasAirMixtureButtonClicked()));
	connect(pcmdShuffleStart,	SIGNAL(clicked()), this, SLOT(shuffleStartButtonClicked()));
	connect(pcmdSequenceStart,	SIGNAL(clicked()), this, SLOT(sequenceStartButtonClicked()));
}

/************************************LOAD LAST SETTINGS************************************/
void MainWindow::loadValveValues() {
	for (auto iterate = 0, posValue = 0, posTimes = 0; iterate < NumValves * NumGridRows; ++iterate) {
		if (0 == (iterate % 2)) {
			ptxtConcentration[iterate]->setText(QString::number(controller->getStartValue(posValue++)));
		}
		if (0 != (iterate % 2)) {
			ptxtConcentration[iterate]->setText(QString::number(controller->getStartTimes(posTimes++)));
		}
	}
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

	QGroupBox *pgbValveSetUp[NumValves];
	QGridLayout *ploValveLayout[NumValves];
	QLabel *plblTimes[NumGridRows * NumValves];

	for (auto k = 0; k < NumValves; ++k) {
		pgbValveSetUp[k] = new QGroupBox(tr("Cartridge %1").arg(k + 1), this);
		ploValveLayout[k] = new QGridLayout(this);

		for (auto column = 0; column < NumGridColumns; ++column) {
			for (auto row = 0; row < NumGridRows; ++row) {

				if (column == 0) {
					if (row == 0) { plblTimes[row + k] = new QLabel("Concentrations", this); }
					if (row == 1) { plblTimes[row + k] = new QLabel("Times", this); }
					ploValveLayout[k]->addWidget(plblTimes[row + k], row, column);
				}

				if (column == 1) {
					static auto iter = 0;
					ptxtConcentration[iter] = new QLineEdit(this);
					ploValveLayout[k]->addWidget(ptxtConcentration[iter++], row, column);
				}
			}
		}

		pgbValveSetUp[k]->setLayout(ploValveLayout[k]);
		ploSetOfAllValves->addWidget(pgbValveSetUp[k]);
	}

	pcmdSend = new QPushButton("Set Up", this);
	ploSetOfAllValves->addWidget(pcmdSend);

	pgbSetOfAllValves->setLayout(ploSetOfAllValves);
	return pgbSetOfAllValves;
}

QGroupBox* MainWindow::createExecuteLayout() {
	auto pgbExecuteLayout = new QGroupBox(tr("Execute sequence"), this);
	auto ploExecuteLayout = new QGridLayout(this);

	plneSequence = new QLineEdit(this);
	ploExecuteLayout->addWidget(plneSequence);

	pcmdShuffleStart = new QPushButton("Shuffle Start", this);
	ploExecuteLayout->addWidget(pcmdShuffleStart);

	pcmdSequenceStart = new QPushButton("Sequence Start", this);
	ploExecuteLayout->addWidget(pcmdSequenceStart);

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
			if (controller->serialPortInitialization(text)) {
				pcmdSearch->setText("Connected");
				pcmdSearch->setCheckable(false);
				pcmbListOfPorts->hide();
				pcmbListOfPorts->clear();
				std::this_thread::sleep_for(std::chrono::seconds(3));
				controller->cleaningAirSystem();
			}
	});
}

void MainWindow::prepareTheGasAirMixtureButtonClicked() {
	for (auto iterate = 0, posValue = 0, posTimes = 0; iterate < NumValves * NumGridRows; ++iterate) {
		if (0 == (iterate % 2)) {
			auto stTimes = ptxtConcentration[iterate]->text();
			controller->setStartValue(stTimes.toDouble(), posValue++);
		}
		if (0 != (iterate % 2)) {
			auto stTimes = ptxtConcentration[iterate]->text();
			controller->setTimes(stTimes.toInt(), posTimes++);
		}
	}
	controller->prepareTheGasAirMixture();
}

void MainWindow::shuffleStartButtonClicked() {
	controller->startUpShuffleGasAirMixture();
}

void MainWindow::sequenceStartButtonClicked() {
	controller->startUpSequenceGasAirMixture();
}