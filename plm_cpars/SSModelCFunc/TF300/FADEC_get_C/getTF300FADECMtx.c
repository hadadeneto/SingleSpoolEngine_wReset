
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../FADEC_get_H/getTF300FADEC.h"

void getTF300FADECMtx(floating *AMtx, floating *ASVec, floating *AltLinVec, floating *BMtx, floating *DSVec, 
     floating *DeltaMtx, floating *FNcMaxContMtx, floating *FNperContMtx, floating *MNLinVec, floating *N_KiMtx, 
     floating *N_KpMtx, floating *NcFANContMtx, floating *NcHPCMapMtx, floating *NcVec, floating *PRHPCMapMtx, 
     floating *Pt3DMtx, floating *Pt3Mtx, floating *Pt5DMtx, floating *Pt5Mtx, floating *Ts0Mtx, 
     floating *Tt4DMtx, floating *Tt4Mtx, floating *Tt5DMtx, floating *Tt5Mtx, floating *WcHPCMapMtx, 
     floating *WfMtx, floating *N_KpshMtx, floating *N_KishMtx, floating *NcFANshContMtx)

{

/* Gets TF300AMtx Matrix */
 getTF300AMtx(AMtx);

/* Gets TF300ASVec Matrix */
 getTF300ASVec(ASVec);

/* Gets TF300AltLinVec Matrix */
 getTF300AltLinVec(AltLinVec);

/* Gets TF300BMtx Matrix */
 getTF300BMtx(BMtx);

/* Gets TF300DSVec Matrix */
 getTF300DSVec(DSVec);

/* Gets TF300DeltaMtx Matrix */
 getTF300DeltaMtx(DeltaMtx);

/* Gets TF300FNcMaxContMtx Matrix */
 getTF300FNcMaxContMtx(FNcMaxContMtx);

/* Gets TF300FNperContMtx Matrix */
 getTF300FNperContMtx(FNperContMtx);

/* Gets TF300MNLinVec Matrix */
 getTF300MNLinVec(MNLinVec);

/* Gets TF300N_KiMtx Matrix */
 getTF300N_KiMtx(N_KiMtx);

/* Gets TF300N_KpMtx Matrix */
 getTF300N_KpMtx(N_KpMtx);

/* Gets TF300NcFANContMtx Matrix */
 getTF300NcFANContMtx(NcFANContMtx);

/* Gets TF300NcHPCMapMtx Matrix */
 getTF300NcHPCMapMtx(NcHPCMapMtx);

/* Gets TF300NcVec Matrix */
 getTF300NcVec(NcVec);

/* Gets TF300PRHPCMapMtx Matrix */
 getTF300PRHPCMapMtx(PRHPCMapMtx);

/* Gets TF300Pt3DMtx Matrix */
 getTF300Pt3DMtx(Pt3DMtx);

/* Gets TF300Pt3Mtx Matrix */
 getTF300Pt3Mtx(Pt3Mtx);

/* Gets TF300Pt5DMtx Matrix */
 getTF300Pt5DMtx(Pt5DMtx);

/* Gets TF300Pt5Mtx Matrix */
 getTF300Pt5Mtx(Pt5Mtx);

/* Gets TF300Ts0Mtx Matrix */
 getTF300Ts0Mtx(Ts0Mtx);

/* Gets TF300Tt4DMtx Matrix */
 getTF300Tt4DMtx(Tt4DMtx);

/* Gets TF300Tt4Mtx Matrix */
 getTF300Tt4Mtx(Tt4Mtx);

/* Gets TF300Tt5DMtx Matrix */
 getTF300Tt5DMtx(Tt5DMtx);

/* Gets TF300Tt5Mtx Matrix */
 getTF300Tt5Mtx(Tt5Mtx);

/* Gets TF300WcHPCMapMtx Matrix */
 getTF300WcHPCMapMtx(WcHPCMapMtx);

/* Gets TF300WfMtx Matrix */
 getTF300WfMtx(WfMtx);

/* Gets TF300N_KpshMtx Matrix */
 getTF300N_KpshMtx(N_KpshMtx);

/* Gets TF300N_KishMtx Matrix */
 getTF300N_KishMtx(N_KishMtx);

/* Gets TF300NcFANshContMtx Matrix */
 getTF300NcFANshContMtx(NcFANshContMtx);

}

