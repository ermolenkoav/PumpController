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
class QSpinBox;

class MainWindow : public QWidget {
    Q_OBJECT    
	Controller *controller = nullptr;

    // widgets:
	QLineEdit* ptxtConcentration[NumValves] = {};
	QVBoxLayout* mainLayout = nullptr;
	QGroupBox* pgbSetOfAllValves = nullptr;
	QGridLayout* ploSetOfAllValves = nullptr;
	QPushButton* pcmdSearch = nullptr;
	QPushButton* pcmdSend = nullptr;
	QPushButton* pcmdStart = nullptr;
	QPushButton* pcmdPause = nullptr;
	QPushButton* pcmdCleaningAirSystem = nullptr;
	QPushButton* pcmdStop = nullptr;
	QPushButton* pcmdSendSP = nullptr;
	QPushButton* pcmdChangeView = nullptr;
	QRadioButton* prbtShuffleStart = nullptr;
	QRadioButton* prbtSequenceStart = nullptr;
	QRadioButton* pchbGCm3 = nullptr;
	QRadioButton* pchbTimes = nullptr;
	QLineEdit* ptxtSerialPort = nullptr;
	QSpinBox* pspbDelayTime = nullptr;
	QSpinBox* pspbSupplyTime = nullptr;
	QLabel* plblTimes[NumValves];
	QTimer* timer = nullptr;

    // methods:
	void createMainWindowLayout();
	void loadSettings();
	void autoConnectToComPort(const QString& text);
	void connectEvent(const QString& text);

	QGroupBox* createConnectionLayout();
	QGroupBox* createSetUpLayout();
	QGroupBox* createExecuteLayout();
	QGroupBox* createManualSettingLayout();

	// variables:
	std::wstring comPortName;
	int supplyTime;
	int delayTime;

public:
	explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

	std::pair<int, int> getWindowPos();
	void setWindowPos(std::array<int, 2>);
	std::wstring getComPortName();
	void setComPortName(std::wstring&);
	void setExecuteSequence(std::wstring&);
	std::wstring getExecuteSequence();
	void setSypplyTime(int);
	void setDalayTime();

private slots:
	void searchButtonClicked();
	void prepareTheGasAirMixtureButtonClicked();
	void cleaningAirSystemButtonClicked();
	void stopButtonClicked();
	void timeOutSlot();
	void manualSettingClicked();
	void changeViewClicked();
	void startButtonClicked();
	void pauseButtonClicked();
};