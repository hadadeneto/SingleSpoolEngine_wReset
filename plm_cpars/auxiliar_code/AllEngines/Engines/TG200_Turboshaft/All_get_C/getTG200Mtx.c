
#include <math.h>
#include "getTG200MtxFunctions.h"

getTG200Mtx(floating *NcFANContMtx, floating *N_KpMtx, floating *N_KiMtx, floating *FNperContMtx, floating *FNcMaxContMtx, 
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



/* Gets TG200NcFANContMtx Matrix */
 getTG200NcFANContMtx(NcFANContMtx);

/* Gets TG200N_KpMtx Matrix */
 getTG200N_KpMtx(N_KpMtx);

/* Gets TG200N_KiMtx Matrix */
 getTG200N_KiMtx(N_KiMtx);

/* Gets TG200FNperContMtx Matrix */
 getTG200FNperContMtx(FNperContMtx);

/* Gets TG200FNcMaxContMtx Matrix */
 getTG200FNcMaxContMtx(FNcMaxContMtx);

/* Gets TG200NcMtx Matrix */
 getTG200NcMtx(NcMtx);

/* Gets TG200Pt21Mtx Matrix */
 getTG200Pt21Mtx(Pt21Mtx);

/* Gets TG200Pt3Mtx Matrix */
 getTG200Pt3Mtx(Pt3Mtx);

/* Gets TG200Pt5Mtx Matrix */
 getTG200Pt5Mtx(Pt5Mtx);

/* Gets TG200Pt6Mtx Matrix */
 getTG200Pt6Mtx(Pt6Mtx);

/* Gets TG200Tt21Mtx Matrix */
 getTG200Tt21Mtx(Tt21Mtx);

/* Gets TG200Tt3Mtx Matrix */
 getTG200Tt3Mtx(Tt3Mtx);

/* Gets TG200Tt4Mtx Matrix */
 getTG200Tt4Mtx(Tt4Mtx);

/* Gets TG200Tt5Mtx Matrix */
 getTG200Tt5Mtx(Tt5Mtx);

/* Gets TG200Tt6Mtx Matrix */
 getTG200Tt6Mtx(Tt6Mtx);

/* Gets TG200WfMtx Matrix */
 getTG200WfMtx(WfMtx);

/* Gets TG200AMtx Matrix */
 getTG200AMtx(AMtx);

/* Gets TG200BMtx Matrix */
 getTG200BMtx(BMtx);

/* Gets TG200Pt21DMtx Matrix */
 getTG200Pt21DMtx(Pt21DMtx);

/* Gets TG200Pt3DMtx Matrix */
 getTG200Pt3DMtx(Pt3DMtx);

/* Gets TG200Pt5DMtx Matrix */
 getTG200Pt5DMtx(Pt5DMtx);

/* Gets TG200Pt6DMtx Matrix */
 getTG200Pt6DMtx(Pt6DMtx);

/* Gets TG200Tt21DMtx Matrix */
 getTG200Tt21DMtx(Tt21DMtx);

/* Gets TG200Tt3DMtx Matrix */
 getTG200Tt3DMtx(Tt3DMtx);

/* Gets TG200Tt4DMtx Matrix */
 getTG200Tt4DMtx(Tt4DMtx);

/* Gets TG200Tt5DMtx Matrix */
 getTG200Tt5DMtx(Tt5DMtx);

/* Gets TG200Tt6DMtx Matrix */
 getTG200Tt6DMtx(Tt6DMtx);

/* Gets TG200NcFANMapMtx Matrix */
 getTG200NcFANMapMtx(NcFANMapMtx);

/* Gets TG200WcFANMapMtx Matrix */
 getTG200WcFANMapMtx(WcFANMapMtx);

/* Gets TG200WcFANStallMtx Matrix */
 getTG200WcFANStallMtx(WcFANStallMtx);

/* Gets TG200PRFANMapMtx Matrix */
 getTG200PRFANMapMtx(PRFANMapMtx);

/* Gets TG200PRFANStallMtx Matrix */
 getTG200PRFANStallMtx(PRFANStallMtx);

/* Gets TG200EffFANMapMtx Matrix */
 getTG200EffFANMapMtx(EffFANMapMtx);

/* Gets TG200NcHPTMapMtx Matrix */
 getTG200NcHPTMapMtx(NcHPTMapMtx);

/* Gets TG200WcHPTMapMtx Matrix */
 getTG200WcHPTMapMtx(WcHPTMapMtx);

/* Gets TG200PRHPTMapMtx Matrix */
 getTG200PRHPTMapMtx(PRHPTMapMtx);

/* Gets TG200EffHPTMapMtx Matrix */
 getTG200EffHPTMapMtx(EffHPTMapMtx);

/* Gets TG200NcHPCMapMtx Matrix */
 getTG200NcHPCMapMtx(NcHPCMapMtx);

/* Gets TG200WcHPCMapMtx Matrix */
 getTG200WcHPCMapMtx(WcHPCMapMtx);

/* Gets TG200WcHPCStallMtx Matrix */
 getTG200WcHPCStallMtx(WcHPCStallMtx);

/* Gets TG200PRHPCMapMtx Matrix */
 getTG200PRHPCMapMtx(PRHPCMapMtx);

/* Gets TG200PRHPCStallMtx Matrix */
 getTG200PRHPCStallMtx(PRHPCStallMtx);

/* Gets TG200EffHPCMapMtx Matrix */
 getTG200EffHPCMapMtx(EffHPCMapMtx);

/* Gets TG200MNLinVec Matrix */
 getTG200MNLinVec(MNLinVec);

/* Gets TG200AltLinVec Matrix */
 getTG200AltLinVec(AltLinVec);

/* Gets TG200DeltaMtx Matrix */
 getTG200DeltaMtx(DeltaMtx);

/* Gets TG200Ts0Mtx Matrix */
 getTG200Ts0Mtx(Ts0Mtx);

/* Gets TG200AwmMtx Matrix */
 getTG200AwmMtx(AwmMtx);

/* Gets TG200AshMtx Matrix */
 getTG200AshMtx(AshMtx);

/* Gets TG200BwmMtx Matrix */
 getTG200BwmMtx(BwmMtx);

/* Gets TG200BshMtx Matrix */
 getTG200BshMtx(BshMtx);

/* Gets TG200RPMwmMtx Matrix */
 getTG200RPMwmMtx(RPMwmMtx);

/* Gets TG200RPMshMtx Matrix */
 getTG200RPMshMtx(RPMshMtx);

/* Gets TG200Tt4CshMtx Matrix */
 getTG200Tt4CshMtx(Tt4CshMtx);

/* Gets TG200Tt4DshMtx Matrix */
 getTG200Tt4DshMtx(Tt4DshMtx);

/* Gets TG200Tt4shMtx Matrix */
 getTG200Tt4shMtx(Tt4shMtx);

/* Gets TG200WfshMtx Matrix */
 getTG200WfshMtx(WfshMtx);

/* Gets TG200ASVec Matrix */
 getTG200ASVec(ASVec);

/* Gets TG200DSVec Matrix */
 getTG200DSVec(DSVec);

/* Gets TG200NcVec Matrix */
 getTG200NcVec(NcVec);

/* Gets TG200NcFANshMtx Matrix */
 getTG200NcFANshMtx(NcFANshMtx);

/* Gets TG200WfwmMtx Matrix */
 getTG200WfwmMtx(WfwmMtx);

/* Gets TG200Pt3shMtx Matrix */
 getTG200Pt3shMtx(Pt3shMtx);

/* Gets TG200Pt3DshMtx Matrix */
 getTG200Pt3DshMtx(Pt3DshMtx);

/* Gets TG200Pt21wmMtx Matrix */
 getTG200Pt21wmMtx(Pt21wmMtx);

/* Gets TG200Pt21DwmMtx Matrix */
 getTG200Pt21DwmMtx(Pt21DwmMtx);

/* Gets TG200Pt3wmMtx Matrix */
 getTG200Pt3wmMtx(Pt3wmMtx);

/* Gets TG200Pt3DwmMtx Matrix */
 getTG200Pt3DwmMtx(Pt3DwmMtx);

/* Gets TG200Pt5wmMtx Matrix */
 getTG200Pt5wmMtx(Pt5wmMtx);

/* Gets TG200Pt5DwmMtx Matrix */
 getTG200Pt5DwmMtx(Pt5DwmMtx);

/* Gets TG200Pt6wmMtx Matrix */
 getTG200Pt6wmMtx(Pt6wmMtx);

/* Gets TG200Pt6DwmMtx Matrix */
 getTG200Pt6DwmMtx(Pt6DwmMtx);

/* Gets TG200Tt21wmMtx Matrix */
 getTG200Tt21wmMtx(Tt21wmMtx);

/* Gets TG200Tt21DwmMtx Matrix */
 getTG200Tt21DwmMtx(Tt21DwmMtx);

/* Gets TG200Tt3wmMtx Matrix */
 getTG200Tt3wmMtx(Tt3wmMtx);

/* Gets TG200Tt3DwmMtx Matrix */
 getTG200Tt3DwmMtx(Tt3DwmMtx);

/* Gets TG200Tt4wmMtx Matrix */
 getTG200Tt4wmMtx(Tt4wmMtx);

/* Gets TG200Tt4DwmMtx Matrix */
 getTG200Tt4DwmMtx(Tt4DwmMtx);

/* Gets TG200Tt5wmMtx Matrix */
 getTG200Tt5wmMtx(Tt5wmMtx);

/* Gets TG200Tt5DwmMtx Matrix */
 getTG200Tt5DwmMtx(Tt5DwmMtx);

/* Gets TG200Tt6wmMtx Matrix */
 getTG200Tt6wmMtx(Tt6wmMtx);

/* Gets TG200Tt6DwmMtx Matrix */
 getTG200Tt6DwmMtx(Tt6DwmMtx);

/* Gets TG200Pt21shMtx Matrix */
 getTG200Pt21shMtx(Pt21shMtx);

/* Gets TG200Pt21DshMtx Matrix */
 getTG200Pt21DshMtx(Pt21DshMtx);

/* Gets TG200Pt5shMtx Matrix */
 getTG200Pt5shMtx(Pt5shMtx);

/* Gets TG200Pt5DshMtx Matrix */
 getTG200Pt5DshMtx(Pt5DshMtx);

/* Gets TG200Pt6shMtx Matrix */
 getTG200Pt6shMtx(Pt6shMtx);

/* Gets TG200Pt6DshMtx Matrix */
 getTG200Pt6DshMtx(Pt6DshMtx);

/* Gets TG200Tt21shMtx Matrix */
 getTG200Tt21shMtx(Tt21shMtx);

/* Gets TG200Tt21DshMtx Matrix */
 getTG200Tt21DshMtx(Tt21DshMtx);

/* Gets TG200Tt3shMtx Matrix */
 getTG200Tt3shMtx(Tt3shMtx);

/* Gets TG200Tt3DshMtx Matrix */
 getTG200Tt3DshMtx(Tt3DshMtx);

/* Gets TG200Tt5shMtx Matrix */
 getTG200Tt5shMtx(Tt5shMtx);

/* Gets TG200Tt5DshMtx Matrix */
 getTG200Tt5DshMtx(Tt5DshMtx);

/* Gets TG200Tt6shMtx Matrix */
 getTG200Tt6shMtx(Tt6shMtx);

/* Gets TG200Tt6DshMtx Matrix */
 getTG200Tt6DshMtx(Tt6DshMtx);