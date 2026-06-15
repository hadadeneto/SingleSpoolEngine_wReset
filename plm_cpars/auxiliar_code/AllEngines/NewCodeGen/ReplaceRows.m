function SinkOut = ReplaceRows(Source,Sink,Interval)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%Initiates variables and output vector
SinkOut = Sink;
Ind = Interval(1):Interval(end);

%Loop for replacing SinkOut rows with Source rows at the defined interval
for i = 1:length(Ind)
    %Replaces rows
    SinkOut(Ind(i)) = Source(i);
end

end

