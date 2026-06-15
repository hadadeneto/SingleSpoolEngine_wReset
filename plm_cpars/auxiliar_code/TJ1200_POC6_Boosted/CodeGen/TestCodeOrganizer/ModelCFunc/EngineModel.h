/*
 * EngineModel.h
 *
 *  Created on: Dec 13, 2019
 *      Author: anton
 */

#ifndef MODELCFUNC_ENGINEMODEL_H_
#define MODELCFUNC_ENGINEMODEL_H_

#include "FaultSim_Types.h"

void EngineModel(struct AmbientPars *AmbientP, struct EngineOutput *EngOutputP, double Wf,
	double Altitude, double MN, double dT, double Mwm, int Ignition, double *NcMtxP, double *Pt21MtxP, double *Pt3MtxP, double *Pt5MtxP, double *Pt6MtxP,
	double *Tt21MtxP, double *Tt3MtxP, double *Tt4MtxP, double *Tt5MtxP, double *Tt6MtxP, double *WfMtxP, double *AMtxP, double *BMtxP,
	double *Pt21DMtxP, double *Pt3DMtxP, double *Pt5DMtxP, double *Pt6DMtxP, double *Tt21DMtxP, double *Tt3DMtxP, double *Tt4DMtxP, double *Tt5DMtxP, double *Tt6DMtxP,
	double *NcFANMapMtxP, double *WcFANMapMtxP, double *WcFANStallMtxP, double *PRFANMapMtxP, double *PRFANStallMtxP, double *EffFANMapMtxP,
	double *NcHPCMapMtxP, double *WcHPCMapMtxP, double *WcHPCStallMtxP, double *PRHPCMapMtxP, double *PRHPCStallMtxP, double *EffHPCMapMtxP,
	double *NcHPTMapMtxP, double *WcHPTMapMtxP, double *PRHPTMapMtxP, double *EffHPTMapMtxP, struct EnginePars *ParsP,
	double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
	double *MapFAN2DP, double *MapFAN2DHP, double *MapFAN1DP, double *MapFAN1DHP, double *MNLinVecP,
	double *MapHPC2DP, double *MapHPC2DHP, double *MapHPC1DP, double *MapHPC1DHP, 
    double *AwmMtxP, double *AshMtxP, double *BwmMtxP, double *BshMtxP, double *RPMwmMtxP, double *RPMshMtxP, 
    double *Tt4CshMtxP, double *Tt4DshMtxP, double *Tt4shMtxP, double *WfshMtxP,
    EngineFaults *FaultsP, struct SensedPars *SensorsP,
    double Ts);



#endif /* MODELCFUNC_ENGINEMODEL_H_ */
