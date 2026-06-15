
#include <math.h>
#include "../HIL_get_H/getGEJ85HIL.h"

void getGEJ85HILMtx(double *AshMtx, double *AwmMtx, double *BshMtx, double *BwmMtx, double *EffFANMapMtx, 
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

