#pragma once
#include "pch.h"
#include "common.h"
#include "model.h"
#include "setupcontroller.h"
#include "startcontroller.h"

class QGroupBox;
class QGridLayout;
class QComboBox;
class QPushButton;
class QListWidget;
class QLineEdit;
class QVBoxLayout;
class QSerialPort;

class MainWindow : public QWidget {
    Q_OBJECT    
	QSerialPort *pSerialPort = nullptr;
	SetUpController *setupcontroller = nullptr;
	StartController * startcontroller = nullptr;

    // widgets:
	QLineEdit *ptxtConcentration[NumGridRows * NumValves] = {};
	QVBoxLayout *mainLayout = nullptr;
	QPushButton *pcmdSearch = nullptr;
	QPushButton *pcmdSend = nullptr;
	QPushButton *pcmdStart = nullptr;
	QLineEdit *plneSequence = nullptr;

    // methods:
	void createMainWindowLayout();
	QGroupBox* createConnectionLayout();
	QGroupBox* createSetUpLayout();
	QGroupBox* createExecuteLayout();


public:
	explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	
private slots:
	void sendButtonClicked();
	void searchButtonClicked();
	void startButtonClicked();
};