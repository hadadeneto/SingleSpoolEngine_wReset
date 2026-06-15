function Prt3DCMtx(EngineName,MtxName,Mtx,NumElWord,ArgType,ArgName,RetType,FolderName)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%------------
% MATRIX
%------------

%Adds the engine name to the matrix name
MtxName = [EngineName MtxName];

%Opens a txt document for printing matrixes of the current altitude
%word = [MtxName '.txt'];
word = [FolderName filesep 'get' MtxName '.c'];
fileword = ['FILE ' word ' GENERATED'];
fid = fopen(word,'w');

%Prints necessary include commands
% word = '#include <math.h>';
% fprintf(fid,word);
% fprintf(fid,'\n');
% word = ['#include ' '"' IncludeType '.h"'];
% fprintf(fid,word);

% fprintf(fid,'\n');
% word = '#include "Constants.h"';
% fprintf(fid,word);

%Prints function declaration
fprintf(fid,'\n\n\n');
%word = ['struct LinMtx *get' MtxName '(void)'];
% word = ['double *get' MtxName '(double *Pointer)'];
% word = ['void ' MtxName '(double *Pointer)'];
word = [RetType ' get' MtxName '(' ArgType ' ' ArgName ')'];
fprintf(fid,word);
%Prints function beginning bracket
word = '\n{';
fprintf(fid,word);

word = '\nint i;';
fprintf(fid,word);

%Adds engine name to variable indicating the number of total elements in
%case NumElWord is a defined constant
if(isnan(str2double(NumElWord)) && ~isempty(EngineName))
    NumElWord = [NumElWord '_' EngineName];
end

%Prints function beginning bracket
word = ['\nint TotalElem = ' NumElWord ';'];
fprintf(fid,word);

%Ptints the desire comment above the printed C code line
fprintf(fid,'\n\n');
word = '/* Reallocates the required ammount of memory to the pointer */';
fprintf(fid,word);

% %Prints memory reallocation piece of code
% PointerName = ArgName(2:end);
% word = ['\n' PointerName '  = ' '(' ArgType ' *)realloc(' PointerName ', ' NumElWord '* sizeof(' ArgType '));'];
% fprintf(fid,word);

%Ptints the desire comment above the printed C code line
fprintf(fid,'\n\n');
word = '/* Matrix containing corresponding value for each breakpoint */';
fprintf(fid,word);
%Prints RPM Matix
[line,column,page] = size(Mtx);
% NumElmts = page*line*column;
%word = ['\ndouble ' MtxName '[' num2str(page) ']' '[' num2str(line) ']' '[' num2str(column) ']'];
word = ['\ndouble ' MtxName '[' NumElWord ']' ];
printxt(fid,1,page,1,line,1,column,Mtx,word);

%Prints pionter declaration
% word = ['\ndouble *' MtxName 'P = &' MtxName ';'];
% fprintf(fid,word);

%Prints for loop
word = '\n\nfor(i = 0; i < TotalElem; i++){';
fprintf(fid,word);
word = ['\n    *(' ArgName(2:end) ' + i) = *(' MtxName ' + i);'];
fprintf(fid,word);
word = '\n};';
fprintf(fid,word);

% fprintf(fid,'\n\n');
% word = 'return Pointer;';
% fprintf(fid,word);


%prints the endif command of .h files
word = '\n};';
fprintf(fid,word);

%closes the generated .txt file
fclose(fid);
disp(' ')
disp(fileword)

end

