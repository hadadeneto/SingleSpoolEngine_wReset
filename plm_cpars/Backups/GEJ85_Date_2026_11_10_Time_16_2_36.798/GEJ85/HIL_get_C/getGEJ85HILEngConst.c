
#include <math.h>
#include "../FADEC_Constants_H/ConstantsGEJ85.h"
#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../../FADEC_Defines_H/Model_Types.h"

void getGEJ85HILEngConst(struct EnginePars *EngPars, floating*WfMax_Pump)
{

    /* Loads engine model parameters */

    *WfMax_Pump = GEJ85_WFMAX;
    EngPars->Ath = GEJ85_Ath_NOZZLE;
    EngPars->FuelPumpTimeConstant = GEJ85_FUELPUMPTIMECONSTANT;
    EngPars->Fuel_BOut = GEJ85_FUEL_BOUT;
    EngPars->Ign_Delta = GEJ85_IGN_DELTAT;
    EngPars->Ign_Time = GEJ85_IGN_TIME;
    EngPars->NDes = GEJ85_NDES;
    EngPars->PFUELHIGH = GEJ85_PFUELHIGH;
    EngPars->PFUELLOW = GEJ85_PFUELLOW;
    EngPars->PFUELMODEL = GEJ85_PFUELMODEL;
    EngPars->PFUELSHORT = GEJ85_PFUELSHORT;
    EngPars->POILHIGH = GEJ85_POILHIGH;
    EngPars->POILLOW = GEJ85_POILLOW;
    EngPars->POILMODEL = GEJ85_POILMODEL;
    EngPars->POilMin = GEJ85_POIL;
    EngPars->PSSHORT = GEJ85_PSSHORT;
    EngPars->PSSOPEN = GEJ85_PSSOPEN;
    EngPars->PSensTimeConst = GEJ85_PSENSTIMECONST;
    EngPars->RPMHIGH = GEJ85_NMAX * 1.15;
    EngPars->RPMSOPEN = GEJ85_RPMOPEN;
    EngPars->RPMSSHORT = GEJ85_RPMSHORT;
    EngPars->RPM_BOut = GEJ85_RPM_BOUT;
    EngPars->TBearHIGH[0] = GEJ85_BEAR_TMAX_0 * 1.15;
    EngPars->TBearHIGH[1] = GEJ85_BEAR_TMAX_1 * 1.15;
    EngPars->TBearHIGH[2] = GEJ85_BEAR_TMAX_2 * 1.15;
    EngPars->TCOPEN = GEJ85_TCOPEN;
    EngPars->TCSCG = GEJ85_TCSCG;
    EngPars->TCSCV = GEJ85_TCSCV;
    EngPars->TTCTimeConst = GEJ85_TTCTIMECONST;
    EngPars->Tt4BLLCK = GEJ85_Tt4BLLCK;
    EngPars->Tt4HIGH = GEJ85_TT4MAX * 1.15;
    EngPars->Tt4SHLCK = GEJ85_Tt4SHLCK;
    EngPars->VIBHIGH = GEJ85_VIBHIGH;
    EngPars->VIBMODEL = GEJ85_VIBMODEL;
    EngPars->VIBOPEN = GEJ85_VIBOPEN;
    EngPars->VIBSHORT = GEJ85_VIBSHORT;
    EngPars->Valve_Fuel = GEJ85_VALVE_FUEL;

}