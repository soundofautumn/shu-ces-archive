% Model Reference Aapative RBF Control
clear; close all;

u_1 = 0;
y_1 = 0;
ym_1 = 0;

x = [0, 0, 0]';
c = [-3 -2 -1 1 2 3;
   -3 -2 -1 1 2 3;
   -3 -2 -1 1 2 3];
b = 2 * ones(6, 1);
w = rands(6, 1);

xite = 0.35;
alfa = 0.05;
h = [0, 0, 0, 0, 0, 0]';
w_1 = w; w_2 = w;

ts = 0.001;

for k = 1:1:3000
    time(k) = k * ts;

    r(k) = 0.5 * sin(2 * pi * k * ts);
    ym(k) = 0.6 * ym_1 + r(k);

    y(k) = (-0.1 * y_1 + u_1) / (1 + y_1 ^ 2); % Nonlinear plant

    for j = 1:1:6
        h(j) = exp(-norm(x - c(:, j)) ^ 2 / (2 * b(j) * b(j)));
    end

    u(k) = w' * h;

    ec(k) = ym(k) - y(k);
    dyu(k) = sign((y(k) - y_1) / (u(k) - u_1));

    d_w = 0 * w;

    for j = 1:1:6
        d_w(j) = xite * ec(k) * h(j) * dyu(k);
    end

    w = w_1 + d_w + alfa * (w_1 - w_2);

    u_1 = u(k);
    y_1 = y(k);
    ym_1 = ym(k);

    x(1) = r(k);
    x(2) = ec(k);
    x(3) = y(k);

    w_2 = w_1; w_1 = w;
end

figure(1);
plot(time, ym, 'r', time, y, 'b');
xlabel('time(s)'); ylabel('ym,y');
saveas(gcf, 'chap9_4_1.png');

figure(2);
plot(time, ym - y, 'r');
xlabel('time(s)'); ylabel('tracking error');
saveas(gcf, 'chap9_4_2.png');
