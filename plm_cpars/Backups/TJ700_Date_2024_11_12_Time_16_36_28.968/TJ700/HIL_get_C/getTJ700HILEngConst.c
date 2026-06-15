
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ700.h"
#include "../../FADEC_Defines_H/Model_Types.h"

void getTJ700HILEngConst(struct EnginePars *EngPars, double*WfMax_Pump)
{

    /* Loads engine model parameters */

    *WfMax_Pump = TJ700_WFMAX;
    EngPars->Ath = TJ700_Ath_NOZZLE;
    EngPars->FuelPumpTimeConstant = TJ700_FUELPUMPTIMECONSTANT;
    EngPars->Fuel_BOut = TJ700_FUEL_BOUT;
    EngPars->Ign_Delta = TJ700_IGN_DELTAT;
    EngPars->Ign_Time = TJ700_IGN_TIME;
    EngPars->NDes = TJ700_NDES;
    EngPars->PFUELHIGH = TJ700_PFUELHIGH;
    EngPars->PFUELLOW = TJ700_PFUELLOW;
    EngPars->PFUELMODEL = TJ700_PFUELMODEL;
    EngPars->PFUELSHORT = TJ700_PFUELSHORT;
    EngPars->POILHIGH = TJ700_POILHIGH;
    EngPars->POILLOW = TJ700_POILLOW;
    EngPars->POILMODEL = TJ700_POILMODEL;
    EngPars->POilMin = TJ700_POIL;
    EngPars->PSSHORT = TJ700_PSSHORT;
    EngPars->PSSOPEN = TJ700_PSSOPEN;
    EngPars->PSensTimeConst = TJ700_PSENSTIMECONST;
    EngPars->RPMHIGH = TJ700_NMAX * 1.15;
    EngPars->RPMSOPEN = TJ700_RPMOPEN;
    EngPars->RPMSSHORT = TJ700_RPMSHORT;
    EngPars->RPM_BOut = TJ700_RPM_BOUT;
    EngPars->TBearHIGH[0] = TJ700_BEAR_TMAX_0 * 1.15;
    EngPars->TBearHIGH[1] = TJ700_BEAR_TMAX_1 * 1.15;
    EngPars->TBearHIGH[2] = TJ700_BEAR_TMAX_2 * 1.15;
    EngPars->TCOPEN = TJ700_TCOPEN;
    EngPars->TCSCG = TJ700_TCSCG;
    EngPars->TCSCV = TJ700_TCSCV;
    EngPars->TTCTimeConst = TJ700_TTCTIMECONST;
    EngPars->Tt4BLLCK = TJ700_Tt4BLLCK;
    EngPars->Tt4HIGH = TJ700_TT4MAX * 1.15;
    EngPars->Tt4SHLCK = TJ700_Tt4SHLCK;
    EngPars->VIBHIGH = TJ700_VIBHIGH;
    EngPars->VIBMODEL = TJ700_VIBMODEL;
    EngPars->VIBOPEN = TJ700_VIBOPEN;
    EngPars->VIBSHORT = TJ700_VIBSHORT;
    EngPars->Valve_Fuel = TJ700_VALVE_FUEL;

}