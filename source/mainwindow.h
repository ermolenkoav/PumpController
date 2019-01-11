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

	Controller *controller = nullptr;
    // widgets:
	QLineEdit *ptxtConcentration[NumGridRows * NumValves] = {};
	QVBoxLayout *mainLayout = nullptr;
	QPushButton *pcmdSearch = nullptr;
	QPushButton *pcmdSend = nullptr;
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
};