function [xstar, fxstar, iter] = penalty(penalty_func, constraints, x0, epsilon)
    % 参数初始化
    max_iter = 500;      % 最大迭代次数
    sigma = 1;           % 初始惩罚因子
    c = 10;              % 惩罚因子增长系数
    iter = 0;            % 迭代计数器
    x = x0;              % 初始迭代点
    
    % 外层循环：更新惩罚因子
    while iter < max_iter
        % 构造当前惩罚函数（含不等式和等式约束）
        F = @(x) penalty_func(x) + sigma * (...
            sum( max(0, -constraints.ineq(x)).^2 ) + ...  % 不等式惩罚项
            sum( constraints.eq(x).^2 ) );                 % 等式惩罚项
        
        % 求解无约束优化问题（使用fminunc）
        options = optimoptions('fminunc', 'Display', 'off', 'Algorithm', 'quasi-newton');
        [x_new, ~] = fminunc(F, x, options);
        
        % 计算约束违反度
        violation = norm([max(0, -constraints.ineq(x_new)), constraints.eq(x_new)], 'inf');
        
        % 判断终止条件
        if violation <= epsilon
            xstar = x_new;
            fxstar = penalty_func(x_new);
            return;
        end
        
        % 更新参数
        sigma = sigma * c;    % 增大惩罚因子
        x = x_new;            % 更新迭代点
        iter = iter + 1;
    end
    
    % 超过最大迭代仍未收敛
    xstar = x_new;
    fxstar = penalty_func(x_new);
    warning('未在%d次迭代内收敛', max_iter);
end