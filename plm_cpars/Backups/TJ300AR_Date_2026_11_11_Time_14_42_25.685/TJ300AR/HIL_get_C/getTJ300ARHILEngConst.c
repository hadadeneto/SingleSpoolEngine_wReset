
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ300AR.h"
#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../../FADEC_Defines_H/Model_Types.h"

void getTJ300ARHILEngConst(struct EnginePars *EngPars, floating*WfMax_Pump)
{

    /* Loads engine model parameters */

    *WfMax_Pump = TJ300AR_WFMAX;
    EngPars->Ath = TJ300AR_Ath_NOZZLE;
    EngPars->FuelPumpTimeConstant = TJ300AR_FUELPUMPTIMECONSTANT;
    EngPars->Fuel_BOut = TJ300AR_FUEL_BOUT;
    EngPars->Ign_Delta = TJ300AR_IGN_DELTAT;
    EngPars->Ign_Time = TJ300AR_IGN_TIME;
    EngPars->NDes = TJ300AR_NDES;
    EngPars->PFUELHIGH = TJ300AR_PFUELHIGH;
    EngPars->PFUELLOW = TJ300AR_PFUELLOW;
    EngPars->PFUELMODEL = TJ300AR_PFUELMODEL;
    EngPars->PFUELSHORT = TJ300AR_PFUELSHORT;
    EngPars->POILHIGH = TJ300AR_POILHIGH;
    EngPars->POILLOW = TJ300AR_POILLOW;
    EngPars->POILMODEL = TJ300AR_POILMODEL;
    EngPars->POilMin = TJ300AR_POIL;
    EngPars->PSSHORT = TJ300AR_PSSHORT;
    EngPars->PSSOPEN = TJ300AR_PSSOPEN;
    EngPars->PSensTimeConst = TJ300AR_PSENSTIMECONST;
    EngPars->RPMHIGH = TJ300AR_NMAX * 1.15;
    EngPars->RPMSOPEN = TJ300AR_RPMOPEN;
    EngPars->RPMSSHORT = TJ300AR_RPMSHORT;
    EngPars->RPM_BOut = TJ300AR_RPM_BOUT;
    EngPars->TBearHIGH[0] = TJ300AR_BEAR_TMAX_0 * 1.15;
    EngPars->TBearHIGH[1] = TJ300AR_BEAR_TMAX_1 * 1.15;
    EngPars->TBearHIGH[2] = TJ300AR_BEAR_TMAX_2 * 1.15;
    EngPars->TCOPEN = TJ300AR_TCOPEN;
    EngPars->TCSCG = TJ300AR_TCSCG;
    EngPars->TCSCV = TJ300AR_TCSCV;
    EngPars->TTCTimeConst = TJ300AR_TTCTIMECONST;
    EngPars->Tt4BLLCK = TJ300AR_Tt4BLLCK;
    EngPars->Tt4HIGH = TJ300AR_TT4MAX * 1.15;
    EngPars->Tt4SHLCK = TJ300AR_Tt4SHLCK;
    EngPars->VIBHIGH = TJ300AR_VIBHIGH;
    EngPars->VIBMODEL = TJ300AR_VIBMODEL;
    EngPars->VIBOPEN = TJ300AR_VIBOPEN;
    EngPars->VIBSHORT = TJ300AR_VIBSHORT;
    EngPars->Valve_Fuel = TJ300AR_VALVE_FUEL;

}