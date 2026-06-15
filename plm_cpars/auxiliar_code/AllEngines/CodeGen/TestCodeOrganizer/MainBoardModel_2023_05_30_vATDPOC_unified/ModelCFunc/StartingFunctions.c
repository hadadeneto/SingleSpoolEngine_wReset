/*		FADEC -- StartingFunctions.c
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % December, 2021
 * %
 * %  This is a file that contains various functions for use in the FADEC C-code
 * % *************************************************************************/

//#include "constants_TMATS.h"
#include <math.h>
#include "IO_Types.h"
#include "Env_SampTime.h"
#include "Control_Types.h"
#include "Interpolation_Types.h"
#include "LinMtxFunctions.h"
#include "MtxIntFunctions.h"
#include "ControlFunctions.h"

/*******************************************************************************
 *
 *	FUNCTION:		Edge()
 *
 *	PURPOSE:		Edge detection of a variable
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Signal[] (must be at least a string of two elements)
 *
 *	RETURNS:		EdgeFlag
 *
 *	COMMENTS:
 *
 *******************************************************************************/


int Edge(int Signal[])
{

	/* Initiates Edge with zero value */
	int	EdgeFlag = 0;

	/* Signal[0] > Signal[1] -> risign edge -> Edge = 1 */
	if (Signal[0] > Signal[1]) {
		EdgeFlag = 1;
	}

	/* Signal[0] < Signal[1] -> risign edge -> Edge = 2 */
	if (Signal[0] < Signal[1]) {
		EdgeFlag = 2;
	}

	return EdgeFlag;

};

/*******************************************************************************
 *
 *	FUNCTION:		TimerSR()
 *
 *	PURPOSE:		Updates and resets timer value 
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double *Time, double Ts, double TimeMax
 *
 *	RETURNS:		int TimeReset
 *
 *	COMMENTS:
 *
 *******************************************************************************/

int TimerSR(double *TimeP, double Ts, double TimeMax)
{
	
	/* Flag indicating that the value of TimeMax has been reached and timer
	has been reset */
	int TimeReset = 0;
	
	/* Updates Time Value */
	*TimeP = *TimeP + Ts;

	/* If Time value is greater or equal TimeMax, the timer must be reset */
	if(*TimeP >= TimeMax ){
		/* Resets Timer Value and sets reset flag to 1 */
		//*TimeP = 0;
		TimeReset = 1;
	}

	/* Returns Timer Value */
	return TimeReset;
};

/*******************************************************************************
 *
 *	FUNCTION:		StatusDelay()
 *
 *	PURPOSE:		Updates the status once a given value has been reached by the
 *					timer
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double *TimeP, double Ts, double TimeMax, int *status
 *
 *	RETURNS:		
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void StatusDelay(double *TimeP, double Ts, double TimeMax, int *status, int NextStatus)
{
	
	/* Declaration of reset flag */
	int TimerReset = 0;

	/* Executes the timer subroutine for desired delay */
	TimerReset = TimerSR(TimeP, Ts, TimeMax);

	/* Updates status if timer has been reset */
	if (TimerReset == 1)
	{
		*status = NextStatus;
		*TimeP = 0;
	}
	
};

/*******************************************************************************
 *
 *	FUNCTION:		AirValveOpen()
 *
 *	PURPOSE:		Obtains the smaller value between two variables (double)
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		RPM, ValveSR
 *
 *	RETURNS:		ValveSR
 *
 *	COMMENTS:
 *
 *******************************************************************************/

double AirValveOpen(struct ControlStart *ContStart, double RPM, int EngineShutDown)
{

	double ValveInit = ContStart->ValveInit;
	double ValveTotal = ContStart->ValveTotal;
	double RPMValve100 = ContStart->RPMValve100;
	double RPMIdle = ContStart->RPMIdle;


	//Initiates ValveSR with defined initial apperture
	double ValveSR = ValveInit;

	//If rotation speed is greater or equal RPM_VALVE_100,
	//valve is opened at its maximum allowed apperture
	if (RPM >= RPMValve100) {
		ValveSR = ValveTotal;
	}

	//If rotation speed is greater or equal TJ1200_RPM_IDLE or engine is shut down,
	//valve must be totally closed
	if ((RPM >= RPMIdle) | (EngineShutDown > 0.5)) {
		ValveSR = 0;
	}

	return ValveSR;
};

/*******************************************************************************
 *
 *	FUNCTION:		StratEdge()
 *
 *	PURPOSE:		Identifies the edge indicating the engine start
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		struct ControlStart *ContStartP, int *status, int NextStatus
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void StartEdge(struct ControlStart *ContStartP, int *status, int NextStatus)
{

	int StartKey[2] = {0,0};
	int KeyEdge;

	/* Computes the values of current and old keys in StartKey */
	StartKey[0] = ContStartP->Current_key_start;
	StartKey[1] = ContStartP->Old_key_start;

	/* Identifies if an edge has occurred */
	KeyEdge = Edge(StartKey);
	
	/* Updates the value of the starting command for stauts computing */
	ContStartP->StartCommand = KeyEdge;

	/* An edge from 0 to 1 in the signal indicates that the variable status, which
	is used in the starting state machine, must be increased by 1 unit */
	if (KeyEdge == 1) 
	{
		*status = NextStatus;
	}
};

/*******************************************************************************
 *
 *	FUNCTION:		DigOutOn()
 *
 *	PURPOSE:		Activates the ditital outputs
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

void DigOutOn(double RPM,  struct ControllerConstants *ContConstP, digital_t *digitalP, int *status, int NextStatus)
{
	/* Verifies if rotation speed is sufficient for activating digital ouptuts */
	if (RPM >= ContConstP->RPMRelaysOn)
		{
			/* Activation of output relays */
			digitalP->bits.igniter = 1;
			digitalP->bits.solenoid = 1;
			digitalP->bits.suction_bomb = 1;
			digitalP->bits.oil_pump = 1;
			digitalP->bits.inverter = 1;
			digitalP->bits.T4_alarm_led = 0;
			digitalP->bits.oil_pump_led = 0;
			digitalP->bits.igniter_led = 0;

			/* Updates state-machine status */
			*status = NextStatus;
		}
};

/*******************************************************************************
 *
 *	FUNCTION:		FuelPulse()
 *
 *	PURPOSE:		Sets fuel flow value to pulse high value
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double *TimePulseP, double Ts, double PulseWidth, double *Fuel, double FuelHigh, double Tt4, double Tt4FlameOn, int *status, int NextStatus
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void FuelPulse(double *TimePulseP, double Ts, double PulseWidth, double *WfP, double WfHigh, double Tt4, double Tt4FlameOn, int *status, int NextStatus)
{

	int TimerReset;

	/* Sets the fuel flow with the high value of fuel pulse */
	*WfP = WfHigh;

	/* Executes the timer subroutine for desired delay */
	TimerReset = TimerSR(TimePulseP, Ts, PulseWidth);

	/* If ignition has been detected or the pulsewidth has been achieved */
	if((Tt4 > Tt4FlameOn) | (TimerReset == 1))
	{
		*status = NextStatus;
		*TimePulseP = 0;
	}

};

/*******************************************************************************
 *
 *	FUNCTION:		IgnMonitor()
 *
 *	PURPOSE:		Sets fuel flow value to pulse high value
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Various
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void IgnitAttempt(digital_t *digitalP, double *IgnTryTimeP, double MaxIgnTryTime,
				double Ts, double Tt4, double Tt4Ign, int *statusP, int statusIgn, 
				int *IgnTries,int IgnMaxTries, double *WfP, double WfInit,
				 int *IgnitionFailP, int NextState)
{

	/* Initiation of flag indicating ignition fail */
	int TRIgnTry = 0;

	/*----------------------------------*/
	/* SETS FUEL VALUE TO INITIAL VALUE */
	/*----------------------------------*/

	*WfP = WfInit;

	/*--------------------------*/
	/* MONITORS IGNITION TIMER  */
	/*--------------------------*/

	/* If the igniter is active, ignition trial time is counted */
	if (digitalP->bits.igniter)
	{
		/* Executes the timer subroutine */
		TRIgnTry = TimerSR(IgnTryTimeP, Ts, MaxIgnTryTime);
	}
	/* If the igniter is not active, the time should not be counted */
	else
	{
		*IgnTryTimeP = 0;
	}

	/*----------------------------*/
	/* IDENTIFICATION OF IGNITION */
	/*----------------------------*/

	/* If the combustion chamber temeprature exceeds the ignition temperature, 
	ignition is detected */
	if (Tt4 > Tt4Ign)
	{
		*IgnTryTimeP = 0;
		TRIgnTry = 0;
		*statusP = NextState;
		*IgnTries = 0;
	}
	

	/*---------------------------*/
	/* MONITORS IGNITION STATUS  */
	/*---------------------------*/

	/* If an ignition trial time has elapsed, IgnTryTime must be reset, the counter of trials must
	be increased by 1 and a new pulse must be sent to the fuel pump*/
	if (TRIgnTry == 1)
	{
		*IgnTries = *IgnTries + 1;
		*IgnTryTimeP = 0;

		/* If the number of trials have been exceeded, fail must be indicated. Otherwise, aother 
		attempt must be accomplished  */
		if (*IgnTries > IgnMaxTries)
		{
			*IgnitionFailP = 1;
		}
		else
		{
			*statusP = statusIgn;
		}
	}
};

/*******************************************************************************
 *
 *	FUNCTION:		FuelRampSR()
 *
 *	PURPOSE:		Increses fuel value following desired ramp
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double *WfP, double WfInit, double RampCoef, double *RampTimeP, double Ts
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void FuelRampSR(double *WfP, double WfInit, double RampCoef, double *RampTimeP, double Ts)
{
	double Time = *RampTimeP;

	/* Updates fuel value */
	*WfP = WfInit + RampCoef * Time;

	/* Updates ramp time */
	Time = Time + Ts;
	*RampTimeP = Time;

};

/*******************************************************************************
 *
 *	FUNCTION:		PITempStart()
 *
 *	PURPOSE:		Closed-Loop to be used during engine start
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		various
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void PITempStart(struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, double Tsample)

{
	/*--------------------------*/
	/* DECLARATION OF VARIABLES */
	/*--------------------------*/

	/* CLOSED-LOOP ROUTINE VARIABLES */

	/* Errors and control signals */
	double eTt4k;
	double uTt4k;
	double uMMk;

	/* Previous samples of errors and control signals */
	double urk1 = ContStartP->urk1;
	double uTt4k1 = ContStartP->uTt4k1;
	double ITermTk1 = ContStartP->ITermTk1;
	double eTt4k1 = ContStartP->eTt4k1;
	double eBTk1 = ContStartP->eBTk1;

	/* Active controller flag */
	double KbT = ContConst->KbT;
    double KpTt4 = ContConst->KpTt4;
	double KiTt4 = ContConst->KiTt4;
    
    /* Controller Constants */
    double    Tt4Max = ContStartP->Tt4CLRef;//ContConst->Tt4CLSafeStart;//ContConst->Tt4Max;
    double    WfMax = ContConst->WfMax;
    
	/* Structures for PI outputs */
	PIOutput PIOutT;

	/* Actuation signal */
	double Wf = ContStartP->Wf;
		
	/* Stations variables */
	double Tt4;

	/* Declares pointer for 3D interpolation indexes */
	InterpIndex3D Index3D;

	/* Starging Parameters */
	double POil;
    
    /* Dummy variable for 2D or 1D calculations */
    double DummyVar = 1;


	/*----------------------------*/
	/* STARTTING OF CONTROL LOGIC */
	/*----------------------------*/

	/* READS CONTROLLER INPUT DATA */

	/* Engine input */
	Tt4 = ContInputP->Tt4;

	/* CALCULATION OF ERRORS */

	/* Calculates Rotation Speed Error and Back Calculation Error*/
	eTt4k = Tt4Max - Tt4;
	eBTk1 = uTt4k1 - urk1;

//printf("\nInside Tem PI of state 45: eTt4k = %f, Tt4 = %f, Tt4Max = %f\n",eTt4k, Tt4,Tt4Max);

	/* CALCULATES PI CONTROL SIGNALS */

	PIControl(KiTt4, KpTt4, KbT, Tsample, ITermTk1, eTt4k, eTt4k1, eBTk1, &PIOutT);
	uTt4k = PIOutT.u;


	/* FUEL PUMP SATURATION */

	uMMk = Min(uTt4k, WfMax);
	uMMk = Max(uMMk, 0);

	/* COMPUTES ACTUATION SIGNAL OUTPUT */

	/* Computes the actuation signal at desired output */
	Wf = uMMk;

	/* MEMORY UPDATE FOR PI CONTROLLER */

	/* Delayed control variables */
	urk1 = uMMk;
	uTt4k1 = PIOutT.u;
	ITermTk1 = PIOutT.Iout;
	eTt4k1 = eTt4k;

	/* Updates fuel flow value */
	ContStartP->Wf = Wf;

	/* Updates calculated memory variables */
	ContStartP->urk1 = urk1;
	ContStartP->uTt4k1 = uTt4k1;
	ContStartP->ITermTk1 = ITermTk1;
	ContStartP->eTt4k1 = eTt4k1;
	ContStartP->eBTk1 = eBTk1;

}

/*******************************************************************************
 *
 *	FUNCTION:		PIMMStart()
 *
 *	PURPOSE:		Closed-Loop to be used during engine start
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		various
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void PIMMStart(double *AltLinVecP, double *MNLinVecP, double *NcVecP,
                double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
                struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, double *NcFANContMtxP, 
				double *N_KpMtxP, double *N_KiMtxP, double Tsample)

{
	/*--------------------------*/
	/* DECLARATION OF VARIABLES */
	/*--------------------------*/

	/* CLOSED-LOOP ROUTINE VARIABLES */

	/* Errors and control signals */
	double eNk;
	double eTt4k;
	double uNk;
	double uTt4k;
	double uMMk;
	double uRUk;

	/* Previous samples of errors and control signals */
	double uNk1 = ContStartP->uNk1;
	double urk1 = ContStartP->urk1;
	double ITermNk1 = ContStartP->ITermNk1;
	double uTt4k1 = ContStartP->uTt4k1;
	double ITermTk1 = ContStartP->ITermTk1;
	double eNk1 = ContStartP->eNk1;
	double eTt4k1 = ContStartP->eTt4k1;
	double eBNk1 = ContStartP->eBNk1;
	double eBTk1 = ContStartP->eBTk1;

	/* Active controller flag */
	double Active = ContStartP->Active;
	double CalcSigVec[] = { 100, 100, 100, 100 };
	double LastSignalIndex = 3;
	double *CSVPointer = &CalcSigVec;

	/* Controller Gains */
	double KiN;
	double KpN;
	double KbN = ContConst->KbN;
	double KbT = ContConst->KbT;
    double KpTt4 = ContConst->KpTt4;
	double KiTt4 = ContConst->KiTt4;
    
    /* Controller Constants */
    int       Alt_Elem = ContConst->Alt_Elem;
    int       Fn_Elem = ContConst->Fn_Elem;
    int       MN_Elem = ContConst->MN_Elem;
    double    NDes = ContConst->NDes;
    double    NMax = ContConst->NMax;
    double    Tt4Max = ContConst->Tt4AvMax;//ContConst->Tt4Max;
    double    WfMax = ContConst->WfMax;

    /* Number of elements of gains and thrust elements */
	double NumEl2D = MN_Elem * Fn_Elem;
	double NumEl1D = Fn_Elem;
    
	/* Structures for PI outputs */
	PIOutput PIOutN;
	PIOutput PIOutT;

	/* Reference variableS */
	double RPMRef = ContStartP->RPMRef;

	/* Actuation signal */
	double Wf = ContStartP->Wf;
		
	/* Variables to be provided externaly via CAN communication */
	double Altitude;
	double MN;
	double RPM;

	/* Stations variables */
	double Tt2;
	double Pt3;
	double Tt4;

	/* Correction parameter */
    double FNcMax;
	double Nc;
	double Theta;
    double Delta;

	/* Declares pointer for 3D interpolation indexes */
	InterpIndex3D Index3D;

	/* Starging Parameters */
	double POil;
    
    /* Dummy variable for 2D or 1D calculations */
    double DummyVar = 1;


	/*----------------------------*/
	/* STARTTING OF CONTROL LOGIC */
	/*----------------------------*/

	/* READS CONTROLLER INPUT DATA */

	/* Ambient input */
	Altitude = ContInputP->Altitude;
	MN = ContInputP->MN;

	/* Engine input */
	Tt2 = ContInputP->Tt2;
	Pt3 = ContInputP->Pt3;
	Tt4 = ContInputP->Tt4;
	RPM = ContInputP->RPM;
	POil = ContInputP->POil;
	   
	/* CALCULATION OF USED NORMALIZED PARAMETERS */

	/* Calculates the Value of Theta */
	Theta = Tt2 / TSTD;

	/* Calculates the Value of Nc */
	Nc = RPM / sqrt(Theta);
	Nc = Nc / NDes;

	/* CALCULATION OF KpN AND KiN */

	/* Finds 3D indexes necessary for interpolation of controller gains */
	InterpInd3DRPM(Altitude, MN, Nc, AltLinVecP, MNLinVecP, NcFANContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Alt_Elem, MN_Elem, Fn_Elem, &Index3D);

	/* Calculates gains used in PI controllers */
	KpN = InterpValue(&Index3D, N_KpMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	KiN = InterpValue(&Index3D, N_KiMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);

	/**/
	// KpN = KpN / 10;
	// KiN = KiN / 10;
	// KpTt4 = KpTt4 / 10;
	// KiTt4 = KiTt4 / 10;

	/* CALCULATION OF ERRORS */

	/* Calculates Rotation Speed Error and Back Calculation Error*/
	eNk = RPMRef - RPM;
	eTt4k = Tt4Max - Tt4;
	eBNk1 = uNk1 - urk1;
	eBTk1 = uTt4k1 - urk1;

	/* CALCULATES PI CONTROL SIGNALS */

	/* Calculates Control Signal for Rotation Speed and Tt4 Protection */
	PIControl(KiN, KpN, KbN, Tsample, ITermNk1, eNk, eNk1, eBNk1, &PIOutN);
	uNk = PIOutN.u;
	PIControl(KiTt4, KpTt4, KbT, Tsample, ITermTk1, eTt4k, eTt4k1, eBTk1, &PIOutT);
	uTt4k = PIOutT.u;

	/* IMPLEMENTS MIN-MAX LOGIC */

	/* Min Logic */
	uMMk = Min(uNk, uTt4k);

	/* IDENTIFIES THE ACTIVE CONTROLLER */
	/*	1 - Power Management
		2 - Tt4 Limiter
		3 - RU Limiter
		9 - Output Different From Any Calculated Signal
	*/

	/* Updates Signals in String */
	*(CSVPointer + 1) = uNk;
	*(CSVPointer + 2) = uTt4k;

	/* Identifies Active Controller */
	Active = ActiveCont(CSVPointer, LastSignalIndex, uMMk);

	/* FUEL PUMP SATURATION */
	uMMk = Min(uMMk, WfMax);
	uMMk = Max(uMMk, 0);

	/* COMPUTES ACTUATION SIGNAL OUTPUT */

	/* Computes the actuation signal at desired output */
	Wf = uMMk;

	/* MEMORY UPDATE FOR PI CONTROLLER */

	/* Delayed control variables */
	uNk1 = PIOutN.u;
	urk1 = uMMk;
	ITermNk1 = PIOutN.Iout;
	uTt4k1 = PIOutT.u;
	ITermTk1 = PIOutT.Iout;
	eNk1 = eNk;
	eTt4k1 = eTt4k;

	ContStartP->Wf = Wf;
	ContStartP->Active = Active;

	/* Updates calculated memory variables */
	ContStartP->uNk1 = uNk1;
	ContStartP->urk1 = urk1;
	ContStartP->ITermNk1 = ITermNk1;
	ContStartP->uTt4k1 = uTt4k1;
	ContStartP->ITermTk1 = ITermTk1;
	ContStartP->eNk1 = eNk1;
	ContStartP->eTt4k1 = eTt4k1;
	ContStartP->eBNk1 = eBNk1;
	ContStartP->eBTk1 = eBTk1;

}

/*******************************************************************************
 *
 *	FUNCTION:		StartVarsUpdt()
 *
 *	PURPOSE:		Closed-Loop to be used during engine start
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		various
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void StartVarsUpdt(struct ControlStart *ContStartP, struct ControllerConstants *ContConstP, double Wf, double RPM, double Tt4)
{
	/* Updates calculated memory variables */
	ContStartP->uNk1 = Wf;
	ContStartP->urk1 = Wf;
	ContStartP->ITermNk1 = Wf;
	ContStartP->uTt4k1 = Wf;
	ContStartP->ITermTk1 = Wf;
	ContStartP->eNk1 = 0;
	ContStartP->eTt4k1 = 0;
	ContStartP->eBNk1 = 0;
	ContStartP->eBTk1 = 0;
	ContStartP->RPMRef = RPM;//ContConstP->RPMIdle;
	ContStartP->RPMCLInit = RPM;
	ContStartP->Tt4CLInit = Tt4;
}

/*******************************************************************************
 *
 *	FUNCTION:		LowFuelRamp()
 *
 *	PURPOSE:		Sets fuel flow value to pulse high value
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		various
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void FuelIncrease(struct ControllerConstants *ContConstP, struct ControlStart *ContStartP, digital_t *digitalP, double RPM, double RPMChange, double RPMIgnOff, double Tt4, 
				double Tt4FlameOn, double *WfP, double *WfChangeP, double WfInit, double WfRampCoef, 
				double *RampTimeP, double Ts, int *statusP, int StatusIgn, int NextStatus)
{

	/* Initiates flat indicating if ramp may be increased */
	int RampAllowed = ContStartP->RampAllowed;
	/* Reads values of minimum and maximum temperature for allowing fuel ramp */
	double Tt4Min = ContConstP->Tt4CLSafeStart;
	double Tt4Max = ContConstP->Tt4AvMax;
	/* Reads the error (difference between Tt4AvMax and Tt4) */
	double ekTt4 = Tt4Max - Tt4;
	/* Caluclates error delta (derivative) */
	double DeTt4 = ekTt4 - ContStartP->eTt4k1;

	/* Local maximum WfMaxLocal*/
	double WfMaxLocal;

	/*Updates previous value of temperature error */
	ContStartP->eTt4k1 = ekTt4;

	/* Ramp should freeze if Tt4 >= Tt4 Max */
	if (Tt4 >= Tt4Max)
	{
		RampAllowed = 0;
	}

	/* Ramp should continue if Tt4 <= Tt4 Max */
	if (Tt4 <= Tt4Min)
	{
		RampAllowed = 1;
	}

	/* Calculates the local maximum Wf value */
	WfMaxLocal = *WfP + WfRampCoef;

	/* Verifies if Tt4 lies within the boundaries  */

	/* Verifies if engine is ignited */
	if (Tt4 >= Tt4FlameOn & RampAllowed == 1)
	{
		/* Verifies if RPM value is slower than ramp change RPM value */
		if (RPM < RPMChange)
		{
			/* Updates fuel flow value according to desired ramp */
			*WfP = *WfP + WfRampCoef * Ts;

			/*Adds derivative term*/
			*WfP = *WfP + ContConstP->WfKdStart * DeTt4;

			/* Gets smalle value between signal with pure ramp (WfMaxLocal) and signal with the derivative term */
			*WfP = Min(*WfP ,WfMaxLocal);

			/* Fuel pump saturation */
			*WfP = Min(*WfP, ContConstP->WfMax);
			*WfP = Max(*WfP, ContConstP->WfInit);

			/* Verifes if igniter must be shut off */
			if(RPM > RPMIgnOff)
			{
				digitalP->bits.igniter = 0;
			}
		}
		else
		{
			/* Updates ramp change fuel value, status value and sets ramp time to 0 */
			*WfChangeP = *WfP;
			*RampTimeP = 0;
			*statusP = NextStatus;
		}

	}

	/* If the engine has cooled down to a temperature below ignition temperature, new ignition attempts are accomplished */
	if (Tt4 < Tt4FlameOn)
	{
		*statusP = StatusIgn;
	}
	
	
	/* A decreasing rapm is applied in case overtemp possibility is detected */
	if (RampAllowed == 0)
	{
		if(Tt4 < ContConstP->Tt4RampDecFast)
        {
            /* Calculation of fuel flow */
            *WfP = *WfP + ContConstP->WfRampDec * Ts;
			
        }
        else
        {
            /* Calculation of fuel flow */
            *WfP = *WfP + ContConstP->WfRampDecFast * Ts;
        }

		/*Adds derivative term*/
		*WfP = *WfP + ContConstP->WfKdStart * DeTt4;

		/* Gets smalle value between signal with pure ramp (WfMaxLocal) and signal with the derivative term */
		*WfP = Min(*WfP, WfMaxLocal);

		/* Fuel pump saturation */
		*WfP = Min(*WfP, ContConstP->WfMax);
		*WfP = Max(*WfP, ContConstP->WfRampDecLowLim);
	}
	

	/* Updates ContStart structure with current flag value */
	ContStartP->RampAllowed = RampAllowed;
	
};

/*******************************************************************************
 *
 *	FUNCTION:		FuelLowCL()
 *
 *	PURPOSE:		Sets fuel flow value to pulse high value
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		various
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void FuelLowCL(double Tt4, double Tt4FlameOn, 
                struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, 
				double Tsample,	int *statusP, int NextStatus)
{

	double Tt4CLSafeStart = ContConst->Tt4CLSafeStart;

	/* Verifies if engine is ignited */
	if (Tt4 > Tt4FlameOn)
	{
		/* Verifies if RPM value is slower than ramp change RPM value */
		if (Tt4 > Tt4CLSafeStart)
		{
			PITempStart(ContConst, ContStartP, ContInputP, Tsample);		
		}
		else
		{
			/* Updates ramp change fuel value, status value and sets ramp time to 0 */
			*statusP = NextStatus;
		}
			
	}
	
};

/*******************************************************************************
 *
 *	FUNCTION:		FuelIncreaseCL()
 *
 *	PURPOSE:		Sets fuel flow value to pulse high value
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		various
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

// void FuelIncreaseCL(digital_t *digitalP, double RPM, double RPMChange, double RPMIgnOff, double Tt4, 
// 				double Tt4FlameOn, double *WfP, double *RampTimeP,
// 				double *AltLinVecP, double *MNLinVecP, double *NcVecP,
//                 double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
//                 struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
//                 struct ControllerInput *ContInputP, double *NcFANContMtxP, 
// 				double *N_KpMtxP, double *N_KiMtxP, double Tsample,
// 				int *statusP, int NextStatus)
void FuelIncreaseCL(digital_t *digitalP, double RPM, double RPMChange, double RPMIgnOff, double Tt4, 
				double Tt4FlameOn, double *WfP, double *RampTimeP, double RPMRampCoef,
				double *AltLinVecP, double *MNLinVecP, double *NcVecP,
                double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
                struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, double *NcFANContMtxP, 
				double *N_KpMtxP, double *N_KiMtxP, double Tsample,
				int *statusP, int NextStatus)
{

	double RPMRef = ContStartP->RPMRef;
	double RPMInit = ContStartP->RPMCLInit;

	/* Verifies if engine is ignited */
	if (Tt4 > Tt4FlameOn)
	{

		/* Increases reference ramp only if temperature protection has not been activated */
		if (ContStartP->Active == 2)
		{
			RPMRef = RPM;
		}
		else
		{
			/* Updates fuel flow value according to desired ramp */
			FuelRampSR(&RPMRef, RPMInit, RPMRampCoef, RampTimeP, Tsample);
		}

		/* Limits the RPM reference to RPMIdle value */
		RPMRef = Min(RPMRef, ContConst->RPMCLStartMaxRef);

		/* Verifes if igniter must be shut off */
		if (RPM > RPMIgnOff)
		{
			digitalP->bits.igniter = 0;
		}

		/* Verifies if RPM value is slower than ramp change RPM value */
		if (RPM < RPMChange)
		{
			/* Runs closed-loop start sub routine */
			PIMMStart(AltLinVecP, MNLinVecP, NcVecP,
                	  Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,
                	  ContConst, ContStartP, 
                	  ContInputP, NcFANContMtxP, 
					  N_KpMtxP, N_KiMtxP, Tsample);
		}
		else
		{
			/* Updates ramp change fuel value, status value and sets ramp time to 0 */
			*statusP = NextStatus;
		}
		
		/* Updates starting RPM reference */
		ContStartP->RPMRef = RPMRef;
		
	}

	/* Updates fuel value with value calculated by the function above */
	*WfP = ContStartP->Wf;
	
};

/*******************************************************************************
 *
 *	FUNCTION:		TempDecreaseCL()
 *
 *	PURPOSE:		Decreases engine temperature to a safer value before starting ramp
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		various


 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void TempDecreaseCL(struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, double *WfP, double *RampTimeP,
				double Tsample,	int *statusP, int NextStatus)
{


	double RampCoef = (-1) * ContConst->Tt4CLRampCoef;
	double Tt4Init =  ContStartP->Tt4CLInit;
	double Tt4Ref, Tt4Min, Tt4Max;

	/* Initiates Tt4Min and Tt4Max assuming that Tt4Init is higher than the safe start value */
	Tt4Min = ContConst->Tt4CLSafeStart;
	Tt4Max = Tt4Init;

	/* Executes temperature reduction only if ignition temperature is higher than safe start temperature */
	if (Tt4Init > ContConst->Tt4CLSafeStart)
	{
		/* The FuelRampSR is also suitable for calculating ramp values of any other variable, not only fuel
		Therefore, the same subroutine is used to calculate the temeprature reference according to a ramp function
		determined by its parameters */
		FuelRampSR(&Tt4Ref, Tt4Init, RampCoef, RampTimeP, Tsample);

		/* Tt4Ref must lie between Tt4Max and Tt4Min */
		Tt4Ref = Min(Tt4Ref,Tt4Max);
		Tt4Ref = Max(Tt4Ref,Tt4Min);

		/* Updates reference value for PITempStart use */
		ContStartP->Tt4CLRef = Tt4Ref;

		/* PI controller actuates for decreasing combustion chamber temperature */
		PITempStart(ContConst, ContStartP,
					ContInputP, Tsample);

		/* Updates fuel value with value calculated by the function above */
		*WfP = ContStartP->Wf;
	}

//    printf("Inside temp reduction: eTt4k1 = %f, Tt4CLSafeStart = %f\n, ", ContStartP->eTt4k1, ContConst->Tt4CLSafeStart);
//    printf("Inside temp reduction: RampCoef = %f, Tt4 = %f, Wf = %f\n",RampCoef, ContInputP->Tt4,ContStartP->Wf);

	/* If the temeprature error is small enough or if the engine ignition temperature is already lower than
	the safe value, next status is activated */
	//if (fabs(ContStartP->eTt4k1) < 0.01 * ContConst->Tt4CLSafeStart || Tt4Init < ContConst->Tt4CLSafeStart)
    if (fabs(ContInputP->Tt4 - ContConst->Tt4CLSafeStart) <= 0.01 * ContConst->Tt4CLSafeStart || ContInputP->Tt4 <= ContConst->Tt4CLSafeStart || Tt4Init < ContConst->Tt4CLSafeStart)
	{
		/* Updates status */
		*statusP = NextStatus;
		/* Sets RampTimeP value to zero for use in next status */
		*RampTimeP = 0;
	}
		
};

/*******************************************************************************
 *
 *	FUNCTION:		LowFuelRamp()
 *
 *	PURPOSE:		Sets fuel flow value to pulse high value
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double *TimePulseP, double Ts, double PulseWidth, double *Wf, double WfHigh, double Tt4, double Tt4FlameOn, int *status, int NextStatus
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void AccomodSR(double *AccomTimeP, double MaxAccomTime, double Ts, int *StartCompleteP, double *WfP, double WfAccom)
{

	/* Internal timer reset flag */
	int TRAccom = 0;

	/* Updates accomodation time and verifies if it has reached maximum accomodation time value */
	TRAccom = TimerSR(AccomTimeP, Ts, MaxAccomTime);

	/* If accomodation time has reached its maximum value, engine start has been completed */
	if (TRAccom == 1)
	{
		*StartCompleteP = 1;
		*WfP =WfAccom;
		*AccomTimeP = 0;
	}
	
};

/*******************************************************************************
 *
 *	FUNCTION:		StartLogic()
 *
 *	PURPOSE:		Accomplishes the necessary fuel logic for engine starging at
 *					test bench
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Time, Ts, TimeMax
 *
 *	RETURNS:		Time
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void StartLogic(struct ControllerConstants *ContConstP,struct ControlStart *ContStartP, double RPM, double Tt4, digital_t *digitalP, double Tsample)
{
	/* Local variables */
	double Wf = ContStartP->Wf;
	int    IgnitionFail = ContStartP->IgnitionFail;
	int	   StartComplete = 0;
	int    OvertempFail = ContStartP->OvertempFail;
	int	   DigitalOut = digitalP->out;
	int    Inverter = digitalP->bits.inverter;
	int	   RecogEdge = 0;
	int    PulsesOn = ContStartP->PulsesOn;
	int    status = ContStartP->status;
	double TimeIgn = ContStartP->TimeIgn;
	double IgnTries = ContStartP->IgnTries;
	double TimeAccom = ContStartP->TimeAccom;
	double WfAccom = ContStartP->WfAccom;
	double PulseWidith = ContStartP->PulseWidith;
	double TimePulse = ContStartP->TimePulse;
	double TimeRamp = ContStartP->TimeRamp;
	double WaitTime = ContStartP->WaitTime;
	double TimeBeforeRamp = ContStartP->TimeBeforeRamp;
	double WfChangeRamp = ContStartP->WfChangeRamp;

	/*-------------------------*/
	/* READS FUEL PULSE WIDITH */
	/*-------------------------*/

	PulseWidith = ContConstP->WfImpulseTime;

	/*---------------------------------------------------*/
	/* SUBROUTINE FOR STARTING PROCEDURE - STATE MACHINE */
	/*---------------------------------------------------*/

	/* Fuel Pulses must be activated if RPM >= TJ1200_RPM_RELAYS_ON and Tt4 < Tt4_FLAME_ON */
	PulsesOn = 1;

	/* Verifies if pulse high widith or pulse low widith is over */
	switch (status)
	{
	/* STATE 0 -> Waits for positive edge on Starting key */
	case 0:
		StartEdge(ContStartP, &status, 1);
		break;

	/* STATE 1 -> Waits for RPM to reach TJ1200_RPM_RELAYS_ON and activates the digital outputs for startgint the engine */
	case 1:
		DigOutOn(RPM, ContConstP, digitalP, &status, 2);
		break;

	/* STATE 2 -> Waits for digital relays to be actually closed */
	case 2:
		StatusDelay(&WaitTime, Tsample, ContConstP->WaitAction, &status, 3);
		break;

	/* STATE 3 -> Gives initial pulse for pump release and sets fuel at initial value */
	case 3:
		FuelPulse(&TimePulse, Tsample, PulseWidith, &Wf, ContConstP->WfHighPulse, Tt4, ContConstP->Tt4AvFlameOn, &status, 4);
		break;

		/* STATE 4 -> Waits for ignition to take place, counting how long it has been since igniter was activated */
	case 4:
		IgnitAttempt(digitalP, &TimeIgn, ContConstP->TimeIgnition,
					Tsample, Tt4, ContConstP->Tt4AvFlameOn, &status, 3, 
					&IgnTries,2, &Wf, ContConstP->WfInit,
				 	&IgnitionFail, 41);
		break;

		/* STATE 4 -> Waits for ignition to take place, counting how long it has been since igniter was activated */
	case 41:
		StatusDelay(&TimeBeforeRamp, Tsample, ContConstP->TimeBeforeRamp, &status, 5);
		break;

	/* STATE 5 -> Executes the subroutine of fuel ramp at lower rotation speeds*/
	case 5:

		FuelIncrease(ContConstP, ContStartP, digitalP, RPM, ContConstP->RPMRampChange, ContConstP->RPMIgnOff, Tt4, 
					ContConstP->Tt4AvFlameOn, &Wf, &WfChangeRamp, ContConstP->WfInit, ContConstP->WfRampLow, 
					&TimeRamp, Tsample, &status, 3, 51);

		break;

	/* STATE 51 -> Executes the subroutine of fuel ramp at higher rotation speeds */
	case 51:

		FuelIncrease(ContConstP, ContStartP, digitalP, RPM, ContConstP->RPMIdle, ContConstP->RPMIgnOff, Tt4, 
					ContConstP->Tt4AvFlameOn, &Wf, &WfAccom, WfChangeRamp, ContConstP->WfRamp, 
					&TimeRamp, Tsample, &status, 3, 6);

		break;
	
	/* STATE 6 -> Waits TJ1200_TIME_ACCOMODATION seconds for the engine to reach steady-state */
	case 6:
		AccomodSR(&TimeAccom, ContConstP->TimeAccomodation, Tsample, &StartComplete, &Wf, WfAccom);
		break;
	}

	/*---------------------*/
	/* INVERTER MUST BE ON */
	/*---------------------*/

	/* If the inverter is not on, the fuel pump must not be activated */
	if (!digitalP->bits.inverter)
	{
		Wf = 0;
		PulsesOn = 0;
	}
	
	/*-----------------*/
	/* OUTPUT UPDATING */
	/*-----------------*/

	/* Updates ControlStartP struct*/
	ContStartP->Wf = Wf;
	ContStartP->IgnitionFail = IgnitionFail;
	ContStartP->StartComplete = StartComplete;
	ContStartP->OvertempFail = OvertempFail;
	ContStartP->ControlPhase = status;
	ContStartP->TimeRamp = TimeRamp;
	ContStartP->WaitTime = WaitTime;
	ContStartP->TimeBeforeRamp = TimeBeforeRamp;
	ContStartP->WfChangeRamp = WfChangeRamp;
	ContStartP->TimePulse = TimePulse;
	ContStartP->PulseWidith = PulseWidith;
	ContStartP->WfAccom = WfAccom;
	ContStartP->PulsesOn = PulsesOn;
	ContStartP->status = status;
	ContStartP->TimeIgn = TimeIgn;
	ContStartP->IgnTries = IgnTries;
	ContStartP->TimeAccom = TimeAccom;

};

/*******************************************************************************
 *
 *	FUNCTION:		StartLogicCL()
 *
 *	PURPOSE:		Accomplishes the necessary fuel logic for engine starging at
 *					test bench
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Time, Ts, TimeMax
 *
 *	RETURNS:		Time
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void StartLogicCL(double RPM, double Tt4, digital_t *digitalP,
				  double *AltLinVecP, double *MNLinVecP, double *NcVecP,
                  double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
                  struct ControllerConstants *ContConstP, struct ControlStart *ContStartP, 
                  struct ControllerInput *ContInputP, double *NcFANContMtxP, 
				  double *N_KpMtxP, double *N_KiMtxP, double Tsample)
{
	/* Local variables */
	double Wf = ContStartP->Wf;
	int    IgnitionFail = ContStartP->IgnitionFail;
	int	   StartComplete = 0;
	int    OvertempFail = ContStartP->OvertempFail;
	int	   DigitalOut = digitalP->out;
	int    Inverter = digitalP->bits.inverter;
	int	   RecogEdge = 0;
	int    PulsesOn = ContStartP->PulsesOn;
	int    status = ContStartP->status;
	double TimeIgn = ContStartP->TimeIgn;
	double IgnTries = ContStartP->IgnTries;
	double TimeAccom = ContStartP->TimeAccom;
	double WfAccom = ContStartP->WfAccom;
	double PulseWidith = ContStartP->PulseWidith;
	double TimePulse = ContStartP->TimePulse;
	double TimeRamp = ContStartP->TimeRamp;
	double WaitTime = ContStartP->WaitTime;
	double TimeBeforeRamp = ContStartP->TimeBeforeRamp;
	double WfChangeRamp = ContStartP->WfChangeRamp;

	/*-------------------------*/
	/* READS FUEL PULSE WIDITH */
	/*-------------------------*/

	PulseWidith = ContConstP->WfImpulseTime;

	/*---------------------------------------------------*/
	/* SUBROUTINE FOR STARTING PROCEDURE - STATE MACHINE */
	/*---------------------------------------------------*/

	/* Fuel Pulses must be activated if RPM >= TJ1200_RPM_RELAYS_ON and Tt4 < Tt4_FLAME_ON */
	PulsesOn = 1;

//printf("\nStatus Inside StartLogicCL: %d\n", status);

	/* Verifies if pulse high widith or pulse low widith is over */
	switch (status)
	{
	/* STATE 0 -> Waits for positive edge on Starting key */
	case 0:
		StartEdge(ContStartP, &status, 1);
		break;

	/* STATE 1 -> Waits for RPM to reach TJ1200_RPM_RELAYS_ON and activates the digital outputs for startgint the engine */
	case 1:
		DigOutOn(RPM, ContConstP, digitalP, &status, 2);
		break;

	/* STATE 2 -> Waits for digital relays to be actually closed */
	case 2:
		StatusDelay(&WaitTime, Tsample, ContConstP->WaitAction, &status, 3);
		break;

	/* STATE 3 -> Gives initial pulse for pump release and sets fuel at initial value */
	case 3:
		FuelPulse(&TimePulse, Tsample, PulseWidith, &Wf, ContConstP->WfHighPulse, Tt4, ContConstP->Tt4AvFlameOn, &status, 4);
		break;

		/* STATE 4 -> Waits for ignition to take place, counting how long it has been since igniter was activated
		and updates the starting memory variables */
	case 4:
		IgnitAttempt(digitalP, &TimeIgn, ContConstP->TimeIgnition,
					Tsample, Tt4, ContConstP->Tt4AvFlameOn, &status, 3, 
					&IgnTries,2, &Wf, ContConstP->WfInit,
				 	&IgnitionFail, 45);
		StartVarsUpdt(ContStartP, ContConstP, Wf, RPM, Tt4);
		break;

		/* STATE 41 -> Waits for ignition to take place, counting how long it has been since igniter was activated */
	case 41:
		StatusDelay(&TimeBeforeRamp, Tsample, ContConstP->TimeBeforeRamp, &status, 52);
		StartVarsUpdt(ContStartP, ContConstP, Wf, RPM, Tt4);
		break;

	/* STATE 45 -> Temperature is reduced to 950 K in order for a safer engine start - ALTERNATIVE TO STATE 41 */
	case 45:
		//StatusDelay(&TimeBeforeRamp, Tsample, ContConstP->TimeBeforeRamp, &status, 52);
		// TempDecreaseCL(ContConstP, ContStartP, ContInputP, &Wf,
		// 			   Tsample, &status, 52);
		TempDecreaseCL(ContConstP, ContStartP, ContInputP, &Wf, &TimeRamp,
				 	   Tsample,	&status, 52);

		/* If the status has changed, the following updates must be accomplished */
		if (status == 52)
		{
			/* Updates status variables */
			StartVarsUpdt(ContStartP, ContConstP, Wf, RPM, Tt4);
		}
		break;

	/* STATE 5 -> Executes the subroutine of fuel ramp at lower rotation speeds*/
	case 5:

		// FuelIncrease(digitalP, RPM, ContConstP->RPMRampChange, ContConstP->RPMIgnOff, Tt4, 
		// 			ContConstP->Tt4AvFlameOn, &Wf, &WfChangeRamp, ContConstP->WfInit, ContConstP->WfRampLow, 
		// 			&TimeRamp, Tsample, &status, 51);

		FuelIncrease(ContConstP, ContStartP, digitalP, RPM, ContConstP->RPMRampChange, ContConstP->RPMIgnOff, Tt4, 
					ContConstP->Tt4AvFlameOn, &Wf, &WfChangeRamp, ContConstP->WfInit, ContConstP->WfRampLow, 
					&TimeRamp, Tsample, &status, 3, 51);
		break;

	/* STATE 51 -> Executes the subroutine of fuel ramp at higher rotation speeds */
	case 51:

		// FuelIncrease(digitalP, RPM, ContConstP->RPMIdle, ContConstP->RPMIgnOff, Tt4, 
		// 			ContConstP->Tt4AvFlameOn, &Wf, &WfAccom, WfChangeRamp, ContConstP->WfRamp, 
		// 			&TimeRamp, Tsample, &status, 6);

		FuelIncrease(ContConstP, ContStartP, digitalP, RPM, ContConstP->RPMIdle, ContConstP->RPMIgnOff, Tt4, 
					ContConstP->Tt4AvFlameOn, &Wf, &WfAccom, WfChangeRamp, ContConstP->WfRamp, 
					&TimeRamp, Tsample, &status, 3, 6);
		break;

	/* STATE 52 -> Executes the subroutine of closed loop rotation speed ramp at lower rotation speeds */
	case 52:

		FuelIncreaseCL(digitalP, RPM, ContConstP->RPMRampChange, ContConstP->RPMIgnOff, Tt4, 
				ContConstP->Tt4AvFlameOn, &Wf, &TimeRamp, ContConstP->RPMCLStartRamp,
				AltLinVecP, MNLinVecP, NcVecP,
                Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,
                ContConstP, ContStartP, 
                ContInputP, NcFANContMtxP, 
				N_KpMtxP, N_KiMtxP, Tsample,
				&status, 53);

		/* If the status has changed, the following updates must be accomplished */
		if (status == 53)
		{
			/* Updates values of ramp initial value to current RPM value */
			ContStartP->RPMCLInit = ContStartP->RPMRef;
			/* Sets TimeRamp to Tsample in order for the ramp to be properly updated */
			TimeRamp = Tsample;
		}

		break;

	/* STATE 53 -> Executes the subroutine of closed loop rotation speed ramp at higher rotation speeds */
	case 53:

		FuelIncreaseCL(digitalP, RPM, ContConstP->RPMIdle, ContConstP->RPMIgnOff, Tt4, 
				ContConstP->Tt4AvFlameOn, &Wf, &TimeRamp, ContConstP->RPMCLStartRampFaster,
				AltLinVecP, MNLinVecP, NcVecP,
                Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,
                ContConstP, ContStartP, 
                ContInputP, NcFANContMtxP, 
				N_KpMtxP, N_KiMtxP, Tsample,
				&status, 6);

		/* Updates fuel value with value calculated by the function above */
		WfAccom = Wf;

		break;

	/* STATE 6 -> Waits TJ1200_TIME_ACCOMODATION seconds for the engine to reach steady-state */
	case 6:
		AccomodSR(&TimeAccom, ContConstP->TimeAccomodation, Tsample, &StartComplete, &Wf, WfAccom);
		break;
	}

	/*---------------------*/
	/* INVERTER MUST BE ON */
	/*---------------------*/

	/* If the inverter is not on, the fuel pump must not be activated */
	if (!digitalP->bits.inverter)
	{
		Wf = 0;
		PulsesOn = 0;
	}
	
	/*-----------------*/
	/* OUTPUT UPDATING */
	/*-----------------*/

	/* Updates ControlStartP struct*/
	ContStartP->Wf = Wf;
	ContStartP->IgnitionFail = IgnitionFail;
	ContStartP->StartComplete = StartComplete;
	ContStartP->OvertempFail = OvertempFail;
	ContStartP->ControlPhase = status;
	ContStartP->TimeRamp = TimeRamp;
	ContStartP->WaitTime = WaitTime;
	ContStartP->TimeBeforeRamp = TimeBeforeRamp;
	ContStartP->WfChangeRamp = WfChangeRamp;
	ContStartP->TimePulse = TimePulse;
	ContStartP->PulseWidith = PulseWidith;
	ContStartP->WfAccom = WfAccom;
	ContStartP->PulsesOn = PulsesOn;
	ContStartP->status = status;
	ContStartP->TimeIgn = TimeIgn;
	ContStartP->IgnTries = IgnTries;
	ContStartP->TimeAccom = TimeAccom;

};

/*******************************************************************************
 *
 *	FUNCTION:		ManualKeysSR()
 *
 *	PURPOSE:		Transfer input keys to digital outputs
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		RPM
 *
 *	RETURNS:		digitalP
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void ManualKeysSR(digital_t *digitalP, keys_t *keysP, int EngineShutDown, double *WfP)
{
	
	digitalP->bits.igniter = !keysP->bits.igniter_key;
	digitalP->bits.solenoid = !keysP->bits.shut_off_key;
	digitalP->bits.suction_bomb = !keysP->bits.scaveng_key;
	digitalP->bits.oil_pump = !keysP->bits.oil_pump_key;
	digitalP->bits.inverter = !keysP->bits.ac_drive_key;
	digitalP->bits.oil_pump_led = 0;
	digitalP->bits.igniter_led = 0;
	digitalP->bits.T4_alarm_led = 0;

};

/*******************************************************************************
 *
 *	FUNCTION:		OpenLoopSR()
 *
 *	PURPOSE:		Open Loop Fuel Response
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Signal[] (must be at least a string of two elements)
 *
 *	RETURNS:		status
 *
 *	COMMENTS:
 *
 *******************************************************************************/

int OpenLoopSR(struct ControlStart *ContStartP, double WfStart, double *WfP)
{

	/* Reads status from ContStartP */
	int status = ContStartP->OpenLoopStatus;
	double WfMin = ( 1 - ContStartP->WfPerc ) * WfStart;
	double WfMax = ( 1 + ContStartP->WfPerc ) * WfStart;

	switch (status)
	{
	case 0:
		/* Condition for fuel flow value not to be changed until it reaches a value between 
		WfMin and WfMax  */
		if ((*WfP >= WfMin) & (*WfP <= WfMax)) {
			status = 1;
		}
		*WfP = WfStart;

		break;
	}

	/* Updates ContStartP */
	ContStartP->OpenLoopStatus = status;

return status;

};

/*******************************************************************************
 *
 *	FUNCTION:		OnOffLogicSR()
 *
 *	PURPOSE:		Treatment of Start, Shut Donw and Emergency external commands
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

void OnOffLogicSR(struct EngineOnOff *EngOnOffP, double Ts)
{

	/*------------------------------------*/
	/* DECLARES AUXILIARY LOCAL VARIABLES */
	/*------------------------------------*/

	/* External command */
	int OnOffCom = EngOnOffP->OnOffCom;

	/* Keys for edge verification - must be updated in the struct afterwards */
	int OldKey = EngOnOffP->OldKey;
	int CurrentKey = EngOnOffP->CurrentKey;

	/* Individual keys */
	int StartKey = EngOnOffP->StartKey;
	int ShutDownKey = EngOnOffP->ShutDownKey;
	int EmergencyKey = EngOnOffP->EmergencyKey;

	/* On/Off status - must be updated in the struct afterwards */
	int statusOnOff = EngOnOffP->statusOnOff;

	/* Commands */
	int Start = EngOnOffP->Start;
	int Emergency = EngOnOffP->Emergency;
	int ShutDown = EngOnOffP->ShutDown;
	// int Start = 0;//EngOnOffP->Start;
	// int Emergency = 0;//EngOnOffP->Emergency;
	// int ShutDown = 0;//EngOnOffP->ShutDown;
	/* Timers - must be updated in the struct afterwards */

	double StartTimer = EngOnOffP->StartTimer;
	double ShutDownTimer = EngOnOffP->ShutDownTimer;
	double EmergencyTimer = EngOnOffP->EmergencyTimer;

	/* Wait timer values */
	double StartWait = EngOnOffP->StartWait;
	double ShutDownWait = EngOnOffP->ShutDownWait;
	double EmergencyWait = EngOnOffP->EmergencyWait;

	/* Auxiliary timer reset flag */
	int TimerReset = 0;

	/* Flag authorizing status update */
	int statusUpdt = 0;

	/*-------------------------------------------------*/
	/* VERIFIES EXTERNAL KEYS COMMAND - FOR TEST BENCH */
	/*-------------------------------------------------*/
	
	/* Verifies if start key is set */
	if (StartKey == 1)
	{
		/* Updates start command value */
		Start = 1;
		/*Updates key values*/
		CurrentKey = 1;
	}
	/* Verifies if shut down key has been activated */
	if (ShutDownKey == 1)
	{
		ShutDown = 1;
		Emergency = 0;
	}
	/* Verifies if emergency key has been activated */
	if (EmergencyKey == 1)
	{
		Emergency = 1;
		ShutDown = 0;
	}

	/*---------------------------------*/
	/* STATE MACHINE FOR ENGINE ON OFF */
	/*---------------------------------*/

	if(statusOnOff == 0)
	{
			
		/* Verifies if start command is set */
		// if (OnOffCom == 0xAA)
		if (OnOffCom == EngOnOffP->StartCom)
		{
			/* Updates start timer */
			statusUpdt = TimerSR(&StartTimer, Ts, StartWait);
			
		}

		/* Updates on off status and start commands */
		if (statusUpdt == 1)
		{
				/* Updates status */
				statusOnOff = 1;
				/* Updates start command value */
				Start = 1;
				/*Updates key values*/
				CurrentKey = 1;
		}
	}
	else if(statusOnOff == 1){

		/*Updates current key value*/
		CurrentKey = 0;

		/* In this sate, external emergency has priority over nominal shut down */
		//if (OnOffCom == 0xEE)
		if(OnOffCom == EngOnOffP->EmergencyCom)
		{
			/* Updates start timer */
			Emergency = TimerSR(&ShutDownTimer, Ts, ShutDownWait);
			/* Sets other commands to zero */
			if (Emergency == 1)
			{
				Start = 0;
				ShutDown = 0;
			}
			
		}
		// else if (OnOffCom == 0xCC)
		else if (OnOffCom == EngOnOffP->ShutDownCom)
		{
			/* Updates start timer */
			ShutDown = TimerSR(&ShutDownTimer, Ts, ShutDownWait);
			/* Sets other commands to zero */
			if (ShutDown == 1)
			{
				Start = 0;
				Emergency = 0;
			}
		}
	}

//printf("EmergencyKey = %d, EmergencyCom = %d\n", EmergencyKey, EngOnOffP->EmergencyCom);

	/* Structure updates */
	EngOnOffP->StartTimer = StartTimer;
	EngOnOffP->ShutDownTimer = ShutDownTimer;
	EngOnOffP->EmergencyTimer = EmergencyTimer;
	EngOnOffP->statusOnOff = statusOnOff;
	EngOnOffP->OldKey = OldKey;
	EngOnOffP->CurrentKey = CurrentKey;
	EngOnOffP->Start = Start;
	EngOnOffP->Emergency = Emergency;
	EngOnOffP->ShutDown = ShutDown;

};



/*------------------------------------------------------------------------------*/
/* FUNCTIONS PRESENT IN THE OLDER VERSION - USE DURING SOFTWARE TRANSITION ONLY */
/*------------------------------------------------------------------------------*/

/*******************************************************************************
 *
 *	FUNCTION:		AirValveOpen()
 *
 *	PURPOSE:		Obtains the smaller value between two variables (double)
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		RPM, ValveSR
 *
 *	RETURNS:		ValveSR
 *
 *	COMMENTS:
 *
 *******************************************************************************/

// double AirValveOpen(struct ControlStart *ContStart, double RPM, int EngineShutDown)
// {

// 	double ValveInit = ContStart->ValveInit;
// 	double ValveTotal = ContStart->ValveTotal;
// 	double RPMValve100 = ContStart->RPMValve100;
// 	double RPMIdle = ContStart->RPMIdle;


// 	//Initiates ValveSR with defined initial apperture
// 	double ValveSR = ValveInit;

// 	//If rotation speed is greater or equal RPM_VALVE_100,
// 	//valve is opened at its maximum allowed apperture
// 	if (RPM >= RPMValve100) {
// 		ValveSR = ValveTotal;
// 	}

// 	//If rotation speed is greater or equal TJ1200_RPM_IDLE or engine is shut down,
// 	//valve must be totally closed
// 	if ((RPM >= RPMIdle) | (EngineShutDown > 0.5)) {
// 		ValveSR = 0;
// 	}

// 	return ValveSR;
// };

/*******************************************************************************
 *
 *	FUNCTION:		FuelLogicSR()
 *
 *	PURPOSE:		Accomplishes the necessary fuel logic for engine starging at
 *					test bench
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Time, Ts, TimeMax
 *
 *	RETURNS:		Time
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void FuelLogic(struct ControlStart *ContStartP, double RPM, double Tt5, FuelRamp_t *FuelSRP, digital_t *digitalP, int EngineShutDown, double Tsample)
{
	/* Local volatile variables */
	double Fuel = FuelSRP->FuelFlow;
	int    IgnitionFail = FuelSRP->IgnitionFail;
	int	   StartComplete = 0;
	int    OvertempFail = FuelSRP->OvertempFail;
	int	   DigitalOut = digitalP->out;
	int    Inverter = digitalP->bits.inverter;
	int Current_key_start = FuelSRP->Current_key_start;
	int Old_key_start = FuelSRP->Old_key_start;
	int	   RecogEdge = 0;

	/* Local static Variables */
	static int PulsesOn = 0;
	static int status = 0;
	static double TimeIgn = 0;
	static double TimeOvertemp = 0;
	static double TimeAccom;
	static double WfAccom = 0;
	static double PulseWidith = 0; 
	static double TimePulse = 0;
	static double TimeRamp = 0;
	static double WaitTime = 0;


	/*-----------------*/
	/* RESET TREATMENT */
	/*-----------------*/
	if (FuelSRP->Reset == 1) 
	{
		/* Resets all static variables */
		PulsesOn = 0;
		status = 0;
		TimeIgn = 0;
		TimeOvertemp = 0;
		TimeAccom = 0;
		WfAccom = 0;
		TimePulse = 0;
		TimeRamp = 0;
		WaitTime = 0;

		/* Sets reset flag to 1 */
		FuelSRP->Reset = 0;
	}

	/*-------------------------*/
	/* READS FUEL PULSE WIDITH */
	/*-------------------------*/

	PulseWidith = ContStartP->FuelImpulseTime;

	/*-------------------------*/
	/* SUBROUTINE FOR IGNITION */
	/*-------------------------*/

	//Fuel Pulses must be activated if RPM >= TJ1200_RPM_RELAYS_ON and Tt5 < Tt5_FLAME_ON
	PulsesOn = 1;
	//Verifies if pulse high widith or pulse low widith is over

	switch (status)
	{
		/* STATE 0 -> Waits for positive edge on Starting key */
	case 0:
		if ((Old_key_start == 0) && (Current_key_start == 1)) // from STOP to START
		{
			status = 1;
		}
		break;

		/* STATE 1 -> Waits for RPM to reach TJ1200_RPM_RELAYS_ON and activates the digital outputs for startgint the engine */
	case 1:
		
		if ((RPM >= ContStartP->RPMRelaysOn))
		{
			//Activation of output relays
			digitalP->bits.igniter = 1;
			digitalP->bits.solenoid = 1;
			digitalP->bits.suction_bomb = 1;
			digitalP->bits.oil_pump = 1;
			digitalP->bits.inverter = 1;
			digitalP->bits.T4_alarm_led = 0;
			digitalP->bits.oil_pump_led = 0;
			digitalP->bits.igniter_led = 0;
			status = 2;
		}
		break;

		/* STATE 2 -> Waits for digital relays to be actually closed */
	case 2:
		if ((RPM >= ContStartP->RPMRelaysOn))
		{
			if (WaitTime < ContStartP->WaitAction) {
				WaitTime = WaitTime + Tsample;
			}
			else {
				status = 3;
			}
		}
		break;

		/* STATE 3 -> Gives initial pulse for pump release and sets fuel at initial value */
	case 3:
		if ((RPM >= ContStartP->RPMRelaysOn))
		{
			if (TimePulse < PulseWidith) {
				//Sets fuel value for high pulse value
				Fuel = ContStartP->FuelHighPulse;
				TimePulse = TimePulse + Tsample;
			}
			else {
				TimePulse = 0;
				status = 4;
			}
		}
		break;

		/* STATE 4 -> Waits for ignition to take place, counting how long it has been since igniter was activated */
	case 4:
		TimeIgn = TimeIgn + Tsample;
		Fuel = ContStartP->FuelInit;
		if (Tt5 > ContStartP->Tt5AvFlameOn) {
			status = 5;
		}
		break;

	/* STATE 5 -> Executes the subroutine of fuel ramp */
	case 5:

		/* If idle rotation speed has been reached, ramp must stop */
		if ((RPM < ContStartP->RPMIdle) && (Tt5 > ContStartP->Tt5AvFlameOn))
		{
			Fuel = ContStartP->FuelInit + ( ContStartP->FuelRamp ) * TimeRamp;
			TimeRamp = TimeRamp + Tsample;			/*if (RPM > TJ1200_RPM_IGN_OFF) {*/
			if (RPM > ContStartP->RPMIgnOff) {
				//Deactivates Ignition
				digitalP->bits.igniter = 0;
			}
		}
		if ((RPM >= ContStartP->RPMIdle) && (Tt5 > ContStartP->Tt5AvFlameOn))
		{
			status = 6;
			WfAccom = Fuel;
		}
		break;
	/* STATE 6 -> Waits TJ1200_TIME_ACCOMODATION seconds for the engine to reach steady-state */
	case 6:
		TimeAccom = TimeAccom + Tsample;
		if (TimeAccom >= ContStartP->TimeAccomodation) {
			StartComplete = 1;
			Fuel = WfAccom;
		}
		
		break;
	}


	//If Time is greater or equal TimePMin-Ts, ignition fail must be indicated
	if (TimeIgn >= (ContStartP->TimeIgnition))
	{
		IgnitionFail = 1;
	}
	/* If the inverter is not on, the fuel pump must not be activated */
	if (!digitalP->bits.inverter)
	{
		Fuel = 0;
		PulsesOn = 0;
	}

	///* The conditional below is not needed for the real case */
	//if (RPM < TJ1200_RPM_RELAYS_ON) {
	//	/* AIR VALVE LOGIC */
	//	Fuel = AirValveOpen(RPM, EngineShutDown);
	//}

	
	/* TEMPERATURE PROTECTION */

	/* If overtempreature is detected, time must be counted in order for shutdown to be activated */
	if (Tt5 > ContStartP->Tt5AvMax)
	{
		//Updates timer for overtemp
		TimeOvertemp = TimeOvertemp + Tsample;

		//Verifies if engine must be shut down
		if (TimeOvertemp > ContStartP->TimeOvertemp)
		{
			digitalP->bits.T4_alarm_led = 1;
		}
	}
	else 
	{
		TimeOvertemp = 0;
	}

	/* Verifies if the engine must be shut down */
	if( EngineShutDown ){

		/* Shuts down the fuel flow in case engine must be shut down  */
		Fuel = 0;
		TimePulse = 0;
		TimeIgn = 0;
		TimeOvertemp = 0;
		PulseWidith = 0;
		PulsesOn = 0;
		StartComplete = 0;

		//Deactivates all relays
		digitalP->out = 0x00000000;
		status = 0;
	}

	/* Updates structure before returning it */
	FuelSRP->FuelFlow = Fuel;
	FuelSRP->IgnitionFail = IgnitionFail;
	FuelSRP->StartComplete = StartComplete;
	FuelSRP->OvertempFail = OvertempFail;
};

/*******************************************************************************
 *
 *	FUNCTION:		DOLogic()
 *
 *	PURPOSE:		Treats the ditigal outputs according to rotation speed
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		RPM
 *
 *	RETURNS:		digitalP
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void ManualKeys(digital_t *digitalP, keys_t *keysP, int EngineShutDown, double *fValueP)
{
	digitalP->bits.igniter = !keysP->bits.igniter_key;
	digitalP->bits.solenoid = !keysP->bits.shut_off_key;
	digitalP->bits.suction_bomb = !keysP->bits.scaveng_key;
	digitalP->bits.oil_pump = !keysP->bits.oil_pump_key;
	digitalP->bits.inverter = !keysP->bits.ac_drive_key;
	digitalP->bits.oil_pump_led = 0;
	digitalP->bits.igniter_led = 0;
	digitalP->bits.T4_alarm_led = 0;

	if (EngineShutDown) {
		digitalP->out = 0;
		*fValueP = 0;
	}
};

/*******************************************************************************
 *
 *	FUNCTION:		POilLogic()
 *
 *	PURPOSE:		Treats the logic of oil pressure
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		RPM, POilSRP
 *
 *	RETURNS:		POilSRP
 *
 *	COMMENTS:
 *
 *******************************************************************************/



void POilLogic(struct ControlStart *ContStartP, double POil, POil_t *POilSRP, digital_t *digitalp, int EngineShutDown, double Tsample)
{

	static int statusPoil=0;
	int    OilPumpOn;
	static double TimePOil=0;

	/*Treats reset request*/
	if (POilSRP->Reset == 1) 
	{
		/* Resets static variables */
		statusPoil = 0;
		TimePOil = 0;

		/* Sets reset flag to 0 */
		POilSRP->Reset = 0;
	}

	OilPumpOn =	digitalp->bits.oil_pump;

	int	POilAlarm = 0; 
	int	POilFailure = 0;
	int Recog = 0;

	/* Verifies if the oil pump is activated */
	if(OilPumpOn)
	{

		/* Verifies if the Oil Pressure is lower then TJ1200_POIL_ALARM */
		if (POil < ContStartP->POilAlarm) {
			/* Sets Oil Pressure Alarm to 1 */
			POilAlarm = 1;
		}

		switch (statusPoil)
		{
			case 0:
				/* Verifies if oil pressure has been low for too long */
				if (POil < ContStartP->POilShutDown) {
					/* Indicates that lubrication system is failing */
					statusPoil = 1;
				}
			break;
			case 1:
				/* If the oil pressure is too low, increments timer and compares with TJ1200_TIME_LOW_POIL */
				if (TimePOil < ContStartP->TimeLowPOil) {

					/*Increases Timer for lubrication failure*/
					TimePOil = TimePOil + Tsample;

					if (POil > ContStartP->POilShutDown) {
						/* Indicates that lubrication system is OK */
						statusPoil = 0;  
						TimePOil = 0;
					}
				}
				/* If timer has exceeded TJ1200_TIME_LOW_POIL, lubrication failure is indicated */
				else {
					POilFailure = 1;
				}
			break;
		}
	}
	else{
		/* If oil pump is not active, Timer is reset */
		TimePOil = 0;
	}

	if( EngineShutDown ){
		POilAlarm = 0;
		POilFailure = 0;
		statusPoil = 0;
	}

	/* Updates struct before it is returned */
	POilSRP->POilAlarm = POilAlarm;
	POilSRP->POilFailure = POilFailure;

};

/*******************************************************************************
 *
 *	FUNCTION:		Emergency()
 *
 *	PURPOSE:		Verifies if engine must be shut down
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		POilSRP
 *
 *	RETURNS:		EngineShutDown
 *
 *	COMMENTS:
 *
 *******************************************************************************/

int Emergency(POil_t *POilSRP, digital_t *digital, FuelRamp_t *FuelSRP, int EmergencyButton)
{

	//Reads the failure flags
	int	POilFailure = POilSRP->POilFailure;
	int IgnitionFail = FuelSRP->IgnitionFail;
	int OvertempFail = FuelSRP->OvertempFail;
	int EngineShutDown = 0;

	//Engine must shut down in case of too low oil pressure
	if(POilFailure || IgnitionFail || OvertempFail || EmergencyButton){
		EngineShutDown = 1;
		digital->out = 0x00000000;		
	}
    
	return EngineShutDown;
};


// /*******************************************************************************
//  *
//  *	FUNCTION:		Edge()
//  *
//  *	PURPOSE:		Edge detection of a variable
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		Signal[] (must be at least a string of two elements)
//  *
//  *	RETURNS:		EdgeFlag
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/


// int Edge(int Signal[])
// {

// 	/* Initiates Edge with zero value */
// 	int	EdgeFlag = 0;

// 	/* Signal[0] > Signal[1] -> risign edge -> Edge = 1 */
// 	if (Signal[0] > Signal[1]) {
// 		EdgeFlag = 1;
// 	}

// 	/* Signal[0] < Signal[1] -> risign edge -> Edge = 2 */
// 	if (Signal[0] < Signal[1]) {
// 		EdgeFlag = 2;
// 	}

// 	return EdgeFlag;

// };

/*******************************************************************************
 *
 *	FUNCTION:		OpenLoop()
 *
 *	PURPOSE:		Open Loop Fuel Response
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Signal[] (must be at least a string of two elements)
 *
 *	RETURNS:		EdgeFlag
 *
 *	COMMENTS:
 *
 *******************************************************************************/


void OpenLoop(struct ControlStart *ContStartP, double StartFuel, double *fValue, int Emergency, int *ResetP)
{

	static int status = 0;

	if (*ResetP == 1) 
	{
		/* Resets status */
		status = 0;

		/* Sets reset flag to 0 */
		*ResetP = 0;
	}

	switch (status)
	{
	case 0:
		/* Verifies if the value read by the valve is  */
		if ((*fValue >= ( 1 - ContStartP->FuelPerc ) * StartFuel) & (*fValue <= ( 1 + ContStartP->FuelPerc ) * StartFuel)) {
			status = 1;
		}
		*fValue = StartFuel;

		/*If Emergency is active, fValue receives null value*/
		if (Emergency == 1) {
			fValue = 0;
		}

		break;
	}

};

/*-------------------------------------------------------------------------------*/

