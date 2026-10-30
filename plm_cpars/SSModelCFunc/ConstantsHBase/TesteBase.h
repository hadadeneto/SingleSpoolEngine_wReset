#ifndef CONSTANTSXXX_H
#define CONSTANTSXXX_H

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


/* Engine Starting Model Parameters */
#define XXX_VALVE_FUEL				7.76e-3     // 
#define XXX_FUEL_BOUT                 0.005//0.01	//kg/s
#define XXX_IGN_TIME					1//10		//s - How long the ignition takes - Model - statring part
#define XXX_IGN_DELTAT				900		//K - Temperature jump at ignition moment - Model - starting part
#define XXX_POIL						2 * 100000		//Pascals - Default oil pressure - Model - starting part, above-idle part
#define XXX_RPM_BOUT                  16000   // RPM - Rotation speed where engine blows out - Model - starting part

/*-------------------------------------*/
/* ENGINE STARTING ALGORITHM CONSTANTS */
/*-------------------------------------*/

/* Time Parameters */
#define XXX_FUEL_IMPULSE_TIME         8 //s - Duration time of fuel impulse - Control - engine start
#define XXX_TIME_LOW_POIL             10			//s - Time admited at low oil pressure condition - Control - engine start
#define XXX_TIME_PMIN                 2			//Second
#define XXX_TIME_PMAX                 0.5			//Second
#define XXX_TIME_IGNITION             7//10//7 -> At TestBench			//Second
#define XXX_TIME_OVERTEMP             5			//Seconds
#define XXX_TIME_ACCOMODATION         0.4//20			//Seconds
#define XXX_WAIT_ACTION				5//2			// second
#define XXX_WAIT_START_COMMAND       0.6         /* second */
#define XXX_WAIT_SHUTDOWN_COMMAND    0.6         /* second */
#define XXX_WAIT_EMERGENCY_COMMAND   0.2         /* second */
#define XXX_TIME_BEFORE_RAMP			5//5//3-> At  TestBench			//Seconds

#endif  /* CONSTANTSXXX_H */
