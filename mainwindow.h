#pragma once

#include "pch.h"

class QGroupBox;
class QGridLayout;
class QComboBox;
class QPushButton;
class QListWidget;
class QLineEdit;
class QVBoxLayout;

class MainWindow : public QWidget
{
    Q_OBJECT    
	// variable:
    QByteArray* dataArray;
	QMap<QString, char> *qmCartridge;
	QMap<QString, char> *qmCommand;
	QMap<QString, int> *qmClapan;
    QString selectedDevice = nullptr;
	int sendCounter = 1;
	// const:
	enum { NumGridRows = 2, NumGridColumns = 3, NumClapans = 6 };
	const int sizeOfArray = 8;

    // widgets:
	QVBoxLayout *mainLayout;
    QSerialPort *pSerialPort;
	QPushButton* pcmdSearch;
	QPushButton* pcmdSend;
	//QLineEdit* ptxtTimes[NumGridRows][NumGridColumns];

    // methods:
	QGroupBox *createGridGroupBox();
    void closeSerialPort();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	
private slots:
   void handlePcmdSendButton();
   void handlePcmdSearchButton();
/*   void pcmbDevisesActivated();
   void pcmbCartridgeActivated();
   void pcmbCommandActivated();*/
};