#include "mainwindow.h"

MainWindow::~MainWindow() {
    closeSerialPort();
}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
	// commands and catridges
	qmCartridge = new QMap<QString, char>;

	qmCartridge->insert("Catrige A", 'A');
	qmCartridge->insert("Catrige B", 'B');
	qmCartridge->insert("Catrige C", 'C');
	qmCartridge->insert("Catrige D", 'D');
	qmCartridge->insert("Catrige E", 'E');
	qmCartridge->insert("Catrige F", 'F');

	qmCommand = new QMap<QString, char>;

	qmCommand->insert("aerate", 'A');
	qmCommand->insert("stop", 'P');
	qmCommand->insert("below to down", 'B');
	qmCommand->insert("step up 100 steps", 'U');

	qmCommand->insert("open clapan", 'K');
	qmCommand->insert("close clapan", 'L');
	qmCommand->insert("step down 100 steps", 'D');

	qmClapan = new QMap<QString, int>;
	qmCommand->insert("first", 1);
	qmCommand->insert("secont", 2);
	qmCommand->insert("third", 3);
	qmCommand->insert("forth", 4);

    // Serial Port:
    pSerialPort = new QSerialPort(this);

    // there's a widgets of application:
    pcmdSend = new QPushButton("Send", this);
    pcmdSearch = new QPushButton("Search", this);
    pcmbDevises = new QComboBox(this);
	ptxtTimes = new QLineEdit(this);
	ptxtTimes->setPlaceholderText(QString::number(sendCounter));

	// set up combo box
	pcmbCartridge = new QComboBox(this);
	pcmbCommand = new QComboBox(this);
	// initialize combo box
	pcmbCartridge->addItems(QStringList(qmCartridge->uniqueKeys()));
	pcmbCommand->addItems(QStringList(qmCommand->uniqueKeys()));

    // Grid:
    QGridLayout* pgrdLayout = new QGridLayout(this);
    pgrdLayout->setMargin(10);
    pgrdLayout->setSpacing(20);
	pgrdLayout->addWidget(pcmdSearch, 0, 6);
    pgrdLayout->addWidget(pcmbDevises, 1, 6);
	pgrdLayout->addWidget(pcmbCartridge, 2, 6);
	pgrdLayout->addWidget(pcmbCommand, 3, 6);
    pgrdLayout->addWidget(pcmdSend, 4, 6);
	pgrdLayout->addWidget(ptxtTimes, 5, 6);

	setLayout(pgrdLayout);

    // data:
    dataArray = new QByteArray();
	dataArray->insert(0, 'A');
	dataArray->insert(1, 'P');


    // Signals:
    connect(pcmdSend, SIGNAL (clicked()), this, SLOT (handlePcmdSendButton()));
    connect(pcmdSearch, SIGNAL (clicked()), this, SLOT (handlePcmdSearchButton()));
    connect(pcmbDevises, SIGNAL (activated(QString)), this, SLOT (pcmbDevisesActivated()));
	connect(pcmbCartridge, SIGNAL(activated(QString)), this, SLOT(pcmbCartridgeActivated()));
	connect(pcmbCommand, SIGNAL(activated(QString)), this, SLOT(pcmbCommandActivated()));
}

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

void MainWindow::pcmbDevisesActivated() {
    selectedDevice = pcmbDevises->currentText();
    if (!pSerialPort->isOpen()) {
		qDebug() << selectedDevice;
        pSerialPort->setPortName(selectedDevice);
        pSerialPort->setBaudRate(QSerialPort::Baud9600);
        pSerialPort->setDataBits(QSerialPort::Data8);
        pSerialPort->setParity(QSerialPort::NoParity);
        pSerialPort->setStopBits(QSerialPort::OneStop);
        pSerialPort->setFlowControl(QSerialPort::NoFlowControl);
        pSerialPort->open(QIODevice::ReadWrite);
    } else {
		QMessageBox::warning(this, "warning", "com port is open", QMessageBox::Ok);
    }
}

void MainWindow::handlePcmdSendButton() {
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
}

void MainWindow::handlePcmdSearchButton() {
	pcmbDevises->clear();
    auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (auto serialPortInfo : serialPortInfos) {
       pcmbDevises->addItem(serialPortInfo.portName());
    }
}

void MainWindow::closeSerialPort() {
    pSerialPort->close();
}
