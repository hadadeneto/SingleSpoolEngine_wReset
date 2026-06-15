function CodeGenMkDir(cFolderName,hFolderName)
%Creates specified files for each device for storing correspoinding .c and
%.h files

%Removes .c folder if it already exists
if exist(cFolderName, 'dir')
    rmdir(cFolderName,'s')
end
%Removes .h folder if it already exists
if exist(hFolderName, 'dir')
    rmdir(hFolderName,'s')
end

%Creates a folders for organizing files
mkdir(cFolderName)
mkdir(hFolderName)

end

