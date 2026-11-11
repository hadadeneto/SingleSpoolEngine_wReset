
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../FADEC_get_H/getTG200FADEC.h"

void getTG200FADECMtx(floating *AMtx, floating *ASVec, floating *AltLinVec, floating *BMtx, floating *DSVec, 
     floating *DeltaMtx, floating *FNcMaxContMtx, floating *FNperContMtx, floating *MNLinVec, floating *N_KiMtx, 
     floating *N_KpMtx, floating *NcFANContMtx, floating *NcHPCMapMtx, floating *NcVec, floating *PRHPCMapMtx, 
     floating *Pt3DMtx, floating *Pt3Mtx, floating *Pt5DMtx, floating *Pt5Mtx, floating *Ts0Mtx, 
     floating *Tt4DMtx, floating *Tt4Mtx, floating *Tt5DMtx, floating *Tt5Mtx, floating *WcHPCMapMtx, 
     floating *WfMtx, floating *N_KpshMtx, floating *N_KishMtx, floating *NcFANshContMtx)

{

/* Gets TG200AMtx Matrix */
 getTG200AMtx(AMtx);

/* Gets TG200ASVec Matrix */
 getTG200ASVec(ASVec);

/* Gets TG200AltLinVec Matrix */
 getTG200AltLinVec(AltLinVec);

/* Gets TG200BMtx Matrix */
 getTG200BMtx(BMtx);

/* Gets TG200DSVec Matrix */
 getTG200DSVec(DSVec);

/* Gets TG200DeltaMtx Matrix */
 getTG200DeltaMtx(DeltaMtx);

/* Gets TG200FNcMaxContMtx Matrix */
 getTG200FNcMaxContMtx(FNcMaxContMtx);

/* Gets TG200FNperContMtx Matrix */
 getTG200FNperContMtx(FNperContMtx);

/* Gets TG200MNLinVec Matrix */
 getTG200MNLinVec(MNLinVec);

/* Gets TG200N_KiMtx Matrix */
 getTG200N_KiMtx(N_KiMtx);

/* Gets TG200N_KpMtx Matrix */
 getTG200N_KpMtx(N_KpMtx);

/* Gets TG200NcFANContMtx Matrix */
 getTG200NcFANContMtx(NcFANContMtx);

/* Gets TG200NcHPCMapMtx Matrix */
 getTG200NcHPCMapMtx(NcHPCMapMtx);

/* Gets TG200NcVec Matrix */
 getTG200NcVec(NcVec);

/* Gets TG200PRHPCMapMtx Matrix */
 getTG200PRHPCMapMtx(PRHPCMapMtx);

/* Gets TG200Pt3DMtx Matrix */
 getTG200Pt3DMtx(Pt3DMtx);

/* Gets TG200Pt3Mtx Matrix */
 getTG200Pt3Mtx(Pt3Mtx);

/* Gets TG200Pt5DMtx Matrix */
 getTG200Pt5DMtx(Pt5DMtx);

/* Gets TG200Pt5Mtx Matrix */
 getTG200Pt5Mtx(Pt5Mtx);

/* Gets TG200Ts0Mtx Matrix */
 getTG200Ts0Mtx(Ts0Mtx);

/* Gets TG200Tt4DMtx Matrix */
 getTG200Tt4DMtx(Tt4DMtx);

/* Gets TG200Tt4Mtx Matrix */
 getTG200Tt4Mtx(Tt4Mtx);

/* Gets TG200Tt5DMtx Matrix */
 getTG200Tt5DMtx(Tt5DMtx);

/* Gets TG200Tt5Mtx Matrix */
 getTG200Tt5Mtx(Tt5Mtx);

/* Gets TG200WcHPCMapMtx Matrix */
 getTG200WcHPCMapMtx(WcHPCMapMtx);

/* Gets TG200WfMtx Matrix */
 getTG200WfMtx(WfMtx);

/* Gets TG200N_KpshMtx Matrix */
 getTG200N_KpshMtx(N_KpshMtx);

/* Gets TG200N_KishMtx Matrix */
 getTG200N_KishMtx(N_KishMtx);

/* Gets TG200NcFANshContMtx Matrix */
 getTG200NcFANshContMtx(NcFANshContMtx);

}

