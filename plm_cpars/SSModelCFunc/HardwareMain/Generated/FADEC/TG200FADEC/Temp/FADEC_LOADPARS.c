
    /* Loads the constants of chosen engine used by FADEC */
    getTG200FADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
                            &PowerMan_Elem, &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC);

    int DimX = 2;
    int DimU = 1;

    AltLinVec      = FADECMalloc(Alt_Elem, &MemSize);
    AMtx           = FADECMalloc(SteadyOp_Elem * DimX * DimX, &MemSize);
    ASVec          = FADECMalloc(AS_Elem, &MemSize);
    BMtx           = FADECMalloc(SteadyOp_Elem * DimX * DimU, &MemSize);
    DeltaMtx       = FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
    DeltaMtx1D     = FADECMalloc(MN_Elem, &MemSize);
    DeltaMtx1DH    = FADECMalloc(MN_Elem, &MemSize);
    DeltaMtx2D     = FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
    DeltaMtx2DH    = FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
    DSVec          = FADECMalloc(AS_Elem, &MemSize);
    FNcMaxContMtx  = FADECMalloc(MN_Elem, &MemSize);
    FNperContMtx   = FADECMalloc(PowerMan_Elem, &MemSize);
    MapHPC1D       = FADECMalloc(Wc_per_Nc_HPC, &MemSize);
    MapHPC1DH      = FADECMalloc(Wc_per_Nc_HPC, &MemSize);
    MapHPC2D       = FADECMalloc(WcHPCMap_Elem, &MemSize);
    MapHPC2DH      = FADECMalloc(WcHPCMap_Elem, &MemSize);
    MNLinVec       = FADECMalloc(MN_Elem, &MemSize);
    Mtx1D          = FADECMalloc(Fn_Elem, &MemSize);
    Mtx1DH         = FADECMalloc(Fn_Elem, &MemSize);
    Mtx2D          = FADECMalloc(MN_Elem * Fn_Elem, &MemSize);
    Mtx2DH         = FADECMalloc(MN_Elem * Fn_Elem, &MemSize);
    N_KiMtx        = FADECMalloc(PowerMan_Elem, &MemSize);
    N_KishMtx      = FADECMalloc(PowerMan_Elem, &MemSize);
    N_KpMtx        = FADECMalloc(PowerMan_Elem, &MemSize);
    N_KpshMtx      = FADECMalloc(PowerMan_Elem, &MemSize);
    NcFANContMtx   = FADECMalloc(PowerMan_Elem, &MemSize);
    NcFANshContMtx = FADECMalloc(PowerMan_Elem, &MemSize);
    NcHPCMapMtx    = FADECMalloc(NcHPCMap_Elem, &MemSize);
    NcVec          = FADECMalloc(AS_Elem, &MemSize);
    PRHPCMapMtx    = FADECMalloc(WcHPCMap_Elem, &MemSize);
    Pt3DMtx        = FADECMalloc(SteadyOp_Elem * DimU, &MemSize);
    Pt3Mtx         = FADECMalloc(SteadyOp_Elem, &MemSize);
    Pt5DMtx        = FADECMalloc(SteadyOp_Elem * DimU, &MemSize);
    Pt5Mtx         = FADECMalloc(SteadyOp_Elem, &MemSize);
    Ts0Mtx         = FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
    Ts0Mtx1D       = FADECMalloc(Alt_Elem, &MemSize);
    Ts0Mtx1DH      = FADECMalloc(Alt_Elem , &MemSize);
    Ts0Mtx2D       = FADECMalloc(Fn_Elem, &MemSize);
    Ts0Mtx2DH      = FADECMalloc(Fn_Elem, &MemSize);
    Tt4DMtx        = FADECMalloc(SteadyOp_Elem * DimU, &MemSize);
    Tt4Mtx         = FADECMalloc(SteadyOp_Elem , &MemSize);
    Tt5DMtx        = FADECMalloc(SteadyOp_Elem * DimU, &MemSize);
    Tt5Mtx         = FADECMalloc(SteadyOp_Elem, &MemSize);
    WcHPCMapMtx    = FADECMalloc(WcHPCMap_Elem, &MemSize);
    WfMtx          = FADECMalloc(SteadyOp_Elem, &MemSize);

    // AltLinVec = (floating *)malloc(Alt_Elem * sizeof(floating));
    // AMtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // ASVec = (floating *)malloc(AS_Elem * sizeof(floating));
    // BMtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // DeltaMtx = (floating *)malloc(Alt_Elem * MN_Elem * sizeof(floating));
    // DeltaMtx1D = (floating *)malloc(MN_Elem * sizeof(floating));
    // DeltaMtx1DH = (floating *)malloc(MN_Elem * sizeof(floating));
    // DeltaMtx2D = (floating *)malloc(Alt_Elem * MN_Elem * sizeof(floating));
    // DeltaMtx2DH = (floating *)malloc(Alt_Elem * MN_Elem * sizeof(floating));
    // DSVec = (floating *)malloc(AS_Elem * sizeof(floating));
    // FNcMaxContMtx = (floating *)malloc(MN_Elem * sizeof(floating));
    // FNperContMtx = (floating *)malloc(PowerMan_Elem * sizeof(floating));
    // MapHPC1D = (floating *)malloc(Wc_per_Nc_HPC * sizeof(floating));
    // MapHPC1DH = (floating *)malloc(Wc_per_Nc_HPC * sizeof(floating));
    // MapHPC2D = (floating *)malloc(WcHPCMap_Elem * sizeof(floating));
    // MapHPC2DH = (floating *)malloc(WcHPCMap_Elem * sizeof(floating));
    // MNLinVec = (floating *)malloc(MN_Elem * sizeof(floating));
    // Mtx1D = (floating *)malloc(Fn_Elem * sizeof(floating));
    // Mtx1DH = (floating *)malloc(Fn_Elem * sizeof(floating));
    // Mtx2D = (floating *)malloc(MN_Elem * Fn_Elem * sizeof(floating));
    // Mtx2DH = (floating *)malloc(MN_Elem * Fn_Elem * sizeof(floating));
    // N_KiMtx = (floating *)malloc(PowerMan_Elem * sizeof(floating));
    // N_KishMtx = (floating *)malloc(PowerMan_Elem * sizeof(floating));
    // N_KpMtx = (floating *)malloc(PowerMan_Elem * sizeof(floating));
    // N_KpshMtx = (floating *)malloc(PowerMan_Elem * sizeof(floating));
    // NcFANContMtx = (floating *)malloc(PowerMan_Elem * sizeof(floating));
    // NcHPCMapMtx = (floating *)malloc(NcHPCMap_Elem * sizeof(floating));
    // NcVec = (floating *)malloc(AS_Elem * sizeof(floating));
    // PRHPCMapMtx = (floating *)malloc(WcHPCMap_Elem * sizeof(floating));
    // Pt3DMtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // Pt3Mtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // Pt5DMtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // Pt5Mtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // Ts0Mtx = (floating *)malloc(Alt_Elem * MN_Elem * sizeof(floating));
    // Ts0Mtx1D = (floating *)malloc(Alt_Elem * sizeof(floating));
    // Ts0Mtx1DH = (floating *)malloc(Alt_Elem * sizeof(floating));
    // Ts0Mtx2D = (floating *)malloc(Fn_Elem * sizeof(floating));
    // Ts0Mtx2DH = (floating *)malloc(Fn_Elem * sizeof(floating));
    // Tt4DMtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // Tt4Mtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // Tt5DMtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // Tt5Mtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // WcHPCMapMtx = (floating *)malloc(WcHPCMap_Elem * sizeof(floating));
    // WfMtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));

    /*=======================================================*/
	/* PIECE OF CODE TO BE EXECUTED WITHIN THE MAIN FUNCTION */
	/*=======================================================*/

    /* ----------- */
	/* SINGLE STOP */
	/* ----------- */

    if(SingleStop == 0)
    {

        /*-----------------*/
        /* FADEC AND MODEL */
        /*-----------------*/

        /* STRUCTS INITIALIZATION */

        Ambient = AmbientEmpty;
        BlowOutPars = EstParsEmpty;
        ContConst = ContConstEmpty;
        ContGenOil = ContGenEmpty;
        ContInModCL = ContInputEmpty;
        ContInput = ContInputEmpty;
        ContOutModCL = ContOutputEmpty;
        ContOutput = ContOutputEmpty;
        ContStart = ContStartEmpty;
        ContStModCL = ContStartEmpty;
        EngOnOff = EngOnOffEmpty;
        Index3D = Index3DEmpty;
        ModelPars = EstParsEmpty;
        ModelParsChosen = EstParsEmpty;
        ModelParsCL = EstParsEmpty;
        PFuelRes = DefaultRes;
        POilRes = DefaultRes;
        Pt3Res = DefaultRes;
        RPMRes = DefaultRes;
        Sensors = SensorsEmpty;
        TBearRes = DefaultRes;
        Ts2Res = DefaultRes;
        Tt4Res = DefaultRes;
        VibrationRes = DefaultRes;

        /* UNIONS INITIALIZATION */

		CANFault = FaultDetectEmpty;
        digital = digitalEmpty;
        digModCL = digitalEmpty;
        EngStatus = EngStatusEmpty;
        ExistFStatus = FaultDetectEmpty;
        ExistFWarning = FaultDetectEmpty;
        FaultSensAuthorize = FaultSensEmpty;
        FaultSSens = FaultSensEmpty;
        FaultSSys = FaultSysEmpty;
        FaultStatus = FaultEmpty;
        FaultSysAuthorize = FaultSysEmpty;
        FaultWarning = FaultEmpty;
        FaultWSens = FaultSensEmpty;
        FaultWSys = FaultSysEmpty;
        HardFAuthorize = FaultDetectEmpty;
        HardFStatus = FaultDetectEmpty;
        HardFWarning = FaultDetectEmpty;
        keys = keysEmpty;
        ModPFault.ModParsBits = 0;
        SoftFStatus = FaultDetectEmpty;
        SoftFWarning = FaultDetectEmpty;
        SoftSimFaults = FaultSensEmpty;
        TB_0.TCFaultBits = 0;
        TB_1.TCFaultBits = 0;
        TB_2.TCFaultBits = 0;
        TrustAll = FaultDetectEmpty;
        TrustHard = FaultDetectEmpty;
        TrustSens = FaultDetectEmpty;
        Ts2_0.TCFaultBits = 0;
        Ts2_1.TCFaultBits = 0;
        Tt4_0.TCFaultBits = 0;
        Tt4_1.TCFaultBits = 0;
        Tt4_2.TCFaultBits = 0;

        /* static int TYPE */

        SingleStop = 1;

    }

    /* -------------------------------------------------- */


    /* LOADING OF CONTROLLER CONSTANTS */
    getTG200FADECContConst(&ContConst);

    /* Loads FADEC matrices */
    getTG200FADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
                     DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
                     N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
                     Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
                     Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
                     WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);

    // /* LOADING OF CONTROLLER MATRIX */

    // /* Linearization Vectors */
    // getTG200AltLinVec(&AltLinVec);
    // getTG200MNLinVec(&MNLinVec);
    // getTG200Ts0Mtx(&Ts0Mtx);
    // getTG200DeltaMtx(&DeltaMtx);

    // /* Controller Gains */
	// getTG200N_KpMtx(&N_KpMtx);
	// getTG200N_KiMtx(&N_KiMtx);
	// getTG200NcFANContMtx(&NcFANContMtx);
    // getTG200FNcMaxContMtx(&FNcMaxContMtx);
	// getTG200FNperContMtx(&FNperContMtx);

    // /* Reference Filter */
    // getTG200ASVec(&ASVec);
    // getTG200DSVec(&DSVec);
    // getTG200NcVec(&NcVec);

    // /* LOADING OF MODEL MATRICES */

    // getTG200AMtx(&AMtx);
    // getTG200BMtx(&BMtx);
    // getTG200Pt3DMtx(&Pt3DMtx);
    // getTG200Pt5DMtx(&Pt5DMtx);
    // getTG200Tt4DMtx(&Tt4DMtx);
    // getTG200Tt5DMtx(&Tt5DMtx);
    // getTG200Pt3Mtx(&Pt3Mtx);
    // getTG200Pt5Mtx(&Pt5Mtx);
    // getTG200Tt4Mtx(&Tt4Mtx);
    // getTG200Tt5Mtx(&Tt5Mtx);
    // getTG200WfMtx(&WfMtx);
    // getTG200PRHPCMapMtx(&PRHPCMapMtx);
    // getTG200WcHPCMapMtx(&WcHPCMapMtx);
    // getTG200NcHPCMapMtx(&NcHPCMapMtx);

    // getTG200FADECMtx(&AMtx[0], &ASVec[0], &AltLinVec[0], &BMtx[0], &DSVec[0],
    //                   &DeltaMtx[0], &FNcMaxContMtx[0], &FNperContMtx[0], &MNLinVec[0], &N_KiMtx[0],
    //                   &N_KpMtx[0], &NcFANContMtx[0], &NcHPCMapMtx[0], &NcVec[0], &PRHPCMapMtx[0],
    //                   &Pt3DMtx[0], &Pt3Mtx[0], &Pt5DMtx[0], &Pt5Mtx[0], &Ts0Mtx[0],
    //                   &Tt4DMtx[0], &Tt4Mtx[0], &Tt5DMtx[0], &Tt5Mtx[0], &WcHPCMapMtx[0],
    //                   &WfMtx[0]);

