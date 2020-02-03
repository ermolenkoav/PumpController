#pragma once

const auto NumValves		= 6;
const auto NumGridColumns	= 2;
const auto NumGridRows		= 2;

const auto _vesselVolume	= 160;
const auto _finalValue		= 1e-15;

const auto DefaultSupplyTime = 3;
const auto DelayTimeMin = 1;
const auto DelayTimeMax = 100;
const auto SupplyTimeMin = 1;
const auto SupplyTimeMax = 9;
const auto WorkingVolumeMin = 1;
const auto WorkingVolumeMax = 10;
const auto TimesofInningsMin = 0;
const auto TimesofInningsMax = 100;

#include "mainwindow.h"
#include "controller.h"
#include "model.h"
#include "settings.h"
#include "csvLog.h"