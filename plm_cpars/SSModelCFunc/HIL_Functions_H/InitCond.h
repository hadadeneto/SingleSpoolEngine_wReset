#ifndef INITCOND_H
#define INITCOND_H

// void InitCond(int *SkipStartP, int Total_Elem, int MN_Elem, int Fn_Elem, floating Altitude, floating MN, floating dT, floating NDes, floating FNpc0, struct AmbientPars *AmbientP, floating *MNLinVecP, floating *FNperContMtxP, 
// 			  floating *NcFANContMtxP, floating *WfMtxP, floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, struct EngineOutput *EngOutputP);

#include "../FADEC_Defines_H/FloatPoint_Precision.h"

void InitCond(int *SkipStartP, int Total_Elem, int MN_Elem, int Fn_Elem, floating Altitude, floating MN, floating dT, floating NDes, floating FNpc0, struct AmbientPars *AmbientP, floating *MNLinVecP, floating *FNperContMtxP, 
			  floating *NcFANContMtxP, floating *FNcMaxContMtxP ,floating *WfMtxP, floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, struct EngineOutput *EngOutputP, int EngUnits);

#endif
