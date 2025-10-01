% Membership function simulation for 6 types
clear all;
close all;

x = 0:0.1:10;

% Gaussian membership function
y1 = gaussmf(x, [2 5]);
subplot(3, 2, 1);
plot(x, y1, 'k');
title('Gaussian MF');
xlabel('x'); ylabel('y');

% General Bell membership function
y2 = gbellmf(x, [2 4 6]);
subplot(3, 2, 2);
plot(x, y2, 'k');
title('General Bell MF');
xlabel('x'); ylabel('y');

% S membership function
y3 = sigmf(x, [2 4]);
subplot(3, 2, 3);
plot(x, y3, 'k');
title('S MF');
xlabel('x'); ylabel('y');

% Trapezoid membership function
y4 = trapmf(x, [1 5 7 8]);
subplot(3, 2, 4);
plot(x, y4, 'k');
title('Trapezoid MF');
xlabel('x'); ylabel('y');

% Triangle membership function
y5 = trimf(x, [3 6 8]);
subplot(3, 2, 5);
plot(x, y5, 'k');
title('Triangle MF');
xlabel('x'); ylabel('y');

% Z membership function
y6 = zmf(x, [3 7]);
subplot(3, 2, 6);
plot(x, y6, 'k');
title('Z MF');
xlabel('x'); ylabel('y');

% Save the figure as a PNG file
saveas(gcf, 'membership_functions.png');