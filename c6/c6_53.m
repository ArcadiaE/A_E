% MATLAB Program for Question 3

% Array of different values for N
N_values = [100, 500, 2000, 10000];

% Loop through each N value
for N = N_values
    % Generate a Gaussian random variable with zero mean and unit variance
    x = randn(1, N);
    
    % Plot the histogram
    figure;
    hist(x, 50); % Using 50 bins for the histogram
    title(['Histogram of Gaussian RV with N = ', num2str(N)]);
    xlabel('Value');
    ylabel('Frequency');
    
    % Overlay the theoretical PDF
    hold on;
    edges = linspace(min(x), max(x), 50); % Bin edges for the histogram
    pdf_values = normpdf(edges, 0, 1); % Theoretical PDF values
    pdf_values = pdf_values * (max(x) - min(x)) / sum(pdf_values); % Scale PDF to match the histogram
    plot(edges, pdf_values * N, 'r', 'LineWidth', 2); % Plotting the theoretical PDF
    hold off;

        % Calculate and plot the empirical CDF
    figure;
    [cdf_values, cdf_edges] = ecdf(x); % Empirical CDF
    stairs(cdf_edges, cdf_values, 'b', 'LineWidth', 2); % Plotting the empirical CDF
    hold on;
    theoretical_cdf = normcdf(edges, 0, 1); % Theoretical CDF
    plot(edges, theoretical_cdf, 'r--', 'LineWidth', 2); % Plotting the theoretical CDF
    title(['CDF of Gaussian RV with N = ', num2str(N)]);
    xlabel('Value');
    ylabel('Cumulative Probability');
    legend('Empirical CDF', 'Theoretical CDF');
    hold off;
end
end
