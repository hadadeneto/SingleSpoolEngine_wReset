
#include <math.h>
#include "getTJ1200MtxFunctions.h"

getTJ1200Mtx(floating *NcFANContMtx, floating *N_KpMtx, floating *N_KiMtx, floating *FNperContMtx, floating *FNcMaxContMtx, 
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

/* Gets TJ1200NcFANshMtx Matrix */
 getTJ1200NcFANshMtx(NcFANshMtx);

/* Gets TJ1200WfwmMtx Matrix */
 getTJ1200WfwmMtx(WfwmMtx);

/* Gets TJ1200Pt3shMtx Matrix */
 getTJ1200Pt3shMtx(Pt3shMtx);

/* Gets TJ1200Pt3DshMtx Matrix */
 getTJ1200Pt3DshMtx(Pt3DshMtx);

/* Gets TJ1200Pt21wmMtx Matrix */
 getTJ1200Pt21wmMtx(Pt21wmMtx);

/* Gets TJ1200Pt21DwmMtx Matrix */
 getTJ1200Pt21DwmMtx(Pt21DwmMtx);

/* Gets TJ1200Pt3wmMtx Matrix */
 getTJ1200Pt3wmMtx(Pt3wmMtx);

/* Gets TJ1200Pt3DwmMtx Matrix */
 getTJ1200Pt3DwmMtx(Pt3DwmMtx);

/* Gets TJ1200Pt5wmMtx Matrix */
 getTJ1200Pt5wmMtx(Pt5wmMtx);

/* Gets TJ1200Pt5DwmMtx Matrix */
 getTJ1200Pt5DwmMtx(Pt5DwmMtx);

/* Gets TJ1200Pt6wmMtx Matrix */
 getTJ1200Pt6wmMtx(Pt6wmMtx);

/* Gets TJ1200Pt6DwmMtx Matrix */
 getTJ1200Pt6DwmMtx(Pt6DwmMtx);

/* Gets TJ1200Tt21wmMtx Matrix */
 getTJ1200Tt21wmMtx(Tt21wmMtx);

/* Gets TJ1200Tt21DwmMtx Matrix */
 getTJ1200Tt21DwmMtx(Tt21DwmMtx);

/* Gets TJ1200Tt3wmMtx Matrix */
 getTJ1200Tt3wmMtx(Tt3wmMtx);

/* Gets TJ1200Tt3DwmMtx Matrix */
 getTJ1200Tt3DwmMtx(Tt3DwmMtx);

/* Gets TJ1200Tt4wmMtx Matrix */
 getTJ1200Tt4wmMtx(Tt4wmMtx);

/* Gets TJ1200Tt4DwmMtx Matrix */
 getTJ1200Tt4DwmMtx(Tt4DwmMtx);

/* Gets TJ1200Tt5wmMtx Matrix */
 getTJ1200Tt5wmMtx(Tt5wmMtx);

/* Gets TJ1200Tt5DwmMtx Matrix */
 getTJ1200Tt5DwmMtx(Tt5DwmMtx);

/* Gets TJ1200Tt6wmMtx Matrix */
 getTJ1200Tt6wmMtx(Tt6wmMtx);

/* Gets TJ1200Tt6DwmMtx Matrix */
 getTJ1200Tt6DwmMtx(Tt6DwmMtx);

/* Gets TJ1200Pt21shMtx Matrix */
 getTJ1200Pt21shMtx(Pt21shMtx);

/* Gets TJ1200Pt21DshMtx Matrix */
 getTJ1200Pt21DshMtx(Pt21DshMtx);

/* Gets TJ1200Pt5shMtx Matrix */
 getTJ1200Pt5shMtx(Pt5shMtx);

/* Gets TJ1200Pt5DshMtx Matrix */
 getTJ1200Pt5DshMtx(Pt5DshMtx);

/* Gets TJ1200Pt6shMtx Matrix */
 getTJ1200Pt6shMtx(Pt6shMtx);

/* Gets TJ1200Pt6DshMtx Matrix */
 getTJ1200Pt6DshMtx(Pt6DshMtx);

/* Gets TJ1200Tt21shMtx Matrix */
 getTJ1200Tt21shMtx(Tt21shMtx);

/* Gets TJ1200Tt21DshMtx Matrix */
 getTJ1200Tt21DshMtx(Tt21DshMtx);

/* Gets TJ1200Tt3shMtx Matrix */
 getTJ1200Tt3shMtx(Tt3shMtx);

/* Gets TJ1200Tt3DshMtx Matrix */
 getTJ1200Tt3DshMtx(Tt3DshMtx);

/* Gets TJ1200Tt5shMtx Matrix */
 getTJ1200Tt5shMtx(Tt5shMtx);

/* Gets TJ1200Tt5DshMtx Matrix */
 getTJ1200Tt5DshMtx(Tt5DshMtx);

/* Gets TJ1200Tt6shMtx Matrix */
 getTJ1200Tt6shMtx(Tt6shMtx);

/* Gets TJ1200Tt6DshMtx Matrix */
 getTJ1200Tt6DshMtx(Tt6DshMtx);