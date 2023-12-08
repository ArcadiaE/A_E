% Load the data from the .mat file
load('delay.mat'); % Replace with the correct path to your .mat file

% Compute the cross-correlation between u and y
[cross_corr, lags] = xcorr(y, u);

% Find the index of the maximum value of cross-correlation
[~, max_index] = max(cross_corr);

% The lag corresponding to the maximum index gives the delay estimate
estimated_tau = lags(max_index);

% Plot the original signals
figure;
subplot(3,1,1);
plot(u);
title('Original Signal u(t)');
xlabel('Time [samples]');
ylabel('Amplitude');

subplot(3,1,2);
plot(y);
title('Received Signal y(t)');
xlabel('Time [samples]');
ylabel('Amplitude');

% Plot the cross-correlation function
subplot(3,1,3);
plot(lags, cross_corr);
title('Cross-Correlation between y(t) and u(t)');
xlabel('Lags [samples]');
ylabel('Cross-correlation amplitude');

% Highlight the peak with a red marker
hold on;
plot(estimated_tau, cross_corr(max_index), 'ro');
legend('Cross-Correlation', 'Estimated Delay');

% Display the estimated delay
disp(['Estimated delay τ is: ', num2str(estimated_tau), ' samples']);
