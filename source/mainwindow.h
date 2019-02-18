#pragma once
#include "common.h"

class QGroupBox;
class QGridLayout;
class QComboBox;
class QPushButton;
class QListWidget;
class QLineEdit;
class QVBoxLayout;
class Controller;

class MainWindow : public QWidget {
    Q_OBJECT    
	Controller *controller = nullptr;

    // widgets:
	QLineEdit *ptxtConcentration[NumGridRows * NumValves] = {};
	QVBoxLayout *mainLayout = nullptr;
	QPushButton *pcmdSearch = nullptr;
	QPushButton *pcmdSend = nullptr;
	QPushButton *pcmdShuffleStart = nullptr;
	QPushButton* pcmdSequenceStart = nullptr;
	QLineEdit *plneSequence = nullptr;

    // methods:
	void createMainWindowLayout();
	void loadSettings();
	QGroupBox* createConnectionLayout();
	QGroupBox* createSetUpLayout();
	QGroupBox* createExecuteLayout();

	

public:
	explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

	std::pair<int, int> getWindowPos();
	void setWindowPos(std::array<int, 2> windowPos);

private slots:
	void searchButtonClicked();
	void prepareTheGasAirMixtureButtonClicked();
	void shuffleStartButtonClicked();
	void sequenceStartButtonClicked();
};