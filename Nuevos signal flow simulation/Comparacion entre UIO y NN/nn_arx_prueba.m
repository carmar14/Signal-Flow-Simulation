clc
clear
close all

%Datos de entrada y salida
load('datos_ataque_individual.mat');
load('tm.mat');

%Promedio de los UIOs
yo1=y1;
yo2=y2;
yo3=y3;
yo4=y4;

%Modelos de redes neuronales para cada salida [y1 y2 y3 y4]'
i=2; %i=1 NN con varias salidas i~=1 NN con salida única
if i==1
    load('nnwy1.mat');
    net1=net;
    load('nnwy2.mat');
    net2=net;
    load('nnwy3.mat');
    net3=net;
    load('nnwy4.mat');
    net4=net;
else
    
    load('nny1.mat');
    net1=net;
    load('nny2.mat');
    net2=net;
    load('nny3.mat');
    net3=net;
    load('nny4.mat');
    net4=net;
end

tm=tm*2;
y=y_ma;
x = u;%Input;
t = y;%Output;

if i==1
    %%----------------ARX: nn_arxout1-----------------
    phi1=[t(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %salidas con delay -1...-11
        t(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y1=[t(12:end,1) t(12:end,2) t(12:end,3) t(12:end,4)]';
    
    %%----------------ARX: nn_arxout2-----------------
    phi2=[t(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %salidas con delay -1...-11
        t(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y2=[t(12:end,1) t(12:end,2) t(12:end,3) t(12:end,4)]';
    
    %%----------------ARX: nn_arxout3-----------------
    phi3=[t(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %salidas con delay -1...-11
        t(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y3=[t(12:end,1) t(12:end,2) t(12:end,3) t(12:end,4)]';
    
    %%----------------ARX: nn_arxout4-----------------
    phi4=[t(11:end-1,4) t(10:end-2,4) t(9:end-3,4) t(8:end-4,4) t(7:end-5,4) ...                     %salidas con delay -1...-11
        t(6:end-6,4)  t(5:end-7,4)  t(4:end-8,4) t(3:end-9,4) t(2:end-10,4) t(1:end-11,4) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y4=[t(12:end,1) t(12:end,2) t(12:end,3) t(12:end,4)]';
    
    
    %vector de tiempos
    t=0:tm:length(y)*tm-tm;
    
    %Salida de la red
    yn1=net1(phi1);
    yn1=yn1';
    t1=0:tm:length(yn1)*tm-tm;
    
    yn2=net2(phi2);
    yn2=yn2';
    t2=0:tm:length(yn2)*tm-tm;
    
    yn3=net3(phi3);
    yn3=yn3';
    t3=0:tm:length(yn3)*tm-tm;
    
    yn4=net4(phi4);
    yn4=yn4';
    t4=0:tm:length(yn4)*tm-tm;
    
    
    % [yupper,ylower] = envelope(y1,1500);
%     [yupper,ylower] = envelope(1.5*y1,800,'rms');
%     figure
%     plot(
    %
    
    dyn1=abs(diff(yn1-y1'));
    dyn2=abs(diff(yn2-y2'));
    dyn3=abs(diff(yn3-y3'));
    dyn4=abs(diff(yn4-y4'));
    
    dy1=abs(diff(yo1));
    dy2=abs(diff(yo2));
    dy3=abs(diff(yo3));
    dy4=abs(diff(yo4));
    % dy1=dy1
    
    plot(t1(1:end-1),dyn1,'-k')
    hold on
    plot(t(1:end-1),dy1,'--r')
    ylim([0 2])
    legend('Der. Residual de red','residual del observador')
    figure
    plot(t2(1:end-1),dyn2,'-k')
    hold on
    plot(t(1:end-1),dy2,'--r')
    legend('Der. Residual de red','residual del observador')
    ylim([0 2])
    
    %Datos de entrada y salida
    load('datos_ataque_multiple.mat');
    
    
    yo1=y1;
    yo2=y2;
    yo3=y3;
    yo4=y4;
    
    y=y_ma;
    x = u;%Input;
    t = y;%Output;
    
    %%----------------ARX: nn_arxout1-----------------
    phi1=[t(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %salidas con delay -1...-11
        t(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y1=[t(12:end,1) t(12:end,2) t(12:end,3) t(12:end,4)]';
    
    %%----------------ARX: nn_arxout2-----------------
    phi2=[t(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %salidas con delay -1...-11
        t(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y2=[t(12:end,1) t(12:end,2) t(12:end,3) t(12:end,4)]';
    
    %%----------------ARX: nn_arxout3-----------------
    phi3=[t(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %salidas con delay -1...-11
        t(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y3=[t(12:end,1) t(12:end,2) t(12:end,3) t(12:end,4)]';
    
    %%----------------ARX: nn_arxout4-----------------
    phi4=[t(11:end-1,4) t(10:end-2,4) t(9:end-3,4) t(8:end-4,4) t(7:end-5,4) ...                     %salidas con delay -1...-11
        t(6:end-6,4)  t(5:end-7,4)  t(4:end-8,4) t(3:end-9,4) t(2:end-10,4) t(1:end-11,4) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y4=[t(12:end,1) t(12:end,2) t(12:end,3) t(12:end,4)]';
    
    %vector de tiempos
    t=0:tm:length(y)*tm-tm;
    
    %Salida de la red
    yn1=net1(phi1);
    yn1=yn1';
    t1=0:tm:length(yn1)*tm-tm;
    
    yn2=net2(phi2);
    yn2=yn2';
    t2=0:tm:length(yn2)*tm-tm;
    
    yn3=net3(phi3);
    yn3=yn3';
    t3=0:tm:length(yn3)*tm-tm;
    
    yn4=net4(phi4);
    yn4=yn4';
    t4=0:tm:length(yn4)*tm-tm;
    
    
    % [yupper,ylower] = envelope(y1,1500);
    % [yupper,ylower] = envelope(1.5*y1,800,'rms');
    %
    
    dynn1=abs(diff(yn1-y1'));
    dynn2=abs(diff(yn2-y2'));
    dynn3=abs(diff(yn3-y3'));
    dynn4=abs(diff(yn4-y4'));
    
    dy1=abs(diff(yo1));
    dy2=abs(diff(yo2));
    dy3=abs(diff(yo3));
    dy4=abs(diff(yo4));
    
    % dy1=dy1
    figure
    plot(t1(1:end-1),dynn1,'-k')
    hold on
    plot(t(1:end-1),dy1,'--r')
    legend('Der. Residual de red','residual del observador')
    ylim([0 2])
    figure
    plot(t2(1:end-1),dynn2,'-k')
    hold on
    plot(t(1:end-1),dy2,'--r')
    ylim([0 2])
    legend('Der. Residual de red','residual del observador')
else
    
    %%----------------ARX: nn_arxout1-----------------
    phi1=[t(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %salidas con delay -1...-11
        t(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y1=t(12:end,1)';
    
    %%----------------ARX: nn_arxout2-----------------
    phi2=[t(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %salidas con delay -1...-11
        t(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y2=t(12:end,2)';
    
    %%----------------ARX: nn_arxout3-----------------
    phi3=[t(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %salidas con delay -1...-11
        t(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y3=t(12:end,3)';
    
    %%----------------ARX: nn_arxout4-----------------
    phi4=[t(11:end-1,4) t(10:end-2,4) t(9:end-3,4) t(8:end-4,4) t(7:end-5,4) ...                     %salidas con delay -1...-11
        t(6:end-6,4)  t(5:end-7,4)  t(4:end-8,4) t(3:end-9,4) t(2:end-10,4) t(1:end-11,4) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y4=t(12:end,4)';
    
    
    %vector de tiempos
    t=0:tm:length(y)*tm-tm;
    
    %Salida de la red
    yn1=net1(phi1);
    yn1=yn1';
    t1=0:tm:length(yn1)*tm-tm;
    
    yn2=net2(phi2);
    yn2=yn2';
    t2=0:tm:length(yn2)*tm-tm;
    
    yn3=net3(phi3);
    yn3=yn3';
    t3=0:tm:length(yn3)*tm-tm;
    
    yn4=net4(phi4);
    yn4=yn4';
    t4=0:tm:length(yn4)*tm-tm;
    
    
    % [yupper,ylower] = envelope(y1,1500);
    
    %
    
    dyn1=abs(diff(yn1-y1'));
    dyn2=abs(diff(yn2-y2'));
    dyn3=abs(diff(yn3-y3'));
    dyn4=abs(diff(yn4-y4'));
    
    dy1=abs(diff(yo1));
    dy2=abs(diff(yo2));
    dy3=abs(diff(yo3));
    dy4=abs(diff(yo4));
    
    [yupper,ylower] = envelope(dy1,300,'rms');%(1.5*dy1,800,'rms');
    figure
    plot(t1,dy1(1:end-10,1),t1,ylower(1:end-10,1),t1,yupper(1:end-10,1))
    [yupper,ylower] = envelope(dy1,800,'rms');
    figure
    plot(t1,dy1(1:end-10,1),t1,ylower(1:end-10,1),t1,yupper(1:end-10,1))
%     figure
    % dy1=dy1
    
%     plot(t1(1:end-1),dyn1,'-k')
%     hold on
%     plot(t(1:end-1),dy1,'--r')
%     ylim([0 2])
%     legend('Der. Residual de red','residual del observador')
%     figure
%     plot(t2(1:end-1),dyn2,'-k')
%     hold on
%     plot(t(1:end-1),dy2,'--r')
%     legend('Der. Residual de red','residual del observador')
%     ylim([0 2])
    
    % figure
    % plot(t1,yn1-y1','-k')
    % hold on
    % plot(t,yo1,'--r')
    % % ylim([0 2])
    % legend('Residual de red','residual del observador')
    % figure
    % plot(t2,yn2-y2','-k')
    % hold on
    % plot(t,yo2,'--r')
    % legend('Residual de red','residual del observador')
    % ylim([0 2])
    
    %Datos de entrada y salida
    load('datos_ataque_multiple.mat');
    
    %Promedio de los UIOs
    yo1=y1;
    yo2=y2;
    yo3=y3;
    yo4=y4;
    
    y=y_ma;
    x = u;%Input;
    t = y;%Output;
    
    %%----------------ARX: nn_arxout1-----------------
    phi1=[t(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %salidas con delay -1...-11
        t(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y1=t(12:end,1)';
    
    %%----------------ARX: nn_arxout2-----------------
    phi2=[t(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %salidas con delay -1...-11
        t(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y2=t(12:end,2)';
    
    %%----------------ARX: nn_arxout3-----------------
    phi3=[t(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %salidas con delay -1...-11
        t(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y3=t(12:end,3)';
    
    %%----------------ARX: nn_arxout4-----------------
    phi4=[t(11:end-1,4) t(10:end-2,4) t(9:end-3,4) t(8:end-4,4) t(7:end-5,4) ...                     %salidas con delay -1...-11
        t(6:end-6,4)  t(5:end-7,4)  t(4:end-8,4) t(3:end-9,4) t(2:end-10,4) t(1:end-11,4) ...
        x(11:end-1,1) t(10:end-2,1) t(9:end-3,1) t(8:end-4,1) t(7:end-5,1) ...                     %u1 con delay -1...-11
        x(6:end-6,1)  t(5:end-7,1)  t(4:end-8,1) t(3:end-9,1) t(2:end-10,1) t(1:end-11,1) ...
        x(11:end-1,2) t(10:end-2,2) t(9:end-3,2) t(8:end-4,2) t(7:end-5,2) ...                     %u2 con delay -1...-11
        x(6:end-6,2)  t(5:end-7,2)  t(4:end-8,2) t(3:end-9,2) t(2:end-10,2) t(1:end-11,2) ...
        x(11:end-1,3) t(10:end-2,3) t(9:end-3,3) t(8:end-4,3) t(7:end-5,3) ...                     %u3 con delay -1...-11
        x(6:end-6,3)  t(5:end-7,3)  t(4:end-8,3) t(3:end-9,3) t(2:end-10,3) t(1:end-11,3)]';
    
    y4=t(12:end,4)';
    
    %vector de tiempos
    t=0:tm:length(y)*tm-tm;
    
    %Salida de la red
    yn1=net1(phi1);
    yn1=yn1';
    t1=0:tm:length(yn1)*tm-tm;
    
    yn2=net2(phi2);
    yn2=yn2';
    t2=0:tm:length(yn2)*tm-tm;
    
    yn3=net3(phi3);
    yn3=yn3';
    t3=0:tm:length(yn3)*tm-tm;
    
    yn4=net4(phi4);
    yn4=yn4';
    t4=0:tm:length(yn4)*tm-tm;
    
    
    % [yupper,ylower] = envelope(y1,1500);
    % [yupper,ylower] = envelope(1.5*y1,800,'rms');
    
    %
    
    dynn1=abs(diff(yn1-y1'));
    dynn2=abs(diff(yn2-y2'));
    dynn3=abs(diff(yn3-y3'));
    dynn4=abs(diff(yn4-y4'));
    
    dy1=abs(diff(yo1));
    dy2=abs(diff(yo2));
    dy3=abs(diff(yo3));
    dy4=abs(diff(yo4));
    
    [yupper,ylower] = envelope(1.5*dy1,800,'rms');
    figure
    t1=t1';
    plot(t1,dy1(1:end-10,1),t1,ylower(1:end-10,1),t1,yupper(1:end-10,1))
    [yupper,ylower] = envelope(dy1,800,'rms');
    figure
    plot(t1,dy1(1:end-10,1),t1,ylower(1:end-10,1),t1,yupper(1:end-10,1))
%     figure
    
    % dy1=dy1
%     figure
%     plot(t1(1:end-1),dynn1,'-k')
%     hold on
%     plot(t(1:end-1),dy1,'--r')
%     legend('Der. Residual de red','residual del observador')
%     ylim([0 2])
%     figure
%     plot(t2(1:end-1),dynn2,'-k')
%     hold on
%     plot(t(1:end-1),dy2,'--r')
%     ylim([0 2])
%     legend('Der. Residual de red','residual del observador')
    
end

% figure
% plot(t1,yn1-y1','-k')
% hold on
% plot(t,yo1,'--r')
% % ylim([0 2])
% legend('Residual de red','residual del observador')
% figure
% plot(t2,yn2-y2','-k')
% hold on
% plot(t,yo2,'--r')
% legend('Residual de red','residual del observador')


% figure
% plot(dyn1)
% hold on
% plot(dynn1)

% figure
% plot(t3(1:end-1),dyn3,'-k')
% hold on
% plot(t(1:end-1),dy3,'--r')
% figure
% plot(t4(1:end-1),dyn4,'-k')
% hold on
% plot(t(1:end-1),dy4,'--r')

% plot(t1,yn1,'-k')
% figure
% plot(t2,yn2,'-k')
% figure
% plot(t3,yn3,'-k')
% figure
% plot(t4,yn4,'-k')


% figure
% plot(t1,yn1,'k')
% figure
% plot(t2,yn2,'k')
% figure
% plot(t3,yn3,'k')
% figure
% plot(t4,yn4,'k')



% gensim(net1,tm);
% gensim(net2,tm);
% gensim(net3,tm);
% gensim(net4,tm);

% figure
% [m n]=size(y2);
% for i=1:n
% subplot(n,1,i)
% % plot(t(1:end-1),y(1:end-1,i),'-r',t2,y2(:,i),':b')
% plot(t(1:end-11),y(1:end-11,i),'-r',t2,y2(:,i),':b')
%
% end

% figure
% for i=1:n
% subplot(n,1,i)
% plot(t(1:end-1),abs(y(1:end-1,i)-y2(:,i)),':b')
% end