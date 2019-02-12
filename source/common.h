#pragma once
#include "pch.h"

const auto NumValves		= 6;
const auto NumGridColumns	= 2;
const auto NumGridRows		= 2;

const auto _vesselVolume	= 160;
const auto _finalValue		= 1e-15;

const auto settingsFileName	= "settings.json";
const auto logFileName		= L"logs.json";

#include "controller.h"
#include "model.h"
#include "settings.h"


