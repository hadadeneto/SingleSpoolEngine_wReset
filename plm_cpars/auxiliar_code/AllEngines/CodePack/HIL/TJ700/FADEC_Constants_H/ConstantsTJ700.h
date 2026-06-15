#ifndef CONSTANTSTJ700_H
#define CONSTANTSTJ700_H

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
#define TJ700_ALT_ELEM				       13
#define TJ700_MN_ELEM 				       11
#define TJ700_FN_ELEM				       12
#define TJ700_TOTAL_ELEM			       1716
#define TJ700_AS_ELEM				       6

/* Components Maps Element Numbers */
#define TJ700_FAN_NC                      10
#define TJ700_FAN_PR                      20
#define TJ700_HPT_NC				       7
#define TJ700_HPT_PR				       21

/* Engine Design Point Constants */
#define TJ700_NDES                        30200
#define TJ700_Ath_NOZZLE                  0.022745

/* Engine Starting Model Parameters */
#define TJ700_VALVE_FUEL				7.76e-3
#define TJ700_FUEL_BOUT				0.005//0.01	//kg/s
#define TJ700_IGN_TIME					1//10		//s
#define TJ700_IGN_DELTAT				900		//K
#define TJ700_POIL						2 * 100000		//Pascals
#define TJ700_RPM_BOUT                 16000   /* RPM - Rotation speed where engine blows out*/

/*-------------------------------------*/
/* ENGINE STARTING ALGORITHM CONSTANTS */
/*-------------------------------------*/

#define TJ700_MANUAL	1
#define TJ700_CLOOP	1
#define TJ700_ENGUNITS 1

/* Time Parameters */
#define TJ700_FUEL_IMPULSE_TIME		8//5//2//4 -> At TestBench			//Second
#define TJ700_TIME_LOW_POIL			10			//Second
#define TJ700_TIME_PMIN				2			//Second
#define TJ700_TIME_PMAX				0.5			//Second
#define TJ700_TIME_IGNITION			7//10//7 -> At TestBench			//Second
#define TJ700_TIME_OVERTEMP			5			//Seconds
#define TJ700_TIME_ACCOMODATION		0.4//20			//Seconds
#define TJ700_WAIT_ACTION				2			// second
#define TJ700_WAIT_START_COMMAND       0.6         /* second */
#define TJ700_WAIT_SHUTDOWN_COMMAND    0.6         /* second */
#define TJ700_WAIT_EMERGENCY_COMMAND   0.2         /* second */
#define TJ700_TIME_BEFORE_RAMP			0//5//3-> At  TestBench			//Seconds

/* Valve Parameters */
#define TJ700_VALVE_INIT				7.76e-3		//Percent
#define TJ700_VALVE_TOTAL				7.76e-3		//Percent

/* Rotation Speed Paremeters */
#define TJ700_RPM_VALVE_100			500			//RPM
#define TJ700_RPM_RELAYS_ON			1500//2000		//RPM
#define TJ700_RPM_IGN_OFF				15000//4000//6000 -> At TestBench		//RPM
#define TJ700_RPM_IDLE					17500//18000		//RPM
#define TJ700_RPM_RAMP_CHANGE			5000//6000//9000		//RPM
#define TJ700_RPM_CLSTARTRAMP          350 //400 At TestBench         /* RPM / 5s - Rotation speed ramp value for lower rotation speeds during closed loop engine starting*/
#define TJ700_RPM_CLSTARTRAMPFASTER    700 //400 At TestBench         /* RPM / 5s - Rotation speed ramp value for higher rotation speeds during closed loop engine starting*/
#define TJ700_RPM_CLSTARTMAXREF        19000       //RPM -- This value must be higher than TJ700_RPM_IDLE

/* Temperature Parameters */
#define TJ700_Tt4AV_FLAME_ON			473//573			/* K - Tt4 value considered for ignition detection*/
#define TJ700_Tt4AV_MAX				1140//1043//2000//1150//1300//860//Tt5Av_MAX is 1200 at TestBench		    /* K - Maximum Tt4 average value allowed during start */
#define TJ700_Tt4_CLSAFESTART          1120//1038//1149//1300//790//950     /* K - Safe start temperature value */
#define TJ700_Tt4_CLRAMPCOEF           10//50//2000         /* K / s - Ramp coefficient value for the safe temperature reference during start */
#define TJ700_Tt4_RAMPDECFAST         1173          /* K - Temerature value where fuel decrease ramp, during engine start, becomes faster for better engine protection */

/* Oil Pressure */
#define TJ700_POIL_ALARM				2 * 100000	//Pascals
#define TJ700_POIL_SHUTDOWN			1 * 100000  //Pascals

/* Fuel Parameters */
#define TJ700_FUEL_HIGH_PULSE			0.021//0.06//0.06//0.07 // 0.032 -> At TestBench		// = 0.175 * 0.4 - Absolute - 40% of the maximum fuel flow - CHANGE IF MAXIMUM VALUE IS CHANGED!!!
#define TJ700_FUEL_INIT                0.010//0.008//0.046//0.055//0.05//0.0175 		// = 0.1 * 0.175 - Absolute - 10% of the maximum fuel flow - CHANGE IF MAXIMUM VALUE IS CHANGED!!!
#define TJ700_FUEL_KDSTART             0.00004 /* Derivative term constant for open-loop starting logic - used in FuelIncrease function */
#define TJ700_FUEL_RAMP                0.0012//0.0025//0.003//0.002//0.00175		// = 0.01 * 0.175 - Absolute/Second (1% every second) - CHANGE IF MAXIMUM VALUE IS CHANGED!!!
#define TJ700_FUEL_PERC				0.2 //0.1 -> At TestBench		//Percentual Value
#define TJ700_FUEL_RAMP_LOW			0.0008//0.0006//0.000875//0.000475 // = 0.005 * 0.175 - //Absolute/Second (0.5% every second) - CHANGE IF MAXIMUM VALUE IS CHANGED!!!
#define TJ700_FUEL_RAMP_DEC            -0.0012//-0.0003    /* kg/s^2 - Decreasing fuel ramp constant used during open-loop start logic, FuelIncrease function */
#define TJ700_FUEL_RAMP_DEC_FAST       -0.0024     /* kg/s^2 - Faster decreasing fuel ramp constant used during open-loop start logic, FuelIncrease function */
#define TJ700_FUEL_RAMP_DEC_LOWLIM     0.0033333   /* kg/s - Low fuel limit during use of decreasing fuel ramp */

#define TJ700_ON 						1
#define TJ700_OFF						0

/*----------------------------------------*/
/* ENGINE PI MIN-MAX CONTROLLER CONSTANTS */
/*----------------------------------------*/

/* Engine Limits */
#define TJ700_NMAX						33300//26400
#define TJ700_NMAXREF                  32700//25800
#define TJ700_TT4MAX					1215//1157//1152
#define TJ700_TT4MAXREF                1210//1152
#define TJ700_TT5MAX					995//1005
#define TJ700_TT5MAXREF                995
#define TJ700_SMMIN					5
#define TJ700_RUMIN					1.3e-7//1.1e-7//1.9e-7

/* Maximum Pump Fuel Flow */
#define TJ700_WFMAX					0.1669//0.2835//0.175 //0.2-> At TestBench			//kg/s

/* Controller Constant Gains */
#define TJ700_KPTT4					0.00046391//0.00086391//0
#define TJ700_KITT4					0.00020778//0.00065778//0.00015	//0.00045 //0.001262
#define TJ700_KBN						20000
#define TJ700_KBT						7000//10000
#define TJ700_REFRAMP					500

/*----------------------------------*/
/* ENGINE PERIPHEALS TIME CONSTANTS */
/*----------------------------------*/

#define TJ700_TTCTIMECONST             -0.5//-2      /* Type T Thermocopule time constant - 1st order model */
#define TJ700_PSENSTIMECONST           -10     /* Pressure sensor time constant - 1st order model */
#define TJ700_FUELPUMPTIMECONSTANT     -1.667//-3.33//-2      /* Fuel pump time constant - 1st order model */

/*-----------------------*/
/* ENGINE SENSOR NUMBERS */
/*-----------------------*/

/* Station 2 */
#define TJ700_TS2SENS                  2
/*  Station 3 */
#define TJ700_PS3SENS                  1
/* Station 4 */
#define TJ700_TT4SENS                  3//2 -> 2 at test bench. In this case, protections will fail due to shift on bit indication position
/* Shaft */
#define TJ700_RPMSENS                  2//1 -> 1 at test bench. In this case, protections will fail due to shift on bit indication position
/* Structure */
#define TJ700_VIBRATIONSENS            1
/* Lubrication */
#define TJ700_POILSENS                 1
/* Fuel System */
#define TJ700_PFUELSENS                1

/*----------------------------------------*/
/* ENGINE MINIMUM TRUSTED SENSORS NUMBERS */
/*----------------------------------------*/

/* This number indicates the least number
of sensors to be trusted before the
calculated model values are used to replace
untrusted sensors */

/* Station 2 */
#define TJ700_TS2SENSTRUST             2
/*  Station 3 */
#define TJ700_PS3SENSTRUST             1
/* Station 4 */
#define TJ700_TT4SENSTRUST             2//3
/* Shaft */
#define TJ700_RPMSENSTRUST             1//2

/*--------------------------------------------------*/
/* ENGINE MODEL PARAMETERS OF POIL, PFUEL VIBRATION */
/*--------------------------------------------------*/

#define TJ700_POILMODEL                2.2 * 100000 //Pascals
#define TJ700_PFUELMODEL               80 * 100000  //Pascals
#define TJ700_VIBMODEL                 5   //mm/s

/*---------------------------------------------------------------------*/
/* SENSOR THRESHOLD VALUES IN PERCENT OF STEADY VALUES - MODEL RESIDUAL */
/*---------------------------------------------------------------------*/

#define TJ700_TCTHRESHOLD              0.1     /* Percentual value used for thermocouple bias identification */
#define TJ700_PSTHRESHOLD              0.1     /* Percentual value used for pressure sensor bias identification */
#define TJ700_TS2THRESHOLD             0.02    /* Percentual value used for Ts2 bias identification */
#define TJ700_PT3THRESHOLD             0.1     /* Percentual value used for Pt3 bias identification */
#define TJ700_TT4THRESHOLD             0.1     /* Percentual value used for Tt4 bias identification */
#define TJ700_RPMTHRESHOLD             0.1     /* Percentual value used for RPM bias identification */
#define TJ700_VIBTHRESHOLD             0.2     /* Percentual value used for vibration sensor bias identification - vibration is not modeled */
#define TJ700_POILTHRESHOLD            0.5     /* Percentual value used for POil sensor bias identification */
#define TJ700_PFUELTHRESHOLD           0.5     /* Percentual value used for PFuel sensor bias identification */

/*----------------------------------------------------------*/
/* SENSOR THRESHOLDS FOR SHORT-CIRCUITED AND OPEN-CIRCUITED */
/*----------------------------------------------------------*/

#define TJ700_PSSHORTTHRESH            5000 //Pascals
#define TJ700_PSOPENTHRESH             1000    //Pascals
#define TJ700_RPMSHORTTHRESH           100     //RPM
#define TJ700_RPMOPENTHRESH            100     //RPM
#define TJ700_VIBSHORTTHRESH           70      //mm/s
#define TJ700_VIBOPENTHRESH            1       //mm/s

/*----------------------------------*/
/* ENGINE THERMOCOUPLE FAULT VALUES */
/*----------------------------------*/

#define TJ700_TCSCV                    2100//5000
#define TJ700_TCSCG                    2100//5000
#define TJ700_TCOPEN                   2100//5000

/*-------------------------------------*/
/* ENGINE PRESSURE SENSOR FAULT VALUES */
/*-------------------------------------*/

#define TJ700_PSSHORT                  130 * 100000//200 * 100000 //Pascal
#define TJ700_PFUELSHORT               200 * 100000 //Pascal
#define TJ700_POILSHORT                130 * 100000//200 * 100000 //Pascal
#define TJ700_PSSOPEN                   -1 * 100000 //Pascal
#define TJ700_PFUELOPEN                -20 * 100000//Pascal
#define TJ700_POILOPEN                  -1 * 100000 //Pascal

/*-------------------------------------*/
/* ENGINE PRESSURE SENSOR FAULT VALUES */
/*-------------------------------------*/

#define TJ700_RPMSHORT                  -99 //RPM
#define TJ700_RPMOPEN                   -99 //RPM

/*--------------------------------*/
/* ENGINE RPM SYSTEM FAULT VALUES */
/*--------------------------------*/

#define TJ700_RPMSHLCK                 16000 //RPM   /* RPM value for shaft lock detection */
//#define TJ700_RPMBOUT                 15000 //RPM   /* RPM value for blow out detection */

/*--------------------------------*/
/* ENGINE Pt3 SYSTEM FAULT VALUES */
/*--------------------------------*/

#define TJ700_Pt3SHLCK                 200000 //Pa   /* Pt3 value for shaft lock detection */
#define TJ700_Pt3BOUT                 200000 //Pa   /* Pt3 value for blow out detection */

/*--------------------------------*/
/* ENGINE Tt4 SYSTEM FAULT VALUES */
/*--------------------------------*/

#define TJ700_Tt4BLLCK                 20000 //K
#define TJ700_Tt4SHLCK                 20000 //K   /* Tt4 value for shaft lock detection */
#define TJ700_Tt4BOUT                   500 //k   /* Tt4 value for blow out detection */

/*-------------------------------*/
/* ENGINE FAULT VABRATION VALUES */
/*-------------------------------*/

#define TJ700_VIBSHORT                  65//100 //mm/s
#define TJ700_VIBOPEN                   -6//0 //mm/s
#define TJ700_VIBHIGH                   20 //mm/s

/*--------------------------*/
/* ENGINE POIL FAULT VALUES */
/*--------------------------*/

#define TJ700_POILHIGH                 11 * 100000 //Pascal
#define TJ700_POILLOW                  0.25 * 100000 //Pascal

/*--------------------------*/
/* ENGINE POIL FAULT VALUES */
/*--------------------------*/

#define TJ700_PFUELHIGH                 120 * 100000 //Pascal
#define TJ700_PFUELLOW                   20 * 100000 //Pascal

/*------------------------------------------*/
/* MAXIMUM TIME BEFORE FAIL ANALYSIS STATRT */
/*------------------------------------------*/

#define TJ700_TIME_FAULTANALYSIS       5 /* Seconds */

/*-----------------------------*/
/* MAXIMUM TIME BEFORE FAILING */
/*-----------------------------*/

#define TJ700_TIME_POILHIHG            5 //Seconds
#define TJ700_TIME_POILLOW             5 //Seconds
#define TJ700_TIME_PFUELHIGH           5 //Seconds
#define TJ700_TIME_PFUELLOW            5 //Seconds
#define TJ700_TIME_VIBHIGH             2 //Seconds
#define TJ700_TIME_OVERSPEED           5 //Seconds
#define TJ700_TIME_BEAR0OT             3 //Seconds
#define TJ700_TIME_BEAR1OT             3 //Seconds
#define TJ700_TIME_BEAR2OT             3 //Seconds
//#define TJ700_TIME_OVERTEMP            5 //Seconds
//#define TJ700_TIME_IGNITION           10 //Seconds

/*--------------------------------------------------*/
/* NUMBER OF INTEGRATION STEPS FOR MODEL ESTIMATION */
/*--------------------------------------------------*/

#define TJ700_NUMSTEPS                 10

/*------------------------------------------------------------*/
/* MAXIMUM NUMBER OF INTERACTIONS BEFORE FAULT IDENDIFICATION */
/*------------------------------------------------------------*/

#define TJ700_MAXINTERFAULT            3

/*------------------------------*/
/* NOMINAL SHUT DOWN PARAMETERS */
/*------------------------------*/

#define TJ700_SD_ERRORFRAC 	        0.02
#define TJ700_SD_RMPMIN                16000
#define TJ700_SD_FUELRAMP              0.00875 // 0.000875
#define TJ700_SD_TIME_TORAMP           5   /* s - Time before ramp status becomes active */
#define TJ700_SD_TIME_TOEMERG          10  /* S - Time before emergency shut off is activated */
// #define TJ700_TS2FAULTS                3
// #define TJ700_PT3FAULTS                2
// #define TJ700_TT4FAULTS                3
// #define TJ700_RPMFAULTS                5
// #define TJ700_VIBFAULTS                2
// #define TJ700_POILFAULTS               2
// #define TJ700_PFUELFAULTS              2

/*------------------------------*/
/* STATUS DEFINITION PARAMETERS */
/*------------------------------*/

/* Time parameters */
#define TJ700_TIME_WINDMILL               0.6//10  /* Seconds */
#define TJ700_TIME_READYTOSTART           1//5  /* Seconds */

/* RPM parameters */
#define TJ700_RPM_WINDMILL               500 /* RPM */

/* Fn command parameters */
#define TJ700_FN_IDLE                    1500//2000 /* N */                  /* Value, in Newtons, of initial engine thrust in idle state */

/*---------------------------------------------*/
/* EXTERNAL START/SHUT DOWN/EMERGENCY COMMANDS */
/*---------------------------------------------*/

#define TJ700_COMMAND_START            0xAA
#define TJ700_COMMAND_SHUTDOWN         0x00
#define TJ700_COMMAND_EMERGENCY        0xCC

/*---------------*/
/* BEARINGS DATA */
/*---------------*/

#define TJ700_BEAR_KP                  -120//-600//-500//-43//-17.989540587756;       /* Ki gain for bearing temperature control */
#define TJ700_BEAR_KI                  -60//-300//-250//-20//-9.91310539505054;      /* Kp gain for bearing temperature control */
#define TJ700_BEAR_KB                  -0.08//-0.04//-0.002//-2.7794e-02//-2.7794e-02             /* Kb value for bearing temp. control - Kb = 0.1/Ki/Ts */
#define TJ700_BEAR_NUM                 3                       /* Number of bearings at the engine */
#define TJ700_BEAR_OPRPMINT            2200    /* RPM - Intermediate oil pump rotation speed */
#define TJ700_BEAR_OPRPMMAX            9000//4500 /* RPM */          /* Maximum oil pump RPM value */
#define TJ700_BEAR_OPRPMMIN            1100//300 /* RPM */          /* Minimum oil pump RPM value */
#define TJ700_BEAR_RPMOILINT           15000 /* RPM - Engine rotation speed value where intermediate value of oil pump is used as minimum */
#define TJ700_BEAR_RPMOILON            4000//1000    /* RPM - engine rotation speed value below which oil pump is shut down */
#define TJ700_BEAR_TMAX_0              473//433  /* K */            /* Maximum bearing 0 allowed temperature */
#define TJ700_BEAR_TMAX_1              463//473  /* K */            /* Maximum bearing 1 allowed temperature */
#define TJ700_BEAR_TMAX_2              473  /* K */            /* Maximum bearing 2 allowed temperature */
#define TJ700_BEAR_TREF_0              448//438//423//400//423  /* K */            /* Bearing 0 reference temperature */
#define TJ700_BEAR_TREF_1              433//423//413//463  /* K */            /* Bearing 1 reference temperature */
#define TJ700_BEAR_TREF_2              448//438//423//413//463  /* K */            /* Bearing 2 reference temperature */

/*-------------------*/
/* BOOSTER CONSTANTS */
/*-------------------*/

#define TJ700_BOOST_TIME               5 /* s - Time between boosters release and activation of blow out protection */

/*---------------------------------*/
/* ELCTRIC MOTOR STARTER CONSTANTS */
/*---------------------------------*/

#define TJ700_STRTINIT                 5       /* PWM duty cycle for electric motor starting in case it exists */
#define TJ700_STRTMAX                  50      /* Maximum value of PWM duty cycle for electric motor starter */
#define TJ700_STRTRAMPCOEFF            2       /* Ramp coefficient for electric motor acceleration during start */
#define TJ700_STRTRPMOFF               13000   /* Rotation speed where the electric motor is deactivated during engine start */
#define TJ700_STRTWHICH                1       /* Defines the statrting logic to be used: 1 - windmill; 2 - electric motor starter */

/*-------------------------------------------------------------------------------------*/
/* ADDITIONAL PARAMETERS PRESENT IN OLDER VERSION - USE DURING SOFTWARE MIGRATION ONLY */
/*-------------------------------------------------------------------------------------*/

/* Temperature Parameters */
#define TJ700_Tt5AV_FLAME_ON			573			//K
#define TJ700_Tt5AV_MAX				860			//K

/*-------------------------------------------------------------------------------------*/

#endif  /* CONSTANTSTJ700_H */
