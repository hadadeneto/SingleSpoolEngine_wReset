function Tick = ReadSampleTime(Path,File)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%Default value for Tick
Tick = 200;
%Reads current path
CurPath = pwd;
%Goes to 
cd(Path)
%Opens file
fid = fopen(File);
%Starts tline with a valid character
tline = 'Begin!';
%Defines part of the line containing the variable of interest
word = '#define TICK';

%while loop for searchin lines
while ischar(tline)
    %Reads current line
    tline = fgetl(fid);
    %Verifies if tline is a character
    if(ischar(tline))
        %Verifies if the length of tline is larger then word's length
        if length(tline) >= length(word)
            %reads the line part of interest
            aux = tline(1:length(word));
            %Must leave the while loop if the variable has been found
            if strcmp(aux,word)
                break;
            end
        end
        
    end
end

%Finds the index of last space between the variable TICK and its value
IH = max(find(tline == '	',1,'Last'),find(tline == ' ',1,'Last'));
%Reads Tick value
Tick = str2double(tline(IH:end));
%Closes file
fclose(fid);
%Comes back to current path
cd(CurPath)


end

