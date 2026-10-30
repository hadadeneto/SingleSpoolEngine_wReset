function Index = FinIndex(Value,Vector,VectorLength)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

%Initiates the Index value with the highest possible
Index = VectorLength;

%Loop for searching the first element of Vector which is greater then or
%equal Value
for i = 1:VectorLength
    %If Value Vector(i) is greater then or equal Value, the value of i is
    %the value of the desired index
    if(Value <= Vector(i))
        Index = i;
        break;
    end
    
end


end

