
%Saves current path
CurrPath = pwd;

%BACKUP

%Goes to plm_cpars
cd ..
cd ..

%Gets date and time
DateTimeCell = GetDateTime;
%Backup folder for MATLAB FADECs
FADECMLBackupFolder = ['FADEC_ML_' char(DateTimeCell)];
%Backup folder path
BackupFolderPath = [pwd filesep BackupFolder filesep FADECMLBackupFolder];
%Makes new folder
CodeGenMkDir(BackupFolderPath,[]);

%Loop for backup of all fadec files
for i = 1:length(EngFADECPack)
    %Reads engine name
    EngName = EngFADECPack{i};
    %Creates original file path
    OldFilePath = [pwd filesep HostFolder filesep 'FADEC_' EngName '.c'];
    %Creates backup file path
    BackupFilePath = [BackupFolderPath filesep 'FADEC_' EngName '.c'];
    %Copies original file into backup folder
    copyfile(OldFilePath,BackupFilePath,'f');
end

%READS BASE FILE

%Goes to host folder
cd([HostFolder filesep FADECMLBase])
%Reads jet FADEC file
fid = fopen('FADEC_XXX_Jet.c','r');
BASE_JET = ReadLines(fid);
fclose(fid);
%Reads shaft FADEC file
fid = fopen('FADEC_XXX_Shaft.c','r');
BASE_SHAFT = ReadLines(fid);
fclose(fid);

%UPDATES FADEC FILES

%Returns to host folder levels up
cd ..
%Writes fake engine name
FakeName = 'XXX';

%Loop for updating all FADEC files
for i = 1:length(EngFADECPack)
    %Reads engne name
    EngineName = EngFADECPack{i};
    %Starts the new code with BASE_JET
    NewCode = BASE_JET;
    %Verifies engine type and if it equals 2, its a turboshaft
    if FADECTypeList(i) == 2
        NewCode = BASE_SHAFT;
    end
    
    %Loop for updating new code with engine name
    for j = 1:length(NewCode)
        %Current line in characters
        charLine = NewCode{j};
        %Replaces fake name with engine name
        UpdtCharLine = replace(charLine,FakeName,EngineName);
        %Updates line in new code
        NewCode(j) = {UpdtCharLine};
    end
    
    %Opens file and updates it
    fid = fopen(['FADEC' EngineName '.c'],'w');
    %Writes the new code lines into FADEC file
    WriteLinesSafe(NewCode,fid);
    %Closes file
    fclose(fid);
    
end

%Comes back to initial path
cd(CurrPath);