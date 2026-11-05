
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTG200.h"
#include "../FADEC_get_H/getTG200FADECSizeConst.h"



void getTG200FADECSizeConst(int *Alt_Elem, int *MN_Elem, int *Fn_Elem, int *AS_Elem, int *SteadyOp_Elem, 
     int *PowerMan_Elem, int *NcHPCMap_Elem, int *WcHPCMap_Elem, int *Wc_per_Nc_HPC)
{

/* Loads sizes of linearization points */

    *AS_Elem = TG200_AS_ELEM;

    *Alt_Elem = TG200_ALT_ELEM;

    *Fn_Elem = TG200_FN_ELEM;

    *MN_Elem = TG200_MN_ELEM;

    *NcHPCMap_Elem = TG200_FAN_NC;

    *PowerMan_Elem = TG200_TOTAL_ELEM;

    *SteadyOp_Elem = TG200_FN_ELEM *TG200_MN_ELEM;

    *WcHPCMap_Elem = TG200_FAN_NC * TG200_FAN_PR;

    *Wc_per_Nc_HPC = TG200_FAN_PR;

}