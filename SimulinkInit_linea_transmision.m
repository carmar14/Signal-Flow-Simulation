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
% load('FitData')

% se carga la libreria de true time.
%run('truetime-2.0\init_truetime');


%  Parámetros Motor Diesel

K1d=1.15; K2d=1; K3d=1; Tao1d=0.5; Tao2d=0.125; Jd=0.3; Pd=0.1;

H_AM = tf([K1d*(K2d*K3d)],[Tao2d 1],'IODelay', Tao1d); % Dinámica Actuador - Motor
H_AM_d = c2d(H_AM,0.01,'tustin')

H_E = tf([Jd*Pd],[1 (Jd*Pd)]); % Dinámica Eje
H_E_d = c2d(H_E,0.01,'tustin')

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
load('mpc_linea_transmision.mat')
CSTR = ss1;%ss(Ab,Bb,Cb,Db);
CSTR.InputName = {'Pin_bio', 'Qin_bio','Pin_gen', 'Qin_gen'}; %u=[Pi_bio.Data Qi_bio.Data Pi_diesel.Data Qi_diesel.Data];
CSTR.OutputName = {'Pout_bio', 'Qout_bio','Pout_gen', 'Qout_gen'}; %y=[Po_bio.Data Qo_bio.Data Po_diesel.Data Qo_diesel.Data];
Ts = 1e-1;
p = 100;
m = 100;
mpcobj = mpc(CSTR, Ts, p, m);

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
% R1=0.1;
% R2=0.1;
% R3=1e-3;
% C1=22e-6;
% C2=22e-6;
% C3=610e-6;
% Cl=2000e-6;
% C=C1+C2+C3+Cl;
% L1=40e-3;
% L2=5e-3;
% L3=30e-3;
% L4=5.2;
% R4=10;
% R5=10;


%BIO
R1=0.1;
L1=40e-3;
C1=22e-6;
R4=0.005;%10;
L4=35e-6;%1e-3;

%REN
R2=0.2;
L2=30e-3;
C2=22e-6;
R5=0.0012;%40;  
L5=22e-6;%10e-3;

%DIESEL
R3=1e-3;
L3=5e-3;
C3=610e-6;
R6=0.001;
L6=10e-6;

%Carga
RL=10;
R=10;
L=5.2;
Cl=20000e-6;

%Tabla 1
cvsi=200/sqrt(2);
carga=cvsi*20;
q=0:0.001:carga*1.2;
soc=100-100*q/carga;


% se cargan las matrices dinamicas del MPC DMC.
load('DMC_matrices2');

% se carga la libreria de true time.
%run('truetime-2.0\init_truetime');

% load('modeloElectrico');
load('modeloDiesel_dotros')

%Parámetros del sistema BIOMASA
factor_t=24*3600;
b=4.91;
Ks=21.5;
Ksc=3;
Kd=0.02;
Kdc=0.02;
K1=9.66;
K2=6.97;
K3=31.8;
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
C=1;
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


%%%Funciones de transferencia
%  h=tf([RL*L RL*R],[Cl*RL*L  (R*RL*Cl+L) RL+R]);
% h2=tf(1,conv([L1 R1],[C1*L4 R4*C1 1])+[0 0 L4 R4]);
% h3=tf(1,conv([L2 R2],[C2*L5 R5*C2 1])+[0 0 L5 R5]);
% h4=tf(1,conv([L3 R3],[C3*L6 R6*C3 1])+[0 0 L6 R6]);
