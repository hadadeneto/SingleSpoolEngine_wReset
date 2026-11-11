
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ40.h"
#include "../../FADEC_Defines_H/Control_Types.h"

void getTJ40HILStartPars(struct ControlStart *ContStartP)
{

    /* Loads starting parameters */

    ContStartP->FuelHighPulse = TJ40_FUEL_HIGH_PULSE;
    ContStartP->FuelImpulseTime = TJ40_FUEL_IMPULSE_TIME;
    ContStartP->FuelInit = TJ40_FUEL_INIT;
    ContStartP->FuelPerc = TJ40_FUEL_PERC;
    ContStartP->FuelRamp = TJ40_FUEL_RAMP;
    ContStartP->POilAlarm = TJ40_POIL_ALARM;
    ContStartP->POilShutDown = TJ40_POIL_SHUTDOWN;
    ContStartP->RPMIdle = TJ40_RPM_IDLE;
    ContStartP->RPMIgnOff = TJ40_RPM_IGN_OFF;
    ContStartP->RPMRelaysOn = TJ40_RPM_RELAYS_ON;
    ContStartP->RPMValve100 = TJ40_RPM_VALVE_100;
    ContStartP->TimeAccomodation = TJ40_TIME_ACCOMODATION;
    ContStartP->TimeIgnition = TJ40_TIME_IGNITION;
    ContStartP->TimeLowPOil = TJ40_TIME_LOW_POIL;
    ContStartP->TimeOvertemp = TJ40_TIME_OVERTEMP;
    ContStartP->Tt5AvFlameOn = TJ40_Tt5AV_FLAME_ON;
    ContStartP->Tt5AvMax = TJ40_Tt5AV_MAX;
    ContStartP->ValveInit = TJ40_VALVE_INIT;
    ContStartP->ValveTotal = TJ40_VALVE_TOTAL;
    ContStartP->WaitAction = TJ40_WAIT_ACTION;

}