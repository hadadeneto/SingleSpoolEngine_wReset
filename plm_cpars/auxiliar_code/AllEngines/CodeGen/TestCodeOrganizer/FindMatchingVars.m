
function [MatchDefVars,PointVars] = FindContConstVars(EngineName,FileName,DefVars)

%--------------------
%OPENS ConstantsXXX.h
%--------------------

% FileName = ['get' EngineName 'ContConst.c'];
fid = fopen(FileName);

%-----------------------------------------------------
%FINDS ALL DEFINED VARIABLES DEFINED IN ConstantsXXX.h
%-----------------------------------------------------

%Reads first line
CurrentLine = fgetl(fid);
MatchDefVars = [];
PointVars = [];
%Reads subsequent lines
while ischar(CurrentLine)
    %Reads current line
    CurrentLine = fgetl(fid);
    if CurrentLine ~= -1
        %Verifies if the charater '= XXX' is present within the line
        isPart = contains(convertCharsToStrings(CurrentLine),convertCharsToStrings(['= ' EngineName]));
        if isPart
            %Verify each defined variable to check which one is part of the line
            for i = 1:length(DefVars)
                
                %Verifies if the engine name is present within the line
                isPart = contains(convertCharsToStrings(CurrentLine),convertCharsToStrings(['= ' DefVars{i}]));
                if(isPart)
                    %Stores
                    MatchDefVars = [MatchDefVars DefVars(i)];
                    %Finds the first space and the first tab in the current line
                    Ireceives = find(CurrentLine == '=');
                    IH = Ireceives - 2;
                    %Find the variables for pointers
                    IL = find(CurrentLine == '>');
                    if ~isempty(IL)
                        IL = IL + 1;
                    else
                        IL = find(CurrentLine == '*',1,'First');
                    end
                    %Stores the defined variable name
                    PointVars = [PointVars {CurrentLine(IL:IH)}];
                    
                end
            end
        end
    end
end

%---------------------
%CLOSES ConstantsXXX.h
%---------------------

fclose(fid);

end