% Generation of a Delayed Unit Step Sequence
n = -20:20; % Generate a vector from -20 to 20
sd = [zeros(1,30) ones(1,11)]; % Generate the delayed unit step sequence with a delay of 10 samples
% Plot the delayed unit step sequence
stem(n, sd);
xlabel('n');
ylabel('sd[n]');
axis([-20 20 -0.2 1.2]);
