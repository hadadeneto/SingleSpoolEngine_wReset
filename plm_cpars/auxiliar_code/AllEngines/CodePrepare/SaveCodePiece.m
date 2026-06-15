function SaveCodePiece(Lines,CodePieceFolder)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

%Starting and end commands
StartCommand = '/******** SAVETO START: ';
EndCommand = '/******** SAVETO END: ';
%Initiates the file name with empty value
FileName = [];

%Saves current path
CurPath = pwd;

for i = 1:length(Lines)
    
    %Disables cpying of code piece
    CopyEneable = 0;
    
    %Turns current line into char
    LineChar = char(Lines(i));
    %Line containing the same number of chars as start command
    LineCharStart = LineChar(1:min(length(StartCommand),length(LineChar)));
    %Line containing the same number of chars as end command 
    LineCharEnd = LineChar(1:min(length(EndCommand),length(LineChar)));
    
    %Conditional for finding start command
    if strcmp(StartCommand,LineCharStart)
        %Computes the low copy index
        ILCopy = i+1;
        %High file name index
        IL = length(StartCommand) + 1;
        %Low file name index
        IH = find(LineChar==' ',1,'last')-1;
        %Creates file name
        FileName = LineChar(IL:IH);
        %Adds file extension
        FileName = [FileName '.c'];
    end
    
    %Conditional for finding end command
    if strcmp(EndCommand,LineCharEnd)
        %Computes the high copy index
        IHCopy = i - 1;
        %
        CopyEneable = 1;
    end
    
    %Conditional for copying the identified code piece to destination
    %folder
    if CopyEneable == 1
        %Separates the copde piece from the whole code
        CodePiece = Lines(ILCopy:IHCopy);
        %Must replace all '\n' by '\\n'
        for j = 1:length(CodePiece)
            LineAux = ReplacePiece(char(CodePiece(j)),'\n','\\n');
            CodePiece(j) = cellstr(LineAux);
        end
        %Goest to code piece folder
        cd(CodePieceFolder)
        %Opens file with FileName
        fid = fopen(FileName,'w');
        %Writes lines to file
        WriteLines(CodePiece,fid);
        %Closes file
        fclose(fid);
        %Returns to initial path
        cd(CurPath);
    end
    
end

%Returns to initial path
cd(CurPath);

end

