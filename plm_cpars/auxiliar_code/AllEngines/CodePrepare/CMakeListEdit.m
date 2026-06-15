function LinesOut = CMakeListEdit(CMakeListName,MainFolder)
%CMakeListsEdit - Edits CMakeLists.txt, adding necessary folders and
%respective contents

First_match = 'include_directories';
Last_match = ')';

%Reads content of current folder
Content = dir(MainFolder);
%Initiates edited code pieces with empty values
EditInclude = [];
EditSources = [];
%Loop for making edited parts
for i = 3:length(Content)
    %Varifies if the current content name is a file name
    if isfolder(Content(i).name)
        %Includdes the folder
        EditInclude = [EditInclude; cellstr(['include_directories(' Content(i).name ')'])];
        %Reads content name
        ContentName = Content(i).name;
        %Gets last tow characters
        LastTwo = ContentName(length(ContentName)-1:end);
        %If the folder ends with _C or _H, only .c and .h files are added
        %for the folder. Else, both are added
        if strcmp(LastTwo,'_C')
            AuxEdit = cellstr(['        ' Content(i).name '/*.c']);
        elseif strcmp(LastTwo,'_H')
            AuxEdit = cellstr(['        ' Content(i).name '/*.h']);
        else
            AuxEdit = [cellstr(['        ' Content(i).name '/*.c']); cellstr(['        ' Content(i).name '/*.h'])];
        end
        %Updates edit sources
        EditSources = [EditSources;AuxEdit];
    end
end

%Final EditSources is created
EditSources = [cellstr('file(GLOB_RECURSE SOURCES'); EditSources; cellstr(')')];

%Opens file name
fid = fopen(CMakeListName,'r');
%Read lines of CMakeLists file
Lines = ReadLines(fid);
%Lines to be edited is stored with Lines
LinesOut = Lines;
%Closes file
fclose(fid);
%Loop for editing the original lines
for i = 1:length(Lines)
    %Initiates replacing flag with 0
    Replace = 0;
    %Transform current line from cell to string
    Charline = char(Lines(i));
    %Gets index of last character for evaluation
    IHF = min(length(First_match),length(Charline));
    IHL = min(length(Last_match),length(Charline));
    %Contidional for first match
    if strcmp(First_match,Charline(1:IHF))
        IL = i - 1;
    end
    %Conditional for last match
    if strcmp(Last_match,Charline(1:IHL))
        IH = i + 1;
        Replace = 1;
    end
    %Relpacement of piece of code to be edited
    if Replace == 1
        LinesOut = [Lines(1:IL); EditInclude; cellstr(' '); EditSources; Lines(IH:end)];
    end
end
%Opens CMakeLists.txt
fid = fopen(CMakeListName,'w');
%Writes the new lines
WriteLines(LinesOut,fid)
%Closes file
fclose(fid);

end

