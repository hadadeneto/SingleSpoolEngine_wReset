
#include <math.h>
#include "../FADEC_Constants_H/ConstantsGET700.h"
#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../../FADEC_Defines_H/Model_Types.h"

void getGET700HILEngConst(struct EnginePars *EngPars, floating*WfMax_Pump)
{

    /* Loads engine model parameters */

    *WfMax_Pump = GET700_WFMAX;
    EngPars->Ath = GET700_Ath_NOZZLE;
    EngPars->FuelPumpTimeConstant = GET700_FUELPUMPTIMECONSTANT;
    EngPars->Fuel_BOut = GET700_FUEL_BOUT;
    EngPars->Ign_Delta = GET700_IGN_DELTAT;
    EngPars->Ign_Time = GET700_IGN_TIME;
    EngPars->NDes = GET700_NDES;
    EngPars->PFUELHIGH = GET700_PFUELHIGH;
    EngPars->PFUELLOW = GET700_PFUELLOW;
    EngPars->PFUELMODEL = GET700_PFUELMODEL;
    EngPars->PFUELSHORT = GET700_PFUELSHORT;
    EngPars->POILHIGH = GET700_POILHIGH;
    EngPars->POILLOW = GET700_POILLOW;
    EngPars->POILMODEL = GET700_POILMODEL;
    EngPars->POilMin = GET700_POIL;
    EngPars->PSSHORT = GET700_PSSHORT;
    EngPars->PSSOPEN = GET700_PSSOPEN;
    EngPars->PSensTimeConst = GET700_PSENSTIMECONST;
    EngPars->RPMHIGH = GET700_NMAX * 1.15;
    EngPars->RPMSOPEN = GET700_RPMOPEN;
    EngPars->RPMSSHORT = GET700_RPMSHORT;
    EngPars->RPM_BOut = GET700_RPM_BOUT;
    EngPars->TBearHIGH[0] = GET700_BEAR_TMAX_0 * 1.15;
    EngPars->TBearHIGH[1] = GET700_BEAR_TMAX_1 * 1.15;
    EngPars->TBearHIGH[2] = GET700_BEAR_TMAX_2 * 1.15;
    EngPars->TCOPEN = GET700_TCOPEN;
    EngPars->TCSCG = GET700_TCSCG;
    EngPars->TCSCV = GET700_TCSCV;
    EngPars->TTCTimeConst = GET700_TTCTIMECONST;
    EngPars->Tt4BLLCK = GET700_Tt4BLLCK;
    EngPars->Tt4HIGH = GET700_TT4MAX * 1.15;
    EngPars->Tt4SHLCK = GET700_Tt4SHLCK;
    EngPars->VIBHIGH = GET700_VIBHIGH;
    EngPars->VIBMODEL = GET700_VIBMODEL;
    EngPars->VIBOPEN = GET700_VIBOPEN;
    EngPars->VIBSHORT = GET700_VIBSHORT;
    EngPars->Valve_Fuel = GET700_VALVE_FUEL;

}