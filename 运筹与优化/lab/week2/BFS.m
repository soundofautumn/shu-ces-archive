function [xs, Bs, x_num] = BFS(A, b)
    % BFS: 计算线性规划问题的基本可行解（Basic Feasible Solutions, BFS）
    % max z = c^T x
    % s.t. Ax = b, x >= 0
    % 输入参数：
    %   A - 系数矩阵 (m x n)
    %   b - 等式右侧向量 (m x 1，要求 b >= 0)
    % 输出参数：
    %   xs - 存储所有基本可行解的矩阵（每列是一个 BFS）
    %   Bs - 存储每个 BFS 对应的基矩阵的单元格数组
    %   x_num - 基本可行解的总数

    [m, n] = size(A); % m 为方程个数，n 为变量个数

    if rank(A) ~= m
        error('矩阵 A 的秩不等于方程个数，不能求解！');
    end

    if length(b) ~= m
        error('向量 b 的维度必须与矩阵 A 的行数一致！');
    end

    % 生成所有可能的基本变量组合
    combinations = nchoosek(1:n, m); % 从 n 个变量中选择 m 个变量的所有组合
    num_combinations = size(combinations, 1); % 计算组合的总数

    xs = []; % 用于存储基本可行解
    Bs = {}; % 用于存储基矩阵
    x_num = 0; % 用于计数基本可行解的数量

    % 遍历每一种变量组合
    for i = 1:num_combinations
        basic_vars = combinations(i, :); % 当前组合中的基变量

        % 构造基矩阵 B
        B = A(:, basic_vars);

        if rank(B) == m % 检查基矩阵 B 是否满秩
            % 解方程 Bx_b = b
            x_b = B \ b;

            % 检查解是否满足非负性条件
            if all(x_b >= 0)
                % 构造完整的解向量 x
                x = zeros(n, 1);
                x(basic_vars) = x_b; % 将基本变量的值赋给 x

                % 存储基本可行解和对应的基矩阵
                xs = [xs, x]; % 将解向量作为列添加到 xs 中
                Bs{end + 1} = B; % 将基矩阵存入 Bs 中
                x_num = x_num + 1; % 基本可行解计数加 1
            end

        end

    end

end
