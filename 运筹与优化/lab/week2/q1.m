A = [2, 1, 1, 0, 0;
     1, 1, 0, 1, 0;
     0, 1, 0, 0, 1];
b = [10; 8; 7];

[xs, Bs, x_num] = BFS(A, b);

disp('基本可行解 (xs):');
disp(xs);
disp('基本可行解的数量:');
disp(x_num);