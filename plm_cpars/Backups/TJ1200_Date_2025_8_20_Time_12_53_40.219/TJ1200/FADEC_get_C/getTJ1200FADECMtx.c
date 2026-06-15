
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../FADEC_get_H/getTJ1200FADEC.h"

void getTJ1200FADECMtx(floating *AMtx, floating *ASVec, floating *AltLinVec, floating *BMtx, floating *DSVec, 
     floating *DeltaMtx, floating *FNcMaxContMtx, floating *FNperContMtx, floating *MNLinVec, floating *N_KiMtx, 
     floating *N_KpMtx, floating *NcFANContMtx, floating *NcHPCMapMtx, floating *NcVec, floating *PRHPCMapMtx, 
     floating *Pt3DMtx, floating *Pt3Mtx, floating *Pt5DMtx, floating *Pt5Mtx, floating *Ts0Mtx, 
     floating *Tt4DMtx, floating *Tt4Mtx, floating *Tt5DMtx, floating *Tt5Mtx, floating *WcHPCMapMtx, 
     floating *WfMtx, floating *N_KpshMtx, floating *N_KishMtx, floating *NcFANshContMtx)

{

/* Gets TJ1200AMtx Matrix */
 getTJ1200AMtx(AMtx);

/* Gets TJ1200ASVec Matrix */
 getTJ1200ASVec(ASVec);

/* Gets TJ1200AltLinVec Matrix */
 getTJ1200AltLinVec(AltLinVec);

/* Gets TJ1200BMtx Matrix */
 getTJ1200BMtx(BMtx);

/* Gets TJ1200DSVec Matrix */
 getTJ1200DSVec(DSVec);

/* Gets TJ1200DeltaMtx Matrix */
 getTJ1200DeltaMtx(DeltaMtx);

/* Gets TJ1200FNcMaxContMtx Matrix */
 getTJ1200FNcMaxContMtx(FNcMaxContMtx);

/* Gets TJ1200FNperContMtx Matrix */
 getTJ1200FNperContMtx(FNperContMtx);

/* Gets TJ1200MNLinVec Matrix */
 getTJ1200MNLinVec(MNLinVec);

/* Gets TJ1200N_KiMtx Matrix */
 getTJ1200N_KiMtx(N_KiMtx);

/* Gets TJ1200N_KpMtx Matrix */
 getTJ1200N_KpMtx(N_KpMtx);

/* Gets TJ1200NcFANContMtx Matrix */
 getTJ1200NcFANContMtx(NcFANContMtx);

/* Gets TJ1200NcHPCMapMtx Matrix */
 getTJ1200NcHPCMapMtx(NcHPCMapMtx);

/* Gets TJ1200NcVec Matrix */
 getTJ1200NcVec(NcVec);

/* Gets TJ1200PRHPCMapMtx Matrix */
 getTJ1200PRHPCMapMtx(PRHPCMapMtx);

/* Gets TJ1200Pt3DMtx Matrix */
 getTJ1200Pt3DMtx(Pt3DMtx);

/* Gets TJ1200Pt3Mtx Matrix */
 getTJ1200Pt3Mtx(Pt3Mtx);

/* Gets TJ1200Pt5DMtx Matrix */
 getTJ1200Pt5DMtx(Pt5DMtx);

/* Gets TJ1200Pt5Mtx Matrix */
 getTJ1200Pt5Mtx(Pt5Mtx);

/* Gets TJ1200Ts0Mtx Matrix */
 getTJ1200Ts0Mtx(Ts0Mtx);

/* Gets TJ1200Tt4DMtx Matrix */
 getTJ1200Tt4DMtx(Tt4DMtx);

/* Gets TJ1200Tt4Mtx Matrix */
 getTJ1200Tt4Mtx(Tt4Mtx);

/* Gets TJ1200Tt5DMtx Matrix */
 getTJ1200Tt5DMtx(Tt5DMtx);

/* Gets TJ1200Tt5Mtx Matrix */
 getTJ1200Tt5Mtx(Tt5Mtx);

/* Gets TJ1200WcHPCMapMtx Matrix */
 getTJ1200WcHPCMapMtx(WcHPCMapMtx);

/* Gets TJ1200WfMtx Matrix */
 getTJ1200WfMtx(WfMtx);

/* Gets TJ1200N_KpshMtx Matrix */
 getTJ1200N_KpshMtx(N_KpshMtx);

/* Gets TJ1200N_KishMtx Matrix */
 getTJ1200N_KishMtx(N_KishMtx);

/* Gets TJ1200NcFANshContMtx Matrix */
 getTJ1200NcFANshContMtx(NcFANshContMtx);

}

