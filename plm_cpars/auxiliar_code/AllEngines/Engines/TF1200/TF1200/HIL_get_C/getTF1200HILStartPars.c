
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTF1200.h"
#include "../../FADEC_Defines_H/Control_Types.h"

void getTF1200HILStartPars(struct ControlStart *ContStartP)
{

    /* Loads starting parameters */

    ContStartP->FuelHighPulse = TF1200_FUEL_HIGH_PULSE;
    ContStartP->FuelImpulseTime = TF1200_FUEL_IMPULSE_TIME;
    ContStartP->FuelInit = TF1200_FUEL_INIT;
    ContStartP->FuelPerc = TF1200_FUEL_PERC;
    ContStartP->FuelRamp = TF1200_FUEL_RAMP;
    ContStartP->POilAlarm = TF1200_POIL_ALARM;
    ContStartP->POilShutDown = TF1200_POIL_SHUTDOWN;
    ContStartP->RPMIdle = TF1200_RPM_IDLE;
    ContStartP->RPMIgnOff = TF1200_RPM_IGN_OFF;
    ContStartP->RPMRelaysOn = TF1200_RPM_RELAYS_ON;
    ContStartP->RPMValve100 = TF1200_RPM_VALVE_100;
    ContStartP->TimeAccomodation = TF1200_TIME_ACCOMODATION;
    ContStartP->TimeIgnition = TF1200_TIME_IGNITION;
    ContStartP->TimeLowPOil = TF1200_TIME_LOW_POIL;
    ContStartP->TimeOvertemp = TF1200_TIME_OVERTEMP;
    ContStartP->Tt5AvFlameOn = TF1200_Tt5AV_FLAME_ON;
    ContStartP->Tt5AvMax = TF1200_Tt5AV_MAX;
    ContStartP->ValveInit = TF1200_VALVE_INIT;
    ContStartP->ValveTotal = TF1200_VALVE_TOTAL;
    ContStartP->WaitAction = TF1200_WAIT_ACTION;

}