function CodeGengetXXXContConst(hFolderName,cFolderName,EngineName,Device,Level_Sep_Defines,Level_Sep_Constants,ContConstAll)
%CodeGengetXXXContConst genreates the function for getting the engines
%controller constants

%----------------------------------------------------------
%PRINTS FUNCTION FOR OBTAINING CONTROLLER CONSTANTS .h FILE
%----------------------------------------------------------

%Name of function to be preinted in .h file
GetFuncConst = cellstr(['void get' EngineName Device 'ContConst(struct ControllerConstants *ContConst)']);

%Opens a .h document for defining function which loads the controller
%constants
word = [hFolderName '/' 'get' EngineName Device 'ContConst.h'];
fileword = ['FILE ' word ' GENERATED'];
fid = fopen(word,'w');

%Prints the altitude value in first line and jumps two lines
word = ['#ifndef ' 'GET' EngineName Device 'CONTCONST_H'];
fprintf(fid,word);
fprintf(fid,'\n');
word = ['#define ' 'GET' EngineName Device 'CONTCONST_H'];
fprintf(fid,word);

word = '\n\n/* get FUNCTIONS FOR ENGINE AND CONTROLLER CONSTANTS */\n\n';
fprintf(fid,word);

for i = 1:length(GetFuncConst)
    word = [GetFuncConst{i} ';'];
    fprintf(fid,word);
end

%Prints the endif command of .h files
word = '\n\n#endif';
fprintf(fid,word);

%closes the generated .txt file
fclose(fid);
disp(' ')
disp(fileword)

%----------------------------------------------------------
%PRINTS FUNCTION FOR OBTAINING CONTROLLER CONSTANTS .c FILE
%----------------------------------------------------------

%Variables of getXXXContConst.c
ContConstPoint = ContConstAll(:,1)';
ContConstDef = ContConstAll(:,2)';
List = cell(1,length(ContConstDef));

%Enlists commands for computing variables
for i = 1:length(ContConstDef)
    %Adds the engine name after each '*' operation
    ContConstDef(i) = DefsOperation(ContConstDef(i),'*',EngineName);
    %Updates list element
    List(i) = cellstr(['    ' char(ContConstPoint(i)) ' = ' EngineName char(ContConstDef(i)) ';\n']);    
end
%Sorts list for alphabetic order
List = sort(List);

%Opens a .h document for defining the function that acquires matrices
word = [cFolderName '/' 'get' EngineName Device 'ContConst.c'];
fileword = ['FILE ' word ' GENERATED'];
fid = fopen(word,'w');

%PRINTS FUNCTION INCLUDES

word = '\n#include <math.h>\n';
fprintf(fid,word);
word = ['#include ' '"' Level_Sep_Constants 'Constants' EngineName '.h"\n'];
fprintf(fid,word);
word = ['#include ' '"' Level_Sep_Defines 'Control_Types.h"\n\n'];
fprintf(fid,word);

%PRINTS FUNCTION HEAD

% word = [];
% NumVarsCount = 0;
%Prints the function in the .c file
for i = 1:length(GetFuncConst)
    word = [GetFuncConst{i}];
    fprintf(fid,word);
end

%PRINTS FUNCTION BODY

%Beginning of function
word = '\n{\n\n';
fprintf(fid,word);
word = ['    /* Loads controller parameters */'];
fprintf(fid,word);
word = '\n\n';
fprintf(fid,word);

%Loop for printing computation of variables describing engine matrices and
%vectors sizes
for i = 1:length(List)
    word = char(List(i));
    fprintf(fid,word);
end

%end of function
word = '\n}';
fprintf(fid,word);
%closes the generated .c file
fclose(fid);

%Acknowledge of .c file generation
disp(' ')
disp(fileword)

end

