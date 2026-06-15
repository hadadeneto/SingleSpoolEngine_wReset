#ifndef CONTROL_TYPES_H
#define CONTROL_TYPES_H


/* Structure for PI parameters */
struct PIOutput
{
    //Control Signal
    double u;
    //Integral Term - must be updated outside this code
    double Iout;
};
typedef struct PIOutput PIOutput;

/* Structure containing the controller input parameters */
struct ControllerInput
{

	/* Flag indicating that reset has been requested */
	int Reset;

	/* Flag indicating that start must be skipped */
	int SkipStart;
	
	/* Digital Inputs */
	int Old_key_start;
	int Current_key_start;
	int bits_inverter;
	int Mode;
	int LeverMode;

	/* Initial fuel value - simulation only */
	double Wf0;

	/* Ambient Inputs */
	double Altitude;
	double MN;

	/* Station 2 */
	double Tt2;
	double Pt2;

	/* Station 3 */
	double Pt3;

	/* Station 5 */
	double Tt5;

	/* Main controlled variable */
	double RPM;

	/* Thrust Command */
	double FNpc;

	/* Bearings oil pressure */
	double POil;

};
typedef struct ControllerInput ControllerInput;

struct ControllerOutput
{

	double fValue, RPMRef, FiltRef;
	int Active;

};
typedef struct ControllerOutput ControllerOutput;

struct ControlStart
{
	double ValveInit, ValveTotal, RPMValve100, RPMIdle;
	double FuelImpulseTime, RPMRelaysOn, WaitAction, FuelHighPulse;
	double FuelInit, Tt5AvFlameOn, FuelRamp, RPMIgnOff, TimeAccomodation;
	double TimeIgnition, Tt5AvMax, TimeOvertemp;
	double POilAlarm, POilShutDown, TimeLowPOil;
	double FuelPerc;
};
typedef struct ControlStart ControlStart;

#endif /* CONTROL_TYPES_H */
