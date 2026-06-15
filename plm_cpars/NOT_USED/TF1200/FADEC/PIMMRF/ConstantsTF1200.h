#ifndef CONSTANTSTF1200_H
#define CONSTANTSTF1200_H

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
#define TF1200_ALT_ELEM				   13   
#define TF1200_MN_ELEM 				   12      
#define TF1200_FN_ELEM				   16	
#define TF1200_TOTAL_ELEM			   2496
#define TF1200_AS_ELEM				   6

/* Components Maps Element Numbers */
#define TF1200_FAN_NC                  10
#define TF1200_FAN_PR                  20
#define TF1200_HPC_NC                  10
#define TF1200_HPC_PR                  20
#define TF1200_HPT_NC				   7
#define TF1200_HPT_PR				   21

/* Engine Design Point Constants */
#define TF1200_NDES						26400
#define TF1200_Ath_NOZZLE				0.0397

/* Engine Starting Model Parameters */
#define TF1200_VALVE_FUEL				7.76e-3
#define TF1200_FUEL_BOUT				0.01	//kg/s
#define TF1200_IGN_TIME					10		//s
#define TF1200_IGN_DELTAT				900		//K
#define TF1200_POIL						2		//Bar

/*-------------------------------------*/
/* ENGINE STARTING ALGORITHM CONSTANTS */
/*-------------------------------------*/

#define TF1200_MANUAL	1
#define TF1200_CLOOP	1

/* Time Parameters */
#define TF1200_FUEL_IMPULSE_TIME		1			//Second      
#define TF1200_TIME_LOW_POIL			10			//Second
#define TF1200_TIME_PMIN				2			//Second
#define TF1200_TIME_PMAX				0.5			//Second
#define TF1200_TIME_IGNITION			10			//Second
#define TF1200_TIME_OVERTEMP			5			//Seconds
#define TF1200_TIME_ACCOMODATION		20			//Seconds
#define TF1200_WAIT_ACTION				2			// second

/* Valve Parameters */
#define TF1200_VALVE_INIT				7.76e-3		//Percent
#define TF1200_VALVE_TOTAL				7.76e-3		//Percent

/* Rotation Speed Paremeters */
#define TF1200_RPM_VALVE_100			500			//RPM 
#define TF1200_RPM_RELAYS_ON			2000		//RPM
#define TF1200_RPM_IGN_OFF				4000		//RPM
#define TF1200_RPM_IDLE					19000		//RPM

/* Temperature Parameters */
#define TF1200_Tt5AV_FLAME_ON			573			//K  
#define TF1200_Tt5AV_MAX				860			//K

/* Oil Pressure */
#define TF1200_POIL_ALARM				2			//Bar
#define TF1200_POIL_SHUTDOWN			1			//Bar

/* Fuel Parameters */
#define TF1200_FUEL_HIGH_PULSE			0.07		//Absolute
#define TF1200_FUEL_INIT				0.0134		//Absolute
#define TF1200_FUEL_RAMP				0.002		//Absolute/Second
#define TF1200_FUEL_PERC				0.02		//Percentual Value

#define TF1200_ON 						1
#define TF1200_OFF						0

/*----------------------------------------*/
/* ENGINE PI MIN-MAX CONTROLLER CONSTANTS */
/*----------------------------------------*/

/* Engine Limits */
#define TF1200_NMAX						26400
#define TF1200_TT4MAX					1200
#define TF1200_TT5MAX					1005
#define TF1200_SMMIN					15
#define TF1200_RUMIN					7e-8

/* Maximum Pump Fuel Flow */
#define TF1200_WFMAX					0.2			//kg/s

/* Controller Constant Gains */
#define TF1200_KPTT4					0
#define TF1200_KITT4					0.001
#define TF1200_KBN						50000
#define TF1200_KBT						50000
#define TF1200_REFRAMP					500


#endif  /* CONSTANTSTF1200_H */
