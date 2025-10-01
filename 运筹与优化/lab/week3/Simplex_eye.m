function [x_opt, fx_opt, iter] = Simplex_eye(A, b, c)
    % 初始化变量
    [m, n] = size(A); % m: 约束数量，n: 变量数量
    iter = 0; % 迭代计数器

    % 找到基变量（对应单位矩阵的列）
    basic_indices = []; % 基本变量的索引集合

    for j = 1:n

        if isequal(A(:, j:j + m - 1), eye(m))
            basic_indices = j:j + m - 1;
            break;
        end

    end

    % 非基变量的索引集合
    nonbasic_indices = setdiff(1:n, basic_indices);

    % 开始单纯形法的迭代
    while (true && iter < 1000)
        iter = iter + 1; % 迭代次数加一

        % 计算检验数
        s = zeros(1, n);
        % 检验数
        s(nonbasic_indices) = c(nonbasic_indices)' - c(basic_indices)' * A(:, nonbasic_indices);

        if all(s <= 0)
            break; % 所有检验数都小于等于0，找到最优解
        end

        [~, k] = max(s); % 选取最大检验数对应的非基变量索引

        d = b ./ A(:, k); % 计算比值
        d(d <= 0) = inf; % 将非正数值替换为无穷大
        [~, l] = min(d); % 选取最小比值对应的基变量索引
        l = basic_indices(l);

        % 更新基变量和非基变量索引
        basic_indices(basic_indices == l) = k;
        nonbasic_indices(nonbasic_indices == k) = l;

        % 更新基变量矩阵和非基变量矩阵
        A(:, nonbasic_indices) = A(:, basic_indices) \ A(:, nonbasic_indices);
        b = A(:, basic_indices) \ b;
        A(:, basic_indices) = eye(m);
    end

    % 输出最优解
    x = zeros(n, 1);
    x(basic_indices) = b;
    fx_opt = c' * x;
    x_opt = x;
end
