#pragma once
#include "pch.h"
#include "controller.h"

class MainWindow : public QWidget {

	Q_OBJECT

    // widgets:
	QLineEdit* ptxtConcentration[NumValves] = {};
    QGridLayout* pGridLayout = nullptr;
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
	QSpinBox* pspbWorkingVolume = nullptr; 
	QSpinBox* pspbTimesofInnings = nullptr;
	QLabel* plblTimes[NumValves]{};
	QTimer* timer = nullptr;

    std::unique_ptr<Controller> controller;

    // methods:
	void saveConcentrationValue();
	void setTimerInterval();
	void createMainWindowLayout();
	void loadSettings();

    [[maybe_unused]] void autoConnectToComPort();
	void connectEvent(const QString& text);
	QString toQString(const std::wstring& str);
    QString toQString(const std::string& str);
	void closeEvent(QCloseEvent* bar) final;

    QGroupBox* createConnectionLayout();
	QGroupBox* createSetUpLayout();
	QGroupBox* createExecuteLayout();
	QGroupBox* createManualSettingLayout();

public:

	explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default ;

	std::pair<int, int> getWindowPos();
	void setWindowPos(std::array<int, 2>);
	void setSupplyTime(int);
	void setDelayTime(int);
	void errorMessage(const std::string&);
	void changeCartridgeView(int, bool);

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