function VecOut = ConcatNoRepeat(VecIn,VecConc,Name)
%ConcatNoRepeat - VecOut is the concatenation of VecIn and all members of
%VecConc not previously present in VecIn

%Initiates VecOut with VecIn
VecOut = VecIn;
%Loop for concatenating new members
for i = 1:length(VecConc)
    %Only concatenates new member of VecConc if it is not part of VecIn
    if ~ismember(VecConc(i),VecIn)
        VecOut = [VecOut VecConc(i)];
    else
        disp(' ')
        disp([char(VecConc(i)) ' is already a member of ' Name])
    end
end

end

