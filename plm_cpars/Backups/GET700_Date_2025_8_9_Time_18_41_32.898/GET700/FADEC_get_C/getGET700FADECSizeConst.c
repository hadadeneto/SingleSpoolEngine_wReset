
#include <math.h>
#include "../FADEC_Constants_H/ConstantsGET700.h"
#include "../FADEC_get_H/getGET700FADECSizeConst.h"



void getGET700FADECSizeConst(int *Alt_Elem, int *MN_Elem, int *Fn_Elem, int *AS_Elem, int *SteadyOp_Elem, 
     int *PowerMan_Elem, int *NcHPCMap_Elem, int *WcHPCMap_Elem, int *Wc_per_Nc_HPC)
{

/* Loads sizes of linearization points */

    *AS_Elem = GET700_AS_ELEM;

    *Alt_Elem = GET700_ALT_ELEM;

    *Fn_Elem = GET700_FN_ELEM;

    *MN_Elem = GET700_MN_ELEM;

    *NcHPCMap_Elem = GET700_FAN_NC;

    *PowerMan_Elem = GET700_TOTAL_ELEM;

    *SteadyOp_Elem = GET700_FN_ELEM *GET700_MN_ELEM;

    *WcHPCMap_Elem = GET700_FAN_NC * GET700_FAN_PR;

    *Wc_per_Nc_HPC = GET700_FAN_PR;

}