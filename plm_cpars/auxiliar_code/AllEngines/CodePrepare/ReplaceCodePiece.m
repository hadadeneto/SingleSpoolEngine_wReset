function LinesUpdate = ReplaceCodePiece(Lines)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

%Starting and end commands
StartCommand = '/******** REPLACE START: ';
EndCommand = '/******** REPLACE END: ';
%Initiates updated lines with current lines
LinesUpdate = Lines;

for i = 1:length(Lines)
    
    %Disables cpying of code piece
    ReplaceEneable = 0;
    
    %Turns current line into char
    LineChar = char(Lines(i));
    %Line containing the same number of chars as start command
    LineCharStart = LineChar(1:min(length(StartCommand),length(LineChar)));
    %Line containing the same number of chars as end command 
    LineCharEnd = LineChar(1:min(length(EndCommand),length(LineChar)));
    
    %Conditional for finding start command
    if strcmp(StartCommand,LineCharStart)
        %Computes the low copy index
        ILReplace = i+1;
        %High file name index
        IL = length(StartCommand) + 1;
        %Remaining characters
        Rest = LineChar(IL:end);
        %Low file name index
        IH = find(Rest==' ',1,'first')-1;
        %Text to be replaced
        Original = Rest(1:IH);
        %Updates initial index 
        IL = IH + 4 + IL;
        %Updates higher index
        IH = length(LineChar)-10;
        %Reads replace word
        Replace = LineChar(IL:IH);
    end
    
    %Conditional for finding end command
    if strcmp(EndCommand,LineCharEnd)
        %Computes the high copy index
        IHReplace = i-1;
        %Eneables copy action
        ReplaceEneable = 1;
    end
    
    %Conditional for copying the identified code piece to destination
    %folder
    if ReplaceEneable == 1
        %Loop for updating each lines from piece of code where replacements
        %must occur
        for j = ILReplace:IHReplace
            %Updates current line
            LinesAux = ReplacePiece(char(LinesUpdate(j)),Original,Replace);
            LinesUpdate(j) = cellstr(LinesAux);
        end        
    end
    
end

end

