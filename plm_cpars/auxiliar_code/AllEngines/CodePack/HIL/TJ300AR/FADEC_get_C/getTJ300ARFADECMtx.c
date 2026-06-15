
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../FADEC_get_H/getTJ300ARFADEC.h"

void getTJ300ARFADECMtx(floating *AMtx, floating *ASVec, floating *AltLinVec, floating *BMtx, floating *DSVec, 
     floating *DeltaMtx, floating *FNcMaxContMtx, floating *FNperContMtx, floating *MNLinVec, floating *N_KiMtx, 
     floating *N_KpMtx, floating *NcFANContMtx, floating *NcHPCMapMtx, floating *NcVec, floating *PRHPCMapMtx, 
     floating *Pt3DMtx, floating *Pt3Mtx, floating *Pt5DMtx, floating *Pt5Mtx, floating *Ts0Mtx, 
     floating *Tt4DMtx, floating *Tt4Mtx, floating *Tt5DMtx, floating *Tt5Mtx, floating *WcHPCMapMtx, 
     floating *WfMtx, floating *N_KpshMtx, floating *N_KishMtx, floating *NcFANshContMtx)

{

/* Gets TJ300ARAMtx Matrix */
 getTJ300ARAMtx(AMtx);

/* Gets TJ300ARASVec Matrix */
 getTJ300ARASVec(ASVec);

/* Gets TJ300ARAltLinVec Matrix */
 getTJ300ARAltLinVec(AltLinVec);

/* Gets TJ300ARBMtx Matrix */
 getTJ300ARBMtx(BMtx);

/* Gets TJ300ARDSVec Matrix */
 getTJ300ARDSVec(DSVec);

/* Gets TJ300ARDeltaMtx Matrix */
 getTJ300ARDeltaMtx(DeltaMtx);

/* Gets TJ300ARFNcMaxContMtx Matrix */
 getTJ300ARFNcMaxContMtx(FNcMaxContMtx);

/* Gets TJ300ARFNperContMtx Matrix */
 getTJ300ARFNperContMtx(FNperContMtx);

/* Gets TJ300ARMNLinVec Matrix */
 getTJ300ARMNLinVec(MNLinVec);

/* Gets TJ300ARN_KiMtx Matrix */
 getTJ300ARN_KiMtx(N_KiMtx);

/* Gets TJ300ARN_KpMtx Matrix */
 getTJ300ARN_KpMtx(N_KpMtx);

/* Gets TJ300ARNcFANContMtx Matrix */
 getTJ300ARNcFANContMtx(NcFANContMtx);

/* Gets TJ300ARNcHPCMapMtx Matrix */
 getTJ300ARNcHPCMapMtx(NcHPCMapMtx);

/* Gets TJ300ARNcVec Matrix */
 getTJ300ARNcVec(NcVec);

/* Gets TJ300ARPRHPCMapMtx Matrix */
 getTJ300ARPRHPCMapMtx(PRHPCMapMtx);

/* Gets TJ300ARPt3DMtx Matrix */
 getTJ300ARPt3DMtx(Pt3DMtx);

/* Gets TJ300ARPt3Mtx Matrix */
 getTJ300ARPt3Mtx(Pt3Mtx);

/* Gets TJ300ARPt5DMtx Matrix */
 getTJ300ARPt5DMtx(Pt5DMtx);

/* Gets TJ300ARPt5Mtx Matrix */
 getTJ300ARPt5Mtx(Pt5Mtx);

/* Gets TJ300ARTs0Mtx Matrix */
 getTJ300ARTs0Mtx(Ts0Mtx);

/* Gets TJ300ARTt4DMtx Matrix */
 getTJ300ARTt4DMtx(Tt4DMtx);

/* Gets TJ300ARTt4Mtx Matrix */
 getTJ300ARTt4Mtx(Tt4Mtx);

/* Gets TJ300ARTt5DMtx Matrix */
 getTJ300ARTt5DMtx(Tt5DMtx);

/* Gets TJ300ARTt5Mtx Matrix */
 getTJ300ARTt5Mtx(Tt5Mtx);

/* Gets TJ300ARWcHPCMapMtx Matrix */
 getTJ300ARWcHPCMapMtx(WcHPCMapMtx);

/* Gets TJ300ARWfMtx Matrix */
 getTJ300ARWfMtx(WfMtx);

/* Gets TJ300ARN_KpshMtx Matrix */
 getTJ300ARN_KpshMtx(N_KpshMtx);

/* Gets TJ300ARN_KishMtx Matrix */
 getTJ300ARN_KishMtx(N_KishMtx);

/* Gets TJ300ARNcFANshContMtx Matrix */
 getTJ300ARNcFANshContMtx(NcFANshContMtx);

}

