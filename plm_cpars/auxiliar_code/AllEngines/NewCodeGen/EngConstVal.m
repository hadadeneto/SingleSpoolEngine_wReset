function Value = EngConstVal(Var,fid)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%Initiates output
Value = [];
%Read file content
FileLines = ReadLines(fid);

%Loop for finding the corresponding line
for i = 1:length(FileLines)
    %Auxiliar character
    CharAux = char(FileLines(i));
    %Final index
    IH = min(length(CharAux),length(Var));
    %Find the indexes of variable name matching
    DefPart = CharAux(1:IH);
    %Verifies if the line contains the exact variable
    if strcmp(DefPart,Var)
        %Gets the value part from the line
        ValPart = CharAux(IH+1:end);
        %Finds if there are any C comment characters after value
        %declaration
        ID = find(ismember(ValPart,'/'));
        %Gets only numeric part in ValPart
        if ~isempty(ID)
            ValPart = ValPart(1:ID-1);
        end
        %Findes indexes limiting value
        IL = find(isstrprop(ValPart,'Digit'),1,'First');
        IH = find(isstrprop(ValPart,'Digit'),1,'Last');
        %Stores value 
        Value = str2double(ValPart(IL:IH));
    end
end

end

