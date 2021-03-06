clc
clear
close all

%Datos de entrada y salida
load('datos_ataque_individual.mat');
% load('ataque_individual_red.mat');
load('tm.mat');


%Promedio de los UIOs
yo1=y1;
yo2=y2;
yo3=y3;
yo4=y4;

%Modelos de redes neuronales para cada salida [y1 y2 y3 y4]'
i=1; %i=1 NN con varias salidas i~=1 NN con salida única
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
    
    
    ynn1=(yn2+yn3+yn4-3*y_ma(12:end,:))/3;
    ynn2=(yn1+yn3+yn4-3*y_ma(12:end,:))/3;
    ynn3=(yn2+yn1+yn4-3*y_ma(12:end,:))/3;
    ynn4=(yn2+yn3+yn1-3*y_ma(12:end,:))/3;
    
    
    dy1=abs(diff(ynn1(:,1)'));
    dy2=abs(diff(ynn2(:,2)''));
    dy3=abs(diff(ynn3(:,3)'));
    dy4=abs(diff(ynn4(:,4)'));
    
    %Umbral con lag & lead
    tao1=0.0000002;%0.002;
    tao2=tao1;
    taod=1;%tao1;
    sis1=tf([taod 0],[tao1 1 0]);
    sis2=tf(1,[tao2 1]);
    [sal tn]=lsim(sis1,dy1,t1(1:1:end-1));
    [u1 tn1]=lsim(sis2,abs(sal)+(4/3)*0.04,tn);
    [sal tn]=lsim(sis1,dy2,t2(1:1:end-1));
    [u2 tn2]=lsim(sis2,abs(sal)+(4/3)*0.04,tn);
    [sal tn]=lsim(sis1,dy3,t3(1:1:end-1));
    [u3 tn3]=lsim(sis2,abs(sal)+(4/3)*0.04,tn);
    [sal tn]=lsim(sis1,dy4,t4(1:1:end-1));
    [u4 tn4]=lsim(sis2,abs(sal)+(4/3)*0.04,tn);
    
    %Umbrales y derivadas de los sensores aislados
    figure
    subplot(2,2,1)
    plot(tn1,u1,'k',tn,dy1,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 1','Residual 1')
    ylim([0 1])
    subplot(2,2,2)
    plot(tn2,u2,'k',tn,dy2,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 2','Residual 2')
    ylim([0 1])
    subplot(2,2,3)
    plot(tn3,u3,'k',tn,dy3,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 3','Residual 3')
    ylim([0 1])
    subplot(2,2,4)
    plot(tn4,u4,'k',tn,dy4,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 4','Residual 4')
    ylim([0 1])
    %     suptitle('Umbrales y derivadas de residuales(NN) en ataques individuales')
    
    [m n]=size(u1);
    
    a1=zeros(m,n);
    a2=a1;
    a3=a1;
    a4=a1;
    b1=0;
    b2=0;
    b3=0;
    b4=0;
    c1=0;
    c2=0;
    c3=0;
    c4=0;
    for i=1:m
        
        if i>60  %tiempo inicial a quitar t(i)
            
            if (dy1(i)>u1(i) || b1==1) && c1<2 %dy1(i)>u1(i) && dy2(i)<u2(i) && dy3(i)<u3(i) && dy4(i)<u4(i)
                if dy1(i)>u1(i)
                    c1=c1+1;
                end
                a1(i)=1;
                b1=1;
                
            else
                a1(i)=0;
                b1=0;
                c1=0;
            end
            
            if (dy2(i)>u2(i)|| b2==1) && c2<2% dy1(i)<u1(i) && dy2(i)>u2(i) && dy3(i)<u3(i) && dy4(i)<u4(i)
                if dy2(i)>u2(i)
                    c2=c2+1;
                end
                a2(i)=1;
                b2=1;
                
            else
                a2(i)=0;
                b2=0;
                c2=0;
            end
            
            if (dy3(i)>u3(i)|| b3==1) && c3<2 %dy1(i)<u1(i) && dy2(i)<u2(i) && dy3(i)>u3(i) && dy4(i)<u4(i)
                if dy3(i)>u3(i)
                    c3=c3+1;
                end
                a3(i)=1;
                b3=1;
                
            else
                a3(i)=0;
                b3=0;
                c3=0;
            end
            
            if (dy4(i)>u4(i)|| b4==1) && c4<2 %dy1(i)<u1(i) && dy2(i)<u2(i) && dy3(i)<u3(i) && dy4(i)>u4(i)
                if dy4(i)>u4(i)
                    c4=c4+1;
                end
                a4(i)=1;
                b4=1;
                
            else
                a4(i)=0;
                b4=0;
                c4=0;
            end
        end
        
        
    end
    
    %Graficas de alarmas
    figure
    subplot(2,2,1)
    plot(tn1,a1,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 1')
    subplot(2,2,2)
    plot(tn2,a2,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 2')
    subplot(2,2,3)
    plot(tn3,a3,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 3')
    subplot(2,2,4)
    plot(tn4,a4,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 4')
%     suptitle('Alarmas de sensores en ataques individuales (NN)')
    
    
    
    %Datos de entrada y salida
    %     load('datos_ataque_multiple_2.mat');
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
    
    dy1=abs(diff(yn1(:,1)'));
    dy2=abs(diff(yn2(:,2)'));
    dy3=abs(diff(yn3(:,3)'));
    dy4=abs(diff(yn4(:,4)'));
    
    %Umbral con lag & lead
    tao1=0.0000002;%0.002;
    tao2=tao1;
    taod=1;%tao1;
    sis1=tf([taod 0],[tao1 1 0]);
    sis2=tf(1,[tao2 1]);
    [sal tn]=lsim(sis1,dy1,t1(1:1:end-1));
    [u1 tn1]=lsim(sis2,abs(sal)+(4/3)*0.4,tn);
    [sal tn]=lsim(sis1,dy2,t2(1:1:end-1));
    [u2 tn2]=lsim(sis2,abs(sal)+(4/3)*1.5,tn);
    [sal tn]=lsim(sis1,dy3,t3(1:1:end-1));
    [u3 tn3]=lsim(sis2,abs(sal)+(4/3)*10,tn);
    [sal tn]=lsim(sis1,dy4,t4(1:1:end-1));
    [u4 tn4]=lsim(sis2,abs(sal)+(4/3)*1.5,tn);
    
    %Umbrales y derivadas de los sensores aislados
    figure
    subplot(2,2,1)
    plot(tn1,u1,'k',tn,dy1,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 1','Residual 1')
    ylim([0 1])
    subplot(2,2,2)
    plot(tn2,u2,'k',tn,dy2,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 2','Residual 2')
    ylim([0 1])
    subplot(2,2,3)
    plot(tn3,u3,'k',tn,dy3,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 3','Residual 3')
    ylim([0 1])
    subplot(2,2,4)
    plot(tn4,u4,'k',tn,dy4,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 4','Residual 4')
    ylim([0 1])
%     suptitle('Umbrales y derivadas de residuales(NN) en ataques simultáneos')
    
    [m n]=size(u1);
    
    a1=zeros(m,n);
    a2=a1;
    a3=a1;
    a4=a1;
    b1=0;
    b2=0;
    b3=0;
    b4=0;
    c1=0;
    c2=0;
    c3=0;
    c4=0;
    for i=1:m
        
        if i>60  %tiempo inicial a quitar t(i)
            
            if (dy1(i)>u1(i) || b1==1) && c1<2 %dy1(i)>u1(i) && dy2(i)<u2(i) && dy3(i)<u3(i) && dy4(i)<u4(i)
                if dy1(i)>u1(i)
                    c1=c1+1;
                end
                a1(i)=1;
                b1=1;
                
            else
                a1(i)=0;
                b1=0;
                c1=0;
            end
            
            if (dy2(i)>u2(i)|| b2==1) && c2<2% dy1(i)<u1(i) && dy2(i)>u2(i) && dy3(i)<u3(i) && dy4(i)<u4(i)
                if dy2(i)>u2(i)
                    c2=c2+1;
                end
                a2(i)=1;
                b2=1;
                
            else
                a2(i)=0;
                b2=0;
                c2=0;
            end
            
            if (dy3(i)>u3(i)|| b3==1) && c3<2 %dy1(i)<u1(i) && dy2(i)<u2(i) && dy3(i)>u3(i) && dy4(i)<u4(i)
                if dy3(i)>u3(i)
                    c3=c3+1;
                end
                a3(i)=1;
                b3=1;
                
            else
                a3(i)=0;
                b3=0;
                c3=0;
            end
            
            if (dy4(i)>u4(i)|| b4==1) && c4<2 %dy1(i)<u1(i) && dy2(i)<u2(i) && dy3(i)<u3(i) && dy4(i)>u4(i)
                if dy4(i)>u4(i)
                    c4=c4+1;
                end
                a4(i)=1;
                b4=1;
                
            else
                a4(i)=0;
                b4=0;
                c4=0;
            end
        end
        
        
    end
    
    %Graficas de alarmas
    figure
    subplot(2,2,1)
    plot(tn1,a1,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 1')
    subplot(2,2,2)
    plot(tn2,a2,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 2')
    subplot(2,2,3)
    plot(tn3,a3,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 3')
    subplot(2,2,4)
    plot(tn4,a4,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 4')

%     suptitle('Alarmas de sensores en ataques simultáneos (NN)')
    
    
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
    
    %Umbral con lag & lead
    tao1=0.000002;%0.0000002;%0.002;
    tao2=tao1;
    taod=1;%tao1;
    sis1=tf([taod 0],[tao1 1 0]);
    sis2=tf(1,[tao2 1]);
    [sal tn]=lsim(sis1,dy1,t(1:1:end-1));
    [u1 tn1]=lsim(sis2,abs(sal)+(4/3)*0.04,tn);
    [sal tn]=lsim(sis1,dy2,t(1:1:end-1));
    [u2 tn2]=lsim(sis2,abs(sal)+(4/3)*0.04,tn);
    [sal tn]=lsim(sis1,dy3,t(1:1:end-1));
    [u3 tn3]=lsim(sis2,abs(sal)+(4/3)*0.04,tn);
    [sal tn]=lsim(sis1,dy4,t(1:1:end-1));
    [u4 tn4]=lsim(sis2,abs(sal)+(4/3)*0.04,tn);
    
    %Umbrales y derivadas de los sensores aislados
    figure
    subplot(2,2,1)
    plot(tn1,u1,'k',tn,dy1,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 1','Residual 1')
    ylim([0 1])
    subplot(2,2,2)
    plot(tn2,u2,'k',tn,dy2,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 2','Residual 2')
    ylim([0 1])
    subplot(2,2,3)
    plot(tn3,u3,'k',tn,dy3,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 3','Residual 3')
    ylim([0 1])
    subplot(2,2,4)
    plot(tn4,u4,'k',tn,dy4,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 4','Residual 4')
    ylim([0 1])
    
    %     suptitle('Umbrales y derivadas de residuales en ataques individuales')
    
    [m n]=size(u1);
    
    a1=zeros(m,n);
    a2=a1;
    a3=a1;
    a4=a1;
    b1=0;
    b2=0;
    b3=0;
    b4=0;
    c1=0;
    c2=0;
    c3=0;
    c4=0;
    for i=1:m
        
        if i>60  %tiempo inicial a quitar t(i)
            
            if (dy1(i)>u1(i) || b1==1) && c1<2 %dy1(i)>u1(i) && dy2(i)<u2(i) && dy3(i)<u3(i) && dy4(i)<u4(i)
                if dy1(i)>u1(i)
                    c1=c1+1;
                end
                a1(i)=1;
                b1=1;
                
            else
                a1(i)=0;
                b1=0;
                c1=0;
            end
            
            if (dy2(i)>u2(i)|| b2==1) && c2<2% dy1(i)<u1(i) && dy2(i)>u2(i) && dy3(i)<u3(i) && dy4(i)<u4(i)
                if dy2(i)>u2(i)
                    c2=c2+1;
                end
                a2(i)=1;
                b2=1;
                
            else
                a2(i)=0;
                b2=0;
                c2=0;
            end
            
            if (dy3(i)>u3(i)|| b3==1) && c3<2 %dy1(i)<u1(i) && dy2(i)<u2(i) && dy3(i)>u3(i) && dy4(i)<u4(i)
                if dy3(i)>u3(i)
                    c3=c3+1;
                end
                a3(i)=1;
                b3=1;
                
            else
                a3(i)=0;
                b3=0;
                c3=0;
            end
            
            if (dy4(i)>u4(i)|| b4==1) && c4<2 %dy1(i)<u1(i) && dy2(i)<u2(i) && dy3(i)<u3(i) && dy4(i)>u4(i)
                if dy4(i)>u4(i)
                    c4=c4+1;
                end
                a4(i)=1;
                b4=1;
                
            else
                a4(i)=0;
                b4=0;
                c4=0;
            end
        end
        
        
    end
    
    %Graficas de alarmas
    figure
    subplot(2,2,1)
    plot(tn1,a1,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 1')
    subplot(2,2,2)
    plot(tn2,a2,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 2')
    subplot(2,2,3)
    plot(tn3,a3,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 3')
    subplot(2,2,4)
    plot(tn4,a4,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 4')
    %     suptitle('Alarmas de sensores en ataques individuales')
    
    
    %Umbral con envolvene
    %     [yupper,ylower] = envelope(dy1);%(dy1,2500,'analytic');%(1.5*dy1,800,'rms');
    %     ys=sgolayfilt(dy1,11,101);
    %     figure
    %     plot(t1,dy1(1:end-10,1),'k',t(1:1:end-1),abs(ys),'r')
    %     figure
    %     diferencia=dy1-ys;
    %     plot(t(1:1:end-1),diferencia)
    %     figure
    %     plot(t1,dy1(1:end-10,1),'k',t1,yupper(1:end-10,1),'r')
    %     [yupper,ylower] = envelope(0.9*dy1);%(dy1,800,'rms');
    %     figure
    %     plot(t1,dy1(1:end-10,1),'k',t1,yupper(1:end-10,1),'r')
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
    %load('datos_ataque_multiple_2.mat');
    %     load('datos_ataque_multiple.mat');
    load('ataque_simultaneo_red.mat');
    
    if tm==1e-5
        tm=tm*2;
    end
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
    
    %-----------------Umbral con envolvente
    %     [yupper,ylower] = envelope(dy1);%(1.5*dy1,800,'rms');
    %     figure
    %     t1=t1';
    %     plot(t1,dy1(1:end-10,1),'k',t1,yupper(1:end-10,1),'r')
    %     [yupper,ylower] = envelope(0.9*dy1);%(dy1,800,'rms');
    %     figure
    %     plot(t1,dy1(1:end-10,1),'k',t1,yupper(1:end-10,1),'r')
    
    %-----------------Umbral con lag & lead
    
    [sal tn]=lsim(sis1,dy1,t(1:1:end-1));
    [u1 tn1]=lsim(sis2,abs(sal)+(4/3)*0.04,tn);
    [sal tn]=lsim(sis1,dy2,t(1:1:end-1));
    [u2 tn2]=lsim(sis2,abs(sal)+(4/3)*0.04,tn);
    [sal tn]=lsim(sis1,dy3,t(1:1:end-1));
    [u3 tn3]=lsim(sis2,abs(sal)+(4/3)*0.04,tn);
    [sal tn]=lsim(sis1,dy4,t(1:1:end-1));
    [u4 tn4]=lsim(sis2,abs(sal)+(4/3)*0.04,tn);
    
    %Umbrales y derivadas de los sensores aislados
    figure
    subplot(2,2,1)
    plot(tn1,u1,'k',tn,dy1,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 1','Residual 1')
    ylim([0 1])
    subplot(2,2,2)
    plot(tn2,u2,'k',tn,dy2,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 2','Residual 2')
    ylim([0 1])
    subplot(2,2,3)
    plot(tn3,u3,'k',tn,dy3,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 3','Residual 3')
    ylim([0 1])
    subplot(2,2,4)
    plot(tn4,u4,'k',tn,dy4,'r')
    xlabel('Time (seconds)')
    legend('Adaptive threshold 4','Residual 4')
    ylim([0 1])
    %     suptitle('Umbrales y derivadas de residuales en ataques simultáneos')
    
    [m n]=size(u1);
    
    a1=zeros(m,n);
    a2=a1;
    a3=a1;
    a4=a1;
    b1=0;
    b2=0;
    b3=0;
    b4=0;
    c1=0;
    c2=0;
    c3=0;
    c4=0;
    for i=1:m
        
        if i>60  %tiempo inicial a quitar t(i)
            
            if (dy1(i)>u1(i) || b1==1) && c1<2 %dy1(i)>u1(i) && dy2(i)<u2(i) && dy3(i)<u3(i) && dy4(i)<u4(i)
                if dy1(i)>u1(i)
                    c1=c1+1;
                end
                a1(i)=1;
                b1=1;
                
            else
                a1(i)=0;
                b1=0;
                c1=0;
            end
            
            if (dy2(i)>u2(i)|| b2==1) && c2<2% dy1(i)<u1(i) && dy2(i)>u2(i) && dy3(i)<u3(i) && dy4(i)<u4(i)
                if dy2(i)>u2(i)
                    c2=c2+1;
                end
                a2(i)=1;
                b2=1;
                
            else
                a2(i)=0;
                b2=0;
                c2=0;
            end
            
            if (dy3(i)>u3(i)|| b3==1) && c3<2 %dy1(i)<u1(i) && dy2(i)<u2(i) && dy3(i)>u3(i) && dy4(i)<u4(i)
                if dy3(i)>u3(i)
                    c3=c3+1;
                end
                a3(i)=1;
                b3=1;
                
            else
                a3(i)=0;
                b3=0;
                c3=0;
            end
            
            if (dy4(i)>u4(i)|| b4==1) && c4<2 %dy1(i)<u1(i) && dy2(i)<u2(i) && dy3(i)<u3(i) && dy4(i)>u4(i)
                if dy4(i)>u4(i)
                    c4=c4+1;
                end
                a4(i)=1;
                b4=1;
                
            else
                a4(i)=0;
                b4=0;
                c4=0;
            end
        end
        
        
    end
    
    %Graficas de alarmas
    figure
    subplot(2,2,1)
    plot(tn1,a1,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 1')
    subplot(2,2,2)
    plot(tn2,a2,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 2')
    subplot(2,2,3)
    plot(tn3,a3,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 3')
    subplot(2,2,4)
    plot(tn4,a4,'LineWidth',1);
    xlabel('Time (seconds)')
    title('Sensor alarm 4')
    %     suptitle('Alarmas de sensores en ataques simultáneos')
    
    
    
end
