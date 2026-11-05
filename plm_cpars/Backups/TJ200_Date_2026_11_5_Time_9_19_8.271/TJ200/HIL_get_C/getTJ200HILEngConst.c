
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ200.h"
#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../../FADEC_Defines_H/Model_Types.h"

void getTJ200HILEngConst(struct EnginePars *EngPars, floating*WfMax_Pump)
{

    /* Loads engine model parameters */

    *WfMax_Pump = TJ200_WFMAX;
    EngPars->Ath = TJ200_Ath_NOZZLE;
    EngPars->FuelPumpTimeConstant = TJ200_FUELPUMPTIMECONSTANT;
    EngPars->Fuel_BOut = TJ200_FUEL_BOUT;
    EngPars->Ign_Delta = TJ200_IGN_DELTAT;
    EngPars->Ign_Time = TJ200_IGN_TIME;
    EngPars->NDes = TJ200_NDES;
    EngPars->PFUELHIGH = TJ200_PFUELHIGH;
    EngPars->PFUELLOW = TJ200_PFUELLOW;
    EngPars->PFUELMODEL = TJ200_PFUELMODEL;
    EngPars->PFUELSHORT = TJ200_PFUELSHORT;
    EngPars->POILHIGH = TJ200_POILHIGH;
    EngPars->POILLOW = TJ200_POILLOW;
    EngPars->POILMODEL = TJ200_POILMODEL;
    EngPars->POilMin = TJ200_POIL;
    EngPars->PSSHORT = TJ200_PSSHORT;
    EngPars->PSSOPEN = TJ200_PSSOPEN;
    EngPars->PSensTimeConst = TJ200_PSENSTIMECONST;
    EngPars->RPMHIGH = TJ200_NMAX * 1.15;
    EngPars->RPMSOPEN = TJ200_RPMOPEN;
    EngPars->RPMSSHORT = TJ200_RPMSHORT;
    EngPars->RPM_BOut = TJ200_RPM_BOUT;
    EngPars->TBearHIGH[0] = TJ200_BEAR_TMAX_0 * 1.15;
    EngPars->TBearHIGH[1] = TJ200_BEAR_TMAX_1 * 1.15;
    EngPars->TBearHIGH[2] = TJ200_BEAR_TMAX_2 * 1.15;
    EngPars->TCOPEN = TJ200_TCOPEN;
    EngPars->TCSCG = TJ200_TCSCG;
    EngPars->TCSCV = TJ200_TCSCV;
    EngPars->TTCTimeConst = TJ200_TTCTIMECONST;
    EngPars->Tt4BLLCK = TJ200_Tt4BLLCK;
    EngPars->Tt4HIGH = TJ200_TT4MAX * 1.15;
    EngPars->Tt4SHLCK = TJ200_Tt4SHLCK;
    EngPars->VIBHIGH = TJ200_VIBHIGH;
    EngPars->VIBMODEL = TJ200_VIBMODEL;
    EngPars->VIBOPEN = TJ200_VIBOPEN;
    EngPars->VIBSHORT = TJ200_VIBSHORT;
    EngPars->Valve_Fuel = TJ200_VALVE_FUEL;

}