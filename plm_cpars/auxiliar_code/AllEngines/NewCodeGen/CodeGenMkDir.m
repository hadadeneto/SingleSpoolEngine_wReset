function CodeGenMkDir(cFolderName,hFolderName)
%Creates specified files for each device for storing correspoinding .c and
%.h files

%Creates .c folder
if ~isempty(cFolderName)
    %Removes .c folder if it already exists
    if exist(cFolderName, 'dir')
        rmdir(cFolderName,'s') 
    end
    %Creates a folders for organizing files
    mkdir(cFolderName)
end

%Creates .h folder
if ~isempty(hFolderName)
    %Removes .h folder if it already exists
    if exist(hFolderName, 'dir')
        rmdir(hFolderName,'s')
    end
    %Creates a folders for organizing files
    mkdir(hFolderName)
end

end

