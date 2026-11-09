#ifndef STARTING_FUNCTIONS_H
#define STARGING_FUNCTIONS_H

#include "../FADEC_Defines_H/IO_Types.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"

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
int TimerSR(floating *Time, floating Ts, floating TimeMax);

/* Function delay inside a state of the state-machine */
void StatusDelay(floating *TimeP, floating Ts, floating TimeMax, int *status, int NextStatus);

/*Air Valve Logic*/
floating AirValveOpen(struct ControlStart *ContStart, floating RPM, int EngineShutDown);

/* Identification of starting command */
void StartEdge( struct ControlStart *ContStartP, int *status, int NextStatus);

/* Activation of digital outputs */
void DigOutOn(floating RPM,  struct ControllerConstants *ContConstP, digital_t *digitalP, int *status, int NextStatus);

/* Sets fuel pulse to high value */
void FuelPulse(floating *TimePulseP, floating Ts, floating PulseWidth, floating *WfP, floating WfHigh, floating Tt4, floating Tt4FlameOn, int *status, int NextStatus);

/* Ignition attempt function */
void IgnitAttempt(digital_t *digitalP, floating *IgnTryTimeP, floating MaxIgnTryTime,
				floating Ts, floating Tt4, floating Tt4Ign, int *statusP, int statusIgn, 
				int *IgnTries,int IgnMaxTries, floating *WfP, floating WfInit,
				 int *IgnitionFailP, int NextState);

/* Fuel ramp sub routine */
void FuelRampSR(floating *WfP, floating WfInit, floating RampCoef, floating *RampTimeP, floating Ts);

/* Closed loop startring temperature control */
void PITempStart(struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, floating Tsample);

/* Closed loop starting sub routine */
void PIMMStart(floating *AltLinVecP, floating *MNLinVecP, floating *NcVecP,
                floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
                struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, floating *NcFANContMtxP, 
				floating *N_KpMtxP, floating *N_KiMtxP, floating Tsample);

/* Updating of starting variables */
void StartVarsUpdt(struct ControlStart *ContStartP, struct ControllerConstants *ContConstP, floating Wf, floating RPM, floating Tt4);

/* Fuel increase logic */
void FuelIncrease(struct ControllerConstants *ContConstP, struct ControlStart *ContStartP, digital_t *digitalP, floating RPM, floating RPMChange, floating RPMIgnOff, floating Tt4, 
				floating Tt4FlameOn, floating *WfP, floating *WfChangeP, floating WfInit, floating WfRampCoef, 
				floating *RampTimeP, floating Ts, int *statusP, int StatusIgn, int NextStatus);

/* Controls Tt4 temperature right after engine ignition  */
void FuelLowCL(floating Tt4, floating Tt4FlameOn, 
                struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, 
				floating Tsample,	int *statusP, int NextStatus);
				
/* Closed loop fuel increase logic */
// void FuelIncreaseCL(digital_t *digitalP, floating RPM, floating RPMChange, floating RPMIgnOff, floating Tt4, 
// 				floating Tt4FlameOn, floating *WfP, floating *RampTimeP,
// 				floating *AltLinVecP, floating *MNLinVecP, floating *NcVecP,
//                 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
//                 struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
//                 struct ControllerInput *ContInputP, floating *NcFANContMtxP, 
// 				floating *N_KpMtxP, floating *N_KiMtxP, floating Tsample,
// 				int *statusP, int NextStatus);
void FuelIncreaseCL(digital_t *digitalP, floating RPM, floating RPMChange, floating RPMIgnOff, floating Tt4, 
				floating Tt4FlameOn, floating *WfP, floating *RampTimeP, floating RPMRampCoef,
				floating *AltLinVecP, floating *MNLinVecP, floating *NcVecP,
                floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
                struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, floating *NcFANContMtxP, 
				floating *N_KpMtxP, floating *N_KiMtxP, floating Tsample,
				int *statusP, int NextStatus);

/* Controls Tt4 during engine early start */
void TempDecreaseCL(struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, floating *WfP, floating *RampTimeP,
				floating Tsample,	int *statusP, int NextStatus);

/* Accomodation logic */
void AccomodSR(floating *AccomTimeP, floating MaxAccomTime, floating Ts, int *StartCompleteP, floating *WfP, floating WfAccom);

/*Starting Logic*/
void StartLogic(struct ControllerConstants *ContConstP,struct ControlStart *ContStartP, floating RPM, floating Tt4, digital_t *digitalP, floating Tsample);

/* Closed loop start logic */
void StartLogicCL(floating RPM, floating Tt4, digital_t *digitalP,
				  floating *AltLinVecP, floating *MNLinVecP, floating *NcVecP,
                  floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
                  struct ControllerConstants *ContConstP, struct ControlStart *ContStartP, 
                  struct ControllerInput *ContInputP, floating *NcFANContMtxP, 
				  floating *N_KpMtxP, floating *N_KiMtxP, floating Tsample);

/* Starting logic of TJ200 engine */
void StartLogicTJ200(struct ControllerConstants *ContConstP,struct ControlStart *ContStartP, floating RPM, floating Tt4, digital_t *digitalP, floating Tsample);

/* Digital Outputs Logic */
void ManualKeysSR(digital_t *digitalP, keys_t *keysP, floating *fValueP);

/* Allows fuel flow to be operated manually */
int OpenLoopSR(struct ControlStart *ContStartP, floating WfStart, floating *WfP);

/* Executes Start/Shut Off/Emergency logic */
void OnOffLogicSR(struct EngineOnOff *EngOnOffP, floating Ts);

/*------------------------------------------------------------------------------*/
/* FUNCTIONS PRESENT IN THE OLDER VERSION - USE DURING SOFTWARE TRANSITION ONLY */
/*------------------------------------------------------------------------------*/

void FuelLogic(struct ControlStart *ContStartP, floating RPM, floating Tt5, FuelRamp_t *FuelSRP, digital_t *digitalP, int EngineShutDown, floating Tsample);

void ManualKeys(digital_t *digitalP, keys_t *keysP, int EngineShutDown, floating *fValueP);

void POilLogic(struct ControlStart *ContStartP, floating POil, POil_t *POilSRP, digital_t *digitalp, int EngineShutDown, floating Tsample);

int Emergency(POil_t *POilSRP, digital_t *digital, FuelRamp_t *FuelSRP, int EmergencyButton);

void OpenLoop(struct ControlStart *ContStartP, floating StartFuel, floating *fValue, int Emergency, int *ResetP);

/*------------------------------------------------------------------------------*/

#endif  /* STARTING_FUNCTIONS_H */
