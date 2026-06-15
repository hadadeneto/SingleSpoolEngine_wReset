
#include <math.h>
#include "../HIL_get_H/getTJ200HIL.h"

void getTJ200HILMtx(double *AshMtx, double *AwmMtx, double *BshMtx, double *BwmMtx, double *EffFANMapMtx, 
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

/* Gets TJ200AshMtx Matrix */
 getTJ200AshMtx(AshMtx);

/* Gets TJ200AwmMtx Matrix */
 getTJ200AwmMtx(AwmMtx);

/* Gets TJ200BshMtx Matrix */
 getTJ200BshMtx(BshMtx);

/* Gets TJ200BwmMtx Matrix */
 getTJ200BwmMtx(BwmMtx);

/* Gets TJ200EffFANMapMtx Matrix */
 getTJ200EffFANMapMtx(EffFANMapMtx);

/* Gets TJ200EffHPCMapMtx Matrix */
 getTJ200EffHPCMapMtx(EffHPCMapMtx);

/* Gets TJ200EffHPTMapMtx Matrix */
 getTJ200EffHPTMapMtx(EffHPTMapMtx);

/* Gets TJ200NcFANMapMtx Matrix */
 getTJ200NcFANMapMtx(NcFANMapMtx);

/* Gets TJ200NcHPTMapMtx Matrix */
 getTJ200NcHPTMapMtx(NcHPTMapMtx);

/* Gets TJ200NcMtx Matrix */
 getTJ200NcMtx(NcMtx);

/* Gets TJ200PRFANMapMtx Matrix */
 getTJ200PRFANMapMtx(PRFANMapMtx);

/* Gets TJ200PRFANStallMtx Matrix */
 getTJ200PRFANStallMtx(PRFANStallMtx);

/* Gets TJ200PRHPCStallMtx Matrix */
 getTJ200PRHPCStallMtx(PRHPCStallMtx);

/* Gets TJ200PRHPTMapMtx Matrix */
 getTJ200PRHPTMapMtx(PRHPTMapMtx);

/* Gets TJ200Pt21DMtx Matrix */
 getTJ200Pt21DMtx(Pt21DMtx);

/* Gets TJ200Pt21Mtx Matrix */
 getTJ200Pt21Mtx(Pt21Mtx);

/* Gets TJ200Pt6DMtx Matrix */
 getTJ200Pt6DMtx(Pt6DMtx);

/* Gets TJ200Pt6Mtx Matrix */
 getTJ200Pt6Mtx(Pt6Mtx);

/* Gets TJ200RPMshMtx Matrix */
 getTJ200RPMshMtx(RPMshMtx);

/* Gets TJ200RPMwmMtx Matrix */
 getTJ200RPMwmMtx(RPMwmMtx);

/* Gets TJ200Tt21DMtx Matrix */
 getTJ200Tt21DMtx(Tt21DMtx);

/* Gets TJ200Tt21Mtx Matrix */
 getTJ200Tt21Mtx(Tt21Mtx);

/* Gets TJ200Tt3DMtx Matrix */
 getTJ200Tt3DMtx(Tt3DMtx);

/* Gets TJ200Tt3Mtx Matrix */
 getTJ200Tt3Mtx(Tt3Mtx);

/* Gets TJ200Tt4CshMtx Matrix */
 getTJ200Tt4CshMtx(Tt4CshMtx);

/* Gets TJ200Tt4DshMtx Matrix */
 getTJ200Tt4DshMtx(Tt4DshMtx);

/* Gets TJ200Tt4shMtx Matrix */
 getTJ200Tt4shMtx(Tt4shMtx);

/* Gets TJ200Tt6DMtx Matrix */
 getTJ200Tt6DMtx(Tt6DMtx);

/* Gets TJ200Tt6Mtx Matrix */
 getTJ200Tt6Mtx(Tt6Mtx);

/* Gets TJ200WcFANMapMtx Matrix */
 getTJ200WcFANMapMtx(WcFANMapMtx);

/* Gets TJ200WcFANStallMtx Matrix */
 getTJ200WcFANStallMtx(WcFANStallMtx);

/* Gets TJ200WcHPCStallMtx Matrix */
 getTJ200WcHPCStallMtx(WcHPCStallMtx);

/* Gets TJ200WcHPTMapMtx Matrix */
 getTJ200WcHPTMapMtx(WcHPTMapMtx);

/* Gets TJ200WfshMtx Matrix */
 getTJ200WfshMtx(WfshMtx);

/* Gets TJ200NcFANshMtx Matrix */
 getTJ200NcFANshMtx(NcFANshMtx);

/* Gets TJ200WfwmMtx Matrix */
 getTJ200WfwmMtx(WfwmMtx);

/* Gets TJ200Pt3shMtx Matrix */
 getTJ200Pt3shMtx(Pt3shMtx);

/* Gets TJ200Pt3DshMtx Matrix */
 getTJ200Pt3DshMtx(Pt3DshMtx);

/* Gets TJ200Pt21wmMtx Matrix */
 getTJ200Pt21wmMtx(Pt21wmMtx);

/* Gets TJ200Pt21DwmMtx Matrix */
 getTJ200Pt21DwmMtx(Pt21DwmMtx);

/* Gets TJ200Pt3wmMtx Matrix */
 getTJ200Pt3wmMtx(Pt3wmMtx);

/* Gets TJ200Pt3DwmMtx Matrix */
 getTJ200Pt3DwmMtx(Pt3DwmMtx);

/* Gets TJ200Pt5wmMtx Matrix */
 getTJ200Pt5wmMtx(Pt5wmMtx);

/* Gets TJ200Pt5DwmMtx Matrix */
 getTJ200Pt5DwmMtx(Pt5DwmMtx);

/* Gets TJ200Pt6wmMtx Matrix */
 getTJ200Pt6wmMtx(Pt6wmMtx);

/* Gets TJ200Pt6DwmMtx Matrix */
 getTJ200Pt6DwmMtx(Pt6DwmMtx);

/* Gets TJ200Tt21wmMtx Matrix */
 getTJ200Tt21wmMtx(Tt21wmMtx);

/* Gets TJ200Tt21DwmMtx Matrix */
 getTJ200Tt21DwmMtx(Tt21DwmMtx);

/* Gets TJ200Tt3wmMtx Matrix */
 getTJ200Tt3wmMtx(Tt3wmMtx);

/* Gets TJ200Tt3DwmMtx Matrix */
 getTJ200Tt3DwmMtx(Tt3DwmMtx);

/* Gets TJ200Tt4wmMtx Matrix */
 getTJ200Tt4wmMtx(Tt4wmMtx);

/* Gets TJ200Tt4DwmMtx Matrix */
 getTJ200Tt4DwmMtx(Tt4DwmMtx);

/* Gets TJ200Tt5wmMtx Matrix */
 getTJ200Tt5wmMtx(Tt5wmMtx);

/* Gets TJ200Tt5DwmMtx Matrix */
 getTJ200Tt5DwmMtx(Tt5DwmMtx);

/* Gets TJ200Tt6wmMtx Matrix */
 getTJ200Tt6wmMtx(Tt6wmMtx);

/* Gets TJ200Tt6DwmMtx Matrix */
 getTJ200Tt6DwmMtx(Tt6DwmMtx);

/* Gets TJ200Pt21shMtx Matrix */
 getTJ200Pt21shMtx(Pt21shMtx);

/* Gets TJ200Pt21DshMtx Matrix */
 getTJ200Pt21DshMtx(Pt21DshMtx);

/* Gets TJ200Pt5shMtx Matrix */
 getTJ200Pt5shMtx(Pt5shMtx);

/* Gets TJ200Pt5DshMtx Matrix */
 getTJ200Pt5DshMtx(Pt5DshMtx);

/* Gets TJ200Pt6shMtx Matrix */
 getTJ200Pt6shMtx(Pt6shMtx);

/* Gets TJ200Pt6DshMtx Matrix */
 getTJ200Pt6DshMtx(Pt6DshMtx);

/* Gets TJ200Tt21shMtx Matrix */
 getTJ200Tt21shMtx(Tt21shMtx);

/* Gets TJ200Tt21DshMtx Matrix */
 getTJ200Tt21DshMtx(Tt21DshMtx);

/* Gets TJ200Tt3shMtx Matrix */
 getTJ200Tt3shMtx(Tt3shMtx);

/* Gets TJ200Tt3DshMtx Matrix */
 getTJ200Tt3DshMtx(Tt3DshMtx);

/* Gets TJ200Tt5shMtx Matrix */
 getTJ200Tt5shMtx(Tt5shMtx);

/* Gets TJ200Tt5DshMtx Matrix */
 getTJ200Tt5DshMtx(Tt5DshMtx);

/* Gets TJ200Tt6shMtx Matrix */
 getTJ200Tt6shMtx(Tt6shMtx);

/* Gets TJ200Tt6DshMtx Matrix */
 getTJ200Tt6DshMtx(Tt6DshMtx);

}

