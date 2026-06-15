function StringOut = ReplacePiece(StringIn,Original,New)
%ReplacePiece - Replace part of an input string with another specified part

%Reads input string
String = StringIn;
%Starts delta and reads lengths
Delta = 0;
LenOr = length(Original);
LenStr = length(StringIn);

if LenStr >= LenOr
    %Loop for finding the string
    for i = 1:LenStr
        %Indexes for patrs of inlet string
        IL = i;
        IH = i + LenOr - 1;
        %High index must not be higher than length of inside string for the
        %software to work properly 
        if  IH > LenStr
            break;        
        end
        %Computes current part
        Part = StringIn(IL:IH);
        %Verifies if the original part searched equals current part
        if strcmp(Part,Original)
            Before = [];
            After = [];
            %Updates indexes according to the addition or subtraction of
            %indexes to the new string
            ILAux = IL - 1 + Delta;
            IHAux = IH + 1 + Delta;
            %Verifies if there is a before part
            if ILAux >= 1
                Before = String(1:ILAux);
            end
            %Verifies if there is an after part
            if IHAux <= length(String)
                After = String(IHAux:end);
            end
            %Updates string
            String = [Before New After];
            %Updates delta of indexes
            Delta = Delta + length(New) - length(Original);
        end
        
    end
end

%Updates output
StringOut = String;

end

