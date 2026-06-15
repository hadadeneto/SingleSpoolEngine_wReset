#ifndef SUBIDLE_MODEL_H
#define SUBIDLE_MODEL_H

//#include "IO_Types.h"

/*		FADEC/HIL -- StartingFunctions.h
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % 
 * % November, 2019
 * %
 * %  This is a file that contains various functions for use in the FADEC C-code
 * % *************************************************************************/

/* SubIdleModel.c */

#include "../FADEC_Defines_H/FloatPoint_Precision.h"

/* WindmillinModel.c - simulates engine windmilling */
// int WindMillingModel(struct EnginePars *ParsP, struct EngineStart *StartingP,
// 					 floating *AwmMtxP, floating *BwmMtxP, floating *RPMwmMtxP, floating *WfwmMtxP, 
// 					 floating Mwm, floating *MNLinVecP,
// 					 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating RPM, floating sqrTheta,
// 					 floating MN_Elem, floating Fn_Elem, floating NumEl1D, floating NumEl2D, floating Pt2, floating Tt2,
// 					 floating PN, floating PNSL, floating PNdot, floating PNdotSL, floating Pu, floating PuSL);

int WindMillingModel(struct EnginePars *ParsP, struct EngineStart *StartingP,
					 floating *AwmMtxP, floating *BwmMtxP, floating *RPMwmMtxP,
					 floating *Pt21wmMtxP, floating *Pt21DwmMtxP, floating *Pt3wmMtxP, floating *Pt3DwmMtxP,
					 floating *Pt5wmMtxP, floating *Pt5DwmMtxP, floating *Pt6wmMtxP, floating *Pt6DwmMtxP,
					 floating *Tt21wmMtxP, floating *Tt21DwmMtxP, floating *Tt3wmMtxP, floating *Tt3DwmMtxP, floating *Tt4wmMtxP, floating *Tt4DwmMtxP,
					 floating *Tt5wmMtxP, floating *Tt5DwmMtxP, floating *Tt6wmMtxP, floating *Tt6DshMtxP, floating *Tt6DwmMtxP, floating *WfwmMtxP,
					 floating Mwm, floating *MNLinVecP,
					 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating RPM, floating sqrTheta,
					 floating MN_Elem, floating Fn_Elem, floating NumEl1D, floating NumEl2D, floating Pt2, floating Tt2,
					 floating PN, floating PNSL, floating PNdot, floating PNdotSL, floating Pu, floating PuSL);

/* SubIdleModel - simulates engine sub-idle model after ignition */
// int SubIdleModel(struct EnginePars *ParsP, struct EngineStart *StartingP, floating *AshMtxP, floating *BshMtxP, floating *WfshMtxP, floating *NcFANshMtxP, floating *MNLinVecP, 
// 					 floating *Pt3shMtxP, floating *Tt4shMtxP, floating *Pt3DshMtxP, floating *Tt4DshMtxP,
// 					 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating RPM, floating sqrTheta,
// 					 floating MN_Elem, floating Fn_Elem, floating NumEl1D, floating NumEl2D, floating Pt2, floating Tt2,
// 					 floating PN, floating PNSL, floating PNdot, floating PNdotSL, floating Pu, floating PuSL);

int SubIdleModel(struct EnginePars *ParsP, struct EngineStart *StartingP, floating *MNLinVecP,
				 floating *AshMtxP, floating *BshMtxP, floating *RPMshMtxP,
				 floating *NcFANshMtxP, floating *Pt21shMtxP, floating *Pt21DshMtxP,
				 floating *Pt3shMtxP, floating *Pt3DshMtxP, floating *Pt5shMtxP, floating *Pt5DshMtxP,
				 floating *Pt6shMtxP, floating *Pt6DshMtxP, floating *Tt21shMtxP, floating *Tt21DshMtxP,
				 floating *Tt3shMtxP, floating *Tt3DshMtxP, floating *Tt4shMtxP, floating *Tt4CshMtxP, floating *Tt4DshMtxP,
				 floating *Tt5shMtxP, floating *Tt5DshMtxP, floating *Tt6shMtxP, floating *Tt6DshMtxP, floating *WfshMtxP,
				 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating RPM, floating sqrTheta,
				 floating MN_Elem, floating Fn_Elem, floating NumEl1D, floating NumEl2D, floating Pt2, floating Tt2,
				 floating PN, floating PNSL, floating PNdot, floating PNdotSL, floating Pu, floating PuSL);

/* StartingModel - Runs the complete starting model, using the above functions */
// int StartingModel(struct EnginePars *ParsP, struct EngineStart *StartingP, floating *AshMtxP, floating *BshMtxP, floating *WfshMtxP, floating *NcFANshMtxP, 
// 					 floating *AwmMtxP, floating *BwmMtxP, floating *WfwmMtxP, floating *RPMwmMtxP, floating Mwm, floating *MNLinVecP, 
// 					 floating *Pt3shMtxP, floating *Tt4shMtxP, floating *Pt3DshMtxP, floating *Tt4DshMtxP,
// 					 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating RPM, floating sqrTheta,
// 					 floating MN_Elem, floating Fn_Elem, floating NumEl1D, floating NumEl2D, floating Pt2, floating Tt2,
// 					 floating PN, floating PNSL, floating PNdot, floating PNdotSL, floating Pu, floating PuSL, floating Ts);

int StartingModel(struct EnginePars *ParsP, struct EngineStart *StartingP, floating *MNLinVecP,
				  floating *AwmMtxP, floating *AshMtxP, floating *BwmMtxP, floating *BshMtxP, floating *RPMwmMtxP, floating *RPMshMtxP,
				  floating *NcFANshMtxP, floating *Pt21shMtxP, floating *Pt21wmMtxP,
				  floating *Pt21DshMtxP, floating *Pt21DwmMtxP, floating *Pt3shMtxP, floating *Pt3wmMtxP,
				  floating *Pt3DshMtxP, floating *Pt3DwmMtxP, floating *Pt5shMtxP, floating *Pt5wmMtxP, floating *Pt5DshMtxP, floating *Pt5DwmMtxP, floating *Pt6shMtxP, floating *Pt6wmMtxP,
				  floating *Pt6DshMtxP, floating *Pt6DwmMtxP, floating *Tt21shMtxP, floating *Tt21wmMtxP, floating *Tt21DshMtxP, floating *Tt21DwmMtxP,
				  floating *Tt3shMtxP, floating *Tt3wmMtxP, floating *Tt3DshMtxP, floating *Tt3DwmMtxP, floating *Tt4shMtxP, floating *Tt4wmMtxP, floating *Tt4CshMtxP, floating *Tt4DshMtxP, floating *Tt4DwmMtxP,
				  floating *Tt5shMtxP, floating *Tt5wmMtxP, floating *Tt5DshMtxP, floating *Tt5DwmMtxP, floating *Tt6shMtxP, floating *Tt6wmMtxP, floating *Tt6DshMtxP, floating *Tt6DwmMtxP, floating *WfshMtxP, floating *WfwmMtxP,
				  floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating RPM, floating Mwm, floating sqrTheta,
				  floating MN_Elem, floating Fn_Elem, floating NumEl1D, floating NumEl2D, floating Pt2, floating Tt2,
				  floating PN, floating PNSL, floating PNdot, floating PNdotSL, floating Pu, floating PuSL, floating Ts);


// /* Detects rising or falling edge */
// int Edge(int Signal[]);

// /* Timer Function for Fuel Pulses */
// int TimerSR(floating *Time, floating Ts, floating TimeMax);

// /* Function delay inside a state of the state-machine */
// void StatusDelay(floating *TimeP, floating Ts, floating TimeMax, int *status, int NextStatus);

// /*Air Valve Logic*/
// floating AirValveOpen(struct ControlStart *ContStart, floating RPM, int EngineShutDown);

// /* Identification of starting command */
// void StartEdge( struct ControlStart *ContStartP, int *status, int NextStatus);

// /* Activation of digital outputs */
// void DigOutOn(floating RPM,  struct ControllerConstants *ContConstP, digital_t *digitalP, int *status, int NextStatus);

// /* Sets fuel pulse to high value */
// void FuelPulse(floating *TimePulseP, floating Ts, floating PulseWidth, floating *WfP, floating WfHigh, floating Tt4, floating Tt4FlameOn, int *status, int NextStatus);

// /* Ignition attempt function */
// void IgnitAttempt(digital_t *digitalP, floating *IgnTryTimeP, floating MaxIgnTryTime,
// 				floating Ts, floating Tt4, floating Tt4Ign, int *statusP, int statusIgn, 
// 				int *IgnTries,int IgnMaxTries, floating *WfP, floating WfInit,
// 				 int *IgnitionFailP, int NextState);

// /* Fuel ramp sub routine */
// void FuelRampSR(floating *WfP, floating WfInit, floating RampCoef, floating *RampTimeP, floating Ts);

// /* Closed loop startring temperature control */
// void PITempStart(struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
//                 struct ControllerInput *ContInputP, floating Tsample);

// /* Closed loop starting sub routine */
// void PIMMStart(floating *AltLinVecP, floating *MNLinVecP, floating *NcVecP,
//                 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
//                 struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
//                 struct ControllerInput *ContInputP, floating *NcFANContMtxP, 
// 				floating *N_KpMtxP, floating *N_KiMtxP, floating Tsample);

// /* Updating of starting variables */
// void StartVarsUpdt(struct ControlStart *ContStartP, struct ControllerConstants *ContConstP, floating Wf, floating RPM, floating Tt4);

// /* Fuel increase logic */
// void FuelIncrease(struct ControllerConstants *ContConstP, struct ControlStart *ContStartP, digital_t *digitalP, floating RPM, floating RPMChange, floating RPMIgnOff, floating Tt4, 
// 				floating Tt4FlameOn, floating *WfP, floating *WfChangeP, floating WfInit, floating WfRampCoef, 
// 				floating *RampTimeP, floating Ts, int *statusP, int StatusIgn, int NextStatus);

// /* Controls Tt4 temperature right after engine ignition  */
// void FuelLowCL(floating Tt4, floating Tt4FlameOn, 
//                 struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
//                 struct ControllerInput *ContInputP, 
// 				floating Tsample,	int *statusP, int NextStatus);
				
// /* Closed loop fuel increase logic */
// // void FuelIncreaseCL(digital_t *digitalP, floating RPM, floating RPMChange, floating RPMIgnOff, floating Tt4, 
// // 				floating Tt4FlameOn, floating *WfP, floating *RampTimeP,
// // 				floating *AltLinVecP, floating *MNLinVecP, floating *NcVecP,
// //                 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
// //                 struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
// //                 struct ControllerInput *ContInputP, floating *NcFANContMtxP, 
// // 				floating *N_KpMtxP, floating *N_KiMtxP, floating Tsample,
// // 				int *statusP, int NextStatus);
// void FuelIncreaseCL(digital_t *digitalP, floating RPM, floating RPMChange, floating RPMIgnOff, floating Tt4, 
// 				floating Tt4FlameOn, floating *WfP, floating *RampTimeP, floating RPMRampCoef,
// 				floating *AltLinVecP, floating *MNLinVecP, floating *NcVecP,
//                 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
//                 struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
//                 struct ControllerInput *ContInputP, floating *NcFANContMtxP, 
// 				floating *N_KpMtxP, floating *N_KiMtxP, floating Tsample,
// 				int *statusP, int NextStatus);

// /* Controls Tt4 during engine early start */
// void TempDecreaseCL(struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
//                 struct ControllerInput *ContInputP, floating *WfP, floating *RampTimeP,
// 				floating Tsample,	int *statusP, int NextStatus);

// /* Accomodation logic */
// void AccomodSR(floating *AccomTimeP, floating MaxAccomTime, floating Ts, int *StartCompleteP, floating *WfP, floating WfAccom);

// /*Starting Logic*/
// void StartLogic(struct ControllerConstants *ContConstP,struct ControlStart *ContStartP, floating RPM, floating Tt4, digital_t *digitalP, floating Tsample);

// /* Closed loop start logic */
// void StartLogicCL(floating RPM, floating Tt4, digital_t *digitalP,
// 				  floating *AltLinVecP, floating *MNLinVecP, floating *NcVecP,
//                   floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
//                   struct ControllerConstants *ContConstP, struct ControlStart *ContStartP, 
//                   struct ControllerInput *ContInputP, floating *NcFANContMtxP, 
// 				  floating *N_KpMtxP, floating *N_KiMtxP, floating Tsample);

// /* Digital Outputs Logic */
// void ManualKeysSR(digital_t *digitalP, keys_t *keysP, floating *fValueP);

// /* Allows fuel flow to be operated manually */
// int OpenLoopSR(struct ControlStart *ContStartP, floating WfStart, floating *WfP);

// /* Executes Start/Shut Off/Emergency logic */
// void OnOffLogicSR(struct EngineOnOff *EngOnOffP, floating Ts);

// /*------------------------------------------------------------------------------*/
// /* FUNCTIONS PRESENT IN THE OLDER VERSION - USE DURING SOFTWARE TRANSITION ONLY */
// /*------------------------------------------------------------------------------*/

// void FuelLogic(struct ControlStart *ContStartP, floating RPM, floating Tt5, FuelRamp_t *FuelSRP, digital_t *digitalP, int EngineShutDown, floating Tsample);

// void ManualKeys(digital_t *digitalP, keys_t *keysP, int EngineShutDown, floating *fValueP);

// void POilLogic(struct ControlStart *ContStartP, floating POil, POil_t *POilSRP, digital_t *digitalp, int EngineShutDown, floating Tsample);

// int Emergency(POil_t *POilSRP, digital_t *digital, FuelRamp_t *FuelSRP, int EmergencyButton);

// void OpenLoop(struct ControlStart *ContStartP, floating StartFuel, floating *fValue, int Emergency, int *ResetP);

/*------------------------------------------------------------------------------*/

#endif  /* SUBIDLE_MODEL_H */
