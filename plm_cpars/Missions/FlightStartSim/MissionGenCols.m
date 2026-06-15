function MissionGenCols(Alt,MN,ThrustRef,EngineCommand,time,MissionName)


%Gets the number of rows to be printed
NumRows = length(time);
MissionNameCSV = [MissionName '.csv'];
MissionNameExcel = [MissionName '.xlsx'];

%Opens a .h document for defining the function that acquires matrices
fid = fopen(MissionNameCSV,'w');

%Defines a matrix to be written in Excel file
MtxExcel = zeros(NumRows,5);

%Prints all columns
for i = 1:NumRows
    %Edits current with the right element order
    Row = [Alt(i) MN(i) ThrustRef(i) EngineCommand(i) time(i)];
    MtxExcel(i,:) = Row;
    %Prints current row
    PrintRow(fid,Row);
end

%closes the generated .txt file
fclose(fid);
disp(' ')
word = ['FILE ' MissionName ' GENERATED'];
disp(word)
disp(' ') 

Range = ['A1:E' num2str(NumRows)];
writematrix(MtxExcel,MissionNameExcel,'Sheet',1,'Range',Range);

end