function CodeGenSizeConst(hFolderName,cFolderName,CallsFolderName,RetType,ArgType,VarsPerLine,EngineName,Device,Level_Sep,Level_Sep_Constants,File_Sep,SizeVars,SizeDefs)
%This function gereates the .h and .c files of getXXXSizeConst
      
%------------------------------------------------------------------
%getXXXSizeConst.h - FILE CONTAINING DECLARATION OF getXXXSizeConst
%------------------------------------------------------------------

%Opens a .h document for defining the function that acquires matrices
word = [hFolderName '/' 'get' EngineName Device 'SizeConst.h'];
fileword = ['FILE ' word ' GENERATED'];
fid = fopen(word,'w');

%Prints the altitude value in first line and jumps two lines
word = ['#ifndef ' 'GET' EngineName Device 'SIZECONST_H'];
fprintf(fid,word);
fprintf(fid,'\n');
word = ['#define ' 'GET' EngineName Device 'SIZECONST_H'];
fprintf(fid,word);

%Prints the desire comment above the printed C code line
fprintf(fid,'\n\n');
word = '/* FUNCTION FOR LOADING SIZE CONSTANTS USED IN FADEC AND MODEL CODES */';
fprintf(fid,word);
fprintf(fid,'\n\n');


word = [];
NumVarsCount = 0;
%Prints the function in the .h file
for i = 1:length(SizeVars)
    
    %Updates vaiables counter
    NumVarsCount = NumVarsCount + 1;
    %First element must be followed by the function name
    if i == 1
        NameVar = [RetType ' ' 'get' EngineName Device 'SizeConst(' ArgType ' *' char(SizeVars(i)) ', '];
        word = [word NameVar];
    %Verifies if the total amount of variables in a line equals 10
    elseif NumVarsCount == VarsPerLine && i ~= length(SizeVars)
        %Counter is reset
        NumVarsCount = 0;
        %New line must be started next
        NameVar = [ArgType ' *' char(SizeVars(i)) ', ' '\n     '];
        word = [word NameVar];
        fprintf(fid,word);
        %Word is emptyed
        word = [];
    %Prints last variable    
    elseif i == length(SizeVars)
        NameVars = [ArgType ' *' char(SizeVars(i)) ');'];
        word = [word NameVars];
        fprintf(fid,word);
    else
        %Gets the variable name
        NameVar = [ArgType ' *' char(SizeVars(i)) ', '];
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
 
%-----------------------------------------------------------------
%getXXXSizeConst.c - FILE CONTAINING getXXXSizeConst FUNCTION BODY
%-----------------------------------------------------------------

%Opens a .h document for defining the function that acquires matrices
word = [cFolderName '/' 'get' EngineName Device 'SizeConst.c'];
fileword = ['FILE ' word ' GENERATED'];
fid = fopen(word,'w');

%PRINTS FUNCTION INCLUDES

word = '\n#include <math.h>\n';
fprintf(fid,word);
word = ['#include ' '"' Level_Sep_Constants 'Constants' EngineName '.h"\n'];
fprintf(fid,word);
word = ['#include ' '"' Level_Sep 'get' EngineName Device 'SizeConst.h"\n\n'];
fprintf(fid,word);
fprintf(fid,'\n\n');

%PRINTS FUNCTION HEAD

word = [];
NumVarsCount = 0;
%Prints the function in the .h file
for i = 1:length(SizeVars)
    
    %Updates vaiables counter
    NumVarsCount = NumVarsCount + 1;
    %First element must be followed by the function name
    if i == 1
        NameVar = [RetType ' ' 'get' EngineName Device 'SizeConst(' ArgType ' *' char(SizeVars(i)) ', '];
        word = [word NameVar];
    %Verifies if the total amount of variables in a line equals 10
    elseif NumVarsCount == VarsPerLine && i ~= length(SizeVars)
        %Counter is reset
        NumVarsCount = 0;
        %New line must be started next
        NameVar = [ArgType ' *' char(SizeVars(i)) ', ' '\n     '];
        word = [word NameVar];
        fprintf(fid,word);
        %Word is emptyed
        word = [];
    %Prints last variable    
    elseif i == length(SizeVars)
        NameVars = [ArgType ' *' char(SizeVars(i)) ')'];
        word = [word NameVars];
        fprintf(fid,word);
    else
        %Gets the variable name
        NameVar = [ArgType ' *' char(SizeVars(i)) ', '];
        word = [word NameVar];
    end
    
end

%PRINTS FUNCTION BODY

%Beginning of function
word = '\n{\n\n';
fprintf(fid,word);
word = ['/* Loads sizes of linearization points */'];
fprintf(fid,word);
word = '\n\n';
fprintf(fid,word);

%Initiates list for storing variable loading
List = cell(1,length(SizeVars));
%Loop for filling list elements
for i = 1:length(SizeVars)
    word = ['    *' char(SizeVars(i)) ' = ' char(SizeDefs(i)) ';\n\n'];
    List(i) = cellstr(word);
end
%Sorts for alphabetic order
List = sort(List);

%Loop for printing computation of variables describing engine matrices and
%vectors sizes
for i = 1:length(SizeVars)
%     word = ['    *' char(SizeVars(i)) ' = ' char(SizeDefs(i)) ';\n\n'];
%     fprintf(fid,word);
    word = char(List(i));
    fprintf(fid,word);
end

%end of function
word = '}';
fprintf(fid,word);
%closes the generated .c file
fclose(fid);

%Acknowledge of .c file generation
disp(' ')
disp(fileword)

%-------------------
%CALLING OF FUNCTION
%-------------------

%Builds word for generating .c file
word = [CallsFolderName File_Sep 'Call_get' EngineName Device 'SizeConst.txt'];
%Builds word for printing after .c file is successfuly created
fileword = ['FILE ' word ' GENERATED'];
%Creates .c file
fid = fopen(word,'w');

%PRINTS FUNCTION CALLING FOR VARIABLES AS ARGUMENTS

%
word = '\n\n';
fprintf(fid,word);
word = ['CALLING get' EngineName Device 'SizeConst.c ' 'USING VARIABLES AS ARGUMENTS'];
fprintf(fid,word);
word = '\n\n';
fprintf(fid,word);


word = [];
NumVarsCount = 0;
%Prints the function in the .h file
for i = 1:length(SizeVars)
    
    %Updates vaiables counter
    NumVarsCount = NumVarsCount + 1;
    %First element must be followed by the function name
    if i == 1
        NameVar = ['' ' ' 'get' EngineName Device 'SizeConst(' '' ' &' char(SizeVars(i)) ', '];
        word = [word NameVar];
    %Verifies if the total amount of variables in a line equals 10
    elseif NumVarsCount == VarsPerLine && i ~= length(SizeVars)
        %Counter is reset
        NumVarsCount = 0;
        %New line must be started next
        NameVar = ['' ' &' char(SizeVars(i)) ', ' '\n     '];
        word = [word NameVar];
        fprintf(fid,word);
        %Word is emptyed
        word = [];
    %Prints last variable    
    elseif i == length(SizeVars)
        NameVars = ['' ' &' char(SizeVars(i)) ')'];
        word = [word NameVars];
        fprintf(fid,word);
    else
        %Gets the variable name
        NameVar = ['' ' &' char(SizeVars(i)) ', '];
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





