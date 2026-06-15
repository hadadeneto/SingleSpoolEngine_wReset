#ifndef CONSTANTSTJ1200_H
#define CONSTANTSTJ1200_H

/*		T-MATS -- constants.h
% *************************************************************************
% written by Jeffryes Chapman bsed on work by Ryan May
% NASA Glenn Research Center, Cleveland, OH
% February 14th, 2013
%
%  This is a file that contains various constants for use in the T-MATS C-code
% *************************************************************************/

/*------------------*/
/* ENGINE CONSTANTS */
/*------------------*/

/* Steady Operating Points Elements Numbers */
#define TJ1200_ALT_ELEM				   13   
#define TJ1200_MN_ELEM 				   11      
#define TJ1200_FN_ELEM				   16	
#define TJ1200_TOTAL_ELEM			   2288
#define TJ1200_AS_ELEM				   6

/* Components Maps Element Numbers */
#define TJ1200_FAN_NC                  10
#define TJ1200_FAN_PR                  20
#define TJ1200_HPT_NC				   7
#define TJ1200_HPT_PR				   21

/* Engine Design Point Constants */
#define TJ1200_NDES						24000
#define TJ1200_Ath_NOZZLE				3.1425e-02 //0.0397

/* Engine Starting Model Parameters */
#define TJ1200_VALVE_FUEL				7.76e-3
#define TJ1200_FUEL_BOUT				0.01	//kg/s
#define TJ1200_IGN_TIME					10		//s
#define TJ1200_IGN_DELTAT				900		//K
#define TJ1200_POIL						2		//Bar

/*-------------------------------------*/
/* ENGINE STARTING ALGORITHM CONSTANTS */
/*-------------------------------------*/

#define TJ1200_MANUAL	1
#define TJ1200_CLOOP	1

/* Time Parameters */
#define TJ1200_FUEL_IMPULSE_TIME		1			//Second      
#define TJ1200_TIME_LOW_POIL			10			//Second
#define TJ1200_TIME_PMIN				2			//Second
#define TJ1200_TIME_PMAX				0.5			//Second
#define TJ1200_TIME_IGNITION			10			//Second
#define TJ1200_TIME_OVERTEMP			5			//Seconds
#define TJ1200_TIME_ACCOMODATION		20			//Seconds
#define TJ1200_WAIT_ACTION				2			// second

/* Valve Parameters */
#define TJ1200_VALVE_INIT				7.76e-3		//Percent
#define TJ1200_VALVE_TOTAL				7.76e-3		//Percent

/* Rotation Speed Paremeters */
#define TJ1200_RPM_VALVE_100			500			//RPM 
#define TJ1200_RPM_RELAYS_ON			2000		//RPM
#define TJ1200_RPM_IGN_OFF				4000		//RPM
#define TJ1200_RPM_IDLE					17000		//RPM

/* Temperature Parameters */
#define TJ1200_Tt5AV_FLAME_ON			573			//K  
#define TJ1200_Tt5AV_MAX				860			//K

/* Oil Pressure */
#define TJ1200_POIL_ALARM				2			//Bar
#define TJ1200_POIL_SHUTDOWN			1			//Bar

/* Fuel Parameters */
#define TJ1200_FUEL_HIGH_PULSE			0.12		//Absolute
#define TJ1200_FUEL_INIT				0.02		//Absolute
#define TJ1200_FUEL_RAMP				0.002		//Absolute/Second
#define TJ1200_FUEL_PERC				0.02		//Percentual Value

#define TJ1200_ON 						1
#define TJ1200_OFF						0

/*----------------------------------------*/
/* ENGINE PI MIN-MAX CONTROLLER CONSTANTS */
/*----------------------------------------*/

/* Engine Limits */
#define TJ1200_NMAX						26400
#define TJ1200_TT4MAX					1005
#define TJ1200_TT5MAX					1005
#define TJ1200_SMMIN					5
#define TJ1200_RUMIN					1.9e-7

/* Maximum Pump Fuel Flow */
#define TJ1200_WFMAX					0.2			//kg/s

/* Controller Constant Gains */
#define TJ1200_KPTT4					0
#define TJ1200_KITT4					0.00045 // 0.001262
#define TJ1200_KBN						20000
#define TJ1200_KBT						10000
#define TJ1200_REFRAMP					500


#endif  /* CONSTANTSTJ1200_H */
