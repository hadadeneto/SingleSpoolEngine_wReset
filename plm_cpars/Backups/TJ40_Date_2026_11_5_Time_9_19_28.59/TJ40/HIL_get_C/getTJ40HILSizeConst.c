
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ40.h"
#include "../HIL_get_H/getTJ40HILSizeConst.h"



void getTJ40HILSizeConst(int *NcFANMap_Elem, int *WcFANMap_Elem, int *Wc_per_Nc_FAN, int *NcHPTMap_Elem, int *PRHPTMap_Elem, 
     int *WcHPTMap_Elem)
{

/* Loads sizes of linearization points */

    *NcFANMap_Elem = TJ40_FAN_NC;

    *NcHPTMap_Elem = TJ40_HPT_NC;

    *PRHPTMap_Elem = TJ40_HPT_PR;

    *WcFANMap_Elem = TJ40_FAN_NC * TJ40_FAN_PR;;

    *WcHPTMap_Elem = TJ40_HPT_NC * TJ40_HPT_PR;

    *Wc_per_Nc_FAN = TJ40_FAN_PR;

}