#pragma once
#include "pch.h"
#include "common.h"
#include "controller.h"

class QGroupBox;
class QGridLayout;
class QComboBox;
class QPushButton;
class QListWidget;
class QLineEdit;
class QVBoxLayout;

class MainWindow : public QWidget {
    Q_OBJECT    
	// variable:
    QByteArray *dataArray;
	QMap<QString, char> *qmCartridge;
	QMap<QString, char> *qmCommand;
	QMap<QString, int> *qmClapan;

	Controller *controller = nullptr;
    // widgets:
	QLineEdit *ptxtConcentration[NumGridRows * NumValves] = {};
	QVBoxLayout *mainLayout = nullptr;
	QPushButton *pcmdSearch = nullptr;
	QPushButton *pcmdSend = nullptr;

    // methods:
	void createMainWindowLayout();


public:
	explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	
private slots:
   void sendButtonClicked();
     void searchButtonClicked();
};