%----------------------------------------------------
%DEFINITION OF ALTITUDE POINTS, NcDes AND ENGINE NAME
%----------------------------------------------------

%Defines altitude points wehre controller gains are to be calcualated
AltLinVec = [0 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 11000 12000];
%Defines the design point rotation speed
NDes = 24000;
%Defines Engine Name
EngineName = 'TJ1200';

%------------------------------
%DEFINES PUMP TRANSFER FUNCTION
%------------------------------

%Pump cutoff frequency
fcp = 2.2759e-01;%6;
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
wcMin = 0.2;%0.5;
wcMax = .6;%5;
MinOSPM = 0.01;
MaxOSPM = 0.1;
MinOSwc = 0.01;
MaxOSwc = 2;
MaxIterPM = 20;
MaxIterwc = 20;
wcDefMode = 0;%1;

%-------------------------------------------------
%ADDITION OF NECESSARY PATHS CONTAINING USED CODES
%-------------------------------------------------

word = [pwd filesep, 'PIDesign'];
addpath(word);
word = [pwd filesep, 'LinPars'];
addpath(word);
word = [pwd filesep, 'CodeGen'];
addpath(word);

%--------------------------
%LOADING OF ENGINE MATRICES
%--------------------------

%INITIALIZES ENGINE MATRICES WITH EMPTY VALUES

%State-Space Matrices
AMtx = []; BMtx = []; CMtx = []; DMtx = []; 
%Controller Gains
N_KpMtx = []; N_KiMtx = []; Pt3_KpMtx = []; Pt3_KiMtx = []; 
Tt4_KpMtx = []; Tt4_KiMtx = []; Tt5_KpMtx = []; Tt5_KiMtx = []; 
%Mechanical Rotation Speed
NcFANMtx = [];
%Station 2
ThetaMtx = []; DeltaMtx = [];
%Station 21
Pt21Mtx = []; Tt21Mtx = []; 
%Station 3
Pt3Mtx = []; Tt3Mtx = []; 
%Station 4
WfMtx = []; Tt4Mtx = [];
%Station 5
Pt5Mtx = []; Tt5Mtx = []; 
%Station 6
Pt6Mtx = []; Tt6Mtx = []; 
%Station 8
FNMtx = []; FNperMtx = [];

%Environment
MNLinPoints = [];
AltLinPoints = 0;


%LOADS ENGINE MATRICES

[MNLinPoints,AMtx,BMtx,CMtx,DMtx,...
Pt21CMtx, Pt21DMtx, Tt21CMtx, Tt21DMtx,...
Pt3CMtx, Pt3DMtx, Tt3CMtx, Tt3DMtx,...
Tt4CMtx, Tt4DMtx,...
Pt5CMtx, Pt5DMtx, Tt5CMtx, Tt5DMtx,...
Pt6CMtx, Pt6DMtx, Tt6CMtx, Tt6DMtx,...
N_KpMtx, N_KiMtx, Pt3_KpMtx, Pt3_KiMtx,... 
Tt4_KpMtx, Tt4_KiMtx, Tt5_KpMtx, Tt5_KiMtx,... 
NcFANMtx,...
Pt21Mtx, Tt21Mtx,...
Pt3Mtx, Tt3Mtx,...
WfMtx, Tt4Mtx,...
Pt5Mtx, Tt5Mtx, Pt6Mtx, Tt6Mtx,... 
FNMtx, FNperMtx] = SetLinPars(AltLinPoints, MNLinPoints,...
AMtx,BMtx,CMtx,DMtx,...
N_KpMtx, N_KiMtx, Pt3_KpMtx, Pt3_KiMtx,... 
Tt4_KpMtx, Tt4_KiMtx, Tt5_KpMtx, Tt5_KiMtx,... 
NcFANMtx,...
Pt21Mtx, Tt21Mtx,...
Pt3Mtx, Tt3Mtx,...
WfMtx, Tt4Mtx,...
Pt5Mtx, Tt5Mtx, Pt6Mtx, Tt6Mtx,... 
FNMtx, FNperMtx,SSFan);

%--------------------------------------------------
%CALCULATION OF ENGINE MATRICES AT HIGHER ALTITUDES
%--------------------------------------------------

%Defines Vectors used in AmbientCalc subroutine
MNVectorPT = MNLinPoints;
AltLinVectorPT = AltLinVec;

%Executes Ambient Calculations
if getAmbient > 0
    AmbientCalc;
end

%Calculates Steady-State Matrices for the engine
SteadyMtx;

%----------------------
%CALCULATON OF PI GAINS
%----------------------

%Calculates steady-state matrices and PI Gains
if getPIGains > 0
    PICalc;
end

%--------------------------------------------
%GENERATES C CODE FOR LOADING ENGINE MATRICES
%--------------------------------------------

%Generates C code for loading engine matrices
if getCCode > 0
    MtxCCode;
end

%-------------------
%DELETES ADDED PATHS
%-------------------

word = [pwd filesep, 'PIDesign'];
rmpath(word);
word = [pwd filesep, 'LinPars'];
rmpath(word);
word = [pwd filesep, 'CodeGen'];
rmpath(word);

