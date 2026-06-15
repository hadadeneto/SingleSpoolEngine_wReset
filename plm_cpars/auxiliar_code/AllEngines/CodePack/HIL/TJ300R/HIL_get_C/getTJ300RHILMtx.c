
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../HIL_get_H/getTJ300RHIL.h"

void getTJ300RHILMtx(floating *AshMtx, floating *AwmMtx, floating *BshMtx, floating *BwmMtx, floating *EffFANMapMtx, 
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

/* Gets TJ300RAshMtx Matrix */
 getTJ300RAshMtx(AshMtx);

/* Gets TJ300RAwmMtx Matrix */
 getTJ300RAwmMtx(AwmMtx);

/* Gets TJ300RBshMtx Matrix */
 getTJ300RBshMtx(BshMtx);

/* Gets TJ300RBwmMtx Matrix */
 getTJ300RBwmMtx(BwmMtx);

/* Gets TJ300REffFANMapMtx Matrix */
 getTJ300REffFANMapMtx(EffFANMapMtx);

/* Gets TJ300REffHPCMapMtx Matrix */
 getTJ300REffHPCMapMtx(EffHPCMapMtx);

/* Gets TJ300REffHPTMapMtx Matrix */
 getTJ300REffHPTMapMtx(EffHPTMapMtx);

/* Gets TJ300RNcFANMapMtx Matrix */
 getTJ300RNcFANMapMtx(NcFANMapMtx);

/* Gets TJ300RNcHPTMapMtx Matrix */
 getTJ300RNcHPTMapMtx(NcHPTMapMtx);

/* Gets TJ300RNcMtx Matrix */
 getTJ300RNcMtx(NcMtx);

/* Gets TJ300RPRFANMapMtx Matrix */
 getTJ300RPRFANMapMtx(PRFANMapMtx);

/* Gets TJ300RPRFANStallMtx Matrix */
 getTJ300RPRFANStallMtx(PRFANStallMtx);

/* Gets TJ300RPRHPCStallMtx Matrix */
 getTJ300RPRHPCStallMtx(PRHPCStallMtx);

/* Gets TJ300RPRHPTMapMtx Matrix */
 getTJ300RPRHPTMapMtx(PRHPTMapMtx);

/* Gets TJ300RPt21DMtx Matrix */
 getTJ300RPt21DMtx(Pt21DMtx);

/* Gets TJ300RPt21Mtx Matrix */
 getTJ300RPt21Mtx(Pt21Mtx);

/* Gets TJ300RPt6DMtx Matrix */
 getTJ300RPt6DMtx(Pt6DMtx);

/* Gets TJ300RPt6Mtx Matrix */
 getTJ300RPt6Mtx(Pt6Mtx);

/* Gets TJ300RRPMshMtx Matrix */
 getTJ300RRPMshMtx(RPMshMtx);

/* Gets TJ300RRPMwmMtx Matrix */
 getTJ300RRPMwmMtx(RPMwmMtx);

/* Gets TJ300RTt21DMtx Matrix */
 getTJ300RTt21DMtx(Tt21DMtx);

/* Gets TJ300RTt21Mtx Matrix */
 getTJ300RTt21Mtx(Tt21Mtx);

/* Gets TJ300RTt3DMtx Matrix */
 getTJ300RTt3DMtx(Tt3DMtx);

/* Gets TJ300RTt3Mtx Matrix */
 getTJ300RTt3Mtx(Tt3Mtx);

/* Gets TJ300RTt4CshMtx Matrix */
 getTJ300RTt4CshMtx(Tt4CshMtx);

/* Gets TJ300RTt4DshMtx Matrix */
 getTJ300RTt4DshMtx(Tt4DshMtx);

/* Gets TJ300RTt4shMtx Matrix */
 getTJ300RTt4shMtx(Tt4shMtx);

/* Gets TJ300RTt6DMtx Matrix */
 getTJ300RTt6DMtx(Tt6DMtx);

/* Gets TJ300RTt6Mtx Matrix */
 getTJ300RTt6Mtx(Tt6Mtx);

/* Gets TJ300RWcFANMapMtx Matrix */
 getTJ300RWcFANMapMtx(WcFANMapMtx);

/* Gets TJ300RWcFANStallMtx Matrix */
 getTJ300RWcFANStallMtx(WcFANStallMtx);

/* Gets TJ300RWcHPCStallMtx Matrix */
 getTJ300RWcHPCStallMtx(WcHPCStallMtx);

/* Gets TJ300RWcHPTMapMtx Matrix */
 getTJ300RWcHPTMapMtx(WcHPTMapMtx);

/* Gets TJ300RWfshMtx Matrix */
 getTJ300RWfshMtx(WfshMtx);

/* Gets TJ300RNcFANshMtx Matrix */
 getTJ300RNcFANshMtx(NcFANshMtx);

/* Gets TJ300RWfwmMtx Matrix */
 getTJ300RWfwmMtx(WfwmMtx);

/* Gets TJ300RPt3shMtx Matrix */
 getTJ300RPt3shMtx(Pt3shMtx);

/* Gets TJ300RPt3DshMtx Matrix */
 getTJ300RPt3DshMtx(Pt3DshMtx);

/* Gets TJ300RPt21wmMtx Matrix */
 getTJ300RPt21wmMtx(Pt21wmMtx);

/* Gets TJ300RPt21DwmMtx Matrix */
 getTJ300RPt21DwmMtx(Pt21DwmMtx);

/* Gets TJ300RPt3wmMtx Matrix */
 getTJ300RPt3wmMtx(Pt3wmMtx);

/* Gets TJ300RPt3DwmMtx Matrix */
 getTJ300RPt3DwmMtx(Pt3DwmMtx);

/* Gets TJ300RPt5wmMtx Matrix */
 getTJ300RPt5wmMtx(Pt5wmMtx);

/* Gets TJ300RPt5DwmMtx Matrix */
 getTJ300RPt5DwmMtx(Pt5DwmMtx);

/* Gets TJ300RPt6wmMtx Matrix */
 getTJ300RPt6wmMtx(Pt6wmMtx);

/* Gets TJ300RPt6DwmMtx Matrix */
 getTJ300RPt6DwmMtx(Pt6DwmMtx);

/* Gets TJ300RTt21wmMtx Matrix */
 getTJ300RTt21wmMtx(Tt21wmMtx);

/* Gets TJ300RTt21DwmMtx Matrix */
 getTJ300RTt21DwmMtx(Tt21DwmMtx);

/* Gets TJ300RTt3wmMtx Matrix */
 getTJ300RTt3wmMtx(Tt3wmMtx);

/* Gets TJ300RTt3DwmMtx Matrix */
 getTJ300RTt3DwmMtx(Tt3DwmMtx);

/* Gets TJ300RTt4wmMtx Matrix */
 getTJ300RTt4wmMtx(Tt4wmMtx);

/* Gets TJ300RTt4DwmMtx Matrix */
 getTJ300RTt4DwmMtx(Tt4DwmMtx);

/* Gets TJ300RTt5wmMtx Matrix */
 getTJ300RTt5wmMtx(Tt5wmMtx);

/* Gets TJ300RTt5DwmMtx Matrix */
 getTJ300RTt5DwmMtx(Tt5DwmMtx);

/* Gets TJ300RTt6wmMtx Matrix */
 getTJ300RTt6wmMtx(Tt6wmMtx);

/* Gets TJ300RTt6DwmMtx Matrix */
 getTJ300RTt6DwmMtx(Tt6DwmMtx);

/* Gets TJ300RPt21shMtx Matrix */
 getTJ300RPt21shMtx(Pt21shMtx);

/* Gets TJ300RPt21DshMtx Matrix */
 getTJ300RPt21DshMtx(Pt21DshMtx);

/* Gets TJ300RPt5shMtx Matrix */
 getTJ300RPt5shMtx(Pt5shMtx);

/* Gets TJ300RPt5DshMtx Matrix */
 getTJ300RPt5DshMtx(Pt5DshMtx);

/* Gets TJ300RPt6shMtx Matrix */
 getTJ300RPt6shMtx(Pt6shMtx);

/* Gets TJ300RPt6DshMtx Matrix */
 getTJ300RPt6DshMtx(Pt6DshMtx);

/* Gets TJ300RTt21shMtx Matrix */
 getTJ300RTt21shMtx(Tt21shMtx);

/* Gets TJ300RTt21DshMtx Matrix */
 getTJ300RTt21DshMtx(Tt21DshMtx);

/* Gets TJ300RTt3shMtx Matrix */
 getTJ300RTt3shMtx(Tt3shMtx);

/* Gets TJ300RTt3DshMtx Matrix */
 getTJ300RTt3DshMtx(Tt3DshMtx);

/* Gets TJ300RTt5shMtx Matrix */
 getTJ300RTt5shMtx(Tt5shMtx);

/* Gets TJ300RTt5DshMtx Matrix */
 getTJ300RTt5DshMtx(Tt5DshMtx);

/* Gets TJ300RTt6shMtx Matrix */
 getTJ300RTt6shMtx(Tt6shMtx);

/* Gets TJ300RTt6DshMtx Matrix */
 getTJ300RTt6DshMtx(Tt6DshMtx);

}

