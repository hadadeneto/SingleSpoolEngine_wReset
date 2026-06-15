
#include <math.h>
#include "../HIL_get_H/getTJ700HIL.h"

void getTJ700HILMtx(double *AshMtx, double *AwmMtx, double *BshMtx, double *BwmMtx, double *EffFANMapMtx, 
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

