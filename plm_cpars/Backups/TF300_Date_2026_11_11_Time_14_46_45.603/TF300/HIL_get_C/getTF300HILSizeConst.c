
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTF300.h"
#include "../HIL_get_H/getTF300HILSizeConst.h"



void getTF300HILSizeConst(int *NcFANMap_Elem, int *WcFANMap_Elem, int *Wc_per_Nc_FAN, int *NcHPTMap_Elem, int *PRHPTMap_Elem, 
     int *WcHPTMap_Elem)
{

/* Loads sizes of linearization points */

    *NcFANMap_Elem = TF300_FAN_NC;

    *NcHPTMap_Elem = TF300_HPT_NC;

    *PRHPTMap_Elem = TF300_HPT_PR;

    *WcFANMap_Elem = TF300_FAN_NC * TF300_FAN_PR;;

    *WcHPTMap_Elem = TF300_HPT_NC * TF300_HPT_PR;

    *Wc_per_Nc_FAN = TF300_FAN_PR;

}