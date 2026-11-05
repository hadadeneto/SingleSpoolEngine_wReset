
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTG200.h"
#include "../HIL_get_H/getTG200HILSizeConst.h"



void getTG200HILSizeConst(int *NcFANMap_Elem, int *WcFANMap_Elem, int *Wc_per_Nc_FAN, int *NcHPTMap_Elem, int *PRHPTMap_Elem, 
     int *WcHPTMap_Elem)
{

/* Loads sizes of linearization points */

    *NcFANMap_Elem = TG200_FAN_NC;

    *NcHPTMap_Elem = TG200_HPT_NC;

    *PRHPTMap_Elem = TG200_HPT_PR;

    *WcFANMap_Elem = TG200_FAN_NC * TG200_FAN_PR;;

    *WcHPTMap_Elem = TG200_HPT_NC * TG200_HPT_PR;

    *Wc_per_Nc_FAN = TG200_FAN_PR;

}