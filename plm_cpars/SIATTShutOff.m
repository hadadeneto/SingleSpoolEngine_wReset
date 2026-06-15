
%Verifies the index where thrust command is not zero
IndSIATT = find((RefVecDyn > 0));
%
if ~isempty(IndSIATT)
    %Uses the corresponding time value to set a shut off command instant
    ExComTime(2) = TimeVector(IndSIATT(end));
else
    ExComTime(2) = TimeVector(end);
end






