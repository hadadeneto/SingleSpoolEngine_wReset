
%LIST OF PROJECTS AND ASSOTIATED ENGINES

%Creates list of projects with respective engine names
ProjectList = [{'TJ1200_POC6_Boosted'},{'TF1200'},{'GEJ85'},{'TJ700'}, {'TJ200'}, {'TJ40'}, {'GET700_Turboshaft'}, {'TG200_Turboshaft'}, {'TJ300_AxRad'}, {'TJ300_Radial'}];
EngineNameList = [{'TJ1200'},{'TF1200'},{'GEJ85'},{'TJ700'},{'TJ200'},{'TJ40'},{'GET700'},{'TG200'},{'TJ300AR'},{'TJ300R'}];
VersionName = [{'2.20'},{'1.10'},{'1.10'},{'1.11'},{'1.20'},{'1.00'},{'1.00'},{'1.00'},{'1.00'},{'1.00'}];

%ENGINES LIST FOR FADEC AND HIL

%Choses the engines to be simulated by HIL - For each engine on this list,
%the code pack necessary for HIL simulation in real hardware
%will be generated and stored in the folder CodePack. Also, the necessary
%compiling commands for SIL to be run in MATLAB will also be generated and
%strored in CompileCall folder
EngHILPack = [{'TJ1200'},{'TF1200'},{'GEJ85'},{'TJ700'},{'TJ200'}, {'TJ40'},{'GET700'},{'TG200'},{'TJ300AR'},{'TJ300R'}];
%Chose engines for FADEC pack of software - For each engine on this list,
%the code pack necessary for real FADEC %will be generated and stored in 
%the folder CodePack. The necessary compiling commands for SIL to be 
%run in MATLAB will also be generated and stored in CompileCall folder.
%Additionally, a folder for the FADEC to the run in SIL using TMATS model,
%which is more complex, is generated
EngFADECPack = [{'TJ1200'},{'TJ200'},{'GET700'},{'TG200'},{'TJ300AR'},{'TJ300R'}];

%S-FUNCTION NAME FOR HIL
HILSFuncName = 'SSModelLoop.c';