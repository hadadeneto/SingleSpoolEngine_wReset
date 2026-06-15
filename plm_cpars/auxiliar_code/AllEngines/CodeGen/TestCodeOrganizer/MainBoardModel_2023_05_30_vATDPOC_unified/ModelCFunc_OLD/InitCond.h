#ifndef INITCOND_H
#define INITCOND_H

// void InitCond(int *SkipStartP, int Total_Elem, int MN_Elem, int Fn_Elem, double Altitude, double MN, double dT, double NDes, double FNpc0, struct AmbientPars *AmbientP, double *MNLinVecP, double *FNperContMtxP, 
// 			  double *NcFANContMtxP, double *WfMtxP, double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP, struct EngineOutput *EngOutputP);

void InitCond(int *SkipStartP, int Total_Elem, int MN_Elem, int Fn_Elem, double Altitude, double MN, double dT, double NDes, double FNpc0, struct AmbientPars *AmbientP, double *MNLinVecP, double *FNperContMtxP, 
			  double *NcFANContMtxP, double *FNcMaxContMtxP ,double *WfMtxP, double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP, struct EngineOutput *EngOutputP, int EngUnits);

#endif
