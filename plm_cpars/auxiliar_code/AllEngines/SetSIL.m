
word = [pwd filesep, 'CodePrepare'];
addpath(word);
word = [pwd filesep, 'NewCodeGen'];
addpath(word);

%Defines the project to be backed up
% Project = 'TJ1200_POC6_Boosted';
%Saves current path
CurPath = pwd;

%Reads current date and time
DateTime = clock;
%Initiates date and time char with empty value
DateTimeChar = [];
for i = 1:length(DateTime)
    %Includes underscore for values separation
    DateTimeChar = [DateTimeChar '_'];
    %Includes word specifying date
    if i == 1
        DateTimeChar = [DateTimeChar 'Date_'];
    end
    %Indluces word specifying time
    if i == 4
        DateTimeChar = [DateTimeChar 'Time_'];
    end
    %Updates DateTimeChar wiht current value
    DateTimeChar = [DateTimeChar num2str(DateTime(i))];
end

% %Creates list of projects with respective engine names
% ProjectList = [{'TJ1200_POC6_Boosted'},{'TF1200'},{'GEJ85'},{'TJ700'}];
% EngineNameList = [{'TJ1200'},{'TF1200'},{'GEJ85'},{'TJ700'}];
SetEngineList

Index = 1;
%Finds the index corresponding to the chosen project
for i = 1:length(ProjectList)
    if strcmp(char(ProjectList(i)),char(Project))
        Index = i;
    end
end
 
%Sets host folders
SetHostFolder;
%Gets path with updated model
NewModelPath = [pwd filesep 'Engines' filesep char(Project)];
%Goes to main path
cd .. 
cd ..
%Sets host path for model and specific engine
HostPath = [pwd filesep HostFolder];
HostEngPath = [HostPath filesep char(EngineNameList(Index))];
%Sets backup path
BackupPath = [pwd filesep BackupFolder];

%-------------------------------------
%PERFOMRS BACKUP BEFORE CHANGING MODEL
%-------------------------------------

%Removes current
if isfolder(HostEngPath)
    %Goes to backup path
    cd(BackupPath)
    %In backup path, sets engine current backup folder
    EngBackupFold = [char(EngineNameList(Index)) DateTimeChar];
    %Generates folder
    CodeGenMkDir(EngBackupFold,[])
    %Copies current model into engine backup folder
    CopyFolder(HostPath,EngineNameList(Index),[BackupPath filesep EngBackupFold]);
    %Comes back to initial path
    cd(CurPath);
end

%-----------------------
%PERFORMS MODEL UPDATING
%-----------------------

%Removes current 
if isfolder(HostEngPath)
    rmdir(HostEngPath,'s');
end

%Copies current model into engine backup folder
CopyFolder(NewModelPath,EngineNameList(Index),HostPath);

%Comes back to original path
cd(CurPath);

%----------------------------------------
%MATLAB COMPILING CODE FOR HIL AND FADECS
%----------------------------------------

%Sets compile call lines
SetCompileCall;

%Comes back to original path
cd(CurPath);

%Removes added MATLAB paths
word = [pwd filesep, 'CodePrepare'];
rmpath(word);
word = [pwd filesep, 'NewCodeGen'];
rmpath(word);

