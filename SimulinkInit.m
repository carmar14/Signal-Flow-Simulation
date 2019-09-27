% este script es ejecutado al momento de ejecutar el modelo de simulink de
% la microgrid de esta carpeta.
% En la seccion de configuracion de simulink, En la pestaña de callBacks se
% configuran los scripts que se desean ejectar al incio, durante o al
% final de la simulacion.
clear
close all
clc
% se cargan las matrices dinamicas del MPC DMC.
load('DMC_matrices');
load('FitData')

% se carga la libreria de true time.
%run('truetime-2.0\init_truetime');


%  Parámetros Motor Diesel

K1=1.15; K2=1; K3=1; Tao1=0.5; Tao2=0.125; J=0.3; P=0.1;

H_AM = tf([K1*(K2*K3)],[Tao2 1],'IODelay', Tao1); % Dinámica Actuador - Motor
H_AM_d = c2d(H_AM,0.01,'tustin')

H_E = tf([J*P],[1 (J*P)]); % Dinámica Eje
H_E_d = c2d(H_E,0.01,'tustin')

%MPC BIO
% 
% C1=22e-6;
% C2=C1;
% C3=610e-6;
% C6=2000e-6;
% C=C1+C2+C3+C6;
% R1=0.1;
% R2=R1;
% R3=1e-3;
% R4=10;
% R5=10;
% L1=40e-3;
% L2=30e-3;
% L3=5e-3;
% L4=5.2;
% Ab= [-R1/L1 0 0 0 -1/L1
%      0 -R2/L2 0 0 -1/L2
%      0 0 -R3/L3 0 -1/L3
%      0 0 0 -R5/L4 1/L4
%      1/C 1/C 1/C -1/C -1/R4];
% Bb = [1/L1 0 0 
%      0 1/L2 0
%      0 0 1/L3
%      0 0 0
%      0 0 0];
% Cb = [1 0 0 0 0
%       0 0 0 0 1];
% 
% Db = zeros(2,3);

load('FitData.mat');
load('AyC.mat');
%tf1.Denominator{2, 1}(2)
% A=[0 1 zeros(1,10)
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
B=[0 0
   0 0
   1 0
   0 0
   0 0
   0 1
   0 0
   0 0
   1 0
   0 0
   0 0
   0 1];
% C=[tf1.Numerator{1,1}(3) tf1.Numerator{1,1}(2) tf1.Numerator{1,1}(1) tf1.Numerator{1,2}(3) tf1.Numerator{1,2}(2) tf1.Numerator{1,2}(1) zeros(1,6)
%    zeros(1,6) tf1.Numerator{2,1}(3) tf1.Numerator{2,1}(2) tf1.Numerator{2,1}(1) tf1.Numerator{2,2}(3) tf1.Numerator{2,2}(2) tf1.Numerator{2,2}(1)];
D=zeros(2,2)
sis=ss(A,B,C,D);

CSTR = sis;%ss(Ab,Bb,Cb,Db);
CSTR.InputName = {'Pin', 'Qin'};
CSTR.OutputName = {'Po','Qo'};
% CSTR.StateName = {'Ibio', 'Idie', 'Ipv', 'I5', 'Vout'};
CSTR

%  Design MPC Controller

%   MPCOBJ = mpc(PLANT,TS,P,M) specifies the control horizon, M. M is
%   either an integer (<= P) or a vector of blocking factors such that
%   sum(M) <= P.
%   MODELS.Plant = plant model (LTI or IDMODEL)
%         .Disturbance = model describing the input disturbances.
%                           This model is assumed to be driven by unit
%                          variance white noise.
%            .Noise = model describing the plant output measurement noise.
%                           This model is assumed to be driven by unit
%                          variance white noise.
%            .Nominal = structure specifying the plant nominal conditions
%                             (e.g., at which the plant was linearized).

% Create the controller object with sampling period, prediction and control horizons:
plant=CSTR;
Ts = 1e-1;
p = 100;
m = 100;
% mpcobj = mpc(plant, Ts, p, m);

% Specify actuator saturation limits as MV constraints.
% mpcobj.MV = struct('Min',{-200;-200},'Max',{200;200},'RateMin',{-100;-100});
% Simulate Using Simulink®

% To run this example, Simulink® is required.
% if ~mpcchecktoolboxinstalled('simulink')
%     disp('Simulink(R) is required to run this example.')
%     return
% end

% n11=tf1.Numerator{1,1};
% n12=tf1.Numerator{1,2};
% n21=tf1.Numerator{2,1};
% n22=tf1.Numerator{2,2};
% d11=tf1.Denominator{1,1};
% d12=tf1.Denominator{1,2};
% d21=tf1.Denominator{2,1};
% d22=tf1.Denominator{2,2};
% 
% N=[n11 n12; n21 n22];
% D=[d11 d12; d21 d22];
% [A1 B1 C1 D1]=tf2ss([n11; n12],[d11])
% [A2 B2 C2 D2]=tf2ss([n21; n22],[d11])
% [A3 B3 C3 D3]=tf2ss([n11; n12],[d12])
% [A4 B4 C4 D4]=tf2ss([n21; n22],[d12])
% [A5 B5 C5 D5]=tf2ss([n11; n12],[d21])
% [A6 B6 C6 D6]=tf2ss([n21; n22],[d21])
% [A7 B7 C7 D7]=tf2ss([n11; n12],[d22])
% [A8 B8 C8 D8]=tf2ss([n21; n22],[d22])


%Parametros 1:Biomasa 2:Diesel 3:VSI
R1=0.1;
R2=0.1;
R3=1e-3;
C1=22e-6;
C2=22e-6;
C3=610e-6;
Cl=2000e-6;
C=C1+C2+C3+Cl;
L1=40e-3;
L2=5e-3;
L3=30e-3;
L4=5.2;
R4=10;
R5=10;


%Tabla 1
cvsi=200/sqrt(2);
carga=cvsi*20;
q=0:0.001:carga*1.2;
soc=100-100*q/carga;


% se cargan las matrices dinamicas del MPC DMC.
load('DMC_matrices2');

% se carga la libreria de true time.
%run('truetime-2.0\init_truetime');

load('modeloElectrico');
load('modeloDiesel_dotros')


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

clc


