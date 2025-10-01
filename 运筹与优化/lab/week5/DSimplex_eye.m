function [x_opt, fx_opt, iter] = DSimplex_eye(A, b, c)
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

    while (true && iter < 1000)
        iter = iter + 1; % 迭代次数加一
        x = zeros(n, 1);
        x(basic_indices) = b;

        if ~any(b < 0)
            break
        end

        index = find(b < 0);

        for i = 1:numel(index)

            if all(A(index(i), :) >= 0) %在b<0的元素,所对应行所有元素都大于0
                error('无可行解');
            end

        end

        s = zeros(1, n);
        % 检验数
        s(nonbasic_indices) = c(nonbasic_indices)' - c(basic_indices)' * A(:, nonbasic_indices);

        [~, q] = min(b);
        % 出基变量
        r = basic_indices(q);
        d = s ./ A(q, :);
        d(d >= 0) = -inf;
        % 入基变量
        [~, k] = max(d);

        % 更新基变量和非基变量索引
        basic_indices(basic_indices == r) = k;
        nonbasic_indices(nonbasic_indices == k) = r;

        % 更新基变量矩阵和非基变量矩阵
        A(:, nonbasic_indices) = A(:, basic_indices) \ A(:, nonbasic_indices);
        b = A(:, basic_indices) \ b;
        A(:, basic_indices) = eye(m);

    end

    x_opt = x;
    fx_opt = c' * x;

end
