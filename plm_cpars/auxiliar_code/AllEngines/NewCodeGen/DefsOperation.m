function CellOut = DefsOperation(CellIn,OpSig,EngineName)
%The function DefsOperation adds the engine name after each operation with
%defined eingine variables

%Transforms cell into char
CharCell = char(CellIn);
%Verifies if the math operation sign is present
IndOp = find(CharCell == OpSig);
%Defines CellOut with CellIn initially
CellOut = CellIn;
%Verifies if there are one or more multiplication signs
if ~isempty(IndOp)
    %Adds 1 to the index for considering space after '*'
    IndOp = IndOp + 1;
    EngineChar = CharCell(1:IndOp);
    %Adds engine name after each operation
    for j = 1:length(IndOp)
        %Calculates low and high indexes
        IL = IndOp(j)+1;
        IH = length(CharCell);
        %Changes high index if the current operation sign index is not the
        %last
        if j < length(IndOp)
            IH = IndOp(j+1);
        end
        %Adds AddChar
        IndOp(j) = IndOp(j) + length(EngineName);
        EngineChar = [EngineChar EngineName CharCell(IL:IH)];

    end
    %Alterates ContConstPoint(i) for having the engine name right after
    %multiplication sign
    CellOut = cellstr(EngineChar);
end

end

