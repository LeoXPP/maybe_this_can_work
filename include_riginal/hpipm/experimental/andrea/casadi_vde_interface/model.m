clc;
clear all;
close all;

import casadi.*

% constants
M = 1;
m = 0.1;
g = 9.81;
l = 0.8;

% variables
x1 = SX.sym('x1');
theta = SX.sym('theta');
v1 = SX.sym('v1');
dtheta = SX.sym('dtheta');

F = SX.sym('F');

x = [x1; theta; v1; dtheta];
u = F;

nx = length(x);
nu = length(u);

% ODE system

f_expl = [   v1; ...
             dtheta; ...
             (- l*m*sin(theta)*dtheta^2 + F + g*m*cos(theta)*sin(theta))/(M + m - m*cos(theta)^2); ...
             (- l*m*cos(theta)*sin(theta)*dtheta^2 + F*cos(theta) + g*m*sin(theta) + M*g*sin(theta))/(l*(M + m - m*cos(theta)^2)) ];


odeFun = Function('odeFun',{x,u},{f_expl});

Sx = SX.sym('Sx',nx,nx);
Sp = SX.sym('Sp',nx,nu);
lambdaX = SX.sym('lambdaX',nx,1);

vdeX = SX.zeros(nx,nx);
vdeX = vdeX + jtimes(f_expl,x,Sx);

vdeP = SX.zeros(nx,nu) + jacobian(f_expl,u);
vdeP = vdeP + jtimes(f_expl,x,Sp);

vdeFun = Function('vdeFun',{x,Sx,Sp,u},{f_expl,vdeX,vdeP});

jacX = SX.zeros(nx,nx) + jacobian(f_expl,x);
jacFun = Function('jacFun',{x,u},{f_expl,jacX});

%adj = jtimes(f_expl,[x;u],lambdaX,true);
adj = jtimes(f_expl,[u;x],lambdaX,true);

adjFun = Function('adjFun',{x,lambdaX,u},{adj});

S_forw = vertcat(horzcat(Sx, Sp), horzcat(zeros(nu,nx), eye(nu)));
hess = S_forw.'*jtimes(adj,[x;u],S_forw);
hess2 = [];
for j = 1:nx+nu
    for i = j:nx+nu
        hess2 = [hess2; hess(i,j)];
    end
end

hessFun = Function('hessFun',{x,Sx,Sp,lambdaX,u},{adj,hess2});

opts = struct('mex', false);
odeFun.generate(['ode_model'], opts);
vdeFun.generate(['vde_forw_model'], opts);
jacFun.generate(['jac_model'], opts);
adjFun.generate(['vde_adj_model'], opts);
hessFun.generate(['vde_hess_model'], opts);
