
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTF1200.h"
#include "../FADEC_get_H/getTF1200FADECSizeConst.h"



void getTF1200FADECSizeConst(int *Alt_Elem, int *MN_Elem, int *Fn_Elem, int *AS_Elem, int *SteadyOp_Elem, 
     int *PowerMan_Elem, int *NcHPCMap_Elem, int *WcHPCMap_Elem, int *Wc_per_Nc_HPC)
{

/* Loads sizes of linearization points */

    *AS_Elem = TF1200_AS_ELEM;

    *Alt_Elem = TF1200_ALT_ELEM;

    *Fn_Elem = TF1200_FN_ELEM;

    *MN_Elem = TF1200_MN_ELEM;

    *NcHPCMap_Elem = TF1200_FAN_NC;

    *PowerMan_Elem = TF1200_TOTAL_ELEM;

    *SteadyOp_Elem = TF1200_FN_ELEM *TF1200_MN_ELEM;

    *WcHPCMap_Elem = TF1200_FAN_NC * TF1200_FAN_PR;

    *Wc_per_Nc_HPC = TF1200_FAN_PR;

}