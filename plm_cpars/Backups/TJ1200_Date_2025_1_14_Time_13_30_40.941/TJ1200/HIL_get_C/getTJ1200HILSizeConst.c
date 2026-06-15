
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ1200.h"
#include "../HIL_get_H/getTJ1200HILSizeConst.h"



void getTJ1200HILSizeConst(int *NcFANMap_Elem, int *WcFANMap_Elem, int *Wc_per_Nc_FAN, int *NcHPTMap_Elem, int *PRHPTMap_Elem, 
     int *WcHPTMap_Elem)
{

/* Loads sizes of linearization points */

    *NcFANMap_Elem = TJ1200_FAN_NC;

    *NcHPTMap_Elem = TJ1200_HPT_NC;

    *PRHPTMap_Elem = TJ1200_HPT_PR;

    *WcFANMap_Elem = TJ1200_FAN_NC * TJ1200_FAN_PR;;

    *WcHPTMap_Elem = TJ1200_HPT_NC * TJ1200_HPT_PR;

    *Wc_per_Nc_FAN = TJ1200_FAN_PR;

}