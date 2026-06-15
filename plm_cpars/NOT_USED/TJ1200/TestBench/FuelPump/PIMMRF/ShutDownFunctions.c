/*		T-MATS -- functions_TMATS.c 
 * % *************************************************************************
 * % written by Jeffryes Chapman
 * % NASA Glenn Research Center, Cleveland, OH
 * % August 2nd, 2016
 * %
 * %  This is a file that contains various functions for use in the T-MATS C-code
 * %  Functions:
 * %  sqrtT - square root with input limits
 * %  divby - divide by X with input limits
 * %  powT  - raised to the power of with input limits
 * % *************************************************************************/

//#include "constants_TMATS.h"
#include <math.h>
#include "Control_Types.h"
#include "FaultSim_Types.h"
#include "IO_Types.h"
#include "Interpolation_Types.h"
#include "Env_SampTime.h"
#include "MtxIntFunctions.h"
#include "StartingFunctions.h"
#include "ControlFunctions.h"


/*******************************************************************************
 *
 *	FUNCTION:		EmergencyShutDown()
 *
 *	PURPOSE:		Performs emergency shut down subroutine
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		a, b
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void EmergencyShutDown(struct ControllerInput *ContInputP, struct ControllerInput *ContInputEmptyP,
						 struct ControllerOutput *ContOutputP, struct ControllerOutput *ContOutputEmptyP,
						 struct ControlStart *ContStartP, struct ControlStart *ContStartEmptyP, digital_t *digitalP, int Emergency)
{

        /* Must set to zero: ContStart, ContInput, ContOutput, digital.out */
        if (Emergency == 1)
        {
            /* Sets values of ContStart to 0 */
            *ContStartP = *ContStartEmptyP;
            /* Sets values of ContInput to 0 */
            *ContInputP = *ContInputEmptyP;
            /* Sets values of ContOutput to 0 */
            *ContOutputP = *ContOutputEmptyP;
            /* Sets values of digital outputs to 0 */
            digitalP->out = 0;
            
        }
};

/*******************************************************************************
 *
 *	FUNCTION:		ShutDownRef()
 *
 *	PURPOSE:		Sets thrust reference to zero if engine shut down has been requested
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		a, b
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void ShutDownRef(int ShutDown, struct ControllerInput *ContInputP, struct ControllerOutput *ContOutputP, struct ControllerConstants *ContContsP)
{

    double FNpc = ContInputP->FNpc;
    double eNk1 = ContOutputP->eNk1;
    double MinRef = ContOutputP->MinRef;
    double Wf0SD = ContInputP->Wf0SD;
    double ErrorFracSD = ContContsP->ErrorFracSD;
    double Rate;
    int StatusSD = ContInputP->StatusSD;

    /* Verifies shut down status  */
    switch (StatusSD)
    {

    case 0:

        /* If shut down has been requested, the reference value to be sent to the
        controller must be set to 0  */
        if (ShutDown == 1)
        {
           FNpc = 0;
           StatusSD = 1;
        }

        break;

    case 1:

        /* Sets thrust reference to 0 */
        FNpc = 0;

        /* Condition for avoiding division per zero */
        if (MinRef <= 0)
        {
            MinRef = eNk1;
        }
        
        /* Calculates the rate between error and MinRef */
        Rate = fabs(eNk1 / MinRef);

        /* If error is smaller or equals 5% of MinRef, state is increased */
        if (Rate <= ErrorFracSD)
        {
            /* Updates value of initial fuel flow for shut down ramp */
            Wf0SD = ContOutputP->Wf;
            /* Sets shut down status to 2 */
            StatusSD = 2;
        }
        
        break;
    
    default:
        break;
    }

    /* Updates input struct */
    ContInputP->FNpc = FNpc;
    ContInputP->StatusSD = StatusSD;
    ContInputP->Wf0SD = Wf0SD;

};

/*******************************************************************************
 *
 *	FUNCTION:		EmergencyShutDown()
 *
 *	PURPOSE:		Performs emergency shut down subroutine
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		a, b
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void ShutDownRamp(struct ControllerInput *ContInputP, struct ControllerInput *ContInputEmptyP,
                  struct ControllerOutput *ContOutputP, struct ControllerOutput *ContOutputEmptyP,
                  struct ControlStart *ContStartP, struct ControlStart *ContStartEmptyP, digital_t *digitalP,
                  struct ControllerConstants *ContConstP, double Ts)

{
    /* Reads the reference sent to the controller */
    double WfInit = ContInputP->Wf0SD;
    double Wf;  
    double RampCoef = -ContConstP->FuelRampSD;
    double RPM = ContInputP->RPM;
    double RPMMinSD = ContConstP->RPMMinSD;
    double TimeSD = ContInputP->TimeSD;
    int StatusSD = ContInputP->StatusSD;
    
    /* Switches shut down status */      
    switch (StatusSD)
    {
    case 2:
        /* Executes fuel descending ramp */
        FuelRampSR(&Wf, WfInit, RampCoef, &TimeSD, Ts);

        /* The value of Wf must never be smaller than 0 */
        Wf = Max(Wf,0);

        /*Updates structure values*/
        ContInputP->TimeSD = TimeSD;
        ContOutputP->Wf = Wf;

        /* If the rotation speed is lower or equals RPMMinSD, an emergency shutdown must be executed */
        if (RPM < RPMMinSD)
        {
            /* Executes emergency shut down */
            EmergencyShutDown(ContInputP, ContInputEmptyP,
						      ContOutputP, ContOutputEmptyP,
						      ContStartP, ContStartEmptyP, digitalP, 1);
        }
        
        break;
    
    default:
        break;
    }
   
};

/*******************************************************************************
 *
 *	FUNCTION:		EmergencyShutDown()
 *
 *	PURPOSE:		Performs emergency shut down subroutine
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		a, b
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void FailureShutDown(EngineFaults *FaultStatusP, int *Failure)
{
    /* Internal auxiliary struct for using single bit variable */
    struct{
        uint64_t Bit :1;
    }Aux;

    /* Initiates Aux.Bit with 0 value */
    Aux.Bit = 0;

    /*LUBRICATION SYSTEM*/

    /* Verifies if low oil pressure has occurred */
    Aux.Bit = Aux.Bit | FaultStatusP->Faults.POil_Low;
    /* Verifies if high oil pressure has occurred */
    Aux.Bit = Aux.Bit | FaultStatusP->Faults.POil_High;

    /* IGNITION SYSTEM */

    /* Verifies if ignition fail has occurred */
    Aux.Bit = Aux.Bit | FaultStatusP->Faults.Ignition;

    /* FUEL SYSTEM */

    /* Verifies if low fuel pressure has occurred */
    Aux.Bit = Aux.Bit | FaultStatusP->Faults.PFuel_Low;
    /* Verifies if high fuel pressure has occurred */
    Aux.Bit = Aux.Bit | FaultStatusP->Faults.PFuel_High;

    /* MECHANICAL SYSTEM */

    /* Verifies if high vibration has occurred */
    Aux.Bit = Aux.Bit | FaultStatusP->Faults.VibrationHigh;
    /* Verifies if overtemp has occurred */
    Aux.Bit = Aux.Bit | FaultStatusP->Faults.OverTemp;
    /* Verifies if overstpeed has occurred */
    Aux.Bit = Aux.Bit | FaultStatusP->Faults.OverSpeed;
    /* Verifies if engine blowout has occurred */
    Aux.Bit = Aux.Bit | FaultStatusP->Faults.BlowOut;
    /* Verifies if engine shaft lock has occurred */
    Aux.Bit = Aux.Bit | FaultStatusP->Faults.Mec_Lock;

    /* If any of the critical failures has been detected, emergency shut down must be accomplished */
    if (Aux.Bit)
    {
        /* Engine must be shut down */
        *Failure = 1;
    }
      
};


