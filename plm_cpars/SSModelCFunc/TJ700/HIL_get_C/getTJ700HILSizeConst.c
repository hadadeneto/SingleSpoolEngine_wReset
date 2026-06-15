
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTJ700.h"
#include "../HIL_get_H/getTJ700HILSizeConst.h"



void getTJ700HILSizeConst(int *NcFANMap_Elem, int *WcFANMap_Elem, int *Wc_per_Nc_FAN, int *NcHPTMap_Elem, int *PRHPTMap_Elem, 
     int *WcHPTMap_Elem)
{

/* Loads sizes of linearization points */

    *NcFANMap_Elem = TJ700_FAN_NC;

    *NcHPTMap_Elem = TJ700_HPT_NC;

    *PRHPTMap_Elem = TJ700_HPT_PR;

    *WcFANMap_Elem = TJ700_FAN_NC * TJ700_FAN_PR;;

    *WcHPTMap_Elem = TJ700_HPT_NC * TJ700_HPT_PR;

    *Wc_per_Nc_FAN = TJ700_FAN_PR;

}