
	/*===========*/
	/* VARIABLES */
    /*===========*/

/******** COMMENT START *********/
	/* PREVIOUSLY DELCARED IN HARDWARE */

	/*floating TYPE*/

    //floating reference = 0.35;                            /* Reference value used initially */

	/*---------------------------------*/
/******** COMMENT END *********/

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
    floating dT = 0;                                      /* Day temperature variation */
    floating FNcMax = 0;                                  /* Maximum allowed corrected net thrust */
    floating FNpc = 0;                                    /* Corrected net thrust */
    floating MemSize = 0;									/* Memory size occupied by matrices */
	floating MN = 0;                                      /* Flight Mach number value */
	floating OPRPMManual = 0;								/* Manual reference for oil pump rotation speed */
    floating POil = 0;                                    /* Oil pressure */
    floating Pt2 = 101325;                                /* Compressor inlet total pressure */
    floating Pt3 = 101325;                                /* Compressor exhaust total pressure */
    floating Pt3MedVal = 101325;                          /* Pt3 medium value */
    floating RefCAN = 0;                                  /* Reference from CAN */
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

	/*----------------------*/
	/* MODEL ONLY VARIABLES */
	/*----------------------*/

	/* STRUCTURES */

	static EngineOutput EngOutput = { 0 };				/* Struct - Contains engine outputs */
	static EngineOutput EngOutputEmpty = { 0 };			/* Struct - Contains engine outputs */

	static EnginePars EngPars = { 0 };					/* Struct - Contains engine parameters */
	static EnginePars EngParsEmpty = { 0 };				/* Struct - Contains engine parameters */

	static EngineStart Starting;						/* Struct - Contains engine starging parameters */
	static EngineStart StartingEmpty = { 0 };			/* Struct - Contains engine starging parameters */

	static SensedPars SensorBias;						/* Struct - Sensors bias for foult simulation */

	/* UNIONS */

	static EngineFaults Faults;							/* Union - Indicates engine faults to be simulated */

	static FaultDetect SysFaults;						/* Union - Indicates system faults to be simulated  */

	static SensorFaults SensFaults;						/* Union - Sensors faults for foult simulation */

	/* int TYPE */

    int Alt_Elem = 0;                                   	/* Number of altitude elements */
    int AS_Elem = 0;                                    	/* Number of acceleration schedule elements */
    int ExtFPModel = 0;										/* Choses between external or internal fuel pump model */
	int FlightStart = 0;									/* Flag defining ground start or start during flight */
	int Fn_Elem = 0;                                   		/* Number of Fn elements */
    int HILMode = 0;                                    	/* Hardware in the Loop Mode */
    int i = 0;                                          	/* Loop index variable */
    int MN_Elem = 0;                                    	/* Number of Mach number elements */
    int NcFANMap_Elem = 0;                                  /* Number of Nc elements - fan map */
    int NcHPCMap_Elem = 0;                                  /* Number of Nc elements - high power compressor map */
    int NcHPTMap_Elem = 0;                                  /* Number of Nc elements - turbine map */
    int PowerMan_Elem = 0;                                  /* Number of total steady operating points used for Power Management Controller - all altitudes */
    int PRHPTMap_Elem = 0;                                  /* Number of pressure ratio elements - turbine map */
    int SteadyOp_Elem = 0;                                  /* Number of steady operating points used for linearization at Sea Level */
    int TsampDiv = 10;                                  	/* Possibility of lower sampling time for the model */
    int Wc_per_Nc_FAN = 0;                                  /* Number of pressure ratio elements - fan map */
    int Wc_per_Nc_HPC = 0;                                  /* Number of pressure ratio elements - high power compressor map */
    int WcFANMap_Elem = 0;                                  /* Number of Wc elements - fan map */
    int WcHPCMap_Elem = 0;                                  /* Number of Wc elements - high power compressor map */
    int WcHPTMap_Elem = 0;                                  /* Number of Wc elements - turbine map */
    int WhichEngine = 1;                                    /* Flag defining the engine to be simulated */

	/* static int TYPE */

	static int bit_start = 0;								/* Starting flag */

	/* floating TYPE */

	floating BPFAN = 0;                                       /* Fan bypass ratio */
    floating Fg = 0;                                          /* Engine gross thrust */
    floating Fn = 0;                                          /* Engine net thrust */
    floating FNpc0 = 0;                                  		/* Initial percent net thrust reference */
    floating MN8 = 0;                                         /* Nozzle thruat gas Mach number */
    floating Mwm = 0.3;                                   	/* Mach number value for windmill simulation - currently used as 0.3 */
    floating NcFAN = 0;                                       /* Fan corrected rotation speed */
    floating NcHPC = 0;                                       /* Compressor corrected rotation speed */
    floating P0 = 101325;                                     /* Ambient pressure */
    floating PRFAN = 1;                                       /* Fan pressure ratio */
    floating PRHPC = 1;                                       /* Compressor pressure ratio */
    floating Pt21 = 101325;                                   /* Fan exhaust total pressure */
    floating Pt4 = 101325;                                    /* Burner exhaust total pressure */
    floating Pt5 = 101325;                                    /* Turbine exhaust total pressure */
    floating Pt6 = 101325;                                    /* Mixer exhaust total pressure */
    floating SMFAN = 25;                                      /* Fan stall margin */
    floating SMHPC = 25;                                      /* Compressor stall margin */
    floating TCOpen = ContConst.TCOpen;                   	/* Thermocouple value when open-circuited */
    floating TsamModel = 0.001 * TICK / TsampDiv;         	/* Model sampling time */
    floating Ts = 0.001 * TICK;                      			/* Sampling Time */
    floating Tt21 = 288.15;                                   /* Fan exhaust total temperature */
    floating Tt3 = 288.15;                                    /* Compressor exhaust total temperature */
    floating Tt6 = 288.15;                                    /* Mixer exhaust total temperature */
    floating V8 = 0;                                          /* Nozzle throat gas speed */
    floating W2 = 0;                                          /* Compressor inlet air flow */
    floating W21 = 0;                                         /* Fan exhaust air flow */
    floating W8 = 0;                                          /* Nozzle exhaust gas mass flow */
    floating WcFAN = 0;                                       /* Fan inlet corrected air flow */
    floating WcHPC = 0;                                       /* Compressor inlet corrected air mass flow */
    floating WfMax_Pump = 0;                                  /* Maximum pump fuel flow value */

	/* static floating TYPE */

	static floating fValue = 0;							/* Fuel flow value */

	/* floating (*) TYPE  */

    floating *AltLinVec;                                  /* Controller and Model - Altitude break points  */
    floating *AMtx;                                       /* Model - pointer for A matrix */
    floating *AshMtx;                                     /* Model - pointer for hot sub idle Ash matrix */
    floating *ASVec;                                      /* Controller - Asceleration schedule (ASVec) break points */
    floating *AwmMtx;                                     /* Model - pointer for windmill Awm matrix */
    floating *BMtx;                                       /* Model - pointer for B matrix */
    floating *BshMtx;                                     /* Model - pointer for hot sub idle Bsh matrix */
    floating *BwmMtx;                                     /* Model - pointer for wind mill Bwm matrix */
    floating *DeltaMtx;                                   /* Controller and Model - Delta break points  */
    floating *DeltaMtx1D;                                 /* Auxiliar matrix - Delta */
    floating *DeltaMtx1DH;                                /* Auxiliar matrix - Delta */
    floating *DeltaMtx2D;                                 /* Auxiliar matrix - Delta */
    floating *DeltaMtx2DH;                                /* Auxiliar matrix - Delta */
    floating *DSVec;                                      /* Controller - Deceleration schedule (DSVec) break points */
    floating *EffFANMapMtx;                               /* Model - pointer for Efficiency values matrix - fan map */
    floating *EffHPCMapMtx;                               /* Model - pointer for Efficiency values matrix - HPC map */
    floating *EffHPTMapMtx;                               /* Model - pointer for Efficiency values matrix - HPT map */
    floating *FNcMaxContMtx;                              /* Controller - pointer for maximum net thrust breakpoint values */
    floating *FNperContMtx;                               /* Controller - pointer for net thrust percent breakpoint values */
    floating *MapFAN1D;                                   /* Auxiliar matrix - fan map */
    floating *MapFAN1DH;                                  /* Auxiliar matrix - fan map */
    floating *MapFAN2D;                                   /* Auxiliar matrix - fan map */
    floating *MapFAN2DH;                                  /* Auxiliar matrix - fan map */
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
    floating *N_KishMtx;									/* Controller - pointer for Ki matrix of N control law - sub-idle */
	floating *N_KpMtx;                                    /* Controller - pointer for Kp matrix of N control law */
    floating *N_KpshMtx;									/* Controller - pointer for Kp matrix of N control law - sub-idle */
	floating *NcFANContMtx;                               /* Controller - pointer for fan Nc breakpoint values */
    floating *NcFANMapMtx;                                /* Model - pointer for Nc values matrix - fan map */
    floating *NcFANshContMtx;								/* Controller - pointer for fan Nc breakpoints values - sub-idle */
	floating *NcFANshMtx;									/* Model - pointer for Ncvalues matrix for sub-idle model */
	floating *NcHPCMapMtx;                                /* Model - pointer for Nc values matrix - HPC map */
    floating *NcHPTMapMtx;                                /* Model - pointer for Nc values matrix - HPT map */
    floating *NcMtx;                                      /* Model - pointer for Nc matrix */
    floating *NcVec;                                      /* Controller - Nc schedule (for ASVec and DSVec) break points  */
    floating *PRFANMapMtx;                                /* Model - pointer for PR values matrix - fan map */
    floating *PRFANStallMtx;                              /* Model - pointer for PR stall values matrix - fan map */
    floating *PRHPCMapMtx;                                /* Model - pointer for PR values matrix - HPC map */
    floating *PRHPCStallMtx;                              /* Model - pointer for PR stall values matrix - HPC map */
    floating *PRHPTMapMtx;                                /* Model - pointer for PR values matrix - HPT map */
    floating *Pt21DMtx;                                   /* Model - pointer for Pt21D matrix */
    floating *Pt21DshMtx;
	floating *Pt21DwmMtx;
    floating *Pt21Mtx;                                    /* Model - pointer for Pt21 matrix */
    floating *Pt21shMtx;
	floating *Pt21wmMtx;
	floating *Pt3DMtx;                                    /* Model - pointer for Pt3D matrix */
    floating *Pt3DshMtx;									/* Model - pointer for Pt3Dsh matrix */
	floating *Pt3DwmMtx;
	floating *Pt3Mtx;                                     /* Model - pointer for Pt3 matrix */
	floating *Pt3shMtx;									/* Model - pointer for Pt3sh matrix */
	floating *Pt3wmMtx;
	floating *Pt5DMtx;                                    /* Model - pointer for Pt5D matrix */
    floating *Pt5DshMtx;
	floating *Pt5DwmMtx;
	floating *Pt5Mtx;                                     /* Model - pointer for Pt5 matrix */
    floating *Pt5shMtx;
	floating *Pt5wmMtx;
	floating *Pt6DMtx;									/* Model - pointer for Pt6D matrix */
	floating *Pt6DshMtx;                                  /* Model - pointer for Pt6Dsh matrix */
    floating *Pt6DwmMtx;
	floating *Pt6Mtx;                                     /* Model - pointer for Pt6 matrix */
    floating *Pt6shMtx;
	floating *Pt6wmMtx;
	floating *RPMshMtx;                                   /* Model - pointer for hot sub idle RPMsh matrix */
    floating *RPMwmMtx;                                   /* Model - pointer for windmill RPMwm matrix */
    floating *Ts0Mtx;                                     /* Controller and Model - pointer Ts0 break points  */
    floating *Ts0Mtx1D;                                   /* Auxiliar matrix - Ts0 */
    floating *Ts0Mtx1DH;                                  /* Auxiliar matrix - Ts0 */
    floating *Ts0Mtx2D;                                   /* Auxiliar matrix - Ts0 */
    floating *Ts0Mtx2DH;                                  /* Auxiliar matrix - Ts0 */
    floating *Tt21DMtx;                                   /* Model - pointer for Tt21D matrix */
    floating *Tt21DshMtx;
	floating *Tt21DwmMtx;
	floating *Tt21Mtx;                                    /* Model - pointer for Nc matrix */
    floating *Tt21shMtx;
	floating *Tt21wmMtx;
	floating *Tt3DMtx;                                    /* Model - pointer for Tt3D matrix */
    floating *Tt3DshMtx;
	floating *Tt3DwmMtx;
	floating *Tt3Mtx;                                     /* Model - pointer for Tt3 matrix */
    floating *Tt3shMtx;
	floating *Tt3wmMtx;
	floating *Tt4CshMtx;                                  /* Model - pointer for hot sub idle Tt4Csh matrix */
    floating *Tt4DMtx;                                    /* Model - pointer for Tt4D matrix */
	floating *Tt4DshMtx;                                  /* Model - pointer for hot sub idle Tt4Dsh matrix */
	floating *Tt4DwmMtx;
    floating *Tt4Mtx;                                     /* Model - pointer for Tt4 matrix */
    floating *Tt4shMtx;                                   /* Model - pointer for hot sub idle Tt4sh matrix */
    floating *Tt4wmMtx;
	floating *Tt5DMtx;                                    /* Model - pointer for Tt5D matrix */
    floating *Tt5DshMtx;
	floating *Tt5DwmMtx;
	floating *Tt5Mtx;                                     /* Model - pointer for Tt5 matrix */
    floating *Tt5shMtx;
	floating *Tt5wmMtx;
	floating *Tt6DMtx;                                    /* Model - pointer for Tt6D matrix */
    floating *Tt6DshMtx;
	floating *Tt6DwmMtx;
	floating *Tt6Mtx;                                     /* Model - pointer for Tt6 matrix */
    floating *Tt6shMtx;
	floating *Tt6wmMtx;
	floating *WcFANMapMtx;                                /* Model - pointer for Wc values matrix - fan map */
    floating *WcFANStallMtx;                              /* Model - pointer for Nc stall values matrix - fan map */
    floating *WcHPCMapMtx;                                /* Model - pointer for Wc values matrix - HPC map */
    floating *WcHPCStallMtx;                              /* Model - pointer for Wc stall values matrix - HPC map */
    floating *WcHPTMapMtx;                                /* Model - pointer for Wc values matrix - HPT map */
    floating *WfMtx;                                      /* Model - pointer for Wf matrix */
    floating *WfshMtx;                                    /* Model - pointer for hot sub idle Wfsh matrix */
	floating *WfwmMtx;									/* Model - pointer for windmill Wfwm matrix */

	/*---------------------------------------------------------------------------------------*/
	/* BEARING MODEL VARIABLES - MUST BE INCORPORATED AT CONSTANTS ONCE VALIDATED */
	/*---------------------------------------------------------------------------------------*/

	/* NOTE: Currently, the three bearigs are common to all engines simulated by the software.
	In a near future, when the current model or a final model is validated to be used as a
	mathematical description of a bearing, the model parameters must be treated by the functions
	getXXXMtx and getXXXContConst */

	// /* Engine RPM vector */
    // floating RPMEVec[3] = {0, 20000, 23000};				/* Engine rotation speed breakpoints (RPME) */

    // /* Bearing 0 data */
    // floating DelT_Bear0[3] = {1, 100, 130};				/* Temperature decrease if maximum oil flow is used at given RPME */
    // floating TNOil_Bear0[3] = {300, 450, 573};			/* Temperature reached if no oil is used at the given RPME */

    // /* Bearing 1 data */
    // floating DelT_Bear1[3] = {1, 40, 120};				/* Temperature decrease if maximum oil flow is used at given RPME */
    // floating TNOil_Bear1[3] = {300, 400, 530};			/* Temperature reached if no oil is used at the given RPME */

    // /* Bearing 2 Data */
    // floating DelT_Bear2[3] = {1, 50, 110};				/* Temperature decrease if maximum oil flow is used at given RPME */
    // floating TNOil_Bear2[3] = {300, 410, 540};			/* Temperature reached if no oil is used at the given RPME */

	/* Engine RPM vector */
    floating RPMEVec[3] = {0, 20000, 23000};//{0.00, 20000.00, 23000.00};				/* Engine rotation speed breakpoints (RPME) */
	/* Bearing 0 data */
    floating DelT_Bear0[3] = {1.00, 50.00, 20.00};				/* Temperature decrease if maximum oil flow is used at given RPME */
    floating TNOil_Bear0[3] = {300.00, 415.00, 450.00};			/* Temperature reached if no oil is used at the given RPME */

    /* Bearing 1 data */
    floating DelT_Bear1[3] = {1.00, 40.00, 70.00};				/* Temperature decrease if maximum oil flow is used at given RPME */
    floating TNOil_Bear1[3] = {300.00, 400.00, 480.00};			/* Temperature reached if no oil is used at the given RPME */

    /* Bearing 2 Data */
    floating DelT_Bear2[3] = {1.00, 50.00, 51.00};				/* Temperature decrease if maximum oil flow is used at given RPME */
    floating TNOil_Bear2[3] = {300.00, 410.00, 480.00};			/* Temperature reached if no oil is used at the given RPME */

	static BearingPars Bear0;
    static BearingPars Bear1;
    static BearingPars Bear2;
    static BearingPars BearEmpty = {0};

