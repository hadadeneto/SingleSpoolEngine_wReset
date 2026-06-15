

%Folder where file list is extracted from MATLAB folder
FolderName = 'SSModelCFunc';
%Reads file list
FileList = dir(FolderName);
MLFileList = cell(1,length(FileList));
%Stores the MATLAB code list
for i = 1:length(FileList)
    %Stores at MATLAB file list
    MLFileList(i) = {FileList(i).name};
end

%Folder where file list is extracted from real HIL folder
FolderName = 'MainBoardModel_2023_05_30_vATDPOC_unified\ModelCFunc';
%Reads file list
FileList = dir(FolderName);
HILFileList = cell(1,length(FileList));
%Stores the MATLAB code list
for i = 1:length(FileList)
    %Stores at MATLAB file list
    HILFileList(i) = {FileList(i).name};
end 

HILFuncList = [];
HILNotMembers = [];
%FinalList
for i = 1:length(MLFileList)
    if ismember(MLFileList(i),HILFileList) && ~strcmp('.',MLFileList{i}) && ~strcmp('..',MLFileList{i})
        HILFuncList = [HILFuncList MLFileList(i)];
    else
        HILNotMembers = [HILNotMembers MLFileList(i)];
    end
end

save HILFuncList.mat HILFuncList;
