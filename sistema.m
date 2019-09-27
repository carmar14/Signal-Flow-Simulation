function  dxdt=sistema(x,u)

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

%%Parametros del PR(z)
num=[0.0201 -0.039932 0.01986];
den=[1 -1.9966 0.998];
Tm=0.0001;
prd=tf(num,den,Tm);
prc=d2c(prd);

num=cell2mat(prc.Numerator);
den=cell2mat(prc.Denominator);

a=num(1);
b=num(2);
c=num(3);
d=den(2);
e=den(3);
%ref potencias activa y reactiva del bio
P1=u(1); 
Q1=u(2);
%ref potencias activa y reactiva del gen
P2=u(3);
Q2=u(4);

%Tensíon dc de cada generador
vdc1=u(5);

y1=a*(P1*x(8)+Q1*x(16))/(x(8)^2+x(16)^2)+(c-e*a)*x(12)+(b-a*d)*x(13);
y2=a*(P1*x(8)+Q1*x(16))/(x(8)^2+x(16)^2)+(c-e*a)*x(12)+(b-a*d)*x(13);

x1p=-R1*x(1)/L1-x(8)/L1+

