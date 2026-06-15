
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../HIL_get_H/getTJ1200HIL.h"

void getTJ1200HILMtx(double *AshMtx, double *AwmMtx, double *BshMtx, double *BwmMtx, double *EffFANMapMtx, 
     double *EffHPCMapMtx, double *EffHPTMapMtx, double *NcFANMapMtx, double *NcHPTMapMtx, double *NcMtx, 
     double *PRFANMapMtx, double *PRFANStallMtx, double *PRHPCStallMtx, double *PRHPTMapMtx, double *Pt21DMtx, 
     double *Pt21Mtx, double *Pt6DMtx, double *Pt6Mtx, double *RPMshMtx, double *RPMwmMtx, 
     double *Tt21DMtx, double *Tt21Mtx, double *Tt3DMtx, double *Tt3Mtx, double *Tt4CshMtx, 
     double *Tt4DshMtx, double *Tt4shMtx, double *Tt6DMtx, double *Tt6Mtx, double *WcFANMapMtx, 
     double *WcFANStallMtx, double *WcHPCStallMtx, double *WcHPTMapMtx, double *WfshMtx, double *NcFANshMtx, 
     double *WfwmMtx, double *Pt3shMtx, double *Pt3DshMtx, double *Pt21wmMtx, double *Pt21DwmMtx, 
     double *Pt3wmMtx, double *Pt3DwmMtx, double *Pt5wmMtx, double *Pt5DwmMtx, double *Pt6wmMtx, 
     double *Pt6DwmMtx, double *Tt21wmMtx, double *Tt21DwmMtx, double *Tt3wmMtx, double *Tt3DwmMtx, 
     double *Tt4wmMtx, double *Tt4DwmMtx, double *Tt5wmMtx, double *Tt5DwmMtx, double *Tt6wmMtx, 
     double *Tt6DwmMtx, double *Pt21shMtx, double *Pt21DshMtx, double *Pt5shMtx, double *Pt5DshMtx, 
     double *Pt6shMtx, double *Pt6DshMtx, double *Tt21shMtx, double *Tt21DshMtx, double *Tt3shMtx, 
     double *Tt3DshMtx, double *Tt5shMtx, double *Tt5DshMtx, double *Tt6shMtx, double *Tt6DshMtx)

{

/* Gets TJ1200AshMtx Matrix */
 getTJ1200AshMtx(AshMtx);

/* Gets TJ1200AwmMtx Matrix */
 getTJ1200AwmMtx(AwmMtx);

/* Gets TJ1200BshMtx Matrix */
 getTJ1200BshMtx(BshMtx);

/* Gets TJ1200BwmMtx Matrix */
 getTJ1200BwmMtx(BwmMtx);

/* Gets TJ1200EffFANMapMtx Matrix */
 getTJ1200EffFANMapMtx(EffFANMapMtx);

/* Gets TJ1200EffHPCMapMtx Matrix */
 getTJ1200EffHPCMapMtx(EffHPCMapMtx);

/* Gets TJ1200EffHPTMapMtx Matrix */
 getTJ1200EffHPTMapMtx(EffHPTMapMtx);

/* Gets TJ1200NcFANMapMtx Matrix */
 getTJ1200NcFANMapMtx(NcFANMapMtx);

/* Gets TJ1200NcHPTMapMtx Matrix */
 getTJ1200NcHPTMapMtx(NcHPTMapMtx);

/* Gets TJ1200NcMtx Matrix */
 getTJ1200NcMtx(NcMtx);

/* Gets TJ1200PRFANMapMtx Matrix */
 getTJ1200PRFANMapMtx(PRFANMapMtx);

/* Gets TJ1200PRFANStallMtx Matrix */
 getTJ1200PRFANStallMtx(PRFANStallMtx);

/* Gets TJ1200PRHPCStallMtx Matrix */
 getTJ1200PRHPCStallMtx(PRHPCStallMtx);

/* Gets TJ1200PRHPTMapMtx Matrix */
 getTJ1200PRHPTMapMtx(PRHPTMapMtx);

/* Gets TJ1200Pt21DMtx Matrix */
 getTJ1200Pt21DMtx(Pt21DMtx);

/* Gets TJ1200Pt21Mtx Matrix */
 getTJ1200Pt21Mtx(Pt21Mtx);

/* Gets TJ1200Pt6DMtx Matrix */
 getTJ1200Pt6DMtx(Pt6DMtx);

/* Gets TJ1200Pt6Mtx Matrix */
 getTJ1200Pt6Mtx(Pt6Mtx);

/* Gets TJ1200RPMshMtx Matrix */
 getTJ1200RPMshMtx(RPMshMtx);

/* Gets TJ1200RPMwmMtx Matrix */
 getTJ1200RPMwmMtx(RPMwmMtx);

/* Gets TJ1200Tt21DMtx Matrix */
 getTJ1200Tt21DMtx(Tt21DMtx);

/* Gets TJ1200Tt21Mtx Matrix */
 getTJ1200Tt21Mtx(Tt21Mtx);

/* Gets TJ1200Tt3DMtx Matrix */
 getTJ1200Tt3DMtx(Tt3DMtx);

/* Gets TJ1200Tt3Mtx Matrix */
 getTJ1200Tt3Mtx(Tt3Mtx);

/* Gets TJ1200Tt4CshMtx Matrix */
 getTJ1200Tt4CshMtx(Tt4CshMtx);

/* Gets TJ1200Tt4DshMtx Matrix */
 getTJ1200Tt4DshMtx(Tt4DshMtx);

/* Gets TJ1200Tt4shMtx Matrix */
 getTJ1200Tt4shMtx(Tt4shMtx);

/* Gets TJ1200Tt6DMtx Matrix */
 getTJ1200Tt6DMtx(Tt6DMtx);

/* Gets TJ1200Tt6Mtx Matrix */
 getTJ1200Tt6Mtx(Tt6Mtx);

/* Gets TJ1200WcFANMapMtx Matrix */
 getTJ1200WcFANMapMtx(WcFANMapMtx);

/* Gets TJ1200WcFANStallMtx Matrix */
 getTJ1200WcFANStallMtx(WcFANStallMtx);

/* Gets TJ1200WcHPCStallMtx Matrix */
 getTJ1200WcHPCStallMtx(WcHPCStallMtx);

/* Gets TJ1200WcHPTMapMtx Matrix */
 getTJ1200WcHPTMapMtx(WcHPTMapMtx);

/* Gets TJ1200WfshMtx Matrix */
 getTJ1200WfshMtx(WfshMtx);

/* Gets TJ1200NcFANshMtx Matrix */
 getTJ1200NcFANshMtx(NcFANshMtx);

/* Gets TJ1200WfwmMtx Matrix */
 getTJ1200WfwmMtx(WfwmMtx);

/* Gets TJ1200Pt3shMtx Matrix */
 getTJ1200Pt3shMtx(Pt3shMtx);

/* Gets TJ1200Pt3DshMtx Matrix */
 getTJ1200Pt3DshMtx(Pt3DshMtx);

/* Gets TJ1200Pt21wmMtx Matrix */
 getTJ1200Pt21wmMtx(Pt21wmMtx);

/* Gets TJ1200Pt21DwmMtx Matrix */
 getTJ1200Pt21DwmMtx(Pt21DwmMtx);

/* Gets TJ1200Pt3wmMtx Matrix */
 getTJ1200Pt3wmMtx(Pt3wmMtx);

/* Gets TJ1200Pt3DwmMtx Matrix */
 getTJ1200Pt3DwmMtx(Pt3DwmMtx);

/* Gets TJ1200Pt5wmMtx Matrix */
 getTJ1200Pt5wmMtx(Pt5wmMtx);

/* Gets TJ1200Pt5DwmMtx Matrix */
 getTJ1200Pt5DwmMtx(Pt5DwmMtx);

/* Gets TJ1200Pt6wmMtx Matrix */
 getTJ1200Pt6wmMtx(Pt6wmMtx);

/* Gets TJ1200Pt6DwmMtx Matrix */
 getTJ1200Pt6DwmMtx(Pt6DwmMtx);

/* Gets TJ1200Tt21wmMtx Matrix */
 getTJ1200Tt21wmMtx(Tt21wmMtx);

/* Gets TJ1200Tt21DwmMtx Matrix */
 getTJ1200Tt21DwmMtx(Tt21DwmMtx);

/* Gets TJ1200Tt3wmMtx Matrix */
 getTJ1200Tt3wmMtx(Tt3wmMtx);

/* Gets TJ1200Tt3DwmMtx Matrix */
 getTJ1200Tt3DwmMtx(Tt3DwmMtx);

/* Gets TJ1200Tt4wmMtx Matrix */
 getTJ1200Tt4wmMtx(Tt4wmMtx);

/* Gets TJ1200Tt4DwmMtx Matrix */
 getTJ1200Tt4DwmMtx(Tt4DwmMtx);

/* Gets TJ1200Tt5wmMtx Matrix */
 getTJ1200Tt5wmMtx(Tt5wmMtx);

/* Gets TJ1200Tt5DwmMtx Matrix */
 getTJ1200Tt5DwmMtx(Tt5DwmMtx);

/* Gets TJ1200Tt6wmMtx Matrix */
 getTJ1200Tt6wmMtx(Tt6wmMtx);

/* Gets TJ1200Tt6DwmMtx Matrix */
 getTJ1200Tt6DwmMtx(Tt6DwmMtx);

/* Gets TJ1200Pt21shMtx Matrix */
 getTJ1200Pt21shMtx(Pt21shMtx);

/* Gets TJ1200Pt21DshMtx Matrix */
 getTJ1200Pt21DshMtx(Pt21DshMtx);

/* Gets TJ1200Pt5shMtx Matrix */
 getTJ1200Pt5shMtx(Pt5shMtx);

/* Gets TJ1200Pt5DshMtx Matrix */
 getTJ1200Pt5DshMtx(Pt5DshMtx);

/* Gets TJ1200Pt6shMtx Matrix */
 getTJ1200Pt6shMtx(Pt6shMtx);

/* Gets TJ1200Pt6DshMtx Matrix */
 getTJ1200Pt6DshMtx(Pt6DshMtx);

/* Gets TJ1200Tt21shMtx Matrix */
 getTJ1200Tt21shMtx(Tt21shMtx);

/* Gets TJ1200Tt21DshMtx Matrix */
 getTJ1200Tt21DshMtx(Tt21DshMtx);

/* Gets TJ1200Tt3shMtx Matrix */
 getTJ1200Tt3shMtx(Tt3shMtx);

/* Gets TJ1200Tt3DshMtx Matrix */
 getTJ1200Tt3DshMtx(Tt3DshMtx);

/* Gets TJ1200Tt5shMtx Matrix */
 getTJ1200Tt5shMtx(Tt5shMtx);

/* Gets TJ1200Tt5DshMtx Matrix */
 getTJ1200Tt5DshMtx(Tt5DshMtx);

/* Gets TJ1200Tt6shMtx Matrix */
 getTJ1200Tt6shMtx(Tt6shMtx);

/* Gets TJ1200Tt6DshMtx Matrix */
 getTJ1200Tt6DshMtx(Tt6DshMtx);

}

