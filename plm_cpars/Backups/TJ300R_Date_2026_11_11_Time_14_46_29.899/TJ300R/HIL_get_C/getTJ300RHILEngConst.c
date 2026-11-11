
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ300R.h"
#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../../FADEC_Defines_H/Model_Types.h"

void getTJ300RHILEngConst(struct EnginePars *EngPars, floating*WfMax_Pump)
{

    /* Loads engine model parameters */

    *WfMax_Pump = TJ300R_WFMAX;
    EngPars->Ath = TJ300R_Ath_NOZZLE;
    EngPars->FuelPumpTimeConstant = TJ300R_FUELPUMPTIMECONSTANT;
    EngPars->Fuel_BOut = TJ300R_FUEL_BOUT;
    EngPars->Ign_Delta = TJ300R_IGN_DELTAT;
    EngPars->Ign_Time = TJ300R_IGN_TIME;
    EngPars->NDes = TJ300R_NDES;
    EngPars->PFUELHIGH = TJ300R_PFUELHIGH;
    EngPars->PFUELLOW = TJ300R_PFUELLOW;
    EngPars->PFUELMODEL = TJ300R_PFUELMODEL;
    EngPars->PFUELSHORT = TJ300R_PFUELSHORT;
    EngPars->POILHIGH = TJ300R_POILHIGH;
    EngPars->POILLOW = TJ300R_POILLOW;
    EngPars->POILMODEL = TJ300R_POILMODEL;
    EngPars->POilMin = TJ300R_POIL;
    EngPars->PSSHORT = TJ300R_PSSHORT;
    EngPars->PSSOPEN = TJ300R_PSSOPEN;
    EngPars->PSensTimeConst = TJ300R_PSENSTIMECONST;
    EngPars->RPMHIGH = TJ300R_NMAX * 1.15;
    EngPars->RPMSOPEN = TJ300R_RPMOPEN;
    EngPars->RPMSSHORT = TJ300R_RPMSHORT;
    EngPars->RPM_BOut = TJ300R_RPM_BOUT;
    EngPars->TBearHIGH[0] = TJ300R_BEAR_TMAX_0 * 1.15;
    EngPars->TBearHIGH[1] = TJ300R_BEAR_TMAX_1 * 1.15;
    EngPars->TBearHIGH[2] = TJ300R_BEAR_TMAX_2 * 1.15;
    EngPars->TCOPEN = TJ300R_TCOPEN;
    EngPars->TCSCG = TJ300R_TCSCG;
    EngPars->TCSCV = TJ300R_TCSCV;
    EngPars->TTCTimeConst = TJ300R_TTCTIMECONST;
    EngPars->Tt4BLLCK = TJ300R_Tt4BLLCK;
    EngPars->Tt4HIGH = TJ300R_TT4MAX * 1.15;
    EngPars->Tt4SHLCK = TJ300R_Tt4SHLCK;
    EngPars->VIBHIGH = TJ300R_VIBHIGH;
    EngPars->VIBMODEL = TJ300R_VIBMODEL;
    EngPars->VIBOPEN = TJ300R_VIBOPEN;
    EngPars->VIBSHORT = TJ300R_VIBSHORT;
    EngPars->Valve_Fuel = TJ300R_VALVE_FUEL;

}