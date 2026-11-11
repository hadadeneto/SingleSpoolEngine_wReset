
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ300R.h"
#include "../HIL_get_H/getTJ300RHILSizeConst.h"



void getTJ300RHILSizeConst(int *NcFANMap_Elem, int *WcFANMap_Elem, int *Wc_per_Nc_FAN, int *NcHPTMap_Elem, int *PRHPTMap_Elem, 
     int *WcHPTMap_Elem)
{

/* Loads sizes of linearization points */

    *NcFANMap_Elem = TJ300R_FAN_NC;

    *NcHPTMap_Elem = TJ300R_HPT_NC;

    *PRHPTMap_Elem = TJ300R_HPT_PR;

    *WcFANMap_Elem = TJ300R_FAN_NC * TJ300R_FAN_PR;;

    *WcHPTMap_Elem = TJ300R_HPT_NC * TJ300R_HPT_PR;

    *Wc_per_Nc_FAN = TJ300R_FAN_PR;

}