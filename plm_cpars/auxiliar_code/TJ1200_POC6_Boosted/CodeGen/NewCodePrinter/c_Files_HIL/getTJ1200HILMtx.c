
#include <math.h>
#include "getTJ1200HIL.h"

void getTJ1200HILMtx(double *AshMtx, double *AwmMtx, double *BshMtx, double *BwmMtx, double *EffFANMapMtx, 
     double *EffHPCMapMtx, double *EffHPTMapMtx, double *NcFANMapMtx, double *NcHPTMapMtx, double *NcMtx, 
     double *PRFANMapMtx, double *PRFANStallMtx, double *PRHPCStallMtx, double *PRHPTMapMtx, double *Pt21DMtx, 
     double *Pt21Mtx, double *Pt6DMtx, double *Pt6Mtx, double *RPMshMtx, double *RPMwmMtx, 
     double *Tt21DMtx, double *Tt21Mtx, double *Tt3DMtx, double *Tt3Mtx, double *Tt4CshMtx, 
     double *Tt4DshMtx, double *Tt4shMtx, double *Tt6DMtx, double *Tt6Mtx, double *WcFANMapMtx, 
     double *WcFANStallMtx, double *WcHPCStallMtx, double *WcHPTMapMtx, double *WfshMtx)



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