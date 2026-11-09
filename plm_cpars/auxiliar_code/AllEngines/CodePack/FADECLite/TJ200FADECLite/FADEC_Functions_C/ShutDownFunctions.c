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

/* -------------------------------------------------- */
/* INCLUDE - T-MATS & PWLM                            */
/* (To be usedi in MATLAB and TMATS simulations only) */
/* -------------------------------------------------- */

//#include "mex.h"

/* -------------------------------------------------- */

//#include "constants_TMATS.h"
#include <math.h>
#include "../FADEC_Defines_H/Control_Types.h"
#include "../FADEC_Defines_H/FaultSim_Types.h"
#include "../FADEC_Defines_H/IO_Types.h"
#include "../FADEC_Defines_H/Interpolation_Types.h"
#include "../FADEC_Defines_H/Env_SampTime.h"
#include "../FADEC_Functions_H/MtxIntFunctions.h"
#include "../FADEC_Functions_H/StartingFunctions.h"
#include "../FADEC_Functions_H/ControlFunctions.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"


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
						 struct ControlStart *ContStartP, struct ControlStart *ContStartEmptyP,
                         struct ControllerGeneral *ContGenOilP, struct ControllerGeneral *ContGenEmptyP,
                         digital_t *digitalP, int Emergency)
{

        /* This mode is used for emergency command only. All outputs must be disabled, including
        bearings temperature control */
        /* Must set to zero: ContStartP, ContInputP, ContOutputP, ContGenOilP, digitalP->out */
        if (Emergency == 1)
        {

            int IgnitionFail = ContStartP->IgnitionFail;

            /* Sets values of ContStart to 0 */
            *ContStartP = *ContStartEmptyP;
            /* Sets values of ContInput to 0 */
            *ContInputP = *ContInputEmptyP;
            /* Sets values of ContOutput to 0 */
            *ContOutputP = *ContOutputEmptyP;
            /* Sets values of ContGenOilP to zero */
            *ContGenOilP = *ContGenEmptyP;
            /* Sets values of digital outputs to 0 */
            digitalP->out = 0;

            /* IgnitionFail flag mus remain with the same value */
            ContStartP->IgnitionFail = IgnitionFail;

        }

        /* This mode should be used during nominal shut-off, where the bearings temepratures
        must remain under control and the shut-down status flag must remain in 2 */
        /* Must set to zero: ContStartP, ContInputP, ContOutputP, digitalP->out */
        if (Emergency == 2)
        {

            int StatusSD = ContInputP->StatusSD;
            int IgnitionFail = ContStartP->IgnitionFail;

            /* Sets values of ContStart to 0 */
            *ContStartP = *ContStartEmptyP;
            /* Sets values of ContInput to 0 */
            *ContInputP = *ContInputEmptyP;
            /* Sets values of ContOutput to 0 */
            *ContOutputP = *ContOutputEmptyP;
            /* Sets values of digital outputs to 0 */
            digitalP->out = 0;

            /* Shut-down status must remain in 2*/
            ContInputP->StatusSD = StatusSD;
            /* IgnitionFail flag mus remain with the same value */
            ContStartP->IgnitionFail = IgnitionFail;

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

void ShutDownRef(int ShutDown, struct ControllerInput *ContInputP, struct ControllerOutput *ContOutputP, struct ControllerConstants *ContContsP, floating Ts)
{

    floating FNpc = ContInputP->FNpc;
    floating eNk1 = ContOutputP->eNk1;
    floating MinRef = ContOutputP->MinRef;
    floating Wf0SD = ContInputP->Wf0SD;
    floating ErrorFracSD = ContContsP->ErrorFracSD;
    floating Rate;
    int Active = ContOutputP->Active;
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

        /* Time to ramp starts to count */
        ContInputP->TimeToRampSD = ContInputP->TimeToRampSD + Ts;
        ContInputP->TimeToEmergSD = ContInputP->TimeToEmergSD + Ts;

        /* Sets thrust reference to 0 */
        FNpc = 0;

        /* Condition for avoiding division per zero */
        if (MinRef <= 0)
        {
            MinRef = eNk1;

            /* If the error is zero, MinRef must receive a non-zero value */
            if (eNk1 == 0)
            {
                MinRef = 1;
            }

        }

        /* Calculates the rate between error and MinRef */
        Rate = fabs(eNk1 / MinRef);

        /* If error is smaller or equals ErrorFracSD of MinRef or if blow out protection is active, or time to ramp
        execution has ellapsed, state is increased */
        if (Rate <= ErrorFracSD || Active > 2 || ContInputP->TimeToRampSD >= ContContsP->TimeToRampSD)
        {
            /* Updates value of initial fuel flow for shut down ramp */
            Wf0SD = ContOutputP->Wf;
            /* Sets shut down status to 2 */
            StatusSD = 2;
        }


        break;

    case 2:

        /* Even after state 2 is reached, the reference must be kept at zero value */
        FNpc = 0;

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
                  struct ControlStart *ContStartP, struct ControlStart *ContStartEmptyP,
                  struct ControllerGeneral *ContGenOilP, struct ControllerGeneral *ContGenEmptyP,
                  digital_t *digitalP, struct ControllerConstants *ContConstP, floating Ts)

{
    /* Reads the reference sent to the controller */
    floating WfInit = ContInputP->Wf0SD;
    floating Wf;
    floating RampCoef = -ContConstP->FuelRampSD;
    floating RPM = ContInputP->RPM;
    floating RPMMinSD = ContConstP->RPMMinSD;
    floating TimeSD = ContInputP->TimeSD;
    int StatusSD = ContInputP->StatusSD;

    /* Switches shut down status */
    switch (StatusSD)
    {
    case 2:
        /* Time to ramp starts to count */
        ContInputP->TimeToEmergSD = ContInputP->TimeToEmergSD + Ts;

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
				ContStartP, ContStartEmptyP,
				ContGenOilP, ContGenEmptyP,
				digitalP, 2);
        }

        /* If time to emergency has ellapsed, complete emergency is activated */
        if (ContInputP->TimeToEmergSD >= ContConstP->TimeToEmergSD)
        {
            /* Executes emergency shut down */
            EmergencyShutDown(ContInputP, ContInputEmptyP,
                ContOutputP, ContOutputEmptyP,
                ContStartP, ContStartEmptyP,
                ContGenOilP, ContGenEmptyP,
                digitalP, 1);
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

    /* Verifies if high bearing 0 temperature has occurred */
    Aux.Bit = Aux.Bit | FaultStatusP->Faults.TBear_0_High;
    /* Verifies if high bearing 1 temperature has occurred */
    Aux.Bit = Aux.Bit | FaultStatusP->Faults.TBear_1_High;
    /* Verifies if high bearing 2 temperature has occurred */
    Aux.Bit = Aux.Bit | FaultStatusP->Faults.TBear_2_High;
//printf("TBear0High = %d, TBear1High = %d, TBearHigh = %d\n", FaultStatusP->Faults.TBear_0_High, FaultStatusP->Faults.TBear_1_High, FaultStatusP->Faults.TBear_2_High);
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

    /* CAN 0 NETWORK */

    /* Verifies if CAN 0 network misscommunicatio has occurred */
    Aux.Bit = Aux.Bit | FaultStatusP->Faults.CAN_0_Fault;

    /* If any of the critical failures has been detected, emergency shut down must be accomplished */
    if (Aux.Bit)
    {
        /* Engine must be shut down */
        *Failure = 1;
    }

};


