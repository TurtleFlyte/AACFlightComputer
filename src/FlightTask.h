#pragma once
#include <ImuLowG.h>
#include <Baro.h>

#include "SdModule.h"

extern Baro s_baro;
extern ImuLowG s_imu;
extern SdModule s_sd;

void FlightTask(void* arg);