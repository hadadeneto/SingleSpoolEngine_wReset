
#include <math.h>
#include "../FADEC_Constants_H/ConstantsGET700.h"
#include "../HIL_get_H/getGET700HILSizeConst.h"



void getGET700HILSizeConst(int *NcFANMap_Elem, int *WcFANMap_Elem, int *Wc_per_Nc_FAN, int *NcHPTMap_Elem, int *PRHPTMap_Elem, 
     int *WcHPTMap_Elem)
{

/* Loads sizes of linearization points */

    *NcFANMap_Elem = GET700_FAN_NC;

    *NcHPTMap_Elem = GET700_HPT_NC;

    *PRHPTMap_Elem = GET700_HPT_PR;

    *WcFANMap_Elem = GET700_FAN_NC * GET700_FAN_PR;;

    *WcHPTMap_Elem = GET700_HPT_NC * GET700_HPT_PR;

    *Wc_per_Nc_FAN = GET700_FAN_PR;

}