#pragma once


#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMessageBox>
#include <QByteArray>
#include <QtWidgets>
#include <QDebug>
#include "commands.h"

class QComboBox;
class QPushButton;
class QListWidget;

class MainWindow : public QWidget
{
    Q_OBJECT
    // const:
    const int sizeOfArray = 8;

    // widgets:
    QSerialPort *pSerialPort;
   // QSerialPortInfo *m_pSerialPortInfo;

    QComboBox* pcmbDevises;
    QPushButton* pcmdSearch;
    QPushButton* pcmdSend;
    QListWidget* listView;
	QComboBox* pcmbCartridge;
	QComboBox* pcmbCommand;
	QLineEdit* ptxtTimes;

    QByteArray* dataArray;
	int sendCounter = 1;

    // variable:
    QString selectedDevice = nullptr;
	QMap<QString, char> *qmCartridge;
	QMap<QString, char> *qmCommand;
	QMap<QString, int> *qmClapan;

    // methods:
    void closeSerialPort();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
   void handlePcmdSendButton();
   void handlePcmdSearchButton();
   void pcmbDevisesActivated();
   void pcmbCartridgeActivated();
   void pcmbCommandActivated();
};

