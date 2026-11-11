
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../FADEC_get_H/getGEJ85FADEC.h"

void getGEJ85FADECMtx(floating *AMtx, floating *ASVec, floating *AltLinVec, floating *BMtx, floating *DSVec, 
     floating *DeltaMtx, floating *FNcMaxContMtx, floating *FNperContMtx, floating *MNLinVec, floating *N_KiMtx, 
     floating *N_KpMtx, floating *NcFANContMtx, floating *NcHPCMapMtx, floating *NcVec, floating *PRHPCMapMtx, 
     floating *Pt3DMtx, floating *Pt3Mtx, floating *Pt5DMtx, floating *Pt5Mtx, floating *Ts0Mtx, 
     floating *Tt4DMtx, floating *Tt4Mtx, floating *Tt5DMtx, floating *Tt5Mtx, floating *WcHPCMapMtx, 
     floating *WfMtx, floating *N_KpshMtx, floating *N_KishMtx, floating *NcFANshContMtx)

{

/* Gets GEJ85AMtx Matrix */
 getGEJ85AMtx(AMtx);

/* Gets GEJ85ASVec Matrix */
 getGEJ85ASVec(ASVec);

/* Gets GEJ85AltLinVec Matrix */
 getGEJ85AltLinVec(AltLinVec);

/* Gets GEJ85BMtx Matrix */
 getGEJ85BMtx(BMtx);

/* Gets GEJ85DSVec Matrix */
 getGEJ85DSVec(DSVec);

/* Gets GEJ85DeltaMtx Matrix */
 getGEJ85DeltaMtx(DeltaMtx);

/* Gets GEJ85FNcMaxContMtx Matrix */
 getGEJ85FNcMaxContMtx(FNcMaxContMtx);

/* Gets GEJ85FNperContMtx Matrix */
 getGEJ85FNperContMtx(FNperContMtx);

/* Gets GEJ85MNLinVec Matrix */
 getGEJ85MNLinVec(MNLinVec);

/* Gets GEJ85N_KiMtx Matrix */
 getGEJ85N_KiMtx(N_KiMtx);

/* Gets GEJ85N_KpMtx Matrix */
 getGEJ85N_KpMtx(N_KpMtx);

/* Gets GEJ85NcFANContMtx Matrix */
 getGEJ85NcFANContMtx(NcFANContMtx);

/* Gets GEJ85NcHPCMapMtx Matrix */
 getGEJ85NcHPCMapMtx(NcHPCMapMtx);

/* Gets GEJ85NcVec Matrix */
 getGEJ85NcVec(NcVec);

/* Gets GEJ85PRHPCMapMtx Matrix */
 getGEJ85PRHPCMapMtx(PRHPCMapMtx);

/* Gets GEJ85Pt3DMtx Matrix */
 getGEJ85Pt3DMtx(Pt3DMtx);

/* Gets GEJ85Pt3Mtx Matrix */
 getGEJ85Pt3Mtx(Pt3Mtx);

/* Gets GEJ85Pt5DMtx Matrix */
 getGEJ85Pt5DMtx(Pt5DMtx);

/* Gets GEJ85Pt5Mtx Matrix */
 getGEJ85Pt5Mtx(Pt5Mtx);

/* Gets GEJ85Ts0Mtx Matrix */
 getGEJ85Ts0Mtx(Ts0Mtx);

/* Gets GEJ85Tt4DMtx Matrix */
 getGEJ85Tt4DMtx(Tt4DMtx);

/* Gets GEJ85Tt4Mtx Matrix */
 getGEJ85Tt4Mtx(Tt4Mtx);

/* Gets GEJ85Tt5DMtx Matrix */
 getGEJ85Tt5DMtx(Tt5DMtx);

/* Gets GEJ85Tt5Mtx Matrix */
 getGEJ85Tt5Mtx(Tt5Mtx);

/* Gets GEJ85WcHPCMapMtx Matrix */
 getGEJ85WcHPCMapMtx(WcHPCMapMtx);

/* Gets GEJ85WfMtx Matrix */
 getGEJ85WfMtx(WfMtx);

/* Gets GEJ85N_KpshMtx Matrix */
 getGEJ85N_KpshMtx(N_KpshMtx);

/* Gets GEJ85N_KishMtx Matrix */
 getGEJ85N_KishMtx(N_KishMtx);

/* Gets GEJ85NcFANshContMtx Matrix */
 getGEJ85NcFANshContMtx(NcFANshContMtx);

}

