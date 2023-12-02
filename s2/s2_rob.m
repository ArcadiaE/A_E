g = 9.81;       % gravity constant in m/s^2
L = 0.20;       % length of the pendulum in meters
w = sqrt(g / L);

c = 10;
tao = 1 / (w * c);

P_s = tf([0, 0, -w^2], [1, 0, -w^2]); % create the transfer function

RealCompensator = tf ([0.1,1],[0.01,1]); % Real Compensator

servo = tf([0,0,1],[0.00025 0.02 1]);%add neglected servo dynamics
actual = series(servo,P_s);

sys1=series(-RealCompensator,actual);
rlocus(sys1);

k = rlocfind (sys1); %demonstrate the value of K on Root Locus Diagram  
sysclp = feedback (sys1,k); %Construct the Close Loop
%bode(sysclp); % Bode(Gain&Phase Analysis)
nyquistplot(sysclp); %Plot Nyquist Diagram