%-------------------------------------
%GENERATION OF C CODE FOR ALL MATRICES
%-------------------------------------

%Function name
FuncName = 'CodeGenAllMtx';
%Sorts for alphabetic order
AllMatrices = sort(AllMatrices);
%Word do be used as function inputs
cellsword = [{'AllMatrices'},{'GetFuncMatrices'},{'GetFuncConst'},{'VarsPerLine'},{'EngineName'}];
cellsword = [cellsword AllMatrices];
%Initiates auxiliar word
word = [];

%Loop for generating function callilng with the required arguments
for i = 1:length(cellsword)
    if i == 1
        word = [word FuncName '('];
    end
    if i == length(cellsword)
        word = [word char(cellsword(i)) ');'];
    else
        word = [word char(cellsword(i)) ','];
    end
end

%Executes function for generating C code
eval(word);