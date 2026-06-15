
%Saves the current path
CurPath = pwd;

%If the CompCalFold does not yet exist, scritp defining folders is called
if ~exist('TMATSFADECPack','var')
    %Defines folders
    SetHostFolder
    SetEngineList
end


%Loop for copying files and folders for each corresponding FADEC folder for
%posterior use in TMATS
for i = 1:length(EngFADECPack)
    %Sets sink folder
    SinkFolder = ['CodePack' filesep 'FADEC_TMATS' filesep char(EngFADECPack(i)) 'FADEC'];
    %Reads the content inside the current engine's FADEC folder
    FADECContent = dir(['CodePack' filesep 'FADEC' filesep char(EngFADECPack(i)) 'FADEC']);
    %Creates a new folder for storing the content
    CodeGenMkDir(SinkFolder,[]);
    %Initiates folder list with empty value
    TMATSFADECFolderList = [];
    %Sets source folder
    SourceFolder = ['CodePack' filesep 'FADEC' filesep char(EngFADECPack(i)) 'FADEC'];
    %Goes to source folder
    cd(SourceFolder)
    %Loop for copying the folders to be used in TMATS FADEC
    for j = 3:length(FADECContent)
        %If the current content is a folder, must be added to list
        if isfolder(FADECContent(j).name)
           TMATSFADECFolderList = [TMATSFADECFolderList cellstr(FADECContent(j).name)];
        end
    end
    %Copies content to 
    cd(CurPath)
    %Path for FADEC compilation file
    TMATSFADECCompilePath = [pwd filesep NoHostCompCalFold filesep 'MATLAB_FADEC_' char(EngFADECPack(i)) '_Compile.m'];
    %Copies necessary folders into corresponding TMATS FADEC folder
    CopyFolder(SourceFolder,TMATSFADECFolderList,SinkFolder);
    %Goes to hots folder
    cd ..
    cd ..
    TMATSFADECMainPath = [pwd filesep HostFolder filesep 'FADEC_' char(EngFADECPack(i)) '.c'];
    %Returns to current path
    cd(CurPath)
    %Goes to SinkFolder for copying main file
    cd(SinkFolder)
    %Copies main file and compilation file
    copyfile(TMATSFADECMainPath);
    copyfile(TMATSFADECCompilePath);
    %Returns to original path
    cd(CurPath)
end
