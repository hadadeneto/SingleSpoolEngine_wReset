

%Initially indicates that no paht must be removed in this script - in the
%case it is called by SetSIL script
PathRemove = 0;
%If the CompCalFold does not yet exist, scritp defining folders is called
if ~exist('CompCalFold','var') || ~exist('NoHostCompCalFold','var')
    %Defines folders
    SetHostFolder
    SetEngineList
end
%Reads all MATLAB paths
pathCell = regexp(path, pathsep, 'split');
%Verifies if CompCalFold is in MATLAB path
if ispc  % Windows is not case-sensitive
  onPath = any(strcmpi(cellstr([pwd filesep 'NewCodeGen']), pathCell));
else
  onPath = any(strcmp(cellstr([pwd filesep 'NewCodeGen']), pathCell));
end
%If the folder is not on MATLAB path, it must be added
if(onPath ~= 1)
    %Indicates that path must be removed at the end of script
    PathRemove = 1;
    %If the path is not yet present, must be added
    word = [pwd filesep, 'NewCodeGen'];
    addpath(word);
    word = [pwd filesep, 'CodePrepare'];
    addpath(word);
end


%File Name
CompFileName = 'MATLAB_HIL_Compile.m';
%Creates the folder CompileCall
CodeGenMkDir(CompCalFold,[]);
%Creates the folder CompileCallNoHost 
CodeGenMkDir(NoHostCompCalFold,[]);

%Names of FADEC and HIL folders
FADECFuncFold = 'FADEC_Functions_C';
FADECgetFold = 'FADEC_get_C';
FADECgetMtxFold = 'Mtx';
HILFuncFold = 'HIL_Functions_C';
HILgetFold = 'HIL_get_C';
HILgetMtxFold = 'Mtx';
FuncFold = [cellstr(FADECFuncFold) cellstr(HILFuncFold)];

%Sets ThreeDots word
ThreeDots = '...';
FirstWord = '    ';
FileSep = '\\';

% %Sets engine list
% SetEngineList

%Saves current path
CurPath = pwd;

%Goes to page above host
cd ..
cd ..

%
cd(HostFolder)
HostPath = pwd;
%
SimFold = ls;
SimFoldCell = cellstr(SimFold);

HILNameList = [];
NoHostHILNameList = [];

for i = 1:length(EngHILPack)
    
    %Initiates auxiliar list with empty value
    getListAux = [];    
    
    %Gets the engines listed for HIL simulation
    if ismember(EngHILPack(i),SimFoldCell)
        
        %FADEC FOLDER
        
        %Goest to corresponding engine FADEC folder
        cd([char(EngHILPack(i)) filesep FADECgetFold])
        %Reads file list
        getListAux = ls;  
        
        %Gets size of getListAux
        [row,~] = size(getListAux);
        %Elaborates list of 'get' functions to be compiles
        for j = 1:row
            if strcmp(getListAux(j,1:3),'get')
                HILNameList = [HILNameList; cellstr([FirstWord '-g ' HostFolder FileSep char(EngHILPack(i)) FileSep FADECgetFold FileSep getListAux(j,:) ThreeDots]);];
                NoHostHILNameList = [NoHostHILNameList; cellstr([FirstWord '-g ' char(EngHILPack(i)) FileSep FADECgetFold FileSep getListAux(j,:) ThreeDots]);];
            end
        end
        
        %Goes to Mtx folder
        cd('Mtx')
        %Reads file list
        getListAux = ls; 
        
        %Gets size of getListAux
        [row,~] = size(getListAux);
        %Elaborates list of 'get' functions to be compiles
        for j = 1:row
            if strcmp(getListAux(j,1:3),'get')
                HILNameList = [HILNameList; cellstr([FirstWord '-g ' HostFolder FileSep char(EngHILPack(i)) FileSep FADECgetFold FileSep FADECgetMtxFold FileSep getListAux(j,:) ThreeDots]);];
                NoHostHILNameList = [NoHostHILNameList; cellstr([FirstWord '-g ' char(EngHILPack(i)) FileSep FADECgetFold FileSep FADECgetMtxFold FileSep getListAux(j,:) ThreeDots]);];
            end
        end
        
        %Verifies if current engine has a FADEC to be compiled
        if ismember(EngHILPack(i),EngFADECPack)
            %Gets current FADED engine files to be compiled from HIL list
            FADECfromHILNameList = [];
            NoHostFADECfromHILNameList = [];
            for j = 1:length(HILNameList)
                %word containing the current engine name followed by FADEC
                wordEng = [char(EngHILPack(i)) '\\FADEC'];
                %Word containing the current function to be compiled from
                %HILNameList
                wordList = char(HILNameList(j)); 
                %The following loop gets a candidate word that has the size
                %of wordEng in each interaction, where the starting index
                %goes from 1 to the final word length                
                for k = 1:length(wordList)
                    IL = k;
                    IH = min(k + length(wordEng) - 1,length(wordList));
                    wordCandidate = wordList(IL:IH);
                    %If the candidate matches wordEng, the current word in
                    %HILNameList must be part of the FADECfromHILNameList                    
                    if strcmp(wordEng,wordCandidate)
                        FADECfromHILNameList = [FADECfromHILNameList;HILNameList(j)];
                        NoHostFADECfromHILNameList = [NoHostFADECfromHILNameList;NoHostHILNameList(j)];
                    end                    
                end
            end
            %Saves the list to be saved in the script to be called for
            %compiling the current engine's FADEC C functions in MATLAB
            %word = ['FADEC' char(EngHILPack(i)) 'List=HILNameList;'];
            word = ['FADEC' char(EngHILPack(i)) 'List=FADECfromHILNameList;'];
            eval(word)
            word = ['NoHostFADEC' char(EngHILPack(i)) 'List=NoHostFADECfromHILNameList;'];
            eval(word)
        end
        
        %Comes back to host folder
        cd(HostPath)
        
        %HIL FOLDER
        
        %Goest to corresponding engine HIL folder
        cd([char(EngHILPack(i)) filesep HILgetFold])
        %Reas file list
        getListAux = ls;  
        
        %Gets size of getListAux
        [row,~] = size(getListAux);
        %Elaborates list of 'get' functions to be compiles
        for j = 1:row
            if strcmp(getListAux(j,1:3),'get')
                HILNameList = [HILNameList; cellstr([FirstWord '-g ' HostFolder FileSep char(EngHILPack(i)) FileSep HILgetFold FileSep getListAux(j,:) ThreeDots]);];
                NoHostHILNameList = [NoHostHILNameList; cellstr([FirstWord '-g ' char(EngHILPack(i)) FileSep HILgetFold FileSep getListAux(j,:) ThreeDots]);];
            end
        end
        
        %Goes to Mtx folder
        cd('Mtx')
        %Reas file list        
        getListAux = ls; 
        
        %Gets size of getListAux
        [row,~] = size(getListAux);
        %Elaborates list of 'get' functions to be compiles        
        for j = 1:row
            if strcmp(getListAux(j,1:3),'get')
                HILNameList = [HILNameList; cellstr([FirstWord '-g ' HostFolder FileSep char(EngHILPack(i)) FileSep HILgetFold FileSep HILgetMtxFold FileSep getListAux(j,:) ThreeDots]);];
                NoHostHILNameList = [NoHostHILNameList; cellstr([FirstWord '-g ' char(EngHILPack(i)) FileSep HILgetFold FileSep getListAux(j,:) ThreeDots]);];
            end
        end
        
        %Comes back to host folder
        cd(HostPath)
    end
end


LastWord = ThreeDots;
FADECFuncNameList = [];
NoHostFADECFuncNameList = [];

for i = 1:length(FuncFold)
    
    %Initiates list value with zero
    getListAux = [];
    
    %Goest to corresponding engine HIL folder
    cd(char(FuncFold(i)))
    %Reas file list
    getListAux = ls;
    
    %Gets size of getListAux
    [row,~] = size(getListAux);
    %Elaborates list of functions to be compiled
    for j = 1:row
        %If this is the last function to be compiled, the word must not end
        %with '...'
        if i == length(FuncFold) && j == row
            LastWord = '';
        end
        %Sets compiling word
        if ~strcmp(getListAux(j,1),'.')
            HILNameList = [HILNameList; cellstr([FirstWord '-g ' HostFolder FileSep char(FuncFold(i)) FileSep getListAux(j,:) LastWord]);];
            NoHostHILNameList = [NoHostHILNameList; cellstr([FirstWord '-g ' char(FuncFold(i)) FileSep getListAux(j,:) LastWord]);];
            %Reads the name of current folder
            FolderAux = char(FuncFold(i));
            %If it is the FADEC folder, compile functions must be stored
            %also in FADEC list
            if strcmp('FADEC',FolderAux(1:length('FADEC')))
                %Sets last word for FADEC
                LastWordFADEC = ThreeDots;
                %If the last FADEC get function is stored, the last word
                %must be empty
                if j == row
                    LastWordFADEC = '';
                end
                FADECFuncNameList = [FADECFuncNameList; cellstr([FirstWord '-g ' HostFolder FileSep char(FuncFold(i)) FileSep getListAux(j,:) LastWordFADEC]);];
                NoHostFADECFuncNameList = [NoHostFADECFuncNameList; cellstr([FirstWord '-g ' char(FuncFold(i)) FileSep getListAux(j,:) LastWordFADEC]);];            
            end
        end
    end
       
    %Comes back to host folder
    cd(HostPath)
    
end

%Adds first line containing compilation of HIL S Function
FirstLine = ['mex -g ' HostFolder FileSep HILSFuncName ThreeDots];
FirstLine = cellstr(FirstLine);
NoHostFirstLine = ['mex -g ' FileSep HILSFuncName ThreeDots];
NoHostFirstLine = cellstr(NoHostFirstLine);
HILNameList = [FirstLine; HILNameList];
NoHostHILNameList = [NoHostFirstLine; NoHostHILNameList];

% %Saves HIL Compilation lines for MATLAB
% HILCompileLines = HILNameList;

%Returns to original path
cd(CurPath);

%------------------------------------------------------------------------
%SAVES COMPILATION FILES FOR USED WITH HIL LOCATED IN DEFINED HOST FOLDER
%------------------------------------------------------------------------

%Goes to compile call folder
cd(CompCalFold)

%Saves HIL compiling code
fid = fopen(CompFileName,'w');
WriteLines(HILNameList,fid)
fclose(fid);

%Initiates list of FADEC compiling codes
FADECCompList = [];

%Saves FADEC compiling code
for i = 1:length(EngFADECPack)
    %Starts variable containing compiling code to empty
    FADECNameList = [];
    %Sets current FADEC S-Function Name
    FADECSFuncName = ['FADEC_' char(EngFADECPack(i)) '.c'];
    %Sets first line to be compiled - S-Function line
    FirstLine = ['mex -g ' HostFolder FileSep FADECSFuncName ThreeDots];
    %Starts FADEC name list
    FADECNameList = [FADECNameList; FirstLine];
    %Completes FADEC name list using eval function for using the current
    %engine's list
    word = ['FADECNameList = [FADECNameList; ' 'FADEC' char(EngFADECPack(i)) 'List; FADECFuncNameList];'];
    eval(word)
    %Writes and saves FADEC compiling file in current folder
    FADECCompFileName = ['MATLAB_FADEC_' char(EngFADECPack(i)) '_Compile.m'];
    fid = fopen(FADECCompFileName,'w');
    WriteLines(FADECNameList,fid);
    fclose(fid);
    %Updates FADEC compile code list
    FADECCompList = [FADECCompList; cellstr(['MATLAB_FADEC_' char(EngFADECPack(i)) '_Compile'])];
end

%File to be called for compiling all listed FADECs
CompFADECFileName = 'MATLAB_FADEC_Compile.m';
%Writes files to be called within MATLAB_FADEC_Compile.m
fid = fopen(CompFADECFileName,'w');
WriteLines(FADECCompList,fid)
fclose(fid);

%Returns to original path
cd(CurPath);

%-----------------------------------------------------------------
%SAVES COMPILATION FILES IN FOLDER FOR GENERAL USE, SUCH AS T-MATS
%-----------------------------------------------------------------

%Goes to compile call folder
cd(NoHostCompCalFold)

%Saves HIL compiling code
fid = fopen(CompFileName,'w');
WriteLines(NoHostHILNameList,fid)
fclose(fid);

%Initiates list of FADEC compiling codes
FADECCompList = [];

%Saves FADEC compiling code
for i = 1:length(EngFADECPack)
    %Starts variable containing compiling code to empty
    FADECNameList = [];
    %Sets current FADEC S-Function Name
    FADECSFuncName = ['FADEC_' char(EngFADECPack(i)) '.c'];
    %Sets first line to be compiled - S-Function line
    FirstLine = ['mex -g ' FADECSFuncName ThreeDots];
    %Starts FADEC name list
    FADECNameList = [FADECNameList; FirstLine];
    %Completes FADEC name list using eval function for using the current
    %engine's list
    word = ['FADECNameList = [FADECNameList; ' 'NoHostFADEC' char(EngFADECPack(i)) 'List; NoHostFADECFuncNameList];'];
    eval(word)
    %Writes and saves FADEC compiling file in current folder
    FADECCompFileName = ['MATLAB_FADEC_' char(EngFADECPack(i)) '_Compile.m'];
    fid = fopen(FADECCompFileName,'w');
    WriteLines(FADECNameList,fid);
    fclose(fid);
    %Updates FADEC compile code list
    FADECCompList = [FADECCompList; cellstr(['MATLAB_FADEC_' char(EngFADECPack(i)) '_Compile'])];
end

%File to be called for compiling all listed FADECs
CompFADECFileName = 'MATLAB_FADEC_Compile.m';
%Writes files to be called within MATLAB_FADEC_Compile.m
fid = fopen(CompFADECFileName,'w');
WriteLines(FADECCompList,fid)
fclose(fid);

%Returns to original path
cd(CurPath);

%-----------------------------------------------------
%SAVES COMPILATION FOLDER IN HOST FOLDER OF MATLAB HIL
%-----------------------------------------------------

%Defines source path for copying 
SourcePath = pwd;

%Goes to main path
cd ..
cd ..

%Defines sink path for copying
SinkPath = pwd;

%Removes current 
if isfolder(CompCalFold)
    rmdir(CompCalFold,'s');
end

%Copies folder containing compiling code
CopyFolder(SourcePath,cellstr(CompCalFold),SinkPath);

%Comes back to original path
cd(CurPath);

%Removes path from MATLAB if necessary
if(PathRemove == 1)
    %Sets path removing flag back to zero
    PathRemove = 0;
    %Removes path
    word = [pwd filesep, 'NewCodeGen'];
    rmpath(word);
    word = [pwd filesep, 'CodePrepare'];
    rmpath(word);
end

