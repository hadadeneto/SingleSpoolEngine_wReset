

% %Choses the engines to be simulated by HIL
% EngHILPack = [{'TJ1200'},{'TF1200'},{'GEJ85'},{'TJ700'}];
%
% %Chose engines for FADEC pack of software
% EngFADECPack = {'TJ1200'};

%GENERAL

%Folder containing FADEC files used by all engines
GenFADECFold = [{'FADEC_Defines_H'},{'FADEC_Functions_C'},{'FADEC_Functions_H'}];
%Folder containing HIL files used by all engines
GenHILFold = [{'HIL_Functions_C'},{'HIL_Functions_H'}];
%Base main code name
MainCodeBaseHIL = 'MainBoardModel.cpp';
MainCodeBaseFADEC = 'MainBoardFADEC.cpp';
%Generated main code name
MainCodeGenHIL = 'MainBoardModel.cpp';
MainCodeGenFADEC = 'MainBoardFADEC.cpp';
%MATLAB S-Function base code
MLSFCodeBase = 'SSModelLoop.c';

%INDIVIDUAL ENGINES

%
EngFADECFold = [{'FADEC_Constants_H'},{'FADEC_get_C'},{'FADEC_get_H'}];
%
EngHILFold = [{'HIL_get_C'},{'HIL_get_H'}];

%Sets the host folder - Currently, SSModelCFun
SetHostFolder;
%Sets the lists of engines
SetEngineList;

%Adds necessary paths
word = [pwd filesep, 'NewCodeGen'];
addpath(word);
word = [pwd filesep, 'CodePrepare'];
addpath(word);

%Saves current path
CurPath = pwd;

cd ..
cd ..

%
HostPath = [pwd filesep HostFolder];

clc

%-----------------------------------------------------
%CORRECTION OF GENERAL FUNCTIONS USED IN FADEC AND HIL
%-----------------------------------------------------

%Host code pack folder
CodePackFolder = [CurPath filesep 'CodePack'];

%Prepares main code considering new updates present on last tested code
MainCodePrep(MLSFCodeBase,HostPath,MainCodeBaseHIL,MainHILBase,MainHILGen,MainCodeGenHIL);

%Temproary folder for copying and treating FADEC and HIL general funcitons
%code
TempGenCodePackFold = [CurPath filesep 'CodePack' filesep  'TempGen'];
%Copies general HIL functions into HIL folder
CopyFolder(HostPath,GenHILFold,TempGenCodePackFold);
%Copies general FADEC functions into HIL folder
CopyFolder(HostPath,GenFADECFold,TempGenCodePackFold);
%Make small correction in general functions code for correct compilation
TreatGenFunc(TempGenCodePackFold,'_Functions_C')

%---------------------
%CREATES HIL CODE PACK
%---------------------

%Creates screen word for top
wordTop = 'CREATING FOLDER:';
%Path for folder containing HIL code packing
HILCodePackFold = [CurPath filesep 'CodePack' filesep 'HIL'];
%Creates screen word for bottom
wordBottom = char(HILCodePackFold);
%Prints words
clc
disp('')
disp(wordTop)
disp(wordBottom)
disp('')

%Creates the folder containing HIL code pack
CodeGenMkDir(HILCodePackFold,[]);

% %Prepares main code considering new updates present on last tested code
% MainCodePrep(MLSFCodeBase,HostPath,MainCodeBaseHIL,MainHILBase,MainHILGen,MainCodeGenHIL);
%
% %Temproary folder for copying and treating FADEC and HIL general funcitons
% %code
% TempGenCodePackFold = [CurPath filesep 'CodePack' filesep  'TempGen'];
% %Copies general HIL functions into HIL folder
% CopyFolder(HostPath,GenHILFold,TempGenCodePackFold);
% %Copies general FADEC functions into HIL folder
% CopyFolder(HostPath,GenFADECFold,TempGenCodePackFold);
% %Make small correction in general functions code for correct compilation
% TreatGenFunc(TempGenCodePackFold,'_Functions_C')

%Copies the engine folders into HIL folder
CopyFolder(HostPath,EngHILPack,HILCodePackFold);
%Copies general HIL functions into HIL folder
% CopyFolder(HostPath,GenHILFold,HILCodePackFold);
CopyFolder(TempGenCodePackFold,GenHILFold,HILCodePackFold);
%Copies general FADEC functions into HIL folder
% CopyFolder(HostPath,GenFADECFold,HILCodePackFold);
CopyFolder(TempGenCodePackFold,GenFADECFold,HILCodePackFold);
%Copies the base main code and additional ones to final folder
CopyFolder([HostPath filesep MainBase],{'HIL'},CodePackFolder);
%Goes to HIL code pack folder
cd([CodePackFolder filesep 'HIL']);
%Deletes the main base code
delete(MainCodeBaseHIL);
%Returns to curren path
cd(CurPath);
%Copies the generated main code to final folder
CopyFolder([HostPath filesep MainGen],{'HIL'},CodePackFolder);
%Goes to HIL code pack folder
cd([CodePackFolder filesep 'HIL']);
%Verifies if a temporary folder Temp exists and, if so, removes it
if isfolder('Temp')
    rmdir('Temp','s')
end
%Edits CMakeList.txt
CMakeListEdit('CMakeLists.txt',pwd);
%
cd(CurPath);

% %Temporary FADEC functions path
% TempFADECFuncPath = [HILCodePackFold filesep 'FADEC_Functions_C'];


%-----------------------
%CREATES FADEC CODE PACK
%-----------------------

%Loop for creating FADEC code pack
for i = 1:length(EngFADECPack)
    
    MainFADECBaseEngine = [MainFADECBase filesep char(EngFADECPack(i)) 'FADEC'];
    MainFADECGenEngine = [MainFADECGen filesep char(EngFADECPack(i)) 'FADEC'];
    FADECSFCodeBase = ['FADEC_' char(EngFADECPack(i)) '.c' ];
    %Prepares main code considering new updates present on last tested code
    MainCodePrep(FADECSFCodeBase,HostPath,MainCodeBaseFADEC,MainFADECBaseEngine,MainFADECGenEngine,MainCodeGenFADEC);
    
    %Computes FADEC code pack engine sinc folder
    FADECCodePackFold = [CurPath filesep 'CodePack' filesep 'FADEC' filesep char(EngFADECPack(i)) 'FADEC' filesep char(EngFADECPack(i))];
    %Computes host engine folder
    HostEngPat = [char(HostPath) filesep char(EngFADECPack(i))];
    %Copies engine specific files
    CopyFolder(HostEngPat,EngFADECFold,FADECCodePackFold);
    %Computes FADEC code pack general sinc folder - one level above engine
    %sink folder
    FADECCodePackFold = [CurPath filesep 'CodePack' filesep 'FADEC' filesep char(EngFADECPack(i)) 'FADEC'];
    %Computes host path
    HostEngPat = char(HostPath);
    %Copies gerneal FADEC files
    %     CopyFolder(HostEngPat,GenFADECFold,FADECCodePackFold);
    CopyFolder(TempGenCodePackFold,GenFADECFold,FADECCodePackFold);
    
    List = cellstr(['FADEC' filesep char(EngFADECPack(i)) 'FADEC']);
    %Copies the base main code and additional ones to final folder
    CopyFolder([HostPath filesep MainBase],List,CodePackFolder);
    %Goes to HIL code pack folder
    cd([CodePackFolder filesep 'FADEC' filesep char(EngFADECPack(i)) 'FADEC']);
    %Deletes the main base code
    delete(MainCodeBaseFADEC);
    %Returns to curren path
    cd(CurPath);
    %Copies the generated main code to final folder
    CopyFolder([HostPath filesep MainGen],List,CodePackFolder);
    %Goes to FADEC code pack folder
    cd([CodePackFolder filesep 'FADEC' filesep char(EngFADECPack(i)) 'FADEC']);
    %Verifies if a temporary folder Temp exists and, if so, removes it
    if isfolder('Temp')
        rmdir('Temp','s')
    end
    %Edits CMakeList.txt
    CMakeListEdit('CMakeLists.txt',pwd);
    %
    cd(CurPath)
    
end

%Returns to initial folder
cd(CurPath);

%-----------------------------------
%SETS PACK FOR USING FADEC IN T-MATS
%-----------------------------------

TMATSFADECPacking;

%-------------
%REMOVES PATHS
%-------------

%Removes added path
word = [pwd filesep, 'NewCodeGen'];
rmpath(word);
word = [pwd filesep, 'CodePrepare'];
rmpath(word);

%Message informing task accomplishment
clc
disp('')
disp('CODE PACK CREATED!')
disp('')