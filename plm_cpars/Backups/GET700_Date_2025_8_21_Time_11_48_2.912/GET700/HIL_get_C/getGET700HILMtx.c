
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../HIL_get_H/getGET700HIL.h"

void getGET700HILMtx(floating *AshMtx, floating *AwmMtx, floating *BshMtx, floating *BwmMtx, floating *EffFANMapMtx, 
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

/* Gets GET700AshMtx Matrix */
 getGET700AshMtx(AshMtx);

/* Gets GET700AwmMtx Matrix */
 getGET700AwmMtx(AwmMtx);

/* Gets GET700BshMtx Matrix */
 getGET700BshMtx(BshMtx);

/* Gets GET700BwmMtx Matrix */
 getGET700BwmMtx(BwmMtx);

/* Gets GET700EffFANMapMtx Matrix */
 getGET700EffFANMapMtx(EffFANMapMtx);

/* Gets GET700EffHPCMapMtx Matrix */
 getGET700EffHPCMapMtx(EffHPCMapMtx);

/* Gets GET700EffHPTMapMtx Matrix */
 getGET700EffHPTMapMtx(EffHPTMapMtx);

/* Gets GET700NcFANMapMtx Matrix */
 getGET700NcFANMapMtx(NcFANMapMtx);

/* Gets GET700NcHPTMapMtx Matrix */
 getGET700NcHPTMapMtx(NcHPTMapMtx);

/* Gets GET700NcMtx Matrix */
 getGET700NcMtx(NcMtx);

/* Gets GET700PRFANMapMtx Matrix */
 getGET700PRFANMapMtx(PRFANMapMtx);

/* Gets GET700PRFANStallMtx Matrix */
 getGET700PRFANStallMtx(PRFANStallMtx);

/* Gets GET700PRHPCStallMtx Matrix */
 getGET700PRHPCStallMtx(PRHPCStallMtx);

/* Gets GET700PRHPTMapMtx Matrix */
 getGET700PRHPTMapMtx(PRHPTMapMtx);

/* Gets GET700Pt21DMtx Matrix */
 getGET700Pt21DMtx(Pt21DMtx);

/* Gets GET700Pt21Mtx Matrix */
 getGET700Pt21Mtx(Pt21Mtx);

/* Gets GET700Pt6DMtx Matrix */
 getGET700Pt6DMtx(Pt6DMtx);

/* Gets GET700Pt6Mtx Matrix */
 getGET700Pt6Mtx(Pt6Mtx);

/* Gets GET700RPMshMtx Matrix */
 getGET700RPMshMtx(RPMshMtx);

/* Gets GET700RPMwmMtx Matrix */
 getGET700RPMwmMtx(RPMwmMtx);

/* Gets GET700Tt21DMtx Matrix */
 getGET700Tt21DMtx(Tt21DMtx);

/* Gets GET700Tt21Mtx Matrix */
 getGET700Tt21Mtx(Tt21Mtx);

/* Gets GET700Tt3DMtx Matrix */
 getGET700Tt3DMtx(Tt3DMtx);

/* Gets GET700Tt3Mtx Matrix */
 getGET700Tt3Mtx(Tt3Mtx);

/* Gets GET700Tt4CshMtx Matrix */
 getGET700Tt4CshMtx(Tt4CshMtx);

/* Gets GET700Tt4DshMtx Matrix */
 getGET700Tt4DshMtx(Tt4DshMtx);

/* Gets GET700Tt4shMtx Matrix */
 getGET700Tt4shMtx(Tt4shMtx);

/* Gets GET700Tt6DMtx Matrix */
 getGET700Tt6DMtx(Tt6DMtx);

/* Gets GET700Tt6Mtx Matrix */
 getGET700Tt6Mtx(Tt6Mtx);

/* Gets GET700WcFANMapMtx Matrix */
 getGET700WcFANMapMtx(WcFANMapMtx);

/* Gets GET700WcFANStallMtx Matrix */
 getGET700WcFANStallMtx(WcFANStallMtx);

/* Gets GET700WcHPCStallMtx Matrix */
 getGET700WcHPCStallMtx(WcHPCStallMtx);

/* Gets GET700WcHPTMapMtx Matrix */
 getGET700WcHPTMapMtx(WcHPTMapMtx);

/* Gets GET700WfshMtx Matrix */
 getGET700WfshMtx(WfshMtx);

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

}

