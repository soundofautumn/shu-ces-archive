function [xstar, fxstar, iter] = SteepDescent(f_name, x0, eps)
    xk = x0;
    iter = 0;
    max_iterations = 1000;

    while iter < max_iterations
        [~, gk] = feval(f_name, xk);

        if norm(gk) <= eps
            break;
        end

        dk = -gk;
        alpha_k = GoldenSectionSearch(f_name, xk, dk, eps);
        xk_new = xk + alpha_k * dk;

        if norm(xk_new - xk) <= eps
            xk = xk_new;
            break;
        end

        xk = xk_new;
        iter = iter + 1;
    end

    xstar = xk;
    fxstar = feval(f_name, xstar);
    fxstar = fxstar(1);
end

function [a, b] = find_initial_interval(f_name, xk, dk, eps)
    a0 = 0;
    h0 = 0.1;
    a_prev = a0;
    [f_prev, ~] = feval(f_name, xk + a_prev * dk);
    a_current = a_prev + h0;
    iter = 1;
    max_iter = 10000;

    while iter <= max_iter
        [f_current, ~] = feval(f_name, xk + a_current * dk);

        if f_current > f_prev && abs(f_current - f_prev) > eps
            b = a_current;
            a = a0;
            return;
        else
            a_prev = a_current;
            f_prev = f_current;
            a_current = a_prev + h0;
            iter = iter + 1;
        end

    end

    error('Exceeded maximum iterations in finding initial interval');
end

function alpha = GoldenSectionSearch(f_name, xk, dk, eps)
    [a, b] = find_initial_interval(f_name, xk, dk, eps);
    tolerance = 1e-6;
    rho = (sqrt(5) - 1) / 2;
    c = a + (1 - rho) * (b - a);
    d = a + rho * (b - a);
    [fc, ~] = feval(f_name, xk + c * dk);
    [fd, ~] = feval(f_name, xk + d * dk);

    while (b - a) > tolerance

        if fc < fd
            b = d;
            d = c;
            fd = fc;
            c = a + (1 - rho) * (b - a);
            [fc, ~] = feval(f_name, xk + c * dk);
        else
            a = c;
            c = d;
            fc = fd;
            d = a + rho * (b - a);
            [fd, ~] = feval(f_name, xk + d * dk);
        end

    end

    alpha = (a + b) / 2;
end
