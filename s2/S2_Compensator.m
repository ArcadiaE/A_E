g = 9.81;       % gravity constant in m/s^2
L = 0.20;       % length of the pendulum in meters
w = sqrt(g / L);

c = 10;
tao = 1 / (w * c);

P_s = tf([0, 0, -w^2], [1, 0, -w^2]); % create the transfer function

Compensator = tf ([(c * tao),1],[tao,1]); % Real Compensator 
RealCompensator = tf ([0.1,1],[0.01,1]); % Real Compensator

servo = tf([0,0,1],[0.00025 0.02 1]);%add neglected servo dynamics
actual = series(servo,P_s);

sys1=series(-Compensator,P_s);
sys2=series(-RealCompensator,P_s);
sys3=series(-RealCompensator,actual);

rlocus(sys3); 
[k, poles] = rlocfind(sys3); % use rlocfind to find gain on root locus

% print the gain
fprintf('Selected gain: %f\n', k);  