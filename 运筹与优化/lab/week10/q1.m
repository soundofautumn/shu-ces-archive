% 定义目标函数
f = @(x) (x(1) - 2) ^ 2 + (x(2) - 1) ^ 2;

% 定义约束（需转化为标准形式）
constraints.ineq = @(x) (-0.25 * x(1) ^ 2 - x(2) ^ 2 + 1);
constraints.eq = @(x) (x(1) - 2 * x(2) + 1);
[xstar, fxstar, iter] = penalty(f, constraints, [0, 0], 1e-3);

fprintf('最优解: x = [%f, %f]\n', xstar);
fprintf('最优值: Z = %f\n', fxstar);
fprintf('迭代次数: %d\n', iter);
