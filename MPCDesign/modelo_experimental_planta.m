% A1=[0 1 zeros(1,10)
%    0 0 1 zeros(1,9)
%    -tf1.Denominator{1,1}(4) -tf1.Denominator{1,1}(3) -tf1.Denominator{1,1}(2) zeros(1,9)
%    zeros(1,4) 1 zeros(1,7)
%    zeros(1,5) 1 zeros(1,6)
%    zeros(1,3) -tf1.Denominator{1,2}(4) -tf1.Denominator{1,2}(3) -tf1.Denominator{1,2}(2) zeros(1,6)
%    zeros(1,7) 1 zeros(1,4)
%    zeros(1,8) 1 zeros(1,3)
%    zeros(1,6) -tf1.Denominator{2,1}(4) -tf1.Denominator{2,1}(3) -tf1.Denominator{2,1}(2) zeros(1,3)
%    zeros(1,10) 1 0
%    zeros(1,11) 1
%    zeros(1,9) -tf1.Denominator{2,2}(4) -tf1.Denominator{2,2}(3) -tf1.Denominator{2,2}(2)
%    ];
% 
% C1=[tf1.Numerator{1,1}(3) tf1.Numerator{1,1}(2) tf1.Numerator{1,1}(1) tf1.Numerator{1,2}(3) tf1.Numerator{1,2}(2) tf1.Numerator{1,2}(1) zeros(1,6)
%    zeros(1,6) tf1.Numerator{2,1}(3) tf1.Numerator{2,1}(2) tf1.Numerator{2,1}(1) tf1.Numerator{2,2}(3) tf1.Numerator{2,2}(2) tf1.Numerator{2,2}(1)];
% 
% B=[0 0
%    0 0
%    1 0
%    0 0
%    0 0
%    0 1
%    0 0
%    0 0
%    1 0
%    0 0
%    0 0
%    0 1];


clear
clc
close all

sim('pqFitting2.slx');

y=[Po_bio.Data Qo_bio.Data Po_diesel.Data Qo_diesel.Data];
u=[Pi_bio.Data Qi_bio.Data Pi_diesel.Data Qi_diesel.Data];
tm=0.0001;
datos_ident=iddata(y,u,tm);

plot(datos_ident)

