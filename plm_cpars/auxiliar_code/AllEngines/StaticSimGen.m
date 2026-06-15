

word = [pwd filesep, 'NewCodeGen'];
addpath(word);

% %Sets the lists of projects and assiciated engine names
% ProjectList = [{'TJ1200_POC6_Boosted'},{'TF1200'},{'GEJ85'},{'TJ700'}];
% EngineNameList = [{'TJ1200'},{'TF1200'},{'GEJ85'},{'TJ700'}];
% VersionName = [{'2.10'},{'1.00'},{'1.00'},{'1.00'}];
SetEngineList;

%Text for text file creation
TextList(1) = cellstr('disp('' '')');
TextList(2) = cellstr('disp(''------------------------------------------------'')');
TextList(4) = cellstr('disp(''              External Version                  '')');
TextList(5) = cellstr('disp(''------------------------------------------------'')');
TextList(6) = cellstr('disp('' '')');

%Current path
CurPath = pwd;
%

for i = 1:length(ProjectList)
    %
    TextList(3) = cellstr(['disp(''' char(EngineNameList(i)) ' CALCULATION PROGRAM - VERSION ' char(VersionName(i)) ''')']);
    %
    NewCorrParsFile = [CurPath filesep 'Engines' filesep char(ProjectList(i))];
    %
    ConstFile = [NewCorrParsFile filesep char(EngineNameList(i)) filesep 'FADEC_Constants_H' filesep 'Constants' char(EngineNameList(i)) '.h'];
    %
    StaticSimFile = [CurPath filesep 'CodePack' filesep 'StaticSim' filesep char(EngineNameList(i))];
    %
    StaticSimPCode = [CurPath filesep 'CodePack' filesep 'StaticSimPCode' filesep char(EngineNameList(i))];
    %
    StaticGenFile = [CurPath filesep 'CodePack' filesep 'StaticSim' filesep 'StaticGenCode'];
    %
    CodeGenMkDir(StaticSimFile,[]);
    %
    CodeGenMkDir(StaticSimPCode,[]);
    %Copies CorrectedPars.mat from 
    SourceFile = NewCorrParsFile;
    SinkFile = StaticSimFile;
    FuncList = {'CorrectedPars.mat'};
    CopyCFunc(SourceFile,SinkFile,FuncList);
    
    SourceFile = StaticGenFile;
    cd(SourceFile);
    FuncListChar = ls ;
    [row,col] = size(FuncListChar);
    FuncList = cell(1,row);
    for j = 1:row
        %
        if ~strcmp(FuncListChar(j,1),'.')
            %
            FuncList(j) = cellstr(FuncListChar(j,:));
        end
    end
    %Copies functions from specified list
    CopyCFunc(SourceFile,SinkFile,FuncList); 
    %Goes to engine file
    cd(StaticSimFile);
    %Creates text file
    fid = fopen('EngVersionText.m','w');
    %Writes the file lines
    WriteLines(TextList,fid);
    
    %READS RU AND NDES PARAMETERS FROM ConstantsXXX.h
    
    %Close the file
    fclose(fid);
    %Chosen variable define word
    word = ['#define ' char(EngineNameList(i)) '_'];
    %Opens constants file
    fid = fopen(ConstFile);
    %Reads RU value
    RUVal = EngConstVal([word 'RUMIN'],fid);
    %Closes constant file
    fclose(fid);
    %Opens constant file
    fid = fopen(ConstFile);
    %Reads NDes value
    NDESVal =  EngConstVal([word 'NDES'],fid);
    %Closes constant file
    fclose(fid);
    
    %SAVES NDES AND RU PARAMETERS
    NDesRU = [];
    NDesRU.NDes = NDESVal;
    NDesRU.RU = RUVal;
    %Saves file containing NDes and RU values
    save NDesRU.mat NDesRU  
    
    %CREATES PROTECTED CODE - pcode
    
    %First, copies the complete content of .m files of current engine to
    %corresponding protected code file
    SourceFile = StaticSimFile;
    SinkFile = StaticSimPCode;
    copyfile(SourceFile,SinkFile,'f');
    
    %Reads function list
    cd(SinkFile)
    FuncListChar = ls;
    %Turns characters into cells
    [row,col] = size(FuncListChar);
    FuncList = cell(1,row);
    for j = 1:row
        %
        if ~strcmp(FuncListChar(j,1),'.')
            %
            FuncList(j) = cellstr(FuncListChar(j,:));
        end
    end
    
    %Goes through each cell
    for i = 1:length(FuncList)
        %
        FuncListElem = char(FuncList{i});
        %
        if((~strcmp(FuncListElem,"Example.m")) && (~isempty(FuncListElem)) && (strcmp(FuncListElem(end),"m")))
            pcodeword = ['pcode ' FuncListElem];
            eval(pcodeword); 
            pcodeword = ['delete(''' FuncListElem ''')'];
            eval(pcodeword);
        end
    end
           
end

cd(CurPath)

word = [pwd filesep, 'NewCodeGen'];
rmpath(word);