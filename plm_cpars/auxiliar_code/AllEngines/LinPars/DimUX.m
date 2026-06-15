function [DimX,DimU] = DimUX(AMtx,BMtx,NcMtx)
%DimUX - Calculates the dimensions of state-variable and actuation variable
%from A and B state matrices and corrected speed matrix

%Gets size of A
[~,Acol] = size(AMtx);
%Gets size of B
[~,Bcol] = size(BMtx);
%Gets size of NcMtx
[~,Nccol] = size(NcMtx);

%Calculates dimensions of state-variable and actutaion variable
DimX = Acol / Nccol;
DimU = Bcol / Nccol;


end

