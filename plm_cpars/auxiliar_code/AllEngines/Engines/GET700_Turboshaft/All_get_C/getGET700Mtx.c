
#include <math.h>
#include "getGET700MtxFunctions.h"

getGET700Mtx(floating *NcFANContMtx, floating *N_KpMtx, floating *N_KiMtx, floating *FNperContMtx, floating *FNcMaxContMtx, 
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



/* Gets GET700NcFANContMtx Matrix */
 getGET700NcFANContMtx(NcFANContMtx);

/* Gets GET700N_KpMtx Matrix */
 getGET700N_KpMtx(N_KpMtx);

/* Gets GET700N_KiMtx Matrix */
 getGET700N_KiMtx(N_KiMtx);

/* Gets GET700FNperContMtx Matrix */
 getGET700FNperContMtx(FNperContMtx);

/* Gets GET700FNcMaxContMtx Matrix */
 getGET700FNcMaxContMtx(FNcMaxContMtx);

/* Gets GET700NcMtx Matrix */
 getGET700NcMtx(NcMtx);

/* Gets GET700Pt21Mtx Matrix */
 getGET700Pt21Mtx(Pt21Mtx);

/* Gets GET700Pt3Mtx Matrix */
 getGET700Pt3Mtx(Pt3Mtx);

/* Gets GET700Pt5Mtx Matrix */
 getGET700Pt5Mtx(Pt5Mtx);

/* Gets GET700Pt6Mtx Matrix */
 getGET700Pt6Mtx(Pt6Mtx);

/* Gets GET700Tt21Mtx Matrix */
 getGET700Tt21Mtx(Tt21Mtx);

/* Gets GET700Tt3Mtx Matrix */
 getGET700Tt3Mtx(Tt3Mtx);

/* Gets GET700Tt4Mtx Matrix */
 getGET700Tt4Mtx(Tt4Mtx);

/* Gets GET700Tt5Mtx Matrix */
 getGET700Tt5Mtx(Tt5Mtx);

/* Gets GET700Tt6Mtx Matrix */
 getGET700Tt6Mtx(Tt6Mtx);

/* Gets GET700WfMtx Matrix */
 getGET700WfMtx(WfMtx);

/* Gets GET700AMtx Matrix */
 getGET700AMtx(AMtx);

/* Gets GET700BMtx Matrix */
 getGET700BMtx(BMtx);

/* Gets GET700Pt21DMtx Matrix */
 getGET700Pt21DMtx(Pt21DMtx);

/* Gets GET700Pt3DMtx Matrix */
 getGET700Pt3DMtx(Pt3DMtx);

/* Gets GET700Pt5DMtx Matrix */
 getGET700Pt5DMtx(Pt5DMtx);

/* Gets GET700Pt6DMtx Matrix */
 getGET700Pt6DMtx(Pt6DMtx);

/* Gets GET700Tt21DMtx Matrix */
 getGET700Tt21DMtx(Tt21DMtx);

/* Gets GET700Tt3DMtx Matrix */
 getGET700Tt3DMtx(Tt3DMtx);

/* Gets GET700Tt4DMtx Matrix */
 getGET700Tt4DMtx(Tt4DMtx);

/* Gets GET700Tt5DMtx Matrix */
 getGET700Tt5DMtx(Tt5DMtx);

/* Gets GET700Tt6DMtx Matrix */
 getGET700Tt6DMtx(Tt6DMtx);

/* Gets GET700NcFANMapMtx Matrix */
 getGET700NcFANMapMtx(NcFANMapMtx);

/* Gets GET700WcFANMapMtx Matrix */
 getGET700WcFANMapMtx(WcFANMapMtx);

/* Gets GET700WcFANStallMtx Matrix */
 getGET700WcFANStallMtx(WcFANStallMtx);

/* Gets GET700PRFANMapMtx Matrix */
 getGET700PRFANMapMtx(PRFANMapMtx);

/* Gets GET700PRFANStallMtx Matrix */
 getGET700PRFANStallMtx(PRFANStallMtx);

/* Gets GET700EffFANMapMtx Matrix */
 getGET700EffFANMapMtx(EffFANMapMtx);

/* Gets GET700NcHPTMapMtx Matrix */
 getGET700NcHPTMapMtx(NcHPTMapMtx);

/* Gets GET700WcHPTMapMtx Matrix */
 getGET700WcHPTMapMtx(WcHPTMapMtx);

/* Gets GET700PRHPTMapMtx Matrix */
 getGET700PRHPTMapMtx(PRHPTMapMtx);

/* Gets GET700EffHPTMapMtx Matrix */
 getGET700EffHPTMapMtx(EffHPTMapMtx);

/* Gets GET700NcHPCMapMtx Matrix */
 getGET700NcHPCMapMtx(NcHPCMapMtx);

/* Gets GET700WcHPCMapMtx Matrix */
 getGET700WcHPCMapMtx(WcHPCMapMtx);

/* Gets GET700WcHPCStallMtx Matrix */
 getGET700WcHPCStallMtx(WcHPCStallMtx);

/* Gets GET700PRHPCMapMtx Matrix */
 getGET700PRHPCMapMtx(PRHPCMapMtx);

/* Gets GET700PRHPCStallMtx Matrix */
 getGET700PRHPCStallMtx(PRHPCStallMtx);

/* Gets GET700EffHPCMapMtx Matrix */
 getGET700EffHPCMapMtx(EffHPCMapMtx);

/* Gets GET700MNLinVec Matrix */
 getGET700MNLinVec(MNLinVec);

/* Gets GET700AltLinVec Matrix */
 getGET700AltLinVec(AltLinVec);

/* Gets GET700DeltaMtx Matrix */
 getGET700DeltaMtx(DeltaMtx);

/* Gets GET700Ts0Mtx Matrix */
 getGET700Ts0Mtx(Ts0Mtx);

/* Gets GET700AwmMtx Matrix */
 getGET700AwmMtx(AwmMtx);

/* Gets GET700AshMtx Matrix */
 getGET700AshMtx(AshMtx);

/* Gets GET700BwmMtx Matrix */
 getGET700BwmMtx(BwmMtx);

/* Gets GET700BshMtx Matrix */
 getGET700BshMtx(BshMtx);

/* Gets GET700RPMwmMtx Matrix */
 getGET700RPMwmMtx(RPMwmMtx);

/* Gets GET700RPMshMtx Matrix */
 getGET700RPMshMtx(RPMshMtx);

/* Gets GET700Tt4CshMtx Matrix */
 getGET700Tt4CshMtx(Tt4CshMtx);

/* Gets GET700Tt4DshMtx Matrix */
 getGET700Tt4DshMtx(Tt4DshMtx);

/* Gets GET700Tt4shMtx Matrix */
 getGET700Tt4shMtx(Tt4shMtx);

/* Gets GET700WfshMtx Matrix */
 getGET700WfshMtx(WfshMtx);

/* Gets GET700ASVec Matrix */
 getGET700ASVec(ASVec);

/* Gets GET700DSVec Matrix */
 getGET700DSVec(DSVec);

/* Gets GET700NcVec Matrix */
 getGET700NcVec(NcVec);

/* Gets GET700NcFANshMtx Matrix */
 getGET700NcFANshMtx(NcFANshMtx);

/* Gets GET700WfwmMtx Matrix */
 getGET700WfwmMtx(WfwmMtx);

/* Gets GET700Pt3shMtx Matrix */
 getGET700Pt3shMtx(Pt3shMtx);

/* Gets GET700Pt3DshMtx Matrix */
 getGET700Pt3DshMtx(Pt3DshMtx);

/* Gets GET700Pt21wmMtx Matrix */
 getGET700Pt21wmMtx(Pt21wmMtx);

/* Gets GET700Pt21DwmMtx Matrix */
 getGET700Pt21DwmMtx(Pt21DwmMtx);

/* Gets GET700Pt3wmMtx Matrix */
 getGET700Pt3wmMtx(Pt3wmMtx);

/* Gets GET700Pt3DwmMtx Matrix */
 getGET700Pt3DwmMtx(Pt3DwmMtx);

/* Gets GET700Pt5wmMtx Matrix */
 getGET700Pt5wmMtx(Pt5wmMtx);

/* Gets GET700Pt5DwmMtx Matrix */
 getGET700Pt5DwmMtx(Pt5DwmMtx);

/* Gets GET700Pt6wmMtx Matrix */
 getGET700Pt6wmMtx(Pt6wmMtx);

/* Gets GET700Pt6DwmMtx Matrix */
 getGET700Pt6DwmMtx(Pt6DwmMtx);

/* Gets GET700Tt21wmMtx Matrix */
 getGET700Tt21wmMtx(Tt21wmMtx);

/* Gets GET700Tt21DwmMtx Matrix */
 getGET700Tt21DwmMtx(Tt21DwmMtx);

/* Gets GET700Tt3wmMtx Matrix */
 getGET700Tt3wmMtx(Tt3wmMtx);

/* Gets GET700Tt3DwmMtx Matrix */
 getGET700Tt3DwmMtx(Tt3DwmMtx);

/* Gets GET700Tt4wmMtx Matrix */
 getGET700Tt4wmMtx(Tt4wmMtx);

/* Gets GET700Tt4DwmMtx Matrix */
 getGET700Tt4DwmMtx(Tt4DwmMtx);

/* Gets GET700Tt5wmMtx Matrix */
 getGET700Tt5wmMtx(Tt5wmMtx);

/* Gets GET700Tt5DwmMtx Matrix */
 getGET700Tt5DwmMtx(Tt5DwmMtx);

/* Gets GET700Tt6wmMtx Matrix */
 getGET700Tt6wmMtx(Tt6wmMtx);

/* Gets GET700Tt6DwmMtx Matrix */
 getGET700Tt6DwmMtx(Tt6DwmMtx);

/* Gets GET700Pt21shMtx Matrix */
 getGET700Pt21shMtx(Pt21shMtx);

/* Gets GET700Pt21DshMtx Matrix */
 getGET700Pt21DshMtx(Pt21DshMtx);

/* Gets GET700Pt5shMtx Matrix */
 getGET700Pt5shMtx(Pt5shMtx);

/* Gets GET700Pt5DshMtx Matrix */
 getGET700Pt5DshMtx(Pt5DshMtx);

/* Gets GET700Pt6shMtx Matrix */
 getGET700Pt6shMtx(Pt6shMtx);

/* Gets GET700Pt6DshMtx Matrix */
 getGET700Pt6DshMtx(Pt6DshMtx);

/* Gets GET700Tt21shMtx Matrix */
 getGET700Tt21shMtx(Tt21shMtx);

/* Gets GET700Tt21DshMtx Matrix */
 getGET700Tt21DshMtx(Tt21DshMtx);

/* Gets GET700Tt3shMtx Matrix */
 getGET700Tt3shMtx(Tt3shMtx);

/* Gets GET700Tt3DshMtx Matrix */
 getGET700Tt3DshMtx(Tt3DshMtx);

/* Gets GET700Tt5shMtx Matrix */
 getGET700Tt5shMtx(Tt5shMtx);

/* Gets GET700Tt5DshMtx Matrix */
 getGET700Tt5DshMtx(Tt5DshMtx);

/* Gets GET700Tt6shMtx Matrix */
 getGET700Tt6shMtx(Tt6shMtx);

/* Gets GET700Tt6DshMtx Matrix */
 getGET700Tt6DshMtx(Tt6DshMtx);