
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ40.h"
#include "../FADEC_get_H/getTJ40FADECSizeConst.h"



void getTJ40FADECSizeConst(int *Alt_Elem, int *MN_Elem, int *Fn_Elem, int *AS_Elem, int *SteadyOp_Elem, 
     int *PowerMan_Elem, int *NcHPCMap_Elem, int *WcHPCMap_Elem, int *Wc_per_Nc_HPC)
{

/* Loads sizes of linearization points */

    *AS_Elem = TJ40_AS_ELEM;

    *Alt_Elem = TJ40_ALT_ELEM;

    *Fn_Elem = TJ40_FN_ELEM;

    *MN_Elem = TJ40_MN_ELEM;

    *NcHPCMap_Elem = TJ40_FAN_NC;

    *PowerMan_Elem = TJ40_TOTAL_ELEM;

    *SteadyOp_Elem = TJ40_FN_ELEM *TJ40_MN_ELEM;

    *WcHPCMap_Elem = TJ40_FAN_NC * TJ40_FAN_PR;

    *Wc_per_Nc_HPC = TJ40_FAN_PR;

}