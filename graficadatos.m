clear
clc
close all
%grafica de datos de la raspberry
load('data5.mat');
%Control Terciario-------Salidas
figure
plot(data5(:,1))
hold on
plot(data5(:,2))
legend('Pb','Qb')
grid on
title('Potencias generadas por el control terciario para la fuente de Biomasa')
figure
plot(data5(:,3))
hold on
plot(data5(:,4))
legend('Pd','Qd')
grid on
title('Potencias generadas por el control terciario para la fuente de Diesel')

%Carga
figure
plot(data5(:,5))
hold on
plot(data5(:,6))
legend('Pm','Qm')
grid on
title('Potencias medidas en la carga')
figure
subplot(2,2,1)
plot(data5(:,7))
title('i1-Biomasa')
% hold on 
subplot(2,2,2)
plot(data5(:,8))
title('i2-Diesel')
subplot(2,2,3)
plot(data5(:,9))
title('i3-Fuentes alternativas')
subplot(2,2,4)
plot(data5(:,10))
title('Vload')
% legend('i1-Biomasa','i2-Diesel','i3-Fuentes alternativas','Vload')
grid on
% title('Variables en la carga')