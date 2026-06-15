%----------------------------------------------------
%DEFINITION OF ALTITUDE POINTS, NcDes AND ENGINE NAME
%----------------------------------------------------

%Defines altitude points wehre controller gains are to be calcualated
%AltLinVec = [0 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 11000 12000 13000 14000 15000];
AltLinVec = [0 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 11000 12000];
%Defines the design point rotation speed
NDes = 23042;%22972;
%Defines Engine Name
EngineName = 'TJ1200';

%-------------------------------
%VECTORS FOR REFERENCE FILTERING
%-------------------------------

%Acceleration Schedule
ASVec = [1.09, 1.08, 1.06, 1.08, 1.09, 1.011];
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
%defines pump´s 1st order pole
wcp = 2*pi*fcp;
%defines pum's transfer function - unitary gain
Gp = tf(wcp,[1 wcp]);

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
PM = 55;
wcMin = 0.2;
wcMax = .6;
MinOSPM = 0.01;
MaxOSPM = 0.1;
MinOSwc = 0.01;
MaxOSwc = 2;
MaxIterPM = 20;
MaxIterwc = 20;
wcDefMode = 0;%1;

%-----------------------------
%DEFINITION OF COMPONENTS MAPS
%-----------------------------

MWS = [];

%FAN

MWS = GTHPCMap(MWS);

NcGain = 23116.775324;%23947.053525;
WcGain = 1.137547;%1.278796;
PRGain = 1.047403;%1.024266;
EffGain = 0.955923;%0.945597;

NcFANMap = MWS.HPC.NcVec * NcGain / NDes;
RlineFANMap = MWS.HPC.RlineVec;
WcFANMap = MWS.HPC.WcArray * WcGain * 1/2.2046226;
WcFANStall = MWS.HPC.WcMapSurge * WcGain * 1/2.2046226;
EffFANMap = MWS.HPC.EffArray * EffGain;
PRFANMap = PRGain * (MWS.HPC.PRArray - 1) + 1;
PRFANStall = PRGain * (MWS.HPC.PRMapSurge - 1) + 1;

%COMPRESSOR - For Single Spool Jet Engine, the HPC becomes a "dummy" component,
%with its map data loaded with the same values as the fan

MWS = GTHPCMap(MWS);

NcGain = 23116.775324;%23947.053525;
WcGain = 1.137547;%1.278796;
PRGain = 1.047403;%1.024266;
EffGain = 0.955923;%0.945597;

NcHPCMap = MWS.HPC.NcVec * NcGain / NDes;
RlineHPCMap = MWS.HPC.RlineVec;
WcHPCMap = MWS.HPC.WcArray * WcGain * 1/2.2046226;
WcHPCStall = MWS.HPC.WcMapSurge * WcGain * 1/2.2046226;
EffHPCMap = MWS.HPC.EffArray * EffGain;
PRHPCMap = PRGain * (MWS.HPC.PRArray - 1) + 1;
PRHPCStall = PRGain * (MWS.HPC.PRMapSurge - 1) + 1;

%TURBINE

MWS = HPT_TMATS(MWS);

NcGain = 114.975102;%115.633018;
WcGain = 0.235287;%0.250411;
PRGain = 0.247350;%0.249984;
EffGain = 0.882860;%0.882860;

NcHPTMap = MWS.HPT.NcVec * NcGain / NDes;
WcHPTMap = MWS.HPT.WcArray * WcGain * 1/2.2046226;
EffHPTMap = MWS.HPT.EffArray * EffGain;
PRHPTMap = PRGain * (MWS.HPT.PRArray - 1) + 1;

% %--------------------
% %GENERATION OF C CODE
% %--------------------
% 
% %Loads PI Gains from the .mat file
% load('PI.mat');
% N_KpMtx = PIGains.Kp;
% N_KiMtx = PIGains.Ki;
% FNperContMtx = PIGains.FNper;
% NcFANContMtx = PIGains.NcFAN;
