% Load the data from the .mat file
load('filtering.mat'); % Replace with the correct path to your .mat file

% Filter coefficients
M = 250;
b = ones(1, M) / M;
a = 1;

% Apply the filter to the received signal y
filtered_signal = filter(b, a, y);

% Plot the original and filtered signals for comparison
figure;
subplot(2,1,1);
plot(y);
title('Received Signal y(t) with Noise');
xlabel('Time [samples]');
ylabel('Amplitude');

subplot(2,1,2);
plot(filtered_signal);
title('Filtered Signal');
xlabel('Time [samples]');
ylabel('Amplitude');