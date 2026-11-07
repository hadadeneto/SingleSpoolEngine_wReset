function Output = FADECBaseUpdt(FileBaseName,ext,FileCoreName,Command,HostFolder,FADECMLBase)
%FADECBASEUPDT Summary of this function goes here
%   Detailed explanation goes here


%Saves current path
CurrPath = pwd;
% %FileName
% FADECCoreFileName = 'FADEC_CoreCode';

%Goes plm_cpars folder
cd ..
cd ..
%Goes to host folder
% HostFolderPath = [pwd filesep HostFolder];
cd(HostFolder)
cd(FADECMLBase)

%READS FILES

%Reads FADEC base file
fid = fopen([FileBaseName ext],'r');
BASE = ReadLines(fid);
fclose(fid);

%Reads the core file
fid = fopen(FileCoreName,'r');
CORE = ReadLines(fid);
fclose(fid);

%ELABORATES NEW BASE FILE

%Command for reading the new code
%Command = {'//<FADECCore>'};
%Reads new code core
lines = find(strcmp(BASE, Command));
%Creates new base code
First = BASE(1:lines(1));
Last = BASE(lines(end):end);
NewBase = [First; CORE; Last];

%CREATION OF BACKUP FOLDER

%Gets date and time
DateTimeCell = GetDateTime;
%Goes to FADECMLBase folder
% cd(FADECMLBase);
%Creates folder for FADE_CoreCode backup
FADECBaseBackupFolder = [FileBaseName '_Bakcup' char(DateTimeCell)];
%Creates backup folder for file
CodeGenMkDir(FADECBaseBackupFolder,[]);

%BACKUP CREATION

%Name of backup file
word = [FileBaseName ext];
%Adds file name to path
BackupFilePath = [pwd filesep FADECBaseBackupFolder filesep word];
%Sets the path of existing constants .h file
OldCoreCodePath = [pwd filesep FileBaseName ext];
%Copies existing constants .h file into backup folder
copyfile(OldCoreCodePath,BackupFilePath,'f');

%WRITE NEW CODE LINES INTO BASE

%Opens file for writing
fid = fopen([FileBaseName ext],'w');
%Write new code lines to original file
WriteLinesSafe(NewBase,fid);
%Closes file
fclose(fid);

%RETURNS TO INITIAL PATH

cd(CurrPath);

Output = 1;

end

