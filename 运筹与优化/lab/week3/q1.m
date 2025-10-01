clear;

A = [2 -3 2 1 0;
     1/3 1 5 0 1];
b = [15; 20];
c = [1; 2; 1; 0; 0];

[x_opt, fx_opt, iter] = Simplex_eye(A, b, c);

fprintf('最优解: x = [%f, %f, %f, %f, %f]\n', x_opt);
fprintf('最优值: Z = %f\n', fx_opt);
fprintf('迭代次数: %d\n', iter);
