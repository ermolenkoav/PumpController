#pragma once

#if defined __cplusplus
#include <QListWidgetItem>
#include <QSerialPortInfo>
#include <QApplication>
#include <QSerialPort>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QTabWidget>
#include <QByteArray>
#include <QComboBox>
#include <QLineEdit>
#include <QtWidgets>
#include <QSpinBox>
#include <QLabel>
#include <QPoint>
#include <QDebug>

#include "cpprest/json.h"
#endif

const auto NumValves		= 6;
const auto NumGridColumns	= 2;
const auto NumGridRows		= 2;

const auto _vesselVolume	= 160;
const auto _finalValue		= 1e-15;

const auto settingsFileName	= L"settings.json";
const auto logFileName		= L"logs.json";

#include "mainwindow.h"
#include "controller.h"
#include "model.h"
#include "settings.h"


