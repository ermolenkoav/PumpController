#pragma once
#include "pch.h"
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
	QPushButton* pcmdSearch = nullptr;
	QPushButton* pcmdSend = nullptr;
	QPushButton* pcmdShuffleStart = nullptr;
	QPushButton* pcmdSequenceStart = nullptr;
	QPushButton* pcmdCleaningAirSystem = nullptr;
	QPushButton* pcmdStop = nullptr;
	QPushButton* pcmdSendSP = nullptr;
	QLineEdit* ptxtSerialPort = nullptr;
	QSpinBox* pspbDelayTime = nullptr;
	QSpinBox* pspbSupplyTime = nullptr;
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
	void setWindowPos(std::array<int, 2> windowPos);

	std::wstring getComPortName();
	void setComPortName(std::wstring& _comPortName);

	void setExecuteSequence(std::wstring& text);
	std::wstring getExecuteSequence();

	void setSypplyTime(int _time);
	void setDalayTime();

private slots:
	void searchButtonClicked();
	void prepareTheGasAirMixtureButtonClicked();
	void shuffleStartButtonClicked();
	void sequenceStartButtonClicked();
	void cleaningAirSystemButtonClicked();
	void stopButtonClicked();
	void timeOutSlot();
	void sequenceValueChanged();
	void manualSettingClicked();
};