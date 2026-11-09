%Adds necessary paths
word = [pwd filesep, 'NewCodeGen'];
addpath(word);
word = [pwd filesep, 'CodePrepare'];
addpath(word);

FADECLitePacking

%Removes added path
word = [pwd filesep, 'NewCodeGen'];
rmpath(word);
word = [pwd filesep, 'CodePrepare'];
rmpath(word);