
#include <math.h>
#include "getTJ1200MtxFunctions.h"

getTJ1200Mtx(double *NcFANContMtx, double *N_KpMtx, double *N_KiMtx, double *FNperContMtx, double *FNcMaxContMtx, 
     double *NcMtx, double *Pt21Mtx, double *Pt3Mtx, double *Pt5Mtx, double *Pt6Mtx, 
     double *Tt21Mtx, double *Tt3Mtx, double *Tt4Mtx, double *Tt5Mtx, double *Tt6Mtx, 
     double *WfMtx, double *AMtx, double *BMtx, double *Pt21DMtx, double *Pt3DMtx, 
     double *Pt5DMtx, double *Pt6DMtx, double *Tt21DMtx, double *Tt3DMtx, double *Tt4DMtx, 
     double *Tt5DMtx, double *Tt6DMtx, double *NcFANMapMtx, double *WcFANMapMtx, double *WcFANStallMtx, 
     double *PRFANMapMtx, double *PRFANStallMtx, double *EffFANMapMtx, double *NcHPTMapMtx, double *WcHPTMapMtx, 
     double *PRHPTMapMtx, double *EffHPTMapMtx, double *NcHPCMapMtx, double *WcHPCMapMtx, double *WcHPCStallMtx, 
     double *PRHPCMapMtx, double *PRHPCStallMtx, double *EffHPCMapMtx, double *MNLinVec, double *AltLinVec, 
     double *DeltaMtx, double *Ts0Mtx, double *AwmMtx, double *AshMtx, double *BwmMtx, 
     double *BshMtx, double *RPMwmMtx, double *RPMshMtx, double *Tt4CshMtx, double *Tt4DshMtx, 
     double *Tt4shMtx, double *WfshMtx, double *ASVec, double *DSVec, double *NcVec)



/* Gets TJ1200NcFANContMtx Matrix */
 getTJ1200NcFANContMtx(NcFANContMtx);

/* Gets TJ1200N_KpMtx Matrix */
 getTJ1200N_KpMtx(N_KpMtx);

/* Gets TJ1200N_KiMtx Matrix */
 getTJ1200N_KiMtx(N_KiMtx);

/* Gets TJ1200FNperContMtx Matrix */
 getTJ1200FNperContMtx(FNperContMtx);

/* Gets TJ1200FNcMaxContMtx Matrix */
 getTJ1200FNcMaxContMtx(FNcMaxContMtx);

/* Gets TJ1200NcMtx Matrix */
 getTJ1200NcMtx(NcMtx);

/* Gets TJ1200Pt21Mtx Matrix */
 getTJ1200Pt21Mtx(Pt21Mtx);

/* Gets TJ1200Pt3Mtx Matrix */
 getTJ1200Pt3Mtx(Pt3Mtx);

/* Gets TJ1200Pt5Mtx Matrix */
 getTJ1200Pt5Mtx(Pt5Mtx);

/* Gets TJ1200Pt6Mtx Matrix */
 getTJ1200Pt6Mtx(Pt6Mtx);

/* Gets TJ1200Tt21Mtx Matrix */
 getTJ1200Tt21Mtx(Tt21Mtx);

/* Gets TJ1200Tt3Mtx Matrix */
 getTJ1200Tt3Mtx(Tt3Mtx);

/* Gets TJ1200Tt4Mtx Matrix */
 getTJ1200Tt4Mtx(Tt4Mtx);

/* Gets TJ1200Tt5Mtx Matrix */
 getTJ1200Tt5Mtx(Tt5Mtx);

/* Gets TJ1200Tt6Mtx Matrix */
 getTJ1200Tt6Mtx(Tt6Mtx);

/* Gets TJ1200WfMtx Matrix */
 getTJ1200WfMtx(WfMtx);

/* Gets TJ1200AMtx Matrix */
 getTJ1200AMtx(AMtx);

/* Gets TJ1200BMtx Matrix */
 getTJ1200BMtx(BMtx);

/* Gets TJ1200Pt21DMtx Matrix */
 getTJ1200Pt21DMtx(Pt21DMtx);

/* Gets TJ1200Pt3DMtx Matrix */
 getTJ1200Pt3DMtx(Pt3DMtx);

/* Gets TJ1200Pt5DMtx Matrix */
 getTJ1200Pt5DMtx(Pt5DMtx);

/* Gets TJ1200Pt6DMtx Matrix */
 getTJ1200Pt6DMtx(Pt6DMtx);

/* Gets TJ1200Tt21DMtx Matrix */
 getTJ1200Tt21DMtx(Tt21DMtx);

/* Gets TJ1200Tt3DMtx Matrix */
 getTJ1200Tt3DMtx(Tt3DMtx);

/* Gets TJ1200Tt4DMtx Matrix */
 getTJ1200Tt4DMtx(Tt4DMtx);

/* Gets TJ1200Tt5DMtx Matrix */
 getTJ1200Tt5DMtx(Tt5DMtx);

/* Gets TJ1200Tt6DMtx Matrix */
 getTJ1200Tt6DMtx(Tt6DMtx);

/* Gets TJ1200NcFANMapMtx Matrix */
 getTJ1200NcFANMapMtx(NcFANMapMtx);

/* Gets TJ1200WcFANMapMtx Matrix */
 getTJ1200WcFANMapMtx(WcFANMapMtx);

/* Gets TJ1200WcFANStallMtx Matrix */
 getTJ1200WcFANStallMtx(WcFANStallMtx);

/* Gets TJ1200PRFANMapMtx Matrix */
 getTJ1200PRFANMapMtx(PRFANMapMtx);

/* Gets TJ1200PRFANStallMtx Matrix */
 getTJ1200PRFANStallMtx(PRFANStallMtx);

/* Gets TJ1200EffFANMapMtx Matrix */
 getTJ1200EffFANMapMtx(EffFANMapMtx);

/* Gets TJ1200NcHPTMapMtx Matrix */
 getTJ1200NcHPTMapMtx(NcHPTMapMtx);

/* Gets TJ1200WcHPTMapMtx Matrix */
 getTJ1200WcHPTMapMtx(WcHPTMapMtx);

/* Gets TJ1200PRHPTMapMtx Matrix */
 getTJ1200PRHPTMapMtx(PRHPTMapMtx);

/* Gets TJ1200EffHPTMapMtx Matrix */
 getTJ1200EffHPTMapMtx(EffHPTMapMtx);

/* Gets TJ1200NcHPCMapMtx Matrix */
 getTJ1200NcHPCMapMtx(NcHPCMapMtx);

/* Gets TJ1200WcHPCMapMtx Matrix */
 getTJ1200WcHPCMapMtx(WcHPCMapMtx);

/* Gets TJ1200WcHPCStallMtx Matrix */
 getTJ1200WcHPCStallMtx(WcHPCStallMtx);

/* Gets TJ1200PRHPCMapMtx Matrix */
 getTJ1200PRHPCMapMtx(PRHPCMapMtx);

/* Gets TJ1200PRHPCStallMtx Matrix */
 getTJ1200PRHPCStallMtx(PRHPCStallMtx);

/* Gets TJ1200EffHPCMapMtx Matrix */
 getTJ1200EffHPCMapMtx(EffHPCMapMtx);

/* Gets TJ1200MNLinVec Matrix */
 getTJ1200MNLinVec(MNLinVec);

/* Gets TJ1200AltLinVec Matrix */
 getTJ1200AltLinVec(AltLinVec);

/* Gets TJ1200DeltaMtx Matrix */
 getTJ1200DeltaMtx(DeltaMtx);

/* Gets TJ1200Ts0Mtx Matrix */
 getTJ1200Ts0Mtx(Ts0Mtx);

/* Gets TJ1200AwmMtx Matrix */
 getTJ1200AwmMtx(AwmMtx);

/* Gets TJ1200AshMtx Matrix */
 getTJ1200AshMtx(AshMtx);

/* Gets TJ1200BwmMtx Matrix */
 getTJ1200BwmMtx(BwmMtx);

/* Gets TJ1200BshMtx Matrix */
 getTJ1200BshMtx(BshMtx);

/* Gets TJ1200RPMwmMtx Matrix */
 getTJ1200RPMwmMtx(RPMwmMtx);

/* Gets TJ1200RPMshMtx Matrix */
 getTJ1200RPMshMtx(RPMshMtx);

/* Gets TJ1200Tt4CshMtx Matrix */
 getTJ1200Tt4CshMtx(Tt4CshMtx);

/* Gets TJ1200Tt4DshMtx Matrix */
 getTJ1200Tt4DshMtx(Tt4DshMtx);

/* Gets TJ1200Tt4shMtx Matrix */
 getTJ1200Tt4shMtx(Tt4shMtx);

/* Gets TJ1200WfshMtx Matrix */
 getTJ1200WfshMtx(WfshMtx);

/* Gets TJ1200ASVec Matrix */
 getTJ1200ASVec(ASVec);

/* Gets TJ1200DSVec Matrix */
 getTJ1200DSVec(DSVec);

/* Gets TJ1200NcVec Matrix */
 getTJ1200NcVec(NcVec);