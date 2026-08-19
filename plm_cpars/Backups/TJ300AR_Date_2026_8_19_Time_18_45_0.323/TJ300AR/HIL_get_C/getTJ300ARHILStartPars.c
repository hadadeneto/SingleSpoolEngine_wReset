
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ300AR.h"
#include "../../FADEC_Defines_H/Control_Types.h"

void getTJ300ARHILStartPars(struct ControlStart *ContStartP)
{

    /* Loads starting parameters */

    ContStartP->FuelHighPulse = TJ300AR_FUEL_HIGH_PULSE;
    ContStartP->FuelImpulseTime = TJ300AR_FUEL_IMPULSE_TIME;
    ContStartP->FuelInit = TJ300AR_FUEL_INIT;
    ContStartP->FuelPerc = TJ300AR_FUEL_PERC;
    ContStartP->FuelRamp = TJ300AR_FUEL_RAMP;
    ContStartP->POilAlarm = TJ300AR_POIL_ALARM;
    ContStartP->POilShutDown = TJ300AR_POIL_SHUTDOWN;
    ContStartP->RPMIdle = TJ300AR_RPM_IDLE;
    ContStartP->RPMIgnOff = TJ300AR_RPM_IGN_OFF;
    ContStartP->RPMRelaysOn = TJ300AR_RPM_RELAYS_ON;
    ContStartP->RPMValve100 = TJ300AR_RPM_VALVE_100;
    ContStartP->TimeAccomodation = TJ300AR_TIME_ACCOMODATION;
    ContStartP->TimeIgnition = TJ300AR_TIME_IGNITION;
    ContStartP->TimeLowPOil = TJ300AR_TIME_LOW_POIL;
    ContStartP->TimeOvertemp = TJ300AR_TIME_OVERTEMP;
    ContStartP->Tt5AvFlameOn = TJ300AR_Tt5AV_FLAME_ON;
    ContStartP->Tt5AvMax = TJ300AR_Tt5AV_MAX;
    ContStartP->ValveInit = TJ300AR_VALVE_INIT;
    ContStartP->ValveTotal = TJ300AR_VALVE_TOTAL;
    ContStartP->WaitAction = TJ300AR_WAIT_ACTION;

}