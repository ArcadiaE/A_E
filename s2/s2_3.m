g = 9.81;       % gravity constant in m/s^2
L = 0.20;       % length of the pendulum in meters
w = sqrt(g / L);


P_s = tf([0, 0, -w^2], [1, 0, -w^2]); % create the transfer function


k = 10; 
sysclp1 = feedback(P_s,k);
%step(sysclp1);              

sysclp2 = feedback(P_s,k,+1);
%t = 0 : 0.1 : 100;
%step(sysclp2, t);

%rlocus(P_s); % For negative feedback
rlocus(-P_s); % For positive feedback

% Plot the step response
%disp(sysclp1);
%disp(sysclp2);
%disp(P_s);

%step(P_s);

title("Root Locus Analysis");
xlabel("Im (seconds^-1 )");
ylabel("Re (seconds^-1 )");