
% %-----------------------------
% %DEFINITION OF COMPONENTS MAPS
% %-----------------------------
% 
% MWS = [];
% 
% %FAN
% 
% MWS = GTHPCMap(MWS);
% 
% NcGain = 24000;
% WcGain = 1.37826;
% PRGain = 0.907561;
% EffGain = 0.992959;
% 
% NcFANMap = MWS.HPC.NcVec * NcGain / NDes;
% RlineFANMap = MWS.HPC.RlineVec;
% WcFANMap = MWS.HPC.WcArray * WcGain * 1/2.2046226;
% WcFANStall = MWS.HPC.WcMapSurge * WcGain * 1/2.2046226;
% EffFANMap = MWS.HPC.EffArray * EffGain;
% PRFANMap = PRGain * (MWS.HPC.PRArray - 1) + 1;
% PRFANStall = PRGain * (MWS.HPC.PRMapSurge - 1) + 1;
% 
% %COMPRESSOR - For Single Spool Jet Engine, the HPC becomes a "dummy" component,
% %with its map data loaded with the same values as the fan
% 
% MWS = GTHPCMap(MWS);
% 
% NcGain = 24000;
% WcGain = 1.37826;
% PRGain = 0.907561;
% EffGain = 0.992959;
% 
% NcHPCMap = MWS.HPC.NcVec * NcGain / NDes;
% RlineHPCMap = MWS.HPC.RlineVec;
% WcHPCMap = MWS.HPC.WcArray * WcGain * 1/2.2046226;
% WcHPCStall = MWS.HPC.WcMapSurge * WcGain * 1/2.2046226;
% EffHPCMap = MWS.HPC.EffArray * EffGain;
% PRHPCMap = PRGain * (MWS.HPC.PRArray - 1) + 1;
% PRHPCStall = PRGain * (MWS.HPC.PRMapSurge - 1) + 1;
% 
% %TURBINE
% 
% MWS = HPT_TMATS(MWS);
% 
% NcGain = 119.99914;
% WcGain = 0.291192;
% PRGain = 0.202161;
% EffGain = 0.947459;
% 
% NcHPTMap = MWS.HPT.NcVec * NcGain / NDes;
% WcHPTMap = MWS.HPT.WcArray * WcGain * 1/2.2046226;
% EffHPTMap = MWS.HPT.EffArray * EffGain;
% PRHPTMap = PRGain * (MWS.HPT.PRArray - 1) + 1;
% 
%--------------------
%GENERATION OF C CODE
%--------------------

%Loads PI Gains from the .mat file
load('PI.mat');
N_KpMtx = PIGains.Kp;
N_KiMtx = PIGains.Ki;
FNperContMtx = PIGains.FNper;
NcFANContMtx = PIGains.NcFAN;


%Generates C code for engine matrices
PritToFile(Ts0,DeltaMtx,ThetaMtx,AMtx, BMtx, ...
    Pt21CMtx,  Pt21DMtx,  Tt21CMtx,  Tt21DMtx, ...
    Pt3CMtx,  Pt3DMtx,  Tt3CMtx,  Tt3DMtx, ...
    Tt4CMtx,  Tt4DMtx, ...
    Pt5CMtx,  Pt5DMtx,  Tt5CMtx,  Tt5DMtx, ...
    Pt6CMtx,  Pt6DMtx,  Tt6CMtx,  Tt6DMtx, ...
    N_KpMtx,  N_KiMtx,  Pt3_KpMtx,  Pt3_KiMtx, ...
    Tt4_KpMtx,  Tt4_KiMtx,  Tt5_KpMtx,  Tt5_KiMtx, ...
    NcFANMtx, ...
    Pt21Mtx,  Tt21Mtx, ...
    Pt3Mtx,  Tt3Mtx, ...
    WfMtx,  Tt4Mtx, ...
    Pt5Mtx,  Tt5Mtx,  Pt6Mtx,  Tt6Mtx, ...
    FNMtx,  FNperMtx, ...
    NcFANMap, WcFANMap, EffFANMap, PRFANMap, ...
    NcHPCMap, WcHPCMap, EffHPCMap, PRHPCMap, ...
    NcHPTMap, WcHPTMap, EffHPTMap, PRHPTMap, ...
    PRFANStall, WcFANStall,PRHPCStall, WcHPCStall, ...
    FNperContMtx,FNcMaxContMtx,NcFANContMtx,EngineName,...
    MNLinVec,AltLinVec,...
    AwmMtx,BwmMtx,CwmMtx,DwmMtx,RPMwmMtx,...
    AshMtx,BshMtx,Pt3CshMtx,Pt3DshMtx,Tt4CshMtx,Tt4DshMtx,...
    NcFANshMtx,WfshMtx,Tt4shMtx,Pt3shMtx,RPMshMtx,...
    ASVec,DSVec,NcVec,...)
    FuelPumpIn,FuelPumpOut,...
    OilPumpIn,OilPumpOut)


