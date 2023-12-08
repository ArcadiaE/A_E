u1 = sin(2*pi*(t+1/4)); % positive time shift
u2 = sin(2*pi*(t-1/4)); % negative time shift
u3 = sin(2*pi*t+pi/2); % positive phase shift
u4 = sin(2*pi*t-pi/2); % negative phase shift
figure, hold on
stem(t,u,'k'), stem(t,u1,'r'), stem(t,u2,'b')
title('Original signal and its time shifts')
xlabel('time, t'), ylabel('u(t), u1(t), u2(t)')
figure, hold on
stem(t,u,'k'), stem(t,u3,'r'), stem(t,u4,'b')
title('Original signal and its phase shifts')
xlabel('time, t'), ylabel('u(t), u3(t), u4(t)')