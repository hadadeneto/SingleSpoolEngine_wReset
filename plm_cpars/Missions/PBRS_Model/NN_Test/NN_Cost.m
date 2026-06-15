function result = NN_Cost(x1,x2,y,w1,w2,b)
%NN_COST Summary of this function goes here
%   Detailed explanation goes here

    
%Initiates result
result = 0;
%
for i = 1:length(x1)
    calc = (x1(i) * w1 + x2(i) * w2 + b);
    d = calc  - y(i);
    result = result + d * d;
end
%Cost result
result = result / length(x1);

end

