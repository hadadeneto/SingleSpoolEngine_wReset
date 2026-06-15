#ifndef CONSTANTSTF1200_H
#define CONSTANTSTF1200_H

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
#define TF1200_ALT_ELEM				       13
#define TF1200_MN_ELEM 				       12
#define TF1200_FN_ELEM				       12
#define TF1200_TOTAL_ELEM			       1872
#define TF1200_AS_ELEM				       6

/* Components Maps Element Numbers */
#define TF1200_FAN_NC                      10
#define TF1200_FAN_PR                      20
#define TF1200_HPT_NC				       7
#define TF1200_HPT_PR				       21

/* Engine Design Point Constants */
#define TF1200_NDES                        26400
#define TF1200_Ath_NOZZLE                  0.039852

/* Engine Starting Model Parameters */
#define TF1200_VALVE_FUEL				7.76e-3
#define TF1200_FUEL_BOUT				0.01	//kg/s
#define TF1200_IGN_TIME					10		//s
#define TF1200_IGN_DELTAT				900		//K
#define TF1200_POIL						2 * 100000		//Pascals
#define TF1200_RPM_BOUT                 16000   /* RPM - Rotation speed where engine blows out*/

/*-------------------------------------*/
/* ENGINE STARTING ALGORITHM CONSTANTS */
/*-------------------------------------*/

#define TF1200_MANUAL	1
#define TF1200_CLOOP	1
#define TF1200_ENGUNITS 1

/* Time Parameters */
#define TF1200_FUEL_IMPULSE_TIME		1			//Second
#define TF1200_TIME_LOW_POIL			10			//Second
#define TF1200_TIME_PMIN				2			//Second
#define TF1200_TIME_PMAX				0.5			//Second
#define TF1200_TIME_IGNITION			10			//Second
#define TF1200_TIME_OVERTEMP			5			//Seconds
#define TF1200_TIME_ACCOMODATION		20			//Seconds
#define TF1200_WAIT_ACTION				2			// second
#define TF1200_WAIT_START_COMMAND       0.6         /* second */
#define TF1200_WAIT_SHUTDOWN_COMMAND    0.6         /* second */
#define TF1200_WAIT_EMERGENCY_COMMAND   0.2         /* second */
#define TF1200_TIME_BEFORE_RAMP			5			//Seconds

/* Valve Parameters */
#define TF1200_VALVE_INIT				7.76e-3		//Percent
#define TF1200_VALVE_TOTAL				7.76e-3		//Percent

/* Rotation Speed Paremeters */
#define TF1200_RPM_VALVE_100			500			//RPM
#define TF1200_RPM_RELAYS_ON			2000		//RPM
#define TF1200_RPM_IGN_OFF				4000		//RPM
#define TF1200_RPM_IDLE					19000		//RPM
#define TF1200_RPM_RAMP_CHANGE			6000		//RPM
#define TF1200_RPM_CLSTARTRAMP          400 //400 At TestBench         /* RPM / 5s - Rotation speed ramp value for lower rotation speeds during closed loop engine starting*/
#define TF1200_RPM_CLSTARTRAMPFASTER    400 //400 At TestBench         /* RPM / 5s - Rotation speed ramp value for higher rotation speeds during closed loop engine starting*/
#define TF1200_RPM_CLSTARTMAXREF        19000       //RPM -- This value must be higher than TF1200_RPM_IDLE

/* Temperature Parameters */
#define TF1200_Tt4AV_FLAME_ON			573			/* K - Tt4 value considered for ignition detection*/
#define TF1200_Tt4AV_MAX				1200//1150	//860	/* K - Maximum Tt4 average value allowed during start */
#define TF1200_Tt4_CLSAFESTART          1180//850//950     /* K - Safe start temperature value */
#define TF1200_Tt4_CLRAMPCOEF           100         /* K / s - Ramp coefficient value for the safe temperature reference during start */
#define TF1200_Tt4_RAMPDECFAST         1173          /* K - Temerature value where fuel decrease ramp, during engine start, becomes faster for better engine protection */

/* Oil Pressure */
#define TF1200_POIL_ALARM				2 * 100000		//Pascals
#define TF1200_POIL_SHUTDOWN			1 * 100000		//Pascals

/* Fuel Parameters */
#define TF1200_FUEL_HIGH_PULSE			0.07		//Absolute
#define TF1200_FUEL_INIT				0.0134		//Absolute
#define TF1200_FUEL_KDSTART             0.00004 /* Derivative term constant for open-loop starting logic - used in FuelIncrease function */
#define TF1200_FUEL_RAMP				0.002		//Absolute/Second
#define TF1200_FUEL_PERC				0.02		//Percentual Value
#define TF1200_FUEL_RAMP_LOW			0.000875 // = 0.005 * 0.175 - //Absolute/Second (0.5% every second) - CHANGE IF MAXIMUM VALUE IS CHANGED!!!
#define TF1200_FUEL_RAMP_DEC            -0.0003    /* Decreasing fuel ramp constant used during open-loop start logic, FuelIncrease function */
#define TF1200_FUEL_RAMP_DEC_FAST       -0.0024     /* kg/s^2 - Faster decreasing fuel ramp constant used during open-loop start logic, FuelIncrease function */
#define TF1200_FUEL_RAMP_DEC_LOWLIM     0.0033333   /* kg/s - Low fuel limit during use of decreasing fuel ramp */

#define TF1200_ON 						1
#define TF1200_OFF						0

/*----------------------------------------*/
/* ENGINE PI MIN-MAX CONTROLLER CONSTANTS */
/*----------------------------------------*/

/* Engine Limits */
#define TF1200_NMAX						30000
#define TF1200_NMAXREF                  29800
#define TF1200_TT4MAX					1150
#define TF1200_TT4MAXREF                1150
#define TF1200_TT5MAX					1005
#define TF1200_TT5MAXREF                1005
#define TF1200_SMMIN					15
#define TF1200_RUMIN					7e-8

/* Maximum Pump Fuel Flow */
#define TF1200_WFMAX					0.2			//kg/s

/* Controller Constant Gains */
#define TF1200_KPTT4					0
#define TF1200_KITT4					0.001
#define TF1200_KBN						50000
#define TF1200_KBT						4000//50000
#define TF1200_REFRAMP					500

/*-------------------------------*/
/* ENGINE SENSORS TIME CONSTANTS */
/*-------------------------------*/

#define TF1200_TTCTIMECONST             -2      /* Type T Thermocopule time constant - 1st order model */
#define TF1200_PSENSTIMECONST           -10     /* Pressure sensor time constant - 1st order model */
#define TF1200_FUELPUMPTIMECONSTANT     -2000//-2      /* Fuel pump time constant - 1st order model */

/*-----------------------*/
/* ENGINE SENSOR NUMBERS */
/*-----------------------*/

/* Station 2 */
#define TF1200_TS2SENS                  2
/*  Station 3 */
#define TF1200_PS3SENS                  1
/* Station 4 */
#define TF1200_TT4SENS                  3
/* Shaft */
#define TF1200_RPMSENS                  2
/* Structure */
#define TF1200_VIBRATIONSENS            1
/* Lubrication */
#define TF1200_POILSENS                 1
/* Fuel System */
#define TF1200_PFUELSENS                1

/*----------------------------------------*/
/* ENGINE MINIMUM TRUSTED SENSORS NUMBERS */
/*----------------------------------------*/

/* This number indicates the least number
of sensors to be trusted before the
calculated model values are used to replace
untrusted sensors */

/* Station 2 */
#define TF1200_TS2SENSTRUST             2
/*  Station 3 */
#define TF1200_PS3SENSTRUST             1
/* Station 4 */
#define TF1200_TT4SENSTRUST             3
/* Shaft */
#define TF1200_RPMSENSTRUST             2

/*--------------------------------------------------*/
/* ENGINE MODEL PARAMETERS OF POIL, PFUEL VIBRATION */
/*--------------------------------------------------*/

#define TF1200_POILMODEL                2.2 * 100000		//Pascals
#define TF1200_PFUELMODEL               80 * 100000		//Pascals
#define TF1200_VIBMODEL                 5   //mm/s

/*---------------------------------------------------------------------*/
/* SENSOR THRESHOLD VALUES IN PERCENT OF STEADY VALUES - MODEL RESIDUAL */
/*---------------------------------------------------------------------*/

#define TF1200_TCTHRESHOLD              0.1     /* Percentual value used for thermocouple bias identification */
#define TF1200_PSTHRESHOLD              0.1     /* Percentual value used for Pt3 bias identification */
#define TF1200_TS2THRESHOLD             0.02    /* Percentual value used for Ts2 bias identification */
#define TF1200_PT3THRESHOLD             0.1     /* Percentual value used for Pt3 bias identification */
#define TF1200_TT4THRESHOLD             0.1     /* Percentual value used for Tt4 bias identification */
#define TF1200_RPMTHRESHOLD             0.1     /* Percentual value used for RPM bias identification */
#define TF1200_VIBTHRESHOLD             0.2     /* Percentual value used for vibration sensor bias identification - vibration is not modeled */
#define TF1200_POILTHRESHOLD            0.5     /* Percentual value used for POil sensor bias identification */
#define TF1200_PFUELTHRESHOLD           0.5     /* Percentual value used for PFuel sensor bias identification */

/*----------------------------------------------------------*/
/* SENSOR THRESHOLDS FOR SHORT-CIRCUITED AND OPEN-CIRCUITED */
/*----------------------------------------------------------*/

#define TF1200_PSSHORTTHRESH            5000 //Pascals
#define TF1200_PSOPENTHRESH             1000    //Pascals
#define TF1200_RPMSHORTTHRESH           100     //RPM
#define TF1200_RPMOPENTHRESH            100     //RPM
#define TF1200_VIBSHORTTHRESH           70      //mm/s
#define TF1200_VIBOPENTHRESH            1       //mm/s

/*----------------------------------*/
/* ENGINE THERMOCOUPLE FAULT VALUES */
/*----------------------------------*/

#define TF1200_TCSCV                    5000
#define TF1200_TCSCG                    5000
#define TF1200_TCOPEN                   5000

/*-------------------------------------*/
/* ENGINE PRESSURE SENSOR FAULT VALUES */
/*-------------------------------------*/

#define TF1200_PSSHORT                  200 * 100000 //Pascal
#define TF1200_PFUELSHORT               200 * 100000 //Pascal
#define TF1200_POILSHORT                200 * 100000 //Pascal
#define TF1200_PSSOPEN                  0
#define TF1200_PFUELOPEN                0
#define TF1200_POILOPEN                 0

/*-------------------------------------*/
/* ENGINE PRESSURE SENSOR FAULT VALUES */
/*-------------------------------------*/

#define TF1200_RPMSHORT                  -99 //RPM
#define TF1200_RPMOPEN                   -99 //RPM

/*--------------------------------*/
/* ENGINE RPM SYSTEM FAULT VALUES */
/*--------------------------------*/

#define TF1200_RPMSHLCK                 16000 //RPM   /* RPM value for shaft lock detection */
//#define TF1200_RPMBOUT                 15000 //RPM   /* RPM value for blow out detection */

/*--------------------------------*/
/* ENGINE Pt3 SYSTEM FAULT VALUES */
/*--------------------------------*/

#define TF1200_Pt3SHLCK                 200000 //Pa   /* Pt3 value for shaft lock detection */
#define TF1200_Pt3BOUT                 200000 //Pa   /* Pt3 value for blow out detection */

/*--------------------------------*/
/* ENGINE Tt4 SYSTEM FAULT VALUES */
/*--------------------------------*/

#define TF1200_Tt4BLLCK                 20000 //K
#define TF1200_Tt4SHLCK                 20000 //K   /* Tt4 value for shaft lock detection */
#define TF1200_Tt4BOUT                   500 //k   /* Tt4 value for blow out detection */

/*-------------------------------*/
/* ENGINE FAULT VABRATION VALUES */
/*-------------------------------*/

#define TF1200_VIBSHORT                100 //mm/s
#define TF1200_VIBOPEN                   0 //mm/s
#define TF1200_VIBHIGH                  20 //mm/s

/*--------------------------*/
/* ENGINE POIL FAULT VALUES */
/*--------------------------*/

#define TF1200_POILHIGH                 4 * 100000 //Pascal
#define TF1200_POILLOW                  0.25 * 100000 //Pascal

/*--------------------------*/
/* ENGINE POIL FAULT VALUES */
/*--------------------------*/

#define TF1200_PFUELHIGH                 120 * 100000 //Pascal
#define TF1200_PFUELLOW                   20 * 100000 //Pascal

/*------------------------------------------*/
/* MAXIMUM TIME BEFORE FAIL ANALYSIS STATRT */
/*------------------------------------------*/

#define TF1200_TIME_FAULTANALYSIS       5 /* Seconds */

/*-----------------------------*/
/* MAXIMUM TIME BEFORE FAILING */
/*-----------------------------*/

#define TF1200_TIME_POILHIHG            5 //Seconds
#define TF1200_TIME_POILLOW             5 //Seconds
#define TF1200_TIME_PFUELHIGH           5 //Seconds
#define TF1200_TIME_PFUELLOW            5 //Seconds
#define TF1200_TIME_VIBHIGH             2 //Seconds
#define TF1200_TIME_OVERSPEED           5 //Seconds
#define TF1200_TIME_BEAR0OT             3 //Seconds
#define TF1200_TIME_BEAR1OT             3 //Seconds
#define TF1200_TIME_BEAR2OT             3 //Seconds
//#define TF1200_TIME_OVERTEMP            5 //Seconds
//#define TF1200_TIME_IGNITION           10 //Seconds

/*--------------------------------------------------*/
/* NUMBER OF INTEGRATION STEPS FOR MODEL ESTIMATION */
/*--------------------------------------------------*/

#define TF1200_NUMSTEPS                 10

/*------------------------------------------------------------*/
/* MAXIMUM NUMBER OF INTERACTIONS BEFORE FAULT IDENDIFICATION */
/*------------------------------------------------------------*/

#define TF1200_MAXINTERFAULT            3

/*------------------------------*/
/* NOMINAL SHUT DOWN PARAMETERS */
/*------------------------------*/

#define TF1200_SD_ERRORFRAC 	        0.02
#define TF1200_SD_RMPMIN                18000
#define TF1200_SD_FUELRAMP              0.000875
#define TF1200_SD_TIME_TORAMP           5   /* s - Time before ramp status becomes active */
#define TF1200_SD_TIME_TOEMERG          10  /* S - Time before emergency shut off is activated */
// #define TF1200_TS2FAULTS                3
// #define TF1200_PT3FAULTS                2
// #define TF1200_TT4FAULTS                3
// #define TF1200_RPMFAULTS                5
// #define TF1200_VIBFAULTS                2
// #define TF1200_POILFAULTS               2
// #define TF1200_PFUELFAULTS              2

/*------------------------------*/
/* STATUS DEFINITION PARAMETERS */
/*------------------------------*/

/* Time parameters */
#define TF1200_TIME_WINDMILL               0.6//10  /* Seconds */
#define TF1200_TIME_READYTOSTART           1//5  /* Seconds */

/* RPM parameters */
#define TF1200_RPM_WINDMILL               500 /* RPM */

/* Fn command parameters */
#define TF1200_FN_IDLE                    2000 /* N */                  /* Value, in Newtons, of initial engine thrust in idle state */

/*---------------------------------------------*/
/* EXTERNAL START/SHUT DOWN/EMERGENCY COMMANDS */
/*---------------------------------------------*/

#define TF1200_COMMAND_START            0xAA
#define TF1200_COMMAND_SHUTDOWN         0x00
#define TF1200_COMMAND_EMERGENCY        0xCC

/*---------------*/
/* BEARINGS DATA */
/*---------------*/

#define TF1200_BEAR_KP                  -600//-500//-43//-17.989540587756;       /* Ki gain for bearing temperature control */
#define TF1200_BEAR_KI                  -300//-250//-20//-9.91310539505054;      /* Kp gain for bearing temperature control */
#define TF1200_BEAR_KB                  -0.002//-2.7794e-02             /* Kb value for bearing temp. control - Kb = 0.1/Ki/Ts */
#define TF1200_BEAR_NUM                 3                       /* Number of bearings at the engine */
#define TF1200_BEAR_OPRPMINT            2200    /* RPM - Intermediate oil pump rotation speed */
#define TF1200_BEAR_OPRPMMAX            9000 /* RPM */          /* Maximum oil pump RPM value */
#define TF1200_BEAR_OPRPMMIN            1500    /* RPM */          /* Minimum oil pump RPM value */
#define TF1200_BEAR_RPMOILINT           15000 /* RPM - Engine rotation speed value where intermediate value of oil pump is used as minimum */
#define TF1200_BEAR_RPMOILON            1000    /* RPM - engine rotation speed value below which oil pump is shut down */
#define TF1200_BEAR_TMAX_0              433  /* K */            /* Maximum bearing 0 allowed temperature */
#define TF1200_BEAR_TMAX_1              473  /* K */            /* Maximum bearing 1 allowed temperature */
#define TF1200_BEAR_TMAX_2              473  /* K */            /* Maximum bearing 2 allowed temperature */
#define TF1200_BEAR_TREF_0              423  /* K */            /* Bearing 0 reference temperature */
#define TF1200_BEAR_TREF_1              463  /* K */            /* Bearing 1 reference temperature */
#define TF1200_BEAR_TREF_2              463  /* K */            /* Bearing 2 reference temperature */

/*-------------------*/
/* BOOSTER CONSTANTS */
/*-------------------*/

#define TF1200_BOOST_TIME               5 /* s - Time between boosters release and activation of blow out protection */

/*---------------------------------*/
/* ELCTRIC MOTOR STARTER CONSTANTS */
/*---------------------------------*/

#define TF1200_STRTINIT                 5       /* PWM duty cycle for electric motor starting in case it exists */
#define TF1200_STRTMAX                  50      /* Maximum value of PWM duty cycle for electric motor starter */
#define TF1200_STRTRAMPCOEFF            2       /* Ramp coefficient for electric motor acceleration during start */
#define TF1200_STRTRPMOFF               13000   /* Rotation speed where the electric motor is deactivated during engine start */
#define TF1200_STRTWHICH                1       /* Defines the statrting logic to be used: 1 - windmill; 2 - electric motor starter */

/*-------------------------------------------------------------------------------------*/
/* ADDITIONAL PARAMETERS PRESENT IN OLDER VERSION - USE DURING SOFTWARE MIGRATION ONLY */
/*-------------------------------------------------------------------------------------*/

/* Temperature Parameters */
#define TF1200_Tt5AV_FLAME_ON			573			//K
#define TF1200_Tt5AV_MAX				860			//K

/*-------------------------------------------------------------------------------------*/


#endif  /* CONSTANTSTF1200_H */
