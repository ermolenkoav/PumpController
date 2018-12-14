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
	qmClapan->insert("first", 1);
	qmClapan->insert("secont", 2);
	qmClapan->insert("third", 3);
	qmClapan->insert("forth", 4);

    dataArray = new QByteArray();
	dataArray->insert(0, 'A');
	dataArray->insert(1, 'P');
/**********************************************************************************/
    // Serial Port:
    pSerialPort = new QSerialPort(this);

    // there's a widgets of application:
	pcmdSearch = new QPushButton("Search", this);
    pcmdSend = new QPushButton("Send", this);


	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(pcmdSearch);
	mainLayout->addWidget(createGridGroupBox());
	mainLayout->addWidget(pcmdSend);
	setLayout(mainLayout);   

    // Signals:
	connect(pcmdSearch, SIGNAL (clicked()), this, SLOT (handlePcmdSearchButton()));
    connect(pcmdSend, SIGNAL (clicked()), this, SLOT (handlePcmdSendButton()));
    /*
	connect(pcmbCartridge, SIGNAL(activated(QString)), this, SLOT(pcmbCartridgeActivated()));
	connect(pcmbCommand, SIGNAL(activated(QString)), this, SLOT(pcmbCommandActivated()));
	*/
}

QGroupBox *MainWindow::createGridGroupBox() {
	auto ggbSetOfAllClapans = new QGroupBox(tr("Set up"));
	auto layout = new QGridLayout();

	QGroupBox *clapanGroupBox[NumClapans];
	QGridLayout *clapanLayout[NumClapans];
	QLineEdit *ptxtTimes[NumClapans][NumGridRows];
	QLabel *plblText[NumClapans][NumGridRows];
		
	for (auto k = 0; k < 6; ++k) {
		clapanGroupBox[k] = new QGroupBox(tr("Clapan %1").arg(k + 1));
		clapanLayout[k] = new QGridLayout();
		/*
		for (auto i = 0; i < 2; ++i) {
			if (i % 2 != 0) {
				plblText[k][i] = new QLabel("Start");
			}
			else {
				plblText[k][i] = new QLabel("Stop");
			}

			ptxtTimes[k][i] = new QLineEdit();
			clapanLayout[k]->addWidget(ptxtTimes[k][i], k, i);
		}
		*/

		clapanGroupBox[k]->setLayout(clapanLayout[k]);
		layout->addWidget(clapanGroupBox[k]);
	}

	ggbSetOfAllClapans->setLayout(layout); 
	return ggbSetOfAllClapans;
}

void MainWindow::handlePcmdSendButton() {
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

void MainWindow::handlePcmdSearchButton() {
	//pcmbDevises->clear();
	auto serialPortInfos = QSerialPortInfo::availablePorts();
	for (auto serialPortInfo : serialPortInfos) {
		//pcmbDevises->addItem(serialPortInfo.portName());
	}
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
*/
void MainWindow::closeSerialPort() {
    pSerialPort->close();
}
