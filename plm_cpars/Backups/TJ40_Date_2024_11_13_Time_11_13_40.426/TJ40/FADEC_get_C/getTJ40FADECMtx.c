
#include <math.h>
#include "../FADEC_get_H/getTJ40FADEC.h"

void getTJ40FADECMtx(double *AMtx, double *ASVec, double *AltLinVec, double *BMtx, double *DSVec, 
     double *DeltaMtx, double *FNcMaxContMtx, double *FNperContMtx, double *MNLinVec, double *N_KiMtx, 
     double *N_KpMtx, double *NcFANContMtx, double *NcHPCMapMtx, double *NcVec, double *PRHPCMapMtx, 
     double *Pt3DMtx, double *Pt3Mtx, double *Pt5DMtx, double *Pt5Mtx, double *Ts0Mtx, 
     double *Tt4DMtx, double *Tt4Mtx, double *Tt5DMtx, double *Tt5Mtx, double *WcHPCMapMtx, 
     double *WfMtx, double *N_KpshMtx, double *N_KishMtx, double *NcFANshContMtx)

{

/* Gets TJ40AMtx Matrix */
 getTJ40AMtx(AMtx);

/* Gets TJ40ASVec Matrix */
 getTJ40ASVec(ASVec);

/* Gets TJ40AltLinVec Matrix */
 getTJ40AltLinVec(AltLinVec);

/* Gets TJ40BMtx Matrix */
 getTJ40BMtx(BMtx);

/* Gets TJ40DSVec Matrix */
 getTJ40DSVec(DSVec);

/* Gets TJ40DeltaMtx Matrix */
 getTJ40DeltaMtx(DeltaMtx);

/* Gets TJ40FNcMaxContMtx Matrix */
 getTJ40FNcMaxContMtx(FNcMaxContMtx);

/* Gets TJ40FNperContMtx Matrix */
 getTJ40FNperContMtx(FNperContMtx);

/* Gets TJ40MNLinVec Matrix */
 getTJ40MNLinVec(MNLinVec);

/* Gets TJ40N_KiMtx Matrix */
 getTJ40N_KiMtx(N_KiMtx);

/* Gets TJ40N_KpMtx Matrix */
 getTJ40N_KpMtx(N_KpMtx);

/* Gets TJ40NcFANContMtx Matrix */
 getTJ40NcFANContMtx(NcFANContMtx);

/* Gets TJ40NcHPCMapMtx Matrix */
 getTJ40NcHPCMapMtx(NcHPCMapMtx);

/* Gets TJ40NcVec Matrix */
 getTJ40NcVec(NcVec);

/* Gets TJ40PRHPCMapMtx Matrix */
 getTJ40PRHPCMapMtx(PRHPCMapMtx);

/* Gets TJ40Pt3DMtx Matrix */
 getTJ40Pt3DMtx(Pt3DMtx);

/* Gets TJ40Pt3Mtx Matrix */
 getTJ40Pt3Mtx(Pt3Mtx);

/* Gets TJ40Pt5DMtx Matrix */
 getTJ40Pt5DMtx(Pt5DMtx);

/* Gets TJ40Pt5Mtx Matrix */
 getTJ40Pt5Mtx(Pt5Mtx);

/* Gets TJ40Ts0Mtx Matrix */
 getTJ40Ts0Mtx(Ts0Mtx);

/* Gets TJ40Tt4DMtx Matrix */
 getTJ40Tt4DMtx(Tt4DMtx);

/* Gets TJ40Tt4Mtx Matrix */
 getTJ40Tt4Mtx(Tt4Mtx);

/* Gets TJ40Tt5DMtx Matrix */
 getTJ40Tt5DMtx(Tt5DMtx);

/* Gets TJ40Tt5Mtx Matrix */
 getTJ40Tt5Mtx(Tt5Mtx);

/* Gets TJ40WcHPCMapMtx Matrix */
 getTJ40WcHPCMapMtx(WcHPCMapMtx);

/* Gets TJ40WfMtx Matrix */
 getTJ40WfMtx(WfMtx);

/* Gets TJ40N_KpshMtx Matrix */
 getTJ40N_KpshMtx(N_KpshMtx);

/* Gets TJ40N_KishMtx Matrix */
 getTJ40N_KishMtx(N_KishMtx);

/* Gets TJ40NcFANshContMtx Matrix */
 getTJ40NcFANshContMtx(NcFANshContMtx);

}

