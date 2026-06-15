function y = wgRoot(fArgs)
%y = WgRoot - Calculates the function:
%cos(Pm - phaseGwg) / absGwg - cos(phaseGwp) / absGwp / Am;
%which is going to be used by tangent method for finding wg corresponding
%to y = 0

%Reads input main argument
wg = fArgs.x;
%Reads input remaining arguments
Pm = fArgs.Pm;
Am = fArgs.Am;
wp = fArgs.wp;
%Calculates complex numbers equivalent to wg and wp
Gwg = evalfr(fArgs.G,1i * wg);
Gwp = evalfr(fArgs.G,1i * wp);
%Calculates phases na absolute values
absGwg = abs(Gwg);
absGwp = abs(Gwp);
phaseGwg = phase(Gwg);
phaseGwp = phase(Gwp);
%Calculates output y
y = cos(Pm - phaseGwg) / absGwg - cos(phaseGwp) / absGwp / Am;

end

