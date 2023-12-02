u5 = sin(2*pi*(2*t)); % time scale by constant > 1
u6 = sin(2*pi*(1/2*t)); % time scale by constant < 1
figure, hold on
stem(t,u,'k'), stem(t,u5,'r'), stem(t,u6,'b')
title('Original signal and its time scaled versions')
xlabel('time, t'), ylabel('u(t), u5(t), u6(t)')