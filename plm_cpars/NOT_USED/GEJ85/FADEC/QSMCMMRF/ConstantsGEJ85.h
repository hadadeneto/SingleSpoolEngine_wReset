#ifndef CONSTANTSGEJ85_H
#define CONSTANTSGEJ85_H

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
#define GEJ85_ALT_ELEM				  13   
#define GEJ85_MN_ELEM 				  10      
#define GEJ85_FN_ELEM				  18	
#define GEJ85_TOTAL_ELEM			  2340
#define GEJ85_AS_ELEM				  6

/* Components Maps Element Numbers */
#define GEJ85_FAN_NC                  7
#define GEJ85_FAN_PR                  11
#define GEJ85_HPT_NC				  7
#define GEJ85_HPT_PR				  21

/* Engine Design Point Constants */
#define GEJ85_NDES						16540
#define GEJ85_Ath_NOZZLE				6.2862e-02

/* Engine Starting Model Parameters */
#define GEJ85_VALVE_FUEL				7.76e-3
#define GEJ85_FUEL_BOUT					0.01	//kg/s
#define GEJ85_IGN_TIME					10		//s
#define GEJ85_IGN_DELTAT				900		//K
#define GEJ85_POIL						2		//Bar

/*-------------------------------------*/
/* ENGINE STARTING ALGORITHM CONSTANTS */
/*-------------------------------------*/

#define GEJ85_MANUAL	1
#define GEJ85_CLOOP		1

/* Time Parameters */
#define GEJ85_FUEL_IMPULSE_TIME		1			//Second      
#define GEJ85_TIME_LOW_POIL			10			//Second
#define GEJ85_TIME_PMIN				2			//Second
#define GEJ85_TIME_PMAX				0.5			//Second
#define GEJ85_TIME_IGNITION			10			//Second
#define GEJ85_TIME_OVERTEMP			5			//Seconds
#define GEJ85_TIME_ACCOMODATION		20			//Seconds
#define GEJ85_WAIT_ACTION			2			// second

/* Valve Parameters */
#define GEJ85_VALVE_INIT			7.76e-3		//Percent
#define GEJ85_VALVE_TOTAL			7.76e-3		//Percent

/* Rotation Speed Paremeters */
#define GEJ85_RPM_VALVE_100			500			//RPM 
#define GEJ85_RPM_RELAYS_ON			2000		//RPM
#define GEJ85_RPM_IGN_OFF			4000		//RPM
#define GEJ85_RPM_IDLE				12000		//RPM

/* Temperature Parameters */
#define GEJ85_Tt5AV_FLAME_ON		573			//K  
#define GEJ85_Tt5AV_MAX				860			//K

/* Oil Pressure */
#define GEJ85_POIL_ALARM			2			//Bar
#define GEJ85_POIL_SHUTDOWN			1			//Bar

/* Fuel Parameters */
#define GEJ85_FUEL_HIGH_PULSE		0.12		//Absolute
#define GEJ85_FUEL_INIT				0.08		//Absolute
#define GEJ85_FUEL_RAMP				0.008		//Absolute/Second
#define GEJ85_FUEL_PERC				0.02		//Percentual Value

#define GEJ85_ON 					1
#define GEJ85_OFF					0

/*----------------------------------------*/
/* ENGINE PI MIN-MAX CONTROLLER CONSTANTS */
/*----------------------------------------*/

/* Engine Limits */
#define GEJ85_NMAX					16540
#define GEJ85_TT4MAX				1250
#define GEJ85_TT5MAX				1005
#define GEJ85_SMMIN					15
#define GEJ85_RUMIN					2.8e-7

/* Maximum Pump Fuel Flow */
#define GEJ85_WFMAX					0.2			//kg/s

/* Controller Constant Gains */
#define GEJ85_KPTT4					0
#define GEJ85_KITT4					0.0039328
#define GEJ85_KBN					20000
#define GEJ85_KBT					10000
#define GEJ85_REFRAMP				500

/* QSMC gains for RPM */
#define GEJ85_GN					1
#define GEJ85_RHON					0.5
#define GEJ85_EPSN					50
#define GEJ85_QN					2.5

/* QSMC gains for Tt5 */
// #define GEJ85_GT					0.02
// #define GEJ85_RHOT					0.02
// #define GEJ85_EPST					500
// #define GEJ85_QT					5
// #define GEJ85_KIAT                  0.015

#define GEJ85_GT					1
#define GEJ85_RHOT					0.2
#define GEJ85_EPST					500
#define GEJ85_QT					10
#define GEJ85_KIAT                  1

#endif  /* CONSTANTSGEJ85_H */
