
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ40.h"
#include "../../FADEC_Defines_H/Model_Types.h"

void getTJ40HILEngConst(struct EnginePars *EngPars, double*WfMax_Pump)
{

    /* Loads engine model parameters */

    *WfMax_Pump = TJ40_WFMAX;
    EngPars->Ath = TJ40_Ath_NOZZLE;
    EngPars->FuelPumpTimeConstant = TJ40_FUELPUMPTIMECONSTANT;
    EngPars->Fuel_BOut = TJ40_FUEL_BOUT;
    EngPars->Ign_Delta = TJ40_IGN_DELTAT;
    EngPars->Ign_Time = TJ40_IGN_TIME;
    EngPars->NDes = TJ40_NDES;
    EngPars->PFUELHIGH = TJ40_PFUELHIGH;
    EngPars->PFUELLOW = TJ40_PFUELLOW;
    EngPars->PFUELMODEL = TJ40_PFUELMODEL;
    EngPars->PFUELSHORT = TJ40_PFUELSHORT;
    EngPars->POILHIGH = TJ40_POILHIGH;
    EngPars->POILLOW = TJ40_POILLOW;
    EngPars->POILMODEL = TJ40_POILMODEL;
    EngPars->POilMin = TJ40_POIL;
    EngPars->PSSHORT = TJ40_PSSHORT;
    EngPars->PSSOPEN = TJ40_PSSOPEN;
    EngPars->PSensTimeConst = TJ40_PSENSTIMECONST;
    EngPars->RPMHIGH = TJ40_NMAX * 1.15;
    EngPars->RPMSOPEN = TJ40_RPMOPEN;
    EngPars->RPMSSHORT = TJ40_RPMSHORT;
    EngPars->RPM_BOut = TJ40_RPM_BOUT;
    EngPars->TBearHIGH[0] = TJ40_BEAR_TMAX_0 * 1.15;
    EngPars->TBearHIGH[1] = TJ40_BEAR_TMAX_1 * 1.15;
    EngPars->TBearHIGH[2] = TJ40_BEAR_TMAX_2 * 1.15;
    EngPars->TCOPEN = TJ40_TCOPEN;
    EngPars->TCSCG = TJ40_TCSCG;
    EngPars->TCSCV = TJ40_TCSCV;
    EngPars->TTCTimeConst = TJ40_TTCTIMECONST;
    EngPars->Tt4BLLCK = TJ40_Tt4BLLCK;
    EngPars->Tt4HIGH = TJ40_TT4MAX * 1.15;
    EngPars->Tt4SHLCK = TJ40_Tt4SHLCK;
    EngPars->VIBHIGH = TJ40_VIBHIGH;
    EngPars->VIBMODEL = TJ40_VIBMODEL;
    EngPars->VIBOPEN = TJ40_VIBOPEN;
    EngPars->VIBSHORT = TJ40_VIBSHORT;
    EngPars->Valve_Fuel = TJ40_VALVE_FUEL;

}