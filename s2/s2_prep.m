L = 0.2; % effective length of pendulum 
g = 9.81; % const
w = sqrt(g/L); % oscillation freqency
Pdm = tf([0,0,-w^2],[1,0,-w^2]); % transfer function model of Pendulum
step(Pdm); % step input
disp(Pdm);
%rlocus(Pdm); % root locus of Pendulum Model