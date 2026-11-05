function Output = UpdtContConstPars(EngConsts,ConstComments,BackupPath,AutoUpdtCommand)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%Initiates Output with 1;
Output = 0;
%Upper case alphabet
AllChars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz1234567890';

%Opens ContConstPars.m
fid = fopen('ContConstPars.m','r');
%Read file lines
FileLines = ReadLines(fid);
%Closes file
fclose(fid);
%Variable to containg all ContConstantPar.m constants
CCPars = [];
iCCPars = [];
%Variable to contain the last line number containing 'ContConst->'
LastLine = 0;

%Loop for separating all parameters
for i = 1:length(FileLines)
    %Reads characters from current file line
    Chars = FileLines{i};
    
    %Updates LastLine with the maximum value between the current line
    %index and the previous value of LastLine
    if(contains(Chars,'];'))
        LastLine = max(i,LastLine);
    end
    
    %Verifies if 'ContConst->' is present on current line text
    if (contains(Chars, 'ContConst->'))         
        %Find indexes of '{'
        [~,iO] = find(double(Chars) == 123);
        %Find indexes of '}'
        [~,iC] = find(double(Chars) == 125);
        %Calculates low and high indexes
        iL = iO(end) + 2;
        iH = iC(end) - 2;
        %Stores element
        CCPars = [CCPars; {Chars(iL:iH)}];
        iCCPars = [iCCPars i];
    end
    
end


%Gets the constants that should be deleted from ContConstPars.m
[DelConsts,iDel] = setdiff(CCPars,EngConsts);

%Output receives additional 1 if any constants have been subtracted
if ~isempty(DelConsts)
    Output = Output + 1;
end

% Loop for 
for i = 1:length(DelConsts)
    %
    Char = DelConsts{i};
    %
    Valid = 1;
    %
    for j = 1:length(Char)
        %
        if ~contains(AllChars,Char(j))
            Valid = 0;
            Output = Output - 1;
            break;
        end
    end
    %
    if Valid == 0
        continue;
    end
    %
    idx = iCCPars(iDel(i));
    %
    %     NewCode = [FileLines(1:iDel-1) FileLines(iDel+1)];
    FileLines(idx) = [];
    %
    LastLine = LastLine - 1;
end

%Gets the additional constants present in EngConst and not present in
%CCPars
[AddConsts,iAdd] = setdiff(EngConsts,CCPars);
%Declares variables to contain the constants names to be automatically 
%added in ContConstPars.m
AutoAdd = [];

%Loop for evaluating if constants must be automatically added
for i = 1:length(AddConsts)
    %Reads the comment from cell
    Chars = ConstComments{iAdd(i)};
    
    %Verifies if the commented part contains command for adding the
    %constant automatically
    if ~isempty(Chars) && contains(Chars,AutoUpdtCommand)
        %Computes both constant name and comment to be added
        AutoAdd = [AutoAdd;AddConsts(i)];
    end
    
end

%Output receives additional 2 if any constants are to be added
if ~isempty(AutoAdd)
    Output = Output + 2;
end

%Stores first part of FileLines in NewCode
NewCode = FileLines(1:LastLine);

%
for i = 1:length(AutoAdd)
    %Characters containing the read constan name
    ConstChar = AutoAdd{i};
    %Index array for finding upper case letters
    idx = find(double(ConstChar) == 95);
    iUp = idx + 1;
    %Lower case C constant
    LCName = [];
    
    %Loop for elaborating name of C constant
    for j = 1:length(ConstChar)
        
        % Verifies if the characther is not a '_'
        if char(ConstChar(j))~=95
   
            %If j is not one of the iUp indexes, the char must be lower
            %case
            if ismember(j,iUp)
                LCName = [LCName ConstChar(j)];
            else
                LCName = [LCName lower(ConstChar(j))];
            end
            
        end
    end
    
    %ContConstAll = [ContConstAll; {'ContConst->StrtInit'},{'_STRTINIT'};...
    NewCode = [NewCode; 'ContConstAll = [ContConstAll; {''ContConst->' LCName '''},{''' ConstChar '''}];'];
end

%Complements the lines of the new code
NewCode = [NewCode; FileLines((LastLine+1):end)];

if Output ~= 0
    %Writes both original and backup file paths
    OriginalFilePath = [pwd filesep 'ContConstPars.m'];
    BackupFilePath = [BackupPath filesep 'ContConstPars.m'];
    %Copies original .m file into backup folder
    copyfile(OriginalFilePath,BackupFilePath,'f');
    %Opens file for writing
    fid = fopen('ContConstPars.m','w');
    %Write new code lines to original file
    WriteLines(NewCode,fid);
    %Closes file
    fclose(fid);
end

end

