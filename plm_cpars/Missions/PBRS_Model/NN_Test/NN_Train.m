function [w1,w2,b] = NN_Train(x1,x2,y,rate,eps,NumInter)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

w1 = rand(1);
w2 = rand(1);
b = rand(1);

% Loop of training or learnig process of single neuron network */
for i = 0:NumInter
    
    % Calculate the gradient
    c = NN_Cost(x1,x2,y,w1,w2,b);
    %
    dw1 = (NN_Cost(x1,x2,y,w1 + eps,w2,b) - c)/eps;
    %dw0 = (cost(w0 + eps,w1,b) - c) / eps;
    dw2 = (NN_Cost(x1,x2,y,w1,w2 + eps,b) - c)/eps;
    db = (NN_Cost(x1,x2,y,w1,w2,b + eps) - c)/eps;
    % w moves in the opposite direction of gradient according proportionally to rate */
    w1 = w1 - rate * dw1;
    w2 = w2 - rate * dw2;
    b  = b - rate * db;
end

end

