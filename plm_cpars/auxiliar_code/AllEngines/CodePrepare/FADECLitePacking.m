
%Saves the current path
CurPath = pwd;

%Used names in software
FakeName = 'XXX';
Command = '//<FADECControl>';

%If the FADECLitePack does not yet exist, scritp defining folders is called
if ~exist('FADECLitePack','var')
    %Defines folders
    SetHostFolder
    SetEngineList
end

%
cd ..
cd ..

%Sets the path for FADECLite shared files
FADECLiteSharedPath = [pwd filesep HostFolder filesep 'FADECLiteBase' filesep 'SharedFiles'];
%Shared content
SharedContent = dir(FADECLiteSharedPath);

%READS JET CONTENT

%Sets base file path
FADECLiteBasePath = [pwd filesep HostFolder filesep 'FADECLiteBase' filesep 'ControlFADECLite_Base_Jet.c'];
%Opens jet file for reading
fid = fopen(FADECLiteBasePath,'r');
%Reads base file code lines
BASE_JET = ReadLines(fid);
%Closes file
fclose(fid);

%READS SHAFT CONTENT

%Sets base file path
FADECLiteBasePath = [pwd filesep HostFolder filesep 'FADECLiteBase' filesep 'ControlFADECLite_Base_Shaft.c'];
%Opens jet file for reading
fid = fopen(FADECLiteBasePath,'r');
%Reads base file code lines
BASE_SHAFT = ReadLines(fid);
%Closes file
fclose(fid);

%NOTE: The current difference between shaft and jet content is that the
%shaft needs to take into account the dimensions of X and U in state-space
%representation while for jet both dimensions are 1. This must be solved
%and made universal with the use of new constants and the final file must
%suit both types.

%Comes back to saved path
cd(CurPath);

%Loop for copying files and folders for each corresponding FADEC folder for
%posterior use in FADEC Lite
for i = 1:length(EngFADECLitePack)
    
    %SAVES CONTENT SHARED BY ALL ENGINES
    
    %Sets sink folder
    SinkFolder = ['CodePack' filesep 'FADECLite' filesep char(EngFADECLitePack(i)) 'FADECLite'];    
    %Reads the content inside the current engine's FADEC folder
    FADECContent = dir(['CodePack' filesep 'FADEC' filesep char(EngFADECLitePack(i)) 'FADEC']);
    %Creates a new folder for storing the content
    CodeGenMkDir(SinkFolder,[]);
    
    %Copies Shared files into sink folder
    for j = 3:length(SharedContent)
        %Sink file path
        SinkFile = [SinkFolder filesep char(SharedContent(j).name)];
        %Source file path
        SourceFile = [FADECLiteSharedPath filesep char(SharedContent(j).name)];
        %Copies from source to sink
        copyfile(SourceFile,SinkFile,'f');
    end
    
    % SAVES CONTENT OF MAIN CONTROL ROUTINE
    
    %Saves current path
    CurPath_1 = pwd;
    %Goes into sink folder
    cd(SinkFolder);
    %Starts new code with content of BASE_JET
    NewCode = BASE_JET;
    
    %If shaft engine is detected, content is replaced by BASE_SHAFT content
    if FADECLiteTypeList(i) == 2
        NewCode = BASE_SHAFT;
    end
    
    %Finds indexes where code line contain the command for identifying core
    %code and replaces with emtpy cell
    idx = find(strcmp(NewCode, Command)); 
    
    %Loop for replacing the lines with empty cell
    for j = 1:length(idx)
        NewCode(idx(j)) = {''};
    end
    
    %Replaces XXX by engine name
    for j = 1:length(NewCode)
        %Line as chars
        CharLine = NewCode{j};
        %Gets char line with correct engine name
        NewCharLine = replace(CharLine,FakeName,EngFADECLitePack{i});
        %Replaces new code line with corrected one
        NewCode{j} = NewCharLine;
    end
    
    %Opens destination control file
    fid = fopen('ControlFADECLite.c','w');
    %Writes new code lines into file
    WriteLinesSafe(NewCode,fid);
    %Closes file
    fclose(fid);
    %Returns to saved path
    cd(CurPath_1);
    
    
    %SAVES FADEC FILES USED BY FADEC LITE
    
    %Initiates folder list with empty value
    FADECLiteFolderList = [];
    %Sets source folder
    SourceFolder = ['CodePack' filesep 'FADEC' filesep char(EngFADECLitePack(i)) 'FADEC'];
    %Goes to source folder
    cd(SourceFolder)
    
    %Loop for copying the folders to be used in TMATS FADEC
    for j = 3:length(FADECContent)
        %If the current content is a folder, must be added to list
        if isfolder(FADECContent(j).name)
           FADECLiteFolderList = [FADECLiteFolderList cellstr(FADECContent(j).name)];
        end
    end
    
    %Copies content to
    cd(CurPath)
    %Copies necessary folders into corresponding TMATS FADEC folder
    CopyFolder(SourceFolder,FADECLiteFolderList,SinkFolder);

end
