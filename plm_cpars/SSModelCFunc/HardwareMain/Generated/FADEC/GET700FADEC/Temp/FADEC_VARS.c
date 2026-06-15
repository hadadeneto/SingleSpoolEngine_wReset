
	/* --------------------------*/
	/* FADEC AND MODEL VARIABLES */
	/* --------------------------*/

    /* STRUCTURES */

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

    /* UNIONS */

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

/******** COMMENT START *********/

    /* REQUIRED INITIALIZATIONS */

    SoftSimFaults = FaultSensEmpty;                     /* Union - Thermocouple full scale simulation */

    /* Each union is initiated with null values */
    Ts2_0.TCFaultBits = 0;
    Ts2_1.TCFaultBits = 0;
    Tt4_0.TCFaultBits = 0;
    Tt4_1.TCFaultBits = 0;
    Tt4_2.TCFaultBits = 0;
    TB_0.TCFaultBits = 0;
    TB_1.TCFaultBits = 0;
    TB_2.TCFaultBits = 0;

/******** COMMENT END *********/

	/* VARIABLES */

    /* int TYPE */

    int EngUnits = 1;                                   /* Engineering units for thrust reference*/
    int Ignition = 0;                                   /* Ignition Signal */
    int LeverMode = 1;                                  /* Lever Mode */
    int Mode = 0;                                       /* Operating Mode */

    /* static int TYPE */

	static int BoosterLStatus = 0xFF;					/* Indicates if left booster is connected (0x55 -> boster connected; 0xAA -> boster released) */
	static int BoosterRStatus = 0xFF;					/* Indicates if left booster is connected (0x55 -> boster connected; 0xAA -> boster released) */
    static int ControlPhase = 0;                        /* Controller phase */
    static int CriticalFailure = 0;                     /* Flag indicating critical failure */
    static int Current_key_start = 0;                   /* Start key current value */
    static int EmergencyCommand = 0;                    /* External command for emergency shut-off */
    static int EmergShutDwn = 0;                        /* Flag (internal) indicating emergency shut-off */
    static int IgnitionFail = 0;                        /* Flag indicating ignition failure */
    static int ModelParsStart = 0;                      /* Flag indicating if model parameters initiation is needed */
    static int Old_key_start = 0;                       /* Start key old value */
    static int OnOffCom = 0xFF;                         /* Command for on/off */
    static int Reset = 0;                               /* Reset flag and pulse detection variable */
    static int ResetButton[2] = {0, 0};                 /* String containing reset button states */
    static int ShutDownCommand = 0;                     /* Command for standard shut-Off */
    static int SingleStop = 0;                          /* Flag for single execution of piece of code */
    static int SkipStart = 0;                           /* Flag indicating if starting algorithm is needed */
    static int StartCommand = 0;                        /* Command for engine start */
    static int StartComplete = 0;                       /* Flag indicating that engine start is complete */
    static int StartFaultAnalysis = 0;                  /* Flag indicating that fault analysis must be accomplished */

    /* unsigned int TYPE */

    unsigned int digitalWord = 0;                      /* Word containing digital outputs states */
	unsigned int GPIOIn = 0;                           /* Contains key states in a single number */
	unsigned int KeyBit0 = 1;                          // Igniter   - Input Keys for software in the loop simulation
	unsigned int KeyBit1 = 1;                          // Shut_Off  - Input Keys for software in the loop simulation
	unsigned int KeyBit2 = 0;                          // Scaveng   - Input Keys for software in the loop simulation
	unsigned int KeyBit3 = 1;                          // Oil Pump  - Input Keys for software in the loop simulation
	unsigned int KeyBit4 = 0;                          // AC_Drive  - Input Keys for software in the loop simulation
	unsigned int KeyBit5 = 1;                          // Emergency - Input Keys for software in the loop simulation
	unsigned int KeyBit6 = 0;                          // Mode	    - Input Keys for software in the loop simulation
    unsigned int keysWord = 0;                         /* Word containing external key states */

	/* floating TYPE */

    floating Altitude = 567;                              /* Altitude value */
    floating Delta = 1;                                       /* Delta = Pt2/PSTD - correction parameter */
/******** COMMENT START *********/
    floating dT = 0;                                      /* Day temperature variation */
/******** COMMENT END *********/
    floating FNcMax = 0;                                  /* Maximum allowed corrected net thrust */
    floating FNpc = 0;                                    /* Corrected net thrust */
    floating MemSize = 0;                                 /* Memory occupied by matrices */
    floating MN = 0;                                      /* Flight Mach number value */
	floating OPRPMManual = 0;								/* Manual reference for oil pump rotation speed */
    floating POil = 0;                                    /* Oil pressure */
    floating Pt2 = 101325;                                /* Compressor inlet total pressure */
    floating Pt3 = 101325;                                /* Compressor exhaust total pressure */
    floating Pt3MedVal = 101325;                          /* Pt3 medium value */
    floating RefCAN = 0;                                  /* Reference from CAN */
/******** COMMENT START *********/
//    floating reference = 0.35;                            /* Reference value used initially */
/******** COMMENT END *********/
    floating RPM = 0;                                     /* Engine mechanical rotation speed */
    floating RPMMedVal = 0;                               /* RPM medium value */
    floating TBear[5] = {0,0,0,0,0};                      /* String containing bearings temperatures */
    floating Ts2 = 288.15;                              	/* Compressor inlet static temperature */
    floating Ts2MedVal = 288.15;                          /* Ts2 medium value */
    floating Tt2 = 288.15;                                /* Compressor inlet total temperature */
    floating Tt4 = 288.15;                                /* Combustion chamber total temperature */
    floating Tt4MedVal = 288.15;                          /* Tt4 medium value */
    floating Tt5 = 288.15;                                /* Turbine inlet total temperature */
    floating WaitTime = 0;                                /* Used by general purpose timer */
    floating Wf0 = 0;                                     /* Initial fuel flow value */

    /* static floating TYPE */

	static floating OPRPM = 0;                            /* Oil pump rotation speed */
    static floating Wf = 0;                               /* Fuel flow */

    // /* VARIABLES */

    // /* int TYPE */

    // int EngUnits = 0;                                   /* Engineering units for thrust reference*/
    // int Ignition = 0;                                   /* Ignition Signal */
    // int LeverMode = 1;                                  /* Lever Mode */
    // int Mode = 0;                                       /* Operating Mode */

    // /* static int TYPE */

    // static int ControlPhase = 0;                        /* Controller phase */
    // static int CriticalFailure = 0;                     /* Flag indicating critical failure */
    // static int Current_key_start;                       /* Start key current value */
    // static int EmergencyCommand = 0;                    /* External command for emergency shut-off */
    // static int EmergShutDwn = 0;                        /* Flag (internal) indicating emergency shut-off */
    // static int IgnitionFail = 0;                        /* Flag indicating ignition failure */
    // static int ModelParsStart = 0;                      /* Flag indicating if model parameters initiation is needed */
    // static int Old_key_start;                           /* Start key old value */
    // static int OnOffCom = 0xFF;                         /* Command for on/off */
    // static int Reset = 0;                               /* Reset flag and pulse detection variable */
    // static int ResetButton[2] = {0, 0};                 /* String containing reset button states */
    // static int ShutDownCommand = 0;                     /* Command for standard shut-Off */
    // static int SingleStop = 0;                          /* Flag for single execution of piece of code */
    // static int SkipStart = 0;                           /* Flag indicating if starting algorithm is needed */
    // static int StartCommand = 0;                        /* Command for engine start */
    // static int StartComplete = 0;                       /* Flag indicating that engine start is complete */
    // static int StartFaultAnalysis = 0;                  /* Flag indicating that fault analysis must be accomplished */

    // /* unsigned int TYPE */

    // unsigned int digitalWord;                          /* Word containing digital outputs states */
	// unsigned int GPIOIn = 0;                           /* Contains key states in a single number */
	// unsigned int KeyBit0 = 1;                          // Igniter   - Input Keys for software in the loop simulation
	// unsigned int KeyBit1 = 1;                          // Shut_Off  - Input Keys for software in the loop simulation
	// unsigned int KeyBit2 = 0;                          // Scaveng   - Input Keys for software in the loop simulation
	// unsigned int KeyBit3 = 1;                          // Oil Pump  - Input Keys for software in the loop simulation
	// unsigned int KeyBit4 = 0;                          // AC_Drive  - Input Keys for software in the loop simulation
	// unsigned int KeyBit5 = 1;                          // Emergency - Input Keys for software in the loop simulation
	// unsigned int KeyBit6 = 0;                          // Mode	    - Input Keys for software in the loop simulation
    // unsigned int keysWord;                             /* Word containing external key states */

	// /* floating TYPE */

    // floating Altitude = 0;                                /* Altitude value */
    // floating Delta;                                       /* Delta = Pt2/PSTD - correction parameter */
    // floating dT = 0;                                      /* Day temperature variation */
    // floating FNcMax = 0;                                  /* Maximum allowed corrected net thrust */
    // floating FNpc = 0;                                    /* Corrected net thrust */
    // floating MN = 0;                                      /* Flight Mach number value */
	// floating OPRPMManual = 0;								/* Manual reference for oil pump rotation speed */
    // floating POil = 0;                                    /* Oil pressure */
    // floating Pt2 = 101325;                                /* Compressor inlet total pressure */
    // floating Pt3;                                         /* Compressor exhaust total pressure */
    // floating Pt3MedVal = 0;                               /* Pt3 medium value */
    // floating RefCAN = 0;                                  /* Reference from CAN */
    // floating reference = 0.35;                            /* Reference value used initially */
    // floating RPM;                                         /* Engine mechanical rotation speed */
    // floating RPMMedVal = 0;                               /* RPM medium value */
    // floating TBear[5];                                    /* String containing bearings temperatures */
    // floating Ts2 = 288.15;                                /* Compressor inlet static temperature */
    // floating Ts2MedVal = 288.15;                          /* Ts2 medium value */
    // floating Tt2 = 288.15;                                /* Compressor inlet total temperature */
    // floating Tt4;                                         /* Combustion chamber total temperature */
    // floating Tt4MedVal = 0;                               /* Tt4 medium value */
    // floating Tt5;                                         /* Turbine inlet total temperature */
    // floating WaitTime;                                    /* Used by general purpose timer */
    // floating Wf0;                                         /* Initial fuel flow value */

    // /* static floating TYPE */

    // static floating OPRPM;                                /* Oil pump rotation speed */
    // static floating Wf = 0;                               /* Fuel flow */

    /*-----------------------------------------------------------*/
    /* FADEC VARIABLES - USED ONLY BY FADEC AND NOT BY THE MODEL */
    /*-----------------------------------------------------------*/

    /* int TYPE */

    int Authorize = 0;                                     /* Flag indicating that controller is authorized to perform */
    int Fn_Elem = GET700_FN_ELEM;                      /* Number of net thrust breakpoint elements */
    int MN_Elem = GET700_MN_ELEM;                      /* Number of Mach number breakpoint elements */

    int Alt_Elem;
    int AS_Elem;
    int SteadyOp_Elem;
    int PowerMan_Elem;
    int NcHPCMap_Elem;
    int WcHPCMap_Elem;
    int Wc_per_Nc_HPC;

    /* floating TYPE */

    floating AuxTimer = 0;                                    /* Dummy timer for general purposes */
    floating Ts = 0.001 * TICK;                           /* Sampling Time */

    /* floating TYPE STRINGS */

    // floating AltLinVec[GET700_ALT_ELEM];                      /* Altitude breakpoints */
    // floating AMtx[GET700_MN_ELEM * GET700_FN_ELEM];           /* Model - A matrix */
    // floating ASVec[GET700_AS_ELEM];                           /* Controller - Asceleration schedule (ASVec) break points */
    // floating BMtx[GET700_MN_ELEM * GET700_FN_ELEM];           /* Model - B matrix */
    // floating DeltaMtx[GET700_ALT_ELEM * GET700_MN_ELEM];      /* Controller - Delta matrix */
    // floating DeltaMtx1D[GET700_MN_ELEM];                      /* Auxiliar matrix - Delta */
    // floating DeltaMtx1DH[GET700_MN_ELEM];                     /* Auxiliar matrix - Delta */
    // floating DeltaMtx2D[GET700_ALT_ELEM * GET700_MN_ELEM];    /* Auxiliar matrix - Delta */
    // floating DeltaMtx2DH[GET700_ALT_ELEM * GET700_MN_ELEM];   /* Auxiliar matrix - Delta */
    // floating DSVec[GET700_AS_ELEM];                           /* Controller - Deceleration schedule (DSVec) break points */
    // floating FNcMaxContMtx[GET700_MN_ELEM];                   /* Controller - Maximum corrected net thrust values */
    // floating FNperContMtx[GET700_TOTAL_ELEM];                 /* Controller - net thrust percentual values matrix */
    // floating MapHPC1D[GET700_FAN_PR];                         /* Auxiliar matrix - HPC map */
    // floating MapHPC1DH[GET700_FAN_PR];                        /* Auxiliar matrix - HPC map */
    // floating MapHPC2D[GET700_FAN_NC * GET700_FAN_PR];         /* Auxiliar matrix - HPC map */
    // floating MapHPC2DH[GET700_FAN_NC * GET700_FAN_PR];        /* Auxiliar matrix - HPC map */
    // floating MNLinVec[GET700_MN_ELEM];                        /* Mach number breakpoints */
    // floating Mtx1D[GET700_FN_ELEM];                           /* Auxiliar matrix */
    // floating Mtx1DH[GET700_FN_ELEM];                          /* Auxiliar matrix */
    // floating Mtx2D[GET700_MN_ELEM * GET700_FN_ELEM];          /* Auxiliar matrix */
    // floating Mtx2DH[GET700_MN_ELEM * GET700_FN_ELEM];         /* Auxiliar matrix */
    // floating N_KiMtx[GET700_TOTAL_ELEM];                      /* Controller - Ki matrix of N control law */
    // floating N_KpMtx[GET700_TOTAL_ELEM];                      /* Controller - Kp matrix of N control law */
    // floating NcFANContMtx[GET700_TOTAL_ELEM];                 /* Controller - Fan Nc breakpoints */
    // floating NcHPCMapMtx[GET700_FAN_NC];                      /* Model - Nc break points matrix - HPC map */
    // floating NcVec[GET700_AS_ELEM];                           /* Controller - Nc schedule (for ASVec and DSVec) break points */
    // floating PRHPCMapMtx[GET700_FAN_NC * GET700_FAN_PR];      /* Model - PR break points matrix - HPC map */
    // floating Pt3DMtx[GET700_MN_ELEM * GET700_FN_ELEM];        /* Model - Pt3D matrix */
    // floating Pt3Mtx[GET700_MN_ELEM * GET700_FN_ELEM];         /* Model - Pt3 matrix */
    // floating Pt5DMtx[GET700_MN_ELEM * GET700_FN_ELEM];        /* Model - Pt5D matrix */
    // floating Pt5Mtx[GET700_MN_ELEM * GET700_FN_ELEM];         /* Model - Pt5 matrix */
    // floating Ts0Mtx[GET700_ALT_ELEM];                         /* Controller and Model - Ts0 break points  */
    // floating Ts0Mtx1D[GET700_ALT_ELEM];                       /* Auxiliar matrix - Ts0 */
    // floating Ts0Mtx1DH[GET700_ALT_ELEM];                      /* Auxiliar matrix - Ts0 */
    // floating Ts0Mtx2D[GET700_FN_ELEM];                        /* Auxiliar matrix - Ts0 */
    // floating Ts0Mtx2DH[GET700_FN_ELEM];                       /* Auxiliar matrix - Ts0 */
    // floating Tt4DMtx[GET700_MN_ELEM * GET700_FN_ELEM];        /* Model - Tt4D matrix */
    // floating Tt4Mtx[GET700_MN_ELEM * GET700_FN_ELEM];         /* Model - Tt4 matrix */
    // floating Tt5DMtx[GET700_MN_ELEM * GET700_FN_ELEM];        /* Model - Tt5D matrix */
    // floating Tt5Mtx[GET700_MN_ELEM * GET700_FN_ELEM];         /* Model - Tt5 matrix */
    // floating WcHPCMapMtx[GET700_FAN_NC * GET700_FAN_PR];      /* Model - Wc break points matrix - HPC map */
    // floating WfMtx[GET700_MN_ELEM * GET700_FN_ELEM];          /* Model - Wf matrix */

    // /* floating TYPE POINTERS */

    floating *Teste;

    floating *AltLinVec;                                  /* Controller and Model - Altitude break points  */
    floating *AMtx;                                       /* Model - pointer for A matrix */
    floating *ASVec;                                      /* Controller - Asceleration schedule (ASVec) break points */
    floating *BMtx;                                       /* Model - pointer for B matrix */
    floating *DeltaMtx;                                   /* Controller and Model - Delta break points  */
    floating *DeltaMtx1D;                                 /* Auxiliar matrix - Delta */
    floating *DeltaMtx1DH;                                /* Auxiliar matrix - Delta */
    floating *DeltaMtx2D;                                 /* Auxiliar matrix - Delta */
    floating *DeltaMtx2DH;                                /* Auxiliar matrix - Delta */
    floating *DSVec;                                      /* Controller - Deceleration schedule (DSVec) break points */
    floating *FNcMaxContMtx;                              /* Controller - pointer for maximum net thrust breakpoint values */
    floating *FNperContMtx;                               /* Controller - pointer for net thrust percent breakpoint values */
    floating *MapHPC1D;                                   /* Auxiliar matrix - HPC map */
    floating *MapHPC1DH;                                  /* Auxiliar matrix - HPC map */
    floating *MapHPC2D;                                   /* Auxiliar matrix - HPC map */
    floating *MapHPC2DH;                                  /* Auxiliar matrix - HPC map */
    floating *MNLinVec;                                   /* Controller and Model - Mach number break points */
    floating *Mtx1D;                                      /* Auxiliar matrix */
    floating *Mtx1DH;                                     /* Auxiliar matrix */
    floating *Mtx2D;                                      /* Auxiliar matrix */
    floating *Mtx2DH;                                     /* Auxiliar matrix */
	floating *N_KiMtx;                                    /* Controller - pointer for Ki matrix of N control law */
	floating *N_KishMtx;                                    /* Controller - pointer for Ki matrix of N control law - sub-idle */
    floating *N_KpMtx;                                    /* Controller - pointer for Kp matrix of N control law */
    floating *N_KpshMtx;                                    /* Controller - pointer for Kp matrix of N control law - sub-idle */
    floating *NcFANContMtx;                               /* Controller - pointer for fan Nc breakpoint values */
    floating *NcFANshContMtx;                               /* Controller - pointer for fan Nc breakpoint values - sub-idle */
    floating *NcHPCMapMtx;                                /* Model - pointer for Nc values matrix - HPC map */
    floating *NcVec;                                      /* Controller - Nc schedule (for ASVec and DSVec) break points  */
    floating *PRHPCMapMtx;                                /* Model - pointer for PR values matrix - HPC map */
    floating *Pt3DMtx;                                    /* Model - pointer for Pt3D matrix */
    floating *Pt3Mtx;                                     /* Model - pointer for Pt3 matrix */
    floating *Pt5DMtx;                                    /* Model - pointer for Pt5D matrix */
    floating *Pt5Mtx;                                     /* Model - pointer for Pt5 matrix */
    floating *Ts0Mtx;                                     /* Controller and Model - pointer Ts0 break points  */
    floating *Ts0Mtx1D;                                   /* Auxiliar matrix - Ts0 */
    floating *Ts0Mtx1DH;                                  /* Auxiliar matrix - Ts0 */
    floating *Ts0Mtx2D;                                   /* Auxiliar matrix - Ts0 */
    floating *Ts0Mtx2DH;                                  /* Auxiliar matrix - Ts0 */
    floating *Tt4DMtx;                                    /* Model - pointer for Tt4D matrix */
    floating *Tt4Mtx;                                     /* Model - pointer for Tt4 matrix */
    floating *Tt5DMtx;                                    /* Model - pointer for Tt5D matrix */
    floating *Tt5Mtx;                                     /* Model - pointer for Tt5 matrix */
    floating *WcHPCMapMtx;                                /* Model - pointer for Wc values matrix - HPC map */
    floating *WfMtx;

