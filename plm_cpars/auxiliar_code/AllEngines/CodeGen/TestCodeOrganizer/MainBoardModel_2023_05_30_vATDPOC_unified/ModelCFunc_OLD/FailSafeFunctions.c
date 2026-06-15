/*		HIL Code - FailSafeFunctions.c 
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % December, 2021
 * % *************************************************************************/

/* Standard libraries */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Created .h files */
#include "constants_TMATS.h"
#include "Control_Types.h"
#include "Env_SampTime.h"
#include "FaultSim_Types.h"
#include "functions_TMATS.h"
#include "Interpolation_Types.h"
#include "MtxIntFunctions.h"
#include "PeripheralDyn.h"
#include "PIOil.h"
#include "SI_AU_Convert.h"
#include "StartingFunctions.h"


/* -------------------------------------------------- */
/* INCLUDE - T-MATS & PWLM                            */
/* (To be usedi in MATLAB and TMATS simulations only) */
/* -------------------------------------------------- */

//#include "mex.h"

/* -------------------------------------------------- */

/*******************************************************************************
 *
 *	FUNCTION:		WindMillingState()
 *
 *	PURPOSE:		Updates status when a value of RPM larger than zero is detected
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double RPM,  struct ControlStart *ContStartP, digital_t *digitalP, int *status
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void WindMillingState(EngineStatus *EngStatusP, double RPM, struct ControllerConstants *ContConstP, double *TimeRPMP, double DetectTime, double Ts)
{

	int TimerReset;    

	/* Writes next status if RPM > 0 is detected */
	if (RPM > ContConstP->RPMWindmill)
	{
		/* Executes the timer subroutine for desired delay */
		TimerReset = TimerSR(TimeRPMP, Ts, DetectTime);

		/* If enought time has ellapsed since RPM > 0 has been detected, windmilling must be indicated */
		if (TimerReset == 1)
		{
			/* updates status */
			EngStatusP->EngineStatus = 0;
            EngStatusP->EngStatusBist.Windmilling = 1;
		}
		
	}
    	
}

/*******************************************************************************
 *
 *	FUNCTION:		ReadyToStartState()
 *
 *	PURPOSE:		Updates status when the value of RPM is larger than starting value
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double RPM,  struct ControlStart *ContStartP, digital_t *digitalP, int *status
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void ReadyToStartState(EngineStatus *EngStatusP, double RPM, struct ControllerConstants *ContConstP, double *TimeRPMP, double DetectTime, double Ts)
{
	int TimerReset;

	/* Writes next status if RPM > 0 is detected */
	if (RPM > ContConstP->RPMRelaysOn)
	{
		/* Executes the timer subroutine for desired delay */
		TimerReset = TimerSR(TimeRPMP, Ts, DetectTime);

		/* If enought time has ellapsed since RPM > 0 has been detected, windmilling must be indicated */
		if (TimerReset == 1)
		{
			/* updates status */
			EngStatusP->EngineStatus = 0;
            EngStatusP->EngStatusBist.ReadyToStart = 1;
		}
		
	}
	
}

/*******************************************************************************
 *
 *	FUNCTION:		RPMIdleState()
 *
 *	PURPOSE:		Updates status when engine is at idle and controlled automatically
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double RPM,  struct ControlStart *ContStartP, digital_t *digitalP, int *status
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void RPMIdleState(EngineStatus *EngStatusP, int status, int statusRef)
{
    //int TimerReset;

    /* If enought time has ellapsed since RPM > 0 has been detected, windmilling must be indicated */
    if (status == statusRef)
    {
        /* updates status */
        EngStatusP->EngineStatus = 0;
        EngStatusP->EngStatusBist.Idle = 1;
    }

}

/*******************************************************************************
 *
 *	FUNCTION:		StartingState()
 *
 *	PURPOSE:		Verifies if the engine is at starting state
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double RPM,  struct ControlStart *ContStartP, digital_t *digitalP, int *status
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void StartingState(EngineStatus *EngStatusP, int statusStart, int status, int StartCom, int StartWord)
{
    /* If enought time has ellapsed since RPM > 0 has been detected, windmilling must be indicated */
    if (status >= statusStart & StartCom == StartWord)
    {
        /* updates status */
        EngStatusP->EngineStatus = 0;
        EngStatusP->EngStatusBist.Starting = 1;
    }

}

/*******************************************************************************
 *
 *	FUNCTION:		RegimeState()
 *
 *	PURPOSE:		Verifires if the engine is at Regime state
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double RPM,  struct ControlStart *ContStartP, digital_t *digitalP, int *status
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void RegimeState(EngineStatus *EngStatusP, int statusIdle, int status, double ThrustCom)
{
    /* If enought time has ellapsed since RPM > 0 has been detected, windmilling must be indicated */
    if (status == statusIdle & ThrustCom > 0)
    {
        /* updates status */
        EngStatusP->EngineStatus = 0;
        EngStatusP->EngStatusBist.Regime = 1;
    }

}

/*******************************************************************************
 *
 *	FUNCTION:		DegradedState()
 *
 *	PURPOSE:		Verifires if the engine is at Degraded state - where, at any
 *                  measured engine station, all sensors have been lost and the 
 *                  corresponding paramter is currently etimated by engine model
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double RPM,  struct ControlStart *ContStartP, digital_t *digitalP, int *status
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void DegradedState(EngineStatus *EngStatusP, ModelParsFault *ModPFaultP)
{

    /* Any of the measured parameters is currently being estimated only by engine model,
       degraded status must be indicated */
    if (ModPFaultP->ModParsBits != 0)
    {
        /* updates status */
        EngStatusP->EngineStatus = 0;
        EngStatusP->EngStatusBist.Degraded = 1;
    }

}

/*******************************************************************************
 *
 *	FUNCTION:		CommandState()
 *
 *	PURPOSE:		Updates status when engine is at idle and controlled automatically
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double RPM,  struct ControlStart *ContStartP, digital_t *digitalP, int *status
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void CommandState(EngineStatus *EngStatusP, int ShutOff, int ShutOffWord, 
                  int Emergency, int EmergencyWord,int Fail, int FailWord)
{

    /* If Shut Off has been commanded and the eingine is not at EMERGENCY or FAIL, it must be set to SHUT OFF state */
    if ((ShutOff == ShutOffWord) & ~EngStatusP->EngStatusBist.Emergency & ~EngStatusP->EngStatusBist.Fail)
    {
        /* updates status */
        EngStatusP->EngineStatus = 0;
        EngStatusP->EngStatusBist.ShutOff = 1;
    }

    /* If Emergency has been commanded and the eingine is not at FAIL, it must be set to EMERGENCY state */
    if ((Emergency == EmergencyWord) & ~EngStatusP->EngStatusBist.Fail)
    {
        /* updates status */
        EngStatusP->EngineStatus = 0;
        EngStatusP->EngStatusBist.Emergency = 1;
    }

    /* If fail has been detected, engine state must be set to FAIL */
    if ((Fail == FailWord) & ~EngStatusP->EngStatusBist.Emergency)
    {
        /* updates status */
        EngStatusP->EngineStatus = 0;
        EngStatusP->EngStatusBist.Fail = 1;
    }

}

/*******************************************************************************
 *
 *	FUNCTION:		EngineStatusDeff()
 *
 *	PURPOSE:		Defnies the engine status to be informed 
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double RPM,  struct ControlStart *ContStartP, digital_t *digitalP, int *status
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void EngStatusDeff(EngineStatus *EngStatusP, ModelParsFault *ModPFaultP, struct ControllerInput *ContInputP,
                    struct ControlStart *ContStartP, struct ControllerConstants *ContConstP, 
                    int statusStart, int statusIdle,
                    int StartCom, int StartWord, int ThrustCom, 
                    int ShutOff, int ShutOffWord, int Emergency, int EmergencyWord,
                    int Fail, int FailWord, double Ts)
{

//    /* Internal auxiliary struct for using single bit variable */
//    struct{
//        uint64_t Bit :1;
//        uint64_t Reserved :63;
//    }StatusUpdate;
    /* Flag for detecting emergency status */
    struct{
        uint64_t Bit :1;
        uint64_t Reserved :63;
    }EmergencySatatus;

    double TimerWindMill = ContStartP->TimerWindMill;
    double TimerReadytoStart = ContStartP->TimerReadytoStart;
    double TimeWindMill = ContConstP->TimeWindmill;
    double TimeReadytoStart = ContConstP->TimeReadytoStart;
    double RPM = ContInputP->RPM;
    int status = ContStartP->status;

    /* The following flag inidcates any of the engine shut off situations, either due to
    shut off external command, emergency shut off external command of engine failure. In
    case any of thos states occur, they must be indicated with priority over the remaining ones */
    EmergencySatatus.Bit = EngStatusP->EngStatusBist.Emergency;
    EmergencySatatus.Bit = EmergencySatatus.Bit | EngStatusP->EngStatusBist.Fail;
    EmergencySatatus.Bit = EmergencySatatus.Bit | EngStatusP->EngStatusBist.ShutOff;

    switch (EngStatusP->EngineStatus)
    {
    case 0:

        /* updates status */
        EngStatusP->EngineStatus = 0;
        EngStatusP->EngStatusBist.Initialize = 1;

        break;

    case 1:

        /* Verifies if the eingine is at initial status or in windmilling */
        WindMillingState(EngStatusP, RPM, ContConstP, &TimerWindMill, TimeWindMill, Ts);

        break;

    case 2:

        /* Verifires if the engine is ready to be started */
        ReadyToStartState(EngStatusP, RPM, ContConstP, &TimerReadytoStart, TimeReadytoStart, Ts);

        break;

    case 4:

        /* If the engine is ready to starti, verifies if it is already starting */
        StartingState(EngStatusP, statusStart, status, StartCom, StartWord);

        break;

    case 8:

        /* Verifies if the engine is in idle state */
        RPMIdleState(EngStatusP, status, statusIdle);

        break;

    case 16:

        /* Verifies if the engine is in idle state */
        RegimeState(EngStatusP, statusIdle, status, ThrustCom);
        /* Verifies if the engine is in degraded state */
        DegradedState(EngStatusP, ModPFaultP);

        break;

    case 32:

        /* Verifies if the engine is in degraded state */
        DegradedState(EngStatusP, ModPFaultP);

        break;

    default:
        break;
    }

    /* Verifies if any engine is at any of the command states */
    CommandState(EngStatusP, ShutOff, ShutOffWord, 
                  Emergency, EmergencyWord, Fail, FailWord);

    /* Updates timer values */
    ContStartP->TimerWindMill = TimerWindMill;
    ContStartP->TimerReadytoStart = TimerReadytoStart;

}

/*******************************************************************************
 *
 *	FUNCTION:		IdleToRegime()
 *
 *	PURPOSE:		Allows change from IDLE to REGIME and thrust reference update 
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		struct ControllerInput *ContInputP, double reference, double *FNpc
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void IdleToRegime(EngineStatus *EngStatusP, struct ControllerInput *ContInputP, double Reference, double RefMin, double IdleRef, double *FNpc, int LeverMode)
{

    EngineStatus EngStatusAux;

    /* As soon as the reference becomes a positive value at, at least, IDLE status, the thrust command flag is set to 1
    indicating that a change from IDLE to REGIME is allowed */
    EngStatusAux.EngineStatus = 0;
    EngStatusAux.EngStatusBist.Idle = 1;
//    if (Reference > RefMin & EngStatusP->EngStatusBist.Idle)
    if (Reference > RefMin & EngStatusP->EngineStatus >= EngStatusAux.EngineStatus)
    {
        ContInputP->ThrustCommandOn = 1;
    }

    /* Once the thrust command flag is set to 1, FNpc can be updated to the reference value */
    /* Until then, it remains in idle reference */
    if (ContInputP->ThrustCommandOn == 1)
    {
        *FNpc = Reference;
    }
    else
    {
        *FNpc = IdleRef;
    }

    /* If the engine is running on manual lever, the reference should be read directly, regardless of any engine state */
    if (LeverMode == 0)
    {
        *FNpc = Reference;
    }
    
        
}

/*******************************************************************************
 *
 *	FUNCTION:		BoosterProtect()
 *
 *	PURPOSE:		Prevents blow out protection malfunctioning during booster
 *                  action
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void BoosterProtect(struct ControllerConstants *ContConstP, struct ControllerInput *ContInputP, double Delta, int BoosterLStatus, int BoosterRStatus, double Ts)
{
    /* Reads the booster timer value from control input */
    double TimerBooster = ContInputP->TimerBoost;

    switch (ContInputP->statusBooster)
    {
    case 0:

        if ((BoosterRStatus == 0x55) | (BoosterLStatus == 0x55))
        {
            /* If left or right booster are connected, Pt3 value is set to PSTD for
            avoiding malfunctioning of blow out protection */
            ContInputP->Pt3 = PSTD * Delta;
            TimerBooster = 0;
        }

        /* If boosters release is detected, a delay must be considered before blow out protection becomes active */
        if ((BoosterRStatus == 0xAA) & (BoosterLStatus == 0xAA))
        {
            /* Executes the timer subroutine for desired delay */
            ContInputP->statusBooster = TimerSR(&TimerBooster, Ts, ContConstP->BoostTime);
            /* If booster waiting time has not yet ellapsed, blow out protection should not yet be used */
            ContInputP->Pt3 = PSTD * Delta;
        }
        break;
    
    default:
        break;
    }

    /* Updates the booster timer value */
    ContInputP->TimerBoost = TimerBooster;

    
}

/*******************************************************************************
 *
 *	FUNCTION:		EstIndexTJ1200()
 *
 *	PURPOSE:		Calculates 3D indexes necessary for calculations
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		a, b
 *
 *	RETURNS:		Value
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void EstIndex(struct EstimatedPars *ModelParsP , double *AltLinVecP, double *MNLinVecP, 
                    double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP, 
                    double *FNperContMtxP, struct ControllerConstants *ContConstP, struct InterpIndex3D *Index3DP)
{
    
    /* Reads variables from the struct */
    double Altitude = ModelParsP->Altitude;
    double MN = ModelParsP->MN;
    double FNpc = ModelParsP->FNpc;
    
    /* Elements numbers */
    double Alt_Elem = ContConstP->Alt_Elem;
    double MN_Elem = ContConstP->MN_Elem;
    double Fn_Elem = ContConstP->Fn_Elem;
           
    /* Finds value of RPM reference from FNpc reference */
    InterpInd3DRPM(Altitude, MN, FNpc, AltLinVecP, MNLinVecP, FNperContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Alt_Elem, MN_Elem, Fn_Elem, Index3DP);
        
}

/*******************************************************************************
 *
 *	FUNCTION:		TCResCalc()
 *
 *	PURPOSE:		Calculates thermocouple residuals according to detected failure
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		a, b
 *
 *	RETURNS:		Value
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void TCResCalc(TCFaults *Ts2_0P, TCFaults *Ts2_1P, TCFaults *Tt4_0P, TCFaults *Tt4_1P, 
               TCFaults *Tt4_2P, TCFaults *TB_0P, TCFaults *TB_1P, TCFaults *TB_2P,
               struct AllResiduals *Ts2ResP, struct AllResiduals *Tt4ResP, struct AllResiduals *TBearResP)
{
    
    /*----------*/
    /* OC FAULT */
    /*----------*/
    
    /* Ts2 RESIDUAL CALCULATIONS */
    
    /* Calculates Ts2 1 OC residuals */
    if(Ts2_0P->Faults.OC)
    {
        Ts2ResP->Open[0] = 0;
    }
    else
    {
        Ts2ResP->Open[0] = 25000000;
    }

    /* Calculates Ts2 2 OC residuals */
    if(Ts2_1P->Faults.OC)
    {
        Ts2ResP->Open[1] = 0;
    }
    else
    {
        Ts2ResP->Open[1] = 25000000;
    }
    
    /* Tt4 RESIDUAL CALCULATIONS */
    
    /* Calculates Tt4 1 OC residuals */
    if(Tt4_0P->Faults.OC)
    {
        Tt4ResP->Open[0] = 0;
    }
    else
    {
        Tt4ResP->Open[0] = 25000000;
    }

    /* Calculates Tt4 2 OC residuals */
    if(Tt4_1P->Faults.OC)
    {
        Tt4ResP->Open[1] = 0;
    }
    else
    {
        Tt4ResP->Open[1] = 25000000;
    }
    /* Calculates Tt4 3 OC residuals */
    if(Tt4_2P->Faults.OC)
    {
        Tt4ResP->Open[2] = 0;
    }
    else
    {
        Tt4ResP->Open[2] = 25000000;
    }

    /* BEARINGS TEMPERATURES RESIDUAL CALCULATIONS */
    
    /* Calculates TB 1 OC residuals */
    if(TB_0P->Faults.OC)
    {
        TBearResP->Open[0] = 0;
    }
    else
    {
        TBearResP->Open[0] = 25000000;
    }

    /* Calculates Tt4 2 OC residuals */
    if(TB_1P->Faults.OC)
    {
        TBearResP->Open[1] = 0;
    }
    else
    {
        TBearResP->Open[1] = 25000000;
    }
    /* Calculates Tt4 3 OC residuals */
    if(TB_2P->Faults.OC)
    {
        TBearResP->Open[2] = 0;
    }
    else
    {
        TBearResP->Open[2] = 25000000;
    }
        
    /*-----------*/
    /* SCV FAULT */
    /*-----------*/
    
    /* Ts2 RESIDUAL CALCULATIONS */
    
    /* Calculates Ts2 1 SCV residuals */
    if(Ts2_0P->Faults.SCV)
    {
        Ts2ResP->SCV[0] = 0;
    }
    else
    {
        Ts2ResP->SCV[0] = 25000000;
    }

    /* Calculates Ts2 2 SCV residuals */
    if(Ts2_1P->Faults.SCV)
    {
        Ts2ResP->SCV[1] = 0;
    }
    else
    {
        Ts2ResP->SCV[1] = 25000000;
    }
    
    /* Tt4 RESIDUAL CALCULATIONS */
    
    /* Calculates Tt4 1 SCV residuals */
    if(Tt4_0P->Faults.SCV)
    {
        Tt4ResP->SCV[0] = 0;
    }
    else
    {
        Tt4ResP->SCV[0] = 25000000;
    }
    /* Calculates Tt4 2 SCV residuals */
    if(Tt4_1P->Faults.SCV)
    {
        Tt4ResP->SCV[1] = 0;
    }
    else
    {
        Tt4ResP->SCV[1] = 25000000;
    }
    /* Calculates Tt4 3 SCV residuals */
    if(Tt4_2P->Faults.SCV)
    {
        Tt4ResP->SCV[2] = 0;
    }
    else
    {
        Tt4ResP->SCV[2] = 25000000;
    }
    
    /*-----------*/
    /* SCG FAULT */
    /*-----------*/
    
    /* Ts2 RESIDUAL CALCULATIONS */
    
    /* Calculates Ts2 1 SCG residuals */
    if(Ts2_0P->Faults.SCG)
    {
        Ts2ResP->SCG[0] = 0;
    }
    else
    {
        Ts2ResP->SCG[0] = 25000000;
    }
    /* Calculates Ts2 2 SCG residuals */
    if(Ts2_1P->Faults.SCG)
    {
        Ts2ResP->SCG[1] = 0;
    }
    else
    {
        Ts2ResP->SCG[1] = 25000000;
    }
    
    /* Tt4 RESIDUAL CALCULATIONS */
    
    /* Calculates Tt4 1 SCG residuals */
    if(Tt4_0P->Faults.SCG)
    {
        Tt4ResP->SCG[0] = 0;
    }
    else
    {
        Tt4ResP->SCG[0] = 25000000;
    }
    /* Calculates Tt4 2 SCG residuals */
    if(Tt4_1P->Faults.SCG)
    {
        Tt4ResP->SCG[1] = 0;
    }
    else
    {
        Tt4ResP->SCG[1] = 25000000;
    }
    /* Calculates Tt4 3 SCG residuals */
    if(Tt4_2P->Faults.SCG)
    {
        Tt4ResP->SCG[2] = 0;
    }
    else
    {
        Tt4ResP->SCG[2] = 25000000;
    }
    
}

/*******************************************************************************
 *
 *	FUNCTION:		MedValue()
 *
 *	PURPOSE:		Calculates the medium value from sensor measurements and 
 *                  using the model value as a reference for evaluating sensors
 *                  Whatever sensor has a hard fault, meaning that is has a 
 *                  sufficiently high bias from the model value, is excluded
 *                  from the medium value
 *                  
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Sens0, Sens1, MaxError
 *
 *	RETURNS:		SensorMatch
 *
 *	COMMENTS:       
 *
 *******************************************************************************/

void MedValue(int SensTrust, double *SensVecP, int SensNum, double *MedVal, double ModelVal, int UseModelVal)
{

    /* Internal variables */
    int i;
    int UnitVar = 1;
    int Trust = 0;
    /* Number of trusted values in calculation */
    int NumTrusted = 0;
    /* Sum of sensors values */
    double Sum = 0;

    /* Loop for calculation of medium value */
    for(i = 0; i < SensNum; i++)
    {
        /* Trust indicates if the current sensor is to be trusted */
        Trust = (SensTrust >> i) & UnitVar;
        /* If the sensor is trusted, it is considered in the calculation
        Otherwise, the model value is considered */
        if(Trust == 1)
        {
            /* Addition of the sensor value */
            Sum = Sum + *(SensVecP + i);
            /* Trusted value number updating */
            NumTrusted++;
        }
        else if(UseModelVal == 1)
        {
            /* Addition of the model value */
            Sum = Sum + ModelVal;
            /* Trusted value number updating */
            NumTrusted++;
        }
        
    }

    /* Calculates the medium value if any sensor is to be trusted
    If not any sensor is to be trusted, the medium value is set to zero */
    if(NumTrusted > 0)
    {
        /* Calculation of medium value */
        *MedVal = Sum / NumTrusted;
    }    
    else
    {
        *MedVal = 0;
    }
}

/*******************************************************************************
 *
 *	FUNCTION:		RElError()
 *
 *	PURPOSE:		Calculates the relative error between two sensors
 *                  
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Sens0, Sens1, MaxError
 *
 *	RETURNS:		SensorMatch
 *
 *	COMMENTS:       
 *
 *******************************************************************************/

int RelError(double Sens0, double Sens1, double MaxError)
{
    /* Initialization of internal variables */
    double LargeSens = Sens0;
    double SmallSens = Sens1;
    double RelativeError;
    double NearZero = 1e-10;
    int SensorMatch = 0;

    /* Avoids division by zero by setting Sens1 equal MaxError in case both are zero */
//    if (Sens1 == 0 && Sens0 == 0)
//    {
//        LargeSens = MaxError;
//        SmallSens = MaxError;
//    }
    if (fabs(Sens1) <= NearZero && fabs(Sens0) <= NearZero)
    {
        LargeSens = MaxError;
        SmallSens = MaxError;
    }
    

    /* Verifies which sensor has measured a larger absolute value */
    if(fabs(Sens1) > fabs(Sens0))
    {
        LargeSens = Sens1;
        SmallSens = Sens0;
    }

    /* Calculates the relative error */
    RelativeError = fabs(LargeSens - SmallSens) / fabs(LargeSens);

    /* Indicates sensor matching if the relative error is lower than the maximum allowed error */
    if(RelativeError < MaxError)
    {
        SensorMatch = 1;
    }

    /* Returns the flag indicating sensor matching */
    return SensorMatch;

}

/*******************************************************************************
 *
 *	FUNCTION:		MatchSens()
 *
 *	PURPOSE:		Checks whitch sensors present similar measurements
 *                  
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double *SensVec, double *MatchVec, double NumSens, double MaxError
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       
 *
 *******************************************************************************/

void MatchSens(double *SensVec, int *MatchVec, int NumSens, double MaxError)
{
    /* Indexes */
    int i,j;
    /* Sensor values */
    double Sensi, Sensj;
    /* Adding termos */
    int AddTerm = 0;

    /* Initiates loop comparing ith sensor with the other jth sensors */
    for (i = 0; i < NumSens; i++)
    {
        
        for (j = 0; j < NumSens; j++)
        {
            /* If the i == j, j must be incremented for a comparison 
            between two equal sensors to be avoided */
            // if(i == j)
            // {
            //     j++;
            // }
            if(i != j)
            {
                
                /* Stores sensor values */
                Sensi = *(SensVec + i);
                Sensj = *(SensVec + j);

                /* Calculates sensors relaitve errors */
                AddTerm = RelError(Sensi, Sensj, MaxError);

                /* Updates number of matches of sensor i with other sensors */
                *(MatchVec + i) = *(MatchVec + i) + AddTerm;
            }
        }
        
    }
    
}

/*******************************************************************************
 *
 *	FUNCTION:		Ts2MediumValue()
 *
 *	PURPOSE:		Calculates the medium value of Ts2
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		void
 *
 *	COMMENTS:      
 *
 *******************************************************************************/

void Ts2MediumValue(ModelParsFault *ModPFaultP, double *Ts2MedValP, int SensNum, FaultDetect *TrustSensP, struct SensedPars *SensorsP, double Ts2Model,  int MinTrustedSens)
{
    int Trusted = 0;
    int NumTrusted = 0;
    int UseModVal = 0;
    double SensorAux[5] = {0,0,0,0,0};

    /* Computes the values of Ts2 sensors */
    SensorAux[0] = SensorsP->Ts2[0];
    SensorAux[1] = SensorsP->Ts2[1];

    /* Verifies if Ts2 0 thermocouple is to be trusted */
    if(TrustSensP->DetFaults.Ts2_0_Fault)
    {
        Trusted = 1;
        NumTrusted = NumTrusted + 1;
    }

    /* Verifies if Ts2 1 thermocouple is to be trusted */
    if(TrustSensP->DetFaults.Ts2_1_Fault)
    {
        Trusted = 2 + Trusted;
        NumTrusted = NumTrusted + 1;
    }

    /* If the number of trusted sensors is below minimum, the model value of Ts2 must beused
    to replace the measurements of the untrusted sensors */
    if(NumTrusted < MinTrustedSens)
    {
        UseModVal = 1;
    }

    /* Initiates ModelPars.Ts2 with 0 */
    ModPFaultP->ModelPars.Ts2 = 0;
    /* If the number of trusted sensors is zero, ModelPars.Ts2 is set to 1 indicating that
    all Ts2 sensors present hard fault */
    if(NumTrusted < 1)
    {
        ModPFaultP->ModelPars.Ts2 = 1;
    }

    /* Calculates the medium value of Ts2 */
    //MedValue(Trusted, &SensorAux, SensNum, Ts2MedValP, Ts2Model, UseModVal);
    MedValue(Trusted, SensorAux, SensNum, Ts2MedValP, Ts2Model, UseModVal);
}

/*******************************************************************************
 *
 *	FUNCTION:		Pt3MediumValue()
 *
 *	PURPOSE:		Calculates the medium value of Pt3
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		void
 *
 *	COMMENTS:      
 *
 *******************************************************************************/

void Pt3MediumValue(ModelParsFault *ModPFaultP, double *Pt3MedValP, int SensNum, FaultDetect *TrustSensP, struct SensedPars *SensorsP, double Pt3Model,  int MinTrustedSens)
{
    int Trusted = 0;
    int NumTrusted = 0;
    int UseModVal = 0;
    double SensorAux[5] = {0,0,0,0,0};

    /* Computes the values of Pt3 sensors */
    SensorAux[0] = SensorsP->Pt3[0];

    /* Verifies if Pt3 0 thermocouple is to be trusted */
    if(TrustSensP->DetFaults.Pt3_0_Fault)
    {
        Trusted = 1;
        NumTrusted = NumTrusted + 1;
    }

    /* If the number of trusted sensors is below minimum, the model value of Pt3 must beused
    to replace the measurements of the untrusted sensors */
    if(NumTrusted < MinTrustedSens)
    {
        UseModVal = 1;
    }

    /* Initiates ModelPars.Pt3 with 0 */
    ModPFaultP->ModelPars.Pt3 = 0;
    /* If the number of trusted sensors is zero, ModelPars.Pt3 is set to 1 indicating that
    all Pt3 sensors present hard fault */
    if(NumTrusted < 1)
    {
        ModPFaultP->ModelPars.Pt3 = 1;
    }

    /* Calculates the medium value of Pt3 */
    //MedValue(Trusted, &SensorAux, SensNum, Pt3MedValP, Pt3Model, UseModVal);
    MedValue(Trusted, SensorAux, SensNum, Pt3MedValP, Pt3Model, UseModVal);
}

/*******************************************************************************
 *
 *	FUNCTION:		Ts2MediumValue()
 *
 *	PURPOSE:		Calculates the medium value of Ts2
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		void
 *
 *	COMMENTS:      
 *
 *******************************************************************************/

void Tt4MediumValue(ModelParsFault *ModPFaultP, double *Tt4MedValP, int SensNum, FaultDetect *TrustSensP, struct SensedPars *SensorsP, double Tt4Model,  int MinTrustedSens)
{
    int Trusted = 0;
    int NumTrusted = 0;
    int UseModVal = 0;
    double SensorAux[5] = {0,0,0,0,0};

    /* Computes the values of Tt4 sensors */
    SensorAux[0] = SensorsP->Tt4[0];
    SensorAux[1] = SensorsP->Tt4[1];
    SensorAux[2] = SensorsP->Tt4[2];

    /* Verifies if Tt4 0 thermocouple is to be trusted */
    if(TrustSensP->DetFaults.Tt4_0_Fault)
    {
        Trusted = 1;
        NumTrusted = NumTrusted + 1;
    }

    /* Verifies if Tt4 1 thermocouple is to be trusted */
    if(TrustSensP->DetFaults.Tt4_1_Fault)
    {
        Trusted = 2 + Trusted;
        NumTrusted = NumTrusted + 1;
    }

    /* Verifies if Tt4 2 thermocouple is to be trusted */
    if(TrustSensP->DetFaults.Tt4_2_Fault)
    {
        Trusted = 4 + Trusted;
        NumTrusted = NumTrusted + 1;
    }

    /* If the number of trusted sensors is below minimum, the model value of Tt4 must beused
    to replace the measurements of the untrusted sensors */
    if(NumTrusted < MinTrustedSens)
    {
        UseModVal = 1;
    }

    /* Initiates ModelPars.Tt4 with 0 */
    ModPFaultP->ModelPars.Tt4 = 0;
    /* If the number of trusted sensors is zero, ModelPars.Tt4 is set to 1 indicating that
    all Tt4 sensors present hard fault */
    if(NumTrusted < 1)
    {
        ModPFaultP->ModelPars.Tt4 = 1;
    }

    /* Calculates the medium value of Tt4 */
    //MedValue(Trusted, &SensorAux, SensNum, Tt4MedValP, Tt4Model, UseModVal);
    MedValue(Trusted, SensorAux, SensNum, Tt4MedValP, Tt4Model, UseModVal);
}

/*******************************************************************************
 *
 *	FUNCTION:		RPMMediumValue()
 *
 *	PURPOSE:		Calculates the medium value of RPM
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		void
 *
 *	COMMENTS:      
 *
 *******************************************************************************/

void RPMMediumValue(ModelParsFault *ModPFaultP, double *RPMMedValP, int SensNum, FaultDetect *TrustSensP, struct SensedPars *SensorsP, double RPMModel,  int MinTrustedSens)
{
    int Trusted = 0;
    int NumTrusted = 0;
    int UseModVal = 0;
    double SensorAux[5] = {0,0,0,0,0};

    /* Computes the values of RPM sensors */
    SensorAux[0] = SensorsP->RPM[0];
    SensorAux[1] = SensorsP->RPM[1];

    /* Verifies if RPM 0 thermocouple is to be trusted */
    if(TrustSensP->DetFaults.RPM_0_Fault)
    {
        Trusted = 1;
        NumTrusted = NumTrusted + 1;
    }

    /* Verifies if RPM 1 thermocouple is to be trusted */
    if(TrustSensP->DetFaults.RPM_1_Fault)
    {
        Trusted = 2 + Trusted;
        NumTrusted = NumTrusted + 1;
    }

    /* If the number of trusted sensors is below minimum, the model value of RPM must beused
    to replace the measurements of the untrusted sensors */
    if(NumTrusted < MinTrustedSens)
    {
        UseModVal = 1;
    }

    /* Initiates ModelPars.RPM with 0 */
    ModPFaultP->ModelPars.RPM = 0;
    /* If the number of trusted sensors is zero, ModelPars.RPM is set to 1 indicating that
    all RPM sensors present hard fault */
    if(NumTrusted < 1)
    {
        ModPFaultP->ModelPars.RPM = 1;
    }

    /* Calculates the medium value of RPM */
    //MedValue(Trusted, &SensorAux, SensNum, RPMMedValP, RPMModel, UseModVal);
    MedValue(Trusted, SensorAux, SensNum, RPMMedValP, RPMModel, UseModVal);
}

// /*******************************************************************************
//  *
//  *	FUNCTION:		VarMediumValue()
//  *
//  *	PURPOSE:		Calculates the medium value of Ts2
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		
//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:      
//  *
//  *******************************************************************************/

// void VarMediumValue(int VarPos, ModelParsFault *ModPFaultP, double *MedValP, int SensNum, uint64_t TrustSens, double *SensorsP, double ModelVal,  int MinTrustedSens)
// {
//     int i;
//     int TruncBits = 0;
//     int TrustBit = 1;
//     int UseModVal = 0;
//     int Trusted = TrustSens; 
//     double SensorAux[5] = {0,0,0,0,0};

//     /* Loop for reading sensor values and preparing the truncating variable */
//     for(i = 0; i < SensNum; i++)
//     {
//         /* Updates current sensor value */
//         SensorAux[i] = *(SensorsP + i);
//         /* Updates variable used for truncating the bits representing the trusted sensors */
//         TruncBits = TruncBits << 1;
//         TruncBits = TruncBits + 1;
//     }

//     /* Corrects the value of Trusted for correct analysis */
//     Trusted = Trusted & TruncBits;


//     /* If the number of trusted sensors is below minimum, the model value of Ts2 must beused
//     to replace the measurements of the untrusted sensors */
//     if(Trusted < MinTrustedSens)
//     {
//         UseModVal = 1;
//     }

//     // /*Sets to 1 the bit of TrustBit corresponding to the current variable's position at ModParsBits*/
//     TrustBit = TrustBit << VarPos;

//     /* If the number of trusted sensors is zero, it is indicated at the current variable's position
//     at ModParsBits */
//     if(Trusted < 1)
//     {    
//         /* Wirte 1 at the position corresponding to the current modeled vairable */
//         ModPFaultP->ModParsBits = ModPFaultP->ModParsBits | TrustBit;
//     }
//     else
//     {
//         /* Wirte 0 at the position corresponding to the current modeled vairable */
//         ModPFaultP->ModParsBits = ModPFaultP->ModParsBits & (~TrustBit);
//     }

//     /* Calculates the medium value of Ts2 */
//     MedValue(Trusted, &SensorAux, SensNum, MedValP, ModelVal, UseModVal);
// };

/*******************************************************************************
 *
 *	FUNCTION:		FaultDetection()
 *
 *	PURPOSE:		Used for detecting sensor faults
 *                   
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Ki, Kp, Kb, Ts, Ik1, ek, ek1, ebk1, *PIOutP
 *
 *	RETURNS:		PIOutP
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void FaultDetection(double Value, double Threshold, int *CounterP, int MaxValue, uint64_t *FaultStatusP, uint64_t *FaultWarningP, int NumShifts)
{

    //int i;

	/* Variable to be shifted */
	//uint64_t Bit = 1 << NumShifts;
    uint64_t Bit = 1;

    /* Shifts using a for loop for avoiding undesired result */
    for (int i = 1; i <= NumShifts; i++)
    {
        /* Shifts a sigle position */
        Bit = Bit << 1;
    }

    /* Declares the bit to bit "not" Bit */
	uint64_t NotBit = ~Bit;
    
    /* Warning variables */
	uint64_t AuxWarning = *FaultWarningP;
	uint64_t AuxStatus = *FaultStatusP;

	/* Compares the residuals and adds 1 to the counter if ResComp >= Resmain
	 Subtracts from the counter otherwise */
	if (Threshold <= Value)
	{
		*CounterP = *CounterP + 1;
		AuxWarning = AuxWarning | Bit;
		*FaultWarningP = AuxWarning;

		/* The value of the counter must not exceed MaxValue */
		if (*CounterP >= MaxValue)
		{
			*CounterP = MaxValue;
			AuxStatus = AuxStatus | Bit;
			*FaultStatusP = AuxStatus;

		}
	}
	else
	{

		*CounterP = *CounterP - 1;
		AuxWarning = AuxWarning & NotBit;
		*FaultWarningP = AuxWarning;

		/* The value of the counter must not be smaller than 0 */
		if (*CounterP <= 0)
		{
			*CounterP = 0;
			AuxStatus = AuxStatus & NotBit;
			*FaultStatusP = AuxStatus;

		}
	}

}

/*******************************************************************************
 *
 *	FUNCTION:		BitIsTrue()
 *
 *	PURPOSE:		Used for reading the value of a single bit
 *                   
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		void
 *
 *	COMMENTS:      
 *
 *******************************************************************************/

void BitIsTrue(int NumShifts, uint64_t AllBits, int *BitTrue)
{
    /* Variable to be shifted */
    uint64_t Bit = 1;

    /* Shifts using a for loop for avoiding undesired result */
    for (int i = 1; i <= NumShifts; i++)
    {
        /* Shifts a sigle position */
        Bit = Bit << 1;
    }

    /* BitIsOne is initialized with 1 */
    *BitTrue = 1;

    /* If the result of NotBit & AllBits is zero, this means that the analyzed bit is zero */
    if ((Bit & AllBits) == 0)
    {
        *BitTrue = 0;
    }
}

/*******************************************************************************
 *
 *	FUNCTION:		HardFault()
 *
 *	PURPOSE:		Used for detecting sensors bias faults
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Ki, Kp, Kb, Ts, Ik1, ek, ek1, ebk1, *PIOutP
 *
 *	RETURNS:		PIOutP
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void HardFault(double Value, double Threshold, int *CounterP, int MaxValue, FaultDetect *FaultStatusP, FaultDetect *FaultWarningP, int NumShifts)
{

	/* Variables needed for calling fault detection function */
	uint64_t FaultWarning = FaultWarningP->FaultBits;
	uint64_t FaultStatus = FaultStatusP->FaultBits;

	/* Performs fault detectoin - if Value >= Threshold, the fault is detected */
	FaultDetection(Value, Threshold, CounterP, MaxValue, &FaultStatus, &FaultWarning, NumShifts);

	/* Updates variables */
	FaultWarningP->FaultBits = FaultWarning;
	FaultStatusP->FaultBits = FaultStatus;

}

// /*******************************************************************************
//  *
//  *	FUNCTION:		PIControl()
//  *
//  *	PURPOSE:		Calculates control signal and integral term with back
//  *                   calculation protection
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		Ki, Kp, Kb, Ts, Ik1, ek, ek1, ebk1, *PIOutP
//  *
//  *	RETURNS:		PIOutP
//  *
//  *	COMMENTS:       Rules for variable name: type_varname or type_VN
//  *
//  *******************************************************************************/

// //struct PIOutput *PIControl(double Ki, double Kp, double Kb, double Ts, double Ik1, double ek, double ek1, double ebk1, struct PIOutput *PIOutP)
// void ResidualCompare(double ResMain, double ResComp, int *CounterP, int MaxValue, EngineFaults *FaultStatusP, EngineFaults *FaultWarningP,  int NumShifts)
// {
    
//     /* If Resmain >= ResComp, the normal regime model residual is higher than the fault model residual  */
//     uint64_t FaultWarning = FaultWarningP->FaultBits;
//     uint64_t FaultStatus = FaultStatusP->FaultBits;    
    
//     /* Performs fault detectoin - if ResMain >= ResComp, the fault is detected */
//     FaultDetection(ResMain, ResComp, CounterP, MaxValue, &FaultStatus, &FaultWarning, NumShifts);
    
//     /* Updates variables */
//     FaultWarningP->FaultBits = FaultWarning;
//     FaultStatusP->FaultBits = FaultStatus;
    
    
// if(*CounterP > 0 & *CounterP <=3)
// {
// printf("\nCounterP = %d",*CounterP);
// printf("\nWarningBits = %d",FaultWarningP->FaultBits);
// printf("\nStatusBits = %d",FaultStatusP->FaultBits);
// }
        
// };

/*******************************************************************************
 *
 *	FUNCTION:		SensResCompare()
 *
 *	PURPOSE:		Calculates control signal and integral term with back
 *                   calculation protection
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void SensResCompare(double ResMain, double ResComp, int *CounterP, int MaxValue, SensorFaults *FaultStatusP, SensorFaults *FaultWarningP,  int NumShifts)
{
    
    /* If Resmain >= ResComp, the normal regime model residual is higher than the fault model residual  */
    uint64_t FaultWarning = FaultWarningP->FaultBits;
    uint64_t FaultStatus = FaultStatusP->FaultBits;    
    
    /* Performs fault detectoin - if ResMain >= ResComp, the fault is detected */
    FaultDetection(ResMain, ResComp, CounterP, MaxValue, &FaultStatus, &FaultWarning, NumShifts);
    
    /* Updates variables */
    FaultWarningP->FaultBits = FaultWarning;
    FaultStatusP->FaultBits = FaultStatus;
    
        
}

/*******************************************************************************
 *
 *	FUNCTION:		SysResCompare()
 *
 *	PURPOSE:		Calculates control signal and integral term with back
 *                   calculation protection
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void SysResCompare(double ResMain, double ResComp, int *CounterP, int MaxValue, SystemFaults *FaultStatusP, SystemFaults *FaultWarningP,  int NumShifts)
{
    
    /* If Resmain >= ResComp, the normal regime model residual is higher than the fault model residual  */
    uint64_t FaultWarning = FaultWarningP->FaultBits;
    uint64_t FaultStatus = FaultStatusP->FaultBits;    
    
    /* Performs fault detectoin - if ResMain >= ResComp, the fault is detected */
    FaultDetection(ResMain, ResComp, CounterP, MaxValue, &FaultStatus, &FaultWarning, NumShifts);
    
    /* Updates variables */
    FaultWarningP->FaultBits = FaultWarning;
    FaultStatusP->FaultBits = FaultStatus;
            
}

// /*******************************************************************************
//  *
//  *	FUNCTION:		FaultIdent()
//  *
//  *	PURPOSE:		If the residual obtained from the normal funcioning model
//  *                  is larger then the residual obtained form the fault model,
//  *                  comparison between the fault model residual and its threshold
//  *                  is performed
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		
//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:       
//  *
//  *******************************************************************************/

// void FaultIdent(double ResModel, double Threshold, double ResComp, int *CounterP, int MaxValue, EngineFaults *FaultStatusP, EngineFaults *FaultWarningP,  int NumShifts)
// {
// // printf("\n\nResModel = %f; ",ResModel);
// // printf("ResComp = %f",ResComp);
//     /* If ResModel > ResMain, there is a residual compare between ResMain and ResComp*/
// //     if(ResModel > ResComp)
// //printf("\nThreshold = %f; ResComp = %f",Threshold,ResComp);
//     if((ResModel > ResComp) | ((*CounterP)>0))
//     {   
// // printf("\nResModel > ResComp!!");
//         ResidualCompare(Threshold, ResComp, CounterP, MaxValue, FaultStatusP, FaultWarningP, NumShifts);
//     }
        
// };

/*******************************************************************************
 *
 *	FUNCTION:		SensFaultIdent()
 *
 *	PURPOSE:		Used for identifying sensor faults
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Ki, Kp, Kb, Ts, Ik1, ek, ek1, ebk1, *PIOutP
 *
 *	RETURNS:		PIOutP
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void SensFaultIdent(double ResModel, double Threshold, double ResComp, int *CounterP, int MaxValue, SensorFaults *FaultStatusP, SensorFaults *FaultWarningP,  int NumShifts)
{
    /* If ResModel > ResComp, there is a residual compare between Threshold and ResComp*/
    if((ResModel > ResComp) | ((*CounterP)>0))
    {
        SensResCompare(Threshold, ResComp, CounterP, MaxValue, FaultStatusP, FaultWarningP, NumShifts);
    }
          
}

/*******************************************************************************
 *
 *	FUNCTION:		SysFaultIdent()
 *
 *	PURPOSE:		Used for identifying system faults
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Ki, Kp, Kb, Ts, Ik1, ek, ek1, ebk1, *PIOutP
 *
 *	RETURNS:		PIOutP
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void SysFaultIdent(double ResModel, double Threshold, double ResComp, int *CounterP, int MaxValue, SystemFaults *FaultStatusP, SystemFaults *FaultWarningP,  int NumShifts)
{
    /* If ResModel > ResComp, there is a residual compare between Threshold and ResComp*/
    if((ResModel > ResComp) | ((*CounterP)>0))
    {
        SysResCompare(Threshold, ResComp, CounterP, MaxValue, FaultStatusP, FaultWarningP, NumShifts);
    }
             
}

/*******************************************************************************
 *
 *	FUNCTION:		HardTrust()
 *
 *	PURPOSE:		Verifies which sensors has had any kind of hard fault - high bias
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, FaultDetect *FaultSHardP, FaultDetect *FaultWHardP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:      
 *
 *******************************************************************************/

void HardTrust(FaultDetect *TrustSensP, FaultDetect *FaultSHardP, FaultDetect *FaultWHardP)
{

    /* Internal auxiliary struct for using single bit variable */
    struct{
        uint64_t Bit :1;
        uint64_t Reserved: 63;
    }Aux;

    /*=========*/
    /*STATION 2*/
    /*=========*/

    /*--------------*/
    /* Ts2 0 SENSOR */
    /*--------------*/

    /* Guarantees that hard fault (high bias) has not occurred */
    Aux.Bit = (~FaultSHardP->DetFaults.Ts2_0_Fault);
    Aux.Bit = Aux.Bit & (~FaultWHardP->DetFaults.Ts2_0_Fault);

    /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.Ts2_0_Fault = Aux.Bit;

    /*--------------*/
    /* Ts2 1 SENSOR */
    /*--------------*/

    /* Guarantees that hard fault (high bias) has not occurred */
    Aux.Bit = (~FaultSHardP->DetFaults.Ts2_1_Fault);
    Aux.Bit = Aux.Bit & (~FaultWHardP->DetFaults.Ts2_1_Fault);

   /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.Ts2_1_Fault = Aux.Bit;


    /*=========*/
    /*STATION 3*/
    /*=========*/

    /*-------------*/
    /* Pt3 SENSOR  */
    /*-------------*/

    /* Guarantees that hard fault (high bias) has not occurred */
    Aux.Bit = (~FaultSHardP->DetFaults.Pt3_0_Fault);
    Aux.Bit = Aux.Bit & (~FaultWHardP->DetFaults.Pt3_0_Fault);

    /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.Pt3_0_Fault = Aux.Bit;

    /*=========*/
    /*STATION 4*/
    /*=========*/

    /*--------------*/
    /* Tt4 0 SENSOR */
    /*--------------*/

    /* Guarantees that hard fault (high bias) has not occurred */
    Aux.Bit = (~FaultSHardP->DetFaults.Tt4_0_Fault);
    Aux.Bit = Aux.Bit & (~FaultWHardP->DetFaults.Tt4_0_Fault);

    /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.Tt4_0_Fault = Aux.Bit;

    /*--------------*/
    /* Tt4 1 SENSOR */
    /*--------------*/

    /* Guarantees that hard fault (high bias) has not occurred */
    Aux.Bit = (~FaultSHardP->DetFaults.Tt4_1_Fault);
    Aux.Bit = Aux.Bit & (~FaultWHardP->DetFaults.Tt4_1_Fault);

   /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.Tt4_1_Fault = Aux.Bit;

    /*--------------*/
    /* Tt4 2 SENSOR */
    /*--------------*/

    /* Guarantees that hard fault (high bias) has not occurred */
    Aux.Bit = (~FaultSHardP->DetFaults.Tt4_2_Fault);
    Aux.Bit = Aux.Bit & (~FaultWHardP->DetFaults.Tt4_2_Fault);

   /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.Tt4_2_Fault = Aux.Bit;

    /*=======*/
    /* SHAFT */
    /*=======*/
    
    /*--------------*/
    /* RPM 0 SENSOR */
    /*--------------*/

    /* Guarantees that hard fault (high bias) has not occurred */
    Aux.Bit = (~FaultSHardP->DetFaults.RPM_0_Fault);
    Aux.Bit = Aux.Bit & (~FaultWHardP->DetFaults.RPM_0_Fault);

   /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.RPM_0_Fault = Aux.Bit;    

    /*--------------*/
    /* RPM 1 SENSOR */
    /*--------------*/

    /* Guarantees that hard fault (high bias) has not occurred */
    Aux.Bit = (~FaultSHardP->DetFaults.RPM_1_Fault);
    Aux.Bit = Aux.Bit & (~FaultWHardP->DetFaults.RPM_1_Fault);

    /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.RPM_1_Fault = Aux.Bit;

}

/*******************************************************************************
 *
 *	FUNCTION:		SensorTrust()
 *
 *	PURPOSE:		Verifies which sensors has had any kind of known sensor fault
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void SensorTrust(FaultDetect *TrustSensP, SensorFaults *FaultSSensP, SensorFaults *FaultWSensP)
{

    /* Internal auxiliary struct for using single bit variable */
    struct{
        uint64_t Bit :1;
        uint64_t Reserved: 63;
    }Aux;

    /*=========*/
    /*STATION 2*/
    /*=========*/

    /*--------------*/
    /* Ts2 0 SENSOR */
    /*--------------*/

    /* Guarantees that the sensor is not open-circuited*/
    Aux.Bit = (~FaultSSensP->SensFaults.Ts2_0_Open);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Ts2_0_Open);
    /* Guarantees that the sensor is not in SCV*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.Ts2_0_SCV);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Ts2_0_SCV);
    /* Guarantees that the sensor is not in SCG*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.Ts2_0_SCG);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Ts2_0_SCG);

    /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.Ts2_0_Fault = Aux.Bit;

    /*--------------*/
    /* Ts2 1 SENSOR */
    /*--------------*/

    /* Guarantees that the sensor is not open-circuited*/
    Aux.Bit = (~FaultSSensP->SensFaults.Ts2_1_Open);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Ts2_1_Open);
    /* Guarantees that the sensor is not in SCV*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.Ts2_1_SCV);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Ts2_1_SCV);
    /* Guarantees that the sensor is not in SCG*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.Ts2_1_SCG);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Ts2_1_SCG);

   /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.Ts2_1_Fault = Aux.Bit;


    /*=========*/
    /*STATION 3*/
    /*=========*/

    /*-------------*/
    /* Pt3 SENSOR  */
    /*-------------*/

    /* Guarantees that the sensor is not open-circuited*/
    Aux.Bit = (~FaultSSensP->SensFaults.Pt3_0_Open);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Pt3_0_Open);
    /* Guarantees that the sensor is not short-circuited*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.Pt3_0_Short);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Pt3_0_Short);

    /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.Pt3_0_Fault = Aux.Bit;

    /*=========*/
    /*STATION 4*/
    /*=========*/

    /*--------------*/
    /* Tt4 0 SENSOR */
    /*--------------*/

    /* Guarantees that the sensor is not open-circuited*/
    Aux.Bit = (~FaultSSensP->SensFaults.Tt4_0_Open);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Tt4_0_Open);
    /* Guarantees that the sensor is not in SCV*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.Tt4_0_SCV);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Tt4_0_SCV);
    /* Guarantees that the sensor is not in SCG*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.Tt4_0_SCG);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Tt4_0_SCG);

    /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.Tt4_0_Fault = Aux.Bit;

    /*--------------*/
    /* Tt4 1 SENSOR */
    /*--------------*/

    /* Guarantees that the sensor is not open-circuited*/
    Aux.Bit = (~FaultSSensP->SensFaults.Tt4_1_Open);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Tt4_1_Open);
    /* Guarantees that the sensor is not in SCV*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.Tt4_1_SCV);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Tt4_1_SCV);
    /* Guarantees that the sensor is not in SCG*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.Tt4_1_SCG);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Tt4_1_SCG);

   /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.Tt4_1_Fault = Aux.Bit;

    /*--------------*/
    /* Tt4 2 SENSOR */
    /*--------------*/

    /* Guarantees that the sensor is not open-circuited*/
    Aux.Bit = (~FaultSSensP->SensFaults.Tt4_2_Open);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Tt4_2_Open);
    /* Guarantees that the sensor is not in SCV*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.Tt4_2_SCV);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Tt4_2_SCV);
    /* Guarantees that the sensor is not in SCG*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.Tt4_2_SCG);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Tt4_2_SCG);

   /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.Tt4_2_Fault = Aux.Bit;

    /*=======*/
    /* SHAFT */
    /*=======*/
    
    /*--------------*/
    /* RPM 0 SENSOR */
    /*--------------*/

    /* Guarantees that the sensor is not open-circuited*/
    Aux.Bit = (~FaultSSensP->SensFaults.RPM_0_Open);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.RPM_0_Open);
    /* Guarantees that the sensor is not short-circuited*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.RPM_0_Short);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.RPM_0_Short);
    // /* Guarantees that the sensor is not losing 1 pulse*/
    // Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.RPM_0_PLoss1);
    // Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.RPM_0_PLoss1);
    // /* Guarantees that the sensor is not losing 2 pulses*/
    // Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.RPM_0_PLoss2);
    // Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.RPM_0_PLoss2);
    // /* Guarantees that the sensor is not losing 3 pulses*/
    // Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.RPM_0_PLoss3);
    // Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.RPM_0_PLoss3);

   /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.RPM_0_Fault = Aux.Bit;    

    /*--------------*/
    /* RPM 1 SENSOR */
    /*--------------*/

    /* Guarantees that the sensor is not open-circuited*/
    Aux.Bit = (~FaultSSensP->SensFaults.RPM_1_Open);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.RPM_1_Open);
    /* Guarantees that the sensor is not short-circuited*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.RPM_1_Short);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.RPM_1_Short);
    // /* Guarantees that the sensor is not losing 1 pulse*/
    // Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.RPM_1_PLoss1);
    // Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.RPM_1_PLoss1);
    // /* Guarantees that the sensor is not losing 2 pulses*/
    // Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.RPM_1_PLoss2);
    // Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.RPM_1_PLoss2);
    // /* Guarantees that the sensor is not losing 3 pulses*/
    // Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.RPM_1_PLoss3);
    // Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.RPM_1_PLoss3);

    /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.RPM_1_Fault = Aux.Bit;

    /*====================*/
    /* LUBRICATION SYSTEM */
    /*====================*/

    /*--------------*/
    /* POil SENSOR  */
    /*--------------*/

    /* Guarantees that the sensor is not open-circuited*/
    Aux.Bit = (~FaultSSensP->SensFaults.POil_0_Open);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.POil_0_Open);
    /* Guarantees that the sensor is not short-circuited*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.POil_0_Short);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.POil_0_Short);

    /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.POil_0_Fault = Aux.Bit;

    /*----------------*/
    /* TBear 0 SENSOR */
    /*----------------*/

    /* Guarantees that the sensor is not open-circuited*/
    Aux.Bit = (~FaultSSensP->SensFaults.TB_0_Open);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.TB_0_Open);
    /* NOTE: Currently, only Open-Circuited sensor is considered for bearings TC */

    /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.TB_0_Fault = Aux.Bit;

    /*----------------*/
    /* TBear 1 SENSOR */
    /*----------------*/

    /* Guarantees that the sensor is not open-circuited*/
    Aux.Bit = (~FaultSSensP->SensFaults.TB_1_Open);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.TB_1_Open);
    /* NOTE: Currently, only Open-Circuited sensor is considered for bearings TC */

    /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.TB_1_Fault = Aux.Bit;

    /*----------------*/
    /* TBear 2 SENSOR */
    /*----------------*/

    /* Guarantees that the sensor is not open-circuited*/
    Aux.Bit = (~FaultSSensP->SensFaults.TB_2_Open);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.TB_2_Open);
    /* NOTE: Currently, only Open-Circuited sensor is considered for bearings TC */

    /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.TB_2_Fault = Aux.Bit;

    /*=============*/
    /* FUEL SYSTEM */
    /*=============*/

    /*---------------*/
    /* PFuel SENSOR  */
    /*---------------*/

    /* Guarantees that the sensor is not open-circuited*/
    Aux.Bit = (~FaultSSensP->SensFaults.PFuel_0_Open);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.PFuel_0_Open);
    /* Guarantees that the sensor is not short-circuited*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.PFuel_0_Short);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.PFuel_0_Short);

    /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.PFuel_0_Fault = Aux.Bit;

    /*===================*/
    /* MECHANICAL SYSTEM */
    /*===================*/

    /*-------------------*/
    /* VIBRATION SENSOR  */
    /*-------------------*/

    /* Guarantees that the sensor is not open-circuited*/
    Aux.Bit = (~FaultSSensP->SensFaults.Vib_0_Open);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Vib_0_Open);
    /* Guarantees that the sensor is not short-circuited*/
    Aux.Bit = Aux.Bit & (~FaultSSensP->SensFaults.Vib_0_Short);
    Aux.Bit = Aux.Bit & (~FaultWSensP->SensFaults.Vib_0_Short);

    /* If Aux.Bit == 0, a sensor fault has been detected
    and the sensor is not to be trusted for system fault detection */
    TrustSensP->DetFaults.Vib_0_Fault = Aux.Bit;

}

/*******************************************************************************
 *
 *	FUNCTION:		BlowOut()
 *
 *	PURPOSE:		Verifies if engine blow out has occured
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void BlowOut(FaultDetect *TrustSensP, SystemFaults *FaultSSysP, EngineFaults *FaultsStatusP)
{    
    
    /* Internal auxiliary struct for using single bit variable */
    struct{
        uint64_t Bit :1;
        uint64_t Reserved: 63;
    }Aux;

    /* Internal variables used for fault detection */
    int Station3 = 0;
    int Station4 = 0;
    int Shaft = 0;

    /*=============================================*/
    /* IDENTIFICATION OF FUEL LACK AT EACH STATION */
    /*=============================================*/

    /*-----------*/
    /* STATION 3 */
    /*-----------*/

    /* Pt3 0 SENSOR */

    /* Auxiliary bit is used to identify if the current sensor can be trusted
    and if fuel lack is identifyed */
    Aux.Bit = FaultSSysP->SysFaults.Pt3_0_BlowOut;
    Aux.Bit = Aux.Bit & (TrustSensP->DetFaults.Pt3_0_Fault);
    if(Aux.Bit)
    {
        Station3++;
    }

    /*-----------*/
    /* STATION 4 */
    /*-----------*/

    /* Tt4 0 SENSOR */

    /* Auxiliary bit is used to identify if the current sensor can be trusted
    and if fuel lack is identifyed */
    Aux.Bit = FaultSSysP->SysFaults.Tt4_0_BlowOut;
    Aux.Bit = Aux.Bit & (TrustSensP->DetFaults.Tt4_0_Fault);
    if(Aux.Bit)
    {
        Station4++;
    }

    /* Tt4 1 SENSOR */

    /* Auxiliary bit is used to identify if the current sensor can be trusted
    and if fuel lack is identifyed */
    Aux.Bit = FaultSSysP->SysFaults.Tt4_1_BlowOut;
    Aux.Bit = Aux.Bit & (TrustSensP->DetFaults.Tt4_1_Fault);
    if(Aux.Bit)
    {
        Station4++;
    }

    /* Tt4 2 SENSOR */

    /* Auxiliary bit is used to identify if the current sensor can be trusted
    and if fuel lack is identifyed */
    Aux.Bit = FaultSSysP->SysFaults.Tt4_2_BlowOut;
    Aux.Bit = Aux.Bit & (TrustSensP->DetFaults.Tt4_2_Fault);
    if(Aux.Bit)
    {
        Station4++;
    }

    /*-------*/
    /* SHAFT */
    /*-------*/

    /* RPM 0 SENSOR */

    /* Auxiliary bit is used to identify if the current sensor can be trusted
    and if fuel lack is identifyed */
    Aux.Bit = FaultSSysP->SysFaults.RPM_0_BlowOut;
    Aux.Bit = Aux.Bit & (TrustSensP->DetFaults.RPM_0_Fault);
    if(Aux.Bit)
    {
        Shaft++;
    }

    /* RPM 1 SENSOR */

    /* Auxiliary bit is used to identify if the current sensor can be trusted
    and if fuel lack is identifyed */
    Aux.Bit = FaultSSysP->SysFaults.RPM_1_BlowOut;
    Aux.Bit = Aux.Bit & (TrustSensP->DetFaults.RPM_1_Fault);
    if(Aux.Bit)
    {
        Shaft++;
    }

    /*============================*/
    /* IDENTIFICATION OF FUEL LACK*/
    /*============================*/

    /* VERIFIES IF THE FUEL LACK HAS BEEN IDEINTIFIED AT EVERY STATION */
 
    /* The auxiliary bit is used for checking if fuel lack has been identified at every section */
    Aux.Bit = 0;
    Aux.Bit = Aux.Bit | ((Station3 > 0) & (Station4 > 0)); 
    Aux.Bit = Aux.Bit | ((Station3 > 0) & (Shaft > 0));
    Aux.Bit = Aux.Bit | ((Station4 > 0) & (Shaft > 0));


    /* Indicates the mechanical lock fault */
    FaultsStatusP->Faults.BlowOut = Aux.Bit;

}

/*******************************************************************************
 *
 *	FUNCTION:		MeckLockTJ1200()
 *
 *	PURPOSE:		Verifies if mechanical lock has occured
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void MecLock(FaultDetect *TrustSensP, SystemFaults *FaultSSysP, EngineFaults *FaultsStatusP)
{    
    
    /* Internal auxiliary struct for using single bit variable */
    struct{
        uint64_t Bit :1;
        uint64_t Reserved: 63;
    }Aux;

    /* Internal variables used for fault detection */
    int Station3 = 0;
    int Station4 = 0;
    int Shaft = 0;

    /*=============================================*/
    /* IDENTIFICATION OF FUEL LACK AT EACH STATION */
    /*=============================================*/  

    /*-----------*/
    /* STATION 3 */
    /*-----------*/

    /* Pt3 0 SENSOR */

    /* Auxiliary bit is used to identify if the current sensor can be trusted
    and if fuel lack is identifyed */
    Aux.Bit = FaultSSysP->SysFaults.Pt3_0_MecLock;
    Aux.Bit = Aux.Bit & (TrustSensP->DetFaults.Pt3_0_Fault);
    if(Aux.Bit)
    {
        Station3++;
    }

    /*-----------*/
    /* STATION 4 */
    /*-----------*/

    /* Tt4 0 SENSOR */

    /* Auxiliary bit is used to identify if the current sensor can be trusted
    and if fuel lack is identifyed */
    Aux.Bit = FaultSSysP->SysFaults.Tt4_0_MecLock;
    Aux.Bit = Aux.Bit & (TrustSensP->DetFaults.Tt4_0_Fault);
    if(Aux.Bit)
    {
        Station4++;
    }

    /* Tt4 1 SENSOR */

    /* Auxiliary bit is used to identify if the current sensor can be trusted
    and if fuel lack is identifyed */
    Aux.Bit = FaultSSysP->SysFaults.Tt4_1_MecLock;
    Aux.Bit = Aux.Bit & (TrustSensP->DetFaults.Tt4_1_Fault);
    if(Aux.Bit)
    {
        Station4++;
    }

    /* Tt4 2 SENSOR */

    /* Auxiliary bit is used to identify if the current sensor can be trusted
    and if fuel lack is identifyed */
    Aux.Bit = FaultSSysP->SysFaults.Tt4_2_MecLock;
    Aux.Bit = Aux.Bit & (TrustSensP->DetFaults.Tt4_2_Fault);
    if(Aux.Bit)
    {
        Station4++;
    }

    /*-------*/
    /* SHAFT */
    /*-------*/

    /* RPM 0 SENSOR */

    /* Auxiliary bit is used to identify if the current sensor can be trusted
    and if fuel lack is identifyed */
    Aux.Bit = FaultSSysP->SysFaults.RPM_0_MecLock;
    //Aux.Bit = Aux.Bit & (TrustSensP->DetFaults.RPM_0_Fault);
    if(Aux.Bit)
    {
        Shaft++;
    }

    /* RPM 1 SENSOR */

    /* Auxiliary bit is used to identify if the current sensor can be trusted
    and if fuel lack is identifyed */
    Aux.Bit = FaultSSysP->SysFaults.RPM_1_MecLock;
    if(Aux.Bit)
    {
        Shaft++;
    }

    /*============================*/
    /* IDENTIFICATION OF FUEL LACK*/
    /*============================*/

    /* VERIFIES IF THE FUEL LACK HAS BEEN IDEINTIFIED AT EVERY STATION */
 
    /* The auxiliary bit is used for checking if fuel lack has been identified at every section */
    Aux.Bit = 1;
    Aux.Bit = Aux.Bit & (Station3 > 0);
    Aux.Bit = Aux.Bit & (Station4 > 0);
    Aux.Bit = Aux.Bit & (Shaft > 0);

    /* Indicates the mechanical lock fault */
    FaultsStatusP->Faults.Mec_Lock = Aux.Bit;

}

/*******************************************************************************
 *
 *	FUNCTION:		OverTemp()
 *
 *	PURPOSE:		Verifies if overtemp has occured
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void OverTemp(struct ControllerConstants *ContConstP, FaultDetect *TrustSensP, SystemFaults *FaultSSysP, struct SensedPars *SensorsP, EngineFaults *FaultStatusP)
{
    /* Internal variables */
    int CounterOT = 0;
    int CounterNOT = 0;
    double SensVecOT[3] = {0,0,0};
    double SensVecNOT[3] = {0,0,0};
    int MatchVec[3] = {0,0,0};
    double MaxError = ContConstP->TCThreshold;
    // double MaxError = TJ1200_TCTHRESHOLD;
    //int MatchElem = 0;
   
    /* If Tt4_0 sensor's value can be trusted, it is stored in either SensVecOT, if overtemp is detected, or in 
    or SensVecNOT, if overtemp is not detected. Also, the corresponding counter is increased */
    if (TrustSensP->DetFaults.Tt4_0_Fault)
    {
        if (FaultSSysP->SysFaults.Tt4_0_High)
        {
            CounterOT++;
            SensVecOT[CounterOT - 1] = SensorsP->Tt4[0];
        }
        else
        {
            CounterNOT++;
            SensVecNOT[CounterNOT - 1] = SensorsP->Tt4[0];
        }
    }
    /* If Tt4_1 sensor's value can be trusted, it is stored in either SensVecOT, if overtemp is detected, or in 
    or SensVecNOT, if overtemp is not detected. Also, the corresponding counter is increased */
    if (TrustSensP->DetFaults.Tt4_1_Fault)
    {
        if (FaultSSysP->SysFaults.Tt4_1_High)
        {
            CounterOT++;
            SensVecOT[CounterOT - 1] = SensorsP->Tt4[1];
        }
        else
        {
            CounterNOT++;
            SensVecNOT[CounterNOT - 1] = SensorsP->Tt4[1];
        }
    }
    /* If Tt4_2 sensor's value can be trusted, it is stored in either SensVecOT, if overtemp is detected, or in 
    or SensVecNOT, if overtemp is not detected. Also, the corresponding counter is increased */
    if (TrustSensP->DetFaults.Tt4_2_Fault)
    {
        if (FaultSSysP->SysFaults.Tt4_2_High)
        {
            CounterOT++;
            SensVecOT[CounterOT - 1] = SensorsP->Tt4[2];
        }
        else
        {
            CounterNOT++;
            SensVecNOT[CounterNOT - 1] = SensorsP->Tt4[2];
        }
    }
    /* Initiates the value of flag indicating overtemp with 0 */
    FaultStatusP->Faults.OverTemp = 0;

    /* If most of the sensors do not indicate overtemp, sernsor match is verifyed  */
    if (CounterNOT > CounterOT && CounterOT > 0)
    {
//        MatchSens(&SensVecNOT, &MatchVec, CounterNOT, MaxError);
        MatchSens(SensVecNOT, MatchVec, CounterNOT, MaxError);

        /* If MatchVec is smaller than CounterNOT, the sensors indicating low temperature
        are biased and cannot be trusted. Therefore, overtemp is to be accused */
        for (int i = 0; i < CounterNOT; i++)
        {
            /* code */
            int MatchElem = *(MatchVec + i);
            
            /* If sensors not measuring overtemp do not match, they are not to be trusted  */
            if (MatchElem < (CounterNOT - 1))
            {
                FaultStatusP->Faults.OverTemp = 1;
            }
            
        }
            
    }

    /* If most sensors indicate overtemp, it is computed or there is no match on the sensors */
    if (CounterOT >= CounterNOT && CounterOT > 0)
    {
         FaultStatusP->Faults.OverTemp = 1;
        
    }  
    
}

/*******************************************************************************
 *
 *	FUNCTION:		OverSpeed()
 *
 *	PURPOSE:		Verifies if overspeed has occured
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void OverSpeed(FaultDetect *TrustSensP, SystemFaults *FaultSSysP, struct SensedPars *SensorsP, EngineFaults *FaultStatusP)
{

    /* Internal variables */
    int CounterOS = 0;
    int CounterNOS = 0;
    double SensVecOS[2] = {0,0};
    double SensVecNOS[2] = {0,0};



    /* If RPM_0 sensor's value can be trusted, it is stored in either SensVecOT, if overtemp is detected, or in 
    or SensVecNOT, if overtemp is not detected. Also, the corresponding counter is increased */
    if (TrustSensP->DetFaults.RPM_0_Fault)
    {
        if (FaultSSysP->SysFaults.RPM_0_High)
        {
            CounterOS++;
            SensVecOS[CounterOS - 1] = SensorsP->RPM[0];
        }
        else
        {
            CounterNOS++;
            SensVecNOS[CounterNOS - 1] = SensorsP->RPM[0];
        }
    }
    /* If RPM_1 sensor's value can be trusted, it is stored in either SensVecOT, if overtemp is detected, or in 
    or SensVecNOT, if overtemp is not detected. Also, the corresponding counter is increased */
    if (TrustSensP->DetFaults.RPM_1_Fault)
    {
        if (FaultSSysP->SysFaults.RPM_1_High)
        {
            CounterOS++;
            SensVecOS[CounterOS - 1] = SensorsP->RPM[1];
        }
        else
        {
            CounterNOS++;
            SensVecNOS[CounterNOS - 1] = SensorsP->RPM[1];
        }
    }

    /* Initiates the value of flag indicating overtemp with 0 */
    FaultStatusP->Faults.OverSpeed = 0;

    /* Verifies if any trusted sensor has indicated overspeed */
    if (CounterOS >= CounterNOS && CounterOS > 0)
    {
        /* Computes overspeed if one trusted sensor indicates it */
        FaultStatusP->Faults.OverSpeed = 1;
    }
    
    
}

/*******************************************************************************
 *
 *	FUNCTION:		CAN1MissComm()
 *
 *	PURPOSE:		Verifies if misscommunication in CAN 1 network has occurred
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       
 *
 *******************************************************************************/

void CAN1MissComm(EngineFaults *FaultStatusP, EngineStatus *EngStatusP, int *OnOffCommP, int EmmergencyCommand, int ShutDownCommand)
{
    /* Engine status must be at STARTING for the CAN 1 fault to be verified */
    if (FaultStatusP->Faults.CAN_1_Fault)
    {
        if (*OnOffCommP != EmmergencyCommand)
        {
            /* If engine is not yet in idle, emergency must be activated */
            if (EngStatusP->EngineStatus <= 8)
            {
                *OnOffCommP = EmmergencyCommand;
            }
            /* If engine is already in IDLE, Shut Donw must be activated */
            else
            {
                *OnOffCommP = ShutDownCommand;
            }
        }
    }
}

/*******************************************************************************
 *
 *	FUNCTION:		POilHighUpdt()
 *
 *	PURPOSE:		Verifies if high oil pressure value has occured
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void POilHighUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP)
{
    /* Updates state of POil High falure */
    FaultStatusP->Faults.POil_High = FaultSysP->SysFaults.POil_0_High;
}

/*******************************************************************************
 *
 *	FUNCTION:		POilLowUpdt()
 *
 *	PURPOSE:		Verifies if low oil pressure value has occured
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void POilLowUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP)
{
    /* Updates state of POil Low failure */
    FaultStatusP->Faults.POil_Low = FaultSysP->SysFaults.POil_0_Low;
}

/*******************************************************************************
 *
 *	FUNCTION:		PFuelHighUpdt()
 *
 *	PURPOSE:		Verifies if high fuel pressure value has occured
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void PFuelHighUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP)
{
    /* Updates state of PFuel High failure */
    FaultStatusP->Faults.PFuel_High = FaultSysP->SysFaults.PFuel_0_High;
}

/*******************************************************************************
 *
 *	FUNCTION:		PFuelLowUpdt()
 *
 *	PURPOSE:		Verifies if low fuel pressure value has occured
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void PFuelLowUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP)
{
    /* Updates state of PFuel Low failure */
    FaultStatusP->Faults.PFuel_Low = FaultSysP->SysFaults.PFuel_0_Low;
}

/*******************************************************************************
 *
 *	FUNCTION:		VibHighUpdt()
 *
 *	PURPOSE:		Verifies if high vibration has occured
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void VibHighUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP)
{
    /* Updates state of Vibrtation High failure */
    FaultStatusP->Faults.VibrationHigh = FaultSysP->SysFaults.Vib_0_High;
}

/*******************************************************************************
 *
 *	FUNCTION:		TB0HighUpdt()
 *
 *	PURPOSE:		Verifies if high temperature on bearing 0 has occurred
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void TB0HighUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP)
{
    /* Updates state of Vibrtation High failure */
    FaultStatusP->Faults.TBear_0_High = FaultSysP->SysFaults.TB_0_High;
}

/*******************************************************************************
 *
 *	FUNCTION:		TB1HighUpdt()
 *
 *	PURPOSE:		Verifies if high temperature on bearing 1 has occurred
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void TB1HighUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP)
{
    /* Updates state of Vibrtation High failure */
    FaultStatusP->Faults.TBear_1_High = FaultSysP->SysFaults.TB_1_High;
}

/*******************************************************************************
 *
 *	FUNCTION:		TB2HighUpdt()
 *
 *	PURPOSE:		Verifies if high temperature on bearing 2 has occurred
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void TB2HighUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP)
{
    /* Updates state of Vibrtation High failure */
    FaultStatusP->Faults.TBear_2_High = FaultSysP->SysFaults.TB_2_High;
}

/*******************************************************************************
 *
 *	FUNCTION:		SensAnalisysAuthorize()
 *
 *	PURPOSE:		Authorizes fault analysis according to established conditions
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       
 *
 *******************************************************************************/

void SensAnalisysAuthorize(SensorFaults *FaultSensAuthP, struct ControlStart *ContStartP, struct ControllerInput *ContInputP, EngineStatus *EngStatusP, int StartAnalysis)
{

    /* STATUS TABLE */

    /*
          1 - Initialize
          2 - Windmilling
          4 - ReadyToStart
          8 - Starting
         16 - Idle
         32 - Regime
         64 - ShutOff
        128 - Emergency
        256 - Fail
        512 - Degraded
    */

    /* INITIALIZATION */

    /* Declares auxiliar union */
    EngineStatus EngStatusAux;

    /* Initially, authorizes analysis of all sensor faults */
    FaultSensAuthP->FaultBits = 0xFFFFFFFFFFFFFFFF;

    /* ANALYSIS CONDITIONS */

    /* If the engine status is not at least in windmillin (status == 2), sensor analysis should not occur */
    EngStatusAux.EngineStatus = 0x0;
    EngStatusAux.EngStatusBist.Windmilling = 1;
    //if (EngStatusP->EngineStatus < 2)
    if (EngStatusP->EngineStatus < EngStatusAux.EngineStatus)
    {
        FaultSensAuthP->FaultBits = 0x0;
    }

//    /* Allows oil pressure analysis */
//    /* The analysis is only allowed after the engine is at READY TO START state
//    allowing the oil pressure to increase before analysis */
//    EngStatusAux.EngineStatus = 0x0;
//    EngStatusAux.EngStatusBist.ReadyToStart = 1;
//    //if (EngStatusP->EngineStatus < 4)
//    if (EngStatusP->EngineStatus < EngStatusAux.EngineStatus)
//    {
//        FaultSensAuthP->SensFaults.POil_0_Short = 0;
//        FaultSensAuthP->SensFaults.POil_0_Open = 0;
//    }

//    /* Allows fuel pressure analysis */
//    /*The analysis is only allowed after the first engine pulse is finished,
//    allowing fuel pressure to increase before analysis*/
//    EngStatusAux.EngineStatus = 0x0;
//    EngStatusAux.EngStatusBist.ReadyToStart = 1;
//    //if (ContStartP->status <= 4)
//    if (ContStartP->status <= EngStatusAux.EngineStatus)
//    {
//        FaultSensAuthP->SensFaults.PFuel_0_Short = 0;
//        FaultSensAuthP->SensFaults.PFuel_0_Open = 0;
//    }
    
    /* If StartAnalysis equals 1, analysis must be authorized regardless of above conditions */
    if (StartAnalysis == 1)
    {
        FaultSensAuthP->FaultBits = 0xFFFFFFFFFFFFFFFF;
    }

    /* If Shut Off has been activated and is currently at shut off ramp phase, sensor fault verification
    must be masked in order for FAIL state not to be activated */
    if (ContInputP->StatusSD >=2)
    {
        /* Disables sensor fault verification */
        FaultSensAuthP->FaultBits = 0x0;
    }

/* Disables all sensor fault analysis */
FaultSensAuthP->FaultBits = 0;


printf("statusBosster=%d StartAnalysis=%d EngStatus=%d\n\n",ContInputP->statusBooster,StartAnalysis, (int)EngStatusP->EngineStatus);
printf("Authorized sensor fault analysis: \n");
/* Testando condições para Pt3 */
if((ContInputP->statusBooster == 1) & (StartAnalysis == 1))
{
    FaultSensAuthP->SensFaults.Pt3_0_Open = 1;
    FaultSensAuthP->SensFaults.Pt3_0_Short = 1;
printf("    Pt3_0 ");
}


///* Allows oil pressure analysis */
///* The analysis is only allowed after the engine is at READY TO START state
//allowing the oil pressure to increase before analysis */
//EngStatusAux.EngineStatus = 0x0;
//EngStatusAux.EngStatusBist.ReadyToStart = 1;
////if (EngStatusP->EngineStatus < 4)
//if (EngStatusP->EngineStatus >= EngStatusAux.EngineStatus)
//{
//    FaultSensAuthP->SensFaults.POil_0_Short = 1;
//    FaultSensAuthP->SensFaults.POil_0_Open = 1;
//printf(" POil")
//}


/* Allows fuel pressure analysis */
/*The analysis is only allowed after the first engine pulse is finished,
allowing fuel pressure to increase before analysis*/
EngStatusAux.EngineStatus = 0x0;
EngStatusAux.EngStatusBist.ReadyToStart = 1;
//if (ContStartP->status <= 4)
if (ContStartP->status > (int)EngStatusAux.EngineStatus)
{
    FaultSensAuthP->SensFaults.PFuel_0_Short = 1;
    FaultSensAuthP->SensFaults.PFuel_0_Open = 1;
printf(" PFuel_0");
}

/* Allows vibration analysis */
/*The analysis is only allowed after Windmilling state is reached*/
EngStatusAux.EngineStatus = 0x0;
EngStatusAux.EngStatusBist.Windmilling = 1;
//if (ContStartP->status <= 4)
if (ContStartP->status >= (int)EngStatusAux.EngineStatus)
{
    FaultSensAuthP->SensFaults.Vib_0_Short = 1;
    FaultSensAuthP->SensFaults.Vib_0_Open = 1;
printf(" Vib_0");
}


/* THERMOCOUPLES */

/* Ts2_0 */

if(StartAnalysis == 1)
{
    FaultSensAuthP->SensFaults.Ts2_0_Open = 1;
    //FaultSensAuthP->SensFaults.Ts2_0_SCG = 1;
    //FaultSensAuthP->SensFaults.Ts2_0_SCV = 1;
printf("    Ts2_0 ");
}

/* Ts2_1 */

if(StartAnalysis == 1)
{
    FaultSensAuthP->SensFaults.Ts2_1_Open = 1;
    //FaultSensAuthP->SensFaults.Ts2_1_SCG = 1;
    //FaultSensAuthP->SensFaults.Ts2_1_SCV = 1;
printf("    Ts2_1 ");
}

/* Tt4_0 */

if(StartAnalysis == 1)
{
    FaultSensAuthP->SensFaults.Tt4_0_Open = 1;
    //FaultSensAuthP->SensFaults.Tt4_0_SCG = 1;
    //FaultSensAuthP->SensFaults.Tt4_0_SCV = 1;
printf("    Tt4_0 ");
}

/* Tt4_1 */

if(StartAnalysis == 1)
{
    FaultSensAuthP->SensFaults.Tt4_1_Open = 1;
    //FaultSensAuthP->SensFaults.Tt4_1_SCG = 1;
    //FaultSensAuthP->SensFaults.Tt4_1_SCV = 1;
printf("    Tt4_1 ");
}

/* Tt4_2 */

if(StartAnalysis == 1)
{
    FaultSensAuthP->SensFaults.Tt4_2_Open = 1;
    //FaultSensAuthP->SensFaults.Tt4_2_SCG = 1;
    //FaultSensAuthP->SensFaults.Tt4_2_SCV = 1;
printf("    Tt4_2 ");
}

/* ROTATION SPEED */

/* RPM_0 */

EngStatusAux.EngineStatus = 0x0;
EngStatusAux.EngStatusBist.Windmilling = 1;

if((StartAnalysis == 1) | (EngStatusP->EngineStatus >= EngStatusAux.EngineStatus))
{
    FaultSensAuthP->SensFaults.RPM_0_Open = 1;
    //FaultSensAuthP->SensFaults.RPM_0_Short = 1;
    FaultSensAuthP->SensFaults.RPM_0_PLoss1 = 1;
    FaultSensAuthP->SensFaults.RPM_0_PLoss2 = 1;
printf("    RPM_0 ");
}

/* RPM_1 */

if((StartAnalysis == 1) | (EngStatusP->EngineStatus >= EngStatusAux.EngineStatus))
{
    FaultSensAuthP->SensFaults.RPM_1_Open = 1;
    //FaultSensAuthP->SensFaults.RPM_1_Short = 1;
    FaultSensAuthP->SensFaults.RPM_1_PLoss1 = 1;
    FaultSensAuthP->SensFaults.RPM_1_PLoss2 = 1;
printf("    RPM_1 ");
}

printf("\n\n");


    
}


/*******************************************************************************
 *
 *	FUNCTION:		SysAnalisysAuthorize()
 *
 *	PURPOSE:		Authorizes fault analysis according to established conditions
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       
 *
 *******************************************************************************/

void SysAnalisysAuthorize(SystemFaults *FaultSysAuthP, struct ControlStart *ContStartP, struct ControllerInput *ContInputP, EngineStatus *EngStatusP, int StartAnalysis)
{

    /* STATUS TABLE */

    /*
          1 - Initialize
          2 - Windmilling
          4 - ReadyToStart
          8 - Starting
         16 - Idle
         32 - Regime
         64 - ShutOff
        128 - Emergency
        256 - Fail
        512 - Degraded
    */

    /* Initially disables all system faults */
    FaultSysAuthP->FaultBits = 0;

    /* ANALYSIS CONDITIONS */

    /* Allows oil pressure analysis */
    /* The analysis is only allowed after the engine is at READY TO START state
    allowing the oil pressure to increase before analysis */
    if (EngStatusP->EngineStatus >= 16)
    {
        FaultSysAuthP->SysFaults.POil_0_High = 1;
        FaultSysAuthP->SysFaults.POil_0_Low = 1;
    }

    /* Allows fuel pressure analysis */
    /*The analysis is only allowed after the first engine pulse is finished,
    allowing fuel pressure to increase before analysis*/
    if (ContStartP->status > 4)
    {
        FaultSysAuthP->SysFaults.PFuel_0_High = 1;
        FaultSysAuthP->SysFaults.PFuel_0_Low = 1;
    }

    /* Always authorize CAN network analysis */
    FaultSysAuthP->SysFaults.CAN_0_Fault = 1;
    FaultSysAuthP->SysFaults.CAN_1_Fault = 1;
   
    /* If StartAnalysis equals 1, analysis must be authorized regardless of above conditions */
    if (StartAnalysis == 1)
    {
        FaultSysAuthP->FaultBits = 0xFFFFFFFFFFFFFFFF;
    }

    /* If the system is at or beyond Idle state, ignition failure must not be analyzed */
    if (EngStatusP->EngineStatus >= 16)
    {
        FaultSysAuthP->SysFaults.Ignition = 0;
    }
    else
    {
        FaultSysAuthP->SysFaults.Ignition = 1;
    }
    

    /* If Shut Off has been activated and is currently at shut off ramp phase, systems fault verification
    must be masked in order for FAIL state not to be activated */
    if (ContInputP->StatusSD >=2)
    {      
        /* Disables sensor fault verification */
        FaultSysAuthP->FaultBits = 0x0;
    }
    
    
}

/*******************************************************************************
 *
 *	FUNCTION:		BiasAnalisysAuthorize()
 *
 *	PURPOSE:		Authorizes fault analysis according to established conditions
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       
 *
 *******************************************************************************/

void BiasAnalisysAuthorize(FaultDetect *FaultHardAuthP, struct ControlStart *ContStartP, struct ControllerInput *ContInputP, EngineStatus *EngStatusP, int StartAnalysis)
{

    /* Initially, authorizes analysis of all sensor faults */
    FaultHardAuthP->FaultBits = 0xFFFFFFFFFFFFFFFF;

    /* ANALYSIS CONDITIONS */

    /* Hard (bias) faults are not allowed before StartAnalysis is 1 */
    FaultHardAuthP->FaultBits = 0x0;

    /* If StartAnalysis equals 1, analysis must be authorized regardless of above conditions */
    if (StartAnalysis == 1)
    {
        FaultHardAuthP->FaultBits = 0xFFFFFFFFFFFFFFFF;
    }

    /* If Shut Off has been activated and is currently at shut off ramp phase, bias verification
    must be masked in order for FAIL state not to be activated */
    if (ContInputP->StatusSD >=2)
    {      
        /* Disables sensor fault verification */
        FaultHardAuthP->FaultBits = 0x0;
    }
    
}

/*******************************************************************************
 *
 *	FUNCTION:		HardFaultUpdt()
 *
 *	PURPOSE:		Verifies if hard fault (high bias) has occured when authorization bit is active
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       
 *
 *******************************************************************************/

void HardFaultUpdt(EngineFaults *FaultStatusP, FaultDetect *FaultHardP, FaultDetect *FaultHardAuthP)
{
    
    FaultStatusP->Faults.Ts2_0_Bias = FaultHardP->DetFaults.Ts2_0_Fault & FaultHardAuthP->DetFaults.Ts2_0_Fault;
    FaultStatusP->Faults.Ts2_1_Bias = FaultHardP->DetFaults.Ts2_1_Fault & FaultHardAuthP->DetFaults.Ts2_1_Fault;    

    /* Pt3 sensor */
    FaultStatusP->Faults.Pt3_0_Bias = FaultHardP->DetFaults.Pt3_0_Fault & FaultHardAuthP->DetFaults.Pt3_0_Fault; 

    /* Tt4 thermocouples */
    FaultStatusP->Faults.Tt4_0_Bias = FaultHardP->DetFaults.Tt4_0_Fault & FaultHardAuthP->DetFaults.Tt4_0_Fault;
    FaultStatusP->Faults.Tt4_1_Bias = FaultHardP->DetFaults.Tt4_1_Fault & FaultHardAuthP->DetFaults.Tt4_1_Fault; 
    FaultStatusP->Faults.Tt4_2_Bias = FaultHardP->DetFaults.Tt4_2_Fault & FaultHardAuthP->DetFaults.Tt4_2_Fault;

    /* RPM thermocouples */
    FaultStatusP->Faults.RPM_0_Bias = FaultHardP->DetFaults.RPM_0_Fault & FaultHardAuthP->DetFaults.RPM_0_Fault;
    FaultStatusP->Faults.RPM_1_Bias = FaultHardP->DetFaults.RPM_1_Fault & FaultHardAuthP->DetFaults.RPM_1_Fault; 

    /* POil sensor */
    FaultStatusP->Faults.POil_0_Bias = FaultHardP->DetFaults.POil_0_Fault & FaultHardAuthP->DetFaults.POil_0_Fault; 

    /* PFuel sensor */
    FaultStatusP->Faults.PFuel_0_Bias = FaultHardP->DetFaults.PFuel_0_Fault & FaultHardAuthP->DetFaults.PFuel_0_Fault; 

    /* Vib sensor */
    FaultStatusP->Faults.Vib_0_Bias = FaultHardP->DetFaults.Vib_0_Fault & FaultHardAuthP->DetFaults.Vib_0_Fault; 

}

/*******************************************************************************
 *
 *	FUNCTION:		SensFaultUpdt()
 *
 *	PURPOSE:		Updates detected sensor faults when authorization bit is active
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void SensFaultUpdt(EngineFaults *FaultStatusP, SensorFaults *FaultSensP, SensorFaults *FaultSensAuthP)
{
    /* Ts2 0 thermocouple */
    FaultStatusP->Faults.Ts2_0_SCV = FaultSensP->SensFaults.Ts2_0_SCV & FaultSensAuthP->SensFaults.Ts2_0_SCV;
    FaultStatusP->Faults.Ts2_0_SCG = FaultSensP->SensFaults.Ts2_0_SCG & FaultSensAuthP->SensFaults.Ts2_0_SCG; 
    FaultStatusP->Faults.Ts2_0_Open = FaultSensP->SensFaults.Ts2_0_Open & FaultSensAuthP->SensFaults.Ts2_0_Open; 

    /* Ts2 1 thermocouple */
    FaultStatusP->Faults.Ts2_1_SCV = FaultSensP->SensFaults.Ts2_1_SCV & FaultSensAuthP->SensFaults.Ts2_1_SCV; 
    FaultStatusP->Faults.Ts2_1_SCG = FaultSensP->SensFaults.Ts2_1_SCG & FaultSensAuthP->SensFaults.Ts2_1_SCG; 
    FaultStatusP->Faults.Ts2_1_Open = FaultSensP->SensFaults.Ts2_1_Open & FaultSensAuthP->SensFaults.Ts2_1_Open; 

    /* Pt3 0 sensor */
    FaultStatusP->Faults.Pt3_0_Short = FaultSensP->SensFaults.Pt3_0_Short & FaultSensAuthP->SensFaults.Pt3_0_Short; 
    FaultStatusP->Faults.Pt3_0_Open = FaultSensP->SensFaults.Pt3_0_Open & FaultSensAuthP->SensFaults.Pt3_0_Open; 
    
    /* Tt4 0 thermocouple */
    FaultStatusP->Faults.Tt4_0_SCV = FaultSensP->SensFaults.Tt4_0_SCV & FaultSensAuthP->SensFaults.Tt4_0_SCV; 
    FaultStatusP->Faults.Tt4_0_SCG = FaultSensP->SensFaults.Tt4_0_SCG & FaultSensAuthP->SensFaults.Tt4_0_SCG; 
    FaultStatusP->Faults.Tt4_0_Open = FaultSensP->SensFaults.Tt4_0_Open & FaultSensAuthP->SensFaults.Tt4_0_Open; 

    /* Tt4 1 thermocouple */
    FaultStatusP->Faults.Tt4_1_SCV = FaultSensP->SensFaults.Tt4_1_SCV & FaultSensAuthP->SensFaults.Tt4_1_SCV; 
    FaultStatusP->Faults.Tt4_1_SCG = FaultSensP->SensFaults.Tt4_1_SCG & FaultSensAuthP->SensFaults.Tt4_1_SCG; 
    FaultStatusP->Faults.Tt4_1_Open = FaultSensP->SensFaults.Tt4_1_Open & FaultSensAuthP->SensFaults.Tt4_1_Open; 

    /* Tt4 2 thermocouple */
    FaultStatusP->Faults.Tt4_2_SCV = FaultSensP->SensFaults.Tt4_2_SCV & FaultSensAuthP->SensFaults.Tt4_2_SCV; 
    FaultStatusP->Faults.Tt4_2_SCG = FaultSensP->SensFaults.Tt4_2_SCG & FaultSensAuthP->SensFaults.Tt4_2_SCG; 
    FaultStatusP->Faults.Tt4_2_Open = FaultSensP->SensFaults.Tt4_2_Open & FaultSensAuthP->SensFaults.Tt4_2_Open; 

    /* RPM 0 thermocouple */
    FaultStatusP->Faults.RPM_0_Short = FaultSensP->SensFaults.RPM_0_Short & FaultSensAuthP->SensFaults.RPM_0_Short; 
    FaultStatusP->Faults.RPM_0_Open = FaultSensP->SensFaults.RPM_0_Open & FaultSensAuthP->SensFaults.RPM_0_Open; 
    FaultStatusP->Faults.RPM_0_1PLoss = FaultSensP->SensFaults.RPM_0_PLoss1 & FaultSensAuthP->SensFaults.RPM_0_PLoss1; 
    FaultStatusP->Faults.RPM_0_2PLoss = FaultSensP->SensFaults.RPM_0_PLoss2 & FaultSensAuthP->SensFaults.RPM_0_PLoss2; 

    /* RPM 1 thermocouple */
    FaultStatusP->Faults.RPM_1_Short = FaultSensP->SensFaults.RPM_1_Short & FaultSensAuthP->SensFaults.RPM_1_Short; 
    FaultStatusP->Faults.RPM_1_Open = FaultSensP->SensFaults.RPM_1_Open & FaultSensAuthP->SensFaults.RPM_1_Open; 
    FaultStatusP->Faults.RPM_1_1PLoss = FaultSensP->SensFaults.RPM_1_PLoss1 & FaultSensAuthP->SensFaults.RPM_1_PLoss1; 
    FaultStatusP->Faults.RPM_1_2PLoss = FaultSensP->SensFaults.RPM_1_PLoss2 & FaultSensAuthP->SensFaults.RPM_1_PLoss2; 

    /* POil 0 sensor */
    FaultStatusP->Faults.POil_0_Short = FaultSensP->SensFaults.POil_0_Short & FaultSensAuthP->SensFaults.POil_0_Short;
    FaultStatusP->Faults.POil_0_Open = FaultSensP->SensFaults.POil_0_Open & FaultSensAuthP->SensFaults.POil_0_Open;

    /* PFuel 0 sensor */
    FaultStatusP->Faults.PFuel_0_Short = FaultSensP->SensFaults.PFuel_0_Short & FaultSensAuthP->SensFaults.PFuel_0_Short;
    FaultStatusP->Faults.PFuel_0_Open = FaultSensP->SensFaults.PFuel_0_Open & FaultSensAuthP->SensFaults.PFuel_0_Open;

    /* Vib 0 sensor */
    FaultStatusP->Faults.Vib_0_Short = FaultSensP->SensFaults.Vib_0_Short & FaultSensAuthP->SensFaults.Vib_0_Short; 
    FaultStatusP->Faults.Vib_0_Open = FaultSensP->SensFaults.Vib_0_Open & FaultSensAuthP->SensFaults.Vib_0_Open;

    /* Bearings Thermocouples */
    FaultStatusP->Faults.TB_0_Open = FaultSensP->SensFaults.TB_0_Open & FaultSensAuthP->SensFaults.TB_0_Open;
    FaultStatusP->Faults.TB_1_Open = FaultSensP->SensFaults.TB_1_Open & FaultSensAuthP->SensFaults.TB_1_Open;
    FaultStatusP->Faults.TB_2_Open = FaultSensP->SensFaults.TB_2_Open & FaultSensAuthP->SensFaults.TB_2_Open;

}

/*******************************************************************************
 *
 *	FUNCTION:		SysFaultUpdt() - NOT BEING CURRENTLY USED
 *
 *	PURPOSE:		Updates system faults that have occurred
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *TrustSensP, SensorFaults *FaultSSensP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void SysFaultUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP, SystemFaults *FaultSysAuthP)
{

    /* LUBRICATION SYSTEM */

    /* POil High */
    FaultStatusP->Faults.POil_High = FaultSysP->SysFaults.POil_0_High & FaultSysAuthP->SysFaults.POil_0_High;
    /* POil Low */
    FaultStatusP->Faults.POil_Low = FaultSysP->SysFaults.POil_0_Low & FaultSysAuthP->SysFaults.POil_0_Low;

    /* FUEL SYSTEM */

    /* PFuel High */
    FaultStatusP->Faults.PFuel_High = FaultSysP->SysFaults.PFuel_0_High & FaultSysAuthP->SysFaults.PFuel_0_High;
    /* PFuel Low */
    FaultStatusP->Faults.PFuel_Low = FaultSysP->SysFaults.PFuel_0_Low & FaultSysAuthP->SysFaults.PFuel_0_Low;

    /* MECHANICAL */

    /* Vibration High */
    FaultStatusP->Faults.VibrationHigh = FaultSysP->SysFaults.Vib_0_High  & FaultSysAuthP->SysFaults.Vib_0_High; 

    /* BEARINGS */
    
    /* Bearing 0 high temperature */
    FaultStatusP->Faults.TBear_0_High = FaultSysP->SysFaults.TB_0_High  & FaultSysAuthP->SysFaults.TB_0_High;
    /* Bearing 1 high temperature */
    FaultStatusP->Faults.TBear_1_High = FaultSysP->SysFaults.TB_1_High  & FaultSysAuthP->SysFaults.TB_1_High;
    /* Bearing 2 high temperature */
    FaultStatusP->Faults.TBear_2_High = FaultSysP->SysFaults.TB_2_High  & FaultSysAuthP->SysFaults.TB_2_High;

    /* CAN NETWORK */

    /* CAN 0 communication fail */
    FaultStatusP->Faults.CAN_0_Fault = FaultSysP->SysFaults.CAN_0_Fault & FaultSysAuthP->SysFaults.CAN_0_Fault;
    /* CAN 1 communication fail */
    FaultStatusP->Faults.CAN_1_Fault = FaultSysP->SysFaults.CAN_1_Fault & FaultSysAuthP->SysFaults.CAN_1_Fault;

}

/*******************************************************************************
 *
 *	FUNCTION:		ResCalc() - NOT BEING CURRENTLY USED
 *
 *	PURPOSE:		Obtains the smaller value between two variables (double)
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		a, b
 *
 *	RETURNS:		Value
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void ResCalc(double *Ts0MtxP, struct ControllerConstants *ContConstP,
             double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
             struct EstimatedPars *ModelParsP, struct EstimatedPars *BlowOutParsP, struct SensedPars *SensorsP,
             struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
             struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
             struct AllResiduals *VibrationResP,
             SensorFaults *FaultSSensP, SensorFaults *FaultWSensP,
             SystemFaults *FaultSSysP, SystemFaults *FaultWSysP,
             FaultDetect *HardFStatusP, FaultDetect *HardFWarningP, struct InterpIndex3D *Index3DP)

{
     
    /* Used internal variables */
    double Ts2Std;
    double Ts2Model;
    InterpIndex3D Index3D;
    int i;
//    int NumShifts = 0;
    int NumShiftsSens = 0;
    int NumShiftsSys = 0;
    int NumShiftsHard = 0;
//    int FaultBias[10] = {0,0,0,0,0,0,0,0,0,0};
//    int AuxCount = 0;
//    int SensFaultsNum = 0;
    
    double Threshold = 0;
    
//    /* Auxiliar Residual Result */
//    double AuxRes = 0;
    
    /* Sensors Numbers */   
    int NumTs2Sens = ContConstP->NumTs2Sens;
    int NumPs3Sens = ContConstP->NumPs3Sens;
    int NumTt4Sens = ContConstP->NumTt4Sens;
    int NumRPMSens = ContConstP->NumRPMSens;
    int NumVibrationSens = ContConstP->NumVibrationSens;
    int NumPOilSens = ContConstP->NumPOilSens;
    int NumPFuelSens = ContConstP->NumPFuelSens;

    /* Engine matrix element numbers */
    int Fn_Elem = ContConstP->Fn_Elem;
    int Alt_Elem = ContConstP->Alt_Elem;

//    /* Time parameters - seconds */
//    double MaxInter_POilHigh = ContConstP->TimeHighPOil;
//    double MaxInter_POilLow = ContConstP->TimeLowPOil;
//    double MaxInter_PFuelHigh = ContConstP->TimeHighPFuel;
//    double MaxInter_PFuelLow = ContConstP->TimeLowPFuel;
//    double MaxInter_VibHigh = ContConstP->TimeHighVibration;
//    double MaxInter_Overspeed = ContConstP->TimeOverspeed;
//    double MaxInter_OverTemp = ContConstP->TimeOvertemp;

//    /* Time parameters adjustment from seconds to interaction number */
//    MaxInter_POilHigh = MaxInter_POilHigh / TICK / 0.001;
//    MaxInter_POilLow = MaxInter_POilLow / TICK / 0.001;
//    MaxInter_PFuelHigh = MaxInter_PFuelHigh / TICK / 0.001;
//    MaxInter_PFuelLow = MaxInter_PFuelLow / TICK / 0.001;
//    MaxInter_VibHigh = MaxInter_VibHigh / TICK / 0.001;
//    MaxInter_Overspeed = MaxInter_Overspeed / TICK / 0.001;
//    MaxInter_OverTemp = MaxInter_OverTemp / TICK / 0.001;

    /* Time parameters - seconds */
    int MaxInter_POilHigh = (int)ContConstP->TimeHighPOil / TICK / 0.001;
    int MaxInter_POilLow = (int)ContConstP->TimeLowPOil / TICK / 0.001;
    int MaxInter_PFuelHigh = (int)ContConstP->TimeHighPFuel / TICK / 0.001;
    int MaxInter_PFuelLow = (int)ContConstP->TimeLowPFuel / TICK / 0.001;
    int MaxInter_VibHigh = (int)ContConstP->TimeHighVibration / TICK / 0.001;
    int MaxInter_Overspeed = (int)ContConstP->TimeOverspeed / TICK / 0.001;
    int MaxInter_OverTemp = (int)ContConstP->TimeOvertemp / TICK / 0.001;


    /* Short-Open sensor values */
    double PFuelShort = ContConstP->PFuelShort;
//    double PSOpen = ContConstP->PSOpen;
    double PSOpenThresh = ContConstP->PSOpenThresh; 
    double PSShort = ContConstP->PSShort; 
    double PSShortThresh =  ContConstP->PSShortThresh;
//    double VibOpen = ContConstP->VibOpen;
//    double VibOpenThresh = ContConstP->VibOpenThresh;
    double VibShort = ContConstP->VibShort;
    double VibShortThresh = ContConstP->VibShortThresh;

    /* Thresholds */
    double TCThreshold = ContConstP->TCThreshold; 
    double Tt4ShaftLock = ContConstP->Tt4ShaftLock;
    double PSThreshold =  ContConstP->PSThreshold;
    double VibThreshold = ContConstP->VibThreshold;
    double RPMThreshold = ContConstP->RPMThreshold;

    /* Limit Values */
    double PFuelHigh = ContConstP->PFuelHigh; 
    double PFuelLow = ContConstP->PFuelLow;
    double POilHigh = ContConstP->POilHigh; 
    double POilLow = ContConstP->POilLow;
    double VibHigh = ContConstP->VibHigh;
    double Tt4Max = ContConstP->Tt4Max;
    double NMax = ContConstP->NMax;

    /* Maps the indexes correctly */
    Index3D.kA = 0;
    Index3D.kAH = 0;
    Index3D.fA = 0;
    Index3D.kMN = 0;
    Index3D.kMNH = 0;
    Index3D.fMN = 0;
    Index3D.kRPM = Index3DP->kA;
    Index3D.kRPMH = Index3DP->kAH;
    Index3D.fRPM = Index3DP->fA;
          
    /* Calculation of static temeprature for ISA + 0 conditions */
    Ts2Std = InterpValue(&Index3D, Ts0MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Fn_Elem, Alt_Elem);
    /* Calculation of static temperature for ISA + dT conditions */
    Ts2Model = Ts2Std + ModelParsP->dT;
    
    /*-----------*/
    /* STATION 2 */
    /*-----------*/

    /* Ts2 Thermocouples */
    for(i = 0; i < NumTs2Sens; i++)
    {
       
        /*-------------------------------*/
        /* CALCULATION OF MODEL RESIDUAL */
        /*-------------------------------*/
        
        /* Model residual */
        Ts2ResP->Model[i] = (SensorsP->Ts2[i] - Ts2Model) * (SensorsP->Ts2[i] - Ts2Model);
//printf("\nOld: Ts2ResP->Model[%d] = %f", i, Ts2ResP->Model[i]);
        /*----------------------*/
        /* HARD FAULT DETECTION */
        /*----------------------*/
        
        /* Hard fault detection */
        Threshold = (Ts2Model * TCThreshold) * (Ts2Model * TCThreshold);
        HardFault(Ts2ResP->Model[i], Threshold, &Ts2ResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP,  NumShiftsHard);
        /* Updates number of shifts for hard fault detection in next sensor */
        NumShiftsHard++;
        
        /*-------------------------*/
        /* SENSORS FAULT ISOLATION */
        /*-------------------------*/
        
        /* SCV */

        /* SCV residual */
        /* The threshold value is set to one, since it will be compared to 0 */
        Threshold = 1;
        SensFaultIdent(Ts2ResP->Model[i],Threshold, Ts2ResP->SCV[i], &Ts2ResP->SCVCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;
        
        /* SCG */
        
        /* SCG residual */ 
        Ts2ResP->SCG[i] = 0;
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;


        /* OPEN */

        /* Open-Circuit residual */
        /* The threshold value is set to one, since it will be compared to 0 */
        Threshold = 1;
        SensFaultIdent(Ts2ResP->Model[i],Threshold, Ts2ResP->Open[i], &Ts2ResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;
       
    }
    
    /*-------------------*/
    /* STATION 3 SENSORS */
    /*-------------------*/

    /* Pt3 Sensors */
    for(i = 0; i < NumPs3Sens; i++)
    {           
        /*-------------------------------*/
        /* CALCULATION OF MODEL RESIDUAL */
        /*-------------------------------*/
        
        /* Model residual - Must work in kPa instead of directly in Pa*/
        Pt3ResP->Model[i] = (SensorsP->Pt3[i] - ModelParsP->Pt3) * (SensorsP->Pt3[i] - ModelParsP->Pt3);
//printf("\nOld: Pt3ResP->Model[%d] = %f", i, Pt3ResP->Model[i]);
        /*----------------------*/
        /* HARD FAULT DETECTION */
        /*----------------------*/
        
        /* Calculation of threshold */
        Threshold = (ModelParsP->Pt3 * PSThreshold) * (ModelParsP->Pt3 * PSThreshold);
        /* Hard Faults detection algorithm */
        HardFault(Pt3ResP->Model[i], Threshold, &Pt3ResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP,  NumShiftsHard);
        /* Updates number of shifts for hard fault detection in next sensor */
        NumShiftsHard++;   
        
        /*-------------------------*/
        /* SENSORS FAULT ISOLATION */
        /*-------------------------*/
        
        /* SHORT CIRCUIT */

        /* Short-Circuit residual */
        Pt3ResP->Short[i] = (SensorsP->Pt3[i] - PSShort) * (SensorsP->Pt3[i] - PSShort);
        Threshold = PSShortThresh;
        Threshold = Threshold * Threshold;
        /* Fault identification subroutine */
	    SensFaultIdent(Pt3ResP->Model[i],Threshold, Pt3ResP->Short[i], &Pt3ResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;
        
        /* OPEN CIRCUIT */

        /* Open-Circuit residual */
        Pt3ResP->Open[i] = (SensorsP->Pt3[i]) * (SensorsP->Pt3[i]);       
        /* Open-Circuit threshold */
        Threshold = PSOpenThresh;
        Threshold = Threshold * Threshold;
        /* Fault identification subroutine */
	    SensFaultIdent(Pt3ResP->Model[i],Threshold, Pt3ResP->Open[i], &Pt3ResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;
        
        /*-----------------------------------*/
        /* IDENTIFICATION OF SYSTEM FAILURES */
        /*-----------------------------------*/
        
        /* ENGINE BLOW OUT */

        /* Blow Out residual */
        Pt3ResP->BlowOut[i] = (SensorsP->Pt3[i] - BlowOutParsP->Pt3) * (SensorsP->Pt3[i] - BlowOutParsP->Pt3);
        /* Compares the residuals of nominal model with fault model */
        SysResCompare(Pt3ResP->Model[i], Pt3ResP->BlowOut[i], &Pt3ResP->BlowOutCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

        /* SHAFT LOCK */

        /* Shaft-Lock residual */
        Pt3ResP->ShaftLock[i] = (SensorsP->Pt3[i] - ModelParsP->Pt2) * (SensorsP->Pt3[i] - ModelParsP->Pt2);
        /* Shaft-Lock threshold */
        Threshold = ModelParsP->Pt2 * PSThreshold;
        Threshold = Threshold * Threshold;
        /* Fault identification subroutine */
	    SysFaultIdent(Pt3ResP->Model[i],Threshold, Pt3ResP->ShaftLock[i], &Pt3ResP->ShaftLockCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);        
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

    }

    /*-------------------*/
    /* STATION 4 SENSORS */
    /*-------------------*/

    /* Tt4 Thermocouple*/
    for(i = 0; i < NumTt4Sens; i++)
    {    

        /*-------------------------------*/
        /* CALCULATION OF MODEL RESIDUAL */
        /*-------------------------------*/
        
        /* Model residual */
        Tt4ResP->Model[i] = (SensorsP->Tt4[i] - ModelParsP->Tt4) * (SensorsP->Tt4[i] - ModelParsP->Tt4);
//printf("\nOld: Tt4ResP->Model[%d] = %f", i, Tt4ResP->Model[i]);
        /*----------------------*/
        /* HARD FAULT DETECTION */
        /*----------------------*/
        
        /* Hard fault threshold */
        Threshold = (ModelParsP->Tt4 * TCThreshold) * (ModelParsP->Tt4 * TCThreshold);
        /* Hard fault detection */
        HardFault(Tt4ResP->Model[i], Threshold, &Tt4ResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP,  NumShiftsHard);
        NumShiftsHard++;        

        /*-------------------------*/
        /* SENSORS FAULT ISOLATION */
        /*-------------------------*/
        
        /* SCV */

        /* The threshold value is set to 1, since it will be compared do 0 */
        Threshold = 1;
        SensFaultIdent(Tt4ResP->Model[i],Threshold, Tt4ResP->SCV[i], &Tt4ResP->SCVCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* SCG */

        /* SCG residual */        
        Tt4ResP->SCG[i] = 0;
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* OPEN-CIRCUIT */

        /* The threshold value is set to 1, since it will be compared to 0 */
        Threshold = 1;
        SensFaultIdent(Tt4ResP->Model[i],Threshold, Tt4ResP->Open[i], &Tt4ResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /*-----------------------------------*/
        /* IDENTIFICATION OF SYSTEM FAILURES */
        /*-----------------------------------*/

        /* OVERTEMP */

        /* Residual for high fuel Pressure */
        Tt4ResP->High[i] = (SensorsP->Tt4[i] - Tt4Max) * (SensorsP->PFuel[i] - Tt4Max);
        /* High fuel pressure threshold */
        Threshold = Tt4Max;
        /* Fault identification subroutine */
        SysResCompare(SensorsP->Tt4[i], Threshold, &Tt4ResP->HighCount[i], MaxInter_OverTemp, FaultSSysP, FaultWSysP, NumShiftsSys);        
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

        /* BLOW OUT */

        /* Blow Out residual */
        Tt4ResP->BlowOut[i] = (SensorsP->Tt4[i] - BlowOutParsP->Tt4) * (SensorsP->Tt4[i] - BlowOutParsP->Tt4);  
        /* Residual comparison for detection of Blow Out by Tt4 */
        SysResCompare(Tt4ResP->Model[i], Tt4ResP->BlowOut[i], &Tt4ResP->BlowOutCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;  

        /* SHAFT LOCK */

        /* Shaft Lock residual */
        Tt4ResP->ShaftLock[i] = (SensorsP->Tt4[i] - Tt4ShaftLock) * (SensorsP->Tt4[i] - Tt4ShaftLock);
        Threshold = Tt4ShaftLock;
        Threshold = Threshold * TCThreshold;
        Threshold = Threshold * Threshold;
        /* Detection of Shaft Lock by Tt4 */
        SysFaultIdent(Tt4ResP->Model[i],Threshold, Tt4ResP->ShaftLock[i], &Tt4ResP->ShaftLockCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);        
         /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

    }

    /*-------*/
    /* SHAFT */
    /*-------*/

    /* RPM Sensors */
    for(i = 0; i < NumRPMSens; i++)
    {    

        /*-------------------------------*/
        /* CALCULATION OF MODEL RESIDUAL */
        /*-------------------------------*/
        
        /* Model residual */
        RPMResP->Model[i] = (SensorsP->RPM[i] - ModelParsP->RPM) * (SensorsP->RPM[i] - ModelParsP->RPM);
//printf("\nOld: RPMResP->Model[%d] = %f", i, RPMResP->Model[i]);
        /*----------------------*/
        /* HARD FAULT DETECTION */
        /*----------------------*/
        
        /* Hard fault threshold */
        Threshold = (ModelParsP->RPM * RPMThreshold) * (ModelParsP->RPM * RPMThreshold);
        /* Hard fault detection */
        HardFault(RPMResP->Model[i], Threshold, &RPMResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP,  NumShiftsHard);
        NumShiftsHard++;        

        /*------------------------*/
        /* SENSOR FAULT ISOLATION */
        /*------------------------*/
                
        /* SHORT-CIRCUIT */

        /* Short-Circuit residual */
        RPMResP->Short[i] = (SensorsP->RPM[i]) * (SensorsP->RPM[i]);
        /* Threshold is set to 1 since it will be compared to 0 */
        Threshold = 1;
        /* Detection of shrt-circuit at RPM sensor */
        SensFaultIdent(RPMResP->Model[i],Threshold, RPMResP->Short[i], &RPMResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);        
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* OPEN-CIRCUIT */

        /* Open-Circuit residual */
        RPMResP->Open[i] = (SensorsP->RPM[i]) * (SensorsP->RPM[i]);
        /* Threshold is set to 1 since it will be compared to 0 */
        Threshold = 1;
        /* Detection of Open-circuit in RPM sensor */
        SensFaultIdent(RPMResP->Model[i],Threshold, RPMResP->Open[i], &RPMResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);        
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* 1 PULSE LOSS */

        /* Loss of 1 pulse */
        RPMResP->PulseLoss1[i] = (SensorsP->RPM[i] - ModelParsP->RPM * 2 / 3) * (SensorsP->RPM[i] - ModelParsP->RPM * 2 / 3);
        /* Threshold value for 1 pulse loss */
        Threshold = ModelParsP->RPM * 2 / 3 * RPMThreshold;
        Threshold = Threshold * Threshold;
        /* Detection of 1 pulse loss by RPM sensor */
        SensFaultIdent(RPMResP->Model[i],Threshold, RPMResP->PulseLoss1[i], &RPMResP->PulseLoss1Count[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);        
         /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* 2 PULSES LOSS */

        /* Loss of 2 pulses */
        RPMResP->PulseLoss2[i] = (SensorsP->RPM[i] - ModelParsP->RPM * 1 / 3) * (SensorsP->RPM[i] - ModelParsP->RPM * 1 / 3);
        /* Threshold value for 2 pulses loss */
        Threshold = ModelParsP->RPM * 1 / 3 * RPMThreshold;
        Threshold = Threshold * Threshold;
        /* Detection of 2 pulses loss by RPM sensor */
        SensFaultIdent(RPMResP->Model[i],Threshold, RPMResP->PulseLoss2[i], &RPMResP->PulseLoss2Count[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);        
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;


        /*------------------------*/
        /* SYSTEM FAULT ISOLATION */
        /*------------------------*/
        
        /* OVERSPEED */

        /* Residual for high fuel Pressure */
        RPMResP->High[i] = (SensorsP->RPM[i] - NMax) * (SensorsP->RPM[i] - NMax);
        /* High fuel pressure threshold */
        Threshold = NMax;
        /* Fault identification subroutine */
        SysResCompare(SensorsP->RPM[i], Threshold, &RPMResP->HighCount[i], MaxInter_Overspeed, FaultSSysP, FaultWSysP, NumShiftsSys);        
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

        /* BLOW OUT */

        /* Blow Out residual */
        RPMResP->BlowOut[i] = (SensorsP->RPM[i] - BlowOutParsP->RPM) * (SensorsP->RPM[i] - BlowOutParsP->RPM);
        /* Detection of blow out by RPM sensor */
        SysResCompare(RPMResP->Model[i], RPMResP->BlowOut[i], &RPMResP->BlowOutCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

        /* SHAFT LOCK */

        /* Shaft Lock residual */
        RPMResP->ShaftLock[i] = (SensorsP->RPM[i]) * (SensorsP->RPM[i]);
        /* Threshold is set to 1 since it will be compared to 0 */
        Threshold = 1;
        /* Identification of shaft lock by RPM sensor */
        SysFaultIdent(RPMResP->Model[i],Threshold, RPMResP->ShaftLock[i], &RPMResP->ShaftLockCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);                
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

    }

    /*--------------------*/
    /* LUBRICATION SYSTEM */
    /*--------------------*/

    /* Oil Pressure sensors */
    for(i = 0; i < NumPOilSens; i++)
    {    
        
        /*-------------------------------*/
        /* CALCULATION OF MODEL RESIDUAL */
        /*-------------------------------*/
          
        /* Model residual */
        POilResP->Model[i] = (SensorsP->POil[i] - ModelParsP->POil) * (SensorsP->POil[i] - ModelParsP->POil);
//printf("\nOld: POilResP->Model[%d] = %f", i, POilResP->Model[i]);
        /*----------------------*/
        /* HARD FAULT DETECTION */
        /*----------------------*/
        
        /* Hard fault threshold */
        Threshold = (ModelParsP->POil * PSThreshold) * (ModelParsP->POil * PSThreshold);
        /* Hard fault detection */
        HardFault(POilResP->Model[i], Threshold, &POilResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP,  NumShiftsHard);
        NumShiftsHard++;  
        
        /*------------------------*/
        /* SENSOR FAULT ISOLATION */
        /*------------------------*/       
        
        /* SHORT-CIRCUIT */

        /* Short-Circuit residual */
        POilResP->Short[i] = (SensorsP->POil[i] - PSShort) * (SensorsP->POil[i] - PSShort);
        /* Short-Circuit threshold */
        Threshold = PSShortThresh;
        Threshold = Threshold * Threshold;
        /* Fault identification subroutine */
	    SensFaultIdent(POilResP->Model[i],Threshold, POilResP->Short[i], &POilResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* OPEN-CIRCUIT */

        /* Open-Circuit residual */
        POilResP->Open[i] = (SensorsP->POil[i]) * (SensorsP->POil[i]);
        /* Threshold is set to 1 since it will be compared to 0 */
        Threshold = 1;
        /* Fault identification subroutine */
	    SensFaultIdent(POilResP->Model[i],Threshold, POilResP->Open[i], &POilResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /*------------------------*/
        /* SYSTEM FAULT ISOLATION */
        /*------------------------*/
                
        /* HIGH OIL PRESSURE */

        /* Residual for High Oil Pressure */
        POilResP->High[i] = (SensorsP->POil[i] - POilHigh) * (SensorsP->POil[i] - POilHigh);
        /* Threshold for high oil pressure */
        Threshold = POilHigh;
        /* High oil pressure detection - uses its own time parameter instead of Model->MaxIter */
        SysResCompare(SensorsP->POil[i], Threshold, &POilResP->HighCount[i], MaxInter_POilHigh, FaultSSysP, FaultWSysP, NumShiftsSys);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

        /* LOW OIL PRESSURE */

        /* Residual for High Oil Pressure */
        POilResP->Low[i] = (SensorsP->POil[i] - POilLow) * (SensorsP->POil[i] - POilLow);
        /* Threshold for low oil pressure */
        Threshold = POilLow;
        /* Low oil pressure detection */
        SysResCompare(Threshold, SensorsP->POil[i], &POilResP->LowCount[i], MaxInter_POilLow, FaultSSysP, FaultWSysP, NumShiftsSys);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

    }

    /*-------------*/
    /* FUEL SYSTEM */
    /*-------------*/

    /* PFuel Sensor */
    for(i = 0; i < NumPFuelSens; i++)
    {    

        /*-------------------------------*/
        /* CALCULATION OF MODEL RESIDUAL */
        /*-------------------------------*/
        
        /* Model residual */
        PFuelResP->Model[i] = (SensorsP->PFuel[i] - ModelParsP->PFuel) * (SensorsP->PFuel[i] - ModelParsP->PFuel);
//printf("\nOld: PFuelResP->Model[%d] = %f", i, PFuelResP->Model[i]);
        /*----------------------*/
        /* HARD FAULT DETECTION */
        /*----------------------*/

        /* Hard fault threshold */
        Threshold = (ModelParsP->PFuel * PSThreshold) * (ModelParsP->PFuel * PSThreshold);
        /* Hard fault detection */
        HardFault(PFuelResP->Model[i], Threshold, &PFuelResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP,  NumShiftsHard);
        NumShiftsHard++;  

        /*------------------------*/
        /* SENSOR FAULT ISOLATION */
        /*------------------------*/
        
        /* SHORT-CIRCUIT */

        /* Short-Circuit residual */
        PFuelResP->Short[i] = (SensorsP->PFuel[i] - PFuelShort) * (SensorsP->PFuel[i] - PFuelShort);
        /* Short-Circuit threshold */
        Threshold = PSShortThresh;
        Threshold = Threshold * Threshold;
        /* Fault identification subroutine */
	    SensFaultIdent(PFuelResP->Model[i],Threshold, PFuelResP->Short[i], &PFuelResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* OPEN-CIRCUIT */

        /* Open-Circuit residual */
        PFuelResP->Open[i] = (SensorsP->PFuel[i]) * (SensorsP->PFuel[i]);
        /* Threshold is set to 1 since it will be compared to 0 */
        Threshold = 1;
        /* Fault identification subroutine */
	    SensFaultIdent(PFuelResP->Model[i],Threshold, PFuelResP->Open[i], &PFuelResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /*------------------------*/
        /* SYSTEM FAULT ISOLATION */
        /*------------------------*/

        /* HIGH FUEL PRESSURE */

        /* Residual for high fuel Pressure */
        PFuelResP->High[i] = (SensorsP->PFuel[i] - PFuelHigh) * (SensorsP->PFuel[i] - PFuelHigh);
        /* High fuel pressure threshold */
        Threshold = PFuelHigh;
        /* Fault identification subroutine */
        SysResCompare(SensorsP->PFuel[i], Threshold, &PFuelResP->HighCount[i], MaxInter_PFuelHigh, FaultSSysP, FaultWSysP, NumShiftsSys);        
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

        /* LOW FUEL PRESSURE */

        /* Residual for high fuel pressure */
        PFuelResP->Low[i] = (SensorsP->PFuel[i] - PFuelLow) * (SensorsP->PFuel[i] - PFuelLow);
        /* High fuel pressure threshold */
        Threshold = PFuelLow;
        /* System fault identification */
        SysResCompare(Threshold, SensorsP->PFuel[i], &PFuelResP->LowCount[i], MaxInter_PFuelLow, FaultSSysP, FaultWSysP, NumShiftsSys);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

    }

    /*-----------*/
    /* VIBRATION */
    /*-----------*/

    /* Vibration Sensor */
    for(i = 0; i < NumVibrationSens; i++)
    {    

        /*-------------------------------*/
        /* CALCULATION OF MODEL RESIDUAL */
        /*-------------------------------*/

        /* Model residual */
        VibrationResP->Model[i] = (SensorsP->Vibration[i] - ModelParsP->Vibration) * (SensorsP->Vibration[i] - ModelParsP->Vibration);      
//printf("\nOld: VibrationResP->Model[%d] = %f", i, VibrationResP->Model[i]);
        /*-----------------------*/
        /* HARD FAULTS DETECTION */
        /*-----------------------*/
        
        /* Hard fault threshold */
        Threshold = (ModelParsP->Vibration * VibThreshold) * (ModelParsP->Vibration * VibThreshold);
        /* Hard fault detection */
        HardFault(VibrationResP->Model[i], Threshold, &VibrationResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP,  NumShiftsHard);
        NumShiftsHard++;   
        
        /*------------------------*/
        /* SENSOR FAULT ISOLATION */
        /*------------------------*/
        
        /* SHORT-CIRCUIT */

        /* Short-Circuit residual */
        VibrationResP->Short[i] = (SensorsP->Vibration[i] - VibShort) * (SensorsP->Vibration[i] - VibShort);
        /* Short-Circuit threshold */
        Threshold = VibShortThresh;
        Threshold = Threshold * Threshold;
        /* Fault identification subroutine */
        SensFaultIdent(VibrationResP->Model[i],Threshold, VibrationResP->Short[i], &VibrationResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);                
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* OPEN-CIRCUIT */

        /* Open-Circuit residual */
        VibrationResP->Open[i] = (SensorsP->Vibration[i]) * (SensorsP->Vibration[i]);
        /* Threshold is set to 1 since it will be compared to 0 */
        Threshold = 1;
        /* Fault identification subroutine */
        SensFaultIdent(VibrationResP->Model[i],Threshold, VibrationResP->Open[i], &VibrationResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);                        
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /*------------------------*/
        /* SYSTEM FAULT ISOLATION */
        /*------------------------*/
        
        /* HIGH VIBRATION */

        /* High vibration residual */
        VibrationResP->High[i] = (SensorsP->Vibration[i] - VibHigh) * (SensorsP->Vibration[i] - VibHigh);
        /* High vibration threshold */
        Threshold = VibHigh;
        /* Fault detection subroutine */
        SysResCompare(SensorsP->Vibration[i], Threshold, &VibrationResP->HighCount[i], MaxInter_VibHigh, FaultSSysP, FaultWSysP, NumShiftsSys);        
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

    }

    /* Updates value of Ts2StdSL */
    ModelParsP->Ts2StdSL = (*Ts0MtxP);
    /* Updates value of Ts2 in model parameters with calculated value */
    ModelParsP->Ts2 = Ts2Model;
    /* Updates value of Ts2Std in model parameters */
    ModelParsP->Ts2Std = Ts2Std;
//printf("\nOld: Ts2 = %f, dT = %f, Ts2StdSL = %f, Ts2Std = %f",ModelParsP->Ts2, ModelParsP->dT, ModelParsP->Ts2StdSL, ModelParsP->Ts2Std);
}

/*******************************************************************************
 *
 *	FUNCTION:		Ts2ModelCalc()
 *
 *	PURPOSE:		Obtains the smaller value between two variables (double)
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		a, b
 *
 *	RETURNS:		Value
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void Ts2ModelCalc(double *Ts0MtxP, struct ControllerConstants *ContConstP,
             double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
             struct EstimatedPars *ModelParsP, struct InterpIndex3D *Index3DP)

{
    /* Used internal variables */
    double Ts2Std;
    double Ts2Model;
    InterpIndex3D Index3D;
//    int i;
     
    /* Engine matrix element numbers */
    int Fn_Elem = ContConstP->Fn_Elem;
    int Alt_Elem = ContConstP->Alt_Elem;

    /* Maps the indexes correctly */
    Index3D.kA = 0;
    Index3D.kAH = 0;
    Index3D.fA = 0;
    Index3D.kMN = 0;
    Index3D.kMNH = 0;
    Index3D.fMN = 0;
    Index3D.kRPM = Index3DP->kA;
    Index3D.kRPMH = Index3DP->kAH;
    Index3D.fRPM = Index3DP->fA;
          
    /*--------------------------------*/
    /* CALCULATION OF MODEL Ts2 VALUE */
    /*--------------------------------*/

    /* Calculation of static temeprature for ISA + 0 conditions */
    Ts2Std = InterpValue(&Index3D, Ts0MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Fn_Elem, Alt_Elem);
    /* Calculation of static temperature for ISA + dT conditions */
    Ts2Model = Ts2Std + ModelParsP->dT;

    /*------------------------------*/
    /* UPDATING OF MODEL PARAMETERS */
    /*------------------------------*/

    /* Updates value of Ts2StdSL */
    ModelParsP->Ts2StdSL = (*Ts0MtxP);
    /* Updates value of Ts2 in model parameters with calculated value */
    ModelParsP->Ts2 = Ts2Model;
    /* Updates value of Ts2Std in model parameters */
    ModelParsP->Ts2Std = Ts2Std;
//printf("\nNew: Ts2 = %f, dT = %f, Ts2StdSL = %f, Ts2Std = %f",ModelParsP->Ts2, ModelParsP->dT, ModelParsP->Ts2StdSL, ModelParsP->Ts2Std);
}

/*******************************************************************************
 *
 *	FUNCTION:		ResidualsCalc()
 *
 *	PURPOSE:		Obtains the smaller value between two variables (double)
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		a, b
 *
 *	RETURNS:		Value
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void ResidualsCalc(struct ControllerConstants *ContConstP,
             struct EstimatedPars *ModelParsP, struct SensedPars *SensorsP,
             struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
             struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
             struct AllResiduals *VibrationResP, struct AllResiduals *TBearResP)

{
     
    /* Used internal variables */
    double Ts2Model = ModelParsP->Ts2;
    int i;
     
    /* Sensors Numbers */   
    int NumTs2Sens = ContConstP->NumTs2Sens;
    int NumPs3Sens = ContConstP->NumPs3Sens;
    int NumTt4Sens = ContConstP->NumTt4Sens;
    int NumRPMSens = ContConstP->NumRPMSens;
    int NumVibrationSens = ContConstP->NumVibrationSens;
    int NumPOilSens = ContConstP->NumPOilSens;
    int NumPFuelSens = ContConstP->NumPFuelSens;
    int NumBearings = ContConstP->NumBear;

    /*--------------------------------*/
    /* CALCULATION OF MODEL RESIDUALS */
    /*--------------------------------*/

    /* STATION 2 SENSORS */

    /* Ts2 Thermocouples */
    for(i = 0; i < NumTs2Sens; i++)
    {
               
        /* Model residual */
        Ts2ResP->Model[i] = (SensorsP->Ts2[i] - Ts2Model) * (SensorsP->Ts2[i] - Ts2Model);
//printf("\nNew: Ts2ResP->Model[%d] = %f", i, Ts2ResP->Model[i]);
    }
    
    /* STATION 3 SENSORS */

    /* Pt3 Sensors */
    for(i = 0; i < NumPs3Sens; i++)
    {           
        
        /* Model residual - Must work in kPa instead of directly in Pa*/
        Pt3ResP->Model[i] = (SensorsP->Pt3[i] - ModelParsP->Pt3) * (SensorsP->Pt3[i] - ModelParsP->Pt3);
//printf("\nNew: Pt3ResP->Model[%d] = %f", i, Pt3ResP->Model[i]);
    }

    /* STATION 4 SENSORS */

    /* Tt4 Thermocouple*/
    for(i = 0; i < NumTt4Sens; i++)
    {    
        
        /* Model residual */
        Tt4ResP->Model[i] = (SensorsP->Tt4[i] - ModelParsP->Tt4) * (SensorsP->Tt4[i] - ModelParsP->Tt4);
//printf("\nNew: Tt4ResP->Model[%d] = %f", i, Tt4ResP->Model[i]);
    }

    /* SHAFT */

    /* RPM Sensors */
    for(i = 0; i < NumRPMSens; i++)
    {    
        
        /* Model residual */
        RPMResP->Model[i] = (SensorsP->RPM[i] - ModelParsP->RPM) * (SensorsP->RPM[i] - ModelParsP->RPM);
//printf("\nNew: RPMResP->Model[%d] = %f", i, RPMResP->Model[i]);
    }

    /* LUBRICATION SYSTEM */

    /* Oil Pressure sensors */
    for(i = 0; i < NumPOilSens; i++)
    {    
                  
        /* Model residual */
        POilResP->Model[i] = (SensorsP->POil[i] - ModelParsP->POil) * (SensorsP->POil[i] - ModelParsP->POil);
//printf("\nNew: POilResP->Model[%d] = %f", i, POilResP->Model[i]);
    }

    /* FUEL SYSTEM */

    /* PFuel Sensor */
    for(i = 0; i < NumPFuelSens; i++)
    {    
        
        /* Model residual */
        PFuelResP->Model[i] = (SensorsP->PFuel[i] - ModelParsP->PFuel) * (SensorsP->PFuel[i] - ModelParsP->PFuel);
//printf("\nNew: PFuelResP->Model[%d] = %f", i, PFuelResP->Model[i]);
    }

    /* VIBRATION */

    /* Vibration Sensor */
    for(i = 0; i < NumVibrationSens; i++)
    {    

        /* Model residual */
        VibrationResP->Model[i] = (SensorsP->Vibration[i] - ModelParsP->Vibration) * (SensorsP->Vibration[i] - ModelParsP->Vibration);      
//printf("\nNew: VibrationResP->Model[%d] = %f", i, VibrationResP->Model[i]);
    }
//printf("\n");

    /* BEARINGS */

    /* Bearings thermocouples */
    for(i = 0; i < NumBearings; i++)
    {    

        /* Model residual */
        TBearResP->Model[i] = (SensorsP->TBear[i] - ModelParsP->TBear[i]) * (SensorsP->TBear[i] - ModelParsP->TBear[i]);      

    }

}

/*******************************************************************************
 *
 *	FUNCTION:		ResProcSens()
 *
 *	PURPOSE:		Obtains the smaller value between two variables (double)
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void ResProcSens(struct ControllerConstants *ContConstP, struct EstimatedPars *ModelParsP, struct SensedPars *SensorsP,
            struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
            struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
            struct AllResiduals *VibrationResP, struct AllResiduals *TBearResP, 
            SensorFaults *FaultSSensP, SensorFaults *FaultWSensP, SensorFaults *FaultSensAuthP)
             
{
     
    /* Used internal variables */
//    double Ts2Std;
//    double Ts2Model = ModelParsP->Ts2;
//    InterpIndex3D Index3D;
    int i;
    int NumShiftsSens = 0;
    
    double Threshold = 0;
    
    /* Sensors Numbers */   
    int NumTs2Sens = ContConstP->NumTs2Sens;
    int NumPs3Sens = ContConstP->NumPs3Sens;
    int NumTt4Sens = ContConstP->NumTt4Sens;
    int NumRPMSens = ContConstP->NumRPMSens;
    int NumVibrationSens = ContConstP->NumVibrationSens;
    int NumPOilSens = ContConstP->NumPOilSens;
    int NumPFuelSens = ContConstP->NumPFuelSens;
    int NumBearings = ContConstP->NumBear;

//    /* Engine matrix element numbers */
//    int Fn_Elem = ContConstP->Fn_Elem;
//    int Alt_Elem = ContConstP->Alt_Elem;

    /* Authorization bit */
    int BitAuthorize;
    /* Auxiliar Bit for authorization information */
    //uint64_t AuxBitAuthor = FaultSensAuthP->FaultBits;

    /* Short-Open sensor values */
    double PFuelShort = ContConstP->PFuelShort;
    double PFuelOpen = ContConstP->PFuelOpen;
    double POilShort = ContConstP->POilShort;
    double POilOpen = ContConstP->POilOpen;
    double PSOpen = ContConstP->PSOpen;
//    double PSOpenThresh = ContConstP->PSOpenThresh;
    double PSShort = ContConstP->PSShort; 
//    double PSShortThresh =  ContConstP->PSShortThresh;
    double VibOpen = ContConstP->VibOpen;
//    double VibOpenThresh = ContConstP->VibOpenThresh;
    double VibShort = ContConstP->VibShort;
//    double VibShortThresh = ContConstP->VibShortThresh;
    double RPMShort = ContConstP->RPMShort;
    double RPMOpen = ContConstP->RPMOpen;
    double TCOpen = ContConstP->TCOpen;

    /* Thresholds */
    double RPMThreshold = ContConstP->RPMThreshold;
    
    /*-----------*/
    /* STATION 2 */
    /*-----------*/

    /* Ts2 Thermocouples */
    for(i = 0; i < NumTs2Sens; i++)
    {
                       
        /*-------------------------*/
        /* SENSORS FAULT ISOLATION */
        /*-------------------------*/


        
        /* SCV */

        /* SCV residual */
        /* The threshold value is set to one, since it will be compared to 0 */
        // Threshold = 1;
        // SensFaultIdent(Ts2ResP->Model[i],Threshold, Ts2ResP->SCV[i], &Ts2ResP->SCVCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        
        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* SCV residual */ 
            Ts2ResP->SCV[i] = 0;
        }
        // Ts2ResP->SCV[i] = 0;
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;
        
        /* SCG */

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* SCG residual */
            Ts2ResP->SCG[i] = 0;
        }

        // /* SCG residual */ 
        // Ts2ResP->SCG[i] = 0;
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;


        /* OPEN */

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
//            /* Open-Circuit residual */
//            /* The threshold value is set to one, since it will be compared to 0 */
//            Threshold = 1;
//            SensFaultIdent(Ts2ResP->Model[i], Threshold, Ts2ResP->Open[i], &Ts2ResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);

            /* Open-circuit threshold */
            Threshold = TCOpen;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SensResCompare(SensorsP->Ts2[i], Threshold, &Ts2ResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);

        }

        // /* Open-Circuit residual */
        // /* The threshold value is set to one, since it will be compared to 0 */
        // Threshold = 1;
        // SensFaultIdent(Ts2ResP->Model[i],Threshold, Ts2ResP->Open[i], &Ts2ResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;
       
    }
    
    /*-------------------*/
    /* STATION 3 SENSORS */
    /*-------------------*/

    /* Pt3 Sensors */
    for(i = 0; i < NumPs3Sens; i++)
    {           

        /*-------------------------*/
        /* SENSORS FAULT ISOLATION */
        /*-------------------------*/
        
        /* SHORT CIRCUIT */

        /* The following commented code makes a model-dependent analysis, wihch should not be currently used */

        // /* Short-Circuit residual */
        // Pt3ResP->Short[i] = (SensorsP->Pt3[i] - PSShort) * (SensorsP->Pt3[i] - PSShort);
        // Threshold = PSShortThresh;
        // Threshold = Threshold * Threshold;
        // /* Fault identification subroutine */
	    // SensFaultIdent(Pt3ResP->Model[i],Threshold, Pt3ResP->Short[i], &Pt3ResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSens++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Short-circuit threshold */
            Threshold = PSShort;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SensResCompare(SensorsP->Pt3[i], Threshold, &Pt3ResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        }
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        // /* Short-circuit threshold */
        // Threshold = PSShort;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(SensorsP->Pt3[i], Threshold, &Pt3ResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens); 
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSens++;
        
        /* OPEN CIRCUIT */

        /* The following commented code makes a model-dependent analysis, wihch should not be currently used */

        // /* Open-Circuit residual */
        // Pt3ResP->Open[i] = (SensorsP->Pt3[i] - PSOpen) * (SensorsP->Pt3[i] - PSOpen);       
        // /* Open-Circuit threshold */
        // Threshold = PSOpenThresh;
        // Threshold = Threshold * Threshold;
        // /* Fault identification subroutine */
	    // SensFaultIdent(Pt3ResP->Model[i],Threshold, Pt3ResP->Open[i], &Pt3ResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSens++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Open-circuit threshold */
            Threshold = PSOpen;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SensResCompare(Threshold, SensorsP->Pt3[i], &Pt3ResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        }
        // /* Open-circuit threshold */
        // Threshold = PSOpen;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(Threshold, SensorsP->Pt3[i], &Pt3ResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens); 
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;
        
    }

    /*-------------------*/
    /* STATION 4 SENSORS */
    /*-------------------*/

    /* Tt4 Thermocouple*/
    for(i = 0; i < NumTt4Sens; i++)
    {    

        /*-------------------------*/
        /* SENSORS FAULT ISOLATION */
        /*-------------------------*/
        
        /* SCV */

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* The threshold value is set to 1, since it will be compared do 0 */
            // Threshold = 1;
            // SensFaultIdent(Tt4ResP->Model[i],Threshold, Tt4ResP->SCV[i], &Tt4ResP->SCVCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
            Tt4ResP->SCV[i] = 0;
        }
        // /* The threshold value is set to 1, since it will be compared do 0 */
        // // Threshold = 1;
        // // SensFaultIdent(Tt4ResP->Model[i],Threshold, Tt4ResP->SCV[i], &Tt4ResP->SCVCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        // Tt4ResP->SCV[i] = 0;
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* SCG */

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* SCG residual */
            Tt4ResP->SCG[i] = 0;
        }
        // /* SCG residual */        
        // Tt4ResP->SCG[i] = 0;
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* OPEN-CIRCUIT */

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
//            /* The threshold value is set to 1, since it will be compared to 0 */
//            Threshold = 1;
//            SensFaultIdent(Tt4ResP->Model[i], Threshold, Tt4ResP->Open[i], &Tt4ResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);

            /* Open-circuit threshold */
            Threshold = TCOpen;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SensResCompare(SensorsP->Tt4[i], Threshold, &Tt4ResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);

        }
        // /* The threshold value is set to 1, since it will be compared to 0 */
        // Threshold = 1;
        // SensFaultIdent(Tt4ResP->Model[i],Threshold, Tt4ResP->Open[i], &Tt4ResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

    }

    /*-------*/
    /* SHAFT */
    /*-------*/

    /* RPM Sensors */
    for(i = 0; i < NumRPMSens; i++)
    {    

        /*------------------------*/
        /* SENSOR FAULT ISOLATION */
        /*------------------------*/
                
        /* SHORT-CIRCUIT */

        /* The following commented code makes a model-dependent analysis, wihch should not be currently used */

        // /* Short-Circuit residual */
        // RPMResP->Short[i] = (SensorsP->RPM[i] - RPMShort) * (SensorsP->RPM[i] - RPMShort);
        // /* Threshold is set to 1 since it will be compared to 0 */
        // Threshold = 1;
        // /* Detection of shrt-circuit at RPM sensor */
        // SensFaultIdent(RPMResP->Model[i],Threshold, RPMResP->Short[i], &RPMResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);        
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSens++;
        
        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Short-circuit threshold */
            Threshold = RPMShort;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SensResCompare(Threshold, SensorsP->RPM[i], &RPMResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        }
        //  /* Short-circuit threshold */
        // Threshold = RPMShort;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(Threshold, SensorsP->RPM[i], &RPMResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens); 
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* OPEN-CIRCUIT */

        /* The following commented code makes a model-dependent analysis, wihch should not be currently used */

        // /* Open-Circuit residual */
        // RPMResP->Open[i] = (SensorsP->RPM[i] - RPMOpen) * (SensorsP->RPM[i] - RPMOpen);
        // /* Threshold is set to 1 since it will be compared to 0 */
        // Threshold = 1;
        // /* Detection of Open-circuit in RPM sensor */
        // SensFaultIdent(RPMResP->Model[i],Threshold, RPMResP->Open[i], &RPMResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);        
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSens++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Open-circuit threshold */
            Threshold = RPMOpen;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SensResCompare(Threshold, SensorsP->RPM[i], &RPMResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        }
        // /* Open-circuit threshold */
        // Threshold = RPMOpen;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(Threshold, SensorsP->RPM[i], &RPMResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens); 
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* 1 PULSE LOSS */

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Loss of 1 pulse */
            RPMResP->PulseLoss1[i] = (SensorsP->RPM[i] - ModelParsP->RPM * 2 / 3) * (SensorsP->RPM[i] - ModelParsP->RPM * 2 / 3);
            /* Threshold value for 1 pulse loss */
            Threshold = ModelParsP->RPM * 2 / 3 * RPMThreshold;
            Threshold = Threshold * Threshold;
            /* Detection of 1 pulse loss by RPM sensor */
            SensFaultIdent(RPMResP->Model[i], Threshold, RPMResP->PulseLoss1[i], &RPMResP->PulseLoss1Count[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        }
        // /* Loss of 1 pulse */
        // RPMResP->PulseLoss1[i] = (SensorsP->RPM[i] - ModelParsP->RPM * 2 / 3) * (SensorsP->RPM[i] - ModelParsP->RPM * 2 / 3);
        // /* Threshold value for 1 pulse loss */
        // Threshold = ModelParsP->RPM * 2 / 3 * RPMThreshold;
        // Threshold = Threshold * Threshold;
        // /* Detection of 1 pulse loss by RPM sensor */
        // SensFaultIdent(RPMResP->Model[i],Threshold, RPMResP->PulseLoss1[i], &RPMResP->PulseLoss1Count[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);        
         /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* 2 PULSES LOSS */

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Loss of 2 pulses */
            RPMResP->PulseLoss2[i] = (SensorsP->RPM[i] - ModelParsP->RPM * 1 / 3) * (SensorsP->RPM[i] - ModelParsP->RPM * 1 / 3);
            /* Threshold value for 2 pulses loss */
            Threshold = ModelParsP->RPM * 1 / 3 * RPMThreshold;
            Threshold = Threshold * Threshold;
            /* Detection of 2 pulses loss by RPM sensor */
            SensFaultIdent(RPMResP->Model[i], Threshold, RPMResP->PulseLoss2[i], &RPMResP->PulseLoss2Count[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        }
        // /* Loss of 2 pulses */
        // RPMResP->PulseLoss2[i] = (SensorsP->RPM[i] - ModelParsP->RPM * 1 / 3) * (SensorsP->RPM[i] - ModelParsP->RPM * 1 / 3);
        // /* Threshold value for 2 pulses loss */
        // Threshold = ModelParsP->RPM * 1 / 3 * RPMThreshold;
        // Threshold = Threshold * Threshold;
        // /* Detection of 2 pulses loss by RPM sensor */
        // SensFaultIdent(RPMResP->Model[i],Threshold, RPMResP->PulseLoss2[i], &RPMResP->PulseLoss2Count[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);        
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

    }

    /*--------------------*/
    /* LUBRICATION SYSTEM */
    /*--------------------*/

    /* Oil Pressure sensors */
    for(i = 0; i < NumPOilSens; i++)
    {    
          
        /*------------------------*/
        /* SENSOR FAULT ISOLATION */
        /*------------------------*/       
        
        /* SHORT-CIRCUIT */

        /* The following commented code makes a model-dependent analysis, wihch should not be currently used */

        // /* Short-Circuit residual */
        // POilResP->Short[i] = (SensorsP->POil[i] - PSShort) * (SensorsP->POil[i] - PSShort);
        // /* Short-Circuit threshold */
        // Threshold = PSShortThresh;
        // Threshold = Threshold * Threshold;
        // /* Fault identification subroutine */
	    // SensFaultIdent(POilResP->Model[i],Threshold, POilResP->Short[i], &POilResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSens++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Short-circuit threshold */
            Threshold = POilShort;//PSShort;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SensResCompare(SensorsP->POil[i], Threshold, &POilResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        }
        // /* Short-circuit threshold */
        // Threshold = PSShort;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(SensorsP->POil[i], Threshold, &POilResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens); 
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* OPEN-CIRCUIT */

        /* The following commented code makes a model-dependent analysis, wihch should not be currently used */

        // /* Open-Circuit residual */
        // POilResP->Open[i] = (SensorsP->POil[i] - PSOpen) * (SensorsP->POil[i] - PSOpen);
        // /* Threshold is set to 1 since it will be compared to 0 */
        // Threshold = 1;
        // /* Fault identification subroutine */
	    // SensFaultIdent(POilResP->Model[i],Threshold, POilResP->Open[i], &POilResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSens++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Open-circuit threshold */
            Threshold = POilOpen;//PSOpen;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SensResCompare(Threshold, SensorsP->POil[i], &POilResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        }
        // /* Open-circuit threshold */
        // Threshold = PSOpen;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(Threshold, SensorsP->POil[i], &POilResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens); 
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

    }
//printf("PSOpen = %f, POil = %f, PFuel = %f\n",PSOpen, SensorsP->POil[0], SensorsP->PFuel[0]);
    /*-------------*/
    /* FUEL SYSTEM */
    /*-------------*/

    /* PFuel Sensor */
    for(i = 0; i < NumPFuelSens; i++)
    {    

        /*------------------------*/
        /* SENSOR FAULT ISOLATION */
        /*------------------------*/
        
        /* SHORT-CIRCUIT */

        /* The following commented code makes a model-dependent analysis, wihch should not be currently used */

        // /* Short-Circuit residual */
        // PFuelResP->Short[i] = (SensorsP->PFuel[i] - PFuelShort) * (SensorsP->PFuel[i] - PFuelShort);
        // /* Short-Circuit threshold */
        // Threshold = PSShortThresh;
        // Threshold = Threshold * Threshold;
        // /* Fault identification subroutine */
	    // SensFaultIdent(PFuelResP->Model[i],Threshold, PFuelResP->Short[i], &PFuelResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSens++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Short-circuit threshold */
            Threshold = PFuelShort;//PSShort;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SensResCompare(SensorsP->PFuel[i], Threshold, &PFuelResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        }
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* OPEN-CIRCUIT */

        /* The following commented code makes a model-dependent analysis, wihch should not be currently used */

        // /* Open-Circuit residual */
        // PFuelResP->Open[i] = (SensorsP->PFuel[i] - PSOpen) * (SensorsP->PFuel[i] - PSOpen);
        // /* Threshold is set to 1 since it will be compared to 0 */
        // Threshold = 1;
        // /* Fault identification subroutine */
	    // SensFaultIdent(PFuelResP->Model[i],Threshold, PFuelResP->Open[i], &PFuelResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSens++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Open-circuit threshold */
            Threshold = PFuelOpen;//PSOpen;
//printf("PFuel=%f, PFuelOpen=%f\n", SensorsP->PFuel[i], PFuelOpen);
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SensResCompare(Threshold, SensorsP->PFuel[i], &PFuelResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        }
        // /* Open-circuit threshold */
        // Threshold = PSOpen;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(Threshold, SensorsP->PFuel[i], &PFuelResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens); 
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

    }

    /*-----------*/
    /* VIBRATION */
    /*-----------*/

    /* Vibration Sensor */
    for(i = 0; i < NumVibrationSens; i++)
    {    
  
        /*------------------------*/
        /* SENSOR FAULT ISOLATION */
        /*------------------------*/
        
        /* SHORT-CIRCUIT */

        /* The following commented code makes a model-dependent analysis, wihch should not be currently used */

        // /* Short-Circuit residual */
        // VibrationResP->Short[i] = (SensorsP->Vibration[i] - VibShort) * (SensorsP->Vibration[i] - VibShort);
        // /* Short-Circuit threshold */
        // Threshold = VibShortThresh;
        // Threshold = Threshold * Threshold;
        // /* Fault identification subroutine */
        // SensFaultIdent(VibrationResP->Model[i],Threshold, VibrationResP->Short[i], &VibrationResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);                
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSens++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Short-circuit threshold */
            Threshold = VibShort;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SensResCompare(SensorsP->Vibration[i], Threshold, &VibrationResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        }
        // /* Short-circuit threshold */
        // Threshold = VibShort;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(SensorsP->Vibration[i], Threshold, &VibrationResP->ShortCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens); 
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

        /* OPEN-CIRCUIT */

        /* The following commented code makes a model-dependent analysis, wihch should not be currently used */

        // /* Open-Circuit residual */
        // VibrationResP->Open[i] = (SensorsP->Vibration[i] - VibOpen) * (SensorsP->Vibration[i] - VibOpen);
        // /* Threshold is set to 1 since it will be compared to 0 */
        // Threshold = 1;
        // /* Fault identification subroutine */
        // SensFaultIdent(VibrationResP->Model[i],Threshold, VibrationResP->Open[i], &VibrationResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);                        
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSens++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Open-circuit threshold */
            Threshold = VibOpen;
//printf("Vib=%f, VibOpen=%f\n\n", SensorsP->Vibration[i], VibOpen);
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SensResCompare(Threshold, SensorsP->Vibration[i], &VibrationResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        }
        // /* Open-circuit threshold */
        // Threshold = VibOpen;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(Threshold, SensorsP->Vibration[i], &VibrationResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens); 
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

    }

    /*----------*/
    /* BEARINGS */
    /*----------*/

    /* Vibration Sensor */
    for(i = 0; i < NumBearings; i++)
    {    
  
        /*------------------------*/
        /* SENSOR FAULT ISOLATION */
        /*------------------------*/
        
        /* OPEN */

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSens, FaultSensAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Open-Circuit residual */
            /* The threshold value is set to one, since it will be compared to 0 */
            Threshold = 1;
            SensFaultIdent(TBearResP->Model[i], Threshold, TBearResP->Open[i], &TBearResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        }
        // /* Open-Circuit residual */
        // /* The threshold value is set to one, since it will be compared to 0 */
        // Threshold = 1;
        // SensFaultIdent(TBearResP->Model[i],Threshold, TBearResP->Open[i], &TBearResP->OpenCount[i], ModelParsP->MaxInter, FaultSSensP, FaultWSensP, NumShiftsSens);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSens++;

    }

}

/*******************************************************************************
 *
 *	FUNCTION:		ResProcSys()
 *
 *	PURPOSE:		Obtains the smaller value between two variables (double)
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void ResProcSys(struct ControllerConstants *ContConstP, struct EstimatedPars *ModelParsP, 
             struct EstimatedPars *BlowOutParsP, struct SensedPars *SensorsP,
             struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
             struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
             struct AllResiduals *VibrationResP, struct AllResiduals *TBearResP,
             SystemFaults *FaultSSysP, SystemFaults *FaultWSysP, SystemFaults *FaultSysAuthP,
             FaultDetect *CANFaultsP, struct ControlStart *ContStartP)

{
     
    /* Used internal variables */
    int i;
    int NumShiftsSys = 0;
    double Threshold = 0;

    /* Authorization bit */
    int BitAuthorize;
        
    /* Sensors Numbers */   
//    int NumTs2Sens = ContConstP->NumTs2Sens;
    int NumPs3Sens = ContConstP->NumPs3Sens;
    int NumTt4Sens = ContConstP->NumTt4Sens;
    int NumRPMSens = ContConstP->NumRPMSens;
    int NumVibrationSens = ContConstP->NumVibrationSens;
    int NumPOilSens = ContConstP->NumPOilSens;
    int NumPFuelSens = ContConstP->NumPFuelSens;
    int NumBearings = ContConstP->NumBear;

    /* Time parameters - seconds */
    double MaxInter_POilHigh = ContConstP->TimeHighPOil;   
    double MaxInter_POilLow = ContConstP->TimeLowPOil;     
    double MaxInter_PFuelHigh = ContConstP->TimeHighPFuel;  
    double MaxInter_PFuelLow = ContConstP->TimeLowPFuel;   
    double MaxInter_VibHigh = ContConstP->TimeHighVibration;    
    double MaxInter_Overspeed = ContConstP->TimeOverspeed; 
    double MaxInter_OverTemp = ContConstP->TimeOvertemp;
    double MaxInter_OTBear[5];
    MaxInter_OTBear[0] = ContConstP->TimeBearOverTemp[0];
    MaxInter_OTBear[1] = ContConstP->TimeBearOverTemp[1];
    MaxInter_OTBear[2] = ContConstP->TimeBearOverTemp[2];   

    /* Time parameters adjustment from seconds to interaction number */
    MaxInter_POilHigh = MaxInter_POilHigh / TICK / 0.001;   
    MaxInter_POilLow = MaxInter_POilLow / TICK / 0.001;    
    MaxInter_PFuelHigh = MaxInter_PFuelHigh / TICK / 0.001;  
    MaxInter_PFuelLow = MaxInter_PFuelLow / TICK / 0.001;   
    MaxInter_VibHigh = MaxInter_VibHigh / TICK / 0.001;    
    MaxInter_Overspeed = MaxInter_Overspeed / TICK / 0.001; 
    MaxInter_OverTemp = MaxInter_OverTemp / TICK / 0.001;   
    MaxInter_OTBear[0] = MaxInter_OTBear[0] / TICK / 0.001;
    MaxInter_OTBear[1] = MaxInter_OTBear[1] / TICK / 0.001;
    MaxInter_OTBear[2] = MaxInter_OTBear[2] / TICK / 0.001;

    /* Thresholds */
    double TCThreshold = ContConstP->TCThreshold; 
    double Tt4ShaftLock = ContConstP->Tt4ShaftLock;
    double Tt4BlowOut = ContConstP->Tt4BlowOut;
    double PSThreshold =  ContConstP->PSThreshold;
    double Pt3BlowOut = ContConstP->Pt3BlowOut;
//    double VibThreshold = ContConstP->VibThreshold;
//    double RPMThreshold = ContConstP->RPMThreshold;
    double RPMBlowOut = ContConstP->RPMBlowOut;

    /* Limit Values */
    double PFuelHigh = ContConstP->PFuelHigh; 
    double PFuelLow = ContConstP->PFuelLow;
    double POilHigh = ContConstP->POilHigh; 
    double POilLow = ContConstP->POilLow;
    double VibHigh = ContConstP->VibHigh;
    double Tt4Max = ContConstP->Tt4Max;
    double NMax = ContConstP->NMax;

    
    /*-------------------*/
    /* STATION 3 SENSORS */
    /*-------------------*/

    /* Pt3 Sensors */
    for(i = 0; i < NumPs3Sens; i++)
    {           
         
        /*-----------------------------------*/
        /* IDENTIFICATION OF SYSTEM FAILURES */
        /*-----------------------------------*/
        
        /* ENGINE BLOW OUT */

        //NOTE: The commented code below is used with a BlowOut dynamic model, which should be
        //validated and refined before actual use

        // /* Blow Out residual */
        // Pt3ResP->BlowOut[i] = (SensorsP->Pt3[i] - BlowOutParsP->Pt3) * (SensorsP->Pt3[i] - BlowOutParsP->Pt3);
        // /* Compares the residuals of nominal model with fault model */
        // SysResCompare(Pt3ResP->Model[i], Pt3ResP->BlowOut[i], &Pt3ResP->BlowOutCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSys++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* High Pt3 threshold */
            Threshold = Pt3BlowOut;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SysResCompare(Threshold, SensorsP->Pt3[i], &Pt3ResP->BlowOutCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);
        }
        // /* High Pt3 threshold */
        // Threshold = Pt3BlowOut;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(Threshold, SensorsP->Pt3[i], &Pt3ResP->BlowOutCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

        /* SHAFT LOCK */

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Shaft-Lock residual */
            Pt3ResP->ShaftLock[i] = (SensorsP->Pt3[i] - ModelParsP->Pt2) * (SensorsP->Pt3[i] - ModelParsP->Pt2);
            /* Shaft-Lock threshold */
            Threshold = ModelParsP->Pt2 * PSThreshold;
            Threshold = Threshold * Threshold;
            /* Fault identification subroutine */
            SysFaultIdent(Pt3ResP->Model[i], Threshold, Pt3ResP->ShaftLock[i], &Pt3ResP->ShaftLockCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);
        }
        // /* Shaft-Lock residual */
        // Pt3ResP->ShaftLock[i] = (SensorsP->Pt3[i] - ModelParsP->Pt2) * (SensorsP->Pt3[i] - ModelParsP->Pt2);
        // /* Shaft-Lock threshold */
        // Threshold = ModelParsP->Pt2 * PSThreshold;
        // Threshold = Threshold * Threshold;
        // /* Fault identification subroutine */
	    // SysFaultIdent(Pt3ResP->Model[i],Threshold, Pt3ResP->ShaftLock[i], &Pt3ResP->ShaftLockCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);        
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

    }

    /*-------------------*/
    /* STATION 4 SENSORS */
    /*-------------------*/

    /* Tt4 Thermocouple*/
    for(i = 0; i < NumTt4Sens; i++)
    {    

        /*-----------------------------------*/
        /* IDENTIFICATION OF SYSTEM FAILURES */
        /*-----------------------------------*/

        /* OVERTEMP */

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Residual for high Tt4 */
            // Tt4ResP->High[i] = (SensorsP->Tt4[i] - Tt4Max) * (SensorsP->Tt4[i] - Tt4Max);
            /* High Tt4 threshold */
            Threshold = Tt4Max;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SysResCompare(SensorsP->Tt4[i], Threshold, &Tt4ResP->HighCount[i], MaxInter_OverTemp, FaultSSysP, FaultWSysP, NumShiftsSys);
        }
        // /* Residual for high Tt4 */
        // //Tt4ResP->High[i] = (SensorsP->Tt4[i] - Tt4Max) * (SensorsP->Tt4[i] - Tt4Max);
        // /* High Tt4 threshold */
        // Threshold = Tt4Max;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(SensorsP->Tt4[i], Threshold, &Tt4ResP->HighCount[i], MaxInter_OverTemp, FaultSSysP, FaultWSysP, NumShiftsSys);        
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

        /* BLOW OUT */

        //NOTE: The commented code below is used with a BlowOut dynamic model, which should be
        //validated and refined before actual use

        // /* Blow Out residual */
        // Tt4ResP->BlowOut[i] = (SensorsP->Tt4[i] - BlowOutParsP->Tt4) * (SensorsP->Tt4[i] - BlowOutParsP->Tt4);  
        // /* Residual comparison for detection of Blow Out by Tt4 */
        // SysResCompare(Tt4ResP->Model[i], Tt4ResP->BlowOut[i], &Tt4ResP->BlowOutCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSys++;  

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Blow out threshold */
            Threshold = Tt4BlowOut;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SysResCompare(Threshold, SensorsP->Tt4[i], &Tt4ResP->BlowOutCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);
        }
        // /* Blow out threshold */
        // Threshold = Tt4BlowOut;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(Threshold, SensorsP->Tt4[i], &Tt4ResP->BlowOutCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys); 
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

        /* SHAFT LOCK */

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Shaft Lock residual */
            Tt4ResP->ShaftLock[i] = (SensorsP->Tt4[i] - Tt4ShaftLock) * (SensorsP->Tt4[i] - Tt4ShaftLock);
            Threshold = Tt4ShaftLock;
            Threshold = Threshold * TCThreshold;
            Threshold = Threshold * Threshold;
            /* Detection of Shaft Lock by Tt4 */
            SysFaultIdent(Tt4ResP->Model[i], Threshold, Tt4ResP->ShaftLock[i], &Tt4ResP->ShaftLockCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);
        }
        // /* Shaft Lock residual */
        // Tt4ResP->ShaftLock[i] = (SensorsP->Tt4[i] - Tt4ShaftLock) * (SensorsP->Tt4[i] - Tt4ShaftLock);
        // Threshold = Tt4ShaftLock;
        // Threshold = Threshold * TCThreshold;
        // Threshold = Threshold * Threshold;
        // /* Detection of Shaft Lock by Tt4 */
        // SysFaultIdent(Tt4ResP->Model[i],Threshold, Tt4ResP->ShaftLock[i], &Tt4ResP->ShaftLockCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);        
         /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

    }

    /*-------*/
    /* SHAFT */
    /*-------*/

    /* RPM Sensors */
    for(i = 0; i < NumRPMSens; i++)
    {    

        /*------------------------*/
        /* SYSTEM FAULT ISOLATION */
        /*------------------------*/
        
        /* OVERSPEED */

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Residual for high fuel Pressure */
            // RPMResP->High[i] = (SensorsP->RPM[i] - NMax) * (SensorsP->RPM[i] - NMax);
            /* Overspeed threshold */
            Threshold = NMax;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SysResCompare(SensorsP->RPM[i], Threshold, &RPMResP->HighCount[i], MaxInter_Overspeed, FaultSSysP, FaultWSysP, NumShiftsSys);
        }
        // /* Residual for high fuel Pressure */
        // //RPMResP->High[i] = (SensorsP->RPM[i] - NMax) * (SensorsP->RPM[i] - NMax);
        // /* Overspeed threshold */
        // Threshold = NMax;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(SensorsP->RPM[i], Threshold, &RPMResP->HighCount[i], MaxInter_Overspeed, FaultSSysP, FaultWSysP, NumShiftsSys);        
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

        /* BLOW OUT */

        //NOTE: The commented code below is used with a BlowOut dynamic model, which should be
        //validated and refined before actual use

        // /* Blow Out residual */
        // RPMResP->BlowOut[i] = (SensorsP->RPM[i] - BlowOutParsP->RPM) * (SensorsP->RPM[i] - BlowOutParsP->RPM);
        // /* Detection of blow out by RPM sensor */
        // SysResCompare(RPMResP->Model[i], RPMResP->BlowOut[i], &RPMResP->BlowOutCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSys++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Blow Out RPM threshold */
            Threshold = RPMBlowOut;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SysResCompare(Threshold, SensorsP->RPM[i], &RPMResP->BlowOutCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);
        }
        // /* Blow Out RPM threshold */
        // Threshold = RPMBlowOut;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(Threshold, SensorsP->RPM[i], &RPMResP->BlowOutCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys); 
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

        /* SHAFT LOCK */

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Shaft Lock residual */
            RPMResP->ShaftLock[i] = (SensorsP->RPM[i]) * (SensorsP->RPM[i]);
            /* Threshold is set to 1 since it will be compared to 0 */
            Threshold = 1;
            /* Identification of shaft lock by RPM sensor */
            SysFaultIdent(RPMResP->Model[i], Threshold, RPMResP->ShaftLock[i], &RPMResP->ShaftLockCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);
        }
        // /* Shaft Lock residual */
        // RPMResP->ShaftLock[i] = (SensorsP->RPM[i]) * (SensorsP->RPM[i]);
        // /* Threshold is set to 1 since it will be compared to 0 */
        // Threshold = 1;
        // /* Identification of shaft lock by RPM sensor */
        // SysFaultIdent(RPMResP->Model[i],Threshold, RPMResP->ShaftLock[i], &RPMResP->ShaftLockCount[i], ModelParsP->MaxInter, FaultSSysP, FaultWSysP, NumShiftsSys);                
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

    }

    /*--------------------*/
    /* LUBRICATION SYSTEM */
    /*--------------------*/

    /* The analysis of oil pressure must not start at the very begining, since the 
    oil might start with zero pressure and a false oil low pressure could be indicated.
    Therefore, the flag POilAllow is treated outside, guaranteeing safe oil pressure analysis */

    // if (ContStartP->POilSysAllow == 1)
    // {

    /* Oil Pressure sensors */
    for (i = 0; i < NumPOilSens; i++)
    {

        /*------------------------*/
        /* SYSTEM FAULT ISOLATION */
        /*------------------------*/

        /* HIGH OIL PRESSURE */

        /* The code commented below is not propper since modeling of oil pressure is not available */

        // /* Residual for High Oil Pressure */
        // POilResP->High[i] = (SensorsP->POil[i] - POilHigh) * (SensorsP->POil[i] - POilHigh);
        // /* Threshold for high oil pressure */
        // Threshold = POilHigh;
        // /* High oil pressure detection - uses its own time parameter instead of Model->MaxIter */
        // SysResCompare(SensorsP->POil[i], Threshold, &POilResP->HighCount[i], MaxInter_POilHigh, FaultSSysP, FaultWSysP, NumShiftsSys);
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSys++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* High Oil pressure threshold */
            Threshold = POilHigh;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SysResCompare(SensorsP->POil[i], Threshold, &POilResP->HighCount[i], MaxInter_POilHigh, FaultSSysP, FaultWSysP, NumShiftsSys);
        }
        // /* High Oil pressure threshold */
        // Threshold = POilHigh;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(SensorsP->POil[i], Threshold, &POilResP->HighCount[i], MaxInter_POilHigh, FaultSSysP, FaultWSysP, NumShiftsSys);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

        /* LOW OIL PRESSURE */

        /* The code commented below is not propper since modeling of oil pressure is not available */

        // /* Residual for High Oil Pressure */
        // POilResP->Low[i] = (SensorsP->POil[i] - POilLow) * (SensorsP->POil[i] - POilLow);
        // /* Threshold for low oil pressure */
        // Threshold = POilLow;
        // /* Low oil pressure detection */
        // SysResCompare(Threshold, SensorsP->POil[i], &POilResP->LowCount[i], MaxInter_POilLow, FaultSSysP, FaultWSysP, NumShiftsSys);
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSys++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Low Oil pressure threshold */
            Threshold = POilLow;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SysResCompare(Threshold, SensorsP->POil[i], &POilResP->LowCount[i], MaxInter_POilLow, FaultSSysP, FaultWSysP, NumShiftsSys);
        }
        // /* Low Oil pressure threshold */
        // Threshold = POilLow;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(Threshold, SensorsP->POil[i], &POilResP->LowCount[i], MaxInter_POilLow, FaultSSysP, FaultWSysP, NumShiftsSys);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;
    }
    //}

    /*-------------*/
    /* FUEL SYSTEM */
    /*-------------*/

    /* The analysis of fuel pressure must not start at the very begining, since the 
    fuel might start with zero pressure and a false fuel low pressure could be indicated.
    Therefore, the flag PFuelAllow is treated outside, guaranteeing safe oil pressure analysis */

    // if (ContStartP->PFuelSysAllow == 1)
    // {

    /* PFuel Sensor */
    for (i = 0; i < NumPFuelSens; i++)
    {

        /*------------------------*/
        /* SYSTEM FAULT ISOLATION */
        /*------------------------*/

        /* HIGH FUEL PRESSURE */

        /* The code commented below is not propper since modeling of oil pressure is not available */

        // /* Residual for high fuel Pressure */
        // PFuelResP->High[i] = (SensorsP->PFuel[i] - PFuelHigh) * (SensorsP->PFuel[i] - PFuelHigh);
        // /* High fuel pressure threshold */
        // Threshold = PFuelHigh;
        // /* Fault identification subroutine */
        // SysResCompare(SensorsP->PFuel[i], Threshold, &PFuelResP->HighCount[i], MaxInter_PFuelHigh, FaultSSysP, FaultWSysP, NumShiftsSys);
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSys++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* High fuel pressure threshold */
            Threshold = PFuelHigh;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SysResCompare(SensorsP->PFuel[i], Threshold, &PFuelResP->HighCount[i], MaxInter_PFuelHigh, FaultSSysP, FaultWSysP, NumShiftsSys);
        }
        // /* High fuel pressure threshold */
        // Threshold = PFuelHigh;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(SensorsP->PFuel[i], Threshold, &PFuelResP->HighCount[i], MaxInter_PFuelHigh, FaultSSysP, FaultWSysP, NumShiftsSys);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

        /* LOW FUEL PRESSURE */

        /* The code commented below is not propper since modeling of oil pressure is not available */

        // /* Residual for high fuel pressure */
        // PFuelResP->Low[i] = (SensorsP->PFuel[i] - PFuelLow) * (SensorsP->PFuel[i] - PFuelLow);
        // /* High fuel pressure threshold */
        // Threshold = PFuelLow;
        // /* System fault identification */
        // SysResCompare(Threshold, SensorsP->PFuel[i], &PFuelResP->LowCount[i], MaxInter_PFuelLow, FaultSSysP, FaultWSysP, NumShiftsSys);
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSys++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Low fuel pressure threshold */
            Threshold = PFuelLow;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SysResCompare(Threshold, SensorsP->PFuel[i], &PFuelResP->LowCount[i], MaxInter_PFuelLow, FaultSSysP, FaultWSysP, NumShiftsSys);
        }
        // /* Low fuel pressure threshold */
        // Threshold = PFuelLow;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(Threshold, SensorsP->PFuel[i], &PFuelResP->LowCount[i], MaxInter_PFuelLow, FaultSSysP, FaultWSysP, NumShiftsSys);
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;
    }
//printf("PFuelLow = %f, PFuel[0] = %f\n", PFuelLow, SensorsP->PFuel[0]);
    //}
    /*-----------*/
    /* VIBRATION */
    /*-----------*/

    /* Vibration Sensor */
    for(i = 0; i < NumVibrationSens; i++)
    {    

        /*------------------------*/
        /* SYSTEM FAULT ISOLATION */
        /*------------------------*/
        
        /* HIGH VIBRATION */

        /* The code commented below is not propper since modeling of oil pressure is not available */

        // /* High vibration residual */
        // VibrationResP->High[i] = (SensorsP->Vibration[i] - VibHigh) * (SensorsP->Vibration[i] - VibHigh);
        // /* High vibration threshold */
        // Threshold = VibHigh;
        // /* Fault detection subroutine */
        // SysResCompare(SensorsP->Vibration[i], Threshold, &VibrationResP->HighCount[i], MaxInter_VibHigh, FaultSSysP, FaultWSysP, NumShiftsSys);        
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSys++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* High vibration threshold */
            Threshold = VibHigh;
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SysResCompare(SensorsP->Vibration[i], Threshold, &VibrationResP->HighCount[i], MaxInter_VibHigh, FaultSSysP, FaultWSysP, NumShiftsSys);
        }
        // /* High vibration threshold */
        // Threshold = VibHigh;
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(SensorsP->Vibration[i], Threshold, &VibrationResP->HighCount[i], MaxInter_VibHigh, FaultSSysP, FaultWSysP, NumShiftsSys); 
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

    }

    /*----------*/
    /* BEARINGS */
    /*----------*/

    /* Bearings Thermocouples */
    for(i = 0; i < NumBearings; i++)
    {    

        /*------------------------*/
        /* SYSTEM FAULT ISOLATION */
        /*------------------------*/
        
        /* HIGH BEARING TEMPERATURE */

        /* The code commented below is not propper since modeling of oil pressure is not available */

        // /* High vibration residual */
        // VibrationResP->High[i] = (SensorsP->Vibration[i] - VibHigh) * (SensorsP->Vibration[i] - VibHigh);
        // /* High vibration threshold */
        // Threshold = VibHigh;
        // /* Fault detection subroutine */
        // SysResCompare(SensorsP->Vibration[i], Threshold, &VibrationResP->HighCount[i], MaxInter_VibHigh, FaultSSysP, FaultWSysP, NumShiftsSys);        
        // /*Updates number of shifts for next fault analysis*/
        // NumShiftsSys++;

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* High bearing temperature threshold */
            Threshold = ContConstP->TMaxBear[i];
            /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
            /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
            /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
            SysResCompare(SensorsP->TBear[i], Threshold, &TBearResP->HighCount[i], MaxInter_OTBear[i], FaultSSysP, FaultWSysP, NumShiftsSys);
        }
        // /* High bearing temperature threshold */
        // Threshold = ContConstP->TMaxBear[i];
        // /* Fault detection subroutine - if the first parameter is equal or larger than the second, the fault is accused */
        // /* If the fault value is larger than operating value, sensor value must be first parameter and fault value (Threshold) must be the second parameter*/
        // /* If the fault value is smaller than operating value, fault value (Threshold) must be first parameter and sensor value must be the second parameter*/
        // SysResCompare(SensorsP->TBear[i], Threshold, &TBearResP->HighCount[i], MaxInter_OTBear[i], FaultSSysP, FaultWSysP, NumShiftsSys); 
        /*Updates number of shifts for next fault analysis*/
        NumShiftsSys++;

    }

    /*-------------*/
    /* CAN NETWORK */
    /*-------------*/

    /* For the CAN network fault update, a simple analysis is required, since the time evaluation is accomplished outside */

    /*-------*/
    /* CAN 0 */
    /*-------*/

    /* Verifies if fault analysis is authorized */
    BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
    /* Analysed the fault only if authorized */
    if (BitAuthorize == 1)
    {
        FaultSSysP->SysFaults.CAN_0_Fault = CANFaultsP->DetFaults.CAN_0_Fault;
        FaultWSysP->SysFaults.CAN_0_Fault = CANFaultsP->DetFaults.CAN_0_Fault;
    }

    /*Updates number of shifts for next fault analysis*/
    NumShiftsSys++;

    /*-------*/
    /* CAN 1 */
    /*-------*/

    /* Verifies if fault analysis is authorized */
    BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
    /* Analysed the fault only if authorized */
    if (BitAuthorize == 1)
    {
        FaultSSysP->SysFaults.CAN_1_Fault = CANFaultsP->DetFaults.CAN_1_Fault;
        FaultWSysP->SysFaults.CAN_1_Fault = CANFaultsP->DetFaults.CAN_1_Fault;
    }

    /*Updates number of shifts for next fault analysis*/
    NumShiftsSys++;   

    /*----------*/
    /* IGNITION */
    /*----------*/

    /* Detection of Ignition failure */
    /* Verifies if fault analysis is authorized */
    BitIsTrue(NumShiftsSys, FaultSysAuthP->FaultBits, &BitAuthorize);
    /* Analysed the fault only if authorized */
    if (BitAuthorize == 1)
    {
        FaultSSysP->SysFaults.Ignition = ContStartP->IgnitionFail;
    }

}

/*******************************************************************************
 *
 *	FUNCTION:		ResProcBias()
 *
 *	PURPOSE:		Obtains the smaller value between two variables (double)
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		a, b
 *
 *	RETURNS:		Value
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void ResProcBias(struct ControllerConstants *ContConstP, struct EstimatedPars *ModelParsP,
             struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
             struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
             struct AllResiduals *VibrationResP, FaultDetect *HardFStatusP, FaultDetect *HardFWarningP, FaultDetect *HardFAuthP) 

{
     
    /* Used internal variables */
    double Ts2Model = ModelParsP->Ts2;
    int i;
    int NumShiftsHard = 0;    
    double Threshold = 0;

    /* Authorization bit */
    int BitAuthorize;
        
    /* Sensors Numbers */   
    int NumTs2Sens = ContConstP->NumTs2Sens;
    int NumPs3Sens = ContConstP->NumPs3Sens;
    int NumTt4Sens = ContConstP->NumTt4Sens;
    int NumRPMSens = ContConstP->NumRPMSens;
    int NumVibrationSens = ContConstP->NumVibrationSens;
    int NumPOilSens = ContConstP->NumPOilSens;
    int NumPFuelSens = ContConstP->NumPFuelSens;

    /* Thresholds */
    double TCThreshold = ContConstP->TCThreshold;
    double Ts2Threshold = ContConstP->Ts2Threshold;
    double Tt4Threshold = ContConstP->Tt4Threshold; 
    double PSThreshold =  ContConstP->PSThreshold;
    double Pt3Threshold = ContConstP->Pt3Threshold;
    double VibThreshold = ContConstP->VibThreshold;
    double RPMThreshold = ContConstP->RPMThreshold;
    double POilThreshold = ContConstP->POilThreshold;
    double PFuelThreshold = ContConstP->PFuelThreshold;
    
    /*-----------*/
    /* STATION 2 */
    /*-----------*/

    /* Ts2 Thermocouples */
    for(i = 0; i < NumTs2Sens; i++)
    {
       
        /*----------------------*/
        /* HARD FAULT DETECTION */
        /*----------------------*/
        
        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsHard, HardFAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Hard fault detection */
            //Threshold = (Ts2Model * TCThreshold) * (Ts2Model * TCThreshold);
            Threshold = (Ts2Model * Ts2Threshold) * (Ts2Model * Ts2Threshold);
            HardFault(Ts2ResP->Model[i], Threshold, &Ts2ResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP, NumShiftsHard);
        }
        // /* Hard fault detection */
        // Threshold = (Ts2Model * TCThreshold) * (Ts2Model * TCThreshold);
        // HardFault(Ts2ResP->Model[i], Threshold, &Ts2ResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP,  NumShiftsHard);
        /* Updates number of shifts for hard fault detection in next sensor */
        NumShiftsHard++;
               
    }
    
    /*-------------------*/
    /* STATION 3 SENSORS */
    /*-------------------*/

    /* Pt3 Sensors */
    for(i = 0; i < NumPs3Sens; i++)
    {           

        /*----------------------*/
        /* HARD FAULT DETECTION */
        /*----------------------*/

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsHard, HardFAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Calculation of threshold */
            //Threshold = (ModelParsP->Pt3 * PSThreshold) * (ModelParsP->Pt3 * PSThreshold);
            Threshold = (ModelParsP->Pt3 * Pt3Threshold) * (ModelParsP->Pt3 * Pt3Threshold);
            /* Hard Faults detection algorithm */
            HardFault(Pt3ResP->Model[i], Threshold, &Pt3ResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP, NumShiftsHard);
        }
        // /* Calculation of threshold */
        // Threshold = (ModelParsP->Pt3 * PSThreshold) * (ModelParsP->Pt3 * PSThreshold);
        // /* Hard Faults detection algorithm */
        // HardFault(Pt3ResP->Model[i], Threshold, &Pt3ResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP,  NumShiftsHard);
        /* Updates number of shifts for hard fault detection in next sensor */
        NumShiftsHard++;   
        
    }

    /*-------------------*/
    /* STATION 4 SENSORS */
    /*-------------------*/

    /* Tt4 Thermocouple*/
    for(i = 0; i < NumTt4Sens; i++)
    {    

        /*----------------------*/
        /* HARD FAULT DETECTION */
        /*----------------------*/

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsHard, HardFAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Hard fault threshold */
            //Threshold = (ModelParsP->Tt4 * TCThreshold) * (ModelParsP->Tt4 * TCThreshold);
            Threshold = (ModelParsP->Tt4 * Tt4Threshold) * (ModelParsP->Tt4 * Tt4Threshold);
            /* Hard fault detection */
            HardFault(Tt4ResP->Model[i], Threshold, &Tt4ResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP, NumShiftsHard);
        }
        // /* Hard fault threshold */
        // Threshold = (ModelParsP->Tt4 * TCThreshold) * (ModelParsP->Tt4 * TCThreshold);
        // /* Hard fault detection */
        // HardFault(Tt4ResP->Model[i], Threshold, &Tt4ResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP,  NumShiftsHard);
        NumShiftsHard++;        

    }

    /*-------*/
    /* SHAFT */
    /*-------*/

    /* RPM Sensors */
    for(i = 0; i < NumRPMSens; i++)
    {    

        /*----------------------*/
        /* HARD FAULT DETECTION */
        /*----------------------*/

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsHard, HardFAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Hard fault threshold */
            Threshold = (ModelParsP->RPM * RPMThreshold) * (ModelParsP->RPM * RPMThreshold);
            /* Hard fault detection */
            HardFault(RPMResP->Model[i], Threshold, &RPMResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP, NumShiftsHard);
        }
        // /* Hard fault threshold */
        // Threshold = (ModelParsP->RPM * RPMThreshold) * (ModelParsP->RPM * RPMThreshold);
        // /* Hard fault detection */
        // HardFault(RPMResP->Model[i], Threshold, &RPMResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP,  NumShiftsHard);
        NumShiftsHard++;        

    }

    /*--------------------*/
    /* LUBRICATION SYSTEM */
    /*--------------------*/

    /* Oil Pressure sensors */
    for(i = 0; i < NumPOilSens; i++)
    {    
        
        /*----------------------*/
        /* HARD FAULT DETECTION */
        /*----------------------*/

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsHard, HardFAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Hard fault threshold */
            // Threshold = (ModelParsP->POil * PSThreshold) * (ModelParsP->POil * PSThreshold);
            Threshold = (ModelParsP->POil * POilThreshold) * (ModelParsP->POil * POilThreshold);
            /* Hard fault detection */
            HardFault(POilResP->Model[i], Threshold, &POilResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP, NumShiftsHard);
        }
        // /* Hard fault threshold */
        // //Threshold = (ModelParsP->POil * PSThreshold) * (ModelParsP->POil * PSThreshold);
        // Threshold = (ModelParsP->POil * POilThreshold) * (ModelParsP->POil * POilThreshold);
        // /* Hard fault detection */
        // HardFault(POilResP->Model[i], Threshold, &POilResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP,  NumShiftsHard);
        NumShiftsHard++;  

    }

    /*-------------*/
    /* FUEL SYSTEM */
    /*-------------*/

    /* PFuel Sensor */
    for(i = 0; i < NumPFuelSens; i++)
    {    

        /*----------------------*/
        /* HARD FAULT DETECTION */
        /*----------------------*/

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsHard, HardFAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Hard fault threshold */
            // Threshold = (ModelParsP->PFuel * PSThreshold) * (ModelParsP->PFuel * PSThreshold);
            Threshold = (ModelParsP->PFuel * PFuelThreshold) * (ModelParsP->PFuel * PFuelThreshold);
            /* Hard fault detection */
            HardFault(PFuelResP->Model[i], Threshold, &PFuelResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP, NumShiftsHard);
        }
        // /* Hard fault threshold */
        // // Threshold = (ModelParsP->PFuel * PSThreshold) * (ModelParsP->PFuel * PSThreshold);
        // Threshold = (ModelParsP->PFuel * PFuelThreshold) * (ModelParsP->PFuel * PFuelThreshold);
        // /* Hard fault detection */
        // HardFault(PFuelResP->Model[i], Threshold, &PFuelResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP,  NumShiftsHard);
        NumShiftsHard++;  

    }

    /*-----------*/
    /* VIBRATION */
    /*-----------*/

    /* Vibration Sensor */
    for(i = 0; i < NumVibrationSens; i++)
    {    

        /*-----------------------*/
        /* HARD FAULTS DETECTION */
        /*-----------------------*/

        /* Verifies if fault analysis is authorized */
        BitIsTrue(NumShiftsHard, HardFAuthP->FaultBits, &BitAuthorize);
        /* Analyzes sensor fault oly if authorized */
        if (BitAuthorize == 1)
        {
            /* Hard fault threshold */
            Threshold = (ModelParsP->Vibration * VibThreshold) * (ModelParsP->Vibration * VibThreshold);
            /* Hard fault detection */
            HardFault(VibrationResP->Model[i], Threshold, &VibrationResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP, NumShiftsHard);
        }
        // /* Hard fault threshold */
        // Threshold = (ModelParsP->Vibration * VibThreshold) * (ModelParsP->Vibration * VibThreshold);
        // /* Hard fault detection */
        // HardFault(VibrationResP->Model[i], Threshold, &VibrationResP->HardCount[i], ModelParsP->MaxInter, HardFStatusP, HardFWarningP,  NumShiftsHard);
        NumShiftsHard++;   
        
    }

}

/*******************************************************************************
 *
 *	FUNCTION:		TBearControl()
 *
 *	PURPOSE:		Controls bearings temperatures
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		-
 *
 *	RETURNS:		None
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void TBearControl(struct ControllerGeneral *ContGenOilP, struct ControllerGeneral *ContGenEmptyP, EngineStatus *EngStatusP, struct ControllerConstants *ContConstP, struct SensedPars *SensorsP, double ManualRef, double RPM, int AutoMode, double Ts)

{
    /*-----------------------*/
    /* OIL PUMP CONTROL LAW */
    /*-----------------------*/

    /* PARTIAL STATUS TABLE */

    // 1 - Initialize
    // 2 - Windmilling
    // 4 - Ready To Start
    // 8 - Starting
    // 16 - Idle
    // 32 - Regime

    /* If engine is not yet at idle speed, oil control must not be active yet */
    if (EngStatusP->EngineStatus < 16 & AutoMode == 1)
    {
        /* Controller output receives miminum oil pump RPM value */
        ContGenOilP->uOut[0] = ContConstP->OPRPMMin;

        /* The minimum value for oil pump RPM increases if RPM is higher than a determined value */
        if (RPM >= ContConstP->RPMOilInt)
        {
            ContGenOilP->uOut[0] = ContConstP->OPRPMInt; // OPRPMInt;
        }

    }
    

    /* The current Status must be higher than Idle and AutoMode must be 1 (automatic oil control) in order for PIOil to be used */
    if (EngStatusP->EngineStatus >= 16 & AutoMode == 1)
    {

        /* Updates Controller Inputs */
        for (int i = 0; i < ContConstP->NumBear; i++)
        {
            /* code */
            ContGenOilP->Ref[i] = ContConstP->TRefBear[i]; // RefTBear[i];
            ContGenOilP->Input[i] = SensorsP->TBear[i];    // TBear[i];
            ContGenOilP->Kp[i] = ContConstP->KpBear;       // KpOil;
            ContGenOilP->Ki[i] = ContConstP->KiBear;       // KiOil;
            ContGenOilP->Kb[i] = ContConstP->KbBear;       // KbOil;
            ContGenOilP->uMax[i] = ContConstP->OPRPMMax;   // OPRPMMax;
            ContGenOilP->uMin[i] = ContConstP->OPRPMMin;   // OPRPMMin;
            ContGenOilP->NumContVar = ContConstP->NumBear; // NumBearings;
            ContGenOilP->Ts = Ts;

            /* The minimum value for oil pump RPM increases if RPM is higher than a determined value */
            if (RPM >= ContConstP->RPMOilInt)
            {
                ContGenOilP->uMin[i] = ContConstP->OPRPMInt;   // OPRPMInt;
            }
            

        }

        PIOil(ContGenOilP);

    }
    /* If manual oil control is used, an external reference the fuel pump signal receives a manual RPM reference */
    if (AutoMode != 1)
    {        
        /* If LeverMode is different from 1, the oil is controlled manually */
        ContGenOilP->uOut[0] = ManualRef;
    }

    /*-----------------------------------------*/
    /* CONDITION FOR OIL PUMP TO BECOME ACTIVE */
    /*-----------------------------------------*/

    if (RPM < ContConstP->RPMOilOn & AutoMode == 1)
    {
        *ContGenOilP = *ContGenEmptyP;
    }
}

/*******************************************************************************
 *
 *	FUNCTION:		Tt2Calc()
 *
 *	PURPOSE:		Calculates values of static and total temperatures as well
 *                  day temperature variation
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double Ts2, struct EstimatedPars *ModelParsP, struct InterpIndex3D *Index3DP
 *
 *	RETURNS:		None
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void Tt2Calc(double Ts2, struct EstimatedPars *ModelParsP)

{
            
    /* Ambient static temperature */
    double dT;   
    double gamma = ModelParsP->gamma_air;
    double MN = ModelParsP->MN;
    double TRatio;
    double Ts2Std = ModelParsP->Ts2Std;
    double Tt2;   
    double Tt2StdSL;
    
    
    /* In case the calculated value of Ts2 is too low and has no 
    physical meaning, what may happen in the very first calculations due
    to measurement lack, the condition below avoids future division per
     zero when calculating theta*/
    if(Ts2 <= 0.5)
    {
        Ts2 = TSTD;
    }

    /* Calculation of dT */
    dT = Ts2 - Ts2Std;
    
    /* Calculates the ratio between total and static temperature as a functino of flight Mach number */
    TRatio = 1 + (gamma - 1) / 2 * MN * MN;
    
    /* Calculation of total inlet temperature */
    Tt2 = Ts2 * TRatio;
    
    /* Calculaton of Tt2 standard at sea level */
    Tt2StdSL = ModelParsP->Ts2StdSL * TRatio;//(*Ts0MtxP) * TRatio;
        
    /* Updates the dT value at the structure */
    ModelParsP->dT = dT;
    ModelParsP->Tt2 = Tt2;
    ModelParsP->Tt2StdSL = Tt2StdSL;
    
}

/*******************************************************************************
 *
 *	FUNCTION:		NozzleCalc()
 *
 *	PURPOSE:		Obtains the larger value between two variables (double)
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		a, b
 *
 *	RETURNS:		Value
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void NozzleCalc(struct EstimatedPars *ModelPars, struct ControllerConstants *ContConstP)
{
   
//    double WIn;     /* Input Flow [pps] 	*/
//    double htIn;     /* enthaply [BTU/lbm] 	*/
    double TtIn;     /* Temperature Input [degR] 	*/
    double PtIn;     /* Pressure Input [psia] 	*/
    double FARcIn;     /* Combusted Fuel to Air Ratio [frac] 	*/
    double PambIn;     /* Ambient Pressure [psia] 	*/
//    double AthroatIn;     /* Throat area [in2] 	*/
//    double AexitIn;     /* Exit area [in2] 	*/
    
	/* Define used matrices */
//	double X_A_AltVec[15] = { -5000, 0, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 60000, 70000, 80000 };
//	double T_A_TsVec[15] = { 536.51, 518.67, 500.84, 483.03, 465.22, 447.41, 429.62, 411.84, 394.06, 389.97, 389.97, 389.97, 389.97, 392.25, 397.69 };
//	double T_A_PsVec[15] = { 17.554, 14.696, 12.228, 10.108, 8.297, 6.759, 5.461, 4.373, 3.468, 2.73, 2.149, 1.692, 1.049, 0.651, 0.406 };
//	double FAR = 0;
	//double Rt = 0.0686;
	//double gammasg = 1.4;
//	double Y_N_FARVec[7] = {0, 0.0050, 0.0100, 0.0150, 0.0200, 0.0250, 0.0300};
//	double T_N_RtArray[7] = {0.0686, 0.0686, 0.0686, 0.0686, 0.0686, 0.0686, 0.0686};
//	double T_N_MAP_gammaArray[14] = {1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4};
//	double X_N_TVec[20] = {300, 10000};

    /*--------Define Constants-------*/
    double choked, Ts, rhos, V, Ptin;// Test, MN1, Ptin;
    double CdTh, Cv, Cfg;//, Therm_growth;
    double PQPa, PQPaMap;//, AthroatHot;
    double Rt, TsMN1, PsMN1;//, Woutcalc;
    double WOut, FgOut;//, NErrorOut;
    double Ath, Vth, Psth;//, Ax, Vx, Psx, Tsx, gammasx, MNx;
    double gammatg, gammasth,gammasMN1, gammasg, MNg, TsMNg, PsMNg, PsMNg_new, PsMNg_old, VMN1;
    double MNth, Tsth, rhosth, rhosMN1;//, rhosx;
//    double Axcalc, Psxg, Psxg_new, Psxg_old, Exthr;
//    double Athcalc, Psthg, Psthg_new, Psthg_old;
    double Sin, hsg, hs, htin, rhosg, Rs, Vg;
    double gammas_s, MN_s, V_s, rhos_s, Ts_s;
//    double Ex, Ex_old;
    double erMN_old, erMN, erthr;
    int maxiter, iter;//, maxiterx, iterx, CDNoz;
//    int interpErr = 0;
        
	/* Reads Inputs */
	PtIn = ModelPars->Pt5;
	TtIn = ModelPars->Tt5;
	FARcIn = ModelPars->Wf / ModelPars->W5;
	WOut = ModelPars->W5;
	PambIn = ModelPars->Ps2;
	Ath = ContConstP->Ath;

	/* Converts to American Units for using TMATS software directly */
	PtIn = PtIn * P_GIn;
	TtIn = TtIn * T_GIn;
	WOut = WOut * W_GIn;
	Ath = Ath * Area_GIn;
	PambIn = PambIn * P_GIn;

    /* Calc entropy */
    Sin = pt2sc(PtIn, TtIn, FARcIn);
    
    /*-- Compute Input enthalpy --------*/
    htin = t2hc(TtIn,FARcIn);
	Rt = 0.0686;
    Rs = Rt;
	
    
    
    /* Warn if there is the potential for back flow */
    Ptin = PtIn;
    /* Determine ideal velocity defined by perfect expansion to Pambient */
    PcalcStat(Ptin, PambIn, TtIn, htin, FARcIn, Rt, &Sin, &Ts, &hs, &rhos, &V);
	gammas_s = 1.4;
    MN_s = V*divby(sqrtT(gammas_s*Rs*Ts*C_GRAVITY*JOULES_CONST));
    Ts_s = Ts;
    V_s = V;
    rhos_s = rhos;
    
    
    /* Determine if nozzle throat is choked by comparing pressure when MN = 1 to ambient pressure
     * ---- set MN = 1 and calc throat Ps for iteration IC --------*/
    MNg = 1;
	gammatg = 1.4;
    /* use isentropic equations for a first cut guess */
    TsMNg = TtIn*divby(1+MNg*MNg*(gammatg-1)/2);
    PsMNg = Ptin*powT((TsMNg*divby(TtIn)),(gammatg*divby(gammatg-1)));
    
    /* Calculate velcocity and MN using guessed static pressure */
    PcalcStat(Ptin, PsMNg, TtIn, htin, FARcIn, Rt, &Sin, &TsMNg, &hsg, &rhosg, &Vg);
	gammasg = 1.4;
    MNg = Vg*divby(sqrtT(gammasg*Rs*TsMNg*C_GRAVITY*JOULES_CONST));
    
    /* determine error based on calculated MN and 1 */
    erMN =1 - MNg;
    
    PsMNg_new = PsMNg + 0.05;
    maxiter = 200;
    iter = 0;
    erthr = 0.001;
    
    /* if Ps is not close enough to Ps at MN = 1, iterate to find Ps at MN = 1 */
    while (fabs(erMN) > erthr && iter < maxiter) {
        erMN_old = erMN;
        PsMNg_old = PsMNg;
        if(fabs(PsMNg - PsMNg_new) < 0.003)
            PsMNg = PsMNg + 0.005;
        else
            PsMNg = PsMNg_new;
        PcalcStat(Ptin, PsMNg, TtIn, htin, FARcIn, Rt, &Sin, &TsMNg, &hsg, &rhosg, &Vg);
		gammasg = 1.4;
        MNg = Vg*divby(sqrtT(gammasg*Rs*TsMNg*C_GRAVITY*JOULES_CONST));
        erMN =1 - MNg;
        if (fabs(erMN) > erthr) {
            /* determine next guess pressure by secant algorithm */
            PsMNg_new = PsMNg - erMN *(PsMNg - PsMNg_old)*divby(erMN - erMN_old);
        }
        iter = iter + 1;
    }
 
    TsMN1 = TsMNg;
    PsMN1 = PsMNg;
    rhosMN1 = rhosg;
    gammasMN1 = gammasg;
    VMN1 = Vg;
    
    /* Determine if Nozzle is choked  */
    if (PsMN1<PambIn)
        choked = 0;
    else {
        choked = 1;
    }
    
    /* throat not choked, set Psth to ideal expansion to Pambient values */
    if (choked ==0){
        Psth = PambIn;
        Tsth = Ts_s;
        Vth = V_s;
        rhosth = rhos_s;
        MNth = MN_s;
    }
    
    else{  /* If nozzle is choked, determine throat parameters based on MN = 1 values */
        Psth = PsMN1;
        Tsth = TsMN1;
        MNth = 1;
		gammasth = 1.4;
     
        Vth = MNth*sqrtT(gammasth*Rs*Tsth*C_GRAVITY*JOULES_CONST);
        rhosth = rhosMN1;
    }
      
    /* Pressure before nozzle/P ambient */
    PQPa = Ptin*divby(PambIn);
    
    /* cacluate Thermal Constants */
    PQPaMap = PQPa;
    
    /* look up Flow Coefficient */
	CdTh = 1;
    
	Cv = 1;
	Cfg = 0.99;

	FgOut = (WOut / C_GRAVITY)*Vth*Cv + (Psth - PambIn)*Ath;

	/* Updates Outputs */
	ModelPars->MNth = MNth;
	ModelPars->Fg = FgOut * Thrust_GOut;
	ModelPars->Vjet = Vth * Alt_GOut;
    
}

/*******************************************************************************
 *
 *	FUNCTION:		ModelCalc()
 *
 *	PURPOSE:		Obtains the larger value between two variables (double)
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		a, b
 *
 *	RETURNS:		Value
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void ModelCalc(struct EstimatedPars *ModelParsP,double *DeltaMtxP,
                 double *AltLinVecP, double *MNLinVecP, struct ControllerConstants *ContConstP,
                 double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP, 
                 double *DeltaMtx2DP, double *DeltaMtx2DHP, double *DeltaMtx1DP, double *DeltaMtx1DHP, 
                 double *NcMtxP, double *Tt4MtxP, double *Pt3MtxP,
                 double *AMtxP, double *BMtxP, double *Tt4DMtxP, double *Pt3DMtxP,
                 double *WfMtxP, double *Ts0Mtx,
                 double *Pt5MtxP, double *Pt5DMtxP, double *Tt5MtxP, double *Tt5DMtxP,
                 double *NcHPCMapMtxP, double *WcHPCMapMtxP, double *PRHPCMapMtxP,
                 double *MapHPC1DP, double *MapHPC1DHP, double *MapHPC2DP, double *MapHPC2DHP)
{

    /* Elements numbers */
    int Alt_Elem = ContConstP->Alt_Elem;
    int MN_Elem = ContConstP->MN_Elem;
    int Fn_Elem = ContConstP->Fn_Elem;
    int NcHPCMAP_Elem = ContConstP->NcHPCMAP_Elem;
    int WcHPCMAP_Elem = ContConstP->WcHPCMAP_Elem;
    int Wc_per_Nc_HPCMAP = ContConstP->Wc_per_Nc_HPCMAP;

    /* Number of elements of gains and thrust elements */
	double NumEl2D = MN_Elem * Fn_Elem;
	double NumEl1D = Fn_Elem;
    
    /* Number of elements of delta matrix */
    double DeltaNumEl2D = Alt_Elem * MN_Elem;
    double DeltaNumEl1D = MN_Elem;

	//Declares pointer for 3D interpolation indexes
	InterpIndex3D Index3D;
    InterpIndex3D Index3DDelta;

	/*-------------------------*/
	/*  ENGINE MODEL VARIABLES */
	/*-------------------------*/
	    
	/* Declared Internal Variables */
    
    /* Loop index */
    int i;
    
    /* Air constants */
    double gamma_air = 1.4;
    double R_air = 287;
    
    /* Number of integration steps */
    double NumSteps = ModelParsP->NumSteps;
    
    /* Sampling Time */
    double Ts = (ModelParsP->Ts) / NumSteps;
    
    /* Ambient */
    double Altitude = ModelParsP->Altitude;
    double MN = ModelParsP->MN;
//    double dT = ModelParsP->dT;
    double VSound;
    double VFlight;

	/* Station 2 */
    double Pt2;
    double Ps2 = ModelParsP->Ps2;
    double Ts2 = ModelParsP->Ts2;
    double Ts2Sensed = ModelParsP->Ts2Sensed;
    double Tt2 = ModelParsP->Tt2;
	double Tt2SL = ModelParsP->Tt2StdSL;
	double N2c;
    double WcHPC;
    double W2;

	/* Station 3 */
    double PRHPC;
	double Pt3;
    double Pt3Sensed = ModelParsP->Pt3Sensed;
	/* Station 4 */
	double Tt4;
    double Tt4Sensed = ModelParsP->Tt4Sensed;
    double Wf;                              /* Variable used for model estimation */
    double WfIn = ModelParsP->Wf;           /* Controller signal */
    double WfOutfp = ModelParsP->WfOutfp;
    /* Station 5 */
    double W5;
    double Pt5;
    double Tt5;
    /* Station 8 */
    double Ath = ContConstP->Ath;
    double MFP;
	/* Shaft design rotation speed */
	double RPM = ModelParsP->RPM; 
    double NDes = ContConstP->NDes;
    // double NDes = TJ1200_NDES;

	/* Correction parameters */
	double Theta = 0;
	double Delta = 0;
	double ThetaSL = 0;
	double DeltaSL = 0;
	double sqrTheta = 0;
	double sqrThetaSL = 0;
    double DeltaStatic = 0;

	/* Dummy Constant */
	double DummyConst = 0;

	/*State-Space Variables*/
	double A;
	double Attc = ContConstP->TTCTimeConst;
	double Apsens = ContConstP->PSensTimeConst;
	double Afp = ContConstP->FuelPumpTimeConstant;
	double B;
	double Bttc = -1 * ContConstP->TTCTimeConst;
	double Bpsens = -1 * ContConstP->PSensTimeConst;
	double Bfp = -1 * ContConstP->FuelPumpTimeConstant;
	double Ad;
	double Adttc;
	double Adpsens;
	double Adfp;
	double Bd;
	double Bdttc;
	double Bdpsens;
	double Bdfp;
	double Pt3D;
	double Pt3ss;
	double Pt5D;
	double Pt5ss;
	double Tt4D;
	double Tt4ss;
	double Tt5D;
	double Tt5ss;
	double Wfss;

	/* Correction Matrices for Sea-Level */
	double PNSL;
	double PNdotSL;
	double PuSL;
	double PTSL;
	double PPSL;

	/* Correction Matrices for current altitude */
	double PN;
	double PNdot;
	double Pu;
	double PT;
	double PP;

//	int kAux;
//	int kHAux;
//	int fAux;
    
    for(i = 1; i <= NumSteps; i++)
    {

        /* FUEL PUMP FIRST ORDER MODEL */

        /* Calculation of discrete coefficients - fuel pump */
        Adfp = exp(Afp * Ts);
        Bdfp = (Adfp - 1) * Bfp / Afp;

        /* The routine FirstOrderSensor performs a 1st order filter and is suitable to be used
        with sensors and fuel pump first order models */
        FirstOrderSensor(WfIn, &WfOutfp, Bdfp);

        /* Updates Wf for taking into account fuel pump dynamics */
        Wf = WfOutfp;

        /* AMBIENT CALCULATIONS */

        /* Calculates the values of Theta and Delta */
        Theta = Tt2 / TSTD;
        ThetaSL = Tt2SL / TSTD;
        
        /* Calculates the squred root of the theta values */
        sqrTheta = sqrt(Theta);
        sqrThetaSL = sqrt(ThetaSL);
        
        /* Calculates the Value of N2c */
        N2c = RPM / sqrTheta;
        N2c = N2c / NDes;
        
        /* FINDS THE VALUE OF THE STATIC PRESSURE */

        /* Gets the indexes of Altitude and MN = 0 with a fake Fnpc value suitable for using InterpInd3DRPM */
        // InterpInd3DRPM(Altitude, 0, N2c, AltLinVecP, MNLinVecP, NcMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, TJ1200_ALT_ELEM, TJ1200_MN_ELEM, TJ1200_FN_ELEM, &Index3D);
        InterpInd3DRPM(Altitude, 0, N2c, AltLinVecP, MNLinVecP, NcMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Alt_Elem, MN_Elem, Fn_Elem, &Index3D);

        /* Shifts the indexes of Index3D for finding a 2D element */
        Index3DDelta.kRPM = Index3D.kMN;
        Index3DDelta.kRPMH = Index3D.kMNH;
        Index3DDelta.fRPM = Index3D.fMN;
        Index3DDelta.kMN = Index3D.kA;
        Index3DDelta.kMNH = Index3D.kAH;
        Index3DDelta.fMN = Index3D.fA;
        Index3DDelta.kA = 0;
        Index3DDelta.kAH = 0;
        Index3DDelta.fA = 0;

        /* Find the value of Delta */
        DeltaStatic = InterpValue(&Index3DDelta, DeltaMtxP, DeltaMtx2DP, DeltaMtx2DHP, DeltaMtx1DP, DeltaMtx1DHP, DeltaNumEl2D, DeltaNumEl1D);
        
        /* Finds the value of the ambient pressure */
        Ps2 = DeltaStatic * PSTD;

        /* FINDS THE VALUE OF THE TOTAL PRESSURE AND SEA LEVEL DELTA */

        /* Gets the indexes of Altitude and MN with a fake Fnpc value suitable for using InterpInd3DRPM */
        // InterpInd3DRPM(Altitude, MN, N2c, AltLinVecP, MNLinVecP, NcMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, TJ1200_ALT_ELEM, TJ1200_MN_ELEM, TJ1200_FN_ELEM, &Index3D);
        InterpInd3DRPM(Altitude, MN, N2c, AltLinVecP, MNLinVecP, NcMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Alt_Elem, MN_Elem, Fn_Elem, &Index3D);
        
        /* Shifts the indexes of Index3D for finding a 2D element */
        Index3DDelta.kRPM = Index3D.kMN;
        Index3DDelta.kRPMH = Index3D.kMNH;
        Index3DDelta.fRPM = Index3D.fMN;
        Index3DDelta.kMN = Index3D.kA;
        Index3DDelta.kMNH = Index3D.kAH;
        Index3DDelta.fMN = Index3D.fA;
        Index3DDelta.kA = 0;
        Index3DDelta.kAH = 0;
        Index3DDelta.fA = 0;
        
        /* Find the value of Delta */
        Delta = InterpValue(&Index3DDelta, DeltaMtxP, DeltaMtx2DP, DeltaMtx2DHP, DeltaMtx1DP, DeltaMtx1DHP, DeltaNumEl2D, DeltaNumEl1D);
    //printf("Delta = %f, Theta = %f, Tt2 = %f\n", Delta, Theta, Tt2);
        /* Calculates the value of Pt2 from Delta */
        Pt2 = Delta * PSTD;
        
        /* Shifts the indexes of Index3D for finding a 2D element */
        Index3DDelta.kRPM = Index3D.kMN;
        Index3DDelta.kRPMH = Index3D.kMNH;
        Index3DDelta.fRPM = Index3D.fMN;
        Index3DDelta.kMN = 0;
        Index3DDelta.kMNH = 0;
        Index3DDelta.fMN = 0;
        Index3DDelta.kA = 0;
        Index3DDelta.kAH = 0;
        Index3DDelta.fA = 0;
        
        /* Find the value of Delta */
        DeltaSL = InterpValue(&Index3DDelta, DeltaMtxP, DeltaMtx2DP, DeltaMtx2DHP, DeltaMtx1DP, DeltaMtx1DHP, DeltaNumEl2D, DeltaNumEl1D);
        
//         /* Calculates the squred root of the theta values */
//         sqrTheta = sqrt(Theta);
//         sqrThetaSL = sqrt(ThetaSL);
        
        /* CALCULATION OF CORRECTION COEFFICIENTS */

        /* Calculates the correction matices for sea-level */
        PNSL = sqrThetaSL;
        PNdotSL = DeltaSL;
        PuSL = DeltaSL * sqrThetaSL;
        PTSL = ThetaSL;
        PPSL = DeltaSL;
        
        /* Calculates the correction matices for sea-level */
        PN = sqrTheta;
        PNdot = Delta;
        Pu = Delta * sqrTheta;
        PT = Theta;
        PP = Delta;
        
        /* MODEL CALCULATIONS */

        /* Calculates the Value of N2c */
        N2c = RPM / sqrTheta;
        N2c = N2c / NDes;
        
        /* CALCULATION OF PARAMETERS USED IN MODEL */
        
        /* Finds 3D indexes necessary for interpolation of controller gains */
        InterpInd3DRPM(DummyConst, MN, N2c, &DummyConst, MNLinVecP, NcMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, DUMMY_ELEM, MN_Elem, Fn_Elem, &Index3D);
        NumEl2D = MN_Elem * Fn_Elem;
        NumEl1D = Fn_Elem;
    //printf("Indexes: %f, %f, %f, %f, %f, %f, %f, %f, %f\n", Index3D.kA, Index3D.kAH, Index3D.fA, Index3D.kMN, Index3D.kMNH, Index3D.fMN, Index3D.kRPM, Index3D.kRPMH, Index3D.fRPM);
        /* Calculates parameters used in model */
        B = InterpValue(&Index3D, BMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
        A = InterpValue(&Index3D, AMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
        Pt3D = InterpValue(&Index3D, Pt3DMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
        Pt5D = InterpValue(&Index3D, Pt5DMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
        Tt4D = InterpValue(&Index3D, Tt4DMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
        Tt5D = InterpValue(&Index3D, Tt5DMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
        Pt3ss = InterpValue(&Index3D, Pt3MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
        Pt5ss = InterpValue(&Index3D, Pt5MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
        Tt4ss = InterpValue(&Index3D, Tt4MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
        Tt5ss = InterpValue(&Index3D, Tt5MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
        Wfss = InterpValue(&Index3D, WfMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
//printf("Antes: Tt4D = %f\n",Tt4D);
        /* Corrects the calculated parameters for sea level and corresponding MN */
        B = 1/PNdotSL * B * PuSL;
        A = 1/PNdotSL * A * PNSL;
        Pt3D = 1 / PPSL * Pt3D * PuSL;
        Pt5D = 1 / PPSL * Pt5D * PuSL;
        Tt4D = 1 / PTSL * Tt4D * PuSL;
        Tt5D = 1 / PTSL * Tt5D * PuSL;
        Pt3ss = Pt3ss / PPSL;
        Pt5ss = Pt5ss / PPSL;
        Tt4ss = Tt4ss / PTSL;
        Tt5ss = Tt5ss / PTSL;
        Wfss = Wfss / PuSL;
//printf("Meio: Tt4D = %f\n",Tt4D);
        /* Calculates the absolute values from the corresponding corrected values*/
        B = PNdot * B / Pu;
        A = PNdot * A / PN;
        Pt3D = PP * Pt3D / Pu;
        Pt5D = PP * Pt5D / Pu;
        Tt4D = PT * Tt4D / Pu;
        Tt5D = PT * Tt5D / Pu;
        Pt3ss = Pt3ss * PP;
        Pt5ss = Pt5ss * PP;
        Tt4ss = Tt4ss * PT;
        Tt5ss = Tt5ss * PT;
        Wfss = Wfss * Pu;
//printf("Depois: Tt4D = %f\n",Tt4D);
        /* Calculation of discrete coefficients */
        Ad = exp(A * Ts);
        Bd = (Ad - 1) * B / A;

        /* Calculation of discrete coefficients - sensors */
        Adttc = exp(Attc * Ts);
        Bdttc = (Adttc - 1) * Bttc / Attc;

        /* Calculation of discrete coefficients - sensors */
        Adpsens = exp(Apsens * Ts);
        Bdpsens = (Adpsens - 1) * Bpsens / Apsens;

        /* CALCULATION OF STATE VARIABLE */

        RPM = RPM + Bd * (Wf - Wfss);
        
        /* CALCULATION OF OBSERVED VARIABLES */
//printf("Tt4 = %f + %f * (%f-%f) = ", Tt4ss, Tt4D, Wf, Wfss);
        Pt3 = Pt3ss + Pt3D * (Wf - Wfss);
        Pt5 = Pt5ss + Pt5D * (Wf - Wfss);
        Tt4 = Tt4ss + Tt4D * (Wf - Wfss);
        Tt5 = Tt5ss + Tt5D * (Wf - Wfss);
//printf("%f\n", Tt4);
        /* CALCULATION OF TOTAL MASS FLOW */

        /* Calculates pressure ratio */
        PRHPC = Pt3 / Pt2;

        /* Calculates the corrected mass flow from fan map */
        InterpInd3DRPM(DummyConst, N2c, PRHPC, &DummyConst, NcHPCMapMtxP, PRHPCMapMtxP, MapHPC2DP, MapHPC2DHP, MapHPC1DP, MapHPC1DHP, DUMMY_ELEM, NcHPCMAP_Elem, Wc_per_Nc_HPCMAP, &Index3D);
        WcHPC = InterpValue(&Index3D, WcHPCMapMtxP, MapHPC2DP, MapHPC2DHP, MapHPC1DP, MapHPC1DHP, WcHPCMAP_Elem, Wc_per_Nc_HPCMAP);
        
        /* Calculates the compressor inlet mass flow */
        W2 = WcHPC * Delta / sqrTheta;
        /* Calculates the total Mass flow */        
        W5 = W2 + Wf;    
        /* Calculation of MFP */
        MFP = W5 * sqrt(Tt5) / Pt5 / Ath;

        /* Updates sensor values */
        FirstOrderSensor(Ts2, &Ts2Sensed, Bdttc);
        FirstOrderSensor(Pt3, &Pt3Sensed, Bdpsens);
        FirstOrderSensor(Tt4, &Tt4Sensed, Bdttc);

// printf("Ts2Sensed = %f + %f * (%f - %f)\n", Ts2Sensed, Bdttc, Ts2Sensed, Ts2);
// printf("Pt3Sensed = %f + %f * (%f - %f)\n", Pt3Sensed, Bdpsens, Pt3Sensed, Pt3);
//printf("Tt4Sensed = %f + %f * (%f - %f)\n", Tt4Sensed, Bdttc, Tt4Sensed, Tt4);

        // /* Updates Ts2 for takin into account sensor dynamics */
        // Ts2 = Ts2Sensed;
        // Pt3 = Pt3Sensed;
        // Tt4 = Tt4Sensed;

        /* UPDATES MODELPARS STRUCT */

        ModelParsP->Ts2Sensed = Ts2Sensed;
        ModelParsP->RPM = RPM;
        ModelParsP->Ps2 = Ps2;
        ModelParsP->Pt2 = Pt2;
        ModelParsP->Pt3 = Pt3;
        ModelParsP->Pt3Sensed = Pt3Sensed;
        ModelParsP->Pt5 = Pt5;
        ModelParsP->Tt4 = Tt4;
        ModelParsP->Tt4Sensed = Tt4Sensed;
        ModelParsP->Wf = Wf;
        ModelParsP->WfOutfp = WfOutfp;
        ModelParsP->Tt5 = Tt5;
        ModelParsP->W5 = W5;
        ModelParsP->MFP = MFP;

        /* NET THRUST CALCULATION */

        /* Calculates nozzle parameters */
        NozzleCalc(ModelParsP, ContConstP);

        /* Calculates ambient sound speed and flight speed */
        VSound = sqrt(gamma_air * R_air * Ts2);
        VFlight = VSound * MN;

        /* Calculates net thrust */
        ModelParsP->Fn = ModelParsP->Fg - W2 * VFlight;
        
    }

    /* Updates Ts2 for takin into account sensor dynamics */
    ModelParsP->Ts2 = ModelParsP->Ts2Sensed;
    ModelParsP->Pt3 = ModelParsP->Pt3Sensed;
    ModelParsP->Tt4 = ModelParsP->Tt4Sensed;

    /* Updates bearings temperatures with fixed values (maximum allowed value) */
    ModelParsP->TBear[0] = ContConstP->TMaxBear[0];
    ModelParsP->TBear[1] = ContConstP->TMaxBear[1];
    ModelParsP->TBear[2] = ContConstP->TMaxBear[2];

}


// /*******************************************************************************
//  *
//  *	FUNCTION:		PIControl()
//  *
//  *	PURPOSE:		Calculates control signal and integral term with back
//  *                   calculation protection
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		Ki, Kp, Kb, Ts, Ik1, ek, ek1, ebk1, *PIOutP
//  *
//  *	RETURNS:		PIOutP
//  *
//  *	COMMENTS:       Rules for variable name: type_varname or type_VN
//  *
//  *******************************************************************************/

// void ResMin(AllResiduals *Residuals)
// {
// //     /* If Ts2 0 SCV fault was detected, model value must be used */
// //     if(FaultWarningP->Faults.Ts2_0_SCV)
// //     {
// //         
// //     }
    
    
// //         /* Normal operation */
// //     DefaultP->Model[5] = 1000000;
// //     /* Short-Circuit with Vcc - Thermocouple Only */
// //     DefaultP->SCV[5] = 1000000; 
// //     DefaultP->SCVCount[5] = 0;
// //     /* Shorg-Circuit with GND - Thermocouple Only */
// //     DefaultP->SCG[5] = 1000000; 
// //     DefaultP->SCGCount[5] = 0;
// //     /* Short-Circuit - Sensors Only */
// //     DefaultP->Short[5] = 1000000; 
// //     DefaultP->ShortCount[5] = 0;
// //     /* Open-Circuit - Sensors and Thermocouples */
// //     DefaultP->Open[5] = 1000000;
// //     DefaultP->OpenCount[5] = 0;
// //     /* 1 Pulse Loss - RPM Sensor Only */
// //     DefaultP->PulseLoss1[5] = 1000000;
// //     DefaultP->PulseLoss1Count[5] = 0;
// //     /* 2 Pulses Loss - RPM Sensor Only */
// //     DefaultP->PulseLoss2[5] = 1000000;
// //     DefaultP->PulseLoss2Count[5] = 0;
// //     /* 3 Pulses Loss - RPM Sensor Only */
// //     DefaultP->PulseLoss3[5] = 1000000;
// //     DefaultP->PulseLoss3Count[5] = 0;
// //     /* Oil Choke */
// //     DefaultP->OilChoke[5] = 1000000;
// //     DefaultP->OilChokeCount[5] = 0;
// //     /* Oil Lack */
// //     DefaultP->OilLack[5] = 1000000;
// //     DefaultP->OilLackCount[5] = 0;
// //     /* Fuel Choke */
// //     DefaultP->FuelChoke[5] = 1000000;
// //     DefaultP->FuelChokeCount[5] = 0;
// //     /* Fuel Lack */
// //     DefaultP->FuelLack[5] = 1000000;
// //     DefaultP->FuelLackCount[5] = 0;
// //     /* Balde Loss */
// //     DefaultP->BladeLoss[5] = 1000000;
// //     DefaultP->BladeLossCount[5] = 0;
// //     /* Shaft Lock */
// //     DefaultP->ShaftLock[5] = 1000000;
// //     DefaultP->ShaftLockCount[5] = 0;

    
// }

// /*******************************************************************************
//  *
//  *	FUNCTION:		InitRes()
//  *
//  *	PURPOSE:		Calculates control signal and integral term with back
//  *                   calculation protection
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		Ki, Kp, Kb, Ts, Ik1, ek, ek1, ebk1, *PIOutP
//  *
//  *	RETURNS:		PIOutP
//  *
//  *	COMMENTS:       Rules for variable name: type_varname or type_VN
//  *
//  *******************************************************************************/

// void InitRes(struct AllResiduals *DefaultP)
// {

//     /* Internal variables */
//     int NumSensors = 5;
//     int NumPos = 20;
//     int i;
//     int j;
    
//     /* Initialization of residuals with high values */
//     for(i = 0; i <= NumSensors; i++)
//     {
//         /* Hard and soft faults counters */
//         DefaultP->HardCount[i] = 0;
//         DefaultP->SoftCount[i] = 0;
//         /* Normal operation */
//         DefaultP->Model[i] = 1000000;
//         /* Short-Circuit with Vcc - Thermocouple Only */
//         DefaultP->SCV[i] = 1000000;
//         DefaultP->SCVCount[i] = 0;
//         /* Shorg-Circuit with GND - Thermocouple Only */
//         DefaultP->SCG[i] = 1000000;
//         DefaultP->SCGCount[i] = 0;
//         /* Short-Circuit - Sensors Only */
//         DefaultP->Short[i] = 1000000;
//         DefaultP->ShortCount[i] = 0;
//         /* Open-Circuit - Sensors and Thermocouples */
//         DefaultP->Open[i] = 1000000;
//         DefaultP->OpenCount[i] = 0;
//         /* 1 Pulse Loss - RPM Sensor Only */
//         DefaultP->PulseLoss1[i] = 1000000;
//         DefaultP->PulseLoss1Count[i] = 0;
//         /* 2 Pulses Loss - RPM Sensor Only */
//         DefaultP->PulseLoss2[i] = 1000000;
//         DefaultP->PulseLoss2Count[i] = 0;
//         /* 3 Pulses Loss - RPM Sensor Only */
//         DefaultP->PulseLoss3[i] = 1000000;
//         DefaultP->PulseLoss3Count[i] = 0;
//         /*Blow Out*/
//         DefaultP->BlowOut[i] = 1000000;
//         DefaultP->BlowOutCount[i] = 0;
//         /* High */
//         DefaultP->High[i] = 1000000;
//         DefaultP->HighCount[i] = 0;
//         /* Low */
//         DefaultP->Low[i] = 1000000;
//         DefaultP->LowCount[i] = 0;
//         // /* Oil Choke */
//         // DefaultP->OilChoke[i] = 1000000;
//         // DefaultP->OilChokeCount[i] = 0;
//         // /* Oil Lack */
//         // DefaultP->OilLack[i] = 1000000;
//         // DefaultP->OilLackCount[i] = 0;
//         // /* Fuel Choke */
//         // DefaultP->FuelChoke[i] = 1000000;
//         // DefaultP->FuelChokeCount[i] = 0;
//         // /* Fuel Lack */
//         // DefaultP->FuelLack[i] = 1000000;
//         // DefaultP->FuelLackCount[i] = 0;
//         /* Balde Loss */
//         DefaultP->BladeLoss[i] = 1000000;
//         DefaultP->BladeLossCount[i] = 0;
//         /* Shaft Lock */
//         DefaultP->ShaftLock[i] = 1000000;
//         DefaultP->ShaftLockCount[i] = 0;
        
//         /* Fault Positions initialization */
//         for(j = 0; j <= NumPos; j++)
//         {
//             DefaultP->ResPosition[i][j] = NumPos;
//         }
        
//     }
 
// }

// /*******************************************************************************
//  *
//  *	FUNCTION:		UpdtEngStatus()
//  *
//  *	PURPOSE:		Updates engine status word accordint to operating conditions
//  *                  
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		
//  *
//  *	RETURNS:		PIOutP
//  *
//  *	COMMENTS:       Rules for variable name: type_varname or type_VN
//  *
//  *******************************************************************************/

// void UpdtEngStatus(EngineStatus *EngStatusP, struct ControlStart *ContStartP)
// {
//     /* Reads engine starting status */
//     int status = ContStartP->status;

//     /* Starts with null state */
//     EngStatusP->EngineStatus = 0;

//     switch (status)
//     {
//     case 0:
//         /* Indicates engine is at null status - zero rotation speed */
//         EngStatusP->EngStatusBist.Initialize = 1;
//         break;

//     case 1:
//         /* Indicates engine windmilling */
//         EngStatusP->EngStatusBist.Windmilling = 1;
//         break;

//     case 2:
//         /* Indicates engine windmilling */
//         EngStatusP->EngStatusBist.Windmilling = 1;
//         break;

//     default:
//         break;
//     }

// }

/*******************************************************************************
 *
 *	FUNCTION:		PrintingTest()
 *
 *	PURPOSE:		Prints the errors when occurring. Used just for testing of 
 *                  algorithms
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		PIOutP
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void PrintFaults(EngineFaults *FaultStatusP, int WhichPrint, int tUpdt)
{

    /* Initiates time with 0 s */
    static double t = 0;

    /* Updates time value */
    if(tUpdt == 1){t = t + TICK * 0.001;}

    if(FaultStatusP->FaultBits != 0)
    {
        if(WhichPrint == 1){
        printf("\n\n --------------------");
        printf("\n Fault Status - HIL");
        printf("\n --------------------\n");
        }
        else{
        printf("\n\n ---------------------");
        printf("\n Fault Warning - HIL");
        printf("\n ---------------------\n");
        }

        /* TS2 0 Faults */
        if(FaultStatusP->Faults.Ts2_0_Bias){ printf("\n Ts2 0 - Bias - at t = %f",t); }
        if(FaultStatusP->Faults.Ts2_0_SCV){ printf("\n Ts2 0 - SCV - at t = %f",t); }
        if(FaultStatusP->Faults.Ts2_0_SCG){ printf("\n Ts2 0 - SCG - at t = %f",t); }
        if(FaultStatusP->Faults.Ts2_0_Open){ printf("\n Ts2 0 - Open - at t = %f",t); }

        /*TS2 1 Faults*/
        if(FaultStatusP->Faults.Ts2_1_Bias){ printf("\n Ts2 1 - Bias - at t = %f",t); }
        if(FaultStatusP->Faults.Ts2_1_SCV){ printf("\n Ts2 1 - SCV - at t = %f",t); }
        if(FaultStatusP->Faults.Ts2_1_SCG){ printf("\n Ts2 1 - SCG - at t = %f",t); }
        if(FaultStatusP->Faults.Ts2_1_Open){ printf("\n Ts2 1 - Open - at t = %f",t); }

        /*Pt3 0 Faults*/
        if(FaultStatusP->Faults.Pt3_0_Bias){ printf("\n Pt3 0 - Bias - at t = %f",t); }
        if(FaultStatusP->Faults.Pt3_0_Open){ printf("\n Pt3 0 - Open - at t = %f",t); }
        if(FaultStatusP->Faults.Pt3_0_Short){ printf("\n Pt3 0 - Short - at t = %f",t); }

        /* Tt4 0 Faults */
        if(FaultStatusP->Faults.Tt4_0_Bias){ printf("\n Tt4 0 - Bias - at t = %f",t); }
        if(FaultStatusP->Faults.Tt4_0_SCV){ printf("\n Tt4 0 - SCV - at t = %f",t); }
        if(FaultStatusP->Faults.Tt4_0_SCG){ printf("\n Tt4 0 - SCG - at t = %f",t); }
        if(FaultStatusP->Faults.Tt4_0_Open){ printf("\n Tt4 0 - Open - at t = %f",t); }

        /* Tt4 1 Faults */
        if(FaultStatusP->Faults.Tt4_1_Bias){ printf("\n Tt4 1 - Bias - at t = %f",t); }
        if(FaultStatusP->Faults.Tt4_1_SCV){ printf("\n Tt4 1 - SCV - at t = %f",t); }
        if(FaultStatusP->Faults.Tt4_1_SCG){ printf("\n Tt4 1 - SCG - at t = %f",t); }
        if(FaultStatusP->Faults.Tt4_1_Open){ printf("\n Tt4 1 - Open - at t = %f",t); }

        /* Tt4 2 Faults */
        if(FaultStatusP->Faults.Tt4_2_Bias){ printf("\n Tt4 2 - Bias - at t = %f",t); }
        if(FaultStatusP->Faults.Tt4_2_SCV){ printf("\n Tt4 2 - SCV - at t = %f",t); }
        if(FaultStatusP->Faults.Tt4_2_SCG){ printf("\n Tt4 2 - SCG - at t = %f",t); }
        if(FaultStatusP->Faults.Tt4_2_Open){ printf("\n Tt4 2 - Open - at t = %f",t); }

        /* RPM 0 Faults */
        if(FaultStatusP->Faults.RPM_0_Bias){ printf("\n RPM 0 - Bias - at t = %f",t); }
        if(FaultStatusP->Faults.RPM_0_Short){ printf("\n RPM 0 - Short - at t = %f",t); }
        if(FaultStatusP->Faults.RPM_0_Open){ printf("\n RPM 0 - Open - at t = %f",t); }
        if(FaultStatusP->Faults.RPM_0_1PLoss){ printf("\n RPM 0 - 1 Pulse Loss - at t = %f",t); }
        if(FaultStatusP->Faults.RPM_0_2PLoss){ printf("\n RPM 0 - 2 Pulses Loss - at t = %f",t); }

        /* RPM 1 Faults */
        if(FaultStatusP->Faults.RPM_1_Bias){ printf("\n RPM 1 - Bias - at t = %f",t); }
        if(FaultStatusP->Faults.RPM_1_Short){ printf("\n RPM 1 - Short - at t = %f",t); }
        if(FaultStatusP->Faults.RPM_1_Open){ printf("\n RPM 1 - Open - at t = %f",t); }
        if(FaultStatusP->Faults.RPM_1_1PLoss){ printf("\n RPM 1 - 1 Pulse Loss - at t = %f",t); }
        if(FaultStatusP->Faults.RPM_1_2PLoss){ printf("\n RPM 1 - 2 Pulses Loss - at t = %f",t); }

        /* POil 0 Faults */
        if(FaultStatusP->Faults.POil_0_Bias){ printf("\n POil 0 - Bias - at t = %f",t); }
        if(FaultStatusP->Faults.POil_0_Open){ printf("\n POil 0 - Open - at t = %f",t); }
        if(FaultStatusP->Faults.POil_0_Short){ printf("\n POil 0 - Short - at t = %f",t); }

        /* PFuel 0 Faults */
        if(FaultStatusP->Faults.PFuel_0_Bias){ printf("\n PFuel 0 - Bias - at t = %f",t); }
        if(FaultStatusP->Faults.PFuel_0_Open){ printf("\n PFuel 0 - Open - at t = %f",t); }
        if(FaultStatusP->Faults.PFuel_0_Short){ printf("\n PFuel 0 - Short - at t = %f",t); }

        /* Vibration 0 Faults */
        if(FaultStatusP->Faults.Vib_0_Bias){ printf("\n Vib 0 - Bias - at t = %f",t); }
        if(FaultStatusP->Faults.Vib_0_Open){ printf("\n Vib 0 - Open - at t = %f",t); }
        if(FaultStatusP->Faults.Vib_0_Short){ printf("\n Vib 0 - Short - at t = %f",t); }

        /* TBear 0 Faults */
        if(FaultStatusP->Faults.TB_0_Open){ printf("\n TBear 0 - Open - at t = %f",t); }
        
        /* TBear 1 Faults */
        if(FaultStatusP->Faults.TB_1_Open){ printf("\n TBear 1 - Open - at t = %f",t); }

        /* TBear 2 Faults */
        if(FaultStatusP->Faults.TB_2_Open){ printf("\n TBear 2 - Open - at t = %f",t); }

        /* Lubrication System */
        if(FaultStatusP->Faults.POil_High){ printf("\n POil High - at t = %f",t); }
        if(FaultStatusP->Faults.POil_Low){ printf("\n POil Low - at t = %f",t); }

        /* Fuel System */
        if(FaultStatusP->Faults.PFuel_High){ printf("\n PFuel High - at t = %f",t); }
        if(FaultStatusP->Faults.PFuel_Low){ printf("\n PFuel Low - at t = %f",t); }

        /* Bearings */
        if(FaultStatusP->Faults.TBear_0_High){ printf("\n TBear 0 High - at t = %f",t); }
        if(FaultStatusP->Faults.TBear_1_High){ printf("\n TBear 1 High - at t = %f",t); }
        if(FaultStatusP->Faults.TBear_2_High){ printf("\n TBear 2 High - at t = %f",t); }
       

        /* Blow Out */
        if(FaultStatusP->Faults.BlowOut)
        { 
            printf("\n Engine Blow Out - at t = %f",t);
        }

        /* Mechanical failures */
        if(FaultStatusP->Faults.VibrationHigh){ printf("\n Vibration High - at t = %f",t); }
        if(FaultStatusP->Faults.Mec_Lock){ printf("\n Shaft Lock - at t = %f",t); }
        if(FaultStatusP->Faults.OverTemp){ printf("\n OverTemp - at t = %f",t); }
        if(FaultStatusP->Faults.OverSpeed){ printf("\n OverSpeed - at t = %f",t); }
        if(FaultStatusP->Faults.Ignition){ printf("\n Ignition - at t = %f",t); }
        if(FaultStatusP->Faults.CAN_0_Fault){ printf("\n CAN 0 - at t = %f",t); }
        if(FaultStatusP->Faults.CAN_1_Fault){ printf("\n CAN 1 - at t = %f",t); }

        printf("\n\n ------------ \n");

    }

}

/*******************************************************************************
 *
 *	FUNCTION:		PrintingTest()
 *
 *	PURPOSE:		Prints the errors when occurring. Used just for testing of 
 *                  algorithms
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		
 *
 *	RETURNS:		PIOutP
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

void PrintEngStatus(EngineStatus *EngStatusP, int tUpdt)
{

    /* Initiates time with 0 s */
    static double t = 0;

    /* Updates time value */
    if(tUpdt == 1){t = t + TICK * 0.001;}

    if (EngStatusP->EngineStatus != 0)
    {
        /* code */
        printf("\n\n ---------------------");
        printf("\n Engine Status - HIL");
        printf("\n --------------------\n");

        printf("\n Engtine Status Number: %d", EngStatusP->EngineStatus);

        /* TS2 0 Faults */
        if (EngStatusP->EngStatusBist.Degraded)
        {
            printf("\n Engtine Status: DEGRADED - at t = %f", t);
        }
        if (EngStatusP->EngStatusBist.Emergency)
        {
            printf("\n Engtine Status: EMERGENCY - at t = %f", t);
        }
        if (EngStatusP->EngStatusBist.Fail)
        {
            printf("\n Engtine Status: FAIL - at t = %f", t);
        }
        if (EngStatusP->EngStatusBist.Idle)
        {
            printf("\n Engtine Status: IDLE - at t = %f", t);
        }
        if (EngStatusP->EngStatusBist.Initialize)
        {
            printf("\n Engtine Status: INITIALIZED - at t = %f", t);
        }
        if (EngStatusP->EngStatusBist.ReadyToStart)
        {
            printf("\n Engtine Status: READY TO START - at t = %f", t);
        }
        if (EngStatusP->EngStatusBist.Regime)
        {
            printf("\n Engtine Status: REGIME - at t = %f", t);
        }
        if (EngStatusP->EngStatusBist.Reserved)
        {
            printf("\n Engtine Status: RESERVED - at t = %f", t);
        }
        if (EngStatusP->EngStatusBist.ShutOff)
        {
            printf("\n Engtine Status: SHUT OFF - at t = %f", t);
        }
        if (EngStatusP->EngStatusBist.Starting)
        {
            printf("\n Engtine Status: STARTING - at t = %f", t);
        }
        if (EngStatusP->EngStatusBist.Windmilling)
        {
            printf("\n Engtine Status: WINDMILLING - at t = %f", t);
        }
        printf("\n\n ------------- \n");
    }
}
