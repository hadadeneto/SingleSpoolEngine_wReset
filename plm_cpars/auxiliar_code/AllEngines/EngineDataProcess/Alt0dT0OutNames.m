function [Alt0dT0LinesOut,VarNames] = Alt0dT0OutNames(Alt0dT0Lines,NewFuncName)
%Alt0dT0OutNames generates the calling of new function based on Alt0dT0 for
%storing data at the correct output variables

%Gets the length of input lines and starts output variable
col = length(Alt0dT0Lines);
Alt0dT0LinesOut = Alt0dT0Lines;
VarNames = [];


for i = 1:col
    %Creates auxiliar variable for line content
    LineCallAux = [];
    %Auxiliar line characters is initiated
    AuxLine = char(Alt0dT0Lines(i));
    %Finds indexes for ','
    IC = find(ismember(AuxLine,','));
    %Find indexes for ' '
    IS = find(ismember(AuxLine,' '));
    %Evaluates every variable, which preceeds a ','
    for j = 1:length(IC)
        %Initiates initial word of current line with empty
        InitWord = [];
        %For the first ',', it must be evaluated if a '[' is present before
        %the variable
        if j == 1
            %Initiates lower index with 1
            IL = 1;
            %Verifies if the '[' is present 
            IB = find(ismember(AuxLine,'['));
            %If '[' is present, the first variable begins right after IB
            %index
            if ~isempty(IB)
                %Lower index is IB + 1
                IL = IB + 1;
                %Initial word must be the '['
                InitWord = '[';
            end  
        else
            %If j not equal 1, IB receives the current space index
            IB = IS(j-1);
            %The variable start right after space character
            IL = IB + 1;
        end
        
        %Auxiliar vairable contains current variable name
        AuxVar = AuxLine(IL:IC(j)-1);
        %Name to be added to variable name
        MtxWord = 'Mtx';
        %MtxWord is concatenated to AuxVar
        if strcmp(AuxVar,'MN')
            MtxWord = 'LinVec';
        else
            VarNames = [VarNames cellstr([AuxVar MtxWord])];
        end
        %Final word, in this case, must be a ',', which separates the
        %variables
        CloseWord = ', ';
        %If j is the final index of IC, verifies if ']' or '...' are
        %present
        if j == length(IC)
            %Verifies which elements are present
            IB = find(ismember(AuxLine,']'));
            ID = find(ismember(AuxLine,'.'));
            %Verifies if ']' is present
            if ~isempty(IB)
                %The last variable must be included, since it does not
                %follow a ',' like the others
                LastVar = [AuxLine(IC(j):IB(end)-1) MtxWord];
                %If ']' is present, function name followed by ',' must be
                %the closing word
                CloseWord = [LastVar AuxLine(IB(end)) ' = ' NewFuncName ';'];
            end
            %Verifies if '.' is present
            if ~isempty(ID)
                %In this case, the word ', ...' must be the final word
                CloseWord = [', ' AuxLine(ID)];
            end
        end
        %Variable containing the cells of each line content is updated
        LineCallAux = [InitWord LineCallAux AuxVar MtxWord CloseWord];

    end
    %Output variable containing all line cells is uptdated
    Alt0dT0LinesOut(i) = cellstr(LineCallAux);
end

end

