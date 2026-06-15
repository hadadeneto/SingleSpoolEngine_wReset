
%--------------------
%DESIGN CONFIGURATION
%--------------------

%Ambient calculations are to be performed only if getAmbient = 1
getAmbient = 0;
%PI calculations are to be performed only if getAmbient = 1
getPIGains = 0;
%Sub-Idle PI calculations are to be performed only if getAmbient = 1
getPIshGains = 0;
%Choses between new or older sub-idle and windmill model
%1 - Older Model
%2 - Newer Model
SubIdleModel = 2;
%Transfer function for zoh with sampler
%1 - Adds Padé approach G(s) = (1 - T/2*s)/(1 + T/2*s)
%2 - Adds actual transfer function G(s) = (1 - exp(T*s))/T*s
AddZOH = 0;
%first order model of the pump is considered if AddPump = 1
AddPump = 0;
%C code is to be generated only if getAmbient = 1
getCCode = 1;

%----------------------------------------------------
%DEFINITION OF ALTITUDE POINTS, NcDes AND ENGINE NAME
%----------------------------------------------------

%Defines altitude points wehre controller gains are to be calcualated
% AltLinVec = [0 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 11000 12000 13000 14000 15000];
AltLinVec = [0 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 11000 12000];
%Defines the design point rotation speed
NDes = 26400;
%Defines the design point nozzle throat area
AthDes = 0.0397;
%Defines Engine Name
EngineName = 'TF1200';

%-------------------------------
%VECTORS FOR REFERENCE FILTERING
%-------------------------------

%Acceleration Schedule
ASVec = [1.0085, 1.0112, 1.01875, 1.044, 1.074, 1.02041];
%Deceleration Schedule
DSVec = [0.92, 0.92, 0.92, 0.92, 0.92, 0.92];
%Break-Points
NcVec = [0.6951, 0.7417, 0.8, 0.862, 0.912, 0.98];

%-------------------------------------
%VECTORS FOR CORRECTING FUEL PUMP BIAS
%-------------------------------------

%Fuel pump input rerference vector
FuelPumpIn = [0 1];
%Fuel pump output rerference vector
FuelPumpOut = [0 1];
    
%-------------------------------------
%VECTORS FOR CORRECTING OIL PUMP BIAS
%-------------------------------------

%Oil pump input rerference vector
OilPumpIn = [0 1];
%Oil pump output rerference vector
OilPumpOut = [0 1];

%------------------------------
%DEFINES CONTROLLER SAMPLE TIME
%------------------------------

Tsamp = 0.02;

%------------------------------
%DEFINES PUMP TRANSFER FUNCTION
%------------------------------

%Pump cutoff frequency
fcp = 6;
%defines pump´s 1st order pole
wcp = 2*pi*fcp;
%defines pum's transfer function - unitary gain
Gp = tf(wcp,[1 wcp]);

%-----------------------
%DEFINES THE ENGINE TYPE
%-----------------------

%SSFan = 1 -> Single-Spool Turbofan
%SSFan = 0 -> Single-Spool Turbojet
SSFan = 1;


%--------------------------------------------
%DEFINITION OF PARAMETERS FOR PI CALCULATIONS
%--------------------------------------------

%Defines parameters for PI Calculations
PM = 55;
wcMin = 0.7;
wcMax = 5;
MinOSPM = 0.01;
MaxOSPM = 0.1;
MinOSwc = 0.01;
MaxOSwc = 2;
MaxIterPM = 20;
MaxIterwc = 20;
wcDefMode = 2;

%Defines parameters for Sub-Idle PI Calculations - This configuration has been used
%in the first flight
PM = 55;
wcshMin = 0.2;
wcshMax = .6;
MinshOSPM = 0.01;
MaxshOSPM = 0.1;
MinshOSwc = 0.01;
MaxshOSwc = 2;
MaxshIterPM = 20;
MaxshIterwc = 20;
wcshDefMode = 0;%1;

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

%Processes engine data obtained from TMATS
EngDataProc;
