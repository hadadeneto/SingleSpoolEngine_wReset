
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ700.h"
#include "../../FADEC_Defines_H/Control_Types.h"

void getTJ700HILStartPars(struct ControlStart *ContStartP)
{

    /* Loads starting parameters */

    ContStartP->FuelHighPulse = TJ700_FUEL_HIGH_PULSE;
    ContStartP->FuelImpulseTime = TJ700_FUEL_IMPULSE_TIME;
    ContStartP->FuelInit = TJ700_FUEL_INIT;
    ContStartP->FuelPerc = TJ700_FUEL_PERC;
    ContStartP->FuelRamp = TJ700_FUEL_RAMP;
    ContStartP->POilAlarm = TJ700_POIL_ALARM;
    ContStartP->POilShutDown = TJ700_POIL_SHUTDOWN;
    ContStartP->RPMIdle = TJ700_RPM_IDLE;
    ContStartP->RPMIgnOff = TJ700_RPM_IGN_OFF;
    ContStartP->RPMRelaysOn = TJ700_RPM_RELAYS_ON;
    ContStartP->RPMValve100 = TJ700_RPM_VALVE_100;
    ContStartP->TimeAccomodation = TJ700_TIME_ACCOMODATION;
    ContStartP->TimeIgnition = TJ700_TIME_IGNITION;
    ContStartP->TimeLowPOil = TJ700_TIME_LOW_POIL;
    ContStartP->TimeOvertemp = TJ700_TIME_OVERTEMP;
    ContStartP->Tt5AvFlameOn = TJ700_Tt5AV_FLAME_ON;
    ContStartP->Tt5AvMax = TJ700_Tt5AV_MAX;
    ContStartP->ValveInit = TJ700_VALVE_INIT;
    ContStartP->ValveTotal = TJ700_VALVE_TOTAL;
    ContStartP->WaitAction = TJ700_WAIT_ACTION;

}