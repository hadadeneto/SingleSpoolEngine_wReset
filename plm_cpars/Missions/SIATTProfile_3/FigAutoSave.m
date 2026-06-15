function FigAutoSave(Namefig,fig)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

fig.WindowState = 'fullscreen';
saveas(fig,Namefig);
close(fig);

end

