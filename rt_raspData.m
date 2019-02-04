close all
clear
clc
% load raspData.mat
load('datan3.mat');
dt=datan3(:,1);
val=datan3(:,1);
dtn=[];
j=1;
for i=1:length(dt)-1
    if dt(i+1)<dt(i)
        dtn=[dtn;dt(i-5) dt(i-4) dt(i-3) dt(i-2) dt(i-1) dt(i) dt(i+1) dt(i+2) dt(i+3) dt(i+4) dt(i+5)]; 
        j=j+1;
    end
end

dt=[];
m=[];
for j=1:size(dtn,1)
    for i=1:size(dtn,2)-1
        dt(j,i)=dtn(j,i+1)-dtn(j,i);
    end
    %dt=[dt;];
end

m=median([dt(:,1:5) dt(:,7:end)]')';

dtM = 5000;
t=zeros(length(dt),1);
conteo = 0;
for i=1:length(dt)
    if dt(i) > dtM*5 %|| dt(i) < dtM*0.0000003
        conteo = conteo + 1;
        dt(i) = dtM;
    end
end

%%
t(1) = dt(1);
for i = 2:length(dt)
    t(i) = t(i-1)+dt(i);
end

plot(t,val);
title('Raspberry Pi 3b - RT output for Diesel Engine emulation')
xlabel('time (\mu S)')
ylabel('Diesel Voltage (Volts)')
grid on
grid minor