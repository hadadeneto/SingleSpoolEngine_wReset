
#include <math.h>
#include "../h_Files_HIL/ConstantsTJ1200.h"
#include "../h_Files_HIL/Control_Types.h"

void getTJ1200HILStartPars(struct ControlStart *ContStartP)
{

    /* Loads starting parameters */

    ContStartP->FuelHighPulse = TJ1200_FUEL_HIGH_PULSE;
    ContStartP->FuelImpulseTime = TJ1200_FUEL_IMPULSE_TIME;
    ContStartP->FuelInit = TJ1200_FUEL_INIT;
    ContStartP->FuelPerc = TJ1200_FUEL_PERC;
    ContStartP->FuelRamp = TJ1200_FUEL_RAMP;
    ContStartP->POilAlarm = TJ1200_POIL_ALARM;
    ContStartP->POilShutDown = TJ1200_POIL_SHUTDOWN;
    ContStartP->RPMIdle = TJ1200_RPM_IDLE;
    ContStartP->RPMIgnOff = TJ1200_RPM_IGN_OFF;
    ContStartP->RPMRelaysOn = TJ1200_RPM_RELAYS_ON;
    ContStartP->RPMValve100 = TJ1200_RPM_VALVE_100;
    ContStartP->TimeAccomodation = TJ1200_TIME_ACCOMODATION;
    ContStartP->TimeIgnition = TJ1200_TIME_IGNITION;
    ContStartP->TimeLowPOil = TJ1200_TIME_LOW_POIL;
    ContStartP->TimeOvertemp = TJ1200_TIME_OVERTEMP;
    ContStartP->Tt5AvFlameOn = TJ1200_Tt5AV_FLAME_ON;
    ContStartP->Tt5AvMax = TJ1200_Tt5AV_MAX;
    ContStartP->ValveInit = TJ1200_VALVE_INIT;
    ContStartP->ValveTotal = TJ1200_VALVE_TOTAL;
    ContStartP->WaitAction = TJ1200_WAIT_ACTION;

}