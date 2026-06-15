
#include <math.h>
#include "getTJ40MtxFunctions.h"

getTJ40Mtx(floating *NcFANContMtx, floating *N_KpMtx, floating *N_KiMtx, floating *FNperContMtx, floating *FNcMaxContMtx, 
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



/* Gets TJ40NcFANContMtx Matrix */
 getTJ40NcFANContMtx(NcFANContMtx);

/* Gets TJ40N_KpMtx Matrix */
 getTJ40N_KpMtx(N_KpMtx);

/* Gets TJ40N_KiMtx Matrix */
 getTJ40N_KiMtx(N_KiMtx);

/* Gets TJ40FNperContMtx Matrix */
 getTJ40FNperContMtx(FNperContMtx);

/* Gets TJ40FNcMaxContMtx Matrix */
 getTJ40FNcMaxContMtx(FNcMaxContMtx);

/* Gets TJ40NcMtx Matrix */
 getTJ40NcMtx(NcMtx);

/* Gets TJ40Pt21Mtx Matrix */
 getTJ40Pt21Mtx(Pt21Mtx);

/* Gets TJ40Pt3Mtx Matrix */
 getTJ40Pt3Mtx(Pt3Mtx);

/* Gets TJ40Pt5Mtx Matrix */
 getTJ40Pt5Mtx(Pt5Mtx);

/* Gets TJ40Pt6Mtx Matrix */
 getTJ40Pt6Mtx(Pt6Mtx);

/* Gets TJ40Tt21Mtx Matrix */
 getTJ40Tt21Mtx(Tt21Mtx);

/* Gets TJ40Tt3Mtx Matrix */
 getTJ40Tt3Mtx(Tt3Mtx);

/* Gets TJ40Tt4Mtx Matrix */
 getTJ40Tt4Mtx(Tt4Mtx);

/* Gets TJ40Tt5Mtx Matrix */
 getTJ40Tt5Mtx(Tt5Mtx);

/* Gets TJ40Tt6Mtx Matrix */
 getTJ40Tt6Mtx(Tt6Mtx);

/* Gets TJ40WfMtx Matrix */
 getTJ40WfMtx(WfMtx);

/* Gets TJ40AMtx Matrix */
 getTJ40AMtx(AMtx);

/* Gets TJ40BMtx Matrix */
 getTJ40BMtx(BMtx);

/* Gets TJ40Pt21DMtx Matrix */
 getTJ40Pt21DMtx(Pt21DMtx);

/* Gets TJ40Pt3DMtx Matrix */
 getTJ40Pt3DMtx(Pt3DMtx);

/* Gets TJ40Pt5DMtx Matrix */
 getTJ40Pt5DMtx(Pt5DMtx);

/* Gets TJ40Pt6DMtx Matrix */
 getTJ40Pt6DMtx(Pt6DMtx);

/* Gets TJ40Tt21DMtx Matrix */
 getTJ40Tt21DMtx(Tt21DMtx);

/* Gets TJ40Tt3DMtx Matrix */
 getTJ40Tt3DMtx(Tt3DMtx);

/* Gets TJ40Tt4DMtx Matrix */
 getTJ40Tt4DMtx(Tt4DMtx);

/* Gets TJ40Tt5DMtx Matrix */
 getTJ40Tt5DMtx(Tt5DMtx);

/* Gets TJ40Tt6DMtx Matrix */
 getTJ40Tt6DMtx(Tt6DMtx);

/* Gets TJ40NcFANMapMtx Matrix */
 getTJ40NcFANMapMtx(NcFANMapMtx);

/* Gets TJ40WcFANMapMtx Matrix */
 getTJ40WcFANMapMtx(WcFANMapMtx);

/* Gets TJ40WcFANStallMtx Matrix */
 getTJ40WcFANStallMtx(WcFANStallMtx);

/* Gets TJ40PRFANMapMtx Matrix */
 getTJ40PRFANMapMtx(PRFANMapMtx);

/* Gets TJ40PRFANStallMtx Matrix */
 getTJ40PRFANStallMtx(PRFANStallMtx);

/* Gets TJ40EffFANMapMtx Matrix */
 getTJ40EffFANMapMtx(EffFANMapMtx);

/* Gets TJ40NcHPTMapMtx Matrix */
 getTJ40NcHPTMapMtx(NcHPTMapMtx);

/* Gets TJ40WcHPTMapMtx Matrix */
 getTJ40WcHPTMapMtx(WcHPTMapMtx);

/* Gets TJ40PRHPTMapMtx Matrix */
 getTJ40PRHPTMapMtx(PRHPTMapMtx);

/* Gets TJ40EffHPTMapMtx Matrix */
 getTJ40EffHPTMapMtx(EffHPTMapMtx);

/* Gets TJ40NcHPCMapMtx Matrix */
 getTJ40NcHPCMapMtx(NcHPCMapMtx);

/* Gets TJ40WcHPCMapMtx Matrix */
 getTJ40WcHPCMapMtx(WcHPCMapMtx);

/* Gets TJ40WcHPCStallMtx Matrix */
 getTJ40WcHPCStallMtx(WcHPCStallMtx);

/* Gets TJ40PRHPCMapMtx Matrix */
 getTJ40PRHPCMapMtx(PRHPCMapMtx);

/* Gets TJ40PRHPCStallMtx Matrix */
 getTJ40PRHPCStallMtx(PRHPCStallMtx);

/* Gets TJ40EffHPCMapMtx Matrix */
 getTJ40EffHPCMapMtx(EffHPCMapMtx);

/* Gets TJ40MNLinVec Matrix */
 getTJ40MNLinVec(MNLinVec);

/* Gets TJ40AltLinVec Matrix */
 getTJ40AltLinVec(AltLinVec);

/* Gets TJ40DeltaMtx Matrix */
 getTJ40DeltaMtx(DeltaMtx);

/* Gets TJ40Ts0Mtx Matrix */
 getTJ40Ts0Mtx(Ts0Mtx);

/* Gets TJ40AwmMtx Matrix */
 getTJ40AwmMtx(AwmMtx);

/* Gets TJ40AshMtx Matrix */
 getTJ40AshMtx(AshMtx);

/* Gets TJ40BwmMtx Matrix */
 getTJ40BwmMtx(BwmMtx);

/* Gets TJ40BshMtx Matrix */
 getTJ40BshMtx(BshMtx);

/* Gets TJ40RPMwmMtx Matrix */
 getTJ40RPMwmMtx(RPMwmMtx);

/* Gets TJ40RPMshMtx Matrix */
 getTJ40RPMshMtx(RPMshMtx);

/* Gets TJ40Tt4CshMtx Matrix */
 getTJ40Tt4CshMtx(Tt4CshMtx);

/* Gets TJ40Tt4DshMtx Matrix */
 getTJ40Tt4DshMtx(Tt4DshMtx);

/* Gets TJ40Tt4shMtx Matrix */
 getTJ40Tt4shMtx(Tt4shMtx);

/* Gets TJ40WfshMtx Matrix */
 getTJ40WfshMtx(WfshMtx);

/* Gets TJ40ASVec Matrix */
 getTJ40ASVec(ASVec);

/* Gets TJ40DSVec Matrix */
 getTJ40DSVec(DSVec);

/* Gets TJ40NcVec Matrix */
 getTJ40NcVec(NcVec);

/* Gets TJ40NcFANshMtx Matrix */
 getTJ40NcFANshMtx(NcFANshMtx);

/* Gets TJ40WfwmMtx Matrix */
 getTJ40WfwmMtx(WfwmMtx);

/* Gets TJ40Pt3shMtx Matrix */
 getTJ40Pt3shMtx(Pt3shMtx);

/* Gets TJ40Pt3DshMtx Matrix */
 getTJ40Pt3DshMtx(Pt3DshMtx);

/* Gets TJ40Pt21wmMtx Matrix */
 getTJ40Pt21wmMtx(Pt21wmMtx);

/* Gets TJ40Pt21DwmMtx Matrix */
 getTJ40Pt21DwmMtx(Pt21DwmMtx);

/* Gets TJ40Pt3wmMtx Matrix */
 getTJ40Pt3wmMtx(Pt3wmMtx);

/* Gets TJ40Pt3DwmMtx Matrix */
 getTJ40Pt3DwmMtx(Pt3DwmMtx);

/* Gets TJ40Pt5wmMtx Matrix */
 getTJ40Pt5wmMtx(Pt5wmMtx);

/* Gets TJ40Pt5DwmMtx Matrix */
 getTJ40Pt5DwmMtx(Pt5DwmMtx);

/* Gets TJ40Pt6wmMtx Matrix */
 getTJ40Pt6wmMtx(Pt6wmMtx);

/* Gets TJ40Pt6DwmMtx Matrix */
 getTJ40Pt6DwmMtx(Pt6DwmMtx);

/* Gets TJ40Tt21wmMtx Matrix */
 getTJ40Tt21wmMtx(Tt21wmMtx);

/* Gets TJ40Tt21DwmMtx Matrix */
 getTJ40Tt21DwmMtx(Tt21DwmMtx);

/* Gets TJ40Tt3wmMtx Matrix */
 getTJ40Tt3wmMtx(Tt3wmMtx);

/* Gets TJ40Tt3DwmMtx Matrix */
 getTJ40Tt3DwmMtx(Tt3DwmMtx);

/* Gets TJ40Tt4wmMtx Matrix */
 getTJ40Tt4wmMtx(Tt4wmMtx);

/* Gets TJ40Tt4DwmMtx Matrix */
 getTJ40Tt4DwmMtx(Tt4DwmMtx);

/* Gets TJ40Tt5wmMtx Matrix */
 getTJ40Tt5wmMtx(Tt5wmMtx);

/* Gets TJ40Tt5DwmMtx Matrix */
 getTJ40Tt5DwmMtx(Tt5DwmMtx);

/* Gets TJ40Tt6wmMtx Matrix */
 getTJ40Tt6wmMtx(Tt6wmMtx);

/* Gets TJ40Tt6DwmMtx Matrix */
 getTJ40Tt6DwmMtx(Tt6DwmMtx);

/* Gets TJ40Pt21shMtx Matrix */
 getTJ40Pt21shMtx(Pt21shMtx);

/* Gets TJ40Pt21DshMtx Matrix */
 getTJ40Pt21DshMtx(Pt21DshMtx);

/* Gets TJ40Pt5shMtx Matrix */
 getTJ40Pt5shMtx(Pt5shMtx);

/* Gets TJ40Pt5DshMtx Matrix */
 getTJ40Pt5DshMtx(Pt5DshMtx);

/* Gets TJ40Pt6shMtx Matrix */
 getTJ40Pt6shMtx(Pt6shMtx);

/* Gets TJ40Pt6DshMtx Matrix */
 getTJ40Pt6DshMtx(Pt6DshMtx);

/* Gets TJ40Tt21shMtx Matrix */
 getTJ40Tt21shMtx(Tt21shMtx);

/* Gets TJ40Tt21DshMtx Matrix */
 getTJ40Tt21DshMtx(Tt21DshMtx);

/* Gets TJ40Tt3shMtx Matrix */
 getTJ40Tt3shMtx(Tt3shMtx);

/* Gets TJ40Tt3DshMtx Matrix */
 getTJ40Tt3DshMtx(Tt3DshMtx);

/* Gets TJ40Tt5shMtx Matrix */
 getTJ40Tt5shMtx(Tt5shMtx);

/* Gets TJ40Tt5DshMtx Matrix */
 getTJ40Tt5DshMtx(Tt5DshMtx);

/* Gets TJ40Tt6shMtx Matrix */
 getTJ40Tt6shMtx(Tt6shMtx);

/* Gets TJ40Tt6DshMtx Matrix */
 getTJ40Tt6DshMtx(Tt6DshMtx);