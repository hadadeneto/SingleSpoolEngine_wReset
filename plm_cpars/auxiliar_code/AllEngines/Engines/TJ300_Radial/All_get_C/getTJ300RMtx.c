
#include <math.h>
#include "getTJ300RMtxFunctions.h"

getTJ300RMtx(floating *NcFANContMtx, floating *N_KpMtx, floating *N_KiMtx, floating *FNperContMtx, floating *FNcMaxContMtx, 
     floating *NcMtx, floating *Pt21Mtx, floating *Pt3Mtx, floating *Pt5Mtx, floating *Pt6Mtx, 
     floating *Tt21Mtx, floating *Tt3Mtx, floating *Tt4Mtx, floating *Tt5Mtx, floating *Tt6Mtx, 
     floating *WfMtx, floating *AMtx, floating *BMtx, floating *Pt21DMtx, floating *Pt3DMtx, 
     floating *Pt5DMtx, floating *Pt6DMtx, floating *Tt21DMtx, floating *Tt3DMtx, floating *Tt4DMtx, 
     floating *Tt5DMtx, floating *Tt6DMtx, floating *NcFANMapMtx, floating *WcFANMapMtx, floating *WcFANStallMtx, 
     floating *PRFANMapMtx, floating *PRFANStallMtx, floating *EffFANMapMtx, floating *NcHPTMapMtx, floating *WcHPTMapMtx, 
     floating *PRHPTMapMtx, floating *EffHPTMapMtx, floating *NcHPCMapMtx, floating *WcHPCMapMtx, floating *WcHPCStallMtx, 
     floating *PRHPCMapMtx, floating *PRHPCStallMtx, floating *EffHPCMapMtx, floating *MNLinVec, floating *AltLinVec, 
     floating *DeltaMtx, floating *Ts0Mtx, floating *AwmMtx, floating *AshMtx, floating *BwmMtx, 
     floating *BshMtx, floating *RPMwmMtx, floating *RPMshMtx, floating *Tt4CshMtx, floating *Tt4DshMtx, 
     floating *Tt4shMtx, floating *WfshMtx, floating *ASVec, floating *DSVec, floating *NcVec, 
     floating *NcFANshMtx, floating *WfwmMtx, floating *Pt3shMtx, floating *Pt3DshMtx, floating *Pt21wmMtx, 
     floating *Pt21DwmMtx, floating *Pt3wmMtx, floating *Pt3DwmMtx, floating *Pt5wmMtx, floating *Pt5DwmMtx, 
     floating *Pt6wmMtx, floating *Pt6DwmMtx, floating *Tt21wmMtx, floating *Tt21DwmMtx, floating *Tt3wmMtx, 
     floating *Tt3DwmMtx, floating *Tt4wmMtx, floating *Tt4DwmMtx, floating *Tt5wmMtx, floating *Tt5DwmMtx, 
     floating *Tt6wmMtx, floating *Tt6DwmMtx, floating *Pt21shMtx, floating *Pt21DshMtx, floating *Pt5shMtx, 
     floating *Pt5DshMtx, floating *Pt6shMtx, floating *Pt6DshMtx, floating *Tt21shMtx, floating *Tt21DshMtx, 
     floating *Tt3shMtx, floating *Tt3DshMtx, floating *Tt5shMtx, floating *Tt5DshMtx, floating *Tt6shMtx, 
     floating *Tt6DshMtx)



/* Gets TJ300RNcFANContMtx Matrix */
 getTJ300RNcFANContMtx(NcFANContMtx);

/* Gets TJ300RN_KpMtx Matrix */
 getTJ300RN_KpMtx(N_KpMtx);

/* Gets TJ300RN_KiMtx Matrix */
 getTJ300RN_KiMtx(N_KiMtx);

/* Gets TJ300RFNperContMtx Matrix */
 getTJ300RFNperContMtx(FNperContMtx);

/* Gets TJ300RFNcMaxContMtx Matrix */
 getTJ300RFNcMaxContMtx(FNcMaxContMtx);

/* Gets TJ300RNcMtx Matrix */
 getTJ300RNcMtx(NcMtx);

/* Gets TJ300RPt21Mtx Matrix */
 getTJ300RPt21Mtx(Pt21Mtx);

/* Gets TJ300RPt3Mtx Matrix */
 getTJ300RPt3Mtx(Pt3Mtx);

/* Gets TJ300RPt5Mtx Matrix */
 getTJ300RPt5Mtx(Pt5Mtx);

/* Gets TJ300RPt6Mtx Matrix */
 getTJ300RPt6Mtx(Pt6Mtx);

/* Gets TJ300RTt21Mtx Matrix */
 getTJ300RTt21Mtx(Tt21Mtx);

/* Gets TJ300RTt3Mtx Matrix */
 getTJ300RTt3Mtx(Tt3Mtx);

/* Gets TJ300RTt4Mtx Matrix */
 getTJ300RTt4Mtx(Tt4Mtx);

/* Gets TJ300RTt5Mtx Matrix */
 getTJ300RTt5Mtx(Tt5Mtx);

/* Gets TJ300RTt6Mtx Matrix */
 getTJ300RTt6Mtx(Tt6Mtx);

/* Gets TJ300RWfMtx Matrix */
 getTJ300RWfMtx(WfMtx);

/* Gets TJ300RAMtx Matrix */
 getTJ300RAMtx(AMtx);

/* Gets TJ300RBMtx Matrix */
 getTJ300RBMtx(BMtx);

/* Gets TJ300RPt21DMtx Matrix */
 getTJ300RPt21DMtx(Pt21DMtx);

/* Gets TJ300RPt3DMtx Matrix */
 getTJ300RPt3DMtx(Pt3DMtx);

/* Gets TJ300RPt5DMtx Matrix */
 getTJ300RPt5DMtx(Pt5DMtx);

/* Gets TJ300RPt6DMtx Matrix */
 getTJ300RPt6DMtx(Pt6DMtx);

/* Gets TJ300RTt21DMtx Matrix */
 getTJ300RTt21DMtx(Tt21DMtx);

/* Gets TJ300RTt3DMtx Matrix */
 getTJ300RTt3DMtx(Tt3DMtx);

/* Gets TJ300RTt4DMtx Matrix */
 getTJ300RTt4DMtx(Tt4DMtx);

/* Gets TJ300RTt5DMtx Matrix */
 getTJ300RTt5DMtx(Tt5DMtx);

/* Gets TJ300RTt6DMtx Matrix */
 getTJ300RTt6DMtx(Tt6DMtx);

/* Gets TJ300RNcFANMapMtx Matrix */
 getTJ300RNcFANMapMtx(NcFANMapMtx);

/* Gets TJ300RWcFANMapMtx Matrix */
 getTJ300RWcFANMapMtx(WcFANMapMtx);

/* Gets TJ300RWcFANStallMtx Matrix */
 getTJ300RWcFANStallMtx(WcFANStallMtx);

/* Gets TJ300RPRFANMapMtx Matrix */
 getTJ300RPRFANMapMtx(PRFANMapMtx);

/* Gets TJ300RPRFANStallMtx Matrix */
 getTJ300RPRFANStallMtx(PRFANStallMtx);

/* Gets TJ300REffFANMapMtx Matrix */
 getTJ300REffFANMapMtx(EffFANMapMtx);

/* Gets TJ300RNcHPTMapMtx Matrix */
 getTJ300RNcHPTMapMtx(NcHPTMapMtx);

/* Gets TJ300RWcHPTMapMtx Matrix */
 getTJ300RWcHPTMapMtx(WcHPTMapMtx);

/* Gets TJ300RPRHPTMapMtx Matrix */
 getTJ300RPRHPTMapMtx(PRHPTMapMtx);

/* Gets TJ300REffHPTMapMtx Matrix */
 getTJ300REffHPTMapMtx(EffHPTMapMtx);

/* Gets TJ300RNcHPCMapMtx Matrix */
 getTJ300RNcHPCMapMtx(NcHPCMapMtx);

/* Gets TJ300RWcHPCMapMtx Matrix */
 getTJ300RWcHPCMapMtx(WcHPCMapMtx);

/* Gets TJ300RWcHPCStallMtx Matrix */
 getTJ300RWcHPCStallMtx(WcHPCStallMtx);

/* Gets TJ300RPRHPCMapMtx Matrix */
 getTJ300RPRHPCMapMtx(PRHPCMapMtx);

/* Gets TJ300RPRHPCStallMtx Matrix */
 getTJ300RPRHPCStallMtx(PRHPCStallMtx);

/* Gets TJ300REffHPCMapMtx Matrix */
 getTJ300REffHPCMapMtx(EffHPCMapMtx);

/* Gets TJ300RMNLinVec Matrix */
 getTJ300RMNLinVec(MNLinVec);

/* Gets TJ300RAltLinVec Matrix */
 getTJ300RAltLinVec(AltLinVec);

/* Gets TJ300RDeltaMtx Matrix */
 getTJ300RDeltaMtx(DeltaMtx);

/* Gets TJ300RTs0Mtx Matrix */
 getTJ300RTs0Mtx(Ts0Mtx);

/* Gets TJ300RAwmMtx Matrix */
 getTJ300RAwmMtx(AwmMtx);

/* Gets TJ300RAshMtx Matrix */
 getTJ300RAshMtx(AshMtx);

/* Gets TJ300RBwmMtx Matrix */
 getTJ300RBwmMtx(BwmMtx);

/* Gets TJ300RBshMtx Matrix */
 getTJ300RBshMtx(BshMtx);

/* Gets TJ300RRPMwmMtx Matrix */
 getTJ300RRPMwmMtx(RPMwmMtx);

/* Gets TJ300RRPMshMtx Matrix */
 getTJ300RRPMshMtx(RPMshMtx);

/* Gets TJ300RTt4CshMtx Matrix */
 getTJ300RTt4CshMtx(Tt4CshMtx);

/* Gets TJ300RTt4DshMtx Matrix */
 getTJ300RTt4DshMtx(Tt4DshMtx);

/* Gets TJ300RTt4shMtx Matrix */
 getTJ300RTt4shMtx(Tt4shMtx);

/* Gets TJ300RWfshMtx Matrix */
 getTJ300RWfshMtx(WfshMtx);

/* Gets TJ300RASVec Matrix */
 getTJ300RASVec(ASVec);

/* Gets TJ300RDSVec Matrix */
 getTJ300RDSVec(DSVec);

/* Gets TJ300RNcVec Matrix */
 getTJ300RNcVec(NcVec);

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