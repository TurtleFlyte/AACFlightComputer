#pragma once
#include <ImuLowG.h>
#include <Baro.h>

extern Baro s_baro;
extern ImuLowG s_imu;

void FlightTask(void* arg);