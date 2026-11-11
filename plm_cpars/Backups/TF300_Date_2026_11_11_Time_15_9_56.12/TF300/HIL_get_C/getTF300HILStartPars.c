
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTF300.h"
#include "../../FADEC_Defines_H/Control_Types.h"

void getTF300HILStartPars(struct ControlStart *ContStartP)
{

    /* Loads starting parameters */

    ContStartP->FuelHighPulse = TF300_FUEL_HIGH_PULSE;
    ContStartP->FuelImpulseTime = TF300_FUEL_IMPULSE_TIME;
    ContStartP->FuelInit = TF300_FUEL_INIT;
    ContStartP->FuelPerc = TF300_FUEL_PERC;
    ContStartP->FuelRamp = TF300_FUEL_RAMP;
    ContStartP->POilAlarm = TF300_POIL_ALARM;
    ContStartP->POilShutDown = TF300_POIL_SHUTDOWN;
    ContStartP->RPMIdle = TF300_RPM_IDLE;
    ContStartP->RPMIgnOff = TF300_RPM_IGN_OFF;
    ContStartP->RPMRelaysOn = TF300_RPM_RELAYS_ON;
    ContStartP->RPMValve100 = TF300_RPM_VALVE_100;
    ContStartP->TimeAccomodation = TF300_TIME_ACCOMODATION;
    ContStartP->TimeIgnition = TF300_TIME_IGNITION;
    ContStartP->TimeLowPOil = TF300_TIME_LOW_POIL;
    ContStartP->TimeOvertemp = TF300_TIME_OVERTEMP;
    ContStartP->Tt5AvFlameOn = TF300_Tt5AV_FLAME_ON;
    ContStartP->Tt5AvMax = TF300_Tt5AV_MAX;
    ContStartP->ValveInit = TF300_VALVE_INIT;
    ContStartP->ValveTotal = TF300_VALVE_TOTAL;
    ContStartP->WaitAction = TF300_WAIT_ACTION;

}