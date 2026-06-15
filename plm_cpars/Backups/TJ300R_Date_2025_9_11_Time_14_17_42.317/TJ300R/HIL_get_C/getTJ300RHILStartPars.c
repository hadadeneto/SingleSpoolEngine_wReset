
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ300R.h"
#include "../../FADEC_Defines_H/Control_Types.h"

void getTJ300RHILStartPars(struct ControlStart *ContStartP)
{

    /* Loads starting parameters */

    ContStartP->FuelHighPulse = TJ300R_FUEL_HIGH_PULSE;
    ContStartP->FuelImpulseTime = TJ300R_FUEL_IMPULSE_TIME;
    ContStartP->FuelInit = TJ300R_FUEL_INIT;
    ContStartP->FuelPerc = TJ300R_FUEL_PERC;
    ContStartP->FuelRamp = TJ300R_FUEL_RAMP;
    ContStartP->POilAlarm = TJ300R_POIL_ALARM;
    ContStartP->POilShutDown = TJ300R_POIL_SHUTDOWN;
    ContStartP->RPMIdle = TJ300R_RPM_IDLE;
    ContStartP->RPMIgnOff = TJ300R_RPM_IGN_OFF;
    ContStartP->RPMRelaysOn = TJ300R_RPM_RELAYS_ON;
    ContStartP->RPMValve100 = TJ300R_RPM_VALVE_100;
    ContStartP->TimeAccomodation = TJ300R_TIME_ACCOMODATION;
    ContStartP->TimeIgnition = TJ300R_TIME_IGNITION;
    ContStartP->TimeLowPOil = TJ300R_TIME_LOW_POIL;
    ContStartP->TimeOvertemp = TJ300R_TIME_OVERTEMP;
    ContStartP->Tt5AvFlameOn = TJ300R_Tt5AV_FLAME_ON;
    ContStartP->Tt5AvMax = TJ300R_Tt5AV_MAX;
    ContStartP->ValveInit = TJ300R_VALVE_INIT;
    ContStartP->ValveTotal = TJ300R_VALVE_TOTAL;
    ContStartP->WaitAction = TJ300R_WAIT_ACTION;

}