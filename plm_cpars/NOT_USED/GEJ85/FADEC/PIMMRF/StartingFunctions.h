#ifndef STARTING_FUNCTIONS_H
#define STARGING_FUNCTIONS_H

#include "IO_Types.h"

/*		T-MATS -- functions.h
 * % *************************************************************************
 * % written by Jeffryes Chapman
 * % NASA Glenn Research Center, Cleveland, OH
 * % August 2nd, 2016
 * %
 * %  This is a file that contains various functions for use in the T-MATS C-code
 * % *************************************************************************/

/* StartingFunctions.c */

/* Timer Function for Fuel Pulses */
double TimerSR(double Time, double Ts, double TimeMax);

/*Fuel Logic*/
//struct FuelRampSR *FuelLogic(double RPM, double Tt5, double Ts, struct FuelRampSR *FuelSRP, union Digital *digitalP, int EngineShutDown, int RecogButton[]);
void FuelLogic(struct ControlStart *ContStart, double RPM, double Tt5, FuelRamp_t *FuelSRP, digital_t *digitalP, int EngineShutDown, double Tsample);

/*Air Valve Logic*/
double AirValveOpen(struct ControlStart *ContStart, double RPM, int EngineShutDown);

/* Digital Outputs Logic */
//union Digital *DOLogic(double RPM, union Digital *digitalP, int EngineShutDown);
void ManualKeys(digital_t *digitalP, keys_t *keysP, int EngineShutDown, double *fValueP);

/* Oil Pressure Logic */
//struct POilSR *POilLogic(double POil, double Ts,struct POilSR *POilSRP, union Digital *digitalP, int RecogButton[]);
//void POilLogic(double POil, double Ts, POil_t *POilSRP, digital_t *digitalp, int RecogButton[]);
void POilLogic(struct ControlStart *ContStartP, double POil, POil_t *POilSRP, digital_t *digitalp, int EngineShutDown, double Tsample);

/* Logic for Shutting Donw the Engine */
//int Emergency(int EngineShutDown, struct POilSR *POilSRP, struct FuelRampSR *FuelSRP, int StartButton[], int EmergencyButton);
//int Emergency(POil_t *POilSRP, FuelRamp_t *FuelSRP, int StartButton[], int EmergencyButton);
int Emergency(POil_t *POilSRP, digital_t *digitalP, FuelRamp_t *FuelSRP, int EmergencyButton);

/* Detects rising or falling edge */
int Edge(int Signal[]);

/* Allows fuel flow to be operated manually */
void OpenLoop(struct ControlStart *ContStartP, double StartFuel, double *fValue, int Emergency);

#endif  /* STARTING_FUNCTIONS_H */
