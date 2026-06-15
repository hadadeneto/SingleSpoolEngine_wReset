/*
 * EngineModel.c
 *
 *  Created on: March 1, 2019
 *      Author: anton
 */


/* Math lib */
#include <math.h>
/* Engines libs */
#include "ConstantsGEJ85.h"
#include "Control_Types.h"



void getGEJ85StartPars(struct ControlStart *ContStartP)
{
    /* LOADS THE GAINS ACCORDING TO REQUESTED ENGINE */
    ContStartP->FuelHighPulse = GEJ85_FUEL_HIGH_PULSE;
    ContStartP->FuelImpulseTime = GEJ85_FUEL_IMPULSE_TIME;
    ContStartP->FuelInit = GEJ85_FUEL_INIT;
    ContStartP->FuelPerc = GEJ85_FUEL_PERC;
    ContStartP->FuelRamp = GEJ85_FUEL_RAMP;
    ContStartP->POilAlarm = GEJ85_POIL_ALARM;
    ContStartP->POilShutDown = GEJ85_POIL_SHUTDOWN;
    ContStartP->RPMIdle = GEJ85_RPM_IDLE;
    ContStartP->RPMIgnOff = GEJ85_RPM_IGN_OFF;
    ContStartP->RPMRelaysOn = GEJ85_RPM_RELAYS_ON;
    ContStartP->RPMValve100 = GEJ85_RPM_VALVE_100;
    ContStartP->TimeAccomodation = GEJ85_TIME_ACCOMODATION;
    ContStartP->TimeIgnition = GEJ85_TIME_IGNITION;
    ContStartP->TimeLowPOil = GEJ85_TIME_LOW_POIL;
    ContStartP->TimeOvertemp = GEJ85_TIME_OVERTEMP;
    ContStartP->Tt5AvFlameOn = GEJ85_Tt5AV_FLAME_ON;
    ContStartP->Tt5AvMax = GEJ85_Tt5AV_MAX;
    ContStartP->ValveInit = GEJ85_VALVE_INIT;
    ContStartP->ValveTotal = GEJ85_VALVE_TOTAL;
    ContStartP->WaitAction = GEJ85_WAIT_ACTION;
}

