
%-------------------------------------------------
%ADDITION OF NECESSARY PATHS CONTAINING USED CODES
%-------------------------------------------------

word = [pwd filesep, 'TJ1000StaticSIATT'];
addpath(word);
word = [pwd filesep, 'TestBench'];
addpath(word);
word = [pwd filesep, 'SIATTProfile'];
addpath(word);
word = [pwd filesep, 'Sebastien'];
addpath(word);
word = [pwd filesep, 'MissionGenCode'];
addpath(word);

% SebastienMission
SIATTProfile

%-------------------
%DELETES ADDED PATHS
%-------------------

word = [pwd filesep, 'TJ1000StaticSIATT'];
rmpath(word);
word = [pwd filesep, 'TestBench'];
rmpath(word);
word = [pwd filesep, 'SIATTProfile'];
rmpath(word);
word = [pwd filesep, 'Sebastien'];
rmpath(word);
word = [pwd filesep, 'MissionGenCode'];
rmpath(word);
% word = [pwd filesep, 'SubIdle',  filesep, 'Combustion'];
% rmpath(word);
% word = [pwd filesep, 'SubIdle'];
% rmpath(word);