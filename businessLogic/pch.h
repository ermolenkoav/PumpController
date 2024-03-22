#pragma once

constexpr auto NumValves		 = 6;
constexpr auto NumGridColumns	 = 2;
constexpr auto NumGridRows		 = 2;

constexpr auto vesselVolume	     = 160;
constexpr auto finalValue		 = 1e-15;

constexpr auto DefaultSupplyTime = 3;
constexpr auto DelayTimeMin      = 1;
constexpr auto DelayTimeMax      = 100;
constexpr auto SupplyTimeMin     = 1;
constexpr auto SupplyTimeMax     = 9;
constexpr auto WorkingVolumeMin  = 1;
constexpr auto WorkingVolumeMax  = 10;
constexpr auto TimesofInningsMin = 0;
constexpr auto TimesofInningsMax = 100;