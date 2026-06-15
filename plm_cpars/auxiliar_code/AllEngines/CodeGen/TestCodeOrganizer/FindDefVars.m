
function DefVars = FindDefVars(EngineName)

%--------------------
%OPENS ConstantsXXX.h
%--------------------

FileName = ['Constants' EngineName '.h'];
fid = fopen(FileName);

%-----------------------------------------------------
%FINDS ALL DEFINED VARIABLES DEFINED IN ConstantsXXX.h
%-----------------------------------------------------

%Reads first line
CurrentLine = fgetl(fid);
% disp(line_ex)
DefVars = [];
%Reads subsequent lines
while ischar(CurrentLine)
    %Reads current line
    CurrentLine = fgetl(fid);
    if CurrentLine ~= -1
        %Verifies if the engine name is present within the line
        isPart = contains(convertCharsToStrings(CurrentLine),convertCharsToStrings(['#define ' EngineName]));
        if(isPart)
            %Finds the first space and the first tab in the current line
            IL = find(CurrentLine == ' ');
            Itab = find(CurrentLine == '	');
            %There are both tabs and spaces in the line
            if ~isempty(Itab) && length(IL) >= 2
                IH = min(IL(2),Itab(1));
            %There are only spaces in the line
            elseif isempty(Itab)
                IH = IL(2);
            %There is only the space after #define in the line
            elseif length(IL) < 2
                IH = Itab(1);
            end
            %Stores the defined variable name
            DefVars = [DefVars {CurrentLine(IL+1:IH-1)}];
            
        end
    end
end

%---------------------
%CLOSES ConstantsXXX.h
%---------------------

fclose(fid);

end