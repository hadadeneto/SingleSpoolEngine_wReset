
#include <math.h>
#include "getGEJ85MtxFunctions.h"

getGEJ85Mtx(floating *NcFANContMtx, floating *N_KpMtx, floating *N_KiMtx, floating *FNperContMtx, floating *FNcMaxContMtx, 
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



/* Gets GEJ85NcFANContMtx Matrix */
 getGEJ85NcFANContMtx(NcFANContMtx);

/* Gets GEJ85N_KpMtx Matrix */
 getGEJ85N_KpMtx(N_KpMtx);

/* Gets GEJ85N_KiMtx Matrix */
 getGEJ85N_KiMtx(N_KiMtx);

/* Gets GEJ85FNperContMtx Matrix */
 getGEJ85FNperContMtx(FNperContMtx);

/* Gets GEJ85FNcMaxContMtx Matrix */
 getGEJ85FNcMaxContMtx(FNcMaxContMtx);

/* Gets GEJ85NcMtx Matrix */
 getGEJ85NcMtx(NcMtx);

/* Gets GEJ85Pt21Mtx Matrix */
 getGEJ85Pt21Mtx(Pt21Mtx);

/* Gets GEJ85Pt3Mtx Matrix */
 getGEJ85Pt3Mtx(Pt3Mtx);

/* Gets GEJ85Pt5Mtx Matrix */
 getGEJ85Pt5Mtx(Pt5Mtx);

/* Gets GEJ85Pt6Mtx Matrix */
 getGEJ85Pt6Mtx(Pt6Mtx);

/* Gets GEJ85Tt21Mtx Matrix */
 getGEJ85Tt21Mtx(Tt21Mtx);

/* Gets GEJ85Tt3Mtx Matrix */
 getGEJ85Tt3Mtx(Tt3Mtx);

/* Gets GEJ85Tt4Mtx Matrix */
 getGEJ85Tt4Mtx(Tt4Mtx);

/* Gets GEJ85Tt5Mtx Matrix */
 getGEJ85Tt5Mtx(Tt5Mtx);

/* Gets GEJ85Tt6Mtx Matrix */
 getGEJ85Tt6Mtx(Tt6Mtx);

/* Gets GEJ85WfMtx Matrix */
 getGEJ85WfMtx(WfMtx);

/* Gets GEJ85AMtx Matrix */
 getGEJ85AMtx(AMtx);

/* Gets GEJ85BMtx Matrix */
 getGEJ85BMtx(BMtx);

/* Gets GEJ85Pt21DMtx Matrix */
 getGEJ85Pt21DMtx(Pt21DMtx);

/* Gets GEJ85Pt3DMtx Matrix */
 getGEJ85Pt3DMtx(Pt3DMtx);

/* Gets GEJ85Pt5DMtx Matrix */
 getGEJ85Pt5DMtx(Pt5DMtx);

/* Gets GEJ85Pt6DMtx Matrix */
 getGEJ85Pt6DMtx(Pt6DMtx);

/* Gets GEJ85Tt21DMtx Matrix */
 getGEJ85Tt21DMtx(Tt21DMtx);

/* Gets GEJ85Tt3DMtx Matrix */
 getGEJ85Tt3DMtx(Tt3DMtx);

/* Gets GEJ85Tt4DMtx Matrix */
 getGEJ85Tt4DMtx(Tt4DMtx);

/* Gets GEJ85Tt5DMtx Matrix */
 getGEJ85Tt5DMtx(Tt5DMtx);

/* Gets GEJ85Tt6DMtx Matrix */
 getGEJ85Tt6DMtx(Tt6DMtx);

/* Gets GEJ85NcFANMapMtx Matrix */
 getGEJ85NcFANMapMtx(NcFANMapMtx);

/* Gets GEJ85WcFANMapMtx Matrix */
 getGEJ85WcFANMapMtx(WcFANMapMtx);

/* Gets GEJ85WcFANStallMtx Matrix */
 getGEJ85WcFANStallMtx(WcFANStallMtx);

/* Gets GEJ85PRFANMapMtx Matrix */
 getGEJ85PRFANMapMtx(PRFANMapMtx);

/* Gets GEJ85PRFANStallMtx Matrix */
 getGEJ85PRFANStallMtx(PRFANStallMtx);

/* Gets GEJ85EffFANMapMtx Matrix */
 getGEJ85EffFANMapMtx(EffFANMapMtx);

/* Gets GEJ85NcHPTMapMtx Matrix */
 getGEJ85NcHPTMapMtx(NcHPTMapMtx);

/* Gets GEJ85WcHPTMapMtx Matrix */
 getGEJ85WcHPTMapMtx(WcHPTMapMtx);

/* Gets GEJ85PRHPTMapMtx Matrix */
 getGEJ85PRHPTMapMtx(PRHPTMapMtx);

/* Gets GEJ85EffHPTMapMtx Matrix */
 getGEJ85EffHPTMapMtx(EffHPTMapMtx);

/* Gets GEJ85NcHPCMapMtx Matrix */
 getGEJ85NcHPCMapMtx(NcHPCMapMtx);

/* Gets GEJ85WcHPCMapMtx Matrix */
 getGEJ85WcHPCMapMtx(WcHPCMapMtx);

/* Gets GEJ85WcHPCStallMtx Matrix */
 getGEJ85WcHPCStallMtx(WcHPCStallMtx);

/* Gets GEJ85PRHPCMapMtx Matrix */
 getGEJ85PRHPCMapMtx(PRHPCMapMtx);

/* Gets GEJ85PRHPCStallMtx Matrix */
 getGEJ85PRHPCStallMtx(PRHPCStallMtx);

/* Gets GEJ85EffHPCMapMtx Matrix */
 getGEJ85EffHPCMapMtx(EffHPCMapMtx);

/* Gets GEJ85MNLinVec Matrix */
 getGEJ85MNLinVec(MNLinVec);

/* Gets GEJ85AltLinVec Matrix */
 getGEJ85AltLinVec(AltLinVec);

/* Gets GEJ85DeltaMtx Matrix */
 getGEJ85DeltaMtx(DeltaMtx);

/* Gets GEJ85Ts0Mtx Matrix */
 getGEJ85Ts0Mtx(Ts0Mtx);

/* Gets GEJ85AwmMtx Matrix */
 getGEJ85AwmMtx(AwmMtx);

/* Gets GEJ85AshMtx Matrix */
 getGEJ85AshMtx(AshMtx);

/* Gets GEJ85BwmMtx Matrix */
 getGEJ85BwmMtx(BwmMtx);

/* Gets GEJ85BshMtx Matrix */
 getGEJ85BshMtx(BshMtx);

/* Gets GEJ85RPMwmMtx Matrix */
 getGEJ85RPMwmMtx(RPMwmMtx);

/* Gets GEJ85RPMshMtx Matrix */
 getGEJ85RPMshMtx(RPMshMtx);

/* Gets GEJ85Tt4CshMtx Matrix */
 getGEJ85Tt4CshMtx(Tt4CshMtx);

/* Gets GEJ85Tt4DshMtx Matrix */
 getGEJ85Tt4DshMtx(Tt4DshMtx);

/* Gets GEJ85Tt4shMtx Matrix */
 getGEJ85Tt4shMtx(Tt4shMtx);

/* Gets GEJ85WfshMtx Matrix */
 getGEJ85WfshMtx(WfshMtx);

/* Gets GEJ85ASVec Matrix */
 getGEJ85ASVec(ASVec);

/* Gets GEJ85DSVec Matrix */
 getGEJ85DSVec(DSVec);

/* Gets GEJ85NcVec Matrix */
 getGEJ85NcVec(NcVec);

/* Gets GEJ85NcFANshMtx Matrix */
 getGEJ85NcFANshMtx(NcFANshMtx);

/* Gets GEJ85WfwmMtx Matrix */
 getGEJ85WfwmMtx(WfwmMtx);

/* Gets GEJ85Pt3shMtx Matrix */
 getGEJ85Pt3shMtx(Pt3shMtx);

/* Gets GEJ85Pt3DshMtx Matrix */
 getGEJ85Pt3DshMtx(Pt3DshMtx);

/* Gets GEJ85Pt21wmMtx Matrix */
 getGEJ85Pt21wmMtx(Pt21wmMtx);

/* Gets GEJ85Pt21DwmMtx Matrix */
 getGEJ85Pt21DwmMtx(Pt21DwmMtx);

/* Gets GEJ85Pt3wmMtx Matrix */
 getGEJ85Pt3wmMtx(Pt3wmMtx);

/* Gets GEJ85Pt3DwmMtx Matrix */
 getGEJ85Pt3DwmMtx(Pt3DwmMtx);

/* Gets GEJ85Pt5wmMtx Matrix */
 getGEJ85Pt5wmMtx(Pt5wmMtx);

/* Gets GEJ85Pt5DwmMtx Matrix */
 getGEJ85Pt5DwmMtx(Pt5DwmMtx);

/* Gets GEJ85Pt6wmMtx Matrix */
 getGEJ85Pt6wmMtx(Pt6wmMtx);

/* Gets GEJ85Pt6DwmMtx Matrix */
 getGEJ85Pt6DwmMtx(Pt6DwmMtx);

/* Gets GEJ85Tt21wmMtx Matrix */
 getGEJ85Tt21wmMtx(Tt21wmMtx);

/* Gets GEJ85Tt21DwmMtx Matrix */
 getGEJ85Tt21DwmMtx(Tt21DwmMtx);

/* Gets GEJ85Tt3wmMtx Matrix */
 getGEJ85Tt3wmMtx(Tt3wmMtx);

/* Gets GEJ85Tt3DwmMtx Matrix */
 getGEJ85Tt3DwmMtx(Tt3DwmMtx);

/* Gets GEJ85Tt4wmMtx Matrix */
 getGEJ85Tt4wmMtx(Tt4wmMtx);

/* Gets GEJ85Tt4DwmMtx Matrix */
 getGEJ85Tt4DwmMtx(Tt4DwmMtx);

/* Gets GEJ85Tt5wmMtx Matrix */
 getGEJ85Tt5wmMtx(Tt5wmMtx);

/* Gets GEJ85Tt5DwmMtx Matrix */
 getGEJ85Tt5DwmMtx(Tt5DwmMtx);

/* Gets GEJ85Tt6wmMtx Matrix */
 getGEJ85Tt6wmMtx(Tt6wmMtx);

/* Gets GEJ85Tt6DwmMtx Matrix */
 getGEJ85Tt6DwmMtx(Tt6DwmMtx);

/* Gets GEJ85Pt21shMtx Matrix */
 getGEJ85Pt21shMtx(Pt21shMtx);

/* Gets GEJ85Pt21DshMtx Matrix */
 getGEJ85Pt21DshMtx(Pt21DshMtx);

/* Gets GEJ85Pt5shMtx Matrix */
 getGEJ85Pt5shMtx(Pt5shMtx);

/* Gets GEJ85Pt5DshMtx Matrix */
 getGEJ85Pt5DshMtx(Pt5DshMtx);

/* Gets GEJ85Pt6shMtx Matrix */
 getGEJ85Pt6shMtx(Pt6shMtx);

/* Gets GEJ85Pt6DshMtx Matrix */
 getGEJ85Pt6DshMtx(Pt6DshMtx);

/* Gets GEJ85Tt21shMtx Matrix */
 getGEJ85Tt21shMtx(Tt21shMtx);

/* Gets GEJ85Tt21DshMtx Matrix */
 getGEJ85Tt21DshMtx(Tt21DshMtx);

/* Gets GEJ85Tt3shMtx Matrix */
 getGEJ85Tt3shMtx(Tt3shMtx);

/* Gets GEJ85Tt3DshMtx Matrix */
 getGEJ85Tt3DshMtx(Tt3DshMtx);

/* Gets GEJ85Tt5shMtx Matrix */
 getGEJ85Tt5shMtx(Tt5shMtx);

/* Gets GEJ85Tt5DshMtx Matrix */
 getGEJ85Tt5DshMtx(Tt5DshMtx);

/* Gets GEJ85Tt6shMtx Matrix */
 getGEJ85Tt6shMtx(Tt6shMtx);

/* Gets GEJ85Tt6DshMtx Matrix */
 getGEJ85Tt6DshMtx(Tt6DshMtx);