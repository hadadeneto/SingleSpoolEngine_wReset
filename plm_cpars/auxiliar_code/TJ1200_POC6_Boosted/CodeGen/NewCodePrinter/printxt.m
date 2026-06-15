function printxt(fid,firsti,lasti,firstj,lastj,firstk,lastk,var,varword)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%i - number of pages of the 3D matrix
%j - number of rows of the 3D matrix
%k - number of columns of the 3D matrix

for i = firsti:lasti
    if i==firsti && lasti > 1.5
        word = [varword ' = {\n'];
        fprintf(fid,word);
    elseif lasti < 1.5
        word = [varword ' = {'];
        fprintf(fid,word); 
    end
    
    for j=firstj:lastj
        for k=firstk:lastk
            
            %Prints EPRh1 on document
            if j==firstj && k==firstk && lastj > 1.5
                %word = '{\n{';
                word = '\n';
                fprintf(fid,word);
                
%             elseif k==firstk
%                 word = '{';
%                 fprintf(fid,word);
            end
            
            fprintf(fid,'%1.5e',var(j,k,i));
            
            if k ~= lastk
                fprintf(fid,',');
            end
            if i == lasti
                stophere = 1;
            end
            if k==lastk && j==lastj && lastj > 1.5
                %fprintf(fid,'}\n},\n');
                word = ',\n\n';
                %fprintf(fid,',\n\n');
                if i == lasti
                    word = '\n\n';
                end
                fprintf(fid,word);
            elseif k==lastk && lastj > 1.5
                %fprintf(fid,'},');
                fprintf(fid,',');
                fprintf(fid,'\n');
            elseif k==lastk && lastj < 1.5
                fprintf(fid,'};');
                fprintf(fid,'\n');                
            else
                fprintf(fid,' ');
            end
            
            
        end
    end
    
%     if i==lasti && lasti > 1.5
%         word = '};\n';
%         fprintf(fid,word);
%     end
    
    if i==lasti && lastj > 1.5
        word = '};\n';
        fprintf(fid,word);
    end
    
end

end


% %Prints EPRh1 on document
% if j==1 && k==1
%     lnum = (initpos+j-1)*numchars;
%     fseek(fid,lnum,-1);
%     word = [varword ' = ['];
%     word = [word repmat(' ',1,(numchars-1-length(word))) '\n'];
%     fprintf(fid,word);
% else
%     fseek(fid,pos,-1);
% end
% fprintf(fid,'%1.5e',var(j,k,i));
% fprintf(fid,' ');
% pos = ftell(fid);
%
% if k==lastk && j==lastj
%     fseek(fid,-1,0);
%     fprintf(fid,'];');
% elseif k==lastk
%     fseek(fid,-1,0);
%     fprintf(fid,';');
%     delchar = numchars-(initpos+j+1)*numchars;
%     fprintf(fid,repmat(' ',1,(delchar)));
%     fprintf(fid,'\n');
%     pos = ftell(fid);
% end
%
% end

