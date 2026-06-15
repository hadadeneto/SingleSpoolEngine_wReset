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
#include "Interpolation_Types.h"
#include "Env_SampTime.h"
#include "MtxIntFunctions.h"


/*******************************************************************************
 *
 *	FUNCTION:		Min()
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

double Min(double a, double b)
{
	double Value;

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

double Max(double a, double b)
{
	double Value;

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

//struct PIOutput *PIControl(double Ki, double Kp, double Kb, double Ts, double Ik1, double ek, double ek1, double ebk1, struct PIOutput *PIOutP)
void PIControl(double Ki, double Kp, double Kb, double Ts, double Ik1, double ek, double ek1, double ebk1, struct PIOutput *PIOutP)

{
    /* DEFINITION OF LOCAL VARIABLES */
    
    
    //Local Variables
    double proportional;
    double integral;
    double eIk1;
    double u;
    
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


 double ASRefFind(double *NcP, double *ASP, double Nc, double Tt2, double NcElNum, double Tstd, double NDes)
 {
     /* Local Variables */
 	double RefValue = 0;
 
 	InterpIndex Indexes;
	//InterpIndex *IndexesP = &Indexes; 
 
 	int k;
 	double f;
 
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
 
 	/* Calculates rpm reference from corrected speed */
 	RefValue = Nc*RefValue*sqrt(Tt2/Tstd)*NDes;
 
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

double ActiveCont(double *Pointer, double NumSignals, double u)
{

	//Local Variables
	double uCalc = 0;
	double Identify = 9;
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

void RefRampSR(struct ControlStart *ContStartP, double *Ref, double RefRamp, double Tick)
{

	int status = ContStartP->RefInitStatus;
	double RefInit = ContStartP->RefInit;


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

void RefRamp(double *Ref, double *RefInit, int *ResetP, double RefRamp, double Tick)
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

