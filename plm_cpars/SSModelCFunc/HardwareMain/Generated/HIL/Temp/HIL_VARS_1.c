
	/*===================================================================================*/
	/* DECLARATION OF VARIABLES USED BY HIL SOFTWARE - MUST BE DONE BEFORE MAIN FUNCTION */
	/*===================================================================================*/

	/* --------------------------*/
	/* FADEC AND MODEL VARIABLES */
	/* --------------------------*/

	/* DECLARATION OF STRUCTURES */

    static AllResiduals PFuelRes;                       /* Struct - Residuals calcultaions and treatment */
    static AllResiduals POilRes;                        /* Struct - Residuals calcultaions and treatment */
    static AllResiduals Pt3Res;                         /* Struct - Residuals calcultaions and treatment */
    static AllResiduals RPMRes;                         /* Struct - Residuals calcultaions and treatment */
    static AllResiduals TBearRes;                       /* Struct - Residuals calcultaions and treatment */
    static AllResiduals Ts2Res;                         /* Struct - Residuals calcultaions and treatment */
    static AllResiduals Tt4Res;                         /* Struct - Residuals calcultaions and treatment */
    static AllResiduals VibrationRes;                   /* Struct - Residuals calcultaions and treatment */
    static AllResiduals DefaultRes = {1000000};         /* Struct - Residuals calcultaions and treatment */

    static AmbientPars Ambient;                         /* Struct - Ambient calculations */
    static AmbientPars AmbientEmpty = { 0 };            /* Struct - Ambient calculations */

    static ControllerConstants ContConst;               /* Struct - Controller Constants */
    static ControllerConstants ContConstEmpty = {0};    /* Struct - Controller Constants */

    static ControllerGeneral ContGenOil;                /* Struct - Bearings temperature control */
    static ControllerGeneral ContGenOilCL;              /* Struct - Bearings temperature control */
    static ControllerGeneral ContGenEmpty = {0};        /* Struct - Bearings temperature control */

	static ControllerInput ContInput;                   /* Struct - Controller Inputs */
    static ControllerInput ContInModCL;                 /* Struct - Controller Inputs */
    static ControllerInput ContInputEmpty = {0};        /* Struct - Controller Inputs */

	static ControllerOutput ContOutput;                 /* Struct - Controller outputs */
    static ControllerOutput ContOutModCL;               /* Struct - Controller outputs */
    static ControllerOutput ContOutputEmpty = {0};      /* Struct - Controller outputs */

	static ControlStart ContStart;                      /* Struct - Controller starting parameters */
    static ControlStart ContStModCL;                    /* Struct - Controller starting parameters */
    static ControlStart ContStartEmpty = {0};           /* Struct - Controller starting parameters */

	static EngineOnOff EngOnOff;                        /* Struct - On/Off logic */
	static EngineOnOff EngOnOffEmpty = {0};             /* Struct - On/Off logic */

    static EstimatedPars BlowOutPars;                   /* Struct - Engine model parameters */
    static EstimatedPars ModelPars;                     /* Struct - Engine model parameters */
    static EstimatedPars ModelParsChosen;               /* Struct - Engine model parameters */
    static EstimatedPars ModelParsCL;                   /* Struct - Engine model parameters */
    static EstimatedPars EstParsEmpty = {0};            /* Struct - Engine model parameters */

    static InterpIndex3D Index3D;                       /* Struct - 3D Matrix indexes */
    static InterpIndex3D Index3DEmpty = {0};            /* Struct - 3D Matrix indexes */

    static SensedPars Sensors;                          /* Struct - Sensors values */
    static SensedPars SensorsEmpty = {0};               /* Struct - Sensors values */

    /* DECLARATION OF UNIONS */

	static digital_t digital;                           /* Union - Digital outputs */
    static digital_t digModCL;                          /* Union - Digital outputs */
	static digital_t digitalEmpty = { 0 };              /* Union - Digital outputs */

    static EngineFaults FaultStatus;                    /* Union - Fault Status */
    static EngineFaults FaultWarning;                   /* Union - Fault Warining */
    static EngineFaults FaultEmpty = {0};               /* Union - Fault Status and warning */

    static EngineStatus EngStatus;                      /* Union - Contains engine status */
    static EngineStatus EngStatusEmpty = {0};           /* Union - Contains engine status */

	static FaultDetect CANFault;						/* Union - Fault analysis */
    static FaultDetect ExistFStatus;                    /* Union - General information about sensors faults*/
    static FaultDetect ExistFWarning;                   /* Union - General information about sensors faults*/
    static FaultDetect HardFAuthorize;                  /* Union - General information about sensors faults*/
    static FaultDetect HardFStatus;                     /* Union - General information about sensors faults*/
    static FaultDetect HardFWarning;                    /* Union - General information about sensors faults*/
    static FaultDetect SoftFStatus;                     /* Union - General information about sensors faults*/
    static FaultDetect SoftFWarning;                    /* Union - General information about sensors faults*/
    static FaultDetect TrustAll;                        /* Union - General information about sensors faults*/
    static FaultDetect TrustHard;                       /* Union - General information about sensors faults*/
    static FaultDetect TrustSens;                       /* Union - General information about sensors faults*/
    static FaultDetect FaultDetectEmpty = {0};          /* Union - General information about sensors faults*/

    static keys_t keys;                                 /* Union - Input keys */
    static keys_t keysEmpty = {0};                      /* Union - Input keys */

    static ModelParsFault ModPFault;                    /* Union - Fault analysis */

    static SensorFaults FaultSensAuthorize;             /* Union - Fault analysis */
    static SensorFaults FaultSSens;                     /* Union - Fault analysis */
    static SensorFaults FaultWSens;                     /* Union - Fault analysis */
    static SensorFaults SoftSimFaults;                  /* Union - Thermocouple full scale simulation */
    static SensorFaults FaultSensEmpty = {0};           /* Union - Fault analysis */

    static SystemFaults FaultSSys;                      /* Union - Fault analysis */
    static SystemFaults FaultSysAuthorize;              /* Union - Fault analysis */
    static SystemFaults FaultWSys;                      /* Union - Fault analysis */
    static SystemFaults FaultSysEmpty = {0};            /* Union - Fault analysis */

    static TCFaults Ts2_0;                              /* Union - Contains thermocouple faults*/
    static TCFaults Ts2_1;                              /* Union - Contains thermocouple faults*/
    static TCFaults Tt4_0;                              /* Union - Contains thermocouple faults*/
    static TCFaults Tt4_1;                              /* Union - Contains thermocouple faults*/
    static TCFaults Tt4_2;                              /* Union - Contains thermocouple faults*/
    static TCFaults TB_0;                               /* Union - Contains thermocouple faults*/
    static TCFaults TB_1;                               /* Union - Contains thermocouple faults*/
    static TCFaults TB_2;                               /* Union - Contains thermocouple faults*/

