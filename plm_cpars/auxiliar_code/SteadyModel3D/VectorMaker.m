function NewVec = VectorMaker(BPNew,BPOrigin,VecOrigin)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%New vector is initiated with zeros
NewVec = zeros(1,length(BPNew));

for i = 1:length(BPNew)
    %If the new breakpoint lies within the bounds of the original
    %breakpoint vector, the value must be calculated
    if(BPNew(i) >= BPOrigin(1))&&(BPNew(i) <= BPOrigin(end))
        %Finds the indexes bounding the new breakpoint value
        IH = find(BPNew(i) < BPOrigin,1,'First');  
        IL = IH - 1;
        %Calculates the needed fractional value
        f = (BPNew(i) - BPOrigin(IL))/(BPOrigin(IH) - BPOrigin(IL));
        %Calculates tne new vector value
        NewVec(i) = VecOrigin(IL) + f * (VecOrigin(IH) - VecOrigin(IL));     
    end
end

end

