function LinesUpdate = CommentCodePiece(Lines)
%ExcludeCodePiece - Excludes specified part from code

%Starting and end commands
StartCommand = '/******** COMMENT START ';
EndCommand = '/******** COMMENT END ';
%Initiates updated lines with current lines
LinesUpdate = Lines;

for i = 1:length(Lines)
    
    %Disables cpying of code piece
    CommentEneable = 0;
    
    %Turns current line into char
    LineChar = char(Lines(i));
    %Line containing the same number of chars as start command
    LineCharStart = LineChar(1:min(length(StartCommand),length(LineChar)));
    %Line containing the same number of chars as end command 
    LineCharEnd = LineChar(1:min(length(EndCommand),length(LineChar)));
    
    %Conditional for finding start command
    if strcmp(StartCommand,LineCharStart)
        %Computes the low copy index
        ILExclude = i;
    end
    
    %Conditional for finding end command
    if strcmp(EndCommand,LineCharEnd)
        %Computes the high copy index
        IHExclude = i;
        %Eneables copy action
        CommentEneable = 1;
    end
    
    %Conditional for copying the identified code piece to destination
    %folder
    if CommentEneable == 1
        %Previous part of updated lines
        LinesUp = LinesUpdate(1:ILExclude);
        %Posterior part of updtated lines
        LinesDown = LinesUpdate(IHExclude:end);
        %Separates code to be commented
        LinesCommented = LinesUpdate(ILExclude+1:IHExclude-1);
        %Loop for commenting code piece
        for j = 1:length(LinesCommented)
            %Comments current line
            LineChar = char(LinesCommented(j));
            LineChar = ['//' LineChar];
            LinesCommented(j) = cellstr(LineChar);
        end
        %Complete updated lines
        LinesUpdate = [LinesUp; LinesCommented; LinesDown];
        
    end
    
end

end

