
% CREATES FOLDERS AND SUBFOLDERS FOR SAVING MISSION FILES

%Name of each separate folder
MainFolder = 'MissionsISAdT';
FilesFolder = 'Missions';
RPMMatchFolder = 'RPMMatch';
FFMatchFolder = 'FFMatch';
XLSXFolder = 'XLSX';
CSVFolder = 'CSV';
FigureFolder = 'FigsPNG';

% Names the folders
RPMMatchXLSXword = [pwd filesep MainFolder filesep FilesFolder filesep RPMMatchFolder...
                    filesep XLSXFolder];
RPMMatchCSVword = [pwd filesep MainFolder filesep FilesFolder filesep RPMMatchFolder...
                    filesep CSVFolder];
                
FFMatchXLSXword = [pwd filesep MainFolder filesep FilesFolder filesep FFMatchFolder...
                    filesep XLSXFolder];

FFMatchCSVword = [pwd filesep MainFolder filesep FilesFolder filesep FFMatchFolder...
                    filesep CSVFolder];                
                
FigureFolderword = [pwd filesep MainFolder filesep FigureFolder];

% Creates each file of the structure if they do not exist
if(exist(RPMMatchXLSXword, 'dir') == 0)
    mkdir(RPMMatchXLSXword)
end
if(exist(RPMMatchCSVword, 'dir') == 0)
mkdir(RPMMatchCSVword)
end
if(exist(FFMatchXLSXword, 'dir') == 0)
mkdir(FFMatchXLSXword)
end
if(exist(FFMatchCSVword, 'dir') == 0)
mkdir(FFMatchCSVword)
end
if(exist(FigureFolderword, 'dir') == 0)
mkdir(FigureFolderword)
end

