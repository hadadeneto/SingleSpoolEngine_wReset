
function CodeGenAllMtx(AllMatrices,GetFuncMatrices,GetFuncConst,VarsPerLine,EngineName,varargin)

%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%-------------------
%BREAKPOINT VECTORS
%-------------------

%Type of function argument
ArgType = 'double';
%Name of function argument
ArgName = '*Pointer';
%Type of returned variable
RetType = 'void';

%.c folder and .h folder names
cFolderName = 'c_Files_Test';
hFolderName = 'h_Files_Test';

%Removes .c folder if it already exists
if exist(cFolderName, 'dir')
    rmdir(cFolderName,'s')
end
%Removes .h folder if it already exists
if exist(hFolderName, 'dir')
    rmdir(hFolderName,'s')
end

%Creates a folders for organizing files
mkdir(cFolderName)% h_Files_Test
mkdir(hFolderName)% c_Files_Test

%------------------
%GENERATES .h FILES
%------------------

%getXXX.h - FILE CONTAINING DECLARATION OF ALL get FUNCTIONS

%Opens a .h document for defining the function that acquires matrices
%word = 'LinMtxFunctions.h';
word = [hFolderName '/' 'get' EngineName '.h'];
fileword = ['FILE ' word ' GENERATED'];
fid = fopen(word,'w');

%Prints the altitude value in first line and jumps two lines
word = ['#ifndef ' 'GET' EngineName '_H'];
fprintf(fid,word);
fprintf(fid,'\n');
word = ['#define ' 'GET' EngineName '_H'];
fprintf(fid,word);

%Prints the desire comment above the printed C code line
fprintf(fid,'\n\n');
word = '/* FUNCTIONS FOR LOADING MATRICES CONTAINING LINEARIZATION POINTS */';
fprintf(fid,word);

%Prints the functions in a .h file
for i = 1:length(AllMatrices)
    NameVar = char(AllMatrices(i));
    PrtFuncName(fid,EngineName,NameVar,ArgType,ArgName,RetType);
end

%PRINTS ADDITIONAL FUNCTIONS CONTAINED IN THE SAME .h FILE

word = ['\n\n/* get FUNCTIONS FOR ENGINE AND CONTROLLER CONSTANTS */\n\n'];
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

%.h FILE CONTAINING MAIN get FUNCTION

%Opens a .h document for defining the function that acquires matrices
%word = 'LinMtxFunctions.h';
word = [hFolderName '/' 'get' EngineName 'Mtx.h'];
fileword = ['FILE ' word ' GENERATED'];
fid = fopen(word,'w');

%Prints the altitude value in first line and jumps two lines
word = ['#ifndef GET' EngineName 'MTX_H'];
fprintf(fid,word);
fprintf(fid,'\n');
word = ['#define GET' EngineName 'MTX_H'];
fprintf(fid,word);

%Prints the desire comment above the printed C code line
fprintf(fid,'\n\n');
word = '/* MAIN FUNCTION FOR LOADING MATRICES CONTAINING LINEARIZATION POINTS */ \n\n';
fprintf(fid,word);

word = [];
NumVarsCount = 0;
%Prints the function in the .h file
for i = 1:length(GetFuncMatrices)
    
    %Updates vaiables counter
    NumVarsCount = NumVarsCount + 1;
    %First element must be followed by the function name
    if i == 1
        NameVar = ['get' EngineName 'Mtx(' ArgType ' *' char(GetFuncMatrices(i)) ', '];
        word = [word NameVar];
    %Verifies if the total amount of variables in a line equals 10
    elseif NumVarsCount == VarsPerLine && i ~= length(GetFuncMatrices)
        %Counter is reset
        NumVarsCount = 0;
        %New line must be started next
        NameVar = [ArgType ' *' char(GetFuncMatrices(i)) ', ' '\n     '];
        word = [word NameVar];
        fprintf(fid,word);
        %Word is emptyed
        word = [];
    %Prints last variable    
    elseif i == length(GetFuncMatrices)
        NameVars = [ArgType ' *' char(GetFuncMatrices(i)) ');'];
        word = [word NameVars];
        fprintf(fid,word);
    else
        %Gets the variable name
        NameVar = [ArgType ' *' char(GetFuncMatrices(i)) ', '];
        word = [word NameVar];
    end
    
end

%Prints the endif command of .h files
word = '\n\n#endif';
fprintf(fid,word);

%closes the generated .txt file
fclose(fid);
disp(' ')
disp(fileword)

%------------------------------------------
%GENERATES C CODE FOR ALL REQUIRED MATRICES
%------------------------------------------

for i = 1:length(AllMatrices)
    
    word = ['[rows,columns,pages] = size(' 'varargin{i}' ');'];
    eval(word);
    word = 'NumElem = num2str(rows * columns * pages);';
    eval(word);
    
    NameVar = char(AllMatrices(i));
    if length(NameVar) < 3
        NameVar = [NameVar 'Mtx'];
    elseif ~strcmp(NameVar(length(NameVar)-2:end),'Mtx') && ~strcmp(NameVar(length(NameVar)-2:end),'Vec')
        NameVar = [NameVar 'Mtx'];
    end
    
    word = ['Prt3DCMtx(EngineName,' '''' NameVar '''' ',' 'varargin{i}' ',NumElem,ArgType,ArgName,RetType,cFolderName);'];
    eval(word);
    
end

%--------------------------------
%GENERATES C CODE FOR getXXXMtx.c
%--------------------------------

%Builds word for generating .c file
word = [cFolderName '/' 'get' EngineName 'Mtx.c'];
%Builds word for printing after .c file is successfuly created
fileword = ['FILE ' word ' GENERATED'];
%Creates .c file
fid = fopen(word,'w');

%PRINTS FUNCTION INCLUDES
word = '\n#include <math.h>\n';
fprintf(fid,word);
word = ['#include ' '"get' EngineName 'MtxFunctions.h"\n\n'];
fprintf(fid,word);

%PRINTS FUNCTION DECLARATION
word = [];
NumVarsCount = 0;
%Prints the function in the .h file
for i = 1:length(GetFuncMatrices)
    
    %Updates vaiables counter
    NumVarsCount = NumVarsCount + 1;
    %First element must be followed by the function name
    if i == 1
        NameVar = ['get' EngineName 'Mtx(' ArgType ' *' char(GetFuncMatrices(i)) ', '];
        word = [word NameVar];
    %Verifies if the total amount of variables in a line equals 10
    elseif NumVarsCount == VarsPerLine && i ~= length(GetFuncMatrices)
        %Counter is reset
        NumVarsCount = 0;
        %New line must be started next
        NameVar = [ArgType ' *' char(GetFuncMatrices(i)) ', ' '\n     '];
        word = [word NameVar];
        fprintf(fid,word);
        %Word is emptyed
        word = [];
    %Prints last variable    
    elseif i == length(GetFuncMatrices)
        NameVars = [ArgType ' *' char(GetFuncMatrices(i)) ')'];
        word = [word NameVars];
        fprintf(fid,word);
    else
        %Gets the variable name
        NameVar = [ArgType ' *' char(GetFuncMatrices(i)) ', '];
        word = [word NameVar];
    end
    
end

%Prints separation lines for the get matrices
word = '\n\n';
fprintf(fid,word);

%Type of function argument
ArgType = '';
%Type of returned variable
RetType = '';

%Prints the functions in a .h file
for i = 1:length(GetFuncMatrices)
    NameVar = char(GetFuncMatrices(i));
    ArgName = GetFuncMatrices{i};
    PrtFuncName(fid,EngineName,NameVar,ArgType,ArgName,RetType);
end

%closes the generated .c file
fclose(fid);
%Prints message informing that .c file has been successfuly created
disp(' ')
disp(fileword)

end

