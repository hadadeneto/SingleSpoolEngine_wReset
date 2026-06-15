
#include <math.h>
#include "../FADEC_Constants_H/ConstantsGEJ85.h"
#include "../HIL_get_H/getGEJ85HILSizeConst.h"



void getGEJ85HILSizeConst(int *NcFANMap_Elem, int *WcFANMap_Elem, int *Wc_per_Nc_FAN, int *NcHPTMap_Elem, int *PRHPTMap_Elem, 
     int *WcHPTMap_Elem)
{

/* Loads sizes of linearization points */

    *NcFANMap_Elem = GEJ85_FAN_NC;

    *NcHPTMap_Elem = GEJ85_HPT_NC;

    *PRHPTMap_Elem = GEJ85_HPT_PR;

    *WcFANMap_Elem = GEJ85_FAN_NC * GEJ85_FAN_PR;;

    *WcHPTMap_Elem = GEJ85_HPT_NC * GEJ85_HPT_PR;

    *Wc_per_Nc_FAN = GEJ85_FAN_PR;

}