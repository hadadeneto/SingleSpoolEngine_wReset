
 /*===========================================================*/
 /* INCLUDES REFERENT TO THE SOFTWARE IN THE LOOP STARTS HERE */
 /*===========================================================*/

/*-------------------*/
/* STANDARD INCLUDES */
/*-------------------*/

#include <inttypes.h>
#include <stdint.h>

/*----------------------------------------------*/
/* COMMON INCLUDES - USED BY BOTH FADEC AND HIL */
/*----------------------------------------------*/

#include "FADEC_Defines_H/constants_TMATS.h"        		/* Adapted from T-MATS */
#include "FADEC_Defines_H/Control_Types.h"          		/* Controller calculations */
#include "FADEC_Defines_H/DigitalOutDefs.h"         		/* Controller calculations */
#include "FADEC_Defines_H/Env_SampTime.h"           		/* General Calculations*/
#include "FADEC_Defines_H/FaultSim_Types.h"         		/* Fault analysis */
#include "FADEC_Defines_H/FloatPoint_Precision.h"			/* Defines the size of used floating point */
#include "FADEC_Defines_H/Interpolation_Types.h"    		/* General Calculations*/
#include "FADEC_Defines_H/IO_Types.h"               		/* Controller calculations */
#include "FADEC_Defines_H/Model_Types.h"            		/* Used for model calculations */
#include "FADEC_Functions_H/Ambient_TMATS.h"          		/* Adapted from T-MATS */
#include "FADEC_Functions_H/ControlFunctions.h"       		/* Controller calculations */
#include "FADEC_Functions_H/FailSafeFunctions.h"      		/* Fault analysis */
#include "FADEC_Functions_H/functions_TMATS.h"        		/* Adapted from T-MATS */
// #include "FADEC_Functions_H/LinMtxFunctions.h"        		/* General Calculations*/
#include "FADEC_Functions_H/MtxIntFunctions.h"        		/* General Calculations*/
#include "FADEC_Functions_H/PIMinMaxRF.h"             		/* Controller calculations */
#include "FADEC_Functions_H/ShutDownFunctions.h"      		/* Functions for engine shutting down */
#include "FADEC_Functions_H/StartingFunctions.h"      		/* Functions for engine start */
#include "FADEC_Functions_H/TCFault.h"                		/* Fault analysis */

/* TJ1200 INCLUDES */

#include "TJ1200/FADEC_Constants_H/ConstantsTJ1200.h"
#include "TJ1200/FADEC_get_H/getTJ1200FADEC.h"
#include "TJ1200/FADEC_get_H/getTJ1200FADECContConst.h"		/* Controller Constants */
#include "TJ1200/FADEC_get_H/getTJ1200FADECMtx.h"			/* FADEC matrices */
#include "TJ1200/FADEC_get_H/getTJ1200FADECSizeConst.h"		/* Matrices sizes */

/* TF1200 INCLUDES */

#include "TF1200/FADEC_Constants_H/ConstantsTF1200.h"
#include "TF1200/FADEC_get_H/getTF1200FADEC.h"
#include "TF1200/FADEC_get_H/getTF1200FADECContConst.h"		/* Controller Constants */
#include "TF1200/FADEC_get_H/getTF1200FADECMtx.h"			/* FADEC matrices */
#include "TF1200/FADEC_get_H/getTF1200FADECSizeConst.h"		/* Matrices sizes */

/* GEJ85 INCLUDES */

#include "GEJ85/FADEC_Constants_H/ConstantsGEJ85.h"
#include "GEJ85/FADEC_get_H/getGEJ85FADEC.h"
#include "GEJ85/FADEC_get_H/getGEJ85FADECContConst.h"		/* Controller Constants */
#include "GEJ85/FADEC_get_H/getGEJ85FADECMtx.h"				/* FADEC matrices */
#include "GEJ85/FADEC_get_H/getGEJ85FADECSizeConst.h"		/* Matrices sizes */

/* TJ700 INCLUDES */

#include "TJ700/FADEC_Constants_H/ConstantsTJ700.h"
#include "TJ700/FADEC_get_H/getTJ700FADEC.h"
#include "TJ700/FADEC_get_H/getTJ700FADECContConst.h"		/* Controller Constants */
#include "TJ700/FADEC_get_H/getTJ700FADECMtx.h"				/* FADEC matrices */
#include "TJ700/FADEC_get_H/getTJ700FADECSizeConst.h"		/* Matrices sizes */

/* TJ200 INCLUDES */

#include "TJ200/FADEC_Constants_H/ConstantsTJ200.h"
#include "TJ200/FADEC_get_H/getTJ200FADEC.h"
#include "TJ200/FADEC_get_H/getTJ200FADECContConst.h"		/* Controller Constants */
#include "TJ200/FADEC_get_H/getTJ200FADECMtx.h"				/* FADEC matrices */
#include "TJ200/FADEC_get_H/getTJ200FADECSizeConst.h"		/* FADEC matrices sizes */

/* TJ40 INCLUDES */

#include "TJ40/FADEC_Constants_H/ConstantsTJ40.h"
#include "TJ40/FADEC_get_H/getTJ40FADEC.h"
#include "TJ40/FADEC_get_H/getTJ40FADECContConst.h"		/* Controller Constants */
#include "TJ40/FADEC_get_H/getTJ40FADECMtx.h"				/* FADEC matrices */
#include "TJ40/FADEC_get_H/getTJ40FADECSizeConst.h"		/* FADEC matrices sizes */


/*----------------------------------*/
/* HIL INCLUDES - NOT USED BY FADEC */
/*----------------------------------*/

#include "HIL_Functions_H/BearingModel.h"					/* Bearing model functions */
#include "HIL_Functions_H/EngineModel.h"					/* Funciton for engine model simulation */
#include "HIL_Functions_H/FaultSimFunctions.h"				/* Functions for fault simulations */
#include "HIL_Functions_H/InitCond.h"						/* Funciton for calculating simulation initial conditions */
#include "FADEC_Functions_H/PeripheralDyn.h"				/* Perypherals' dynamics functions */

/* TJ1200 INCLUDES */

#include "TJ1200/HIL_get_H/getTJ1200HIL.h"
#include "TJ1200/HIL_get_H/getTJ1200HILEngConst.h"			/* Engine constants */
#include "TJ1200/HIL_get_H/getTJ1200HILMtx.h"				/* HIL matrices*/
#include "TJ1200/HIL_get_H/getTJ1200HILSizeConst.h"			/* HIL matrices sizes */
#include "TJ1200/HIL_get_H/getTJ1200HILStartPars.h"

/* TF1200 INCLUDES */

#include "TF1200/HIL_get_H/getTF1200HIL.h"
#include "TF1200/HIL_get_H/getTF1200HILEngConst.h"			/* Engine constants */
#include "TF1200/HIL_get_H/getTF1200HILMtx.h"				/* HIL matrices*/
#include "TF1200/HIL_get_H/getTF1200HILSizeConst.h"			/* HIL matrices sizes */
#include "TF1200/HIL_get_H/getTF1200HILStartPars.h"

/* GEJ85 INCLUDES */

#include "GEJ85/HIL_get_H/getGEJ85HIL.h"
#include "GEJ85/HIL_get_H/getGEJ85HILEngConst.h"			/* Engine constants */
#include "GEJ85/HIL_get_H/getGEJ85HILMtx.h"					/* HIL matrices*/
#include "GEJ85/HIL_get_H/getGEJ85HILSizeConst.h"			/* HIL matrices sizes */
#include "GEJ85/HIL_get_H/getGEJ85HILStartPars.h"

/* TJ700 INCLUDES */

#include "TJ700/HIL_get_H/getTJ700HIL.h"
#include "TJ700/HIL_get_H/getTJ700HILEngConst.h"			/* Engine constants */
#include "TJ700/HIL_get_H/getTJ700HILMtx.h"					/* HIL matrices*/
#include "TJ700/HIL_get_H/getTJ700HILSizeConst.h"			/* HIL matrices sizes */
#include "TJ700/HIL_get_H/getTJ700HILStartPars.h"

/* TJ200 INCLUDES */

#include "TJ200/HIL_get_H/getTJ200HIL.h"
#include "TJ200/HIL_get_H/getTJ200HILEngConst.h"			/* Engine constants */
#include "TJ200/HIL_get_H/getTJ200HILMtx.h"					/* HIL matrices*/
#include "TJ200/HIL_get_H/getTJ200HILSizeConst.h"			/* HIL matrices sizes */
#include "TJ200/HIL_get_H/getTJ200HILStartPars.h"

/* TJ40 INCLUDES */

#include "TJ40/HIL_get_H/getTJ40HIL.h"
#include "TJ40/HIL_get_H/getTJ40HILEngConst.h"			/* Engine constants */
#include "TJ40/HIL_get_H/getTJ40HILMtx.h"					/* HIL matrices*/
#include "TJ40/HIL_get_H/getTJ40HILSizeConst.h"			/* HIL matrices sizes */
#include "TJ40/HIL_get_H/getTJ40HILStartPars.h"


