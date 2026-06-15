

%-------------------------------------------------
%ADDITION OF NECESSARY PATHS CONTAINING USED CODES
%-------------------------------------------------

UpperFolder = pwd;

word = [pwd filesep, EngFoldName];
addpath(word);
word = [pwd filesep, 'PIDesign'];
addpath(word);
word = [pwd filesep, 'LinPars'];
addpath(word);
word = [pwd filesep, 'NewCodeGen'];
addpath(word);
word = [pwd filesep, 'SubIdle'];
addpath(word);
word = [pwd filesep, 'SubIdle', filesep, 'Windmill'];
addpath(word);
word = [pwd filesep, 'SubIdle',  filesep, 'Combustion'];
addpath(word);
word = [pwd filesep, 'ComponentsMaps'];
addpath(word);
word = [pwd filesep, 'CodePrepare'];
addpath(word);
word = [pwd filesep, 'EngineDataProcess'];
addpath(word);

%-----------------
%LOADS ENGINE DATA
%-----------------

EngineData;

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
MNLinVec = [];
AltLinPoints = 0;


%LOADS ENGINE MATRICES

%New Alt0dT0.m generation
if CallSetLinMtx == 1
    
    SetLinMtx
    
end

%Old Alt0dT0.txt generation
if CallSetLinPars == 1
    
    [MNLinVec,AMtx,BMtx,CMtx,DMtx,...
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
        FNMtx, FNperMtx] = SetLinPars(AltLinPoints, MNLinVec,...
        AMtx,BMtx,CMtx,DMtx,...
        N_KpMtx, N_KiMtx, Pt3_KpMtx, Pt3_KiMtx,...
        Tt4_KpMtx, Tt4_KiMtx, Tt5_KpMtx, Tt5_KiMtx,...
        NcFANMtx,...
        Pt21Mtx, Tt21Mtx,...
        Pt3Mtx, Tt3Mtx,...
        WfMtx, Tt4Mtx,...
        Pt5Mtx, Tt5Mtx, Pt6Mtx, Tt6Mtx,...
        FNMtx, FNperMtx,SSFan);
    
    %The matrix NcMtx is not used in the "old way" where Al0dT0.txt is
    %used. Therefore, the code line below allows the further use of NcMtx
    %by making it equal NcFANMtx
    NcMtx = NcFANMtx;
    
end

%DEFINITION OF STATE VARIABLE AND ACTUATOIN VARIABLE DIMENSIONS

[DimX,DimU] = DimUX(AMtx,BMtx,NcMtx);

%--------------------------------------------------
%CALCULATION OF ENGINE MATRICES AT HIGHER ALTITUDES
%--------------------------------------------------

%Defines Vectors used in AmbientCalc subroutine
MNVectorPT = MNLinVec;
AltLinVectorPT = AltLinVec;

%Executes Ambient Calculations
if getAmbient > 0
    AmbientCalc;
end

%Calculates Steady-State Matrices for the engine
SteadyMtx;
% AcMtx - ATest
%Calculates the SubIdle Matrices for the engine
SubIdleMtx;

%Calculates low rotation speed estimated matrices of the engine - also part
%of sub-idle, but uses delta and theta
% ParsLR;

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
    AllMtc;
%     MtxCCode;
%     CopyCToPureJet;
%     CopyCToSingleSpoolFan;
end

%-------------------
%DELETES ADDED PATHS
%-------------------
word = [pwd filesep, EngFoldName];
rmpath(word);
word = [pwd filesep, 'PIDesign'];
rmpath(word);
word = [pwd filesep, 'LinPars'];
rmpath(word);
word = [pwd filesep, 'NewCodeGen'];
rmpath(word);
word = [pwd filesep, 'SubIdle', filesep, 'WindMill'];
rmpath(word);
word = [pwd filesep, 'SubIdle',  filesep, 'Combustion'];
rmpath(word);
word = [pwd filesep, 'SubIdle'];
rmpath(word);
word = [pwd filesep, 'ComponentsMaps'];
rmpath(word);
word = [pwd filesep, 'CodePrepare'];
rmpath(word);
word = [pwd filesep, 'EngineDataProcess'];
rmpath(word);
