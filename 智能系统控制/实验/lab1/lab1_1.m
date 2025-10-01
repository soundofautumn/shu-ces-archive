% 开环控制

Ra = 1; % 电阻
Km = 10; % 电机常数
J = 2; % 转动惯量
b = 0.5; % 摩擦系数
Kb = 0.1; % 反电动势常数

% 输出
output = tf(1, [J, b]);

% 电动势
electric = tf(Km / Ra, 1);

% 反电动势
anti_electric = tf(Kb, 1);

sys_o = -feedback(output, series(electric, anti_electric));

[yo, T] = step(sys_o);

% plot(T, yo)
% title('Open-loop Disturbance Step Response')
% xlabel('Time (sec)')
% ylabel('\omega_o (rad/sec)')
% grid

% 到达稳态的时间
T(length(T))
% 最终稳态误差 - 输出yc的最后一个值
yo(length(T))
