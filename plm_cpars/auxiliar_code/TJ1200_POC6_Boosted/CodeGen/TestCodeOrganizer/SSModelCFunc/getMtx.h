/*
 * getMtx.h
 *
 *  Created on: January 29, 2020
 *      Author: Antonio Hadade Neto
 */

#ifndef GETMTX_H
#define GETMTX_H

/* FUNCTION FOR LOADING TJ1200 MATRICES */

void getTJ1200Mtx(double *NcFANContMtx, double *N_KpMtx, double *N_KiMtx, double *FNperContMtx, double *FNcMaxContMtx, double *NcMtx, double *Pt21Mtx, double *Pt3Mtx, double *Pt5Mtx, double *Pt6Mtx,
	double *Tt21Mtx, double *Tt3Mtx, double *Tt4Mtx, double *Tt5Mtx, double *Tt6Mtx, double *WfMtx, double *AMtx, double *BMtx, double *Pt21DMtx, double *Pt3DMtx, double *Pt5DMtx, double *Pt6DMtx,
	double *Tt21DMtx, double *Tt3DMtx, double *Tt4DMtx, double *Tt5DMtx, double *Tt6DMtx, double *NcFANMapMtx, double *WcFANMapMtx, double *WcFANStallMtx, double *PRFANMapMtx,
	double *PRFANStallMtx, double *EffFANMapMtx, double *NcHPTMapMtx, double *WcHPTMapMtx, double *PRHPTMapMtx, double *EffHPTMapMtx,
	double *NcHPCMapMtx, double *WcHPCMapMtx, double *WcHPCStallMtx, double *PRHPCMapMtx, double *PRHPCStallMtx, double *EffHPCMapMtx, double *MNLinVec, double *AltLinVec, double *DeltaMtx, double *Ts0Mtx,
    double *AwmMtx, double *AshMtx, double *BwmMtx, double *BshMtx, double *RPMwmMtx, double *RPMshMtx, double *Tt4CshMtx, double *Tt4DshMtx, double *Tt4shMtx, double *WfshMtx,
	double *ASVec, double *DSVec, double *NcVec);

/* FUNCTION FOR LOADING TF1200 MATRICES */

void getTF1200Mtx(double *NcFANContMtx, double *N_KpMtx, double *N_KiMtx, double *FNperContMtx, double *FNcMaxContMtx, double *NcMtx, double *Pt21Mtx, double *Pt3Mtx, double *Pt5Mtx, double *Pt6Mtx,
	double *Tt21Mtx, double *Tt3Mtx, double *Tt4Mtx, double *Tt5Mtx, double *Tt6Mtx, double *WfMtx, double *AMtx, double *BMtx, double *Pt21DMtx, double *Pt3DMtx, double *Pt5DMtx, double *Pt6DMtx,
	double *Tt21DMtx, double *Tt3DMtx, double *Tt4DMtx, double *Tt5DMtx, double *Tt6DMtx, double *NcFANMapMtx, double *WcFANMapMtx, double *WcFANStallMtx, double *PRFANMapMtx,
	double *PRFANStallMtx, double *EffFANMapMtx, double *NcHPTMapMtx, double *WcHPTMapMtx, double *PRHPTMapMtx, double *EffHPTMapMtx,
	double *NcHPCMapMtx, double *WcHPCMapMtx, double *WcHPCStallMtx, double *PRHPCMapMtx, double *PRHPCStallMtx, double *EffHPCMapMtx, double *MNLinVec, double *AltLinVec, double *DeltaMtx, double *Ts0Mtx,
    double *AwmMtx, double *AshMtx, double *BwmMtx, double *BshMtx, double *RPMwmMtx, double *RPMshMtx, double *Tt4CshMtx, double *Tt4DshMtx, double *Tt4shMtx, double *WfshMtx,
	double *ASVec, double *DSVec, double *NcVec);

/* FUNCTION FOR LOADING GE J85 MATRICES */

void getGEJ85Mtx(double *NcFANContMtx, double *N_KpMtx, double *N_KiMtx, double *FNperContMtx, double *FNcMaxContMtx, double *NcMtx, double *Pt21Mtx, double *Pt3Mtx, double *Pt5Mtx, double *Pt6Mtx,
	double *Tt21Mtx, double *Tt3Mtx, double *Tt4Mtx, double *Tt5Mtx, double *Tt6Mtx, double *WfMtx, double *AMtx, double *BMtx, double *Pt21DMtx, double *Pt3DMtx, double *Pt5DMtx, double *Pt6DMtx,
	double *Tt21DMtx, double *Tt3DMtx, double *Tt4DMtx, double *Tt5DMtx, double *Tt6DMtx, double *NcFANMapMtx, double *WcFANMapMtx, double *WcFANStallMtx, double *PRFANMapMtx,
	double *PRFANStallMtx, double *EffFANMapMtx, double *NcHPTMapMtx, double *WcHPTMapMtx, double *PRHPTMapMtx, double *EffHPTMapMtx,
	double *NcHPCMapMtx, double *WcHPCMapMtx, double *WcHPCStallMtx, double *PRHPCMapMtx, double *PRHPCStallMtx, double *EffHPCMapMtx, double *MNLinVec, double *AltLinVec, double *DeltaMtx, double *Ts0Mtx,
    double *AwmMtx, double *AshMtx, double *BwmMtx, double *BshMtx, double *RPMwmMtx, double *RPMshMtx, double *Tt4CshMtx, double *Tt4DshMtx, double *Tt4shMtx, double *WfshMtx,
	double *ASVec, double *DSVec, double *NcVec);


#endif /* GETTJ1200MTX_H */
