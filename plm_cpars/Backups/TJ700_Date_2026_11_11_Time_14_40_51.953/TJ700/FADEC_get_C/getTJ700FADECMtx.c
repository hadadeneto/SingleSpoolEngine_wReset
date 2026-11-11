
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../FADEC_get_H/getTJ700FADEC.h"

void getTJ700FADECMtx(floating *AMtx, floating *ASVec, floating *AltLinVec, floating *BMtx, floating *DSVec, 
     floating *DeltaMtx, floating *FNcMaxContMtx, floating *FNperContMtx, floating *MNLinVec, floating *N_KiMtx, 
     floating *N_KpMtx, floating *NcFANContMtx, floating *NcHPCMapMtx, floating *NcVec, floating *PRHPCMapMtx, 
     floating *Pt3DMtx, floating *Pt3Mtx, floating *Pt5DMtx, floating *Pt5Mtx, floating *Ts0Mtx, 
     floating *Tt4DMtx, floating *Tt4Mtx, floating *Tt5DMtx, floating *Tt5Mtx, floating *WcHPCMapMtx, 
     floating *WfMtx, floating *N_KpshMtx, floating *N_KishMtx, floating *NcFANshContMtx)

{

/* Gets TJ700AMtx Matrix */
 getTJ700AMtx(AMtx);

/* Gets TJ700ASVec Matrix */
 getTJ700ASVec(ASVec);

/* Gets TJ700AltLinVec Matrix */
 getTJ700AltLinVec(AltLinVec);

/* Gets TJ700BMtx Matrix */
 getTJ700BMtx(BMtx);

/* Gets TJ700DSVec Matrix */
 getTJ700DSVec(DSVec);

/* Gets TJ700DeltaMtx Matrix */
 getTJ700DeltaMtx(DeltaMtx);

/* Gets TJ700FNcMaxContMtx Matrix */
 getTJ700FNcMaxContMtx(FNcMaxContMtx);

/* Gets TJ700FNperContMtx Matrix */
 getTJ700FNperContMtx(FNperContMtx);

/* Gets TJ700MNLinVec Matrix */
 getTJ700MNLinVec(MNLinVec);

/* Gets TJ700N_KiMtx Matrix */
 getTJ700N_KiMtx(N_KiMtx);

/* Gets TJ700N_KpMtx Matrix */
 getTJ700N_KpMtx(N_KpMtx);

/* Gets TJ700NcFANContMtx Matrix */
 getTJ700NcFANContMtx(NcFANContMtx);

/* Gets TJ700NcHPCMapMtx Matrix */
 getTJ700NcHPCMapMtx(NcHPCMapMtx);

/* Gets TJ700NcVec Matrix */
 getTJ700NcVec(NcVec);

/* Gets TJ700PRHPCMapMtx Matrix */
 getTJ700PRHPCMapMtx(PRHPCMapMtx);

/* Gets TJ700Pt3DMtx Matrix */
 getTJ700Pt3DMtx(Pt3DMtx);

/* Gets TJ700Pt3Mtx Matrix */
 getTJ700Pt3Mtx(Pt3Mtx);

/* Gets TJ700Pt5DMtx Matrix */
 getTJ700Pt5DMtx(Pt5DMtx);

/* Gets TJ700Pt5Mtx Matrix */
 getTJ700Pt5Mtx(Pt5Mtx);

/* Gets TJ700Ts0Mtx Matrix */
 getTJ700Ts0Mtx(Ts0Mtx);

/* Gets TJ700Tt4DMtx Matrix */
 getTJ700Tt4DMtx(Tt4DMtx);

/* Gets TJ700Tt4Mtx Matrix */
 getTJ700Tt4Mtx(Tt4Mtx);

/* Gets TJ700Tt5DMtx Matrix */
 getTJ700Tt5DMtx(Tt5DMtx);

/* Gets TJ700Tt5Mtx Matrix */
 getTJ700Tt5Mtx(Tt5Mtx);

/* Gets TJ700WcHPCMapMtx Matrix */
 getTJ700WcHPCMapMtx(WcHPCMapMtx);

/* Gets TJ700WfMtx Matrix */
 getTJ700WfMtx(WfMtx);

/* Gets TJ700N_KpshMtx Matrix */
 getTJ700N_KpshMtx(N_KpshMtx);

/* Gets TJ700N_KishMtx Matrix */
 getTJ700N_KishMtx(N_KishMtx);

/* Gets TJ700NcFANshContMtx Matrix */
 getTJ700NcFANshContMtx(NcFANshContMtx);

}

