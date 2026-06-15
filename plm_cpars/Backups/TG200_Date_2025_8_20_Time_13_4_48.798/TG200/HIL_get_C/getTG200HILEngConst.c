
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTG200.h"
#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../../FADEC_Defines_H/Model_Types.h"

void getTG200HILEngConst(struct EnginePars *EngPars, floating*WfMax_Pump)
{

    /* Loads engine model parameters */

    *WfMax_Pump = TG200_WFMAX;
    EngPars->Ath = TG200_Ath_NOZZLE;
    EngPars->FuelPumpTimeConstant = TG200_FUELPUMPTIMECONSTANT;
    EngPars->Fuel_BOut = TG200_FUEL_BOUT;
    EngPars->Ign_Delta = TG200_IGN_DELTAT;
    EngPars->Ign_Time = TG200_IGN_TIME;
    EngPars->NDes = TG200_NDES;
    EngPars->PFUELHIGH = TG200_PFUELHIGH;
    EngPars->PFUELLOW = TG200_PFUELLOW;
    EngPars->PFUELMODEL = TG200_PFUELMODEL;
    EngPars->PFUELSHORT = TG200_PFUELSHORT;
    EngPars->POILHIGH = TG200_POILHIGH;
    EngPars->POILLOW = TG200_POILLOW;
    EngPars->POILMODEL = TG200_POILMODEL;
    EngPars->POilMin = TG200_POIL;
    EngPars->PSSHORT = TG200_PSSHORT;
    EngPars->PSSOPEN = TG200_PSSOPEN;
    EngPars->PSensTimeConst = TG200_PSENSTIMECONST;
    EngPars->RPMHIGH = TG200_NMAX * 1.15;
    EngPars->RPMSOPEN = TG200_RPMOPEN;
    EngPars->RPMSSHORT = TG200_RPMSHORT;
    EngPars->RPM_BOut = TG200_RPM_BOUT;
    EngPars->TBearHIGH[0] = TG200_BEAR_TMAX_0 * 1.15;
    EngPars->TBearHIGH[1] = TG200_BEAR_TMAX_1 * 1.15;
    EngPars->TBearHIGH[2] = TG200_BEAR_TMAX_2 * 1.15;
    EngPars->TCOPEN = TG200_TCOPEN;
    EngPars->TCSCG = TG200_TCSCG;
    EngPars->TCSCV = TG200_TCSCV;
    EngPars->TTCTimeConst = TG200_TTCTIMECONST;
    EngPars->Tt4BLLCK = TG200_Tt4BLLCK;
    EngPars->Tt4HIGH = TG200_TT4MAX * 1.15;
    EngPars->Tt4SHLCK = TG200_Tt4SHLCK;
    EngPars->VIBHIGH = TG200_VIBHIGH;
    EngPars->VIBMODEL = TG200_VIBMODEL;
    EngPars->VIBOPEN = TG200_VIBOPEN;
    EngPars->VIBSHORT = TG200_VIBSHORT;
    EngPars->Valve_Fuel = TG200_VALVE_FUEL;

}