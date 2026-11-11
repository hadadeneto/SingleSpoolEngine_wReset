
#include <math.h>
#include "../FADEC_Constants_H/ConstantsGEJ85.h"
#include "../FADEC_get_H/getGEJ85FADECSizeConst.h"



void getGEJ85FADECSizeConst(int *Alt_Elem, int *MN_Elem, int *Fn_Elem, int *AS_Elem, int *SteadyOp_Elem, 
     int *PowerMan_Elem, int *NcHPCMap_Elem, int *WcHPCMap_Elem, int *Wc_per_Nc_HPC)
{

/* Loads sizes of linearization points */

    *AS_Elem = GEJ85_AS_ELEM;

    *Alt_Elem = GEJ85_ALT_ELEM;

    *Fn_Elem = GEJ85_FN_ELEM;

    *MN_Elem = GEJ85_MN_ELEM;

    *NcHPCMap_Elem = GEJ85_FAN_NC;

    *PowerMan_Elem = GEJ85_TOTAL_ELEM;

    *SteadyOp_Elem = GEJ85_FN_ELEM *GEJ85_MN_ELEM;

    *WcHPCMap_Elem = GEJ85_FAN_NC * GEJ85_FAN_PR;

    *Wc_per_Nc_HPC = GEJ85_FAN_PR;

}