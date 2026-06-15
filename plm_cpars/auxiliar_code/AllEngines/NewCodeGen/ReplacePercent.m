function StringOut = ReplacePercent(string)
%ReplacePercent replaces % with %% for correct printing of percent symbol

%Initiates indexes and auxiliar string with input string
Indexes = find(string == '%');
Aux = string;

%Loop for replacing % with %%
for i = 1:length(Indexes)
    %Aux1 receives string from first element until current detected %
    Aux1 = Aux(1:Indexes(i));
    %Aux2 receives string from current detected % until last element
    Aux2 = Aux(Indexes(i):end);
    %When Aux1 and Aux2 are concatenated, the current detected % turns into
    %a %%
    Aux = [Aux1 Aux2];
    %Indexes must be increased since a new % has been inserted into Aux
    Indexes = Indexes + 1;
end

%Computes output
StringOut = Aux;

end

