function CodeGengetXXXEngConst(hFolderName,cFolderName,ArgType,EngineName,Device,Level_Sep_Constants,Level_Sep_Defines,EngConstAll)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

%----------------------------------------------------------
%PRINTS FUNCTION FOR OBTAINING CONTROLLER CONSTANTS .h FILE
%----------------------------------------------------------

%Name of function to be preinted in .h file
GetFuncConst = cellstr(['void get' EngineName Device 'EngConst(struct EnginePars *EngPars, ' ArgType '*WfMax_Pump)']);

%Opens a .h document for defining function which loads the controller
%constants
word = [hFolderName '/' 'get' EngineName Device 'EngConst.h'];
fileword = ['FILE ' word ' GENERATED'];
fid = fopen(word,'w');

%Prints the altitude value in first line and jumps two lines
word = ['#ifndef ' 'GET' EngineName Device 'ENGCONST_H'];
fprintf(fid,word);
fprintf(fid,'\n');
word = ['#define ' 'GET' EngineName Device 'ENGCONST_H'];
fprintf(fid,word);

%Includes file for floating point precision definition
word = '\n\n#include "../../FADEC_Defines_H/FloatPoint_Precision.h"';
fprintf(fid,word);

word = '\n\n/* get FUNCTIONS FOR ENGINE MODEL CONSTANTS */\n\n';
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
EngConstPoint = EngConstAll(:,1)';
EngConstDef = EngConstAll(:,2)';
List = cell(1,length(EngConstDef));
%Enlists commands for computing variables
for i = 1:length(EngConstDef)
    List(i) = cellstr(['    ' char(EngConstPoint(i)) ' = ' EngineName char(EngConstDef(i)) ';\n']);    
end
%Sorts list for alphabetic order
List = sort(List);

%Opens a .h document for defining the function that acquires matrices
word = [cFolderName '/' 'get' EngineName Device 'EngConst.c'];
fileword = ['FILE ' word ' GENERATED'];
fid = fopen(word,'w');

%PRINTS FUNCTION INCLUDES

word = '\n#include <math.h>\n';
fprintf(fid,word);
word = ['#include ' '"' Level_Sep_Constants 'Constants' EngineName '.h"\n'];
fprintf(fid,word);
word = '#include "../../FADEC_Defines_H/FloatPoint_Precision.h"\n';
fprintf(fid,word);
word = ['#include ' '"' Level_Sep_Defines 'Model_Types.h"\n\n'];
fprintf(fid,word);

%PRINTS FUNCTION HEAD

%Prints the function in the .c file
for i = 1:length(GetFuncConst)
    word = [GetFuncConst{i}];
    fprintf(fid,word);
end

%PRINTS FUNCTION BODY

%Beginning of function
word = '\n{\n\n';
fprintf(fid,word);
word = ['    /* Loads engine model parameters */'];
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

