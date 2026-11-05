
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTF300.h"
#include "../FADEC_get_H/getTF300FADECSizeConst.h"



void getTF300FADECSizeConst(int *Alt_Elem, int *MN_Elem, int *Fn_Elem, int *AS_Elem, int *SteadyOp_Elem, 
     int *PowerMan_Elem, int *NcHPCMap_Elem, int *WcHPCMap_Elem, int *Wc_per_Nc_HPC)
{

/* Loads sizes of linearization points */

    *AS_Elem = TF300_AS_ELEM;

    *Alt_Elem = TF300_ALT_ELEM;

    *Fn_Elem = TF300_FN_ELEM;

    *MN_Elem = TF300_MN_ELEM;

    *NcHPCMap_Elem = TF300_FAN_NC;

    *PowerMan_Elem = TF300_TOTAL_ELEM;

    *SteadyOp_Elem = TF300_FN_ELEM *TF300_MN_ELEM;

    *WcHPCMap_Elem = TF300_FAN_NC * TF300_FAN_PR;

    *Wc_per_Nc_HPC = TF300_FAN_PR;

}