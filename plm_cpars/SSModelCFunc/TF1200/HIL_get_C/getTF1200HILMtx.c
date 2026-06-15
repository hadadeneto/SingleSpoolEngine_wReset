
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../HIL_get_H/getTF1200HIL.h"

void getTF1200HILMtx(floating *AshMtx, floating *AwmMtx, floating *BshMtx, floating *BwmMtx, floating *EffFANMapMtx, 
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

/* Gets TF1200AshMtx Matrix */
 getTF1200AshMtx(AshMtx);

/* Gets TF1200AwmMtx Matrix */
 getTF1200AwmMtx(AwmMtx);

/* Gets TF1200BshMtx Matrix */
 getTF1200BshMtx(BshMtx);

/* Gets TF1200BwmMtx Matrix */
 getTF1200BwmMtx(BwmMtx);

/* Gets TF1200EffFANMapMtx Matrix */
 getTF1200EffFANMapMtx(EffFANMapMtx);

/* Gets TF1200EffHPCMapMtx Matrix */
 getTF1200EffHPCMapMtx(EffHPCMapMtx);

/* Gets TF1200EffHPTMapMtx Matrix */
 getTF1200EffHPTMapMtx(EffHPTMapMtx);

/* Gets TF1200NcFANMapMtx Matrix */
 getTF1200NcFANMapMtx(NcFANMapMtx);

/* Gets TF1200NcHPTMapMtx Matrix */
 getTF1200NcHPTMapMtx(NcHPTMapMtx);

/* Gets TF1200NcMtx Matrix */
 getTF1200NcMtx(NcMtx);

/* Gets TF1200PRFANMapMtx Matrix */
 getTF1200PRFANMapMtx(PRFANMapMtx);

/* Gets TF1200PRFANStallMtx Matrix */
 getTF1200PRFANStallMtx(PRFANStallMtx);

/* Gets TF1200PRHPCStallMtx Matrix */
 getTF1200PRHPCStallMtx(PRHPCStallMtx);

/* Gets TF1200PRHPTMapMtx Matrix */
 getTF1200PRHPTMapMtx(PRHPTMapMtx);

/* Gets TF1200Pt21DMtx Matrix */
 getTF1200Pt21DMtx(Pt21DMtx);

/* Gets TF1200Pt21Mtx Matrix */
 getTF1200Pt21Mtx(Pt21Mtx);

/* Gets TF1200Pt6DMtx Matrix */
 getTF1200Pt6DMtx(Pt6DMtx);

/* Gets TF1200Pt6Mtx Matrix */
 getTF1200Pt6Mtx(Pt6Mtx);

/* Gets TF1200RPMshMtx Matrix */
 getTF1200RPMshMtx(RPMshMtx);

/* Gets TF1200RPMwmMtx Matrix */
 getTF1200RPMwmMtx(RPMwmMtx);

/* Gets TF1200Tt21DMtx Matrix */
 getTF1200Tt21DMtx(Tt21DMtx);

/* Gets TF1200Tt21Mtx Matrix */
 getTF1200Tt21Mtx(Tt21Mtx);

/* Gets TF1200Tt3DMtx Matrix */
 getTF1200Tt3DMtx(Tt3DMtx);

/* Gets TF1200Tt3Mtx Matrix */
 getTF1200Tt3Mtx(Tt3Mtx);

/* Gets TF1200Tt4CshMtx Matrix */
 getTF1200Tt4CshMtx(Tt4CshMtx);

/* Gets TF1200Tt4DshMtx Matrix */
 getTF1200Tt4DshMtx(Tt4DshMtx);

/* Gets TF1200Tt4shMtx Matrix */
 getTF1200Tt4shMtx(Tt4shMtx);

/* Gets TF1200Tt6DMtx Matrix */
 getTF1200Tt6DMtx(Tt6DMtx);

/* Gets TF1200Tt6Mtx Matrix */
 getTF1200Tt6Mtx(Tt6Mtx);

/* Gets TF1200WcFANMapMtx Matrix */
 getTF1200WcFANMapMtx(WcFANMapMtx);

/* Gets TF1200WcFANStallMtx Matrix */
 getTF1200WcFANStallMtx(WcFANStallMtx);

/* Gets TF1200WcHPCStallMtx Matrix */
 getTF1200WcHPCStallMtx(WcHPCStallMtx);

/* Gets TF1200WcHPTMapMtx Matrix */
 getTF1200WcHPTMapMtx(WcHPTMapMtx);

/* Gets TF1200WfshMtx Matrix */
 getTF1200WfshMtx(WfshMtx);

/* Gets TF1200NcFANshMtx Matrix */
 getTF1200NcFANshMtx(NcFANshMtx);

/* Gets TF1200WfwmMtx Matrix */
 getTF1200WfwmMtx(WfwmMtx);

/* Gets TF1200Pt3shMtx Matrix */
 getTF1200Pt3shMtx(Pt3shMtx);

/* Gets TF1200Pt3DshMtx Matrix */
 getTF1200Pt3DshMtx(Pt3DshMtx);

/* Gets TF1200Pt21wmMtx Matrix */
 getTF1200Pt21wmMtx(Pt21wmMtx);

/* Gets TF1200Pt21DwmMtx Matrix */
 getTF1200Pt21DwmMtx(Pt21DwmMtx);

/* Gets TF1200Pt3wmMtx Matrix */
 getTF1200Pt3wmMtx(Pt3wmMtx);

/* Gets TF1200Pt3DwmMtx Matrix */
 getTF1200Pt3DwmMtx(Pt3DwmMtx);

/* Gets TF1200Pt5wmMtx Matrix */
 getTF1200Pt5wmMtx(Pt5wmMtx);

/* Gets TF1200Pt5DwmMtx Matrix */
 getTF1200Pt5DwmMtx(Pt5DwmMtx);

/* Gets TF1200Pt6wmMtx Matrix */
 getTF1200Pt6wmMtx(Pt6wmMtx);

/* Gets TF1200Pt6DwmMtx Matrix */
 getTF1200Pt6DwmMtx(Pt6DwmMtx);

/* Gets TF1200Tt21wmMtx Matrix */
 getTF1200Tt21wmMtx(Tt21wmMtx);

/* Gets TF1200Tt21DwmMtx Matrix */
 getTF1200Tt21DwmMtx(Tt21DwmMtx);

/* Gets TF1200Tt3wmMtx Matrix */
 getTF1200Tt3wmMtx(Tt3wmMtx);

/* Gets TF1200Tt3DwmMtx Matrix */
 getTF1200Tt3DwmMtx(Tt3DwmMtx);

/* Gets TF1200Tt4wmMtx Matrix */
 getTF1200Tt4wmMtx(Tt4wmMtx);

/* Gets TF1200Tt4DwmMtx Matrix */
 getTF1200Tt4DwmMtx(Tt4DwmMtx);

/* Gets TF1200Tt5wmMtx Matrix */
 getTF1200Tt5wmMtx(Tt5wmMtx);

/* Gets TF1200Tt5DwmMtx Matrix */
 getTF1200Tt5DwmMtx(Tt5DwmMtx);

/* Gets TF1200Tt6wmMtx Matrix */
 getTF1200Tt6wmMtx(Tt6wmMtx);

/* Gets TF1200Tt6DwmMtx Matrix */
 getTF1200Tt6DwmMtx(Tt6DwmMtx);

/* Gets TF1200Pt21shMtx Matrix */
 getTF1200Pt21shMtx(Pt21shMtx);

/* Gets TF1200Pt21DshMtx Matrix */
 getTF1200Pt21DshMtx(Pt21DshMtx);

/* Gets TF1200Pt5shMtx Matrix */
 getTF1200Pt5shMtx(Pt5shMtx);

/* Gets TF1200Pt5DshMtx Matrix */
 getTF1200Pt5DshMtx(Pt5DshMtx);

/* Gets TF1200Pt6shMtx Matrix */
 getTF1200Pt6shMtx(Pt6shMtx);

/* Gets TF1200Pt6DshMtx Matrix */
 getTF1200Pt6DshMtx(Pt6DshMtx);

/* Gets TF1200Tt21shMtx Matrix */
 getTF1200Tt21shMtx(Tt21shMtx);

/* Gets TF1200Tt21DshMtx Matrix */
 getTF1200Tt21DshMtx(Tt21DshMtx);

/* Gets TF1200Tt3shMtx Matrix */
 getTF1200Tt3shMtx(Tt3shMtx);

/* Gets TF1200Tt3DshMtx Matrix */
 getTF1200Tt3DshMtx(Tt3DshMtx);

/* Gets TF1200Tt5shMtx Matrix */
 getTF1200Tt5shMtx(Tt5shMtx);

/* Gets TF1200Tt5DshMtx Matrix */
 getTF1200Tt5DshMtx(Tt5DshMtx);

/* Gets TF1200Tt6shMtx Matrix */
 getTF1200Tt6shMtx(Tt6shMtx);

/* Gets TF1200Tt6DshMtx Matrix */
 getTF1200Tt6DshMtx(Tt6DshMtx);

}

