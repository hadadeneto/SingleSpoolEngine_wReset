
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../HIL_get_H/getGEJ85HIL.h"

void getGEJ85HILMtx(floating *AshMtx, floating *AwmMtx, floating *BshMtx, floating *BwmMtx, floating *EffFANMapMtx, 
     floating *EffHPCMapMtx, floating *EffHPTMapMtx, floating *NcFANMapMtx, floating *NcHPTMapMtx, floating *NcMtx, 
     floating *PRFANMapMtx, floating *PRFANStallMtx, floating *PRHPCStallMtx, floating *PRHPTMapMtx, floating *Pt21DMtx, 
     floating *Pt21Mtx, floating *Pt6DMtx, floating *Pt6Mtx, floating *RPMshMtx, floating *RPMwmMtx, 
     floating *Tt21DMtx, floating *Tt21Mtx, floating *Tt3DMtx, floating *Tt3Mtx, floating *Tt4CshMtx, 
     floating *Tt4DshMtx, floating *Tt4shMtx, floating *Tt6DMtx, floating *Tt6Mtx, floating *WcFANMapMtx, 
     floating *WcFANStallMtx, floating *WcHPCStallMtx, floating *WcHPTMapMtx, floating *WfshMtx, floating *NcFANshMtx, 
     floating *WfwmMtx, floating *Pt3shMtx, floating *Pt3DshMtx, floating *Pt21wmMtx, floating *Pt21DwmMtx, 
     floating *Pt3wmMtx, floating *Pt3DwmMtx, floating *Pt5wmMtx, floating *Pt5DwmMtx, floating *Pt6wmMtx, 
     floating *Pt6DwmMtx, floating *Tt21wmMtx, floating *Tt21DwmMtx, floating *Tt3wmMtx, floating *Tt3DwmMtx, 
     floating *Tt4wmMtx, floating *Tt4DwmMtx, floating *Tt5wmMtx, floating *Tt5DwmMtx, floating *Tt6wmMtx, 
     floating *Tt6DwmMtx, floating *Pt21shMtx, floating *Pt21DshMtx, floating *Pt5shMtx, floating *Pt5DshMtx, 
     floating *Pt6shMtx, floating *Pt6DshMtx, floating *Tt21shMtx, floating *Tt21DshMtx, floating *Tt3shMtx, 
     floating *Tt3DshMtx, floating *Tt5shMtx, floating *Tt5DshMtx, floating *Tt6shMtx, floating *Tt6DshMtx)

{

/* Gets GEJ85AshMtx Matrix */
 getGEJ85AshMtx(AshMtx);

/* Gets GEJ85AwmMtx Matrix */
 getGEJ85AwmMtx(AwmMtx);

/* Gets GEJ85BshMtx Matrix */
 getGEJ85BshMtx(BshMtx);

/* Gets GEJ85BwmMtx Matrix */
 getGEJ85BwmMtx(BwmMtx);

/* Gets GEJ85EffFANMapMtx Matrix */
 getGEJ85EffFANMapMtx(EffFANMapMtx);

/* Gets GEJ85EffHPCMapMtx Matrix */
 getGEJ85EffHPCMapMtx(EffHPCMapMtx);

/* Gets GEJ85EffHPTMapMtx Matrix */
 getGEJ85EffHPTMapMtx(EffHPTMapMtx);

/* Gets GEJ85NcFANMapMtx Matrix */
 getGEJ85NcFANMapMtx(NcFANMapMtx);

/* Gets GEJ85NcHPTMapMtx Matrix */
 getGEJ85NcHPTMapMtx(NcHPTMapMtx);

/* Gets GEJ85NcMtx Matrix */
 getGEJ85NcMtx(NcMtx);

/* Gets GEJ85PRFANMapMtx Matrix */
 getGEJ85PRFANMapMtx(PRFANMapMtx);

/* Gets GEJ85PRFANStallMtx Matrix */
 getGEJ85PRFANStallMtx(PRFANStallMtx);

/* Gets GEJ85PRHPCStallMtx Matrix */
 getGEJ85PRHPCStallMtx(PRHPCStallMtx);

/* Gets GEJ85PRHPTMapMtx Matrix */
 getGEJ85PRHPTMapMtx(PRHPTMapMtx);

/* Gets GEJ85Pt21DMtx Matrix */
 getGEJ85Pt21DMtx(Pt21DMtx);

/* Gets GEJ85Pt21Mtx Matrix */
 getGEJ85Pt21Mtx(Pt21Mtx);

/* Gets GEJ85Pt6DMtx Matrix */
 getGEJ85Pt6DMtx(Pt6DMtx);

/* Gets GEJ85Pt6Mtx Matrix */
 getGEJ85Pt6Mtx(Pt6Mtx);

/* Gets GEJ85RPMshMtx Matrix */
 getGEJ85RPMshMtx(RPMshMtx);

/* Gets GEJ85RPMwmMtx Matrix */
 getGEJ85RPMwmMtx(RPMwmMtx);

/* Gets GEJ85Tt21DMtx Matrix */
 getGEJ85Tt21DMtx(Tt21DMtx);

/* Gets GEJ85Tt21Mtx Matrix */
 getGEJ85Tt21Mtx(Tt21Mtx);

/* Gets GEJ85Tt3DMtx Matrix */
 getGEJ85Tt3DMtx(Tt3DMtx);

/* Gets GEJ85Tt3Mtx Matrix */
 getGEJ85Tt3Mtx(Tt3Mtx);

/* Gets GEJ85Tt4CshMtx Matrix */
 getGEJ85Tt4CshMtx(Tt4CshMtx);

/* Gets GEJ85Tt4DshMtx Matrix */
 getGEJ85Tt4DshMtx(Tt4DshMtx);

/* Gets GEJ85Tt4shMtx Matrix */
 getGEJ85Tt4shMtx(Tt4shMtx);

/* Gets GEJ85Tt6DMtx Matrix */
 getGEJ85Tt6DMtx(Tt6DMtx);

/* Gets GEJ85Tt6Mtx Matrix */
 getGEJ85Tt6Mtx(Tt6Mtx);

/* Gets GEJ85WcFANMapMtx Matrix */
 getGEJ85WcFANMapMtx(WcFANMapMtx);

/* Gets GEJ85WcFANStallMtx Matrix */
 getGEJ85WcFANStallMtx(WcFANStallMtx);

/* Gets GEJ85WcHPCStallMtx Matrix */
 getGEJ85WcHPCStallMtx(WcHPCStallMtx);

/* Gets GEJ85WcHPTMapMtx Matrix */
 getGEJ85WcHPTMapMtx(WcHPTMapMtx);

/* Gets GEJ85WfshMtx Matrix */
 getGEJ85WfshMtx(WfshMtx);

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

}

