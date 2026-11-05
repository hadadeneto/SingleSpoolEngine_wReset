
#include <math.h>

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../FADEC_get_H/getGET700FADEC.h"

void getGET700FADECMtx(floating *AMtx, floating *ASVec, floating *AltLinVec, floating *BMtx, floating *DSVec, 
     floating *DeltaMtx, floating *FNcMaxContMtx, floating *FNperContMtx, floating *MNLinVec, floating *N_KiMtx, 
     floating *N_KpMtx, floating *NcFANContMtx, floating *NcHPCMapMtx, floating *NcVec, floating *PRHPCMapMtx, 
     floating *Pt3DMtx, floating *Pt3Mtx, floating *Pt5DMtx, floating *Pt5Mtx, floating *Ts0Mtx, 
     floating *Tt4DMtx, floating *Tt4Mtx, floating *Tt5DMtx, floating *Tt5Mtx, floating *WcHPCMapMtx, 
     floating *WfMtx, floating *N_KpshMtx, floating *N_KishMtx, floating *NcFANshContMtx)

{

/* Gets GET700AMtx Matrix */
 getGET700AMtx(AMtx);

/* Gets GET700ASVec Matrix */
 getGET700ASVec(ASVec);

/* Gets GET700AltLinVec Matrix */
 getGET700AltLinVec(AltLinVec);

/* Gets GET700BMtx Matrix */
 getGET700BMtx(BMtx);

/* Gets GET700DSVec Matrix */
 getGET700DSVec(DSVec);

/* Gets GET700DeltaMtx Matrix */
 getGET700DeltaMtx(DeltaMtx);

/* Gets GET700FNcMaxContMtx Matrix */
 getGET700FNcMaxContMtx(FNcMaxContMtx);

/* Gets GET700FNperContMtx Matrix */
 getGET700FNperContMtx(FNperContMtx);

/* Gets GET700MNLinVec Matrix */
 getGET700MNLinVec(MNLinVec);

/* Gets GET700N_KiMtx Matrix */
 getGET700N_KiMtx(N_KiMtx);

/* Gets GET700N_KpMtx Matrix */
 getGET700N_KpMtx(N_KpMtx);

/* Gets GET700NcFANContMtx Matrix */
 getGET700NcFANContMtx(NcFANContMtx);

/* Gets GET700NcHPCMapMtx Matrix */
 getGET700NcHPCMapMtx(NcHPCMapMtx);

/* Gets GET700NcVec Matrix */
 getGET700NcVec(NcVec);

/* Gets GET700PRHPCMapMtx Matrix */
 getGET700PRHPCMapMtx(PRHPCMapMtx);

/* Gets GET700Pt3DMtx Matrix */
 getGET700Pt3DMtx(Pt3DMtx);

/* Gets GET700Pt3Mtx Matrix */
 getGET700Pt3Mtx(Pt3Mtx);

/* Gets GET700Pt5DMtx Matrix */
 getGET700Pt5DMtx(Pt5DMtx);

/* Gets GET700Pt5Mtx Matrix */
 getGET700Pt5Mtx(Pt5Mtx);

/* Gets GET700Ts0Mtx Matrix */
 getGET700Ts0Mtx(Ts0Mtx);

/* Gets GET700Tt4DMtx Matrix */
 getGET700Tt4DMtx(Tt4DMtx);

/* Gets GET700Tt4Mtx Matrix */
 getGET700Tt4Mtx(Tt4Mtx);

/* Gets GET700Tt5DMtx Matrix */
 getGET700Tt5DMtx(Tt5DMtx);

/* Gets GET700Tt5Mtx Matrix */
 getGET700Tt5Mtx(Tt5Mtx);

/* Gets GET700WcHPCMapMtx Matrix */
 getGET700WcHPCMapMtx(WcHPCMapMtx);

/* Gets GET700WfMtx Matrix */
 getGET700WfMtx(WfMtx);

/* Gets GET700N_KpshMtx Matrix */
 getGET700N_KpshMtx(N_KpshMtx);

/* Gets GET700N_KishMtx Matrix */
 getGET700N_KishMtx(N_KishMtx);

/* Gets GET700NcFANshContMtx Matrix */
 getGET700NcFANshContMtx(NcFANshContMtx);

}

