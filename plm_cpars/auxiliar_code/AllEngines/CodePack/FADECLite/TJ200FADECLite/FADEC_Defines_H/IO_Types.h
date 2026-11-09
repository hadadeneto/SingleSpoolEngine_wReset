#ifndef IO_TYPES_H
#define IO_TYPES_H
//#include <io.h>

#include "FloatPoint_Precision.h"

/*----------------*/
/* DIGITAL RELAYS */
/*----------------*/

typedef union
{					/* Access equipment either as:	 */
	//alt_u32 in;			/*   unsigned or				 */
    unsigned int in;
	struct				/*   bit fields 				 */
	{
	    unsigned igniter_key   : 1;	/* 0 */
	    unsigned shut_off_key  : 1;	/* 1 */
	    unsigned scaveng_key   : 1;	/* 2 */
	    unsigned oil_pump_key  : 1; /* 3 */
	    unsigned ac_drive_key  : 1; /* 4 */
	    unsigned emergency_key : 1;	/* 5 */
	    unsigned mode_key      : 1;	/* 6 */
		unsigned ignSOV_key	   : 1; /* 7 */
	} bits;
} keys_t;

typedef union
{					/* Access equipment either as:	 */
	//alt_u32 out;			/*   unsigned or				 */
    unsigned int out;
	struct				/*   bit fields 				 */
	{
	    unsigned igniter   	   : 1;	 /*P2*/
		unsigned solenoid 	   : 1;  /*P3*/
	    unsigned suction_bomb  : 1;	 /*P4*/
	    unsigned oil_pump 	   : 1;  /*P5*/
	    unsigned inverter 	   : 1;	 /*P6*/
	    unsigned oil_pump_led  : 1;	 /*P7*/
	    unsigned igniter_led   : 1;	 /*P8*/
	    unsigned T4_alarm_led  : 1;	 /*P9*/
		unsigned ignSOV		   : 1;  /*P10*/

	} bits;
} digital_t;


/* ----------------------------------*/
/* STARTING FUNCTION FUEL FLOW LOGIC */
/* ----------------------------------*/

typedef struct  {

	floating FuelFlow;	/*Fuel Flow Value*/
	floating TimePulse;	/* Time Value for Fuel Pulse */	
	floating TimeIgn;		/* Time Value for Ignition */
	floating TimeOvertemp;/* Time Value allowing overtemp before automatic shutdown */
	floating PulseWidith; /* Pulse Widith*/
	int PulsesOn;		/* Flag indicating that fuel pulses are being generated */
	int IgnitionFail;	/* Flag indicating if ignition has failed */
	int StartComplete;	/* Flag indicating if stargin sequence is complete */
	int OvertempFail;	/* Flag indicating if overtemperature has happened for too long */
    int ControlPhase;
    int Start;
    int Current_key_start;
    int Old_key_start;

	int Reset;

    //floating TimePulse;
    floating TimeRamp;
    floating WaitTime;
    
}FuelRamp_t;


/* ----------------------------*/
/* STARTING OIL PRESSURE LOGIC */
/* ----------------------------*/

typedef struct  {

	floating Time;
	int	   POilAlarm;
	int	   POilFailure;
	int	   Reset;
}POil_t;

#endif /* IO_TYPES_H */
