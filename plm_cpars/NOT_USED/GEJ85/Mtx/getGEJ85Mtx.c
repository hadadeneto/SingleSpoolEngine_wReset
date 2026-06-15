/*
 * EngineModel.c
 *
 *  Created on: Dec 13, 2019
 *      Author: anton
 */


/* Math lib */
#include <math.h>
//#include "LinMtxFunctions.h"


void getGEJ85Mtx(double *NcFANContMtx, double *N_KpMtx, double *N_KiMtx, double *FNperContMtx, double *FNcMaxContMtx, double *NcMtx, double *Pt21Mtx, double *Pt3Mtx, double *Pt5Mtx, double *Pt6Mtx,
	double *Tt21Mtx, double *Tt3Mtx, double *Tt4Mtx, double *Tt5Mtx, double *Tt6Mtx, double *WfMtx, double *AMtx, double *BMtx, double *Pt21DMtx, double *Pt3DMtx, double *Pt5DMtx, double *Pt6DMtx,
	double *Tt21DMtx, double *Tt3DMtx, double *Tt4DMtx, double *Tt5DMtx, double *Tt6DMtx, double *NcFANMapMtx, double *WcFANMapMtx, double *WcFANStallMtx, double *PRFANMapMtx,
	double *PRFANStallMtx, double *EffFANMapMtx, double *NcHPTMapMtx, double *WcHPTMapMtx, double *PRHPTMapMtx, double *EffHPTMapMtx,
	double *NcHPCMapMtx, double *WcHPCMapMtx, double *WcHPCStallMtx, double *PRHPCMapMtx, double *PRHPCStallMtx, double *EffHPCMapMtx, double *MNLinVec, double *AltLinVec, double *DeltaMtx, double *Ts0Mtx,
    double *AwmMtx, double *AshMtx, double *BwmMtx, double *BshMtx, double *RPMwmMtx, double *RPMshMtx, double *Tt4CshMtx, double *Tt4DshMtx, double *Tt4shMtx, double *WfshMtx,
	double *ASVec, double *DSVec, double *NcVec)

{
	
	/* INITIALIZATION OF CONTOLLER MATRICES */

	/* Steady-State points of interest */

	getGEJ85NcFANContMtx(NcFANContMtx);
	getGEJ85FNperContMtx(FNperContMtx);
    getGEJ85FNcMaxContMtx(FNcMaxContMtx);

	/* Power Management controller gains */

	getGEJ85N_KpMtx(N_KpMtx);
	getGEJ85N_KiMtx(N_KiMtx);
	
	/* Reference Filter Vectors */

	getTJ1200ASVec(ASVec);
	getTJ1200DSVec(DSVec);
	getTJ1200NcVec(NcVec);

	/* INITIALIZATION OF MODEL MATRICES */

	/* Steady-State operating points of interest */

	getGEJ85NcFANMtx(NcMtx);
	getGEJ85Pt21Mtx(Pt21Mtx);
	getGEJ85Pt3Mtx(Pt3Mtx);
	getGEJ85Pt5Mtx(Pt5Mtx);
	getGEJ85Pt6Mtx(Pt6Mtx);
	getGEJ85Tt21Mtx(Tt21Mtx);
	getGEJ85Tt3Mtx(Tt3Mtx);
	getGEJ85Tt4Mtx(Tt4Mtx);
	getGEJ85Tt5Mtx(Tt5Mtx);
	getGEJ85Tt6Mtx(Tt6Mtx);
	getGEJ85WfMtx(WfMtx);

	/* Space-State constants matrices */

	getGEJ85AMtx(AMtx);
	getGEJ85BMtx(BMtx);
	getGEJ85Pt21DMtx(Pt21DMtx);
	getGEJ85Pt3DMtx(Pt3DMtx);
	getGEJ85Pt5DMtx(Pt5DMtx);
	getGEJ85Pt6DMtx(Pt6DMtx);
	getGEJ85Tt21DMtx(Tt21DMtx);
	getGEJ85Tt3DMtx(Tt3DMtx);
	getGEJ85Tt4DMtx(Tt4DMtx);
	getGEJ85Tt5DMtx(Tt5DMtx);
	getGEJ85Tt6DMtx(Tt6DMtx);

	/* COMPONENTS MAPS MATRICES */

	/* Fan */

	getGEJ85NcFANMapMtx(NcFANMapMtx);
	getGEJ85WcFANMapMtx(WcFANMapMtx);
	getGEJ85WcFANStallMtx(WcFANStallMtx);
	getGEJ85PRFANMapMtx(PRFANMapMtx);
	getGEJ85PRFANStallMtx(PRFANStallMtx);
	getGEJ85EffFANMapMtx(EffFANMapMtx);

	/* Compressor */

	getGEJ85NcHPCMapMtx(NcHPCMapMtx);
	getGEJ85WcHPCMapMtx(WcHPCMapMtx);
	getGEJ85WcHPCStallMtx(WcHPCStallMtx);
	getGEJ85PRHPCMapMtx(PRHPCMapMtx);
	getGEJ85PRHPCStallMtx(PRHPCStallMtx);
	getGEJ85EffHPCMapMtx(EffHPCMapMtx);

	/* Turbine */

	getGEJ85NcHPTMapMtx(NcHPTMapMtx);
	getGEJ85WcHPTMapMtx(WcHPTMapMtx);
	getGEJ85PRHPTMapMtx(PRHPTMapMtx);
	getGEJ85EffHPTMapMtx(EffHPTMapMtx);
    
    /* Ambient linearizing vectors */
    
    getGEJ85MNLinVec(MNLinVec);
    getGEJ85AltLinVec(AltLinVec);
    getGEJ85DeltaMtx(DeltaMtx);
	getTJ1200Ts0Mtx(Ts0Mtx);
    
    /* Sub-Idle matrices */
    
    getGEJ85AshMtx(AshMtx);
    getGEJ85AwmMtx(AwmMtx);
    getGEJ85BshMtx(BshMtx);
    getGEJ85BwmMtx(BwmMtx);
    getGEJ85RPMshMtx(RPMshMtx);
    getGEJ85RPMwmMtx(RPMwmMtx);
    getGEJ85Tt4CshMtx(Tt4CshMtx);
    getGEJ85Tt4DshMtx(Tt4DshMtx);
    getGEJ85Tt4shMtx(Tt4shMtx);
    getGEJ85WfshMtx(WfshMtx);

}

