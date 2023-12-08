% Question 2
% Generate and display a Gaussian random signal
N = 100000;
variance = 2;
std_dev = sqrt(variance);
gaussian_signal = std_dev.*randn(1, N); % Zero mean and specified variance

% Display the signal
figure;
plot(gaussian_signal);
title('Gaussian Random Signal');
xlabel('Sample Index');
ylabel('Signal Amplitude');

% Display the PDF of the signal
figure;
hist(gaussian_signal, 100); % 100 bins for the histogram
title('PDF of the Gaussian Random Signal');
xlabel('Signal Amplitude');
ylabel('Frequency');

% Display the CDF of the signal
figure;
cdfplot(gaussian_signal);
title('CDF of the Gaussian Random Signal');
xlabel('Signal Amplitude');
ylabel('Cumulative Probability');