
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../HIL_get_H/getTJ40HIL.h"

void getTJ40HILMtx(floating *AshMtx, floating *AwmMtx, floating *BshMtx, floating *BwmMtx, floating *EffFANMapMtx, 
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

/* Gets TJ40AshMtx Matrix */
 getTJ40AshMtx(AshMtx);

/* Gets TJ40AwmMtx Matrix */
 getTJ40AwmMtx(AwmMtx);

/* Gets TJ40BshMtx Matrix */
 getTJ40BshMtx(BshMtx);

/* Gets TJ40BwmMtx Matrix */
 getTJ40BwmMtx(BwmMtx);

/* Gets TJ40EffFANMapMtx Matrix */
 getTJ40EffFANMapMtx(EffFANMapMtx);

/* Gets TJ40EffHPCMapMtx Matrix */
 getTJ40EffHPCMapMtx(EffHPCMapMtx);

/* Gets TJ40EffHPTMapMtx Matrix */
 getTJ40EffHPTMapMtx(EffHPTMapMtx);

/* Gets TJ40NcFANMapMtx Matrix */
 getTJ40NcFANMapMtx(NcFANMapMtx);

/* Gets TJ40NcHPTMapMtx Matrix */
 getTJ40NcHPTMapMtx(NcHPTMapMtx);

/* Gets TJ40NcMtx Matrix */
 getTJ40NcMtx(NcMtx);

/* Gets TJ40PRFANMapMtx Matrix */
 getTJ40PRFANMapMtx(PRFANMapMtx);

/* Gets TJ40PRFANStallMtx Matrix */
 getTJ40PRFANStallMtx(PRFANStallMtx);

/* Gets TJ40PRHPCStallMtx Matrix */
 getTJ40PRHPCStallMtx(PRHPCStallMtx);

/* Gets TJ40PRHPTMapMtx Matrix */
 getTJ40PRHPTMapMtx(PRHPTMapMtx);

/* Gets TJ40Pt21DMtx Matrix */
 getTJ40Pt21DMtx(Pt21DMtx);

/* Gets TJ40Pt21Mtx Matrix */
 getTJ40Pt21Mtx(Pt21Mtx);

/* Gets TJ40Pt6DMtx Matrix */
 getTJ40Pt6DMtx(Pt6DMtx);

/* Gets TJ40Pt6Mtx Matrix */
 getTJ40Pt6Mtx(Pt6Mtx);

/* Gets TJ40RPMshMtx Matrix */
 getTJ40RPMshMtx(RPMshMtx);

/* Gets TJ40RPMwmMtx Matrix */
 getTJ40RPMwmMtx(RPMwmMtx);

/* Gets TJ40Tt21DMtx Matrix */
 getTJ40Tt21DMtx(Tt21DMtx);

/* Gets TJ40Tt21Mtx Matrix */
 getTJ40Tt21Mtx(Tt21Mtx);

/* Gets TJ40Tt3DMtx Matrix */
 getTJ40Tt3DMtx(Tt3DMtx);

/* Gets TJ40Tt3Mtx Matrix */
 getTJ40Tt3Mtx(Tt3Mtx);

/* Gets TJ40Tt4CshMtx Matrix */
 getTJ40Tt4CshMtx(Tt4CshMtx);

/* Gets TJ40Tt4DshMtx Matrix */
 getTJ40Tt4DshMtx(Tt4DshMtx);

/* Gets TJ40Tt4shMtx Matrix */
 getTJ40Tt4shMtx(Tt4shMtx);

/* Gets TJ40Tt6DMtx Matrix */
 getTJ40Tt6DMtx(Tt6DMtx);

/* Gets TJ40Tt6Mtx Matrix */
 getTJ40Tt6Mtx(Tt6Mtx);

/* Gets TJ40WcFANMapMtx Matrix */
 getTJ40WcFANMapMtx(WcFANMapMtx);

/* Gets TJ40WcFANStallMtx Matrix */
 getTJ40WcFANStallMtx(WcFANStallMtx);

/* Gets TJ40WcHPCStallMtx Matrix */
 getTJ40WcHPCStallMtx(WcHPCStallMtx);

/* Gets TJ40WcHPTMapMtx Matrix */
 getTJ40WcHPTMapMtx(WcHPTMapMtx);

/* Gets TJ40WfshMtx Matrix */
 getTJ40WfshMtx(WfshMtx);

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

}

