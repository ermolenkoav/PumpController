#pragma once

#if defined __cplusplus
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMessageBox>
#include <QByteArray>
#include <QtWidgets>
#include <QDebug>
#include <QPoint>
#endif

#include "cpprest/json.h"

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


