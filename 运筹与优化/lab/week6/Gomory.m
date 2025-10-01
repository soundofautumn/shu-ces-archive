function [xstar, fxstar, iter] = Gomory(A, b, c)
    % 初始化
    [~, n] = size(A);
    iter = 0;
    maxIter = 100;
    options = optimoptions('linprog', 'Display', 'off');

    % 初始LP求解
    [x, fx] = linprog(-c, [], [], A, b, zeros(n, 1), [], options);

    if isempty(x)
        xstar = []; fxstar = Inf;
        return;
    end

    fx = -fx; % linprog求最小值，需要转换

    % 当前问题约束
    A_cur = A;
    b_cur = b;

    while iter < maxIter
        iter = iter + 1;

        % 检查整数可行性
        if all(abs(round(x) - x) < 1e-3)
            xstar = x;
            fxstar = fx;
            return;
        end

        % 找到分数解
        [~, idx] = max(abs(round(x) - x));

        % 生成Gomory割约束
        f = x(idx) - floor(x(idx));

        if f > 1e-10
            % 构造新约束 sum(a_i*x_i) <= floor(b)
            A_new = zeros(1, n);
            A_new(idx) = 1;
            b_new = floor(x(idx));

            % 添加新约束
            A_cur = [A_cur; A_new];
            b_cur = [b_cur; b_new];

            % 求解新的LP问题
            [x, fx] = linprog(-c, [], [], A_cur, b_cur, zeros(n, 1), [], options);

            if isempty(x)
                xstar = []; fxstar = Inf;
                return;
            end

            fx = -fx;
        end

    end

end
