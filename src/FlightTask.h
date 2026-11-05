#pragma once
#include <ImuLowG.h>
#include <Baro.h>

static Baro s_baro;
static ImuLowG s_imu;

void FlightTask(void* arg);