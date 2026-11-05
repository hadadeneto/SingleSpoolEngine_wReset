
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ300AR.h"
#include "../FADEC_get_H/getTJ300ARFADECSizeConst.h"



void getTJ300ARFADECSizeConst(int *Alt_Elem, int *MN_Elem, int *Fn_Elem, int *AS_Elem, int *SteadyOp_Elem, 
     int *PowerMan_Elem, int *NcHPCMap_Elem, int *WcHPCMap_Elem, int *Wc_per_Nc_HPC)
{

/* Loads sizes of linearization points */

    *AS_Elem = TJ300AR_AS_ELEM;

    *Alt_Elem = TJ300AR_ALT_ELEM;

    *Fn_Elem = TJ300AR_FN_ELEM;

    *MN_Elem = TJ300AR_MN_ELEM;

    *NcHPCMap_Elem = TJ300AR_FAN_NC;

    *PowerMan_Elem = TJ300AR_TOTAL_ELEM;

    *SteadyOp_Elem = TJ300AR_FN_ELEM *TJ300AR_MN_ELEM;

    *WcHPCMap_Elem = TJ300AR_FAN_NC * TJ300AR_FAN_PR;

    *Wc_per_Nc_HPC = TJ300AR_FAN_PR;

}