
#include <math.h>
#include "../HIL_get_H/getTF1200HIL.h"

void getTF1200HILMtx(double *AshMtx, double *AwmMtx, double *BshMtx, double *BwmMtx, double *EffFANMapMtx, 
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

