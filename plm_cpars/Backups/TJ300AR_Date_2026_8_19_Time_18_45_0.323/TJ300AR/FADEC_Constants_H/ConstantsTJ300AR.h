#ifndef CONSTANTSTJ300AR_H
#define CONSTANTSTJ300AR_H

/*		T-MATS -- constants.h
% *************************************************************************
% written by Jeffryes Chapman bsed on work by Ryan May
% NASA Glenn Research Center, Cleveland, OH
% February 14th, 2013
%
%  This is a file that contains various constants for use in the T-MATS C-code
% *************************************************************************/

/*------------------*/
/* ENGINE CONSTANTS */
/*------------------*/

/* Steady Operating Points Elements Numbers */
#define TJ300AR_ALT_ELEM				       13
#define TJ300AR_MN_ELEM 				       11
#define TJ300AR_FN_ELEM				       12
#define TJ300AR_TOTAL_ELEM			       1716
#define TJ300AR_AS_ELEM				       6

/* Components Maps Element Numbers */
#define TJ300AR_FAN_NC                      8
#define TJ300AR_FAN_PR                      19
#define TJ300AR_HPT_NC				       7
#define TJ300AR_HPT_PR				       21

/* Engine Design Point Constants */
#define TJ300AR_NDES                        58900
#define TJ300AR_Ath_NOZZLE                  0.0089413

/* Engine Starting Model Parameters */
#define TJ300AR_VALVE_FUEL				7.76e-3
#define TJ300AR_FUEL_BOUT                 0.005//0.01	//kg/s
#define TJ300AR_IGN_TIME					1//10		//s
#define TJ300AR_IGN_DELTAT				900		//K
#define TJ300AR_POIL						2 * 100000		//Pascals
#define TJ300AR_RPM_BOUT                  16000   /* RPM - Rotation speed where engine blows out*/

/*-------------------------------------*/
/* ENGINE STARTING ALGORITHM CONSTANTS */
/*-------------------------------------*/

#define TJ300AR_MANUAL                    1
#define TJ300AR_CLOOP                     1
#define TJ300AR_ENGUNITS                  1

/* Time Parameters */
#define TJ300AR_FUEL_IMPULSE_TIME         8//5//2//4 -> At TestBench			//Second
#define TJ300AR_TIME_LOW_POIL             10			//Second
#define TJ300AR_TIME_PMIN                 2			//Second
#define TJ300AR_TIME_PMAX                 0.5			//Second
#define TJ300AR_TIME_IGNITION             7//10//7 -> At TestBench			//Second
#define TJ300AR_TIME_OVERTEMP             5			//Seconds
#define TJ300AR_TIME_ACCOMODATION         0.4//20			//Seconds
#define TJ300AR_WAIT_ACTION				5//2			// second
#define TJ300AR_WAIT_START_COMMAND       0.6         /* second */
#define TJ300AR_WAIT_SHUTDOWN_COMMAND    0.6         /* second */
#define TJ300AR_WAIT_EMERGENCY_COMMAND   0.2         /* second */
#define TJ300AR_TIME_BEFORE_RAMP			5//5//3-> At  TestBench			//Seconds

/* Valve Parameters */
#define TJ300AR_VALVE_INIT				7.76e-3		//Percent
#define TJ300AR_VALVE_TOTAL				7.76e-3		//Percent

/* Rotation Speed Paremeters */
#define TJ300AR_RPM_VALVE_100             500			//RPM
#define TJ300AR_RPM_RELAYS_ON             1500//2000		//RPM
#define TJ300AR_RPM_IGN_OFF				10000//15000//4000//6000 -> At TestBench		//RPM
#define TJ300AR_RPM_IDLE					42000//20000//17500//18000		//RPM
#define TJ300AR_RPM_RAMP_CHANGE			5000//6000//9000		//RPM
#define TJ300AR_RPM_CLSTARTRAMP           350 //400 At TestBench         /* RPM / 5s - Rotation speed ramp value for lower rotation speeds during closed loop engine starting*/
#define TJ300AR_RPM_CLSTARTRAMPFASTER     700 //400 At TestBench         /* RPM / 5s - Rotation speed ramp value for higher rotation speeds during closed loop engine starting*/
#define TJ300AR_RPM_CLSTARTMAXREF         19000       //RPM -- This value must be higher than TJ300AR_RPM_IDLE

/* Temperature Parameters */
#define TJ300AR_Tt4AV_FLAME_ON			373//473//573			/* K - Tt4 value considered for ignition detection*/
#define TJ300AR_Tt4AV_MAX                 1140//1043//2000//1150//1300//860//Tt5Av_MAX is 1200 at TestBench		    /* K - Maximum Tt4 average value allowed during start */
#define TJ300AR_Tt4_CLSAFESTART           1120//1038//1149//1300//790//950     /* K - Safe start temperature value */
#define TJ300AR_Tt4_CLRAMPCOEF            10//50//2000         /* K / s - Ramp coefficient value for the safe temperature reference during start */
#define TJ300AR_Tt4_RAMPDECFAST           1173          /* K - Temerature value where fuel decrease ramp, during engine start, becomes faster for better engine protection */

/* Oil Pressure */
#define TJ300AR_POIL_ALARM				2 * 100000	//Pascals
#define TJ300AR_POIL_SHUTDOWN             1 * 100000  //Pascals

/* Fuel Parameters */
#define TJ300AR_FUEL_HIGH_PULSE			0.1*0.1669//0.021//0.06//0.06//0.07 // 0.032 -> At TestBench		// = 0.175 * 0.4 - Absolute - 40% of the maximum fuel flow - CHANGE IF MAXIMUM VALUE IS CHANGED!!!
#define TJ300AR_FUEL_INIT                 0.1*0.1669//0.010//0.008//0.046//0.055//0.05//0.0175 		// = 0.1 * 0.175 - Absolute - 10% of the maximum fuel flow - CHANGE IF MAXIMUM VALUE IS CHANGED!!!
#define TJ300AR_FUEL_KDSTART              0.00004 /* Derivative term constant for open-loop starting logic - used in FuelIncrease function */
#define TJ300AR_FUEL_RAMP                 0.0012//0.0025//0.003//0.002//0.00175		// = 0.01 * 0.175 - Absolute/Second (1% every second) - CHANGE IF MAXIMUM VALUE IS CHANGED!!!
#define TJ300AR_FUEL_PERC                 0.2 //0.1 -> At TestBench		//Percentual Value
#define TJ300AR_FUEL_RAMP_LOW             0.0008//0.0006//0.000875//0.000475 // = 0.005 * 0.175 - //Absolute/Second (0.5% every second) - CHANGE IF MAXIMUM VALUE IS CHANGED!!!
#define TJ300AR_FUEL_RAMP_DEC            -0.0012//-0.0003    /* kg/s^2 - Decreasing fuel ramp constant used during open-loop start logic, FuelIncrease function */
#define TJ300AR_FUEL_RAMP_DEC_FAST       -0.0024     /* kg/s^2 - Faster decreasing fuel ramp constant used during open-loop start logic, FuelIncrease function */
#define TJ300AR_FUEL_RAMP_DEC_LOWLIM     0.0033333   /* kg/s - Low fuel limit during use of decreasing fuel ramp */

#define TJ300AR_ON 						1
#define TJ300AR_OFF						0

/*----------------------------------------*/
/* ENGINE PI MIN-MAX CONTROLLER CONSTANTS */
/*----------------------------------------*/

/* Engine Limits */
#define TJ300AR_NMAX						72000
#define TJ300AR_NMAXREF                   70000
#define TJ300AR_TT4MAX					1215//1157//1152
#define TJ300AR_TT4MAXREF                 1210//1152
#define TJ300AR_TT5MAX					995//1005
#define TJ300AR_TT5MAXREF                 995
#define TJ300AR_SMMIN                     5
#define TJ300AR_RUMIN                     0//1.6e-7//1.9e-7

/* Maximum Pump Fuel Flow */
#define TJ300AR_WFMAX                     0.1669//0.2835//0.175 //0.2-> At TestBench			//kg/s

/* Controller Constant Gains */
#define TJ300AR_KPTT4                     0.00046391//0.00086391//0
#define TJ300AR_KITT4                     0.00020778//0.00065778//0.00015	//0.00045 //0.001262
#define TJ300AR_KBN						20000
#define TJ300AR_KBT						7000//10000
#define TJ300AR_REFRAMP					500

/*----------------------------------*/
/* ENGINE PERIPHEALS TIME CONSTANTS */
/*----------------------------------*/

#define TJ300AR_TTCTIMECONST             -0.5//-2      /* Type T Thermocopule time constant - 1st order model */
#define TJ300AR_PSENSTIMECONST           -10     /* Pressure sensor time constant - 1st order model */
#define TJ300AR_FUELPUMPTIMECONSTANT     -1.667//-3.33//-2      /* Fuel pump time constant - 1st order model */

/*-----------------------*/
/* ENGINE SENSOR NUMBERS */
/*-----------------------*/

/* Station 2 */
#define TJ300AR_TS2SENS                  2
/*  Station 3 */
#define TJ300AR_PS3SENS                  1
/* Station 4 */
#define TJ300AR_TT4SENS                  3//2 -> 2 at test bench. In this case, protections will fail due to shift on bit indication position
/* Shaft */
#define TJ300AR_RPMSENS                  2//1 -> 1 at test bench. In this case, protections will fail due to shift on bit indication position
/* Structure */
#define TJ300AR_VIBRATIONSENS            1
/* Lubrication */
#define TJ300AR_POILSENS                 1
/* Fuel System */
#define TJ300AR_PFUELSENS                1

/*----------------------------------------*/
/* ENGINE MINIMUM TRUSTED SENSORS NUMBERS */
/*----------------------------------------*/

/* This number indicates the least number
of sensors to be trusted before the
calculated model values are used to replace
untrusted sensors */

/* Station 2 */
#define TJ300AR_TS2SENSTRUST             2
/*  Station 3 */
#define TJ300AR_PS3SENSTRUST             1
/* Station 4 */
#define TJ300AR_TT4SENSTRUST             2//3
/* Shaft */
#define TJ300AR_RPMSENSTRUST             1//2

/*--------------------------------------------------*/
/* ENGINE MODEL PARAMETERS OF POIL, PFUEL VIBRATION */
/*--------------------------------------------------*/

#define TJ300AR_POILMODEL                2.2 * 100000 //Pascals
#define TJ300AR_PFUELMODEL               80 * 100000  //Pascals
#define TJ300AR_VIBMODEL                 5   //mm/s

/*---------------------------------------------------------------------*/
/* SENSOR THRESHOLD VALUES IN PERCENT OF STEADY VALUES - MODEL RESIDUAL */
/*---------------------------------------------------------------------*/

#define TJ300AR_TCTHRESHOLD              0.1     /* Percentual value used for thermocouple bias identification */
#define TJ300AR_PSTHRESHOLD              0.1     /* Percentual value used for pressure sensor bias identification */
#define TJ300AR_TS2THRESHOLD             0.02    /* Percentual value used for Ts2 bias identification */
#define TJ300AR_PT3THRESHOLD             0.1     /* Percentual value used for Pt3 bias identification */
#define TJ300AR_TT4THRESHOLD             0.1     /* Percentual value used for Tt4 bias identification */
#define TJ300AR_RPMTHRESHOLD             0.1     /* Percentual value used for RPM bias identification */
#define TJ300AR_VIBTHRESHOLD             0.2     /* Percentual value used for vibration sensor bias identification - vibration is not modeled */
#define TJ300AR_POILTHRESHOLD            0.5     /* Percentual value used for POil sensor bias identification */
#define TJ300AR_PFUELTHRESHOLD           0.5     /* Percentual value used for PFuel sensor bias identification */

/*----------------------------------------------------------*/
/* SENSOR THRESHOLDS FOR SHORT-CIRCUITED AND OPEN-CIRCUITED */
/*----------------------------------------------------------*/

#define TJ300AR_PSSHORTTHRESH            5000 //Pascals
#define TJ300AR_PSOPENTHRESH             1000    //Pascals
#define TJ300AR_RPMSHORTTHRESH           100     //RPM
#define TJ300AR_RPMOPENTHRESH            100     //RPM
#define TJ300AR_VIBSHORTTHRESH           70      //mm/s
#define TJ300AR_VIBOPENTHRESH            1       //mm/s

/*----------------------------------*/
/* ENGINE THERMOCOUPLE FAULT VALUES */
/*----------------------------------*/

#define TJ300AR_TCSCV                    2100//5000
#define TJ300AR_TCSCG                    2100//5000
#define TJ300AR_TCOPEN                   2100//5000

/*-------------------------------------*/
/* ENGINE PRESSURE SENSOR FAULT VALUES */
/*-------------------------------------*/

#define TJ300AR_PSSHORT                  130 * 100000//200 * 100000 //Pascal
#define TJ300AR_PFUELSHORT               200 * 100000 //Pascal
#define TJ300AR_POILSHORT                130 * 100000//200 * 100000 //Pascal
#define TJ300AR_PSSOPEN                   -1 * 100000 //Pascal
#define TJ300AR_PFUELOPEN                -20 * 100000//Pascal
#define TJ300AR_POILOPEN                  -1 * 100000 //Pascal

/*-------------------------------------*/
/* ENGINE PRESSURE SENSOR FAULT VALUES */
/*-------------------------------------*/

#define TJ300AR_RPMSHORT                  -99 //RPM
#define TJ300AR_RPMOPEN                   -99 //RPM

/*--------------------------------*/
/* ENGINE RPM SYSTEM FAULT VALUES */
/*--------------------------------*/

#define TJ300AR_RPMSHLCK                 16000 //RPM   /* RPM value for shaft lock detection */
//#define TJ300AR_RPMBOUT                 15000 //RPM   /* RPM value for blow out detection */

/*--------------------------------*/
/* ENGINE Pt3 SYSTEM FAULT VALUES */
/*--------------------------------*/

#define TJ300AR_Pt3SHLCK                 200000 //Pa   /* Pt3 value for shaft lock detection */
#define TJ300AR_Pt3BOUT                 200000 //Pa   /* Pt3 value for blow out detection */

/*--------------------------------*/
/* ENGINE Tt4 SYSTEM FAULT VALUES */
/*--------------------------------*/

#define TJ300AR_Tt4BLLCK                 20000 //K
#define TJ300AR_Tt4SHLCK                 20000 //K   /* Tt4 value for shaft lock detection */
#define TJ300AR_Tt4BOUT                   500 //k   /* Tt4 value for blow out detection */

/*-------------------------------*/
/* ENGINE FAULT VABRATION VALUES */
/*-------------------------------*/

#define TJ300AR_VIBSHORT                  65//100 //mm/s
#define TJ300AR_VIBOPEN                   -6//0 //mm/s
#define TJ300AR_VIBHIGH                   20 //mm/s

/*--------------------------*/
/* ENGINE POIL FAULT VALUES */
/*--------------------------*/

#define TJ300AR_POILHIGH                 11 * 100000 //Pascal
#define TJ300AR_POILLOW                  0.25 * 100000 //Pascal

/*--------------------------*/
/* ENGINE POIL FAULT VALUES */
/*--------------------------*/

#define TJ300AR_PFUELHIGH                 120 * 100000 //Pascal
#define TJ300AR_PFUELLOW                   20 * 100000 //Pascal

/*------------------------------------------*/
/* MAXIMUM TIME BEFORE FAIL ANALYSIS STATRT */
/*------------------------------------------*/

#define TJ300AR_TIME_FAULTANALYSIS       5 /* Seconds */

/*-----------------------------*/
/* MAXIMUM TIME BEFORE FAILING */
/*-----------------------------*/

#define TJ300AR_TIME_POILHIHG            5 //Seconds
#define TJ300AR_TIME_POILLOW             5 //Seconds
#define TJ300AR_TIME_PFUELHIGH           5 //Seconds
#define TJ300AR_TIME_PFUELLOW            5 //Seconds
#define TJ300AR_TIME_VIBHIGH             2 //Seconds
#define TJ300AR_TIME_OVERSPEED           5 //Seconds
#define TJ300AR_TIME_BEAR0OT             3 //Seconds
#define TJ300AR_TIME_BEAR1OT             3 //Seconds
#define TJ300AR_TIME_BEAR2OT             3 //Seconds
//#define TJ300AR_TIME_OVERTEMP            5 //Seconds
//#define TJ300AR_TIME_IGNITION           10 //Seconds

/*--------------------------------------------------*/
/* NUMBER OF INTEGRATION STEPS FOR MODEL ESTIMATION */
/*--------------------------------------------------*/

#define TJ300AR_NUMSTEPS                 10

/*------------------------------------------------------------*/
/* MAXIMUM NUMBER OF INTERACTIONS BEFORE FAULT IDENDIFICATION */
/*------------------------------------------------------------*/

#define TJ300AR_MAXINTERFAULT            3

/*------------------------------*/
/* NOMINAL SHUT DOWN PARAMETERS */
/*------------------------------*/

#define TJ300AR_SD_ERRORFRAC             0.02
#define TJ300AR_SD_RMPMIN                16000
#define TJ300AR_SD_FUELRAMP              0.00875 // 0.000875
#define TJ300AR_SD_TIME_TORAMP           5   /* s - Time before ramp status becomes active */
#define TJ300AR_SD_TIME_TOEMERG          10  /* S - Time before emergency shut off is activated */
// #define TJ300AR_TS2FAULTS                3
// #define TJ300AR_PT3FAULTS                2
// #define TJ300AR_TT4FAULTS                3
// #define TJ300AR_RPMFAULTS                5
// #define TJ300AR_VIBFAULTS                2
// #define TJ300AR_POILFAULTS               2
// #define TJ300AR_PFUELFAULTS              2

/*------------------------------*/
/* STATUS DEFINITION PARAMETERS */
/*------------------------------*/

/* Time parameters */
#define TJ300AR_TIME_WINDMILL               0.6//10  /* Seconds */
#define TJ300AR_TIME_READYTOSTART           1//5  /* Seconds */

/* RPM parameters */
#define TJ300AR_RPM_WINDMILL               500 /* RPM */

/* Fn command parameters */
#define TJ300AR_FN_IDLE                    300//2000 /* N */                  /* Value, in Newtons, of initial engine thrust in idle state */

/*---------------------------------------------*/
/* EXTERNAL START/SHUT DOWN/EMERGENCY COMMANDS */
/*---------------------------------------------*/

#define TJ300AR_COMMAND_START            0xAA
#define TJ300AR_COMMAND_SHUTDOWN         0x00
#define TJ300AR_COMMAND_EMERGENCY        0xCC

/*---------------*/
/* BEARINGS DATA */
/*---------------*/

#define TJ300AR_BEAR_KP                  -120//-600//-500//-43//-17.989540587756;       /* Ki gain for bearing temperature control */
#define TJ300AR_BEAR_KI                  -60//-300//-250//-20//-9.91310539505054;      /* Kp gain for bearing temperature control */
#define TJ300AR_BEAR_KB                  -0.08//-0.04//-0.002//-2.7794e-02//-2.7794e-02             /* Kb value for bearing temp. control - Kb = 0.1/Ki/Ts */
#define TJ300AR_BEAR_NUM                 3                       /* Number of bearings at the engine */
#define TJ300AR_BEAR_OPRPMINT            2200    /* RPM - Intermediate oil pump rotation speed */
#define TJ300AR_BEAR_OPRPMMAX            9000//4500 /* RPM */          /* Maximum oil pump RPM value */
#define TJ300AR_BEAR_OPRPMMIN            1100//300 /* RPM */          /* Minimum oil pump RPM value */
#define TJ300AR_BEAR_RPMOILINT           15000 /* RPM - Engine rotation speed value where intermediate value of oil pump is used as minimum */
#define TJ300AR_BEAR_RPMOILON            4000//1000    /* RPM - engine rotation speed value below which oil pump is shut down */
#define TJ300AR_BEAR_TMAX_0              473//433  /* K */            /* Maximum bearing 0 allowed temperature */
#define TJ300AR_BEAR_TMAX_1              463//473  /* K */            /* Maximum bearing 1 allowed temperature */
#define TJ300AR_BEAR_TMAX_2              473  /* K */            /* Maximum bearing 2 allowed temperature */
#define TJ300AR_BEAR_TREF_0              448//438//423//400//423  /* K */            /* Bearing 0 reference temperature */
#define TJ300AR_BEAR_TREF_1              433//423//413//463  /* K */            /* Bearing 1 reference temperature */
#define TJ300AR_BEAR_TREF_2              448//438//423//413//463  /* K */            /* Bearing 2 reference temperature */

/*-------------------*/
/* BOOSTER CONSTANTS */
/*-------------------*/

#define TJ300AR_BOOST_TIME               5 /* s - Time between boosters release and activation of blow out protection */

/*---------------------------------*/
/* ELCTRIC MOTOR STARTER CONSTANTS */
/*---------------------------------*/

#define TJ300AR_STRTINIT                 10//5       /* PWM duty cycle for electric motor starting in case it exists */
#define TJ300AR_STRTMAX                  100      /* Maximum value of PWM duty cycle for electric motor starter */
#define TJ300AR_STRTRAMPCOEFF            8//2       /* Ramp coefficient for electric motor acceleration during start */
#define TJ300AR_STRTRPMOFF               13000   /* Rotation speed where the electric motor is deactivated during engine start */
#define TJ300AR_STRTWHICH                1//2       /* Defines the statrting logic to be used: 1 - windmill; 2 - electric motor starter */

/*--------------------------------------------------------------*/
/* TEMEPRATURE MEASUREMENT TYPE AT COMPRESSOR INLET - STATION 2 */
/*--------------------------------------------------------------*/

/* 0 - Measures Ts2 (local day temperature) */   
/* 1 - Measures Tt2 (total temperature) */
#define TJ300AR_T2TYPE                   0   

/*-------------------------------------------------------------------------------------*/
/* ADDITIONAL PARAMETERS PRESENT IN OLDER VERSION - USE DURING SOFTWARE MIGRATION ONLY */
/*-------------------------------------------------------------------------------------*/

/* Temperature Parameters */
#define TJ300AR_Tt5AV_FLAME_ON			573			//K
#define TJ300AR_Tt5AV_MAX                 860			//K

/*-------------------------------------------------------------------------------------*/

#endif  /* CONSTANTSTJ300AR_H */
