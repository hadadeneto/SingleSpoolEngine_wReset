function MtxNew = MtxMaker(MtxOrigin,BPMtxOrigin,BPNew)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%Initiates the new matrix to be built
[RowO,~] = size(MtxOrigin);
MtxNew = zeros(RowO,length(BPNew));

%Builds the new matrix baed on the original one
for i = 1:RowO
    VecOrigin = MtxOrigin(i,:);
    BPOrigin = BPMtxOrigin(i,:);
    MtxNew(i,:) = VectorMaker(BPNew,BPOrigin,VecOrigin);
end

end

