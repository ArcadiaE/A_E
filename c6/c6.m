clear all, close all
T = 1; ts = 0.01; % time horizon and discretization time
t = 0:ts:T; % time vector
phi = 0;
u = sin(2*pi*0.9*t + phi);
%u = sin(2*pi*1.1*t + phi); % signal
figure, hold on, stem(t,u,'k')
title('Signal'), xlabel('time, t'), ylabel('u(t)')