% 闭环系统

Ra = 1; % 电阻
Km = 10; % 电机常数
J = 2; % 转动惯量
b = 0.5; % 摩擦系数
Kb = 0.1; % 反电动势常数
Ka = 54; % 放大器增益
Kt = 1; % 转速计增益

% 输出
output = tf(1, [J, b]);

% 电动势
electric = tf(Km / Ra, 1);

% 反电动势
anti_electric = tf(Kb, 1);

% 放大器
amplifier = tf(Ka, 1);

% 转速计
tachometer = tf(Kt, 1);

% 控制信号
control_signal = series(tachometer, amplifier);

% 闭环系统
sys_c =- feedback(output, series(parallel(control_signal, anti_electric), electric));

[yc, T] = step(sys_c);

% plot(T, yc)
% title('Closed-loop Disturbance Step Response')
% xlabel('Time (sec)')
% ylabel('\omega_c (rad/sec)')
% grid

% 到达稳态的时间
T(length(T))
% 最终稳态误差 - 输出yc的最后一个值。
yc(length(T))
