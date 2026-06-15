function WriteLines(Source,fid)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

%Loop for printing source lines to file
for i = 1:length(Source)    
    %Prints current line to file
    word = [char(Source(i)) '\n'];
    %Looks for %symbols for replacing them
    word = ReplacePercent(word);
    %Prints line
    fprintf(fid,word);
end

end

