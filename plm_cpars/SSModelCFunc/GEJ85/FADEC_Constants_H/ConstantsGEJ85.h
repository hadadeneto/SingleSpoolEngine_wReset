#ifndef CONSTANTSGEJ85_H
#define CONSTANTSGEJ85_H

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
#define GEJ85_ALT_ELEM				       13
#define GEJ85_MN_ELEM 				       10
#define GEJ85_FN_ELEM				       18
#define GEJ85_TOTAL_ELEM			       2340
#define GEJ85_AS_ELEM				       6

/* Components Maps Element Numbers */
#define GEJ85_FAN_NC                      7
#define GEJ85_FAN_PR                      11
#define GEJ85_HPT_NC				       7
#define GEJ85_HPT_PR				       21

/* Engine Design Point Constants */
#define GEJ85_NDES                        16540
#define GEJ85_Ath_NOZZLE                  0.062862

/* Engine Starting Model Parameters */
#define GEJ85_VALVE_FUEL				7.76e-3
#define GEJ85_FUEL_BOUT					0.01	//kg/s
#define GEJ85_IGN_TIME					10		//s
#define GEJ85_IGN_DELTAT				900		//K
#define GEJ85_POIL						2		//Bar
#define GEJ85_RPM_BOUT                 10000   /* RPM - Rotation speed where engine blows out*/

/*-------------------------------------*/
/* ENGINE STARTING ALGORITHM CONSTANTS */
/*-------------------------------------*/

#define GEJ85_MANUAL	1
#define GEJ85_CLOOP		1
#define GEJ85_ENGUNITS 1

/* Time Parameters */
#define GEJ85_FUEL_IMPULSE_TIME		1			//Second
#define GEJ85_TIME_LOW_POIL			10			//Second
#define GEJ85_TIME_PMIN				2			//Second
#define GEJ85_TIME_PMAX				0.5			//Second
#define GEJ85_TIME_IGNITION			10			//Second
#define GEJ85_TIME_OVERTEMP			5			//Seconds
#define GEJ85_TIME_ACCOMODATION		20			//Seconds
#define GEJ85_WAIT_ACTION			2			// second
#define GEJ85_WAIT_START_COMMAND       0.6         /* second */
#define GEJ85_WAIT_SHUTDOWN_COMMAND    0.6         /* second */
#define GEJ85_WAIT_EMERGENCY_COMMAND   0.2         /* second */
#define GEJ85_TIME_BEFORE_RAMP		5			//Seconds

/* Valve Parameters */
#define GEJ85_VALVE_INIT			7.76e-3		//Percent
#define GEJ85_VALVE_TOTAL			7.76e-3		//Percent

/* Rotation Speed Paremeters */
#define GEJ85_RPM_VALVE_100			500			//RPM
#define GEJ85_RPM_RELAYS_ON			2000		//RPM
#define GEJ85_RPM_IGN_OFF			4000		//RPM
#define GEJ85_RPM_IDLE				12000		//RPM
#define GEJ85_RPM_RAMP_CHANGE		4000		//RPM
#define GEJ85_RPM_CLSTARTRAMP       500 //400 At TestBench         /* RPM / 5s - Rotation speed ramp value for lower rotation speeds during closed loop engine starting*/
#define GEJ85_RPM_CLSTARTRAMPFASTER 500 //400 At TestBench         /* RPM / 5s - Rotation speed ramp value for higher rotation speeds during closed loop engine starting*/
#define GEJ85_RPM_CLSTARTMAXREF     15000       //RPM -- This value must be higher than GEJ85_RPM_IDLE

/* Temperature Parameters */
#define GEJ85_Tt4AV_FLAME_ON			573		   /* K - Tt4 value considered for ignition detection*/
#define GEJ85_Tt4AV_MAX				860		/* K - Maximum Tt4 average value allowed during start */
#define GEJ85_Tt4_CLSAFESTART          790//950     /* K - Safe start temperature value */
#define GEJ85_Tt4_CLRAMPCOEF           100         /* K / s - Ramp coefficient value for the safe temperature reference during start */
#define GEJ85_Tt4_RAMPDECFAST         1173          /* K - Temerature value where fuel decrease ramp, during engine start, becomes faster for better engine protection */

/* Oil Pressure */
#define GEJ85_POIL_ALARM			2 * 100000	//Pascals
#define GEJ85_POIL_SHUTDOWN			1 * 100000  //Pascals			//Bar

/* Fuel Parameters */
#define GEJ85_FUEL_HIGH_PULSE		0.12		//Absolute
#define GEJ85_FUEL_INIT				0.08		//Absolute
#define GEJ85_FUEL_KDSTART             0.00004 /* Derivative term constant for open-loop starting logic - used in FuelIncrease function */
#define GEJ85_FUEL_RAMP				0.008		//Absolute/Second
#define GEJ85_FUEL_PERC				0.02		//Percentual Value
#define GEJ85_FUEL_RAMP_LOW		0.000875 // = 0.005 * 0.175 - //Absolute/Second (0.5% every second) - CHANGE IF MAXIMUM VALUE IS CHANGED!!!
#define GEJ85_FUEL_RAMP_DEC         -0.0003    /* Decreasing fuel ramp constant used during open-loop start logic, FuelIncrease function */
#define GEJ85_FUEL_RAMP_DEC_FAST       -0.0024     /* kg/s^2 - Faster decreasing fuel ramp constant used during open-loop start logic, FuelIncrease function */
#define GEJ85_FUEL_RAMP_DEC_LOWLIM     0.0033333   /* kg/s - Low fuel limit during use of decreasing fuel ramp */

#define GEJ85_ON 					1
#define GEJ85_OFF					0

/*----------------------------------------*/
/* ENGINE PI MIN-MAX CONTROLLER CONSTANTS */
/*----------------------------------------*/

/* Engine Limits */
#define GEJ85_NMAX					16540
#define GEJ85_NMAXREF               16540
#define GEJ85_TT4MAX				1250
#define GEJ85_TT4MAXREF             1250
#define GEJ85_TT5MAX				1005
#define GEJ85_TT5MAXREF             1005
#define GEJ85_SMMIN					15
#define GEJ85_RUMIN					2.8e-7

/* Maximum Pump Fuel Flow */
#define GEJ85_WFMAX					0.62			//kg/s

/* Controller Constant Gains */
#define GEJ85_KPTT4					0
#define GEJ85_KITT4					0.0039328
#define GEJ85_KBN					20000
#define GEJ85_KBT					1000//10000
#define GEJ85_REFRAMP				500

/*-------------------------------*/
/* ENGINE SENSORS TIME CONSTANTS */
/*-------------------------------*/

#define GEJ85_TTCTIMECONST             -2       /* Type T Thermocopule time constant - 1st order model */
#define GEJ85_PSENSTIMECONST           -10      /* Pressure sensor time constant - 1st order model */
#define GEJ85_FUELPUMPTIMECONSTANT     -2000//-2       /* Fuel pump time constant - 1st order model */

/*-----------------------*/
/* ENGINE SENSOR NUMBERS */
/*-----------------------*/

/* Station 2 */
#define GEJ85_TS2SENS                  2
/*  Station 3 */
#define GEJ85_PS3SENS                  1
/* Station 4 */
#define GEJ85_TT4SENS                  3
/* Shaft */
#define GEJ85_RPMSENS                  2
/* Structure */
#define GEJ85_VIBRATIONSENS            1
/* Lubrication */
#define GEJ85_POILSENS                 1
/* Fuel System */
#define GEJ85_PFUELSENS                1

/*----------------------------------------*/
/* ENGINE MINIMUM TRUSTED SENSORS NUMBERS */
/*----------------------------------------*/

/* This number indicates the least number
of sensors to be trusted before the
calculated model values are used to replace
untrusted sensors */

/* Station 2 */
#define GEJ85_TS2SENSTRUST             2
/*  Station 3 */
#define GEJ85_PS3SENSTRUST             1
/* Station 4 */
#define GEJ85_TT4SENSTRUST             3
/* Shaft */
#define GEJ85_RPMSENSTRUST             2

/*--------------------------------------------------*/
/* ENGINE MODEL PARAMETERS OF POIL, PFUEL VIBRATION */
/*--------------------------------------------------*/

#define GEJ85_POILMODEL                2.2 * 100000 //Pascals
#define GEJ85_PFUELMODEL               80 * 100000  //Pascals
#define GEJ85_VIBMODEL                 5   //mm/s

/*---------------------------------------------------------------------*/
/* SENSOR THRESHOLD VALUES IN PERCENT OF STEADY VALUES - MODEL RESIDUAL */
/*---------------------------------------------------------------------*/

#define GEJ85_TCTHRESHOLD              0.1     /* Percentual value used for thermocouple bias identification */
#define GEJ85_PSTHRESHOLD              0.1     /* Percentual value used for Pt3 bias identification */
#define GEJ85_TS2THRESHOLD             0.02    /* Percentual value used for Ts2 bias identification */
#define GEJ85_PT3THRESHOLD             0.1     /* Percentual value used for Pt3 bias identification */
#define GEJ85_TT4THRESHOLD             0.1     /* Percentual value used for Tt4 bias identification */
#define GEJ85_RPMTHRESHOLD             0.1     /* Percentual value used for RPM bias identification */
#define GEJ85_VIBTHRESHOLD             0.2     /* Percentual value used for vibration sensor bias identification - vibration is not modeled */
#define GEJ85_POILTHRESHOLD            0.5     /* Percentual value used for POil sensor bias identification */
#define GEJ85_PFUELTHRESHOLD           0.5     /* Percentual value used for PFuel sensor bias identification */


/*----------------------------------------------------------*/
/* SENSOR THRESHOLDS FOR SHORT-CIRCUITED AND OPEN-CIRCUITED */
/*----------------------------------------------------------*/

#define GEJ85_PSSHORTTHRESH            5000 //Pascals
#define GEJ85_PSOPENTHRESH             1000    //Pascals
#define GEJ85_RPMSHORTTHRESH           100     //RPM
#define GEJ85_RPMOPENTHRESH            100     //RPM
#define GEJ85_VIBSHORTTHRESH           70      //mm/s
#define GEJ85_VIBOPENTHRESH            1       //mm/s

/*----------------------------------*/
/* ENGINE THERMOCOUPLE FAULT VALUES */
/*----------------------------------*/

#define GEJ85_TCSCV                    5000
#define GEJ85_TCSCG                    5000
#define GEJ85_TCOPEN                   5000

/*-------------------------------------*/
/* ENGINE PRESSURE SENSOR FAULT VALUES */
/*-------------------------------------*/

#define GEJ85_PSSHORT                  200 * 100000 //Pascal
#define GEJ85_PFUELSHORT               200 * 100000 //Pascal
#define GEJ85_POILSHORT                200 * 100000 //Pascal
#define GEJ85_PSSOPEN                  0
#define GEJ85_PFUELOPEN                0
#define GEJ85_POILOPEN                 0

/*-------------------------------------*/
/* ENGINE PRESSURE SENSOR FAULT VALUES */
/*-------------------------------------*/

#define GEJ85_RPMSHORT                  -99 //RPM
#define GEJ85_RPMOPEN                   -99 //RPM

/*--------------------------------*/
/* ENGINE RPM SYSTEM FAULT VALUES */
/*--------------------------------*/

#define GEJ85_RPMSHLCK                 8000 //RPM   /* RPM value for shaft lock detection */
//#define GEJ85_RPMBOUT                 15000 //RPM   /* RPM value for blow out detection */

/*--------------------------------*/
/* ENGINE Pt3 SYSTEM FAULT VALUES */
/*--------------------------------*/

#define GEJ85_Pt3SHLCK                 200000 //Pa   /* Pt3 value for shaft lock detection */
#define GEJ85_Pt3BOUT                 200000 //Pa   /* Pt3 value for blow out detection */

/*--------------------------------*/
/* ENGINE Tt4 SYSTEM FAULT VALUES */
/*--------------------------------*/

#define GEJ85_Tt4BLLCK                 20000 //K
#define GEJ85_Tt4SHLCK                 20000 //K   /* Tt4 value for shaft lock detection */
#define GEJ85_Tt4BOUT                   500 //k   /* Tt4 value for blow out detection */

/*-------------------------------*/
/* ENGINE FAULT VABRATION VALUES */
/*-------------------------------*/

#define GEJ85_VIBSHORT                 100 //mm/s
#define GEJ85_VIBOPEN                    0 //mm/s
#define GEJ85_VIBHIGH                   20 //mm/s

/*--------------------------*/
/* ENGINE POIL FAULT VALUES */
/*--------------------------*/

#define GEJ85_POILHIGH                 4 * 100000 //Pascal
#define GEJ85_POILLOW                  0.25 * 100000 //Pascal

/*--------------------------*/
/* ENGINE POIL FAULT VALUES */
/*--------------------------*/

#define GEJ85_PFUELHIGH                 120 * 100000 //Pascal
#define GEJ85_PFUELLOW                   20 * 100000 //Pascal

/*------------------------------------------*/
/* MAXIMUM TIME BEFORE FAIL ANALYSIS STATRT */
/*------------------------------------------*/

#define GEJ85_TIME_FAULTANALYSIS       5 /* Seconds */

/*-----------------------------*/
/* MAXIMUM TIME BEFORE FAILING */
/*-----------------------------*/

#define GEJ85_TIME_POILHIHG            5 //Seconds
#define GEJ85_TIME_POILLOW             5 //Seconds
#define GEJ85_TIME_PFUELHIGH           5 //Seconds
#define GEJ85_TIME_PFUELLOW            5 //Seconds
#define GEJ85_TIME_VIBHIGH             2 //Seconds
#define GEJ85_TIME_OVERSPEED           5 //Seconds
#define GEJ85_TIME_BEAR0OT             3 //Seconds
#define GEJ85_TIME_BEAR1OT             3 //Seconds
#define GEJ85_TIME_BEAR2OT             3 //Seconds
//#define GEJ85_TIME_OVERTEMP            5 //Seconds
//#define GEJ85_TIME_IGNITION           10 //Seconds

/*--------------------------------------------------*/
/* NUMBER OF INTEGRATION STEPS FOR MODEL ESTIMATION */
/*--------------------------------------------------*/

#define GEJ85_NUMSTEPS                 10

/*------------------------------------------------------------*/
/* MAXIMUM NUMBER OF INTERACTIONS BEFORE FAULT IDENDIFICATION */
/*------------------------------------------------------------*/

#define GEJ85_MAXINTERFAULT            3

/*------------------------------*/
/* NOMINAL SHUT DOWN PARAMETERS */
/*------------------------------*/

#define GEJ85_SD_ERRORFRAC 	        0.02
#define GEJ85_SD_RMPMIN                12000
#define GEJ85_SD_FUELRAMP              0.000875
#define GEJ85_SD_TIME_TORAMP           5   /* s - Time before ramp status becomes active */
#define GEJ85_SD_TIME_TOEMERG          10  /* S - Time before emergency shut off is activated */
// #define GEJ85_TS2FAULTS                3
// #define GEJ85_PT3FAULTS                2
// #define GEJ85_TT4FAULTS                3
// #define GEJ85_RPMFAULTS                5
// #define GEJ85_VIBFAULTS                2
// #define GEJ85_POILFAULTS               2
// #define GEJ85_PFUELFAULTS              2

/*------------------------------*/
/* STATUS DEFINITION PARAMETERS */
/*------------------------------*/

/* Time parameters */
#define GEJ85_TIME_WINDMILL               0.6//10  /* Seconds */
#define GEJ85_TIME_READYTOSTART           1//5  /* Seconds */

/* RPM parameters */
#define GEJ85_RPM_WINDMILL               500 /* RPM */

/* Fn command parameters */
#define GEJ85_FN_IDLE                    2000 /* N */                  /* Value, in Newtons, of initial engine thrust in idle state */

/*---------------------------------------------*/
/* EXTERNAL START/SHUT DOWN/EMERGENCY COMMANDS */
/*---------------------------------------------*/

#define GEJ85_COMMAND_START            0xAA
#define GEJ85_COMMAND_SHUTDOWN         0x00
#define GEJ85_COMMAND_EMERGENCY        0xCC

/*---------------*/
/* BEARINGS DATA */
/*---------------*/

#define GEJ85_BEAR_KP                  -600//-500//-43//-17.989540587756;       /* Ki gain for bearing temperature control */
#define GEJ85_BEAR_KI                  -300//-250//-20//-9.91310539505054;      /* Kp gain for bearing temperature control */
#define GEJ85_BEAR_KB                  -0.002//-2.7794e-02             /* Kb value for bearing temp. control - Kb = 0.1/Ki/Ts */
#define GEJ85_BEAR_NUM                 3                       /* Number of bearings at the engine */
#define GEJ85_BEAR_OPRPMINT            2200    /* RPM - Intermediate oil pump rotation speed */
#define GEJ85_BEAR_OPRPMMAX            9000 /* RPM */          /* Maximum oil pump RPM value */
#define GEJ85_BEAR_OPRPMMIN            1500    /* RPM */          /* Minimum oil pump RPM value */
#define GEJ85_BEAR_RPMOILINT           15000 /* RPM - Engine rotation speed value where intermediate value of oil pump is used as minimum */
#define GEJ85_BEAR_RPMOILON            1000    /* RPM - engine rotation speed value below which oil pump is shut down */
#define GEJ85_BEAR_TMAX_0              433  /* K */            /* Maximum bearing 0 allowed temperature */
#define GEJ85_BEAR_TMAX_1              473  /* K */            /* Maximum bearing 1 allowed temperature */
#define GEJ85_BEAR_TMAX_2              473  /* K */            /* Maximum bearing 2 allowed temperature */
#define GEJ85_BEAR_TREF_0              423  /* K */            /* Bearing 0 reference temperature */
#define GEJ85_BEAR_TREF_1              463  /* K */            /* Bearing 1 reference temperature */
#define GEJ85_BEAR_TREF_2              463  /* K */            /* Bearing 2 reference temperature */

/*-------------------*/
/* BOOSTER CONSTANTS */
/*-------------------*/

#define GEJ85_BOOST_TIME               5 /* s - Time between boosters release and activation of blow out protection */

/*---------------------------------*/
/* ELCTRIC MOTOR STARTER CONSTANTS */
/*---------------------------------*/

#define GEJ85_STRTINIT                 5       /* PWM duty cycle for electric motor starting in case it exists */
#define GEJ85_STRTMAX                  50      /* Maximum value of PWM duty cycle for electric motor starter */
#define GEJ85_STRTRAMPCOEFF            2       /* Ramp coefficient for electric motor acceleration during start */
#define GEJ85_STRTRPMOFF               13000   /* Rotation speed where the electric motor is deactivated during engine start */
#define GEJ85_STRTWHICH                1       /* Defines the statrting logic to be used: 1 - windmill; 2 - electric motor starter */

/*-------------------------------------------------------------------------------------*/
/* ADDITIONAL PARAMETERS PRESENT IN OLDER VERSION - USE DURING SOFTWARE MIGRATION ONLY */
/*-------------------------------------------------------------------------------------*/

/* Temperature Parameters */
#define GEJ85_Tt5AV_FLAME_ON			573			//K
#define GEJ85_Tt5AV_MAX				    860			//K

/*-------------------------------------------------------------------------------------*/


#endif  /* CONSTANTSGEJ85_H */
