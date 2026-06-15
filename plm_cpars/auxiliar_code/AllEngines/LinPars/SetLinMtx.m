
%Calls Alt0dT0 function directly
DirAlt0dT0Call;

%Runs correction of matrix order if necessary
FNFlip;

%For the unified model
if isempty(Pt21Mtx)
    
    Pt21Mtx = Pt3Mtx;
    Pt21CMtx = Pt3CMtx;
    Pt21DMtx = Pt3DMtx;
    Tt21Mtx = Tt3Mtx;
    Tt21CMtx = Tt3CMtx;
    Tt21DMtx = Tt3DMtx;
    
    Pt6Mtx = Pt5Mtx;
    Pt6CMtx = Pt5CMtx;
    Pt6DMtx = Pt5DMtx;
    Tt6Mtx = Tt5Mtx;
    Tt6CMtx = Tt5CMtx;
    Tt6DMtx = Tt5DMtx;
    
end
