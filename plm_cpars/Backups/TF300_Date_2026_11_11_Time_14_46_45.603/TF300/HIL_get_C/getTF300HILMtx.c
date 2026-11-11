
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../HIL_get_H/getTF300HIL.h"

void getTF300HILMtx(floating *AshMtx, floating *AwmMtx, floating *BshMtx, floating *BwmMtx, floating *EffFANMapMtx, 
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

/* Gets TF300AshMtx Matrix */
 getTF300AshMtx(AshMtx);

/* Gets TF300AwmMtx Matrix */
 getTF300AwmMtx(AwmMtx);

/* Gets TF300BshMtx Matrix */
 getTF300BshMtx(BshMtx);

/* Gets TF300BwmMtx Matrix */
 getTF300BwmMtx(BwmMtx);

/* Gets TF300EffFANMapMtx Matrix */
 getTF300EffFANMapMtx(EffFANMapMtx);

/* Gets TF300EffHPCMapMtx Matrix */
 getTF300EffHPCMapMtx(EffHPCMapMtx);

/* Gets TF300EffHPTMapMtx Matrix */
 getTF300EffHPTMapMtx(EffHPTMapMtx);

/* Gets TF300NcFANMapMtx Matrix */
 getTF300NcFANMapMtx(NcFANMapMtx);

/* Gets TF300NcHPTMapMtx Matrix */
 getTF300NcHPTMapMtx(NcHPTMapMtx);

/* Gets TF300NcMtx Matrix */
 getTF300NcMtx(NcMtx);

/* Gets TF300PRFANMapMtx Matrix */
 getTF300PRFANMapMtx(PRFANMapMtx);

/* Gets TF300PRFANStallMtx Matrix */
 getTF300PRFANStallMtx(PRFANStallMtx);

/* Gets TF300PRHPCStallMtx Matrix */
 getTF300PRHPCStallMtx(PRHPCStallMtx);

/* Gets TF300PRHPTMapMtx Matrix */
 getTF300PRHPTMapMtx(PRHPTMapMtx);

/* Gets TF300Pt21DMtx Matrix */
 getTF300Pt21DMtx(Pt21DMtx);

/* Gets TF300Pt21Mtx Matrix */
 getTF300Pt21Mtx(Pt21Mtx);

/* Gets TF300Pt6DMtx Matrix */
 getTF300Pt6DMtx(Pt6DMtx);

/* Gets TF300Pt6Mtx Matrix */
 getTF300Pt6Mtx(Pt6Mtx);

/* Gets TF300RPMshMtx Matrix */
 getTF300RPMshMtx(RPMshMtx);

/* Gets TF300RPMwmMtx Matrix */
 getTF300RPMwmMtx(RPMwmMtx);

/* Gets TF300Tt21DMtx Matrix */
 getTF300Tt21DMtx(Tt21DMtx);

/* Gets TF300Tt21Mtx Matrix */
 getTF300Tt21Mtx(Tt21Mtx);

/* Gets TF300Tt3DMtx Matrix */
 getTF300Tt3DMtx(Tt3DMtx);

/* Gets TF300Tt3Mtx Matrix */
 getTF300Tt3Mtx(Tt3Mtx);

/* Gets TF300Tt4CshMtx Matrix */
 getTF300Tt4CshMtx(Tt4CshMtx);

/* Gets TF300Tt4DshMtx Matrix */
 getTF300Tt4DshMtx(Tt4DshMtx);

/* Gets TF300Tt4shMtx Matrix */
 getTF300Tt4shMtx(Tt4shMtx);

/* Gets TF300Tt6DMtx Matrix */
 getTF300Tt6DMtx(Tt6DMtx);

/* Gets TF300Tt6Mtx Matrix */
 getTF300Tt6Mtx(Tt6Mtx);

/* Gets TF300WcFANMapMtx Matrix */
 getTF300WcFANMapMtx(WcFANMapMtx);

/* Gets TF300WcFANStallMtx Matrix */
 getTF300WcFANStallMtx(WcFANStallMtx);

/* Gets TF300WcHPCStallMtx Matrix */
 getTF300WcHPCStallMtx(WcHPCStallMtx);

/* Gets TF300WcHPTMapMtx Matrix */
 getTF300WcHPTMapMtx(WcHPTMapMtx);

/* Gets TF300WfshMtx Matrix */
 getTF300WfshMtx(WfshMtx);

/* Gets TF300NcFANshMtx Matrix */
 getTF300NcFANshMtx(NcFANshMtx);

/* Gets TF300WfwmMtx Matrix */
 getTF300WfwmMtx(WfwmMtx);

/* Gets TF300Pt3shMtx Matrix */
 getTF300Pt3shMtx(Pt3shMtx);

/* Gets TF300Pt3DshMtx Matrix */
 getTF300Pt3DshMtx(Pt3DshMtx);

/* Gets TF300Pt21wmMtx Matrix */
 getTF300Pt21wmMtx(Pt21wmMtx);

/* Gets TF300Pt21DwmMtx Matrix */
 getTF300Pt21DwmMtx(Pt21DwmMtx);

/* Gets TF300Pt3wmMtx Matrix */
 getTF300Pt3wmMtx(Pt3wmMtx);

/* Gets TF300Pt3DwmMtx Matrix */
 getTF300Pt3DwmMtx(Pt3DwmMtx);

/* Gets TF300Pt5wmMtx Matrix */
 getTF300Pt5wmMtx(Pt5wmMtx);

/* Gets TF300Pt5DwmMtx Matrix */
 getTF300Pt5DwmMtx(Pt5DwmMtx);

/* Gets TF300Pt6wmMtx Matrix */
 getTF300Pt6wmMtx(Pt6wmMtx);

/* Gets TF300Pt6DwmMtx Matrix */
 getTF300Pt6DwmMtx(Pt6DwmMtx);

/* Gets TF300Tt21wmMtx Matrix */
 getTF300Tt21wmMtx(Tt21wmMtx);

/* Gets TF300Tt21DwmMtx Matrix */
 getTF300Tt21DwmMtx(Tt21DwmMtx);

/* Gets TF300Tt3wmMtx Matrix */
 getTF300Tt3wmMtx(Tt3wmMtx);

/* Gets TF300Tt3DwmMtx Matrix */
 getTF300Tt3DwmMtx(Tt3DwmMtx);

/* Gets TF300Tt4wmMtx Matrix */
 getTF300Tt4wmMtx(Tt4wmMtx);

/* Gets TF300Tt4DwmMtx Matrix */
 getTF300Tt4DwmMtx(Tt4DwmMtx);

/* Gets TF300Tt5wmMtx Matrix */
 getTF300Tt5wmMtx(Tt5wmMtx);

/* Gets TF300Tt5DwmMtx Matrix */
 getTF300Tt5DwmMtx(Tt5DwmMtx);

/* Gets TF300Tt6wmMtx Matrix */
 getTF300Tt6wmMtx(Tt6wmMtx);

/* Gets TF300Tt6DwmMtx Matrix */
 getTF300Tt6DwmMtx(Tt6DwmMtx);

/* Gets TF300Pt21shMtx Matrix */
 getTF300Pt21shMtx(Pt21shMtx);

/* Gets TF300Pt21DshMtx Matrix */
 getTF300Pt21DshMtx(Pt21DshMtx);

/* Gets TF300Pt5shMtx Matrix */
 getTF300Pt5shMtx(Pt5shMtx);

/* Gets TF300Pt5DshMtx Matrix */
 getTF300Pt5DshMtx(Pt5DshMtx);

/* Gets TF300Pt6shMtx Matrix */
 getTF300Pt6shMtx(Pt6shMtx);

/* Gets TF300Pt6DshMtx Matrix */
 getTF300Pt6DshMtx(Pt6DshMtx);

/* Gets TF300Tt21shMtx Matrix */
 getTF300Tt21shMtx(Tt21shMtx);

/* Gets TF300Tt21DshMtx Matrix */
 getTF300Tt21DshMtx(Tt21DshMtx);

/* Gets TF300Tt3shMtx Matrix */
 getTF300Tt3shMtx(Tt3shMtx);

/* Gets TF300Tt3DshMtx Matrix */
 getTF300Tt3DshMtx(Tt3DshMtx);

/* Gets TF300Tt5shMtx Matrix */
 getTF300Tt5shMtx(Tt5shMtx);

/* Gets TF300Tt5DshMtx Matrix */
 getTF300Tt5DshMtx(Tt5DshMtx);

/* Gets TF300Tt6shMtx Matrix */
 getTF300Tt6shMtx(Tt6shMtx);

/* Gets TF300Tt6DshMtx Matrix */
 getTF300Tt6DshMtx(Tt6DshMtx);

}

