
%Saves current path
CurrPath = pwd;
%FileName
FADECCoreFileName = 'FADEC_CoreCode';

%Goes plm_cpars folder
cd ..
cd ..
%Goes to host folder
%HostFolderPath = [pwd filesep HostFolder];
cd(HostFolder)

%Reads FADEC SSModelLoop.c
fid = fopen('SSModelLoop.c','r');
SSML = ReadLines(fid);
fclose(fid);

%Command for reading the new code
Command = {'//<FADECCore>'};
%Reads new code core
lines = find(strcmp(SSML, Command));
NewBase = SSML(lines(1)+1:lines(end)-1);

%CREATION OF BACKUP FOLDER

%Gets date and time
DateTimeCell = GetDateTime;
DateTimeStr = char(DateTimeCell);
% %Replaces all ':', '.' and ' ' for '_'
% DateTimeStr = strrep(DateTimeStr, ':', '_');
% DateTimeStr = strrep(DateTimeStr, '.', '_'); % Substitui o ponto dos milissegundos
% DateTimeStr = strrep(DateTimeStr, ' ', '_');
%Goes to FADECMLBase folder
cd(FADECMLBase);
%Creates folder for FADE_CoreCode backup
FADECCCBackupFolder = [FADECCoreFileName '_Bakcup' DateTimeStr];
%Creates backup folder for file
CodeGenMkDir(FADECCCBackupFolder,[]);

%BACKUP CREATION

%Name of backup file
%word = [FADECCoreFileName '_Backup' DateTimeStr '.h'];
word = [FADECCoreFileName '.h'];
%Adds file name to path
BackupFilePath = [pwd filesep FADECCCBackupFolder filesep word];
%Sets the path of existing constants .h file
OldCoreCodePath = [pwd filesep 'FADEC_CoreCode.h'];
% disp(['Origem existe? ', num2str(exist(OldCoreCodePath, 'file'))]);
% disp(['Pasta de destino existe? ', num2str(exist(fileparts(BackupFilePath), 'dir'))]);
% disp(['Caminho Origem: ', OldCoreCodePath]);
% disp(['Caminho Destino: ', BackupFilePath]);
%Copies existing constants .h file into backup folder
copyfile(OldCoreCodePath,BackupFilePath,'f');

%WRITE NEW CODE LINES INTO BASE

%Opens file for writing
fid = fopen([FADECCoreFileName '.h'],'w');
%Write new code lines to original file
WriteLinesSafe(NewBase,fid);
%Closes file
fclose(fid);

%RETURNS TO INITIAL PATH

cd(CurrPath);
