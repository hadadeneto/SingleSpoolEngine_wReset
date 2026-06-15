function FileLines = ReadLines(fid)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

FileLines = [];
tline = 'Begin!';

while ischar(tline)
    %Reads current line
    tline = fgetl(fid);
    %
    if(ischar(tline))
        %Updates FileLines
        FileLines = [FileLines; cellstr(tline)];
    end
end

end

