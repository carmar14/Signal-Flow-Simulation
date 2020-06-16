function [ ] = DisplayMatrix( Array )
% Display a matrix into the command window such that you can copy and past
% it into simulink or other
% Input: - Array: the matrix to be displayed
% Output:  No

Name=inputname(1);

if(isnumeric(Array)==1) 
    Array=vpa(Array);
end

[nb_lin,nb_col]=size(Array);
fprintf('\n%s=[\t',Name)
for i=1:nb_lin
    for j=1:nb_col
        A=char(Array(i,j));
        if j~=nb_col
            fprintf('%s, ',A)
        else
                if i~=nb_lin
                    fprintf('%s; ',A) 
                else
                    fprintf('%s',A) 
                end
        end
    end
    if i~=nb_lin
        fprintf('\n\t')
    else
        fprintf('];\n\n')
    end
end

end


