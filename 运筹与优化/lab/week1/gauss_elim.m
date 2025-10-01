function x = gauss_elim(A, b)
    % 高斯消元法求解 Ax = b
    % 输入:
    % A - 系数矩阵
    % b - 常数向量
    % 输出:
    % x - 解向量

    [m, n] = size(A);

    if m ~= n
        error('矩阵 A 必须是方阵');
    end

    Ab = [A b]; % 增广矩阵

    % 前向消元过程
    for i = 1:n
        % 选主元并交换行
        [~, maxRow] = max(abs(Ab(i:n, i)));
        maxRow = maxRow + i - 1;

        if maxRow ~= i
            % 交换第 i 行和主元所在行
            Ab([i, maxRow], :) = Ab([maxRow, i], :);
        end

        % 消元
        for j = i + 1:n
            factor = Ab(j, i) / Ab(i, i);
            Ab(j, i:end) = Ab(j, i:end) - factor * Ab(i, i:end);
        end

    end

    % 回代求解
    x = zeros(n, 1); % 初始化解向量

    for i = n:-1:1
        x(i) = (Ab(i, end) - Ab(i, i + 1:n) * x(i + 1:n)) / Ab(i, i);
    end

end
