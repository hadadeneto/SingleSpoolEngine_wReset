function LinesUpdate = ExcludeCodePiece(Lines)
%ExcludeCodePiece - Excludes specified part from code

%Starting and end commands
StartCommand = '/******** EXCLUDE START ';
EndCommand = '/******** EXCLUDE END ';
%Initiates updated lines with current lines
LinesUpdate = Lines;
%Initiates Delta with 0
Delta = 0;

for i = 1:length(Lines)
    
    %Disables cpying of code piece
    ExcludeEneable = 0;
    
    %Turns current line into char
    LineChar = char(Lines(i));
    %Line containing the same number of chars as start command
    LineCharStart = LineChar(1:min(length(StartCommand),length(LineChar)));
    %Line containing the same number of chars as end command 
    LineCharEnd = LineChar(1:min(length(EndCommand),length(LineChar)));
    
    %Conditional for finding start command
    if strcmp(StartCommand,LineCharStart)
        %Computes the low copy index
        ILExclude = i + Delta;
    end
    
    %Conditional for finding end command
    if strcmp(EndCommand,LineCharEnd)
        %Computes the high copy index
        IHExclude = i + Delta;
        %Eneables copy action
        ExcludeEneable = 1;
    end
    
    %Conditional for copying the identified code piece to destination
    %folder
    if ExcludeEneable == 1
        %Previous part of updated lines
        LinesUp = LinesUpdate(1:ILExclude);
        %Posterior part of updtated lines
        LinesDown = LinesUpdate(IHExclude:end);
        %Complete updated lines
        LinesUpdate = [LinesUp; LinesDown];
        %Calculates Delta Exclude
        Delta = Delta - IHExclude + ILExclude - 1;
        
    end
    
end

end

