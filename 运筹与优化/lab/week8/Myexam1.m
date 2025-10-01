function [f, g] = Myexam1(x)
    f = x(1) ^ 2 + 2 * x(2) ^ 2;
    g = [2 * x(1); 4 * x(2)];
end
