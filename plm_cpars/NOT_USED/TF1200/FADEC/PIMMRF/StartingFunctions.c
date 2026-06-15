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
#include "IO_Types.h"
#include "Env_SampTime.h"
#include "Control_Types.h"

//double ADC_Read();

/*******************************************************************************
 *
 *	FUNCTION:		TimerSR()
 *
 *	PURPOSE:		Obtains the smaller value between two variables (double)
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

double TimerSR(double Time, double Ts, double TimeMax)
{
	//Updates Time Value
	Time = Time + Ts;

	//If Time value is greater or equal TimeMax, the timer must be reset
	if(Time >= TimeMax ){
		//Resets Timer Value
		Time = 0;
	}

	//Returns Timer Value
	return Time;
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

