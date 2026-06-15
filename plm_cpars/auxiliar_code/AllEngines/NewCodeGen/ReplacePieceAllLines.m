function LinesOut = ReplacePieceAllLines(LinesIn,Original,New,Times)
%ReplacePieceAllLines - Replaces a piece of line code defined by Original
%with a new one defined by New, in a number of lines defined be Times and
%in all lines defined by LinesIn. The corrected output is stored in
%LinesOut

%Initializatin
LinesOut = LinesIn;
Counter = 0;

for i = 1:length(LinesIn)
    %If the counter of replaced lines equals the maximum number of lines
    %where piece must be replace, replacement happens, or else, process
    %stops
    if Counter < Times
        %Defines input string
        StringIn = char(LinesIn(i));
        %Gets output string
        StringOut = ReplacePiece(StringIn,Original,New);
        %Replaces current line for correct one
        LinesOut(i) = cellstr(StringOut);
    else
        break;
    end
    %Updates Counter if a difference between input and output lines is
    %found
    if ~strcmp(char(StringIn),char(StringOut))
        Counter = Counter + 1;
    end
end

end

