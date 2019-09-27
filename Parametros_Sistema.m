clear
clc
close all

%BIO
R1=0.1;
L1=40e-3;
C1=22e-6;
R4=10;
L4=1e-3;

%REN
R2=0.2;
L2=30e-3;
C2=22e-6;
R5=4;  
L5=10e-3;

%DIESEL
R3=1e-3;
L3=5e-3;
C3=610e-6;
R6=25;
L6=40e-3;

%Carga
RL=10;
R=10;
L=5.2;
Cl=20000e-6;

% Matrices
A=[-R1/L1 zeros(1,6) -1/L1 zeros(1,3);
    0 -R2/L2 zeros(1,6) -1/L2 0 0;
    zeros(1,2) -R3/L3 zeros(1,6) -1/L3 0;
    zeros(1,3) -R4/L4 zeros(1,3) 1/L4 0 0 -1/L4;
    zeros(1,4) -R5/L5 zeros(1,3) 1/L5 0 -1/L5;
    zeros(1,5) -R6/L6 zeros(1,3) 1/L6 -1/L6;
    zeros(1,6) -R/L zeros(1,3) 1/L;
    1/C1 zeros(1,2) -1/C1 zeros(1,7);
    0 1/C2 0 0 -1/C2 zeros(1,6);
    0 0 1/C3 0 0 -1/C3 zeros(1,5);
    zeros(1,3) 1/Cl 1/Cl 1/Cl -1/Cl zeros(1,3) -1/(Cl*RL)]; 
B=[1/L1 0 0;
   0 1/L2 0;
   0 0 1/L3;
   zeros(8,3)];
C11=[zeros(1,3) 1 zeros(1,7)]; %Salida del BIO
C22=[zeros(1,4) 1 zeros(1,6)]; %Salida del gene
C33=[zeros(1,5) 1 zeros(1,5)]; %Salida del Diesel
C44=[zeros(1,10) 1];
C=[C11; C22; C33;C44];
D=zeros(4,3);
D1=zeros(1,3);
D3=zeros(1,3);
D2=zeros(1,3);

sis=ss(A,B,C11,D1);
sis2=ss(A,B,C22,D2);
ts=0.0001;
tm=ts/10;
sisd=c2d(sis,tm);
sisd2=c2d(sis2,tm);

Ts = 1e-1;
p = 100;
m = 100;
mpcobj = mpc(sisd, Ts, p, m);
mpcobj1 = mpc(sisd2, Ts, p, m);

% step(sis)
%Controlador PR en z

num=[0.0201 -0.039932 0.01986];
den=[1 -1.9966 0.998];
Tm=0.0001;
prd=tf(num,den,Tm);
% step(prd)

prc=d2c(prd);

% [a,b,c,d]=tf2ss(cell2mat(prc.Numerator),cell2mat(prc.Denominator));
% sis=ss(a,b,c,d);
% hold on
% step(prc)
% step(sis)
% 
% figure
% pzmap(prd)
% 
% figure
% pzmap(prc)


