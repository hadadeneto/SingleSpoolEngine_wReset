function CopyFolder(HostSourceFolder,FolderList,HostSinkFolder)
%CopyFolder - Copies folders from a source folder to a sink folder, where
%both the source folder and the sink folders, despite having different
%roots, have the same foldername defined in the folder list

%Loop for copying all folders from source folders into sink folders
for i = 1:length(FolderList)
    %Defines source folder
    SourceFolder = [char(HostSourceFolder) filesep char(FolderList(i))]; 
    %Defines sink folder
    SinkFolder = [HostSinkFolder filesep char(FolderList(i))];
    
    clc
    
    wordTop1 = 'COPYING FROM:';
    wordBottom1 = char(SourceFolder);
    wordTop2 = 'TO:';
    wordBottom2 = char(SinkFolder);
    
    disp('')
    disp(wordTop1)
    disp(wordBottom1)
    disp(wordTop2)
    disp(wordBottom2)
    disp('')
    
    %Copies content from source to sink
    copyfile(SourceFolder,SinkFolder,'f');
end

end

