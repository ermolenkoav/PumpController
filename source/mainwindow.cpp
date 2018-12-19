#include "mainwindow.h"


MainWindow::~MainWindow() {
	delete qmCartridge;
	delete qmCommand;
	delete qmClapan;
	delete dataArray;
	delete controller;
}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
	// commands and cartridge
	qmCartridge = new QMap<QString, char>;
	qmCartridge->insert("Cartridge A", 'A');
	qmCartridge->insert("Cartridge B", 'B');
	qmCartridge->insert("Cartridge C", 'C');
	qmCartridge->insert("Cartridge D", 'D');
	qmCartridge->insert("Cartridge E", 'E');
	qmCartridge->insert("Cartridge F", 'F');

	qmCommand = new QMap<QString, char>;
	qmCommand->insert("aerate", 'A');
	qmCommand->insert("stop", 'P');
	qmCommand->insert("below to down", 'B');
	qmCommand->insert("step up 100 steps", 'U');
	qmCommand->insert("open valve", 'K');
	qmCommand->insert("close valve", 'L');
	qmCommand->insert("step down 100 steps", 'D');

	qmClapan = new QMap<QString, int>;
	qmClapan->insert("first", 1);
	qmClapan->insert("second", 2);
	qmClapan->insert("third", 3);
	qmClapan->insert("forth", 4);

    dataArray = new QByteArray();
	dataArray->insert(0, 'A');
	dataArray->insert(1, 'P');
/**********************************************************************************/
	createMainWindowLayout();

    // Signals:
	connect(pcmdSearch, SIGNAL (clicked()), this, SLOT (searchButtonClicked()));
    connect(pcmdSend, SIGNAL (clicked()), this, SLOT (sendButtonClicked()));
}

void MainWindow::createMainWindowLayout() {
	pcmdSearch = new QPushButton("Search", this);
	pcmdSend = new QPushButton("Send", this);
	mainLayout = new QVBoxLayout(this);
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
					ptxtConcentration[row + k] = new QLineEdit(this);
					ploValveLayout[k]->addWidget(ptxtConcentration[row + k], row, column);
				}
			}
		}

		pgbValveSetUp[k]->setLayout(ploValveLayout[k]);
		ploSetOfAllValves->addWidget(pgbValveSetUp[k]);
	}   

	pgbSetOfAllValves->setLayout(ploSetOfAllValves);
	mainLayout->addWidget(pcmdSearch);
	mainLayout->addWidget(pgbSetOfAllValves);
	mainLayout->addWidget(pcmdSend);
	setLayout(mainLayout);
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
		controller = new Controller;
		controller->devisesActivated(text);
		pcmdSearch->setText("Connected");
		pcmdSearch->setCheckable(false);
		pcmbListOfPorts->hide();
		pcmbListOfPorts->clear();
	});
	
}


void MainWindow::sendButtonClicked() {
	for(auto iterator : ptxtConcentration) {
		
	}

	/*
	auto stTimes = ptxtTimes->text();
	int times = stTimes.split(" ")[0].toInt();
	if (1 >= times) {
		times = 2;
	}
	int debug = 0;
	for (int i = 0; i < times; i++) {
		if (pSerialPort->isOpen()) {
			auto temp(dataArray);
			pSerialPort->write(*temp);
			pSerialPort->waitForBytesWritten(10000);

			debug++;
		}
		else {
			QMessageBox::warning(this, "error", "no com port", QMessageBox::Ok);
		}
	}
	qDebug() << debug;
	*/
}


/*
void MainWindow::pcmbCartridgeActivated() {
	auto stValueComboBox = pcmbCartridge->currentText();
	auto value = qmCartridge->take(stValueComboBox);
	dataArray->replace(0,1, &value);
	qDebug() << dataArray[0];
}

void MainWindow::pcmbCommandActivated() {
	auto stValueComboBox = pcmbCommand->currentText();
	auto value = qmCommand->take(stValueComboBox);
	dataArray->replace(1, 1, &value);
	qDebug() << dataArray[0];
}
*/
