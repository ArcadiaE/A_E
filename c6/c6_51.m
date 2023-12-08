% Question 1
% Generate and display a uniform random signal
N = 100000;
a = -4;
b = 4;
uniform_signal = a + (b-a).*rand(1, N);

% Display the signal
figure;
plot(uniform_signal);
title('Uniform Random Signal');
xlabel('Sample Index');
ylabel('Signal Amplitude');

% Display the PDF of the signal
figure;
hist(uniform_signal, 100); % 100 bins for the histogram
title('PDF of the Uniform Random Signal');
xlabel('Signal Amplitude');
ylabel('Frequency');

% Display the CDF of the signal
figure;
cdfplot(uniform_signal);
title('CDF of the Uniform Random Signal');
xlabel('Signal Amplitude');
ylabel('Cumulative Probability');