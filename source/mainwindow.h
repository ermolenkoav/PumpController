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
	QSpinBox* pspbWorkingVolume = nullptr; 
	QSpinBox* pspbTimesofInnings = nullptr;
	QLabel* plblTimes[NumValves];
	QTimer* timer = nullptr;

    // methods:
	void createMainWindowLayout();
	void loadSettings();
	void autoConnectToComPort();
	void connectEvent(const QString& text);
	QString& toQString(const std::wstring& str);
	void closeEvent(QCloseEvent* bar);

	QGroupBox* createConnectionLayout();
	QGroupBox* createSetUpLayout();
	QGroupBox* createExecuteLayout();
	QGroupBox* createManualSettingLayout();

public:
	explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

	std::pair<int, int> getWindowPos();
	void setWindowPos(std::array<int, 2>);
	void setSypplyTime(int);
	void setDalayTime(int);
	void errorMessage(const std::wstring&);

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