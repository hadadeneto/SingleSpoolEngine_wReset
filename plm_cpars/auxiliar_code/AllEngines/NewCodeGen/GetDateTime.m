function DateTimeCell = GetDateTime
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

%Reads current date and time
DateTime = clock;
%Initiates date and time char with empty value
DateTimeChar = [];
for i = 1:length(DateTime)
    %Includes underscore for values separation
    DateTimeChar = [DateTimeChar '_'];
    %Includes word specifying date
    if i == 1
        DateTimeChar = [DateTimeChar 'Date_'];
    end
    %Indluces word specifying time
    if i == 4
        DateTimeChar = [DateTimeChar 'Time_'];
    end
    %Updates DateTimeChar wiht current value
    DateTimeChar = [DateTimeChar num2str(DateTime(i))];
end

DateTimeCell = {DateTimeChar};

end

