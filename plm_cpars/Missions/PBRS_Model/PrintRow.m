function PrintRow(fid,Row)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%Prints a row in the file idendifyed by fid
for i = 1:length(Row)
    word = [num2str(Row(i)) '; ' ];
    fprintf(fid,word);
end
%Prints a line for jumping to next line
fprintf(fid,'\n');

end

