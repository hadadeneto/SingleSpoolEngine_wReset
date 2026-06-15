
Example = 4;

%Defines variable s
s = zpk('s');

%DEFAULT INPUT PARAMETERS

%Defines the alpha value (wp = wc * alpha)
alpha = 1;
%Defines the gain margin
Am = 3;
%Defines phase margin
Pm = pi/3;

%TRANSFER FUNCTION

switch Example
    
    case 0
        %Example 0
        G1 = tf(1,[1 3]);
        G2 = tf(1,[1 1]);
        d = exp(-1*s);
    case 1
        %Example 1
        G1 = tf(1,1);
        G2 = tf(1,[0.12 1.33 1.24]);
        d = exp(-2*s);
    case 2
        %Example 2
        G1 = tf(1,1);
        G2 = tf(1,[1 2 3]);
        d = exp(-2*s);
    case 3
        %Example 2
        G1 = tf(1,[1 1 5]);
        G2 = tf(1,[1 1]);
        d = exp(-2*s);
    case 4
        %Example 4
        Gzoh = 5/(s + 5);
        G1 = tf(1.663,[1 1.663]);
        G1 = Gzoh * G1;
        G2 = tf(1.53197e+05,[1 3.43511e+00]);
        d = exp(-0*s);
        
        alpha = 0.3;
        Am = 3;
        Pm = pi/4;
end
%Calcualates transfer function
G = G1 * G2 * d;

%Finds the crossover frequency
[~, ~, wc, ~] = margin(G);
%If there is no crossover frequency, the bandwidth is used as reference
if isinf(wc)
    %Finds the cutoff frequency
    wc = bandwidth(G);
end
%Calculates wp
wp = alpha * wc;

%Evaluation of G at wp
Gwp = evalfr(G,1i * wp);
%Computation of Kp
Kp = real(-1 / Am / Gwp);

% %FOR TESTING PURPOSES!!! ERASE LATER!!
% Kp = abs(Kp);

%VERIFICATION OF CONDITIONS AND CALCULATION OF wg

%Finds wg to satisfy necessary condition
PhaseGwp = phase(Gwp);
Condition1 = -pi + atan((1 - Am * cos(Pm))/(Am * sin(Pm))) - PhaseGwp;
Condition2 = PhaseGwp + pi/2;


% %FOR TESTING PURPOSES!! ERASE LATER!!!
% Condition1 = -1;
% Condition2 = -1;

%If Condition1 < 0 and Condition2 < 0, there is a valid solution for the gains
if Condition2 < 0 && Condition1 < 0
    
    %Defines the function to be used by secant method
    word = 'f = @wgRoot;';
    %defines input arguments
    fArgs = [];
    fArgs.G = G;
    fArgs.Pm = Pm;
    fArgs.Am = Am;
    fArgs.wp = wp;
    fArgs.x = wp/2;
    %Calculates wg value using secant method
    wg = SecantMethod1D(word,fArgs,wp/2,0.99*wp/2,0.001,20);
    
    %CALCULATION OF Xg AND Xp TERMS
    
    %Calculates terms Xg and Xp
    Gwg = evalfr(G,1i * wg);
    Xp = imag(-1 / Gwp / Am);
    Xg = imag(-exp(1i * Pm) / Gwg);
    %Calculates integral and derivative gains
    Ki = (Xp * wg - Xg * wp) * (wp/wg - wg/wp)^-1;
    Kd = (Xp/wg - Xg/wp) * (wp/wg - wg/wp)^-1;

% %TEST WITH FORCED POSITIVE VALUES
% Kd = abs(Kd);
% Ki = abs(Ki);
    
    %Controller definition for simulation
    Gc = Kp + Ki/s + Kd * s;
    H = feedback(Gc * G,1);
    step(H)
    
    disp(' ')
    word = ['wp = ',num2str(wp),'; wg = ',num2str(wg),';'];
    disp(word)
    word = ['Kp = ',num2str(Kp),';'];
    disp(word)
    word = ['Ki = ',num2str(Ki),';'];
    disp(word)
    word = ['Kd = ',num2str(Kd),';'];
    disp(word)
    
else
    
    disp(' ')
    disp('CONDITIONS NOT MET')
    
end

