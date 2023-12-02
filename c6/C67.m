% Load the data
load('filtering.mat'); % Replace with the actual path if necessary

% Filter coefficients for a moving average filter
M = 250;
b = ones(1, M) / M;
a = 1;

% Apply the moving average filter to the received signal y
filtered_y = filter(b, a, y);

% Plot the original and filtered signals
figure;
plot(y, 'b');
hold on;
plot(filtered_y, 'r');
title('Received Signal vs. Filtered Signal');
xlabel('Time');
ylabel('Amplitude');
legend('Original Signal', 'Filtered Signal');
