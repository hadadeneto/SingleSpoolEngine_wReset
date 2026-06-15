/*
 * EngineModel.c
 *
 *  Created on: March 1, 2019
 *      Author: anton
 */


/* Math lib */
#include <math.h>

#include "Model_Types.h"
#include "ConstantsTJ1200.h"
#include "ConstantsTF1200.h"
#include "ConstantsGEJ85.h"



void getEngConst(int *Alt_Elem, int *MN_Elem, int *AS_Elem, int *Fn_Elem, int *SteadyOp_Elem, int *PowerMan_Elem, int *NcFANMap_Elem, int *WcFANMap_Elem, int *Wc_per_Nc_FAN,
			     int *NcHPCMap_Elem, int *WcHPCMap_Elem, int *Wc_per_Nc_HPC, int *NcHPTMap_Elem, int *PRHPTMap_Elem, int *WcHPTMap_Elem, double *WfMax_Pump,
			     struct EnginePars *EngPars, int WhichEngine)
{
  
	/* LOADS THE GAINS ACCORDING TO REQUESTED ENGINE */
	/* WhichEngine == 1 -> TJ1200 */

	// if (WhichEngine == 1)
	// {

	// 	/* Number of altitude, Mach Number and Power Elements */
	// 	*Alt_Elem = TJ1200_ALT_ELEM;
	// 	*MN_Elem = TJ1200_MN_ELEM;
	// 	*Fn_Elem = TJ1200_FN_ELEM;
	// 	*AS_Elem = TJ1200_AS_ELEM;
        
	// 	/* Number of steady operating points used for linearization at Sea Level */
	// 	*SteadyOp_Elem = TJ1200_FN_ELEM * TJ1200_MN_ELEM;

	// 	/* Number of total steady operating points used for Power Management Controller - all altitudes */
	// 	*PowerMan_Elem = TJ1200_TOTAL_ELEM;

	// 	/* Fan map size */
	// 	*NcFANMap_Elem = TJ1200_FAN_NC;
	// 	*WcFANMap_Elem = TJ1200_FAN_NC * TJ1200_FAN_PR;
	// 	*Wc_per_Nc_FAN = TJ1200_FAN_PR;

	// 	/* Compressor map size */
	// 	*NcHPCMap_Elem = TJ1200_FAN_NC;
	// 	*WcHPCMap_Elem = TJ1200_FAN_NC * TJ1200_FAN_PR;
	// 	*Wc_per_Nc_HPC = TJ1200_FAN_PR;

	// 	/* Turbine map size */
	// 	*NcHPTMap_Elem = TJ1200_HPT_NC;
	// 	*PRHPTMap_Elem = TJ1200_HPT_PR;
	// 	*WcHPTMap_Elem = TJ1200_HPT_NC * TJ1200_HPT_PR;

	// 	/* Loads Engine Parameters */
	// 	EngPars->Fuel_BOut = TJ1200_FUEL_BOUT;
	// 	EngPars->Ign_Delta = TJ1200_IGN_DELTAT;
	// 	EngPars->Ign_Time = TJ1200_IGN_TIME;
	// 	EngPars->POilMin = TJ1200_POIL;
	// 	EngPars->Valve_Fuel = TJ1200_VALVE_FUEL;
	// 	EngPars->Ath = TJ1200_Ath_NOZZLE;
	// 	EngPars->NDes = TJ1200_NDES;
	// 	EngPars->RPM_BOut = TJ1200_RPM_BOUT;

	// 	/* Pump maximum fuel flow - used in real Hardware only */
	// 	*WfMax_Pump = TJ1200_WFMAX;
        
    //     /* Loads fault parameters */
    //     EngPars->TCSCV = TJ1200_TCSCV;
    //     EngPars->TCSCG = TJ1200_TCSCG;
    //     EngPars->TCOPEN = TJ1200_TCOPEN;
    //     EngPars->PSSHORT = TJ1200_PSSHORT; 
	// 	EngPars->PFUELSHORT = TJ1200_PFUELSHORT;
    //     EngPars->PSSOPEN = TJ1200_PSSOPEN;  
	// 	EngPars->Tt4HIGH = TJ1200_TT4MAX * 1.15;
    //     EngPars->Tt4BLLCK = TJ1200_Tt4BLLCK; 
    //     EngPars->Tt4SHLCK = TJ1200_Tt4SHLCK;
	// 	EngPars->RPMHIGH = TJ1200_NMAX * 1.15;
	// 	EngPars->RPMSOPEN = TJ1200_RPMOPEN;
	// 	EngPars->RPMSSHORT = TJ1200_RPMSHORT;
    // 	EngPars->VIBSHORT = TJ1200_VIBSHORT;
    //     EngPars->VIBOPEN = TJ1200_VIBOPEN; 
    //     EngPars->VIBHIGH = TJ1200_VIBHIGH; 
    //     EngPars->POILHIGH = TJ1200_POILHIGH; 
    //     EngPars->POILLOW = TJ1200_POILLOW; 
    //     EngPars->PFUELHIGH = TJ1200_PFUELHIGH;
    //     EngPars->PFUELLOW = TJ1200_PFUELLOW;
	// 	EngPars->TBearHIGH[0] = TJ1200_BEAR_TMAX_0 * 1.15;
	// 	EngPars->TBearHIGH[1] = TJ1200_BEAR_TMAX_1 * 1.15;
	// 	EngPars->TBearHIGH[2] = TJ1200_BEAR_TMAX_2 * 1.15;
        
    //     /* Loads model parameters for Pfuel, POil and Vibration */
    //     EngPars->PFUELMODEL = TJ1200_PFUELMODEL;
    //     EngPars->POILMODEL = TJ1200_POILMODEL;
    //     EngPars->VIBMODEL = TJ1200_VIBMODEL;

	// 	/* Loads peripherals time constants */
	// 	EngPars->TTCTimeConst = TJ1200_TTCTIMECONST;
	// 	EngPars->PSensTimeConst = TJ1200_PSENSTIMECONST;
	// 	EngPars->FuelPumpTimeConstant = TJ1200_FUELPUMPTIMECONSTANT;
	// }

	// if (WhichEngine == 2)
	// {

	// 	/* Number of altitude, Mach Number and Power Elements */
	// 	*Alt_Elem = TF1200_ALT_ELEM;
	// 	*MN_Elem = TF1200_MN_ELEM;
	// 	*Fn_Elem = TF1200_FN_ELEM;
	// 	*AS_Elem = TF1200_AS_ELEM;
        
	// 	/* Number of steady operating points used for linearization at Sea Level */
	// 	*SteadyOp_Elem = TF1200_FN_ELEM * TF1200_MN_ELEM;

	// 	/* Number of total steady operating points used for Power Management Controller - all altitudes */
	// 	*PowerMan_Elem = TF1200_TOTAL_ELEM;

	// 	/* Fan map size */
	// 	*NcFANMap_Elem = TF1200_FAN_NC;
	// 	*WcFANMap_Elem = TF1200_FAN_NC * TF1200_FAN_PR;
	// 	*Wc_per_Nc_FAN = TF1200_FAN_PR;

	// 	/* Compressor map size */
	// 	*NcHPCMap_Elem = TF1200_HPC_NC;
	// 	*WcHPCMap_Elem = TF1200_HPC_NC * TF1200_HPC_PR;
	// 	*Wc_per_Nc_HPC = TF1200_HPC_PR;

	// 	/* Turbine map size */
	// 	*NcHPTMap_Elem = TF1200_HPT_NC;
	// 	*PRHPTMap_Elem = TF1200_HPT_PR;
	// 	*WcHPTMap_Elem = TF1200_HPT_NC * TF1200_HPT_PR;

	// 	/* Loads Engine Parameters */
	// 	EngPars->Fuel_BOut = TF1200_FUEL_BOUT;
	// 	EngPars->Ign_Delta = TF1200_IGN_DELTAT;
	// 	EngPars->Ign_Time = TF1200_IGN_TIME;
	// 	EngPars->POilMin = TF1200_POIL;
	// 	EngPars->Valve_Fuel = TF1200_VALVE_FUEL;
	// 	EngPars->Ath = TF1200_Ath_NOZZLE;
	// 	EngPars->NDes = TF1200_NDES;
	// 	EngPars->RPM_BOut = TF1200_RPM_BOUT;

	// 	/* Pump maximum fuel flow - used in real Hardware only */
	// 	*WfMax_Pump = TF1200_WFMAX;
        
    //     /* Loads fault parameters */
    //     EngPars->TCSCV = TF1200_TCSCV;
    //     EngPars->TCSCG = TF1200_TCSCG;
    //     EngPars->TCOPEN = TF1200_TCOPEN;
    //     EngPars->PSSHORT = TF1200_PSSHORT; 
    //     EngPars->PSSOPEN = TF1200_PSSOPEN;  
	// 	EngPars->Tt4HIGH = TF1200_TT4MAX * 1.15;
    //     EngPars->Tt4BLLCK = TF1200_Tt4BLLCK; 
    //     EngPars->Tt4SHLCK = TF1200_Tt4SHLCK;
	// 	EngPars->RPMHIGH = TF1200_NMAX * 1.15;
	// 	EngPars->RPMSOPEN = TF1200_RPMOPEN;
	// 	EngPars->RPMSSHORT = TF1200_RPMSHORT;
    // 	EngPars->VIBSHORT = TF1200_VIBSHORT;
    //     EngPars->VIBOPEN = TF1200_VIBOPEN; 
    //     EngPars->VIBHIGH = TF1200_VIBHIGH; 
    //     EngPars->POILHIGH = TF1200_POILHIGH; 
    //     EngPars->POILLOW = TF1200_POILLOW; 
    //     EngPars->PFUELHIGH = TF1200_PFUELHIGH;
    //     EngPars->PFUELLOW = TF1200_PFUELLOW;
	// 	EngPars->TBearHIGH[0] = TF1200_BEAR_TMAX_0 * 1.15;
	// 	EngPars->TBearHIGH[1] = TF1200_BEAR_TMAX_1 * 1.15;
	// 	EngPars->TBearHIGH[2] = TF1200_BEAR_TMAX_2 * 1.15;

    //     /* Loads model parameters for Pfuel, POil and Vibration */
    //     EngPars->PFUELMODEL = TF1200_PFUELMODEL;
    //     EngPars->POILMODEL = TF1200_POILMODEL;
    //     EngPars->VIBMODEL = TF1200_VIBMODEL;

	// 	/* Loads peripherals time constants */
	// 	EngPars->TTCTimeConst = TF1200_TTCTIMECONST;
	// 	EngPars->PSensTimeConst = TF1200_PSENSTIMECONST;
	// 	EngPars->FuelPumpTimeConstant = TF1200_FUELPUMPTIMECONSTANT;
	// }

	if (WhichEngine == 3)
	{

		/* Number of altitude, Mach Number and Power Elements */
		*Alt_Elem = GEJ85_ALT_ELEM;
		*MN_Elem = GEJ85_MN_ELEM;
		*Fn_Elem = GEJ85_FN_ELEM;
		*AS_Elem = GEJ85_AS_ELEM;
        
		/* Number of steady operating points used for linearization at Sea Level */
		*SteadyOp_Elem = GEJ85_FN_ELEM * GEJ85_MN_ELEM;

		/* Number of total steady operating points used for Power Management Controller - all altitudes */
		*PowerMan_Elem = GEJ85_TOTAL_ELEM;

		/* Fan map size */
		*NcFANMap_Elem = GEJ85_FAN_NC;
		*WcFANMap_Elem = GEJ85_FAN_NC * GEJ85_FAN_PR;
		*Wc_per_Nc_FAN = GEJ85_FAN_PR;

		/* Compressor map size */
		*NcHPCMap_Elem = GEJ85_FAN_NC;
		*WcHPCMap_Elem = GEJ85_FAN_NC * GEJ85_FAN_PR;
		*Wc_per_Nc_HPC = GEJ85_FAN_PR;

		/* Turbine map size */
		*NcHPTMap_Elem = GEJ85_HPT_NC;
		*PRHPTMap_Elem = GEJ85_HPT_PR;
		*WcHPTMap_Elem = GEJ85_HPT_NC * GEJ85_HPT_PR;

		/* Loads Engine Parameters */
		EngPars->Fuel_BOut = GEJ85_FUEL_BOUT;
		EngPars->Ign_Delta = GEJ85_IGN_DELTAT;
		EngPars->Ign_Time = GEJ85_IGN_TIME;
		EngPars->POilMin = GEJ85_POIL;
		EngPars->Valve_Fuel = GEJ85_VALVE_FUEL;
		EngPars->Ath = GEJ85_Ath_NOZZLE;
		EngPars->NDes = GEJ85_NDES;
		EngPars->RPM_BOut = GEJ85_RPM_BOUT;

		/* Pump maximum fuel flow - used in real Hardware only */
		*WfMax_Pump = GEJ85_WFMAX;
        
        /* Loads fault parameters */
        EngPars->TCSCV = GEJ85_TCSCV;
        EngPars->TCSCG = GEJ85_TCSCG;
        EngPars->TCOPEN = GEJ85_TCOPEN;
        EngPars->PSSHORT = GEJ85_PSSHORT; 
        EngPars->PSSOPEN = GEJ85_PSSOPEN;  
		EngPars->Tt4HIGH = GEJ85_TT4MAX * 1.15;
        EngPars->Tt4BLLCK = GEJ85_Tt4BLLCK; 
        EngPars->Tt4SHLCK = GEJ85_Tt4SHLCK;
		EngPars->RPMHIGH = GEJ85_NMAX * 1.15;
		EngPars->RPMSOPEN = GEJ85_RPMOPEN;
		EngPars->RPMSSHORT = GEJ85_RPMSHORT;
    	EngPars->VIBSHORT = GEJ85_VIBSHORT;
        EngPars->VIBOPEN = GEJ85_VIBOPEN; 
        EngPars->VIBHIGH = GEJ85_VIBHIGH; 
        EngPars->POILHIGH = GEJ85_POILHIGH; 
        EngPars->POILLOW = GEJ85_POILLOW; 
        EngPars->PFUELHIGH = GEJ85_PFUELHIGH;
        EngPars->PFUELLOW = GEJ85_PFUELLOW;
		EngPars->TBearHIGH[0] = GEJ85_BEAR_TMAX_0 * 1.15;
		EngPars->TBearHIGH[1] = GEJ85_BEAR_TMAX_1 * 1.15;
		EngPars->TBearHIGH[2] = GEJ85_BEAR_TMAX_2 * 1.15;
        
        /* Loads model parameters for Pfuel, POil and Vibration */
        EngPars->PFUELMODEL = GEJ85_PFUELMODEL;
        EngPars->POILMODEL = GEJ85_POILMODEL;
        EngPars->VIBMODEL = GEJ85_VIBMODEL;

		/* Loads peripherals time constants */
		EngPars->TTCTimeConst = GEJ85_TTCTIMECONST;
		EngPars->PSensTimeConst = GEJ85_PSENSTIMECONST;
		EngPars->FuelPumpTimeConstant = GEJ85_FUELPUMPTIMECONSTANT;
	}

}

