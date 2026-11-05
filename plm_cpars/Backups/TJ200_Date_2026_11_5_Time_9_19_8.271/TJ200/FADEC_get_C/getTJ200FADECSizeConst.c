
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ200.h"
#include "../FADEC_get_H/getTJ200FADECSizeConst.h"



void getTJ200FADECSizeConst(int *Alt_Elem, int *MN_Elem, int *Fn_Elem, int *AS_Elem, int *SteadyOp_Elem, 
     int *PowerMan_Elem, int *NcHPCMap_Elem, int *WcHPCMap_Elem, int *Wc_per_Nc_HPC)
{

/* Loads sizes of linearization points */

    *AS_Elem = TJ200_AS_ELEM;

    *Alt_Elem = TJ200_ALT_ELEM;

    *Fn_Elem = TJ200_FN_ELEM;

    *MN_Elem = TJ200_MN_ELEM;

    *NcHPCMap_Elem = TJ200_FAN_NC;

    *PowerMan_Elem = TJ200_TOTAL_ELEM;

    *SteadyOp_Elem = TJ200_FN_ELEM *TJ200_MN_ELEM;

    *WcHPCMap_Elem = TJ200_FAN_NC * TJ200_FAN_PR;

    *Wc_per_Nc_HPC = TJ200_FAN_PR;

}