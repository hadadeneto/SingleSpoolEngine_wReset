
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ200.h"
#include "../../FADEC_Defines_H/Control_Types.h"

void getTJ200HILStartPars(struct ControlStart *ContStartP)
{

    /* Loads starting parameters */

    ContStartP->FuelHighPulse = TJ200_FUEL_HIGH_PULSE;
    ContStartP->FuelImpulseTime = TJ200_FUEL_IMPULSE_TIME;
    ContStartP->FuelInit = TJ200_FUEL_INIT;
    ContStartP->FuelPerc = TJ200_FUEL_PERC;
    ContStartP->FuelRamp = TJ200_FUEL_RAMP;
    ContStartP->POilAlarm = TJ200_POIL_ALARM;
    ContStartP->POilShutDown = TJ200_POIL_SHUTDOWN;
    ContStartP->RPMIdle = TJ200_RPM_IDLE;
    ContStartP->RPMIgnOff = TJ200_RPM_IGN_OFF;
    ContStartP->RPMRelaysOn = TJ200_RPM_RELAYS_ON;
    ContStartP->RPMValve100 = TJ200_RPM_VALVE_100;
    ContStartP->TimeAccomodation = TJ200_TIME_ACCOMODATION;
    ContStartP->TimeIgnition = TJ200_TIME_IGNITION;
    ContStartP->TimeLowPOil = TJ200_TIME_LOW_POIL;
    ContStartP->TimeOvertemp = TJ200_TIME_OVERTEMP;
    ContStartP->Tt5AvFlameOn = TJ200_Tt5AV_FLAME_ON;
    ContStartP->Tt5AvMax = TJ200_Tt5AV_MAX;
    ContStartP->ValveInit = TJ200_VALVE_INIT;
    ContStartP->ValveTotal = TJ200_VALVE_TOTAL;
    ContStartP->WaitAction = TJ200_WAIT_ACTION;

}