A = [-1 3 1 0;
     7 1 0 1];
b = [6 35]';
c = [7 9 0 0]';

[xstar, fxstar, iter] = Gomory(A, b, c);
fprintf('最优解: x = [%f, %f, %f, %f]\n', xstar);
fprintf('最优值: Z = %f\n', fxstar);
fprintf('迭代次数: %d\n', iter);
