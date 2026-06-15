function CodeGengetXXXStartPars(hFolderName,cFolderName,EngineName,Device,Level_Sep_Constants,Level_Sep_Defines,StartAll)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

GetStartPars = cellstr(['void get' EngineName Device 'StartPars(struct ControlStart *ContStartP)']);

%---------------------------------------------------------
%PRINTS FUNCTION FOR OBTAINING STARTING PARAMETERS .h FILE
%---------------------------------------------------------

%Opens a .h document for defining function which loads the controller
%constants
word = [hFolderName '/' 'get' EngineName Device 'StartPars.h'];
fileword = ['FILE ' word ' GENERATED'];
fid = fopen(word,'w');

%Prints the altitude value in first line and jumps two lines
word = ['#ifndef ' 'GET' EngineName Device 'STARTPARS_H'];
fprintf(fid,word);
fprintf(fid,'\n');
word = ['#define ' 'GET' EngineName Device 'STARTPARS_H'];
fprintf(fid,word);

word = ['\n\n/* get FUNCTIONS FOR GETTING' Device 'STARTING PARAMETERS */\n\n'];
fprintf(fid,word);

for i = 1:length(GetStartPars)
    word = [GetStartPars{i} ';'];
    fprintf(fid,word);
end

%Prints the endif command of .h files
word = '\n\n#endif';
fprintf(fid,word);

%closes the generated .txt file
fclose(fid);
disp(' ')
disp(fileword)

%---------------------------------------------------------
%PRINTS FUNCTION FOR OBTAINING STARTING PARAMETERS .c FILE
%---------------------------------------------------------

%Variables of getXXXStartPars.c
StartPoint = StartAll(:,1)';
StartDef = StartAll(:,2)';
List = cell(1,length(StartDef));
%Enlists commands for computing variables
for i = 1:length(StartDef)
    List(i) = cellstr(['    ' char(StartPoint(i)) ' = ' EngineName char(StartDef(i)) ';\n']);    
end
%Sorts list for alphabetic order
List = sort(List);

%Opens a .h document for defining the function that acquires matrices
word = [cFolderName '/' 'get' EngineName Device 'StartPars.c'];
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
for i = 1:length(GetStartPars)
    word = [GetStartPars{i}];
    fprintf(fid,word);
end

%PRINTS FUNCTION BODY

%Beginning of function
word = '\n{\n\n';
fprintf(fid,word);
word = ['    /* Loads starting parameters */'];
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

