close all
clc

%Parámetros del sistema BIOMASA
factor_t=24*3600;
b=4.91;
Ks=21.5;
Ksc=3;
Kd=0.02;
Kdc=0.02;
K1bio=9.66; %cambio
K2bio=6.97; %cambio
K3bio=31.8; %cambio
K4=15.1; 
Sbin=13.8;%13.8;  0.65
Svin=2.91;%2.91;    85
V=20;
wref=70000;%70000;
K=25; 
K11=0.8; 
K22=0.2; 
T1=0.4;
T2=1;
T3=15;
T4=2.5;
T5=3.3;
Tt=450;
Kv=1;
Tv=0.05;
Cbio=1; %cambio
K33=0.23; 
Kf=1; 
Tr=950;%950; 100
Tf=0.04;
Tcr=0.01;
Ttd=0.04;
Tcd=0.2;
Kh=1.2;
Z=3;

X_acid=1.2;
S_b=4.51;
S_v=0.63;
X_meth=0.35;
