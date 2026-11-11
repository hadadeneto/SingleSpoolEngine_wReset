
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../FADEC_get_H/getTF1200FADEC.h"

void getTF1200FADECMtx(floating *AMtx, floating *ASVec, floating *AltLinVec, floating *BMtx, floating *DSVec, 
     floating *DeltaMtx, floating *FNcMaxContMtx, floating *FNperContMtx, floating *MNLinVec, floating *N_KiMtx, 
     floating *N_KpMtx, floating *NcFANContMtx, floating *NcHPCMapMtx, floating *NcVec, floating *PRHPCMapMtx, 
     floating *Pt3DMtx, floating *Pt3Mtx, floating *Pt5DMtx, floating *Pt5Mtx, floating *Ts0Mtx, 
     floating *Tt4DMtx, floating *Tt4Mtx, floating *Tt5DMtx, floating *Tt5Mtx, floating *WcHPCMapMtx, 
     floating *WfMtx, floating *N_KpshMtx, floating *N_KishMtx, floating *NcFANshContMtx)

{

/* Gets TF1200AMtx Matrix */
 getTF1200AMtx(AMtx);

/* Gets TF1200ASVec Matrix */
 getTF1200ASVec(ASVec);

/* Gets TF1200AltLinVec Matrix */
 getTF1200AltLinVec(AltLinVec);

/* Gets TF1200BMtx Matrix */
 getTF1200BMtx(BMtx);

/* Gets TF1200DSVec Matrix */
 getTF1200DSVec(DSVec);

/* Gets TF1200DeltaMtx Matrix */
 getTF1200DeltaMtx(DeltaMtx);

/* Gets TF1200FNcMaxContMtx Matrix */
 getTF1200FNcMaxContMtx(FNcMaxContMtx);

/* Gets TF1200FNperContMtx Matrix */
 getTF1200FNperContMtx(FNperContMtx);

/* Gets TF1200MNLinVec Matrix */
 getTF1200MNLinVec(MNLinVec);

/* Gets TF1200N_KiMtx Matrix */
 getTF1200N_KiMtx(N_KiMtx);

/* Gets TF1200N_KpMtx Matrix */
 getTF1200N_KpMtx(N_KpMtx);

/* Gets TF1200NcFANContMtx Matrix */
 getTF1200NcFANContMtx(NcFANContMtx);

/* Gets TF1200NcHPCMapMtx Matrix */
 getTF1200NcHPCMapMtx(NcHPCMapMtx);

/* Gets TF1200NcVec Matrix */
 getTF1200NcVec(NcVec);

/* Gets TF1200PRHPCMapMtx Matrix */
 getTF1200PRHPCMapMtx(PRHPCMapMtx);

/* Gets TF1200Pt3DMtx Matrix */
 getTF1200Pt3DMtx(Pt3DMtx);

/* Gets TF1200Pt3Mtx Matrix */
 getTF1200Pt3Mtx(Pt3Mtx);

/* Gets TF1200Pt5DMtx Matrix */
 getTF1200Pt5DMtx(Pt5DMtx);

/* Gets TF1200Pt5Mtx Matrix */
 getTF1200Pt5Mtx(Pt5Mtx);

/* Gets TF1200Ts0Mtx Matrix */
 getTF1200Ts0Mtx(Ts0Mtx);

/* Gets TF1200Tt4DMtx Matrix */
 getTF1200Tt4DMtx(Tt4DMtx);

/* Gets TF1200Tt4Mtx Matrix */
 getTF1200Tt4Mtx(Tt4Mtx);

/* Gets TF1200Tt5DMtx Matrix */
 getTF1200Tt5DMtx(Tt5DMtx);

/* Gets TF1200Tt5Mtx Matrix */
 getTF1200Tt5Mtx(Tt5Mtx);

/* Gets TF1200WcHPCMapMtx Matrix */
 getTF1200WcHPCMapMtx(WcHPCMapMtx);

/* Gets TF1200WfMtx Matrix */
 getTF1200WfMtx(WfMtx);

/* Gets TF1200N_KpshMtx Matrix */
 getTF1200N_KpshMtx(N_KpshMtx);

/* Gets TF1200N_KishMtx Matrix */
 getTF1200N_KishMtx(N_KishMtx);

/* Gets TF1200NcFANshContMtx Matrix */
 getTF1200NcFANshContMtx(NcFANshContMtx);

}

