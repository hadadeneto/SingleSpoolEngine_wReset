#ifndef STARTING_FUNCTIONS_H
#define STARGING_FUNCTIONS_H

#include "IO_Types.h"

/*		FADEC/HIL -- StartingFunctions.h
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % 
 * % November, 2019
 * %
 * %  This is a file that contains various functions for use in the FADEC C-code
 * % *************************************************************************/

/* StartingFunctions.c */

/* Detects rising or falling edge */
int Edge(int Signal[]);

/* Timer Function for Fuel Pulses */
int TimerSR(double *Time, double Ts, double TimeMax);

/* Function delay inside a state of the state-machine */
void StatusDelay(double *TimeP, double Ts, double TimeMax, int *status, int NextStatus);

/*Air Valve Logic*/
double AirValveOpen(struct ControlStart *ContStart, double RPM, int EngineShutDown);

/* Identification of starting command */
void StartEdge( struct ControlStart *ContStartP, int *status, int NextStatus);

/* Activation of digital outputs */
void DigOutOn(double RPM,  struct ControllerConstants *ContConstP, digital_t *digitalP, int *status, int NextStatus);

/* Sets fuel pulse to high value */
void FuelPulse(double *TimePulseP, double Ts, double PulseWidth, double *WfP, double WfHigh, double Tt4, double Tt4FlameOn, int *status, int NextStatus);

/* Ignition attempt function */
void IgnitAttempt(digital_t *digitalP, double *IgnTryTimeP, double MaxIgnTryTime,
				double Ts, double Tt4, double Tt4Ign, int *statusP, int statusIgn, 
				int *IgnTries,int IgnMaxTries, double *WfP, double WfInit,
				 int *IgnitionFailP, int NextState);

/* Fuel ramp sub routine */
void FuelRampSR(double *WfP, double WfInit, double RampCoef, double *RampTimeP, double Ts);

/* Closed loop startring temperature control */
void PITempStart(struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, double Tsample);

/* Closed loop starting sub routine */
void PIMMStart(double *AltLinVecP, double *MNLinVecP, double *NcVecP,
                double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
                struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, double *NcFANContMtxP, 
				double *N_KpMtxP, double *N_KiMtxP, double Tsample);

/* Updating of starting variables */
void StartVarsUpdt(struct ControlStart *ContStartP, struct ControllerConstants *ContConstP, double Wf, double RPM, double Tt4);

/* Fuel increase logic */
void FuelIncrease(struct ControllerConstants *ContConstP, struct ControlStart *ContStartP, digital_t *digitalP, double RPM, double RPMChange, double RPMIgnOff, double Tt4, 
				double Tt4FlameOn, double *WfP, double *WfChangeP, double WfInit, double WfRampCoef, 
				double *RampTimeP, double Ts, int *statusP, int StatusIgn, int NextStatus);

/* Controls Tt4 temperature right after engine ignition  */
void FuelLowCL(double Tt4, double Tt4FlameOn, 
                struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, 
				double Tsample,	int *statusP, int NextStatus);
				
/* Closed loop fuel increase logic */
// void FuelIncreaseCL(digital_t *digitalP, double RPM, double RPMChange, double RPMIgnOff, double Tt4, 
// 				double Tt4FlameOn, double *WfP, double *RampTimeP,
// 				double *AltLinVecP, double *MNLinVecP, double *NcVecP,
//                 double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
//                 struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
//                 struct ControllerInput *ContInputP, double *NcFANContMtxP, 
// 				double *N_KpMtxP, double *N_KiMtxP, double Tsample,
// 				int *statusP, int NextStatus);
void FuelIncreaseCL(digital_t *digitalP, double RPM, double RPMChange, double RPMIgnOff, double Tt4, 
				double Tt4FlameOn, double *WfP, double *RampTimeP, double RPMRampCoef,
				double *AltLinVecP, double *MNLinVecP, double *NcVecP,
                double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
                struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, double *NcFANContMtxP, 
				double *N_KpMtxP, double *N_KiMtxP, double Tsample,
				int *statusP, int NextStatus);

/* Controls Tt4 during engine early start */
void TempDecreaseCL(struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, double *WfP, double *RampTimeP,
				double Tsample,	int *statusP, int NextStatus);

/* Accomodation logic */
void AccomodSR(double *AccomTimeP, double MaxAccomTime, double Ts, int *StartCompleteP, double *WfP, double WfAccom);

/*Starting Logic*/
void StartLogic(struct ControllerConstants *ContConstP,struct ControlStart *ContStartP, double RPM, double Tt4, digital_t *digitalP, double Tsample);

/* Closed loop start logic */
void StartLogicCL(double RPM, double Tt4, digital_t *digitalP,
				  double *AltLinVecP, double *MNLinVecP, double *NcVecP,
                  double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
                  struct ControllerConstants *ContConstP, struct ControlStart *ContStartP, 
                  struct ControllerInput *ContInputP, double *NcFANContMtxP, 
				  double *N_KpMtxP, double *N_KiMtxP, double Tsample);

/* Digital Outputs Logic */
void ManualKeysSR(digital_t *digitalP, keys_t *keysP, double *fValueP);

/* Allows fuel flow to be operated manually */
int OpenLoopSR(struct ControlStart *ContStartP, double WfStart, double *WfP);

/* Executes Start/Shut Off/Emergency logic */
void OnOffLogicSR(struct EngineOnOff *EngOnOffP, double Ts);

/*------------------------------------------------------------------------------*/
/* FUNCTIONS PRESENT IN THE OLDER VERSION - USE DURING SOFTWARE TRANSITION ONLY */
/*------------------------------------------------------------------------------*/

void FuelLogic(struct ControlStart *ContStartP, double RPM, double Tt5, FuelRamp_t *FuelSRP, digital_t *digitalP, int EngineShutDown, double Tsample);

void ManualKeys(digital_t *digitalP, keys_t *keysP, int EngineShutDown, double *fValueP);

void POilLogic(struct ControlStart *ContStartP, double POil, POil_t *POilSRP, digital_t *digitalp, int EngineShutDown, double Tsample);

int Emergency(POil_t *POilSRP, digital_t *digital, FuelRamp_t *FuelSRP, int EmergencyButton);

void OpenLoop(struct ControlStart *ContStartP, double StartFuel, double *fValue, int Emergency, int *ResetP);

/*------------------------------------------------------------------------------*/

#endif  /* STARTING_FUNCTIONS_H */
