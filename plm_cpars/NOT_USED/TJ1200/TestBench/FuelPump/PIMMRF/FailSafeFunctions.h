#ifndef FAILSAFE_FUNCTIONS_H
#define FAILSAFE_FUNCTIONS_H


/*		FADEC -- FailSafeFunctoins.h
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % Turbomachine, S�o Jos� dos Campos, SP
 * % July, 2021
 * %
 * %  This is a file that contains various functions for use in the FADEC C-code
 * % *************************************************************************/

/* FeilSafeFunctions.c */

#include "FaultSim_Types.h"
#include "Control_Types.h"

/*-------------------------------------------------*/
/* FUNCTIONS FOR DETERINING EXTERNAL ENGINE STATUS */
/*-------------------------------------------------*/

void WindMillingState(EngineStatus *EngStatusP, double RPM, struct ControllerConstants *ContConstP, double *TimeRPMP, int DetectTime, int status, double Ts);

void ReadyToStartState(EngineStatus *EngStatusP, double RPM, struct ControllerConstants *ContConstP, double *TimeRPMP, int DetectTime, double Ts);

void RPMIdleState(EngineStatus *EngStatusP, double RPM, int status, int statusRef);

void StartingState(EngineStatus *EngStatusP, int statusStart, int status, double StartCom, double StartWord);

void RegimeState(EngineStatus *EngStatusP, int statusIdle, int status, double ThrustCom);

void DegradedState(EngineStatus *EngStatusP, ModelParsFault *ModPFaultP);

void CommandState(EngineStatus *EngStatusP, double ShutOff, double ShutOffWord, 
                  double Emergency, double EmergencyWord,double Fail, double FailWord);

void EngStatusDeff(EngineStatus *EngStatusP, ModelParsFault *ModPFaultP, struct ControllerInput *ContInputP,
                    struct ControlStart *ContStartP, struct ControllerConstants *ContConstP, 
                    int statusStart, int statusIdle,
                    double StartCom, double StartWord, double ThrustCom, 
                    double ShutOff, double ShutOffWord, double Emergency, double EmergencyWord,
                    double Fail, double FailWord, double Ts);

/*--------------------------------------------------------*/
/* FUNCTIONS USED FOR MODEL ESTIMATION AND FAULT ANALYSIS */
/*--------------------------------------------------------*/

void EstIndex(struct EstimatedPars *ModelParsP , double *AltLinVecP, double *MNLinVecP, 
                    double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP, 
                    double *FNperContMtxP, struct ControllerConstants *ContConstP, struct InterpIndex3D *Index3DP);

void TCResCalc(TCFaults *Ts2_0P, TCFaults *Ts2_1P, TCFaults *Tt4_0P, TCFaults *Tt4_1P, 
     TCFaults *Tt4_2P, struct AllResiduals *Ts2ResP, struct AllResiduals *Tt4ResP);

void MedValue(int SensTrust, double *SensVecP, int SensNum, double *MedVal, double ModelVal, int UseModelVal);

int RelError(double Sens0, double Sens1, double MaxError);

void MatchSens(double *SensVec, int *MatchVec, int NumSens, double MaxError);

void Ts2MediumValue(ModelParsFault *ModPFaultP, double *Ts2MedValP, int SensNum, FaultDetect *TrustSensP, struct SensedPars *SensorsP, double Ts2Model,  int MinTrustedSens);

void Pt3MediumValue(ModelParsFault *ModPFaultP, double *Pt3MedValP, int SensNum, FaultDetect *TrustSensP, struct SensedPars *SensorsP, double Pt3Model,  int MinTrustedSens);

void Tt4MediumValue(ModelParsFault *ModPFaultP, double *Tt4MedValP, int SensNum, FaultDetect *TrustSensP, struct SensedPars *SensorsP, double Tt4Model,  int MinTrustedSens);

void RPMMediumValue(ModelParsFault *ModPFaultP, double *RPMMedValP, int SensNum, FaultDetect *TrustSensP, struct SensedPars *SensorsP, double RPMModel,  int MinTrustedSens);

void FaultDetection(double Value, double Threshold, int *CounterP, int MaxValue, uint64_t *FaultStatusP, uint64_t *FaultWarningP, int NumShifts);

void HardFault(double Value, double Threshold, int *CounterP, int MaxValue, FaultDetect *FaultStatusP, FaultDetect *FaultWarningP, int NumShifts);

void SensResCompare(double ResMain, double ResComp, int *CounterP, int MaxValue, SensorFaults *FaultStatusP, SensorFaults *FaultWarningP,  int NumShifts);

void SysResCompare(double ResMain, double ResComp, int *CounterP, int MaxValue, SystemFaults *FaultStatusP, SystemFaults *FaultWarningP,  int NumShifts);

void SensFaultIdent(double ResModel, double Threshold, double ResComp, int *CounterP, int MaxValue, SensorFaults *FaultStatusP, SensorFaults *FaultWarningP,  int NumShifts);

void SysFaultIdent(double ResModel, double Threshold, double ResComp, int *CounterP, int MaxValue, SystemFaults *FaultStatusP, SystemFaults *FaultWarningP,  int NumShifts);

void HardTrust(FaultDetect *TrustSensP, FaultDetect *FaultSHardP, FaultDetect *FaultWHardP);

void SensorTrust(FaultDetect *TrustSensP, SensorFaults *FaultSSensP);

void BlowOut(FaultDetect *TrustSensP, SystemFaults *FaultSSysP, EngineFaults *FaultsStatusP);

void MecLock(FaultDetect *TrustSensP, SystemFaults *FaultSSysP, EngineFaults *FaultsStatusP);

void OverTemp(struct ControllerConstants *ContConstP, FaultDetect *TrustSensP, SystemFaults *FaultSSysP, struct SensedPars *SensorsP, EngineFaults *FaultStatusP);

void OverSpeed(FaultDetect *TrustSensP, SystemFaults *FaultSSysP, struct SensedPars *SensorsP, EngineFaults *FaultStatusP);

void HardFaultUpdt(EngineFaults *FaultStatusP, FaultDetect *FaultHardP);

void SensFaultUpdt(EngineFaults *FaultStatusP, SensorFaults *FaultSensP);

void SysFaultUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP);

void ResCalc(double *Ts0MtxP, struct ControllerConstants *ContConstP,
             double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
             struct EstimatedPars *ModelParsP, struct EstimatedPars *BlowOutParsP, struct SensedPars *SensorsP,
             struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
             struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
             struct AllResiduals *VibrationResP,
             SensorFaults *FaultSSensP, SensorFaults *FaultWSensP,
             SystemFaults *FaultSSysP, SystemFaults *FaultWSysP,
             FaultDetect *HardFStatusP, FaultDetect *HardFWarningP, struct InterpIndex3D *Index3DP);
/* NEW FUNCTION TO BE TESTED */
void Ts2ModelCalc(double *Ts0MtxP, struct ControllerConstants *ContConstP,
             double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
             struct EstimatedPars *ModelParsP, struct InterpIndex3D *Index3DP);
/* NEW FUNCTION TO BE TESTED */
void ResidualsCalc(struct ControllerConstants *ContConstP,
             struct EstimatedPars *ModelParsP, struct SensedPars *SensorsP,
             struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
             struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
             struct AllResiduals *VibrationResP);
/* NEW FUNCTION TO BE TESTED */
void ResProcSens(struct ControllerConstants *ContConstP, struct EstimatedPars *ModelParsP, struct SensedPars *SensorsP,
            struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
            struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
            struct AllResiduals *VibrationResP,
            SensorFaults *FaultSSensP, SensorFaults *FaultWSensP);
/* NEW FUNCTION TO BE TESTED */
void ResProcSys(struct ControllerConstants *ContConstP, struct EstimatedPars *ModelParsP, 
             struct EstimatedPars *BlowOutParsP, struct SensedPars *SensorsP,
             struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
             struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
             struct AllResiduals *VibrationResP,
             SystemFaults *FaultSSysP, SystemFaults *FaultWSysP);
/* NEW FUNCTION TO BE TESTED */
void ResProcBias(struct ControllerConstants *ContConstP, struct EstimatedPars *ModelParsP,
             struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
             struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
             struct AllResiduals *VibrationResP, FaultDetect *HardFStatusP, FaultDetect *HardFWarningP);

void Tt2Calc(double Ts2, struct EstimatedPars *ModelParsP);

void NozzleCalc(struct EstimatedPars *ModelPars, struct ControllerConstants *ContConstP);

double ModelCalc(struct EstimatedPars *ModelParsP,double *DeltaMtxP,
                 double *AltLinVecP, double *MNLinVecP, struct ControllerConstants *ContConstP,
                 double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP, 
                 double *DeltaMtx2DP, double *DeltaMtx2DHP, double *DeltaMtx1DP, double *DeltaMtx1DHP, 
                 double *NcMtxP, double *Tt4MtxP, double *Pt3MtxP,
                 double *AMtxP, double *BMtxP, double *Tt4DMtxP, double *Pt3DMtxP,
                 double *WfMtxP, double *Ts0Mtx,
                 double *Pt5MtxP, double *Pt5DMtxP, double *Tt5MtxP, double *Tt5DMtxP,
                 double *NcHPCMapMtxP, double *WcHPCMapMtxP, double *PRHPCMapMtxP,
                 double *MapHPC1DP, double *MapHPC1DHP, double *MapHPC2DP, double *MapHPC2DHP);

void InitRes(struct AllResiduals *DefaultP);

void PrintFaults(EngineFaults *FaultStatusP, int WhichPrint, int tUpdt);

void PrintEngStatus(EngineStatus *EngStatusP, int tUpdt);


#endif  /* FAILSAFE_FUNCTIONS_H */
