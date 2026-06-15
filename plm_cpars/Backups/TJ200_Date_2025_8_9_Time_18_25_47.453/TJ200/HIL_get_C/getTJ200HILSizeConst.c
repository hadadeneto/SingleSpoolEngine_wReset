
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ200.h"
#include "../HIL_get_H/getTJ200HILSizeConst.h"



void getTJ200HILSizeConst(int *NcFANMap_Elem, int *WcFANMap_Elem, int *Wc_per_Nc_FAN, int *NcHPTMap_Elem, int *PRHPTMap_Elem, 
     int *WcHPTMap_Elem)
{

/* Loads sizes of linearization points */

    *NcFANMap_Elem = TJ200_FAN_NC;

    *NcHPTMap_Elem = TJ200_HPT_NC;

    *PRHPTMap_Elem = TJ200_HPT_PR;

    *WcFANMap_Elem = TJ200_FAN_NC * TJ200_FAN_PR;;

    *WcHPTMap_Elem = TJ200_HPT_NC * TJ200_HPT_PR;

    *Wc_per_Nc_FAN = TJ200_FAN_PR;

}