
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../FADEC_get_H/getTJ200FADEC.h"

void getTJ200FADECMtx(floating *AMtx, floating *ASVec, floating *AltLinVec, floating *BMtx, floating *DSVec, 
     floating *DeltaMtx, floating *FNcMaxContMtx, floating *FNperContMtx, floating *MNLinVec, floating *N_KiMtx, 
     floating *N_KpMtx, floating *NcFANContMtx, floating *NcHPCMapMtx, floating *NcVec, floating *PRHPCMapMtx, 
     floating *Pt3DMtx, floating *Pt3Mtx, floating *Pt5DMtx, floating *Pt5Mtx, floating *Ts0Mtx, 
     floating *Tt4DMtx, floating *Tt4Mtx, floating *Tt5DMtx, floating *Tt5Mtx, floating *WcHPCMapMtx, 
     floating *WfMtx, floating *N_KpshMtx, floating *N_KishMtx, floating *NcFANshContMtx)

{

/* Gets TJ200AMtx Matrix */
 getTJ200AMtx(AMtx);

/* Gets TJ200ASVec Matrix */
 getTJ200ASVec(ASVec);

/* Gets TJ200AltLinVec Matrix */
 getTJ200AltLinVec(AltLinVec);

/* Gets TJ200BMtx Matrix */
 getTJ200BMtx(BMtx);

/* Gets TJ200DSVec Matrix */
 getTJ200DSVec(DSVec);

/* Gets TJ200DeltaMtx Matrix */
 getTJ200DeltaMtx(DeltaMtx);

/* Gets TJ200FNcMaxContMtx Matrix */
 getTJ200FNcMaxContMtx(FNcMaxContMtx);

/* Gets TJ200FNperContMtx Matrix */
 getTJ200FNperContMtx(FNperContMtx);

/* Gets TJ200MNLinVec Matrix */
 getTJ200MNLinVec(MNLinVec);

/* Gets TJ200N_KiMtx Matrix */
 getTJ200N_KiMtx(N_KiMtx);

/* Gets TJ200N_KpMtx Matrix */
 getTJ200N_KpMtx(N_KpMtx);

/* Gets TJ200NcFANContMtx Matrix */
 getTJ200NcFANContMtx(NcFANContMtx);

/* Gets TJ200NcHPCMapMtx Matrix */
 getTJ200NcHPCMapMtx(NcHPCMapMtx);

/* Gets TJ200NcVec Matrix */
 getTJ200NcVec(NcVec);

/* Gets TJ200PRHPCMapMtx Matrix */
 getTJ200PRHPCMapMtx(PRHPCMapMtx);

/* Gets TJ200Pt3DMtx Matrix */
 getTJ200Pt3DMtx(Pt3DMtx);

/* Gets TJ200Pt3Mtx Matrix */
 getTJ200Pt3Mtx(Pt3Mtx);

/* Gets TJ200Pt5DMtx Matrix */
 getTJ200Pt5DMtx(Pt5DMtx);

/* Gets TJ200Pt5Mtx Matrix */
 getTJ200Pt5Mtx(Pt5Mtx);

/* Gets TJ200Ts0Mtx Matrix */
 getTJ200Ts0Mtx(Ts0Mtx);

/* Gets TJ200Tt4DMtx Matrix */
 getTJ200Tt4DMtx(Tt4DMtx);

/* Gets TJ200Tt4Mtx Matrix */
 getTJ200Tt4Mtx(Tt4Mtx);

/* Gets TJ200Tt5DMtx Matrix */
 getTJ200Tt5DMtx(Tt5DMtx);

/* Gets TJ200Tt5Mtx Matrix */
 getTJ200Tt5Mtx(Tt5Mtx);

/* Gets TJ200WcHPCMapMtx Matrix */
 getTJ200WcHPCMapMtx(WcHPCMapMtx);

/* Gets TJ200WfMtx Matrix */
 getTJ200WfMtx(WfMtx);

/* Gets TJ200N_KpshMtx Matrix */
 getTJ200N_KpshMtx(N_KpshMtx);

/* Gets TJ200N_KishMtx Matrix */
 getTJ200N_KishMtx(N_KishMtx);

/* Gets TJ200NcFANshContMtx Matrix */
 getTJ200NcFANshContMtx(NcFANshContMtx);

}

