
#include <math.h>
#include "../FADEC_Constants_H/ConstantsGET700.h"
#include "../../FADEC_Defines_H/Control_Types.h"

void getGET700HILStartPars(struct ControlStart *ContStartP)
{

    /* Loads starting parameters */

    ContStartP->FuelHighPulse = GET700_FUEL_HIGH_PULSE;
    ContStartP->FuelImpulseTime = GET700_FUEL_IMPULSE_TIME;
    ContStartP->FuelInit = GET700_FUEL_INIT;
    ContStartP->FuelPerc = GET700_FUEL_PERC;
    ContStartP->FuelRamp = GET700_FUEL_RAMP;
    ContStartP->POilAlarm = GET700_POIL_ALARM;
    ContStartP->POilShutDown = GET700_POIL_SHUTDOWN;
    ContStartP->RPMIdle = GET700_RPM_IDLE;
    ContStartP->RPMIgnOff = GET700_RPM_IGN_OFF;
    ContStartP->RPMRelaysOn = GET700_RPM_RELAYS_ON;
    ContStartP->RPMValve100 = GET700_RPM_VALVE_100;
    ContStartP->TimeAccomodation = GET700_TIME_ACCOMODATION;
    ContStartP->TimeIgnition = GET700_TIME_IGNITION;
    ContStartP->TimeLowPOil = GET700_TIME_LOW_POIL;
    ContStartP->TimeOvertemp = GET700_TIME_OVERTEMP;
    ContStartP->Tt5AvFlameOn = GET700_Tt5AV_FLAME_ON;
    ContStartP->Tt5AvMax = GET700_Tt5AV_MAX;
    ContStartP->ValveInit = GET700_VALVE_INIT;
    ContStartP->ValveTotal = GET700_VALVE_TOTAL;
    ContStartP->WaitAction = GET700_WAIT_ACTION;

}