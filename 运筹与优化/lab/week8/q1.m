[xstar, fxstar, iter] = SteepDescent(@Myexam1, [1, 1]', 1e-3);

fprintf('最优解: x = [%f, %f]\n', xstar);
fprintf('最优值: Z = %f\n', fxstar);
fprintf('迭代次数: %d\n', iter);