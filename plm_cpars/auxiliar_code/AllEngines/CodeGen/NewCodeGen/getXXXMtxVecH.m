function List = getXXXMtxVecH(hFolderName,EngineName,Device,RetType,ArgType,ArgName,GetMatrices)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%-----------------------------------------------------------
%getXXX.h - FILE CONTAINING DECLARATION OF ALL get FUNCTIONS
%-----------------------------------------------------------

%Opens a .h document for defining the function that acquires matrices
word = [hFolderName '/' 'get' EngineName Device '.h'];
fileword = ['FILE ' word ' GENERATED'];
fid = fopen(word,'w');

%Prints the altitude value in first line and jumps two lines
word = ['#ifndef ' 'GET' EngineName Device '_H'];
fprintf(fid,word);
fprintf(fid,'\n');
word = ['#define ' 'GET' EngineName Device '_H'];
fprintf(fid,word);

%Prints the desire comment above the printed C code line
fprintf(fid,'\n\n');
word = ['/* FUNCTIONS FOR LOADING MATRICES USED BY ' Device ' CODE */'];
fprintf(fid,word);

%Creation of function list
List = cell(1,length(GetMatrices));
%Prints the functions in a .h file
for i = 1:length(GetMatrices)
    NameVar = char(GetMatrices(i));
    FuncName = PrtFuncName(fid,EngineName,NameVar,ArgType,ArgName,RetType);
    List(i) = {FuncName};
end

%Prints the endif command of .h files
word = '\n\n#endif';
fprintf(fid,word);

%closes the generated .txt file
fclose(fid);
disp(' ')
disp(fileword)

end

