
%--------------------------
%UPDATING OF ConstantsXXX.h
%--------------------------

%The following code updates the file ConstantsXXX.h (where XXX corresponds
%to the chosen engine) with new values of vector sizes and design point
%values of mechanical rotation speed ant nozzle throat area

%Cells the name of constants file and MtxSizes (source file)
ConstHFile = cellstr(['Constants' EngineName '.h']);
SizeFile = cellstr('MtxSizes.txt');
%Copies constants file to temporary file
SourceFile = HostEngConstPath;
SinkFile = EngTempPath;
FuncList = ConstHFile;
CopyCFunc(SourceFile,SinkFile,FuncList);
%Copies source file to temporary file
SourceFile = EngMtxSizePath;
SinkFile = EngTempPath;
FuncList = SizeFile;
CopyCFunc(SourceFile,SinkFile,FuncList);

%Computes pathes of source and sink files
EngConstTempFile = [EngTempPath filesep char(ConstHFile)];
EngSizeTempFile = [EngTempPath filesep char(SizeFile)];
%Reads sink file lines
fid = fopen(EngConstTempFile);
FileConstLines = ReadLines(fid);
%Closes file
fclose(fid);
%Reads source file lines
fid = fopen(EngSizeTempFile);
FileSizeLines = ReadLines(fid);
%Closes file
fclose(fid);

%Finds the first line to be replaced in sink file
FirstLineIndex = find(ismember(FileConstLines,FileSizeLines(1)));
%Replace the lines in the sink storage cell array
FileConstLines = ReplaceRows(FileSizeLines,FileConstLines,[FirstLineIndex length(FileSizeLines)+FirstLineIndex-1]);

%Creates a new file equivalent to the original sink file outside temp
%folder
word = [EngConstPath filesep 'Constants' EngineName '.h'];
fid = fopen(word,'w');
%Writes the updated lines in final sink file
WriteLines(FileConstLines,fid);
fclose(fid);

%Removes temporary file
if exist(EngTempPath, 'dir')
    rmdir(EngTempPath,'s')
end