function WriteLinesSafe(Source,fid)
%WRITELINESSAFE Writes every character of a line
%   Writes all characters of every line in Source, including \n and %, not
%   using such symbols for undesirable formatting

% Loop for printing source lines to file
for i = 1:length(Source)    
    % Uses '%s\n' for formatting. 
    % '%s' prints the content of Source(i) literally (including \n and %).
    % The '\n' at the end ensures it adds a new line in the file after printing.
    fprintf(fid, '%s\n', char(Source(i)));
end

end

