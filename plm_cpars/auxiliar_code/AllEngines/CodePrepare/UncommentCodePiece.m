function LinesUpdate = UncommentCodePiece(Lines)
%UncommentCodePiece - Uncomments the specified code piece commented with
%'//'

%Starting and end commands
StartCommand = '/******** UNCOMMENT START ';
EndCommand = '/******** UNCOMMENT END ';
%Initiates updated lines with current lines
LinesUpdate = Lines;
%Replacement characters
Original = '//';
Replace = '';

for i = 1:length(Lines)
    
    %Disables cpying of code piece
    UncommentEneable = 0;
    
    %Turns current line into char
    LineChar = char(Lines(i));
    %Line containing the same number of chars as start command
    LineCharStart = LineChar(1:min(length(StartCommand),length(LineChar)));
    %Line containing the same number of chars as end command 
    LineCharEnd = LineChar(1:min(length(EndCommand),length(LineChar)));
    
    %Conditional for finding start command
    if strcmp(StartCommand,LineCharStart)
        %Computes the low uncomment index
        ILReplace = i+1;
    end
    
    %Conditional for finding end command
    if strcmp(EndCommand,LineCharEnd)
        %Computes the high uncomment index
        IHReplace = i-1;
        %Eneables copy action
        UncommentEneable = 1;
    end
    
    %Conditional for copying the identified code piece to destination
    %folder
    if UncommentEneable == 1
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

