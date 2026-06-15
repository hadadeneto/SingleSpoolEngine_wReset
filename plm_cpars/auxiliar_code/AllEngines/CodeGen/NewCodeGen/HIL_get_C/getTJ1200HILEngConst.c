
#include <math.h>
#include "../HIL_get_H/ConstantsTJ1200.h"
#include "../HIL_get_H/Model_Types.h"

void getTJ1200HILEngConst(struct EnginePars *EngPars, double*WfMax_Pump)
{

    /* Loads engine model parameters */

    *WfMax_Pump = TJ1200_WFMAX;
    EngPars->Ath = TJ1200_Ath_NOZZLE;
    EngPars->FuelPumpTimeConstant = TJ1200_FUELPUMPTIMECONSTANT;
    EngPars->Fuel_BOut = TJ1200_FUEL_BOUT;
    EngPars->Ign_Delta = TJ1200_IGN_DELTAT;
    EngPars->Ign_Time = TJ1200_IGN_TIME;
    EngPars->NDes = TJ1200_NDES;
    EngPars->PFUELHIGH = TJ1200_PFUELHIGH;
    EngPars->PFUELLOW = TJ1200_PFUELLOW;
    EngPars->PFUELMODEL = TJ1200_PFUELMODEL;
    EngPars->PFUELSHORT = TJ1200_PFUELSHORT;
    EngPars->POILHIGH = TJ1200_POILHIGH;
    EngPars->POILLOW = TJ1200_POILLOW;
    EngPars->POILMODEL = TJ1200_POILMODEL;
    EngPars->POilMin = TJ1200_POIL;
    EngPars->PSSHORT = TJ1200_PSSHORT;
    EngPars->PSSOPEN = TJ1200_PSSOPEN;
    EngPars->PSensTimeConst = TJ1200_PSENSTIMECONST;
    EngPars->RPMHIGH = TJ1200_NMAX * 1.15;
    EngPars->RPMSOPEN = TJ1200_RPMOPEN;
    EngPars->RPMSSHORT = TJ1200_RPMSHORT;
    EngPars->RPM_BOut = TJ1200_RPM_BOUT;
    EngPars->TBearHIGH[0] = TJ1200_BEAR_TMAX_0 * 1.15;
    EngPars->TBearHIGH[1] = TJ1200_BEAR_TMAX_1 * 1.15;
    EngPars->TBearHIGH[2] = TJ1200_BEAR_TMAX_2 * 1.15;
    EngPars->TCOPEN = TJ1200_TCOPEN;
    EngPars->TCSCG = TJ1200_TCSCG;
    EngPars->TCSCV = TJ1200_TCSCV;
    EngPars->TTCTimeConst = TJ1200_TTCTIMECONST;
    EngPars->Tt4BLLCK = TJ1200_Tt4BLLCK;
    EngPars->Tt4HIGH = TJ1200_TT4MAX * 1.15;
    EngPars->Tt4SHLCK = TJ1200_Tt4SHLCK;
    EngPars->VIBHIGH = TJ1200_VIBHIGH;
    EngPars->VIBMODEL = TJ1200_VIBMODEL;
    EngPars->VIBOPEN = TJ1200_VIBOPEN;
    EngPars->VIBSHORT = TJ1200_VIBSHORT;
    EngPars->Valve_Fuel = TJ1200_VALVE_FUEL;

}