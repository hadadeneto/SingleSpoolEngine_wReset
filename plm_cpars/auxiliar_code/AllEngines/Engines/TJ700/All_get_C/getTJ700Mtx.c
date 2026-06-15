
#include <math.h>
#include "getTJ700MtxFunctions.h"

getTJ700Mtx(floating *NcFANContMtx, floating *N_KpMtx, floating *N_KiMtx, floating *FNperContMtx, floating *FNcMaxContMtx, 
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



/* Gets TJ700NcFANContMtx Matrix */
 getTJ700NcFANContMtx(NcFANContMtx);

/* Gets TJ700N_KpMtx Matrix */
 getTJ700N_KpMtx(N_KpMtx);

/* Gets TJ700N_KiMtx Matrix */
 getTJ700N_KiMtx(N_KiMtx);

/* Gets TJ700FNperContMtx Matrix */
 getTJ700FNperContMtx(FNperContMtx);

/* Gets TJ700FNcMaxContMtx Matrix */
 getTJ700FNcMaxContMtx(FNcMaxContMtx);

/* Gets TJ700NcMtx Matrix */
 getTJ700NcMtx(NcMtx);

/* Gets TJ700Pt21Mtx Matrix */
 getTJ700Pt21Mtx(Pt21Mtx);

/* Gets TJ700Pt3Mtx Matrix */
 getTJ700Pt3Mtx(Pt3Mtx);

/* Gets TJ700Pt5Mtx Matrix */
 getTJ700Pt5Mtx(Pt5Mtx);

/* Gets TJ700Pt6Mtx Matrix */
 getTJ700Pt6Mtx(Pt6Mtx);

/* Gets TJ700Tt21Mtx Matrix */
 getTJ700Tt21Mtx(Tt21Mtx);

/* Gets TJ700Tt3Mtx Matrix */
 getTJ700Tt3Mtx(Tt3Mtx);

/* Gets TJ700Tt4Mtx Matrix */
 getTJ700Tt4Mtx(Tt4Mtx);

/* Gets TJ700Tt5Mtx Matrix */
 getTJ700Tt5Mtx(Tt5Mtx);

/* Gets TJ700Tt6Mtx Matrix */
 getTJ700Tt6Mtx(Tt6Mtx);

/* Gets TJ700WfMtx Matrix */
 getTJ700WfMtx(WfMtx);

/* Gets TJ700AMtx Matrix */
 getTJ700AMtx(AMtx);

/* Gets TJ700BMtx Matrix */
 getTJ700BMtx(BMtx);

/* Gets TJ700Pt21DMtx Matrix */
 getTJ700Pt21DMtx(Pt21DMtx);

/* Gets TJ700Pt3DMtx Matrix */
 getTJ700Pt3DMtx(Pt3DMtx);

/* Gets TJ700Pt5DMtx Matrix */
 getTJ700Pt5DMtx(Pt5DMtx);

/* Gets TJ700Pt6DMtx Matrix */
 getTJ700Pt6DMtx(Pt6DMtx);

/* Gets TJ700Tt21DMtx Matrix */
 getTJ700Tt21DMtx(Tt21DMtx);

/* Gets TJ700Tt3DMtx Matrix */
 getTJ700Tt3DMtx(Tt3DMtx);

/* Gets TJ700Tt4DMtx Matrix */
 getTJ700Tt4DMtx(Tt4DMtx);

/* Gets TJ700Tt5DMtx Matrix */
 getTJ700Tt5DMtx(Tt5DMtx);

/* Gets TJ700Tt6DMtx Matrix */
 getTJ700Tt6DMtx(Tt6DMtx);

/* Gets TJ700NcFANMapMtx Matrix */
 getTJ700NcFANMapMtx(NcFANMapMtx);

/* Gets TJ700WcFANMapMtx Matrix */
 getTJ700WcFANMapMtx(WcFANMapMtx);

/* Gets TJ700WcFANStallMtx Matrix */
 getTJ700WcFANStallMtx(WcFANStallMtx);

/* Gets TJ700PRFANMapMtx Matrix */
 getTJ700PRFANMapMtx(PRFANMapMtx);

/* Gets TJ700PRFANStallMtx Matrix */
 getTJ700PRFANStallMtx(PRFANStallMtx);

/* Gets TJ700EffFANMapMtx Matrix */
 getTJ700EffFANMapMtx(EffFANMapMtx);

/* Gets TJ700NcHPTMapMtx Matrix */
 getTJ700NcHPTMapMtx(NcHPTMapMtx);

/* Gets TJ700WcHPTMapMtx Matrix */
 getTJ700WcHPTMapMtx(WcHPTMapMtx);

/* Gets TJ700PRHPTMapMtx Matrix */
 getTJ700PRHPTMapMtx(PRHPTMapMtx);

/* Gets TJ700EffHPTMapMtx Matrix */
 getTJ700EffHPTMapMtx(EffHPTMapMtx);

/* Gets TJ700NcHPCMapMtx Matrix */
 getTJ700NcHPCMapMtx(NcHPCMapMtx);

/* Gets TJ700WcHPCMapMtx Matrix */
 getTJ700WcHPCMapMtx(WcHPCMapMtx);

/* Gets TJ700WcHPCStallMtx Matrix */
 getTJ700WcHPCStallMtx(WcHPCStallMtx);

/* Gets TJ700PRHPCMapMtx Matrix */
 getTJ700PRHPCMapMtx(PRHPCMapMtx);

/* Gets TJ700PRHPCStallMtx Matrix */
 getTJ700PRHPCStallMtx(PRHPCStallMtx);

/* Gets TJ700EffHPCMapMtx Matrix */
 getTJ700EffHPCMapMtx(EffHPCMapMtx);

/* Gets TJ700MNLinVec Matrix */
 getTJ700MNLinVec(MNLinVec);

/* Gets TJ700AltLinVec Matrix */
 getTJ700AltLinVec(AltLinVec);

/* Gets TJ700DeltaMtx Matrix */
 getTJ700DeltaMtx(DeltaMtx);

/* Gets TJ700Ts0Mtx Matrix */
 getTJ700Ts0Mtx(Ts0Mtx);

/* Gets TJ700AwmMtx Matrix */
 getTJ700AwmMtx(AwmMtx);

/* Gets TJ700AshMtx Matrix */
 getTJ700AshMtx(AshMtx);

/* Gets TJ700BwmMtx Matrix */
 getTJ700BwmMtx(BwmMtx);

/* Gets TJ700BshMtx Matrix */
 getTJ700BshMtx(BshMtx);

/* Gets TJ700RPMwmMtx Matrix */
 getTJ700RPMwmMtx(RPMwmMtx);

/* Gets TJ700RPMshMtx Matrix */
 getTJ700RPMshMtx(RPMshMtx);

/* Gets TJ700Tt4CshMtx Matrix */
 getTJ700Tt4CshMtx(Tt4CshMtx);

/* Gets TJ700Tt4DshMtx Matrix */
 getTJ700Tt4DshMtx(Tt4DshMtx);

/* Gets TJ700Tt4shMtx Matrix */
 getTJ700Tt4shMtx(Tt4shMtx);

/* Gets TJ700WfshMtx Matrix */
 getTJ700WfshMtx(WfshMtx);

/* Gets TJ700ASVec Matrix */
 getTJ700ASVec(ASVec);

/* Gets TJ700DSVec Matrix */
 getTJ700DSVec(DSVec);

/* Gets TJ700NcVec Matrix */
 getTJ700NcVec(NcVec);

/* Gets TJ700NcFANshMtx Matrix */
 getTJ700NcFANshMtx(NcFANshMtx);

/* Gets TJ700WfwmMtx Matrix */
 getTJ700WfwmMtx(WfwmMtx);

/* Gets TJ700Pt3shMtx Matrix */
 getTJ700Pt3shMtx(Pt3shMtx);

/* Gets TJ700Pt3DshMtx Matrix */
 getTJ700Pt3DshMtx(Pt3DshMtx);

/* Gets TJ700Pt21wmMtx Matrix */
 getTJ700Pt21wmMtx(Pt21wmMtx);

/* Gets TJ700Pt21DwmMtx Matrix */
 getTJ700Pt21DwmMtx(Pt21DwmMtx);

/* Gets TJ700Pt3wmMtx Matrix */
 getTJ700Pt3wmMtx(Pt3wmMtx);

/* Gets TJ700Pt3DwmMtx Matrix */
 getTJ700Pt3DwmMtx(Pt3DwmMtx);

/* Gets TJ700Pt5wmMtx Matrix */
 getTJ700Pt5wmMtx(Pt5wmMtx);

/* Gets TJ700Pt5DwmMtx Matrix */
 getTJ700Pt5DwmMtx(Pt5DwmMtx);

/* Gets TJ700Pt6wmMtx Matrix */
 getTJ700Pt6wmMtx(Pt6wmMtx);

/* Gets TJ700Pt6DwmMtx Matrix */
 getTJ700Pt6DwmMtx(Pt6DwmMtx);

/* Gets TJ700Tt21wmMtx Matrix */
 getTJ700Tt21wmMtx(Tt21wmMtx);

/* Gets TJ700Tt21DwmMtx Matrix */
 getTJ700Tt21DwmMtx(Tt21DwmMtx);

/* Gets TJ700Tt3wmMtx Matrix */
 getTJ700Tt3wmMtx(Tt3wmMtx);

/* Gets TJ700Tt3DwmMtx Matrix */
 getTJ700Tt3DwmMtx(Tt3DwmMtx);

/* Gets TJ700Tt4wmMtx Matrix */
 getTJ700Tt4wmMtx(Tt4wmMtx);

/* Gets TJ700Tt4DwmMtx Matrix */
 getTJ700Tt4DwmMtx(Tt4DwmMtx);

/* Gets TJ700Tt5wmMtx Matrix */
 getTJ700Tt5wmMtx(Tt5wmMtx);

/* Gets TJ700Tt5DwmMtx Matrix */
 getTJ700Tt5DwmMtx(Tt5DwmMtx);

/* Gets TJ700Tt6wmMtx Matrix */
 getTJ700Tt6wmMtx(Tt6wmMtx);

/* Gets TJ700Tt6DwmMtx Matrix */
 getTJ700Tt6DwmMtx(Tt6DwmMtx);

/* Gets TJ700Pt21shMtx Matrix */
 getTJ700Pt21shMtx(Pt21shMtx);

/* Gets TJ700Pt21DshMtx Matrix */
 getTJ700Pt21DshMtx(Pt21DshMtx);

/* Gets TJ700Pt5shMtx Matrix */
 getTJ700Pt5shMtx(Pt5shMtx);

/* Gets TJ700Pt5DshMtx Matrix */
 getTJ700Pt5DshMtx(Pt5DshMtx);

/* Gets TJ700Pt6shMtx Matrix */
 getTJ700Pt6shMtx(Pt6shMtx);

/* Gets TJ700Pt6DshMtx Matrix */
 getTJ700Pt6DshMtx(Pt6DshMtx);

/* Gets TJ700Tt21shMtx Matrix */
 getTJ700Tt21shMtx(Tt21shMtx);

/* Gets TJ700Tt21DshMtx Matrix */
 getTJ700Tt21DshMtx(Tt21DshMtx);

/* Gets TJ700Tt3shMtx Matrix */
 getTJ700Tt3shMtx(Tt3shMtx);

/* Gets TJ700Tt3DshMtx Matrix */
 getTJ700Tt3DshMtx(Tt3DshMtx);

/* Gets TJ700Tt5shMtx Matrix */
 getTJ700Tt5shMtx(Tt5shMtx);

/* Gets TJ700Tt5DshMtx Matrix */
 getTJ700Tt5DshMtx(Tt5DshMtx);

/* Gets TJ700Tt6shMtx Matrix */
 getTJ700Tt6shMtx(Tt6shMtx);

/* Gets TJ700Tt6DshMtx Matrix */
 getTJ700Tt6DshMtx(Tt6DshMtx);