
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../FADEC_get_H/getTJ300RFADEC.h"

void getTJ300RFADECMtx(floating *AMtx, floating *ASVec, floating *AltLinVec, floating *BMtx, floating *DSVec, 
     floating *DeltaMtx, floating *FNcMaxContMtx, floating *FNperContMtx, floating *MNLinVec, floating *N_KiMtx, 
     floating *N_KpMtx, floating *NcFANContMtx, floating *NcHPCMapMtx, floating *NcVec, floating *PRHPCMapMtx, 
     floating *Pt3DMtx, floating *Pt3Mtx, floating *Pt5DMtx, floating *Pt5Mtx, floating *Ts0Mtx, 
     floating *Tt4DMtx, floating *Tt4Mtx, floating *Tt5DMtx, floating *Tt5Mtx, floating *WcHPCMapMtx, 
     floating *WfMtx, floating *N_KpshMtx, floating *N_KishMtx, floating *NcFANshContMtx)

{

/* Gets TJ300RAMtx Matrix */
 getTJ300RAMtx(AMtx);

/* Gets TJ300RASVec Matrix */
 getTJ300RASVec(ASVec);

/* Gets TJ300RAltLinVec Matrix */
 getTJ300RAltLinVec(AltLinVec);

/* Gets TJ300RBMtx Matrix */
 getTJ300RBMtx(BMtx);

/* Gets TJ300RDSVec Matrix */
 getTJ300RDSVec(DSVec);

/* Gets TJ300RDeltaMtx Matrix */
 getTJ300RDeltaMtx(DeltaMtx);

/* Gets TJ300RFNcMaxContMtx Matrix */
 getTJ300RFNcMaxContMtx(FNcMaxContMtx);

/* Gets TJ300RFNperContMtx Matrix */
 getTJ300RFNperContMtx(FNperContMtx);

/* Gets TJ300RMNLinVec Matrix */
 getTJ300RMNLinVec(MNLinVec);

/* Gets TJ300RN_KiMtx Matrix */
 getTJ300RN_KiMtx(N_KiMtx);

/* Gets TJ300RN_KpMtx Matrix */
 getTJ300RN_KpMtx(N_KpMtx);

/* Gets TJ300RNcFANContMtx Matrix */
 getTJ300RNcFANContMtx(NcFANContMtx);

/* Gets TJ300RNcHPCMapMtx Matrix */
 getTJ300RNcHPCMapMtx(NcHPCMapMtx);

/* Gets TJ300RNcVec Matrix */
 getTJ300RNcVec(NcVec);

/* Gets TJ300RPRHPCMapMtx Matrix */
 getTJ300RPRHPCMapMtx(PRHPCMapMtx);

/* Gets TJ300RPt3DMtx Matrix */
 getTJ300RPt3DMtx(Pt3DMtx);

/* Gets TJ300RPt3Mtx Matrix */
 getTJ300RPt3Mtx(Pt3Mtx);

/* Gets TJ300RPt5DMtx Matrix */
 getTJ300RPt5DMtx(Pt5DMtx);

/* Gets TJ300RPt5Mtx Matrix */
 getTJ300RPt5Mtx(Pt5Mtx);

/* Gets TJ300RTs0Mtx Matrix */
 getTJ300RTs0Mtx(Ts0Mtx);

/* Gets TJ300RTt4DMtx Matrix */
 getTJ300RTt4DMtx(Tt4DMtx);

/* Gets TJ300RTt4Mtx Matrix */
 getTJ300RTt4Mtx(Tt4Mtx);

/* Gets TJ300RTt5DMtx Matrix */
 getTJ300RTt5DMtx(Tt5DMtx);

/* Gets TJ300RTt5Mtx Matrix */
 getTJ300RTt5Mtx(Tt5Mtx);

/* Gets TJ300RWcHPCMapMtx Matrix */
 getTJ300RWcHPCMapMtx(WcHPCMapMtx);

/* Gets TJ300RWfMtx Matrix */
 getTJ300RWfMtx(WfMtx);

/* Gets TJ300RN_KpshMtx Matrix */
 getTJ300RN_KpshMtx(N_KpshMtx);

/* Gets TJ300RN_KishMtx Matrix */
 getTJ300RN_KishMtx(N_KishMtx);

/* Gets TJ300RNcFANshContMtx Matrix */
 getTJ300RNcFANshContMtx(NcFANshContMtx);

}

