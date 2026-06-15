function StringOut = CorrectPercent(string)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

Cells = cell(1,length(string));
StringOut = string;
%
for i = 1:length(string)
    %Transforms each individual char into a cell
    Cells(i) = cellstr(string(i));
end
%
Indexes = find(ismember(Cells,{'%'}));

if ~isempty(Indexes)
    %
    for i = 1:length(Indexes)
        Cells(Indexes(i)) = {'%%'};
    end
    %
    StringOut = [];
    %
    for i = 1:length(Cells)
        if ismember(Cells(i),{''})
            Cells(i) = {' '};
        end
        StringOut = [StringOut char(Cells(i))];
    end
end

end

