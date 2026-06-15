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

#include "../FADEC_Defines_H/FaultSim_Types.h"
#include "../FADEC_Defines_H/Control_Types.h"
#include "../FADEC_Defines_H/Interpolation_Types.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"

/*-------------------------------------------------*/
/* FUNCTIONS FOR DETERINING EXTERNAL ENGINE STATUS */
/*-------------------------------------------------*/

void WindMillingState(EngineStatus *EngStatusP, floating RPM, struct ControllerConstants *ContConstP, floating *TimeRPMP, floating DetectTime, floating Ts);

void ReadyToStartState(EngineStatus *EngStatusP, floating RPM, struct ControllerConstants *ContConstP, floating *TimeRPMP, floating DetectTime, floating Ts);

void RPMIdleState(EngineStatus *EngStatusP, int status, int statusRef);

void StartingState(EngineStatus *EngStatusP, int statusStart, int status, int StartCom, int StartWord);

void RegimeState(EngineStatus *EngStatusP, int statusIdle, int status, floating ThrustCom);

void DegradedState(EngineStatus *EngStatusP, ModelParsFault *ModPFaultP);

void CommandState(EngineStatus *EngStatusP, int ShutOff, int ShutOffWord, 
                  int Emergency, int EmergencyWord,int Fail, int FailWord);

void EngStatusDeff(EngineStatus *EngStatusP, ModelParsFault *ModPFaultP, struct ControllerInput *ContInputP,
                    struct ControlStart *ContStartP, struct ControllerConstants *ContConstP, 
                    int statusStart, int statusIdle,
                    int StartCom, int StartWord, int ThrustCom, 
                    int ShutOff, int ShutOffWord, int Emergency, int EmergencyWord,
                    int Fail, int FailWord, floating Ts);

void IdleToRegime(EngineStatus *EngStatusP, struct ControllerInput *ContInputP, floating Reference, floating RefMin, floating IdleRef, floating *FNpc, int LeverMode);

/*-----------------------------------------*/
/* FUNCTIONS FOR IDENTIFYING BOOSTER STATE */
/*-----------------------------------------*/

void BoosterProtect(struct ControllerConstants *ContConstP, struct ControllerInput *ContInputP, floating Delta, int BoosterLStatus, int BoosterRStatus, floating Ts);

/*--------------------------------------------------------*/
/* FUNCTIONS USED FOR MODEL ESTIMATION AND FAULT ANALYSIS */
/*--------------------------------------------------------*/

void EstIndex(struct EstimatedPars *ModelParsP , floating *AltLinVecP, floating *MNLinVecP, 
                    floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, 
                    floating *FNperContMtxP, struct ControllerConstants *ContConstP, struct InterpIndex3D *Index3DP);

void TCResCalc(TCFaults *Ts2_0P, TCFaults *Ts2_1P, TCFaults *Tt4_0P, TCFaults *Tt4_1P, 
               TCFaults *Tt4_2P, TCFaults *TB_0P, TCFaults *TB_1P, TCFaults *TB_2P,
               struct AllResiduals *Ts2ResP, struct AllResiduals *Tt4ResP, struct AllResiduals *TBearResP);

void MedValue(int SensTrust, floating *SensVecP, int SensNum, floating *MedVal, floating ModelVal, int UseModelVal);

int RelError(floating Sens0, floating Sens1, floating MaxError);

void MatchSens(floating *SensVec, int *MatchVec, int NumSens, floating MaxError);

void Ts2MediumValue(ModelParsFault *ModPFaultP, floating *Ts2MedValP, int SensNum, FaultDetect *TrustSensP, struct SensedPars *SensorsP, floating Ts2Model,  int MinTrustedSens);

void Pt3MediumValue(ModelParsFault *ModPFaultP, floating *Pt3MedValP, int SensNum, FaultDetect *TrustSensP, struct SensedPars *SensorsP, floating Pt3Model,  int MinTrustedSens);

void Tt4MediumValue(ModelParsFault *ModPFaultP, floating *Tt4MedValP, int SensNum, FaultDetect *TrustSensP, struct SensedPars *SensorsP, floating Tt4Model,  int MinTrustedSens);

void RPMMediumValue(ModelParsFault *ModPFaultP, floating *RPMMedValP, int SensNum, FaultDetect *TrustSensP, struct SensedPars *SensorsP, floating RPMModel,  int MinTrustedSens);

void FaultDetection(floating Value, floating Threshold, int *CounterP, int MaxValue, uint64_t *FaultStatusP, uint64_t *FaultWarningP, int NumShifts);

void BitIsTrue(int NumShifts, uint64_t AllBits, int *BitTrue);

void HardFault(floating Value, floating Threshold, int *CounterP, int MaxValue, FaultDetect *FaultStatusP, FaultDetect *FaultWarningP, int NumShifts);

void SensResCompare(floating ResMain, floating ResComp, int *CounterP, int MaxValue, SensorFaults *FaultStatusP, SensorFaults *FaultWarningP,  int NumShifts);

void SysResCompare(floating ResMain, floating ResComp, int *CounterP, int MaxValue, SystemFaults *FaultStatusP, SystemFaults *FaultWarningP,  int NumShifts);

void SensFaultIdent(floating ResModel, floating Threshold, floating ResComp, int *CounterP, int MaxValue, SensorFaults *FaultStatusP, SensorFaults *FaultWarningP,  int NumShifts);

void SysFaultIdent(floating ResModel, floating Threshold, floating ResComp, int *CounterP, int MaxValue, SystemFaults *FaultStatusP, SystemFaults *FaultWarningP,  int NumShifts);

void HardTrust(FaultDetect *TrustSensP, FaultDetect *FaultSHardP, FaultDetect *FaultWHardP);

//void SensorTrust(FaultDetect *TrustSensP, SensorFaults *FaultSSensP);
void SensorTrust(FaultDetect *TrustSensP, SensorFaults *FaultSSensP, SensorFaults *FaultWSensP);

void BlowOut(FaultDetect *TrustSensP, SystemFaults *FaultSSysP, EngineFaults *FaultsStatusP);

void MecLock(FaultDetect *TrustSensP, SystemFaults *FaultSSysP, EngineFaults *FaultsStatusP);

void OverTemp(struct ControllerConstants *ContConstP, FaultDetect *TrustSensP, SystemFaults *FaultSSysP, struct SensedPars *SensorsP, EngineFaults *FaultStatusP);

void OverSpeed(FaultDetect *TrustSensP, SystemFaults *FaultSSysP, struct SensedPars *SensorsP, EngineFaults *FaultStatusP);

void CAN1MissComm(EngineFaults *FaultStatusP, EngineStatus *EngStatusP, int *OnOffCommP, int EmmergencyCommand, int ShutDownCommand);

void POilHighUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP);

void POilLowUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP);

void PFuelHighUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP);

void PFuelLowUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP);

void VibHighUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP);

void TB0HighUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP);

void TB1HighUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP);

void TB2HighUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP);

void SensAnalisysAuthorize(SensorFaults *FaultSensAuthP, struct ControlStart *ContStartP, struct ControllerInput *ContInputP, EngineStatus *EngStatusP, int StartAnalysis);

void SysAnalisysAuthorize(SystemFaults *FaultSysAuthP, struct ControlStart *ContStartP, struct ControllerInput *ContInputP, EngineStatus *EngStatusP, int StartAnalysis);

void BiasAnalisysAuthorize(FaultDetect *FaultHardAuthP, struct ControlStart *ContStartP, struct ControllerInput *ContInputP, EngineStatus *EngStatusP, int StartAnalysis);

void HardFaultUpdt(EngineFaults *FaultStatusP, FaultDetect *FaultHardP, FaultDetect *FaultHardAuthP);

void SensFaultUpdt(EngineFaults *FaultStatusP, SensorFaults *FaultSensP, SensorFaults *FaultSensAuthP);

void SysFaultUpdt(EngineFaults *FaultStatusP, SystemFaults *FaultSysP, SystemFaults *FaultSysAuthP);

void ResCalc(floating *Ts0MtxP, struct ControllerConstants *ContConstP,
             floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
             struct EstimatedPars *ModelParsP, struct EstimatedPars *BlowOutParsP, struct SensedPars *SensorsP,
             struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
             struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
             struct AllResiduals *VibrationResP,
             SensorFaults *FaultSSensP, SensorFaults *FaultWSensP,
             SystemFaults *FaultSSysP, SystemFaults *FaultWSysP,
             FaultDetect *HardFStatusP, FaultDetect *HardFWarningP, struct InterpIndex3D *Index3DP);

void Ts2ModelCalc(floating *Ts0MtxP, struct ControllerConstants *ContConstP,
             floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
             struct EstimatedPars *ModelParsP, struct InterpIndex3D *Index3DP);

void ResidualsCalc(struct ControllerConstants *ContConstP,
             struct EstimatedPars *ModelParsP, struct SensedPars *SensorsP,
             struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
             struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
             struct AllResiduals *VibrationResP, struct AllResiduals *TBearResP);

void ResProcSens(struct ControllerConstants *ContConstP, struct EstimatedPars *ModelParsP, struct SensedPars *SensorsP,
            struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
            struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
            struct AllResiduals *VibrationResP, struct AllResiduals *TBearResP, 
            SensorFaults *FaultSSensP, SensorFaults *FaultWSensP, SensorFaults *FaultSensAuthP);

void ResProcSys(struct ControllerConstants *ContConstP, struct EstimatedPars *ModelParsP, 
             struct EstimatedPars *BlowOutParsP, struct SensedPars *SensorsP,
             struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
             struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
             struct AllResiduals *VibrationResP, struct AllResiduals *TBearResP,
             SystemFaults *FaultSSysP, SystemFaults *FaultWSysP, SystemFaults *FaultSysAuthP,
             FaultDetect *CANFaultsP, struct ControlStart *ContStartP);

void ResProcBias(struct ControllerConstants *ContConstP, struct EstimatedPars *ModelParsP,
             struct AllResiduals *Ts2ResP, struct AllResiduals *Pt3ResP, struct AllResiduals *Tt4ResP,
             struct AllResiduals *RPMResP, struct AllResiduals *POilResP, struct AllResiduals *PFuelResP,
             struct AllResiduals *VibrationResP, FaultDetect *HardFStatusP, FaultDetect *HardFWarningP, FaultDetect *HardFAuthP);

void TBearControl(struct ControllerGeneral *ContGenOilP, struct ControllerGeneral *ContGenEmptyP, EngineStatus *EngStatusP, struct ControllerConstants *ContConstP, struct SensedPars *SensorsP, floating ManualRef, floating RPM, int AutoMode, floating Ts);

void Tt2Calc(floating Ts2, struct EstimatedPars *ModelParsP);

void NozzleCalc(struct EstimatedPars *ModelPars, struct ControllerConstants *ContConstP);

void ModelCalc(struct EstimatedPars *ModelParsP,floating *DeltaMtxP,
                 floating *AltLinVecP, floating *MNLinVecP, struct ControllerConstants *ContConstP,
                 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, 
                 floating *DeltaMtx2DP, floating *DeltaMtx2DHP, floating *DeltaMtx1DP, floating *DeltaMtx1DHP, 
                 floating *NcMtxP, floating *Tt4MtxP, floating *Pt3MtxP,
                 floating *AMtxP, floating *BMtxP, floating *Tt4DMtxP, floating *Pt3DMtxP,
                 floating *WfMtxP, floating *Ts0Mtx,
                 floating *Pt5MtxP, floating *Pt5DMtxP, floating *Tt5MtxP, floating *Tt5DMtxP,
                 floating *NcHPCMapMtxP, floating *WcHPCMapMtxP, floating *PRHPCMapMtxP,
                 floating *MapHPC1DP, floating *MapHPC1DHP, floating *MapHPC2DP, floating *MapHPC2DHP);

void InitRes(struct AllResiduals *DefaultP);

void PrintFaults(EngineFaults *FaultStatusP, int WhichPrint, int tUpdt);

void PrintEngStatus(EngineStatus *EngStatusP, int tUpdt);


#endif  /* FAILSAFE_FUNCTIONS_H */
