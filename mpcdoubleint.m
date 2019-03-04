%% Control of a Single-Input-Single-Output Plant
% This example shows how to control a double integrator plant under input
% saturation in Simulink(R).

% Copyright 1990-2014 The MathWorks, Inc.

%% Define Plant Model
% The linear open-loop dynamic model is a double integrator:
plant = tf(1,[1 0 0]);

%% Design MPC Controller
% Create the controller object with sampling period, prediction and control
% horizons:
Ts = 0.1;   
p = 10;
m = 3;
mpcobj = mpc(plant, Ts, p, m);
%%
% Specify actuator saturation limits as MV constraints.
mpcobj.MV = struct('Min',-1,'Max',1); 

%% Simulate Using Simulink(R)
% To run this example, Simulink(R) is required.
if ~mpcchecktoolboxinstalled('simulink')
    disp('Simulink(R) is required to run this example.')
    return
end
%%
% Simulate closed-loop control of the linear plant model in Simulink.
% Controller "mpcobj" is specified in the block dialog.
% mdl = 'mpc_doubleint';
% open_system(mdl);
% sim(mdl);
% %%
% % The closed-loop response shows good setpoint tracking performance.
% 
% %%
% bdclose(mdl)