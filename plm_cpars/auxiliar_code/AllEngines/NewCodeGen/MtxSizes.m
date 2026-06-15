function MtxSizes(SizeMsgs,DividingIndex,SizeDefines,GetFuncMatrices,VarsPerLine,EngineName,EngFoldName,varargin)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%Opens files containing matrices sizes
word = [EngFoldName filesep 'MtxSizes.txt'];
fileword = ['FILE ' word ' GENERATED'];
fid = fopen(word,'w');

%Loop for printing
for i = 1:length(SizeDefines)
    %Prints first message
    if i == 1
        %Prints first message
        word = [char(SizeMsgs(i))];
        %Prints the word in file
        fprintf(fid,word);
    end
    %Prints separating messages
    if i == DividingIndex(i)
        %Prints first message
        word = ['\n\n' char(SizeMsgs(i))];
        %Prints the word in file
        fprintf(fid,word);
    end
    %Calculate number of elements
    value = varargin{i};
    [row,col,page] = size(value);
    NumElements = num2str(row * col * page);
    %Verifies if NDes is the current parameter
    if i == length(SizeDefines) - 1
        NumElements = num2str(value);
    end
    if i == length(SizeDefines)
        NumElements = num2str(value);
    end
    %Elaborates word do be printed
    word = ['\n' '#define ' EngineName char(SizeDefines(i)) NumElements];
    %Prints the word in file
    fprintf(fid,word);
end

% %PRINTS C CALLING OF MAIN getXXXMtx function
% 
% %Prints the desire comment above the printed C code line
% fprintf(fid,'\n\n\n\n');
% word = '/* Loads matrices */ \n';
% fprintf(fid,word);
% 
% word = [];
% NumVarsCount = 0;
% %Prints the function calling to be used in a .c file
% for i = 1:length(GetFuncMatrices)
%     
%     %Updates vaiables counter
%     NumVarsCount = NumVarsCount + 1;
%     %First element must be followed by the function name
%     if i == 1
%         NameVar = ['get' EngineName 'Mtx(' char(GetFuncMatrices(i)) ', '];
%         word = [word NameVar];
%     %Verifies if the total amount of variables in a line equals 10
%     elseif NumVarsCount == VarsPerLine && i ~= length(GetFuncMatrices)
%         %Counter is reset
%         NumVarsCount = 0;
%         %New line must be started next
%         NameVar = [char(GetFuncMatrices(i)) ', ' '\n     '];
%         word = [word NameVar];
%         fprintf(fid,word);
%         %Word is emptyed
%         word = [];
%     %Prints last variable    
%     elseif i == length(GetFuncMatrices)
%         NameVars = [char(GetFuncMatrices(i)) ');'];
%         word = [word NameVars];
%         fprintf(fid,word);
%     else
%         %Gets the variable name
%         NameVar = [char(GetFuncMatrices(i)) ', '];
%         word = [word NameVar];
%     end
%     
% end
% 
% %Prints the desire comment above the printed C code line
% fprintf(fid,'\n\n\n\n');
% word = '/* Loads matrices */ \n';
% fprintf(fid,word);
% 
% word = [];
% NumVarsCount = 0;
% %Prints the function calling to be used in a .c file
% for i = 1:length(GetFuncMatrices)
%     
%     %Updates vaiables counter
%     NumVarsCount = NumVarsCount + 1;
%     %First element must be followed by the function name    
%     if i == 1
%         NameVar = ['get' EngineName 'Mtx(' '&' char(GetFuncMatrices(i)) ', '];
%         word = [word NameVar];
%     %Verifies if the total amount of variables in a line equals 10
%     elseif NumVarsCount == VarsPerLine && i ~= length(GetFuncMatrices)
%         %Counter is reset
%         NumVarsCount = 0;
%         %New line must be started next
%         NameVar = ['&' char(GetFuncMatrices(i)) ', ' '\n     '];
%         word = [word NameVar];
%         fprintf(fid,word);
%         %Word is emptyed
%         word = [];
%     %Prints last variable    
%     elseif i == length(GetFuncMatrices)
%         NameVars = ['&' char(GetFuncMatrices(i)) ');'];
%         word = [word NameVars];
%         fprintf(fid,word);
%     else
%         %Gets the variable name
%         NameVar = ['&' char(GetFuncMatrices(i)) ', '];
%         word = [word NameVar];
%     end
%     
% end

%Closes the generated .txt file
fclose(fid);
disp(' ')
disp(fileword)

end

