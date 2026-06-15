
#include <math.h>
#include "getTJ300ARMtxFunctions.h"

getTJ300ARMtx(floating *NcFANContMtx, floating *N_KpMtx, floating *N_KiMtx, floating *FNperContMtx, floating *FNcMaxContMtx, 
     floating *NcMtx, floating *Pt21Mtx, floating *Pt3Mtx, floating *Pt5Mtx, floating *Pt6Mtx, 
     floating *Tt21Mtx, floating *Tt3Mtx, floating *Tt4Mtx, floating *Tt5Mtx, floating *Tt6Mtx, 
     floating *WfMtx, floating *AMtx, floating *BMtx, floating *Pt21DMtx, floating *Pt3DMtx, 
     floating *Pt5DMtx, floating *Pt6DMtx, floating *Tt21DMtx, floating *Tt3DMtx, floating *Tt4DMtx, 
     floating *Tt5DMtx, floating *Tt6DMtx, floating *NcFANMapMtx, floating *WcFANMapMtx, floating *WcFANStallMtx, 
     floating *PRFANMapMtx, floating *PRFANStallMtx, floating *EffFANMapMtx, floating *NcHPTMapMtx, floating *WcHPTMapMtx, 
     floating *PRHPTMapMtx, floating *EffHPTMapMtx, floating *NcHPCMapMtx, floating *WcHPCMapMtx, floating *WcHPCStallMtx, 
     floating *PRHPCMapMtx, floating *PRHPCStallMtx, floating *EffHPCMapMtx, floating *MNLinVec, floating *AltLinVec, 
     floating *DeltaMtx, floating *Ts0Mtx, floating *AwmMtx, floating *AshMtx, floating *BwmMtx, 
     floating *BshMtx, floating *RPMwmMtx, floating *RPMshMtx, floating *Tt4CshMtx, floating *Tt4DshMtx, 
     floating *Tt4shMtx, floating *WfshMtx, floating *ASVec, floating *DSVec, floating *NcVec, 
     floating *NcFANshMtx, floating *WfwmMtx, floating *Pt3shMtx, floating *Pt3DshMtx, floating *Pt21wmMtx, 
     floating *Pt21DwmMtx, floating *Pt3wmMtx, floating *Pt3DwmMtx, floating *Pt5wmMtx, floating *Pt5DwmMtx, 
     floating *Pt6wmMtx, floating *Pt6DwmMtx, floating *Tt21wmMtx, floating *Tt21DwmMtx, floating *Tt3wmMtx, 
     floating *Tt3DwmMtx, floating *Tt4wmMtx, floating *Tt4DwmMtx, floating *Tt5wmMtx, floating *Tt5DwmMtx, 
     floating *Tt6wmMtx, floating *Tt6DwmMtx, floating *Pt21shMtx, floating *Pt21DshMtx, floating *Pt5shMtx, 
     floating *Pt5DshMtx, floating *Pt6shMtx, floating *Pt6DshMtx, floating *Tt21shMtx, floating *Tt21DshMtx, 
     floating *Tt3shMtx, floating *Tt3DshMtx, floating *Tt5shMtx, floating *Tt5DshMtx, floating *Tt6shMtx, 
     floating *Tt6DshMtx)



/* Gets TJ300ARNcFANContMtx Matrix */
 getTJ300ARNcFANContMtx(NcFANContMtx);

/* Gets TJ300ARN_KpMtx Matrix */
 getTJ300ARN_KpMtx(N_KpMtx);

/* Gets TJ300ARN_KiMtx Matrix */
 getTJ300ARN_KiMtx(N_KiMtx);

/* Gets TJ300ARFNperContMtx Matrix */
 getTJ300ARFNperContMtx(FNperContMtx);

/* Gets TJ300ARFNcMaxContMtx Matrix */
 getTJ300ARFNcMaxContMtx(FNcMaxContMtx);

/* Gets TJ300ARNcMtx Matrix */
 getTJ300ARNcMtx(NcMtx);

/* Gets TJ300ARPt21Mtx Matrix */
 getTJ300ARPt21Mtx(Pt21Mtx);

/* Gets TJ300ARPt3Mtx Matrix */
 getTJ300ARPt3Mtx(Pt3Mtx);

/* Gets TJ300ARPt5Mtx Matrix */
 getTJ300ARPt5Mtx(Pt5Mtx);

/* Gets TJ300ARPt6Mtx Matrix */
 getTJ300ARPt6Mtx(Pt6Mtx);

/* Gets TJ300ARTt21Mtx Matrix */
 getTJ300ARTt21Mtx(Tt21Mtx);

/* Gets TJ300ARTt3Mtx Matrix */
 getTJ300ARTt3Mtx(Tt3Mtx);

/* Gets TJ300ARTt4Mtx Matrix */
 getTJ300ARTt4Mtx(Tt4Mtx);

/* Gets TJ300ARTt5Mtx Matrix */
 getTJ300ARTt5Mtx(Tt5Mtx);

/* Gets TJ300ARTt6Mtx Matrix */
 getTJ300ARTt6Mtx(Tt6Mtx);

/* Gets TJ300ARWfMtx Matrix */
 getTJ300ARWfMtx(WfMtx);

/* Gets TJ300ARAMtx Matrix */
 getTJ300ARAMtx(AMtx);

/* Gets TJ300ARBMtx Matrix */
 getTJ300ARBMtx(BMtx);

/* Gets TJ300ARPt21DMtx Matrix */
 getTJ300ARPt21DMtx(Pt21DMtx);

/* Gets TJ300ARPt3DMtx Matrix */
 getTJ300ARPt3DMtx(Pt3DMtx);

/* Gets TJ300ARPt5DMtx Matrix */
 getTJ300ARPt5DMtx(Pt5DMtx);

/* Gets TJ300ARPt6DMtx Matrix */
 getTJ300ARPt6DMtx(Pt6DMtx);

/* Gets TJ300ARTt21DMtx Matrix */
 getTJ300ARTt21DMtx(Tt21DMtx);

/* Gets TJ300ARTt3DMtx Matrix */
 getTJ300ARTt3DMtx(Tt3DMtx);

/* Gets TJ300ARTt4DMtx Matrix */
 getTJ300ARTt4DMtx(Tt4DMtx);

/* Gets TJ300ARTt5DMtx Matrix */
 getTJ300ARTt5DMtx(Tt5DMtx);

/* Gets TJ300ARTt6DMtx Matrix */
 getTJ300ARTt6DMtx(Tt6DMtx);

/* Gets TJ300ARNcFANMapMtx Matrix */
 getTJ300ARNcFANMapMtx(NcFANMapMtx);

/* Gets TJ300ARWcFANMapMtx Matrix */
 getTJ300ARWcFANMapMtx(WcFANMapMtx);

/* Gets TJ300ARWcFANStallMtx Matrix */
 getTJ300ARWcFANStallMtx(WcFANStallMtx);

/* Gets TJ300ARPRFANMapMtx Matrix */
 getTJ300ARPRFANMapMtx(PRFANMapMtx);

/* Gets TJ300ARPRFANStallMtx Matrix */
 getTJ300ARPRFANStallMtx(PRFANStallMtx);

/* Gets TJ300AREffFANMapMtx Matrix */
 getTJ300AREffFANMapMtx(EffFANMapMtx);

/* Gets TJ300ARNcHPTMapMtx Matrix */
 getTJ300ARNcHPTMapMtx(NcHPTMapMtx);

/* Gets TJ300ARWcHPTMapMtx Matrix */
 getTJ300ARWcHPTMapMtx(WcHPTMapMtx);

/* Gets TJ300ARPRHPTMapMtx Matrix */
 getTJ300ARPRHPTMapMtx(PRHPTMapMtx);

/* Gets TJ300AREffHPTMapMtx Matrix */
 getTJ300AREffHPTMapMtx(EffHPTMapMtx);

/* Gets TJ300ARNcHPCMapMtx Matrix */
 getTJ300ARNcHPCMapMtx(NcHPCMapMtx);

/* Gets TJ300ARWcHPCMapMtx Matrix */
 getTJ300ARWcHPCMapMtx(WcHPCMapMtx);

/* Gets TJ300ARWcHPCStallMtx Matrix */
 getTJ300ARWcHPCStallMtx(WcHPCStallMtx);

/* Gets TJ300ARPRHPCMapMtx Matrix */
 getTJ300ARPRHPCMapMtx(PRHPCMapMtx);

/* Gets TJ300ARPRHPCStallMtx Matrix */
 getTJ300ARPRHPCStallMtx(PRHPCStallMtx);

/* Gets TJ300AREffHPCMapMtx Matrix */
 getTJ300AREffHPCMapMtx(EffHPCMapMtx);

/* Gets TJ300ARMNLinVec Matrix */
 getTJ300ARMNLinVec(MNLinVec);

/* Gets TJ300ARAltLinVec Matrix */
 getTJ300ARAltLinVec(AltLinVec);

/* Gets TJ300ARDeltaMtx Matrix */
 getTJ300ARDeltaMtx(DeltaMtx);

/* Gets TJ300ARTs0Mtx Matrix */
 getTJ300ARTs0Mtx(Ts0Mtx);

/* Gets TJ300ARAwmMtx Matrix */
 getTJ300ARAwmMtx(AwmMtx);

/* Gets TJ300ARAshMtx Matrix */
 getTJ300ARAshMtx(AshMtx);

/* Gets TJ300ARBwmMtx Matrix */
 getTJ300ARBwmMtx(BwmMtx);

/* Gets TJ300ARBshMtx Matrix */
 getTJ300ARBshMtx(BshMtx);

/* Gets TJ300ARRPMwmMtx Matrix */
 getTJ300ARRPMwmMtx(RPMwmMtx);

/* Gets TJ300ARRPMshMtx Matrix */
 getTJ300ARRPMshMtx(RPMshMtx);

/* Gets TJ300ARTt4CshMtx Matrix */
 getTJ300ARTt4CshMtx(Tt4CshMtx);

/* Gets TJ300ARTt4DshMtx Matrix */
 getTJ300ARTt4DshMtx(Tt4DshMtx);

/* Gets TJ300ARTt4shMtx Matrix */
 getTJ300ARTt4shMtx(Tt4shMtx);

/* Gets TJ300ARWfshMtx Matrix */
 getTJ300ARWfshMtx(WfshMtx);

/* Gets TJ300ARASVec Matrix */
 getTJ300ARASVec(ASVec);

/* Gets TJ300ARDSVec Matrix */
 getTJ300ARDSVec(DSVec);

/* Gets TJ300ARNcVec Matrix */
 getTJ300ARNcVec(NcVec);

/* Gets TJ300ARNcFANshMtx Matrix */
 getTJ300ARNcFANshMtx(NcFANshMtx);

/* Gets TJ300ARWfwmMtx Matrix */
 getTJ300ARWfwmMtx(WfwmMtx);

/* Gets TJ300ARPt3shMtx Matrix */
 getTJ300ARPt3shMtx(Pt3shMtx);

/* Gets TJ300ARPt3DshMtx Matrix */
 getTJ300ARPt3DshMtx(Pt3DshMtx);

/* Gets TJ300ARPt21wmMtx Matrix */
 getTJ300ARPt21wmMtx(Pt21wmMtx);

/* Gets TJ300ARPt21DwmMtx Matrix */
 getTJ300ARPt21DwmMtx(Pt21DwmMtx);

/* Gets TJ300ARPt3wmMtx Matrix */
 getTJ300ARPt3wmMtx(Pt3wmMtx);

/* Gets TJ300ARPt3DwmMtx Matrix */
 getTJ300ARPt3DwmMtx(Pt3DwmMtx);

/* Gets TJ300ARPt5wmMtx Matrix */
 getTJ300ARPt5wmMtx(Pt5wmMtx);

/* Gets TJ300ARPt5DwmMtx Matrix */
 getTJ300ARPt5DwmMtx(Pt5DwmMtx);

/* Gets TJ300ARPt6wmMtx Matrix */
 getTJ300ARPt6wmMtx(Pt6wmMtx);

/* Gets TJ300ARPt6DwmMtx Matrix */
 getTJ300ARPt6DwmMtx(Pt6DwmMtx);

/* Gets TJ300ARTt21wmMtx Matrix */
 getTJ300ARTt21wmMtx(Tt21wmMtx);

/* Gets TJ300ARTt21DwmMtx Matrix */
 getTJ300ARTt21DwmMtx(Tt21DwmMtx);

/* Gets TJ300ARTt3wmMtx Matrix */
 getTJ300ARTt3wmMtx(Tt3wmMtx);

/* Gets TJ300ARTt3DwmMtx Matrix */
 getTJ300ARTt3DwmMtx(Tt3DwmMtx);

/* Gets TJ300ARTt4wmMtx Matrix */
 getTJ300ARTt4wmMtx(Tt4wmMtx);

/* Gets TJ300ARTt4DwmMtx Matrix */
 getTJ300ARTt4DwmMtx(Tt4DwmMtx);

/* Gets TJ300ARTt5wmMtx Matrix */
 getTJ300ARTt5wmMtx(Tt5wmMtx);

/* Gets TJ300ARTt5DwmMtx Matrix */
 getTJ300ARTt5DwmMtx(Tt5DwmMtx);

/* Gets TJ300ARTt6wmMtx Matrix */
 getTJ300ARTt6wmMtx(Tt6wmMtx);

/* Gets TJ300ARTt6DwmMtx Matrix */
 getTJ300ARTt6DwmMtx(Tt6DwmMtx);

/* Gets TJ300ARPt21shMtx Matrix */
 getTJ300ARPt21shMtx(Pt21shMtx);

/* Gets TJ300ARPt21DshMtx Matrix */
 getTJ300ARPt21DshMtx(Pt21DshMtx);

/* Gets TJ300ARPt5shMtx Matrix */
 getTJ300ARPt5shMtx(Pt5shMtx);

/* Gets TJ300ARPt5DshMtx Matrix */
 getTJ300ARPt5DshMtx(Pt5DshMtx);

/* Gets TJ300ARPt6shMtx Matrix */
 getTJ300ARPt6shMtx(Pt6shMtx);

/* Gets TJ300ARPt6DshMtx Matrix */
 getTJ300ARPt6DshMtx(Pt6DshMtx);

/* Gets TJ300ARTt21shMtx Matrix */
 getTJ300ARTt21shMtx(Tt21shMtx);

/* Gets TJ300ARTt21DshMtx Matrix */
 getTJ300ARTt21DshMtx(Tt21DshMtx);

/* Gets TJ300ARTt3shMtx Matrix */
 getTJ300ARTt3shMtx(Tt3shMtx);

/* Gets TJ300ARTt3DshMtx Matrix */
 getTJ300ARTt3DshMtx(Tt3DshMtx);

/* Gets TJ300ARTt5shMtx Matrix */
 getTJ300ARTt5shMtx(Tt5shMtx);

/* Gets TJ300ARTt5DshMtx Matrix */
 getTJ300ARTt5DshMtx(Tt5DshMtx);

/* Gets TJ300ARTt6shMtx Matrix */
 getTJ300ARTt6shMtx(Tt6shMtx);

/* Gets TJ300ARTt6DshMtx Matrix */
 getTJ300ARTt6DshMtx(Tt6DshMtx);