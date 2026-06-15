/*
 * EngineModel.c
 *
 *  Created on: Dec 13, 2019
 *      Author: anton
 */


/* Math lib */
#include <math.h>
//#include "LinMtxFunctions.h"


void getTJ1200Mtx(double *NcFANContMtx, double *N_KpMtx, double *N_KiMtx, double *FNperContMtx, double *FNcMaxContMtx, double *NcMtx, double *Pt21Mtx, double *Pt3Mtx, double *Pt5Mtx, double *Pt6Mtx,
	double *Tt21Mtx, double *Tt3Mtx, double *Tt4Mtx, double *Tt5Mtx, double *Tt6Mtx, double *WfMtx, double *AMtx, double *BMtx, double *Pt21DMtx, double *Pt3DMtx, double *Pt5DMtx, double *Pt6DMtx,
	double *Tt21DMtx, double *Tt3DMtx, double *Tt4DMtx, double *Tt5DMtx, double *Tt6DMtx, double *NcFANMapMtx, double *WcFANMapMtx, double *WcFANStallMtx, double *PRFANMapMtx,
	double *PRFANStallMtx, double *EffFANMapMtx, double *NcHPTMapMtx, double *WcHPTMapMtx, double *PRHPTMapMtx, double *EffHPTMapMtx,
	double *NcHPCMapMtx, double *WcHPCMapMtx, double *WcHPCStallMtx, double *PRHPCMapMtx, double *PRHPCStallMtx, double *EffHPCMapMtx, double *MNLinVec, double *AltLinVec, double *DeltaMtx, double *Ts0Mtx,
    double *AwmMtx, double *AshMtx, double *BwmMtx, double *BshMtx, double *RPMwmMtx, double *RPMshMtx, double *Tt4CshMtx, double *Tt4DshMtx, double *Tt4shMtx, double *WfshMtx,
	double *ASVec, double *DSVec, double *NcVec)

{
	
	/* INITIALIZATION OF CONTOLLER MATRICES */

	/* Steady-State points of interest */

	getTJ1200NcFANContMtx(NcFANContMtx);
	getTJ1200FNperContMtx(FNperContMtx);
    getTJ1200FNcMaxContMtx(FNcMaxContMtx);

	/* Power Management controller gains */

	getTJ1200N_KpMtx(N_KpMtx);
	getTJ1200N_KiMtx(N_KiMtx);
	
	/* Reference Filter Vectors */

	getTJ1200ASVec(ASVec);
	getTJ1200DSVec(DSVec);
	getTJ1200NcVec(NcVec);
	

	/* INITIALIZATION OF MODEL MATRICES */

	/* Steady-State operating points of interest */

	getTJ1200NcFANMtx(NcMtx);
	getTJ1200Pt21Mtx(Pt21Mtx);
	getTJ1200Pt3Mtx(Pt3Mtx);
	getTJ1200Pt5Mtx(Pt5Mtx);
	getTJ1200Pt6Mtx(Pt6Mtx);
	getTJ1200Tt21Mtx(Tt21Mtx);
	getTJ1200Tt3Mtx(Tt3Mtx);
	getTJ1200Tt4Mtx(Tt4Mtx);
	getTJ1200Tt5Mtx(Tt5Mtx);
	getTJ1200Tt6Mtx(Tt6Mtx);
	getTJ1200WfMtx(WfMtx);

	/* Space-State constants matrices */

	getTJ1200AMtx(AMtx);
	getTJ1200BMtx(BMtx);
	getTJ1200Pt21DMtx(Pt21DMtx);
	getTJ1200Pt3DMtx(Pt3DMtx);
	getTJ1200Pt5DMtx(Pt5DMtx);
	getTJ1200Pt6DMtx(Pt6DMtx);
	getTJ1200Tt21DMtx(Tt21DMtx);
	getTJ1200Tt3DMtx(Tt3DMtx);
	getTJ1200Tt4DMtx(Tt4DMtx);
	getTJ1200Tt5DMtx(Tt5DMtx);
	getTJ1200Tt6DMtx(Tt6DMtx);

	/* COMPONENTS MAPS MATRICES */

	/* Fan */

	getTJ1200NcFANMapMtx(NcFANMapMtx);
	getTJ1200WcFANMapMtx(WcFANMapMtx);
	getTJ1200WcFANStallMtx(WcFANStallMtx);
	getTJ1200PRFANMapMtx(PRFANMapMtx);
	getTJ1200PRFANStallMtx(PRFANStallMtx);
	getTJ1200EffFANMapMtx(EffFANMapMtx);

	/* Compressor */

	getTJ1200NcHPCMapMtx(NcHPCMapMtx);
	getTJ1200WcHPCMapMtx(WcHPCMapMtx);
	getTJ1200WcHPCStallMtx(WcHPCStallMtx);
	getTJ1200PRHPCMapMtx(PRHPCMapMtx);
	getTJ1200PRHPCStallMtx(PRHPCStallMtx);
	getTJ1200EffHPCMapMtx(EffHPCMapMtx);

	/* Turbine */

	getTJ1200NcHPTMapMtx(NcHPTMapMtx);
	getTJ1200WcHPTMapMtx(WcHPTMapMtx);
	getTJ1200PRHPTMapMtx(PRHPTMapMtx);
	getTJ1200EffHPTMapMtx(EffHPTMapMtx);
    
    /* Ambient inearizing vectors */
    
    getTJ1200MNLinVec(MNLinVec);
    getTJ1200AltLinVec(AltLinVec);
    getTJ1200DeltaMtx(DeltaMtx);
	getTJ1200Ts0Mtx(Ts0Mtx);
    
    /* Sub-Idle matrices */
    
    getTJ1200AshMtx(AshMtx);
    getTJ1200AwmMtx(AwmMtx);
    getTJ1200BshMtx(BshMtx);
    getTJ1200BwmMtx(BwmMtx);
    getTJ1200RPMshMtx(RPMshMtx);
    getTJ1200RPMwmMtx(RPMwmMtx);
    getTJ1200Tt4CshMtx(Tt4CshMtx);
    getTJ1200Tt4DshMtx(Tt4DshMtx);
    getTJ1200Tt4shMtx(Tt4shMtx);
    getTJ1200WfshMtx(WfshMtx);

}

