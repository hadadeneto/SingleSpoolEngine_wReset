/*
 * EngineModel.h
 *
 *  Created on: Dec 13, 2019
 *      Author: anton
 */

#ifndef MODELCFUNC_ENGINEMODEL_H_
#define MODELCFUNC_ENGINEMODEL_H_

#include "../FADEC_Defines_H/FaultSim_Types.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"

// void EngineModel(struct AmbientPars *AmbientP, struct EngineOutput *EngOutputP, floating WfIn,
// 				 floating Altitude, floating MN, floating dT, floating Mwm, int Ignition, floating *NcMtxP, floating *Pt21MtxP, floating *Pt3MtxP, floating *Pt5MtxP, floating *Pt6MtxP,
// 				 floating *Tt21MtxP, floating *Tt3MtxP, floating *Tt4MtxP, floating *Tt5MtxP, floating *Tt6MtxP, floating *WfMtxP, floating *AMtxP, floating *BMtxP,
// 				 floating *Pt21DMtxP, floating *Pt3DMtxP, floating *Pt5DMtxP, floating *Pt6DMtxP, floating *Tt21DMtxP, floating *Tt3DMtxP, floating *Tt4DMtxP, floating *Tt5DMtxP, floating *Tt6DMtxP,
// 				 floating *NcFANMapMtxP, floating *WcFANMapMtxP, floating *WcFANStallMtxP, floating *PRFANMapMtxP, floating *PRFANStallMtxP, floating *EffFANMapMtxP,
// 				 floating *NcHPCMapMtxP, floating *WcHPCMapMtxP, floating *WcHPCStallMtxP, floating *PRHPCMapMtxP, floating *PRHPCStallMtxP, floating *EffHPCMapMtxP,
// 				 floating *NcHPTMapMtxP, floating *WcHPTMapMtxP, floating *PRHPTMapMtxP, floating *EffHPTMapMtxP, struct EnginePars *ParsP,
// 				 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
// 				 floating *MapFAN2DP, floating *MapFAN2DHP, floating *MapFAN1DP, floating *MapFAN1DHP, floating *MNLinVecP,
// 				 floating *MapHPC2DP, floating *MapHPC2DHP, floating *MapHPC1DP, floating *MapHPC1DHP,
// 				 floating *AwmMtxP, floating *AshMtxP, floating *BwmMtxP, floating *BshMtxP, floating *RPMwmMtxP, floating *RPMshMtxP,
// 				 floating *NcFANshMtxP, floating *Pt21shMtxP, floating *Pt21wmMtxP,
// 				 floating *Pt21DshMtxP, floating *Pt21DwmMtxP, floating *Pt3shMtxP, floating *Pt3wmMtxP,
// 				 floating *Pt3DshMtxP, floating *Pt3DwmMtxP, floating *Pt5shMtxP, floating *Pt5wmMtxP, floating *Pt5DshMtxP, floating *Pt5DwmMtxP, floating *Pt6shMtxP, floating *Pt6wmMtxP, 
// 				 floating *Pt6DshMtxP, floating *Pt6DwmMtxP, floating *Tt21shMtxP, floating *Tt21wmMtxP, floating *Tt21DshMtxP, floating *Tt21DwmMtxP,
// 				 floating *Tt3shMtxP, floating *Tt3wmMtxP, floating *Tt3DshMtxP, floating *Tt3DwmMtxP, floating *Tt4shMtxP, floating *Tt4wmMtxP, floating *Tt4CshMtxP, floating *Tt4DshMtxP, floating *Tt4DwmMtxP, 
// 				 floating *Tt5shMtxP, floating *Tt5wmMtxP, floating *Tt5DshMtxP, floating *Tt5DwmMtxP, floating *Tt6shMtxP, floating *Tt6wmMtxP, floating *Tt6DshMtxP, floating *Tt6DwmMtxP, floating *WfshMtxP, floating *WfwmMtxP,
// 				 EngineFaults *FaultsP, struct SensedPars *SensorsP,
// 				 floating Ts);

void EngineModel(struct AmbientPars *AmbientP, struct EngineOutput *EngOutputP, floating WfIn,
				 floating Altitude, floating MN, floating dT, floating Mwm, int Ignition, floating *NcMtxP, floating *Pt21MtxP, floating *Pt3MtxP, floating *Pt5MtxP, floating *Pt6MtxP,
				 floating *Tt21MtxP, floating *Tt3MtxP, floating *Tt4MtxP, floating *Tt5MtxP, floating *Tt6MtxP, floating *WfMtxP, floating *AMtxP, floating *BMtxP,
				 floating *Pt21DMtxP, floating *Pt3DMtxP, floating *Pt5DMtxP, floating *Pt6DMtxP, floating *Tt21DMtxP, floating *Tt3DMtxP, floating *Tt4DMtxP, floating *Tt5DMtxP, floating *Tt6DMtxP,
				 floating *NcFANMapMtxP, floating *WcFANMapMtxP, floating *WcFANStallMtxP, floating *PRFANMapMtxP, floating *PRFANStallMtxP, floating *EffFANMapMtxP,
				 floating *NcHPCMapMtxP, floating *WcHPCMapMtxP, floating *WcHPCStallMtxP, floating *PRHPCMapMtxP, floating *PRHPCStallMtxP, floating *EffHPCMapMtxP,
				 floating *NcHPTMapMtxP, floating *WcHPTMapMtxP, floating *PRHPTMapMtxP, floating *EffHPTMapMtxP, struct EnginePars *ParsP,
				 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
				 floating *MapFAN2DP, floating *MapFAN2DHP, floating *MapFAN1DP, floating *MapFAN1DHP, floating *MNLinVecP,
				 floating *MapHPC2DP, floating *MapHPC2DHP, floating *MapHPC1DP, floating *MapHPC1DHP,
				 floating *AwmMtxP, floating *AshMtxP, floating *BwmMtxP, floating *BshMtxP, floating *RPMwmMtxP, floating *RPMshMtxP,
				 floating *NcFANshMtxP, floating *Pt21shMtxP, floating *Pt21wmMtxP,
				 floating *Pt21DshMtxP, floating *Pt21DwmMtxP, floating *Pt3shMtxP, floating *Pt3wmMtxP,
				 floating *Pt3DshMtxP, floating *Pt3DwmMtxP, floating *Pt5shMtxP, floating *Pt5wmMtxP, floating *Pt5DshMtxP, floating *Pt5DwmMtxP, floating *Pt6shMtxP, floating *Pt6wmMtxP,
				 floating *Pt6DshMtxP, floating *Pt6DwmMtxP, floating *Tt21shMtxP, floating *Tt21wmMtxP, floating *Tt21DshMtxP, floating *Tt21DwmMtxP,
				 floating *Tt3shMtxP, floating *Tt3wmMtxP, floating *Tt3DshMtxP, floating *Tt3DwmMtxP, floating *Tt4shMtxP, floating *Tt4wmMtxP, floating *Tt4CshMtxP, floating *Tt4DshMtxP, floating *Tt4DwmMtxP, 
				 floating *Tt5shMtxP, floating *Tt5wmMtxP, floating *Tt5DshMtxP, floating *Tt5DwmMtxP, floating *Tt6shMtxP, floating *Tt6wmMtxP, floating *Tt6DshMtxP, floating *Tt6DwmMtxP, floating *WfshMtxP, floating *WfwmMtxP,
				 EngineFaults *FaultsP, struct SensedPars *SensorsP,
				 floating Ts, int ExtFPModel, int FlightStart);


#endif /* MODELCFUNC_ENGINEMODEL_H_ */
