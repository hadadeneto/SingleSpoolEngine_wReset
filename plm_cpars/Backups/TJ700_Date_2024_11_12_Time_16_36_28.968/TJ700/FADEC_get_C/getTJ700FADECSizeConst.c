
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ700.h"
#include "../FADEC_get_H/getTJ700FADECSizeConst.h"



void getTJ700FADECSizeConst(int *Alt_Elem, int *MN_Elem, int *Fn_Elem, int *AS_Elem, int *SteadyOp_Elem, 
     int *PowerMan_Elem, int *NcHPCMap_Elem, int *WcHPCMap_Elem, int *Wc_per_Nc_HPC)
{

/* Loads sizes of linearization points */

    *AS_Elem = TJ700_AS_ELEM;

    *Alt_Elem = TJ700_ALT_ELEM;

    *Fn_Elem = TJ700_FN_ELEM;

    *MN_Elem = TJ700_MN_ELEM;

    *NcHPCMap_Elem = TJ700_FAN_NC;

    *PowerMan_Elem = TJ700_TOTAL_ELEM;

    *SteadyOp_Elem = TJ700_FN_ELEM *TJ700_MN_ELEM;

    *WcHPCMap_Elem = TJ700_FAN_NC * TJ700_FAN_PR;

    *Wc_per_Nc_HPC = TJ700_FAN_PR;

}