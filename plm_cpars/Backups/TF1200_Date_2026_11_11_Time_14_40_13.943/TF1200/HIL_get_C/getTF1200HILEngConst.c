
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTF1200.h"
#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../../FADEC_Defines_H/Model_Types.h"

void getTF1200HILEngConst(struct EnginePars *EngPars, floating*WfMax_Pump)
{

    /* Loads engine model parameters */

    *WfMax_Pump = TF1200_WFMAX;
    EngPars->Ath = TF1200_Ath_NOZZLE;
    EngPars->FuelPumpTimeConstant = TF1200_FUELPUMPTIMECONSTANT;
    EngPars->Fuel_BOut = TF1200_FUEL_BOUT;
    EngPars->Ign_Delta = TF1200_IGN_DELTAT;
    EngPars->Ign_Time = TF1200_IGN_TIME;
    EngPars->NDes = TF1200_NDES;
    EngPars->PFUELHIGH = TF1200_PFUELHIGH;
    EngPars->PFUELLOW = TF1200_PFUELLOW;
    EngPars->PFUELMODEL = TF1200_PFUELMODEL;
    EngPars->PFUELSHORT = TF1200_PFUELSHORT;
    EngPars->POILHIGH = TF1200_POILHIGH;
    EngPars->POILLOW = TF1200_POILLOW;
    EngPars->POILMODEL = TF1200_POILMODEL;
    EngPars->POilMin = TF1200_POIL;
    EngPars->PSSHORT = TF1200_PSSHORT;
    EngPars->PSSOPEN = TF1200_PSSOPEN;
    EngPars->PSensTimeConst = TF1200_PSENSTIMECONST;
    EngPars->RPMHIGH = TF1200_NMAX * 1.15;
    EngPars->RPMSOPEN = TF1200_RPMOPEN;
    EngPars->RPMSSHORT = TF1200_RPMSHORT;
    EngPars->RPM_BOut = TF1200_RPM_BOUT;
    EngPars->TBearHIGH[0] = TF1200_BEAR_TMAX_0 * 1.15;
    EngPars->TBearHIGH[1] = TF1200_BEAR_TMAX_1 * 1.15;
    EngPars->TBearHIGH[2] = TF1200_BEAR_TMAX_2 * 1.15;
    EngPars->TCOPEN = TF1200_TCOPEN;
    EngPars->TCSCG = TF1200_TCSCG;
    EngPars->TCSCV = TF1200_TCSCV;
    EngPars->TTCTimeConst = TF1200_TTCTIMECONST;
    EngPars->Tt4BLLCK = TF1200_Tt4BLLCK;
    EngPars->Tt4HIGH = TF1200_TT4MAX * 1.15;
    EngPars->Tt4SHLCK = TF1200_Tt4SHLCK;
    EngPars->VIBHIGH = TF1200_VIBHIGH;
    EngPars->VIBMODEL = TF1200_VIBMODEL;
    EngPars->VIBOPEN = TF1200_VIBOPEN;
    EngPars->VIBSHORT = TF1200_VIBSHORT;
    EngPars->Valve_Fuel = TF1200_VALVE_FUEL;

}