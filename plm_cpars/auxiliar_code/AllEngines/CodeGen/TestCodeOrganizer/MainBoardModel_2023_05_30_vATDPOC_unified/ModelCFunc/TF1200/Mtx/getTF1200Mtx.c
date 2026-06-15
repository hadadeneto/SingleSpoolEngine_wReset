/*
 * EngineModel.c
 *
 *  Created on: Dec 13, 2019
 *      Author: anton
 */


/* Math lib */
#include <math.h>
//#include "LinMtxFunctions.h"


void getTF1200Mtx(double *NcFANContMtx, double *N_KpMtx, double *N_KiMtx, double *FNperContMtx, double *FNcMaxContMtx, double *NcMtx, double *Pt21Mtx, double *Pt3Mtx, double *Pt5Mtx, double *Pt6Mtx,
	double *Tt21Mtx, double *Tt3Mtx, double *Tt4Mtx, double *Tt5Mtx, double *Tt6Mtx, double *WfMtx, double *AMtx, double *BMtx, double *Pt21DMtx, double *Pt3DMtx, double *Pt5DMtx, double *Pt6DMtx,
	double *Tt21DMtx, double *Tt3DMtx, double *Tt4DMtx, double *Tt5DMtx, double *Tt6DMtx, double *NcFANMapMtx, double *WcFANMapMtx, double *WcFANStallMtx, double *PRFANMapMtx,
	double *PRFANStallMtx, double *EffFANMapMtx, double *NcHPTMapMtx, double *WcHPTMapMtx, double *PRHPTMapMtx, double *EffHPTMapMtx,
	double *NcHPCMapMtx, double *WcHPCMapMtx, double *WcHPCStallMtx, double *PRHPCMapMtx, double *PRHPCStallMtx, double *EffHPCMapMtx, double *MNLinVec, double *AltLinVec, double *DeltaMtx, double *Ts0Mtx,
    double *AwmMtx, double *AshMtx, double *BwmMtx, double *BshMtx, double *RPMwmMtx, double *RPMshMtx, double *Tt4CshMtx, double *Tt4DshMtx, double *Tt4shMtx, double *WfshMtx,
	double *ASVec, double *DSVec, double *NcVec)
{
	
	/* INITIALIZATION OF CONTOLLER MATRICES */

	/* Steady-State points of interest */

	getTF1200NcFANContMtx(NcFANContMtx);
	getTF1200FNperContMtx(FNperContMtx);
    getTF1200FNcMaxContMtx(FNcMaxContMtx);

	/* Power Management controller gains */

	getTF1200N_KpMtx(N_KpMtx);
	getTF1200N_KiMtx(N_KiMtx);

	/* Reference Filter Vectors */

	getTF1200ASVec(ASVec);
	getTF1200DSVec(DSVec);
	getTF1200NcVec(NcVec);
	

	/* INITIALIZATION OF MODEL MATRICES */

	/* Steady-State operating points of interest */

	getTF1200NcFANMtx(NcMtx);
	getTF1200Pt21Mtx(Pt21Mtx);
	getTF1200Pt3Mtx(Pt3Mtx);
	getTF1200Pt5Mtx(Pt5Mtx);
	getTF1200Pt6Mtx(Pt6Mtx);
	getTF1200Tt21Mtx(Tt21Mtx);
	getTF1200Tt3Mtx(Tt3Mtx);
	getTF1200Tt4Mtx(Tt4Mtx);
	getTF1200Tt5Mtx(Tt5Mtx);
	getTF1200Tt6Mtx(Tt6Mtx);
	getTF1200WfMtx(WfMtx);

	/* Space-State constants matrices */

	getTF1200AMtx(AMtx);
	getTF1200BMtx(BMtx);
	getTF1200Pt21DMtx(Pt21DMtx);
	getTF1200Pt3DMtx(Pt3DMtx);
	getTF1200Pt5DMtx(Pt5DMtx);
	getTF1200Pt6DMtx(Pt6DMtx);
	getTF1200Tt21DMtx(Tt21DMtx);
	getTF1200Tt3DMtx(Tt3DMtx);
	getTF1200Tt4DMtx(Tt4DMtx);
	getTF1200Tt5DMtx(Tt5DMtx);
	getTF1200Tt6DMtx(Tt6DMtx);

	/* COMPONENTS MAPS MATRICES */

	/* Fan */

	getTF1200NcFANMapMtx(NcFANMapMtx);
	getTF1200WcFANMapMtx(WcFANMapMtx);
	getTF1200WcFANStallMtx(WcFANStallMtx);
	getTF1200PRFANMapMtx(PRFANMapMtx);
	getTF1200PRFANStallMtx(PRFANStallMtx);
	getTF1200EffFANMapMtx(EffFANMapMtx);

	/* Compressor */

	getTF1200NcHPCMapMtx(NcHPCMapMtx);
	getTF1200WcHPCMapMtx(WcHPCMapMtx);
	getTF1200WcHPCStallMtx(WcHPCStallMtx);
	getTF1200PRHPCMapMtx(PRHPCMapMtx);
	getTF1200PRHPCStallMtx(PRHPCStallMtx);
	getTF1200EffHPCMapMtx(EffHPCMapMtx);

	/* Turbine */

	getTF1200NcHPTMapMtx(NcHPTMapMtx);
	getTF1200WcHPTMapMtx(WcHPTMapMtx);
	getTF1200PRHPTMapMtx(PRHPTMapMtx);
	getTF1200EffHPTMapMtx(EffHPTMapMtx);
    
    /* Ambient linearizing vectors */
    
    getTF1200MNLinVec(MNLinVec);
    getTF1200AltLinVec(AltLinVec);
    getTF1200DeltaMtx(DeltaMtx);
	getTF1200Ts0Mtx(Ts0Mtx);
    
    /* Sub-Idle matrices */
    
    getTF1200AshMtx(AshMtx);
    getTF1200AwmMtx(AwmMtx);
    getTF1200BshMtx(BshMtx);
    getTF1200BwmMtx(BwmMtx);
    getTF1200RPMshMtx(RPMshMtx);
    getTF1200RPMwmMtx(RPMwmMtx);
    getTF1200Tt4CshMtx(Tt4CshMtx);
    getTF1200Tt4DshMtx(Tt4DshMtx);
    getTF1200Tt4shMtx(Tt4shMtx);
    getTF1200WfshMtx(WfshMtx);

}

