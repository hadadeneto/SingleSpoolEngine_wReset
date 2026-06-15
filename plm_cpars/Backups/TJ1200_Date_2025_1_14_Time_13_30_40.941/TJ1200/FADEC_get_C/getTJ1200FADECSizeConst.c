
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ1200.h"
#include "../FADEC_get_H/getTJ1200FADECSizeConst.h"



void getTJ1200FADECSizeConst(int *Alt_Elem, int *MN_Elem, int *Fn_Elem, int *AS_Elem, int *SteadyOp_Elem, 
     int *PowerMan_Elem, int *NcHPCMap_Elem, int *WcHPCMap_Elem, int *Wc_per_Nc_HPC)
{

/* Loads sizes of linearization points */

    *AS_Elem = TJ1200_AS_ELEM;

    *Alt_Elem = TJ1200_ALT_ELEM;

    *Fn_Elem = TJ1200_FN_ELEM;

    *MN_Elem = TJ1200_MN_ELEM;

    *NcHPCMap_Elem = TJ1200_FAN_NC;

    *PowerMan_Elem = TJ1200_TOTAL_ELEM;

    *SteadyOp_Elem = TJ1200_FN_ELEM *TJ1200_MN_ELEM;

    *WcHPCMap_Elem = TJ1200_FAN_NC * TJ1200_FAN_PR;

    *Wc_per_Nc_HPC = TJ1200_FAN_PR;

}