function [xstar, fxstar] = BranchBound(A, b, c)
    % 初始化
    xstar = [];
    fxstar = -inf;

    % 初始LP求解
    [x, fval] = linprog(-c, A, b, [], [], zeros(size(c)), [], optimoptions('linprog', 'Display', 'off'));

    if isempty(x)
        return;
    end

    % 开始分支定界
    [xstar, fxstar] = BranchBoundRecursive(A, b, c, x, -fval, -inf, []);
end

function [best_x, best_val] = BranchBoundRecursive(A, b, c, x_current, f_current, curr_best_val, curr_best_x)

    % 边界判断
    if f_current <= curr_best_val
        best_x = curr_best_x;
        best_val = curr_best_val;
        return;
    end

    % 检查整数可行性
    idx = find(abs(x_current - round(x_current)) > 1e-3);

    if isempty(idx)

        if f_current > curr_best_val
            best_val = f_current;
            best_x = x_current;
        else
            best_val = curr_best_val;
            best_x = curr_best_x;
        end

        return;
    end

    % 分支过程
    branch_var = idx(1);
    x_value = x_current(branch_var);

    % 下分支
    A_new = [A; zeros(1, size(A, 2))];
    A_new(end, branch_var) = 1;
    b_new = [b; floor(x_value)];
    [x, fval] = linprog(-c, A_new, b_new, [], [], zeros(size(c)), [], optimoptions('linprog', 'Display', 'off'));

    if ~isempty(x)
        [temp_x, temp_val] = BranchBoundRecursive(A_new, b_new, c, x, -fval, curr_best_val, curr_best_x);

        if temp_val > curr_best_val
            curr_best_val = temp_val;
            curr_best_x = temp_x;
        end

    end

    % 上分支
    A_new(end, branch_var) = -1;
    b_new(end) = -ceil(x_value);
    [x, fval] = linprog(-c, A_new, b_new, [], [], zeros(size(c)), [], optimoptions('linprog', 'Display', 'off'));

    if ~isempty(x)
        [best_x, best_val] = BranchBoundRecursive(A_new, b_new, c, x, -fval, curr_best_val, curr_best_x);
    else
        best_x = curr_best_x;
        best_val = curr_best_val;
    end

end
