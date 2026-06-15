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
AddZOH = 2;
%first order model of the pump is considered if AddPump = 1
AddPump = 1;
%C code is to be generated only if getAmbient = 1
getCCode = 1;

%----------------------------------------------------
%DEFINITION OF ALTITUDE POINTS, NcDes AND ENGINE NAME
%----------------------------------------------------

%Defines altitude points wehre controller gains are to be calcualated
%AltLinVec = [0 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 11000 12000 13000 14000 15000];
AltLinVec = [0 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 11000 12000];
%Defines the design point rotation speed
NDes = 98000;%22972;
%Defines the design point nozzle throat area
AthDes = 0.0281;
%Defines Engine Name
EngineName = 'TJ40';

%-------------------------------
%VECTORS FOR REFERENCE FILTERING
%-------------------------------

%Acceleration Schedule
ASVec = [2, 2, 2, 2, 2, 2];%[1.09, 1.08, 1.06, 1.08, 1.09, 1.011];
%Deceleration Schedule
DSVec = [0.92, 0.92, 0.92, 0.92, 0.92, 0.92];
%Break-Points
NcVec = [0.55, 0.6, 0.7, 0.8, 0.9, 0.99];

%-------------------------------------
%VECTORS FOR CORRECTING FUEL PUMP BIAS
%-------------------------------------

%Fuel pump input rerference vector
FuelPumpIn = [0 0.0972 0.0992 0.1134 0.1275 0.1417 0.1559 0.1615 0.1701 0.1559 0.1417 0.1275 0.1134 0.0992 0.085 0.32035];
%Fuel pump output rerference vector
FuelPumpOut = [0 0.059753 0.062369 0.079561 0.094712 0.1093 0.12347 0.12856 0.1367 0.12262 0.10831 0.093632 0.078921 0.064097 0.048149 0.2835];

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

Tsamp = 0.2;

%------------------------------
%DEFINES PUMP TRANSFER FUNCTION
%------------------------------

%Pump cutoff frequency
fcp = 2.6526e-01;%5.3052e-01;%6;
fcp = 1.5915e-01; % A = -1
fcp = 3.1831e-01; % A = -2;
fcp = 1.5 * 1.5915e-01;%A = -1.5
% fcp = 2.6526e-01;%=1.6667 * 1.5915e-01;%A = -1.6667
% fcp = 1.7 * 1.5915e-01;
% fcp = 1.1141e-01; % A = -0.7
%defines pump´s 1st order pole
wcp = 2*pi*fcp;
%defines pum's transfer function - unitary gain
Gp = tf(wcp,[1 wcp]);

% %Defines variable s
% s = zpk('s');
% %Zero-Order Hold Padé approach
% Gzoh = tf(1,[0.1 1]);
% % Gzoh = (1 - exp(-s*0.2))/s/0.2;
% Gp = Gp * Gzoh;

%-----------------------
%DEFINES THE ENGINE TYPE
%-----------------------

%SSFan = 1 -> Single-Spool Turbofan
%SSFan = 0 -> Single-Spool Turbojet
SSFan = 0;


%--------------------------------------------
%DEFINITION OF PARAMETERS FOR PI CALCULATIONS
%--------------------------------------------

%Defines parameters for PI Calculations
% PM = 55;
% wcMin = 0.2;
% wcMax = .6;
% MinOSPM = 0.01;
% MaxOSPM = 0.1;
% MinOSwc = 0.01;
% MaxOSwc = 2;
% MaxIterPM = 20;
% MaxIterwc = 20;
% wcDefMode = 0;%1;

%ATTEMPT FOR FASTER - YET UNDER TESTING, FOR MAKING TJ1000 WITH FASTER
%RESPONSE!!!

%NOTE: WcMax = 1.2 and WcMin = 0.9 worked fine in the real test, with
%satisfactory oscilations and sufficiently fast!

PM = 55;
wcMin = 0.5;%1.5;%0.9;%0.5;
wcMax = 1;%2;%1.5;%1.1;%1.5;%%1;
MinOSPM = 0.01;
MaxOSPM = 0.1;
MinOSwc = 0.01;
MaxOSwc = 2;
MaxIterPM = 20;
MaxIterwc = 20;
wcDefMode = 0;%1;

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

%ATTEMPT FOR INTERMEDIATE RESPONSE OF TJ1000 ENGINE
% PM = 55;
% wcMin = 0.5;
% wcMax = 1;%0.8;%1;
% MinOSPM = 0.01;
% MaxOSPM = 0.1;
% MinOSwc = 0.01;
% MaxOSwc = 2;
% MaxIterPM = 20;
% MaxIterwc = 20;
% wcDefMode = 0;%1;

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
% NcGain = 23116.775324;%23947.053525;
% WcGain = 1.137547;%1.278796;
% PRGain = 1.047403;%1.024266;
% EffGain = 0.955923;%0.945597;
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
% NcGain = 23116.775324;%23947.053525;
% WcGain = 1.137547;%1.278796;
% PRGain = 1.047403;%1.024266;
% EffGain = 0.955923;%0.945597;
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
% NcGain = 114.975102;%115.633018;
% WcGain = 0.235287;%0.250411;
% PRGain = 0.247350;%0.249984;
% EffGain = 0.882860;%0.882860;
% 
% NcHPTMap = MWS.HPT.NcVec * NcGain / NDes;
% WcHPTMap = MWS.HPT.WcArray * WcGain * 1/2.2046226;
% EffHPTMap = MWS.HPT.EffArray * EffGain;
% PRHPTMap = PRGain * (MWS.HPT.PRArray - 1) + 1;

%Processes engine data obtained from TMATS
EngDataProc;
