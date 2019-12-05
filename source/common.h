#pragma once

#include <Qt>
#include <QApplication>
#include <QMessageBox>
#include <QtWidgets>
#include <QTimer>
#include <QListWidgetItem>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QToolButton>
#include <QCloseEvent>
#include <QCheckBox>
#include <QTabWidget>
#include <QByteArray>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QPoint>
#include <QDebug>

#include "cpprest/json.h"

#include <initializer_list>
#include <filesystem>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <array>
#include <cmath>
#include <list>

const auto NumValves		= 6;
const auto NumGridColumns	= 2;
const auto NumGridRows		= 2;

const auto _vesselVolume	= 160;
const auto _finalValue		= 1e-15;

const auto settingsFileName	= L"settings.json";
const auto logFileName		= L"logs.json";

const auto DefaultSupplyTime = 3;
const auto DelayTimeMin = 1;
const auto DelayTimeMax = 100;
const auto SupplyTimeMin = 1;
const auto SupplyTimeMax = 9;
const auto WorkingVolumeMin = 1;
const auto WorkingVolumeMax = 9;
const auto TimesofInningsMin = 0;
const auto TimesofInningsMax = 100;

#include "mainwindow.h"
#include "controller.h"
#include "model.h"
#include "settings.h"