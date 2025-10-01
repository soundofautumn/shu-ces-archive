% Age domain
a = 0:0.1:100;

% Old (O) membership function
mu_O = zeros(size(a));
mu_O(a > 50 & a <= 70) = (a(a > 50 & a <= 70) - 50) / 20;
mu_O(a > 70) = 1;

% Young (Y) membership function
mu_Y = zeros(size(a));
mu_Y(a <= 25) = 1;
mu_Y(a > 25 & a < 70) = (70 - a(a > 25 & a < 70)) / 45;

% Very Young (W) membership function
mu_W = zeros(size(a));
mu_W(a <= 20) = 1;
mu_W(a > 20 & a < 45) = (45 - a(a > 20 & a < 45)) / 25;

% Neither Old Nor Young (V) membership function
mu_V = zeros(size(a));
mu_V(a > 25 & a < 40) = (a(a > 25 & a < 40) - 25) / 15;
mu_V(a >= 40 & a <= 55) = 1;
mu_V(a > 55 & a < 70) = (70 - a(a > 55 & a < 70)) / 15;

% Plot the membership functions
figure;
subplot(2, 2, 1);
plot(a, mu_O, 'k', 'LineWidth', 1.5);
title('Old (O)');
xlabel('Age'); ylabel('Membership');

subplot(2, 2, 2);
plot(a, mu_Y, 'k', 'LineWidth', 1.5);
title('Young (Y)');
xlabel('Age'); ylabel('Membership');

subplot(2, 2, 3);
plot(a, mu_W, 'k', 'LineWidth', 1.5);
title('Very Young (W)');
xlabel('Age'); ylabel('Membership');

subplot(2, 2, 4);
plot(a, mu_V, 'k', 'LineWidth', 1.5);
title('Neither Old Nor Young (V)');
xlabel('Age'); ylabel('Membership');

% Save the figure as a PNG file
saveas(gcf, 'fuzzy_age_membership_functions.png');