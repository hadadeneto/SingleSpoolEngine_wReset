function CopyCList(cFolderName,SubFolderName,SourceFolder,List)
%Creates folder using name in cFolderName and copies files specified in
%List from SourceFolder to [cFolderName filesep Subfolder]


%-----------------------------------
%COPIES .c FILES TO SPECIFIED FOLDER
%-----------------------------------

Subfolder = [filesep SubFolderName];
word = [cFolderName Subfolder];
mkdir(word);
SinkFile = word;
CopyCFunc(SourceFolder,SinkFile,List);

end

