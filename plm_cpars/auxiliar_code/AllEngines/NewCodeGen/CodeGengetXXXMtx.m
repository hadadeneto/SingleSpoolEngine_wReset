function CodeGengetXXXMtx(cFolderName, hFolderName, CallsFolderName, File_Sep, EngineName, VarsPerLine, RetType, ArgType, Device, GetMatrices)
%This code printer generates the .h and .c files of getXXXMtx for either
%FADEC or HIL devices

%Finds indexes where engine name begins at cFolderName
EngNameInd = strfind(hFolderName,EngineName);
hFolderNameInclude = [hFolderName(EngNameInd(end)+length(EngineName):end) File_Sep];

%------------------------------------
%.h FILE CONTAINING MAIN get FUNCTION
%------------------------------------

%Opens a .h document for defining the function that acquires matrices
%word = 'LinMtxFunctions.h';
word = [hFolderName File_Sep 'get' EngineName Device 'Mtx.h'];
fileword = ['FILE ' word ' GENERATED'];
fid = fopen(word,'w');

%Prints the altitude value in first line and jumps two lines
word = ['#ifndef GET' EngineName Device 'MTX_H'];
fprintf(fid,word);
fprintf(fid,'\n');
word = ['#define GET' EngineName Device 'MTX_H'];
fprintf(fid,word);

%Prints include for floating point precision definition
fprintf(fid,'\n');
word = '\n#include "../../FADEC_Defines_H/FloatPoint_Precision.h"\n';
fprintf(fid,word);

%Prints the desire comment above the printed C code line
fprintf(fid,'\n\n');
word = ['/* MAIN FUNCTION FOR LOADING MATRICES USED BY ' Device ' CODE */ \n\n'];
fprintf(fid,word);

word = [];
NumVarsCount = 0;
%Prints the function in the .h file
for i = 1:length(GetMatrices)
    
    %Updates vaiables counter
    NumVarsCount = NumVarsCount + 1;
    %First element must be followed by the function name
    if i == 1
        NameVar = [RetType ' ' 'get' EngineName Device 'Mtx(' ArgType ' *' char(GetMatrices(i)) ', '];
        word = [word NameVar];
    %Verifies if the total amount of variables in a line equals 10
    elseif NumVarsCount == VarsPerLine && i ~= length(GetMatrices)
        %Counter is reset
        NumVarsCount = 0;
        %New line must be started next
        NameVar = [ArgType ' *' char(GetMatrices(i)) ', ' '\n     '];
        word = [word NameVar];
        fprintf(fid,word);
        %Word is emptyed
        word = [];
    %Prints last variable    
    elseif i == length(GetMatrices)
        NameVars = [ArgType ' *' char(GetMatrices(i)) ');'];
        word = [word NameVars];
        fprintf(fid,word);
    else
        %Gets the variable name
        NameVar = [ArgType ' *' char(GetMatrices(i)) ', '];
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

%--------------------------------
%GENERATES C CODE FOR getXXXMtx.c
%--------------------------------

%Builds word for generating .c file
word = [cFolderName File_Sep 'get' EngineName Device 'Mtx.c'];
%Builds word for printing after .c file is successfuly created
fileword = ['FILE ' word ' GENERATED'];
%Creates .c file
fid = fopen(word,'w');

%PRINTS FUNCTION INCLUDES
word = '\n#include <math.h>\n';
fprintf(fid,word);
word = '\n#include "../../FADEC_Defines_H/FloatPoint_Precision.h"\n';
fprintf(fid,word);
word = ['#include "' '..' hFolderNameInclude 'get' EngineName Device '.h"\n\n'];
fprintf(fid,word);

%PRINTS FUNCTION DECLARATION
word = [];
NumVarsCount = 0;
%Prints the function in the .h file
for i = 1:length(GetMatrices)
    
    %Updates vaiables counter
    NumVarsCount = NumVarsCount + 1;
    %First element must be followed by the function name
    if i == 1
        NameVar = [RetType ' ' 'get' EngineName Device 'Mtx(' ArgType ' *' char(GetMatrices(i)) ', '];
        word = [word NameVar];
    %Verifies if the total amount of variables in a line equals 10
    elseif NumVarsCount == VarsPerLine && i ~= length(GetMatrices)
        %Counter is reset
        NumVarsCount = 0;
        %New line must be started next
        NameVar = [ArgType ' *' char(GetMatrices(i)) ', ' '\n     '];
        word = [word NameVar];
        fprintf(fid,word);
        %Word is emptyed
        word = [];
    %Prints last variable    
    elseif i == length(GetMatrices)
        NameVars = [ArgType ' *' char(GetMatrices(i)) ')'];
        word = [word NameVars];
        fprintf(fid,word);
    else
        %Gets the variable name
        NameVar = [ArgType ' *' char(GetMatrices(i)) ', '];
        word = [word NameVar];
    end
    
end

%Prints beginning bracket
word = '\n\n';
fprintf(fid,word);
word = '{';
fprintf(fid,word);

%Prints the functions in a .h file
for i = 1:length(GetMatrices)
    NameVar = char(GetMatrices(i));
    ArgName = GetMatrices{i};
    PrtFuncName(fid,EngineName,NameVar,'',ArgName,'');
end

%Prints ending bracket
word = '\n\n';
fprintf(fid,word);
word = '}';
fprintf(fid,word);
word = '\n\n';
fprintf(fid,word);

%closes the generated .c file
fclose(fid);
%Prints message informing that .c file has been successfuly created
disp(' ')
disp(fileword)

%---------------------------------------
%GENERATES CALL getXXXMtx.c IN TWO CASES
%---------------------------------------


%Builds word for generating .c file
word = [CallsFolderName File_Sep 'Call_get' EngineName Device 'Mtx.txt'];
%Builds word for printing after .c file is successfuly created
fileword = ['FILE ' word ' GENERATED'];
%Creates .c file
fid = fopen(word,'w');

ArgType = '';
RetType = '';

%PRINTS FUNCTION CALLING FOR POINTERS

%
word = '\n\n';
fprintf(fid,word);
word = ['CALLING get' EngineName Device 'Mtx.c ' 'USING POINTERS AS ARGUMENTS'];
fprintf(fid,word);
word = '\n\n';
fprintf(fid,word);

word = [];
NumVarsCount = 0;
%Prints the function call in the .txt file
for i = 1:length(GetMatrices)
    
    %Updates vaiables counter
    NumVarsCount = NumVarsCount + 1;
    %First element must be followed by the function name
    if i == 1
        NameVar = [RetType ' ' 'get' EngineName Device 'Mtx(' ArgType '' char(GetMatrices(i)) ', '];
        word = [word NameVar];
    %Verifies if the total amount of variables in a line equals 10
    elseif NumVarsCount == VarsPerLine && i ~= length(GetMatrices)
        %Counter is reset
        NumVarsCount = 0;
        %New line must be started next
        NameVar = [ArgType '' char(GetMatrices(i)) ', ' '\n     '];
        word = [word NameVar];
        fprintf(fid,word);
        %Word is emptyed
        word = [];
    %Prints last variable    
    elseif i == length(GetMatrices)
        NameVars = [ArgType '' char(GetMatrices(i)) ')'];
        word = [word NameVars];
        fprintf(fid,word);
    else
        %Gets the variable name
        NameVar = [ArgType '' char(GetMatrices(i)) ', '];
        word = [word NameVar];
    end
    
end

word = ';';
fprintf(fid,word);

%PRINTS FUNCTION CALLING FOR VARIABLES AS ARGUMENTS

%
word = '\n\n';
fprintf(fid,word);
word = ['CALLING get' EngineName Device 'Mtx.c ' 'USING VARIABLES AS ARGUMENTS'];
fprintf(fid,word);
word = '\n\n';
fprintf(fid,word);

word = [];
NumVarsCount = 0;
%Prints the function call in the .txt file
for i = 1:length(GetMatrices)
    
    %Updates vaiables counter
    NumVarsCount = NumVarsCount + 1;
    %First element must be followed by the function name
    if i == 1
        NameVar = [RetType ' ' 'get' EngineName Device 'Mtx(' ArgType '&' char(GetMatrices(i)) ', '];
        word = [word NameVar];
    %Verifies if the total amount of variables in a line equals 10
    elseif NumVarsCount == VarsPerLine && i ~= length(GetMatrices)
        %Counter is reset
        NumVarsCount = 0;
        %New line must be started next
        NameVar = [ArgType '&' char(GetMatrices(i)) ', ' '\n     '];
        word = [word NameVar];
        fprintf(fid,word);
        %Word is emptyed
        word = [];
    %Prints last variable    
    elseif i == length(GetMatrices)
        NameVars = [ArgType '&' char(GetMatrices(i)) ')'];
        word = [word NameVars];
        fprintf(fid,word);
    else
        %Gets the variable name
        NameVar = [ArgType '&' char(GetMatrices(i)) ', '];
        word = [word NameVar];
    end
    
end

word = ';';
fprintf(fid,word);

%PRINTS FUNCTION CALLING FOR VARIABLES AS ARGUMENTS

%
word = '\n\n';
fprintf(fid,word);
word = ['CALLING get' EngineName Device 'Mtx.c ' 'USING VARIABLES AS ARGUMENTS'];
fprintf(fid,word);
word = '\n\n';
fprintf(fid,word);

word = [];
NumVarsCount = 0;
%Prints the function call in the .txt file
for i = 1:length(GetMatrices)
    
    %Updates vaiables counter
    NumVarsCount = NumVarsCount + 1;
    %First element must be followed by the function name
    if i == 1
        NameVar = [RetType ' ' 'get' EngineName Device 'Mtx(' ArgType '&' char(GetMatrices(i)) '[0], '];
        word = [word NameVar];
    %Verifies if the total amount of variables in a line equals 10
    elseif NumVarsCount == VarsPerLine && i ~= length(GetMatrices)
        %Counter is reset
        NumVarsCount = 0;
        %New line must be started next
        NameVar = [ArgType '&' char(GetMatrices(i)) '[0], ' '\n     '];
        word = [word NameVar];
        fprintf(fid,word);
        %Word is emptyed
        word = [];
    %Prints last variable    
    elseif i == length(GetMatrices)
        NameVars = [ArgType '&' char(GetMatrices(i)) '[0])'];
        word = [word NameVars];
        fprintf(fid,word);
    else
        %Gets the variable name
        NameVar = [ArgType '&' char(GetMatrices(i)) '[0], '];
        word = [word NameVar];
    end
    
end

word = ';';
fprintf(fid,word);

word = '\n\n';
fprintf(fid,word);

%closes the generated .c file
fclose(fid);
%Prints message informing that .c file has been successfuly created
disp(' ')
disp(fileword)

end

