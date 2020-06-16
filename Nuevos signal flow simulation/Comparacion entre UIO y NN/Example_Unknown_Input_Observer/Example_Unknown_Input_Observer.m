%% Unknown Input Observer (UIO) for linear time-invariant systems
% Design of an unknown input observer
% Reconstruction of the unknow inputs with a system inversion
% Requires the free YALMIP toolbox: https://yalmip.github.io
% Contact: pierremarie.damon@gmail.com

clear all; close all; clc;


% SYSTEM:
% x_dot = Ax + Bu + Dd
% y     = Cx
% with
% x: vector of states
% y: vector of measures
% u: vector of inputs
% d: vector of unknown inputs
% A: state matrix
% B: input matrix
% D: unknown input matrix
% C: observation matrix


% OBSERVER DESIGN:
% General expression of the UIO:
% z_dot = Nz + Gu + Ly
% x_hat = z - Hy

% Estimation error:
% e = x - x_hat
%   = x - z + Hy
%   = (I+HC)x - z
%   = Px - z           with P = I + HC

% Estimation error dynamics:
% e_dot = Px_dot - z_dot
%       = PAx + PBu + PDd - Nz - Gu - LCx
%       = (PA-LC)x + (PB-G)u + PDd - N(Px-e)
%       = Ne +(PA-LC-NP)x + (PB-G)u + (PD)d

% Existence conditions of the UIO:
% C0: PD = 0  <=>     (I+HC)D = 0
%             <=>     H = -D(CD)^-1 admits a solution iff rang(CD) = rang(D)
% C1: the pair (PA,C) must be detectable <=> rank([sI-A  D; C  0])= rank(A) + rank(D) with s the eigen values of A
% C2: G = PB
% C3: N must be Hurwitz
% C4: PA-LC-NP = 0  <=>     N(I+HC) = PA - LC
%                   <=>     N = PA - (L+NH)C
%                   <=>     N = PA - KC         avec K = L + NH
% Under these conditions: 
% e_dot = (PA - KC)e

% LMIs problem:
% Lyapunov function: 
% V = e^T X e
% Lyapunov function dynamics:
% V_dot = e_dot^T*X*e + e^T*X*e_dot
% V_dot = e^T(A^T*P^T*X + X*P*A - C^T*K^T*X - X*K*C)e
% V_dot = e^T(A^T*P^T*X + X*P*A - C^T*K_bar^T - K_bar*C)e    avec K_bar = X*K


% UI RECONSTRUCTION:
% System inversion to reconstruct the UI:
% y     = C.x
% y_dot = C.x_dot
% y_dot = C.A.x + C.B.u + C.D.d
% d_dot = inc(C.D)(y_dot - C.A.x - C.B.u)


% SYSTEM:
A = [-2      1   1;
      0     -1   3;
     -2      0  -5];
 
B = [ 0; 1; 0];
 
C = [ 0 1 0];

D = [0; 1; 1];


% OBSERVER DESIGN:
% C0:
if rank(C*D)~=rank(D)
     error('rang(CD) different from rang(D)')
end

% C1:
s=eig(A);
for i=1:length(s)    
    if (rank([s(i)*eye(rank(A))-A    D;  C   zeros(size(C,1),size(D,2))]) ~= rank(A) + rank(D))
        error('Non detectable');
    end
end

H = -D*inv(C*D);
P = eye(size(A))+ H*C;

% C2:
G = P*B;

% C3 & C4: 
% Requires YALMIP
X=sdpvar(size(A,1));
K_bar=sdpvar(size(A,1),size(C,1));

a=1e-3;
pb= (X > eye(size(A,1))*a) +...
    (A'*P'*X + X*P*A - C'*K_bar' - K_bar*C < -eye(size(A,1))*a);

solvesdp(pb)

K_bar = double(K_bar);
X     = double(X);

% Matrices computations:
K = inv(X)*K_bar;
N = P*A - K*C;
L = K - N*H;

% Display matrices to copy/past into simulink
% System
DisplayMatrix(A)
DisplayMatrix(B)
DisplayMatrix(C)
DisplayMatrix(D)

% Observer
DisplayMatrix(N)
DisplayMatrix(G)
DisplayMatrix(L)
DisplayMatrix(H)





 