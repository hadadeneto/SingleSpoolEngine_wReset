
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../HIL_get_H/getTJ700HIL.h"

void getTJ700HILMtx(floating *AshMtx, floating *AwmMtx, floating *BshMtx, floating *BwmMtx, floating *EffFANMapMtx, 
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

/* Gets TJ700AshMtx Matrix */
 getTJ700AshMtx(AshMtx);

/* Gets TJ700AwmMtx Matrix */
 getTJ700AwmMtx(AwmMtx);

/* Gets TJ700BshMtx Matrix */
 getTJ700BshMtx(BshMtx);

/* Gets TJ700BwmMtx Matrix */
 getTJ700BwmMtx(BwmMtx);

/* Gets TJ700EffFANMapMtx Matrix */
 getTJ700EffFANMapMtx(EffFANMapMtx);

/* Gets TJ700EffHPCMapMtx Matrix */
 getTJ700EffHPCMapMtx(EffHPCMapMtx);

/* Gets TJ700EffHPTMapMtx Matrix */
 getTJ700EffHPTMapMtx(EffHPTMapMtx);

/* Gets TJ700NcFANMapMtx Matrix */
 getTJ700NcFANMapMtx(NcFANMapMtx);

/* Gets TJ700NcHPTMapMtx Matrix */
 getTJ700NcHPTMapMtx(NcHPTMapMtx);

/* Gets TJ700NcMtx Matrix */
 getTJ700NcMtx(NcMtx);

/* Gets TJ700PRFANMapMtx Matrix */
 getTJ700PRFANMapMtx(PRFANMapMtx);

/* Gets TJ700PRFANStallMtx Matrix */
 getTJ700PRFANStallMtx(PRFANStallMtx);

/* Gets TJ700PRHPCStallMtx Matrix */
 getTJ700PRHPCStallMtx(PRHPCStallMtx);

/* Gets TJ700PRHPTMapMtx Matrix */
 getTJ700PRHPTMapMtx(PRHPTMapMtx);

/* Gets TJ700Pt21DMtx Matrix */
 getTJ700Pt21DMtx(Pt21DMtx);

/* Gets TJ700Pt21Mtx Matrix */
 getTJ700Pt21Mtx(Pt21Mtx);

/* Gets TJ700Pt6DMtx Matrix */
 getTJ700Pt6DMtx(Pt6DMtx);

/* Gets TJ700Pt6Mtx Matrix */
 getTJ700Pt6Mtx(Pt6Mtx);

/* Gets TJ700RPMshMtx Matrix */
 getTJ700RPMshMtx(RPMshMtx);

/* Gets TJ700RPMwmMtx Matrix */
 getTJ700RPMwmMtx(RPMwmMtx);

/* Gets TJ700Tt21DMtx Matrix */
 getTJ700Tt21DMtx(Tt21DMtx);

/* Gets TJ700Tt21Mtx Matrix */
 getTJ700Tt21Mtx(Tt21Mtx);

/* Gets TJ700Tt3DMtx Matrix */
 getTJ700Tt3DMtx(Tt3DMtx);

/* Gets TJ700Tt3Mtx Matrix */
 getTJ700Tt3Mtx(Tt3Mtx);

/* Gets TJ700Tt4CshMtx Matrix */
 getTJ700Tt4CshMtx(Tt4CshMtx);

/* Gets TJ700Tt4DshMtx Matrix */
 getTJ700Tt4DshMtx(Tt4DshMtx);

/* Gets TJ700Tt4shMtx Matrix */
 getTJ700Tt4shMtx(Tt4shMtx);

/* Gets TJ700Tt6DMtx Matrix */
 getTJ700Tt6DMtx(Tt6DMtx);

/* Gets TJ700Tt6Mtx Matrix */
 getTJ700Tt6Mtx(Tt6Mtx);

/* Gets TJ700WcFANMapMtx Matrix */
 getTJ700WcFANMapMtx(WcFANMapMtx);

/* Gets TJ700WcFANStallMtx Matrix */
 getTJ700WcFANStallMtx(WcFANStallMtx);

/* Gets TJ700WcHPCStallMtx Matrix */
 getTJ700WcHPCStallMtx(WcHPCStallMtx);

/* Gets TJ700WcHPTMapMtx Matrix */
 getTJ700WcHPTMapMtx(WcHPTMapMtx);

/* Gets TJ700WfshMtx Matrix */
 getTJ700WfshMtx(WfshMtx);

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

}

