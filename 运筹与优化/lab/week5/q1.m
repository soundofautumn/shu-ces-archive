clear;

A = [-1 -2 -1 1 0;
     -2 1 -3 0 1];
b = [-3 -4]';
c = [-2 -3 -4 0 0]';

[x_opt, fx_opt, iter] = DSimplex_eye(A, b, c);

fprintf('最优解: x = [%f, %f, %f, %f, %f]\n', x_opt);
fprintf('最优值: Z = %f\n', fx_opt);
fprintf('迭代次数: %d\n', iter);