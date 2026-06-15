
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTG200.h"
#include "../../FADEC_Defines_H/Control_Types.h"

void getTG200HILStartPars(struct ControlStart *ContStartP)
{

    /* Loads starting parameters */

    ContStartP->FuelHighPulse = TG200_FUEL_HIGH_PULSE;
    ContStartP->FuelImpulseTime = TG200_FUEL_IMPULSE_TIME;
    ContStartP->FuelInit = TG200_FUEL_INIT;
    ContStartP->FuelPerc = TG200_FUEL_PERC;
    ContStartP->FuelRamp = TG200_FUEL_RAMP;
    ContStartP->POilAlarm = TG200_POIL_ALARM;
    ContStartP->POilShutDown = TG200_POIL_SHUTDOWN;
    ContStartP->RPMIdle = TG200_RPM_IDLE;
    ContStartP->RPMIgnOff = TG200_RPM_IGN_OFF;
    ContStartP->RPMRelaysOn = TG200_RPM_RELAYS_ON;
    ContStartP->RPMValve100 = TG200_RPM_VALVE_100;
    ContStartP->TimeAccomodation = TG200_TIME_ACCOMODATION;
    ContStartP->TimeIgnition = TG200_TIME_IGNITION;
    ContStartP->TimeLowPOil = TG200_TIME_LOW_POIL;
    ContStartP->TimeOvertemp = TG200_TIME_OVERTEMP;
    ContStartP->Tt5AvFlameOn = TG200_Tt5AV_FLAME_ON;
    ContStartP->Tt5AvMax = TG200_Tt5AV_MAX;
    ContStartP->ValveInit = TG200_VALVE_INIT;
    ContStartP->ValveTotal = TG200_VALVE_TOTAL;
    ContStartP->WaitAction = TG200_WAIT_ACTION;

}