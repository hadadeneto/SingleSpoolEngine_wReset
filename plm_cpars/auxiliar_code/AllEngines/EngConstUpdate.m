
%Adds paths
word = [pwd filesep, 'NewCodeGen'];
addpath(word);
%Sets host folders
SetHostFolder;
%Sets engine list
SetEngineList;
%Saves current path and rises two folder levels
CurrPath = pwd;
cd .. 
cd ..
%
BackupPath = [pwd filesep BackupFolder];
%Goes to folder where base file is stored
word = [HostFolder filesep ConstantsHBase];
cd(word)
%Opens the base .h file for engine constants
fid = fopen('ConstantsBase.h','r');
%fid = fopen('TesteBase.h');
%Reads constants, values, comments and code lines
[ConsNameBase,ConsValBase,ConsComBase,LineNumBase,...
    ComLinesBase,FlagLinesBase,ComLinesNumBase,FlagLinesNumBase] = ConstantsHRead(fid);
%Closes file
fclose(fid);
%Goes to upper level folder
cd ..;

%Maximum number of characters between first code line position and
%constant's value - for right tabulation
MAX_CHARS_VAL = 50;
MAX_CHARS_COMMENT = 15;
%Selects the variable comments either from the base file or from the
%existing engine constants file
COMMENTS_FROM_BASE = 0;

%Gets date and time
DateTimeCell = GetDateTime;

%LOOP FOR GOING THROUGH EVERY ENGINE

%Sets backup path
BackupPath = [BackupPath filesep 'ConstantsH_' char(DateTimeCell)];
%Generates backup folder
CodeGenMkDir(BackupPath,[])

%Loop for reading every engine's constants file, comparing and making the
%necessary modifications
for i = 1:length(EngineNameList)
    %Reads current engine name
    EngName = EngineNameList{i};
    %Stores in word the file path
    word = [EngName filesep 'FADEC_Constants_H'];
    %Goes to engine folder
    cd(word)
    %Stores in word the name of the file to be opened
    word = ['Constants' EngName '.h'];
    EngFileName = word;
    %word = ['Teste' EngName '.h'];
    %Adds file name to path
    BackupFilePath = [BackupPath filesep word];
    %Sets the path of existing constants .h file
    OldConstPath = [pwd filesep word];
    %Copies existing constants .h file into backup folder
    copyfile(OldConstPath,BackupFilePath,'f');
    %Opens the base .h file for engine constants
    fid = fopen(word,'r');
    %Reads constants, values, comments and code lines
    [ConsNameEng,ConsValEng,ConsComEng,LineNumEng,...
        ComLinesEng,FlagLinesEng,ComLinesNumEng,FlagLinesNumEng] = ConstantsHRead(fid);
    %Closes file
    fclose(fid);
    %Declares empty variables for new code
    ConsNameNew = [];
    ConsValNew  = [];
    LineNumNew  = [];
    ConsComNew  = [];
    ConsSpacesNew  = [];
    ComSpacesNew   = [];
    CodeNew = [];
    
    %Loop for finding the index of each
    for j = 1:length(ConsNameBase)
        %Adds engine name to constant
        ConsNameChar = [EngName ConsNameBase{j}];
        %Calculates the number of spaces to be placed between constant name
        %and constant value
        SpacesLeft = max(1,(MAX_CHARS_VAL - length(ConsNameChar)));
        %Computes number of characters in ConsNameChar
        ConsSpacesNew = [ConsSpacesNew {char(32 * ones(1,SpacesLeft))}];
        %Updates new constants with base member
        ConsNameNew = [ConsNameNew;{ConsNameChar}];
        %Updates new constant comments with base member
        ConsComNew = [ConsComNew;ConsComBase(j)];
        %Updates new line number with base data
        LineNumNew =  [LineNumNew;LineNumBase(j)];
        %Verifies if current constant is a member of the engine's list
        [membOK,idx] = ismember(ConsNameBase(j),ConsNameEng);
        %If the current constant is part of engine's list, the engine value
        %must be preserved
        if membOK
            %Updates new values with corresponding engine constant value
            ConsValNew  = [ConsValNew;ConsValEng(idx)];
            %Calculates the number of spaces between values and commentsfor
            %current line
            SpacesLeft = max(1,MAX_CHARS_COMMENT - length(ConsValEng{idx}));
            %Computes the number of spaces between values and comments for
            %current line
            ComSpacesNew = [ComSpacesNew {char(32 * ones(1,(MAX_CHARS_COMMENT - length(ConsValEng{idx}))))}];
            %If the comments of original .h file is to be preserved,
            %computes the oringal comment for current line
            if ~COMMENTS_FROM_BASE
                ConsComNew(j) = ConsComEng(idx);
            end
        else
            %Updates new values with corresponding base constant value
            ConsValNew  = [ConsValNew;ConsValBase(j)];
            %Calculates number of spaces between constant value and
            %constant comment
            SpacesLeft = max(1,MAX_CHARS_COMMENT - length(ConsValBase{j}));
            %Computes calculated number of spaces
            ComSpacesNew = [ComSpacesNew {char(32 * ones(1,(MAX_CHARS_COMMENT - length(ConsValBase{j}))))}];
        end
              
    end
    
    %PREPARATION OF NEW CODE
    
    %Preparation of new code
    iH = length(ConsNameBase) + length(ComLinesBase) + length(FlagLinesBase);
    
    %Loop for concatenating new code lines
    for j = 1:iH
        
        %Verifies if j is member of LineNumBase
        [membOK,idx] = ismember(j,LineNumBase);
        %If the current index is a member of LineNumBase, it is a constant
        if membOK
            %Prepares word contaning new line
            word = ['#define ' ConsNameNew{idx} ConsSpacesNew{idx} ConsValNew{idx} ComSpacesNew{idx} ConsComNew{idx}];
            CodeNew = [CodeNew; {word}];
            continue;
        end
        %Verifies if j is member of ComLinesNumBase
        [membOK,idx] = ismember(j,ComLinesNumBase);
        %If the current index is a member of ComLinesNumBase, it is a
        %comment
        if membOK
            %Prepares word contaning new commented line
            CodeNew = [CodeNew; ComLinesBase(idx)];
            continue;
        end
        %Verifies if j is member of FlagLineNumBase
        [membOK,idx] = ismember(j,FlagLinesNumBase);
        %If the current index is a member of FlagLinesNumBase, it is a
        %definition of flag
        if membOK
            %Prepares word contaning new line
            CodeNew = [CodeNew; FlagLinesEng(idx)];
            continue;
        end
        
    end
    
    %WRITES NEW CONTENT INTO ORIGINAL FILE
    
    %Opens file for writing
    fid = fopen(EngFileName,'w');
    %Write new code lines to original file
    WriteLines(CodeNew,fid);
    %Closes file
    fclose(fid);
    %Returns to host folder
    cd ..
    cd ..
    
end

%Goes to initial path
cd(CurrPath);
%Removes added paths
word = [pwd filesep, 'NewCodeGen'];
rmpath(word);