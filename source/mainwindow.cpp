#include <source/mainwindow.h>

MainWindow::~MainWindow() {
	delete controller;
} 

MainWindow::MainWindow(QWidget *parent) : QWidget(parent = nullptr) {
	createMainWindowLayout();
	controller = new Controller();

    // Signals:
	connect(pcmdSearch, SIGNAL (clicked()), this, SLOT (searchButtonClicked()));
    connect(pcmdSend, SIGNAL (clicked()), this, SLOT (sendButtonClicked()));
}

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

	pgbSetOfAllValves->setLayout(ploSetOfAllValves);
	return pgbSetOfAllValves;
}

QGroupBox* MainWindow::createExecuteLayout() {
	auto pgbExecuteLayout = new QGroupBox(tr("Execute sequence"), this);
	auto ploExecuteLayout = new QGridLayout(this);

	plneSequence = new QLineEdit(this);
	ploExecuteLayout->addWidget(plneSequence);

	pcmdSend = new QPushButton("Send", this);
	ploExecuteLayout->addWidget(pcmdSend);

	pgbExecuteLayout->setLayout(ploExecuteLayout);
	return pgbExecuteLayout;
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
		controller->devisesActivated(text);
		pcmdSearch->setText("Connected");
		pcmdSearch->setCheckable(false);
		pcmbListOfPorts->hide();
		pcmbListOfPorts->clear();
	});
	
}

void MainWindow::sendButtonClicked() {
	controller->clearBuffer();
	for (auto iterate = 0; iterate < NumValves * NumGridRows; ++iterate) {
		if (0 == (iterate % 2)) {
			static auto pos = 0;
			auto stTimes = ptxtConcentration[iterate]->text();
			controller->setStartValue(stTimes.split(" ")[0].toDouble(), pos++);
		}
		if (0 != (iterate % 2)) {
			static auto pos = 0;
			auto stTimes = ptxtConcentration[iterate]->text();
			controller->setTimes(stTimes.split(" ")[0].toInt(), pos++);
		}
	}
	controller->calculateData();
	controller->sendCommand();
}