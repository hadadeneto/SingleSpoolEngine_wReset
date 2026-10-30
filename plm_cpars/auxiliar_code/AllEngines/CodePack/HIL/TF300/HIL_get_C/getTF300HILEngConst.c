
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTF300.h"
#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../../FADEC_Defines_H/Model_Types.h"

void getTF300HILEngConst(struct EnginePars *EngPars, floating*WfMax_Pump)
{

    /* Loads engine model parameters */

    *WfMax_Pump = TF300_WFMAX;
    EngPars->Ath = TF300_Ath_NOZZLE;
    EngPars->FuelPumpTimeConstant = TF300_FUELPUMPTIMECONSTANT;
    EngPars->Fuel_BOut = TF300_FUEL_BOUT;
    EngPars->Ign_Delta = TF300_IGN_DELTAT;
    EngPars->Ign_Time = TF300_IGN_TIME;
    EngPars->NDes = TF300_NDES;
    EngPars->PFUELHIGH = TF300_PFUELHIGH;
    EngPars->PFUELLOW = TF300_PFUELLOW;
    EngPars->PFUELMODEL = TF300_PFUELMODEL;
    EngPars->PFUELSHORT = TF300_PFUELSHORT;
    EngPars->POILHIGH = TF300_POILHIGH;
    EngPars->POILLOW = TF300_POILLOW;
    EngPars->POILMODEL = TF300_POILMODEL;
    EngPars->POilMin = TF300_POIL;
    EngPars->PSSHORT = TF300_PSSHORT;
    EngPars->PSSOPEN = TF300_PSSOPEN;
    EngPars->PSensTimeConst = TF300_PSENSTIMECONST;
    EngPars->RPMHIGH = TF300_NMAX * 1.15;
    EngPars->RPMSOPEN = TF300_RPMOPEN;
    EngPars->RPMSSHORT = TF300_RPMSHORT;
    EngPars->RPM_BOut = TF300_RPM_BOUT;
    EngPars->TBearHIGH[0] = TF300_BEAR_TMAX_0 * 1.15;
    EngPars->TBearHIGH[1] = TF300_BEAR_TMAX_1 * 1.15;
    EngPars->TBearHIGH[2] = TF300_BEAR_TMAX_2 * 1.15;
    EngPars->TCOPEN = TF300_TCOPEN;
    EngPars->TCSCG = TF300_TCSCG;
    EngPars->TCSCV = TF300_TCSCV;
    EngPars->TTCTimeConst = TF300_TTCTIMECONST;
    EngPars->Tt4BLLCK = TF300_Tt4BLLCK;
    EngPars->Tt4HIGH = TF300_TT4MAX * 1.15;
    EngPars->Tt4SHLCK = TF300_Tt4SHLCK;
    EngPars->VIBHIGH = TF300_VIBHIGH;
    EngPars->VIBMODEL = TF300_VIBMODEL;
    EngPars->VIBOPEN = TF300_VIBOPEN;
    EngPars->VIBSHORT = TF300_VIBSHORT;
    EngPars->Valve_Fuel = TF300_VALVE_FUEL;

}