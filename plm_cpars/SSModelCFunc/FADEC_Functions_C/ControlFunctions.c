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
#include "../FADEC_Defines_H/Control_Types.h"
#include "../FADEC_Defines_H/Interpolation_Types.h"
#include "../FADEC_Defines_H/Env_SampTime.h"
#include "../FADEC_Functions_H/functions_TMATS.h"
#include "../FADEC_Functions_H/MtxIntFunctions.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"


/*******************************************************************************
 *
 *	FUNCTION:		Min()
 *
 *	PURPOSE:		Obtains the smaller value between two variables (floating)
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

floating Min(floating a, floating b)
{
	floating Value;

	/* Initiates the Value with a */
	Value = a;

	/* If b < a, stores b at Value */
	if(b < a){
		Value = b;
	}

	return Value;
};

/*******************************************************************************
 *
 *	FUNCTION:		Max()
 *
 *	PURPOSE:		Obtains the larger value between two variables (floating)
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

floating Max(floating a, floating b)
{
	floating Value;

	/* Initiates the Value with a */
	Value = a;

	/* If b > a, stores b at Value */
	if(b > a){
		Value = b;
	}

	return Value;
};


/*******************************************************************************
 *
 *	FUNCTION:		PIControl()
 *
 *	PURPOSE:		Calculates control signal and integral term with back
 *                   calculation protection
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Ki, Kp, Kb, Ts, Ik1, ek, ek1, ebk1, *PIOutP
 *
 *	RETURNS:		PIOutP
 *
 *	COMMENTS:       Rules for variable name: type_varname or type_VN
 *
 *******************************************************************************/

//struct PIOutput *PIControl(floating Ki, floating Kp, floating Kb, floating Ts, floating Ik1, floating ek, floating ek1, floating ebk1, struct PIOutput *PIOutP)
void PIControl(floating Ki, floating Kp, floating Kb, floating Ts, floating Ik1, floating ek, floating ek1, floating ebk1, struct PIOutput *PIOutP)

{
    /* DEFINITION OF LOCAL VARIABLES */
    
    
    //Local Variables
    floating proportional;
    floating integral;
    floating eIk1;
    floating u;
    
    /* CONTROLLER BODY FUNCTION */
    
    //Calculates proportional term
    proportional = Kp*ek;
    //Calculates the error to be integrated
    eIk1 = ek1 - Kb*ebk1;
    //Calculates integral term with BackCalculation Windup Protection
    integral = Ik1 + Ki*Ts*eIk1;
    //Calculates final control value
    u = proportional + integral;
    
    /* COMPUTATION OF OUTPUTS */
    
    //Updates string values
	PIOutP->Iout = integral;
    PIOutP->u = u;
    
}


/*******************************************************************************
 *
 *	FUNCTION:		ASRefFinc()
 *
 *	PURPOSE:		returns the Acceleration Schedule reference value
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		*NcP, *ASP, Nc, Tt2
 *
 *	RETURNS:		RefValue
 *
 *	COMMENTS:
 *
 *******************************************************************************/


 floating ASRefFind(floating *NcP, floating *ASP, floating Nc, floating Tt2, floating NcElNum, floating Tstd, floating NDes)
 {
     /* Local Variables */
 	floating RefValue = 0;
 
 	InterpIndex Indexes;
	//InterpIndex *IndexesP = &Indexes; 
 
 	int k;
 	floating f;
 
 	/* Finds the indexes for the given Nc */
 	IndFind(Nc, NcElNum, NcP, &Indexes);
 
 	/* Reads the value of the Acceleration Schedule corrected rotation reference */
 	k = Indexes.K;
 	f = Indexes.f;

	/* In case f < 0, f must be set to zero so the minimum acceleration value is used */
	if (f < 0)
	{
		f = 0;
	}
	 	
 	if(f != 0){
 		RefValue = *(ASP + k) + f*(*(ASP + k + 1) - *(ASP + k));
 	}
 	else{
 		RefValue = *(ASP + k);
 	}
 
 	/* Calculates rpm reference from corrected speed - requires definition of sqrtT*/
 	RefValue = Nc*RefValue*sqrtT(Tt2/Tstd)*NDes;
 
 	/* Returns the value of the Acceleration Schedule reference */
 	return RefValue;
 };


/*******************************************************************************
 *
 *	FUNCTION:		ActiveCont()
 *
 *	PURPOSE:		Identify
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		*Pointer, NumSignals, u
 *
 *	RETURNS:		Identify
 *
 *	COMMENTS:
 *
 *******************************************************************************/

floating ActiveCont(floating *Pointer, floating NumSignals, floating u)
{

	//Local Variables
	floating uCalc = 0;
	floating Identify = 9;
	int i;

	/* LOOP FOR IDENTIFYING ACTIVE CONTROLLER */
	for(i = 0; i < NumSignals; i++){

		//Updates Calculated Signal
		uCalc = *(Pointer + i);

		//Verifies if the current signal equals u
		if(uCalc == u){

			//Stores the Value of the Active Controller
			Identify = i;
			break;
		};

	};

	//Returns the Value Corresponding to Active Controller
	return Identify;
}

/*******************************************************************************
 *
 *	FUNCTION:		RefRamp()
 *
 *	PURPOSE:		Generate a smooth reference ramp durin transition from 
 *					starting to idle
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		*Ref
 *
 *	RETURNS:		Identify
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void RefRampSR(struct ControlStart *ContStartP, floating *Ref, floating RefRamp, floating Tick)
{

	int status = ContStartP->RefInitStatus;
	floating RefInit = ContStartP->RefInit;


	switch (status)
	{
	case 0:	

		/* Updates the ramp value for reference */
		RefInit = RefInit + RefRamp * 0.001 * Tick;

		/* Status is updated case the ramp value has reached the value read from ADC */
		/*Otherwise, the reference is updated with the ramp value*/
		if (*Ref <= RefInit) 
		{
			status = 1;
		}
		else 
		{
			*Ref = RefInit;
		}

		break;
	}

	/* Updates ContStartP */
	ContStartP->RefInit = RefInit;
	ContStartP->RefInitStatus = status;

}


/*---------------------------------------------------------------------------------*/
/* FUNCTIONS PRESENT IN OLDER VERSION - TO BE USED DURING SOFTWARE TRANSITION ONLY */
/*---------------------------------------------------------------------------------*/

/*******************************************************************************
 *
 *	FUNCTION:		RefRamp()
 *
 *	PURPOSE:		Identify
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		*Ref
 *
 *	RETURNS:		Identify
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void RefRamp(floating *Ref, floating *RefInit, int *ResetP, floating RefRamp, floating Tick)
{

	static int status = 0;

	if (*ResetP == 1) 
	{
		status = 0;
		*ResetP = 0;
	}

	switch (status)
	{
	case 0:	

		/* Updates the ramp value for reference */
		//*RefInit = *RefInit + TF1200_REFRAMP * 0.001 * TICK;
		*RefInit = *RefInit + RefRamp * 0.001 * Tick;

		/* Status is updated case the ramp value has reached the value read from ADC */
		/*Otherwise, the reference is updated with the ramp value*/
		if (*Ref <= *RefInit) 
		{
			status = 1;
		}
		else 
		{
			*Ref = *RefInit;
		}

		break;
	}

}

/*---------------------------------------------------------------------------------*/

