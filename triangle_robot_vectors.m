clear all
close all
clc

%create symbolic variables
syms a1;
syms a2;
syms a3;

%create unit vector directions
p = pi; 
u1 = [cos(p*4/3);sin(p*4/3);1];
u2 = [1;0;1];
u3 = [cos(p*2/3);sin(p*2/3);1];

u1 = u1*a1;
u2 = u2*a2;
u3 = u3*a3;

%create knowns vector
syms Vx;
syms Vy;
syms W;
K = [Vx;Vy;W]


%create augmented matrix and rref
M = [u1,u2,u3,K]

rref(M)

