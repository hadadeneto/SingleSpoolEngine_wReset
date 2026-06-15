function TreatGenFunc(TempGenCodePackFold,FoldWord)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

%Saves current path
CurPath = pwd;
%Creates folder list
TempFoldList = dir(TempGenCodePackFold);
%Loop for functions treatment
for i = 1:length(TempFoldList)
    %Gets the folder name
    FoldName = TempFoldList(i).name;
    %Defines indexes where '_' is found
    IL = find(FoldName == '_',1,'first');
    IH = find(FoldName == '_',1,'last');
    %Gets word of interest from FoldName
    word = FoldName(IL:IH+1);
    %Verifies if word matches FoldWord
    if strcmp(word,FoldWord)
        %If matched, gets the paht of folder to be treated
        TreatedFolder = [TempGenCodePackFold filesep FoldName];
        %Goes to the folder to be treated
        cd(TreatedFolder)
        %Gets file list
        FileList = dir(TreatedFolder);
        %Starts updating files from 3 member of file liest, since the first
        %tow are '.' and '..'
        for j = 3:length(FileList)
            %Reads current file name
            CurFile = FileList(j).name;
            %Erases screen
            clc
            disp('TREATING FILE:')
            disp(CurFile)
            %Opens file for reading
            fid = fopen(CurFile,'r');
            %Reads file lines
            Lines = ReadLines(fid);
            %Closes file
            fclose(fid);
            %Comments inclusion of mex.h library, since it is not compiled
            %in final code
            Lines = ReplacePieceAllLines(Lines,'#include "mex.h"','//#include "mex.h"',1);
            %Replaces all \n with \\n for right use of fprintf
            Lines = ReplacePieceAllLines(Lines,'\n','\\n',length(Lines)+1);
            %Replaces all mexPrintf with printf since mexPrintf is only
            %recognized within MATLAB environment
            Lines = ReplacePieceAllLines(Lines,'mexPrintf','printf',length(Lines)+1);
            %Reopens file for writing
            fid = fopen(CurFile,'w');
            %Updates file
            WriteLines(Lines,fid);
            %Closes file
            fclose(fid);
            
        end
    end
end
%Comes back to current path
cd(CurPath);

end

