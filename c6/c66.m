% Load the data
load('delay.mat'); % Assuming delay.mat contains two vectors y and u

% Perform cross-correlation between the sent signal u and received signal y
[correlation, lags] = xcorr(y, u);

% Find the index of the peak of the cross-correlation
[~, idx] = max(abs(correlation));

% The corresponding lag gives the estimate of the delay 2*tau
estimated_delay = lags(idx);

% Since the signal is delayed by 2*tau, the actual tau is half the estimated_delay
tau = estimated_delay / 2;

% Display the result
fprintf('The estimated delay τ is %f seconds.\n', tau);

% Optionally, plot the cross-correlation function
figure;
plot(lags, correlation);
title('Cross-Correlation between u(t) and y(t)');
xlabel('Lags');
ylabel('Correlation');
grid on;

% Highlight the peak point
hold on;
plot(lags(idx), correlation(idx), 'ro');
legend('Cross-Correlation', 'Estimated Delay');
hold off;
