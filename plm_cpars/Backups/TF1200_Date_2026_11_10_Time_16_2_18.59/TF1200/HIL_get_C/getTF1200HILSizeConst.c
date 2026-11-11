
#include <math.h>
#include "../FADEC_Constants_H/ConstantsTF1200.h"
#include "../HIL_get_H/getTF1200HILSizeConst.h"



void getTF1200HILSizeConst(int *NcFANMap_Elem, int *WcFANMap_Elem, int *Wc_per_Nc_FAN, int *NcHPTMap_Elem, int *PRHPTMap_Elem, 
     int *WcHPTMap_Elem)
{

/* Loads sizes of linearization points */

    *NcFANMap_Elem = TF1200_FAN_NC;

    *NcHPTMap_Elem = TF1200_HPT_NC;

    *PRHPTMap_Elem = TF1200_HPT_PR;

    *WcFANMap_Elem = TF1200_FAN_NC * TF1200_FAN_PR;;

    *WcHPTMap_Elem = TF1200_HPT_NC * TF1200_HPT_PR;

    *Wc_per_Nc_FAN = TF1200_FAN_PR;

}