function Yadd = PolyExpand(Y,X,Xadd,n)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

P = polyfit(X,Y,n);
%Initiates additional Y vector with zeros
Yadd = zeros(1,length(Xadd));
%
for i = 1:length(Xadd)
    %
    Yadd(i) = 0;
    for j = 1:(n+1)
        Yadd(i) = Yadd(i) + P(j) * Xadd(i)^(n + 1 - i);
    end
end

end

