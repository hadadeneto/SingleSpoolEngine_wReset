function x = SecantMethod1D(word,fArgs,x1,x0,errMax,MaxInter)
%SecangMethod1D - Finds the roots of function f, which must be defined
%outside as a word describing the handle of a function descirbed in a .m
%file

Inter = 0;
%Defines function to be used
eval(word);
%Calculates the first two values
fArgs.x = x1;
fx1 = f(fArgs);
fArgs.x = x0;
fx0 = f(fArgs);
%Initiates error value
x = x1;
%Initiates interactions
while (Inter <= MaxInter) && (abs(fx1) > errMax)
    %Calculates next value of x2
    x = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
    %Updates values of x
    x0 = x1;
    x1 = x;
    fx0 = fx1;
    fArgs.x = x;
    fx1 = f(fArgs);
end

end

