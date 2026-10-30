function [ConsNameCell,ConsValCell,ConsComCell,LineNum,ComLines,FlagLines,ComLinesNum,FlagLinesNum] = ConstantsHRead(fid)
%CONSTREAD Reads ConstantsXXX.h 
%   The function reads the file ConstantsXXX.h, separating the constants
%   names, their values and comments in separate variables

%Reads written code lines
ConsBase = ReadLines(fid);
%Declaration of initially  outputs
ConsNameCell = [];
ConsValCell  = [];
ConsComCell  = [];
LineNum      = [];
ComLines     = [];
FlagLines    = [];
ComLinesNum  = [];
FlagLinesNum = [];

FlagLines = [ConsBase(1); ConsBase(2); ConsBase(end)];
FlagLinesNum = [1,2,length(ConsBase)];

%Loop for finding all present constants
for i = 3:length(ConsBase)
    %Turns ConsBase into an array of characters
    ConsArray = ConsBase{i};
    
    %Verifies if the first 7 characteres correspond to #define
    if (length(ConsArray) >= 7) && strcmp(ConsArray(1:7),'#define')
        %Finds ASCII values of each character
        ConsASCII = double(ConsArray);
        %Declares empty name variable
        ConsName = [];
        ConsVal  = [];
        ConsCom  = [];
        %State machine status
        status = 0;
        
        %Loop for bulding constant name
        for j = 9:length(ConsASCII)
                       
            switch status
                
                case 0
                    %Verifies if the current character is either ' ' (9) or '    '
                    %(32)
                    if(ConsASCII(j) == 95)
                        %Updates line code number
                        ConsName = [ConsName ConsArray(j)];
                        status = 1;                        
                    end
                
                case 1
                    
                    %Verifies if the current character is either ' ' (9) or '    '
                    %(32)
                    if((ConsASCII(j) == 9) || (ConsASCII(j) == 32))
                        %Updates line code number
                        LineNum = [LineNum i];
                        status = 2;
                    else
                        %Updates name
                        ConsName = [ConsName ConsArray(j)];
                    end
                    
                case 2
                    
                    %Verifies if the current character is either ' ' (9) or '    '
                    %(32)
                    if((ConsASCII(j) ~= 9) && (ConsASCII(j) ~= 32))
                        ConsVal = [ConsVal ConsArray(j)];
                        status = 3;
                    end
                    
                case 3
                    
                    %Verifies if the current character is either ' ' (9) or '    '
                    %(32) or '/' (47)
                    if(ConsASCII(j) == 47)
                        %Updates line comment
                        ConsCom = ConsArray(j:end);
                        status = 4;
                    elseif((ConsASCII(j) ~= 9) || (ConsASCII(j) ~= 32)) 
                        %Updates constant
                        ConsVal = [ConsVal ConsArray(j)];
                    end
                    
            end
            
            
        end
        %Stores name in name cell and value in value cell
        ConsNameCell = [ConsNameCell; {ConsName}];
        ConsValCell  = [ConsValCell; {ConsVal}];
        ConsComCell  = [ConsComCell; {ConsCom}];
        
    else
        %If i is not the last code line, which is part of the flag
        %definition, it must be part of the commented lines
        if i < length(ConsBase)
            ComLines = [ComLines; ConsBase(i)];
            ComLinesNum = [ComLinesNum i];
        end
    end
    
    
end

%Filtering of values (excludes spaces)
for i = 1:length(ConsValCell)
    %Transforms into chars
    Chars = ConsValCell{i};
    CharsNew = [];
    %Loop for cleaning from spaces
    for j = 1:length(Chars)
        %If current char is not space, stores it
        if (double(Chars(j))~=32) && (double(Chars(j))~=9)
            CharsNew = [CharsNew Chars(j)];
        end
    end
    %Replaces old cell with filtered cell
    ConsValCell(i) = {CharsNew};
end

end

