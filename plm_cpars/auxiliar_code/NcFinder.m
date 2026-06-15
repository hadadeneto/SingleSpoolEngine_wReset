function [Nc,FnPcFound] = NcFinder(Fn, FnSearch, FnPc, NcSearch)
%This function searches the correct value of Nc given the wanted percentual
%of Fn

%Input thrust value considered 100%
%Fn = 100;
%Input Thrust Vector
%FnIdeal = Fn*(1:-0.05:0.25);

%The vector FnSearch is converted from percentual values to thrust values
FnIdeal = Fn*FnPc;

%Total number of elements to be identifyied with Nc
NumEl = length(FnIdeal);
Nc = [];
FnPcFound = [];
%NumMeas = length(FnSearch);

%Searching Loop
for i=1:NumEl
    
%     %Initiates IL and IH
%     IL = 0;
%     IH = 0;
    
    %     for j=1:NumMeas
    %
    %         %Verifies if
    %         if FnIdeal(i) > FnSearch(j);
    %             IL = j;
    %             IH = j-1;
    %             break;
    %         end
    %
    %         %Calculates the values of Nc
    %         if IL > 0 && IH > 0
    %             %Calculates the corresponding value of Nc
    %             coef = (FnIdeal(i)-FnSearch(IL))/(FnSearch(IH)-FnSearch(IL));
    %             NcVal = NcSearch(IL) + coef*(NcSearch(IH)-NcSearch(IL));
    %             Nc = [Nc NcVal];
    %             FnPcFound = [FnPcFound FnPC(i)];
    %         end
    %
    %     end
    CurrentFn = FnIdeal(i);
    %Finds the index containing the first value of FnSearch which is
    %smaller than FnIdeal(i)
    [IL,~] = find(CurrentFn >= FnSearch,1,'first');
    
    if ~isempty(IL)
        
        IH = IL - 1;
        
        if IL == 1
            Nc = [Nc NcSearch(IL)];
            FnPcFound = [FnPcFound FnPc(IL)];
        else
        
        coef = (FnIdeal(i)-FnSearch(IL))/(FnSearch(IH)-FnSearch(IL));
        NcVal = NcSearch(IL) + coef*(NcSearch(IH)-NcSearch(IL));
        Nc = [Nc NcVal];
        FnPcFound = [FnPcFound FnPc(i)];
        end
        
    end
    
end

%Starts a word with vectors names and start
WORDNc = 'Nc = [';
WORDFn = 'FnPc = [';

%Transforme vectors into string to be printed in workspace
for i = 1:length(Nc)
    if i==1
        WORDNc = [WORDNc num2str(Nc(i))];
        WORDFn = [WORDFn num2str(FnPcFound(i))];
    else
        WORDNc = [WORDNc ' ' num2str(Nc(i))];
        WORDFn = [WORDFn ' ' num2str(FnPcFound(i))];
    end
end

%Finishes the strings to be printed
WORDNc = [WORDNc ']'];
WORDFn = [WORDFn ']'];

%Ptints strings on screen
disp(WORDNc)
disp(WORDFn)

end
