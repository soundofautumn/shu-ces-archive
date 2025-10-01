%Expert PID Controller
clear;
close all;
ts = 0.001;

sys = tf(5.235e005, [1, 87.35, 1.047e004, 0]); %Plant
dsys = c2d(sys, ts, 'z');
[num, den] = tfdata(dsys, 'v');

u_1 = 0; u_2 = 0; u_3 = 0;
y_1 = 0; y_2 = 0; y_3 = 0;

x = [0, 0, 0]';
x2_1 = 0;

kp = 0.6;
ki = 0.03;
kd = 0.01;

error_1 = 0;

for k = 1:1:500
    time(k) = k * ts;

    r(k) = 1.0; %Tracing Step Signal

    u(k) = kp * x(1) + kd * x(2) + ki * x(3); %PID Controller

    %Restricting the output of controller
    if u(k) >= 10
        u(k) = 10;
    end

    if u(k) <= -10
        u(k) = -10;
    end

    %Linear model
    y(k) = -den(2) * y_1 - den(3) * y_2 - den(4) * y_3 + num(1) * u(k) + num(2) * u_1 + num(3) * u_2 + num(4) * u_3;
    error(k) = r(k) - y(k);

    %----------Return of parameters------------%
    u_3 = u_2; u_2 = u_1; u_1 = u(k);
    y_3 = y_2; y_2 = y_1; y_1 = y(k);

    x(1) = error(k); % Calculating P
    x2_1 = x(2);
    x(2) = (error(k) - error_1) / ts; % Calculating D
    x(3) = x(3) + error(k) * ts; % Calculating I

    error_1 = error(k);
end

figure(1);
plot(time, r, 'b', time, y, 'r');
xlabel('time(s)'); ylabel('r,y');
figure(2);
plot(time, r - y, 'r');
xlabel('time(s)'); ylabel('error');
