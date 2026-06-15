function CopyFromCodePiece(Lines,CodePieceFolder,FinalCodeFileName)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

%Starting and end commands
StartCommand = '/******** COPYFROM START: ';
EndCommand = '/******** COPYFROM END: ';
%Initiates the file name with empty value
FileName = [];
%Initiates updated lines with current lines
LinesUpdate = Lines;
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
        ILCopy = i;
        %High file name index
        IL = length(StartCommand) + 1;
        %Low file name index
        IH = find(LineChar==' ',1,'last')-1;
        %Creates file name
        FileName = LineChar(IL:IH);
        %Start command with file name
        StartCommandFile = [StartCommand FileName];
        %Adds file extension
        FileNameExt = [FileName '.c'];
    end
    
    %Conditional for finding end command
    if strcmp(EndCommand,LineCharEnd)
        %Computes the high copy index
        IHCopy = i;
        %Eneables copy action
        CopyEneable = 1;
        %Calculates difference between indexes
        DeltaI = IHCopy - ILCopy;
    end
    
    %Conditional for copying the identified code piece to destination
    %folder
    if CopyEneable == 1
        %Loop for updating code lines
        for j = 1:length(LinesUpdate)
            %Turns current line into char
            LineUpdateChar = char(LinesUpdate(j));
            %Line containing the same number of chars as start command
            LineUpdateCharStart = LineUpdateChar(1:min(length(StartCommandFile),length(LineUpdateChar)));
            %Verifies if the part of code to be copyied from file has been
            %found
            if strcmp(StartCommandFile,LineUpdateCharStart)
                %Defines indexes for copying piece of code
                ILCopy = j;
                IHCopy = ILCopy + DeltaI;
                %Separates the copde piece from the whole code
                LinesUp = LinesUpdate(1:ILCopy);
                LinesDown = LinesUpdate(IHCopy:end);
                %Goest to code piece folder
                cd(CodePieceFolder)
                %Opens file with FileName
                fid = fopen(FileNameExt,'r');
                %Writes lines to file
                CodePiece = ReadLines(fid);
                %Closes file
                fclose(fid);
                %Gets auxiliar lines
                LinesAux = [LinesUp; CodePiece; LinesDown];
                %Updates lines
                LinesUpdate = LinesAux;
                %Returns to initial path
                cd(CurPath);
                %Breaks inner loop for preventing futher unnecessary search
                break;
            end
        end
        
    end
    
end

%Replaces '\n' with '\\n' for correct use of printf and 'mexPrintf' with
%'printf' for correct future compilation
for i = 1:length(LinesUpdate)
    LineAux = ReplacePiece(char(LinesUpdate(i)),'\n','\\n');
    LinesUpdate(i) = cellstr(LineAux);
    LineAux = ReplacePiece(char(LinesUpdate(i)),'mexPrintf','printf');
    LinesUpdate(i) = cellstr(LineAux);
end

%Erases specified code piece
LinesUpdate = ExcludeCodePiece(LinesUpdate);
%Replaces specified code piece
LinesUpdate = ReplaceCodePiece(LinesUpdate);
%Comments specified code piece
LinesUpdate = CommentCodePiece(LinesUpdate);
%Uncomments specified code piece
LinesUpdate = UncommentCodePiece(LinesUpdate);
%Replaces Tsample for Ts
LinesUpdate = ReplacePieceAllLines(LinesUpdate,'Tsample','Ts',length(LinesUpdate)+1);

%Opens file with final code name
fid = fopen(FinalCodeFileName,'w');
%Writes the code
WriteLines(LinesUpdate,fid);
%Closes file
fclose(fid);
%Returns to initial path
cd(CurPath);

end

