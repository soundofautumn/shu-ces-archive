m = 3;
n = 8;
A = 10 * rand(m, n); % 随机生成一个 m x n 矩阵
I = eye(m, m); % 生成单位矩阵
randIndex = randperm(size(A, 2));
A(:, randIndex(1:m)) = I; % 将单位矩阵插入随机列

disp(A); % 显示矩阵 A

% 检查是否包含单位矩阵
found = false;
unit_col_indices = [];

for i = 1:(n - m + 1)
    subMatrix = A(:, i:i + m - 1); % 取连续的 m 列

    if isequal(subMatrix, I)
        found = true;
        unit_col_indices = i:i + m - 1;
        break;
    end

end

if found
    fprintf('单位矩阵存在，所在列索引为：');
    disp(unit_col_indices);
else
    fprintf('单位矩阵不存在。\n');
end
