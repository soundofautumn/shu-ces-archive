//
// Created by 邱姜铭 on 2023/8/30.
//
#include "Solver.h"
#include <cmath>


std::pair<double, double> RootFormula::solve(double a, double b, double c) {
    // 求根公式求解一元二次方程
    double delta = b * b - 4 * a * c;
    if (delta < 0) {
        return std::make_pair(NAN, NAN);
    }
    double x1 = (-b + sqrt(delta)) / (2 * a);
    double x2 = (-b - sqrt(delta)) / (2 * a);
    return std::make_pair(x1, x2);
}

std::pair<double, double> Dichotomy::solve(double a, double b, double c) {
    // 二分法求解一元二次方程
    auto f = [a, b, c](double x) { return a * x * x + b * x + c; }; // lambda表达式
    double left, right;
    if (f(LEFT_BEGIN) * f(-b / (2 * a)) > 0 && f(-b / (2 * a)) * f(RIGHT_BEGIN) > 0) {
        return std::make_pair(NAN, NAN);
    }
    left = LEFT_BEGIN, right = -b / (2 * a);
    while (right - left > EPSILON) {
        double mid = (left + right) / 2;
        if (f(mid) * f(left) <= 0) {
            right = mid;
        } else {
            left = mid;
        }
    }
    double x1 = (left + right) / 2;
    left = -b / (2 * a), right = RIGHT_BEGIN;
    while (right - left > EPSILON) {
        double mid = (left + right) / 2;
        if (f(mid) * f(right) <= 0) {
            left = mid;
        } else {
            right = mid;
        }
    }
    double x2 = (left + right) / 2;
    return std::make_pair(x1, x2);

}

std::pair<double, double> Newton::solve(double a, double b, double c) {
    // 牛顿法求解一元二次方程
    auto f = [a, b, c](double x) { return a * x * x + b * x + c; };
    auto df = [a, b](double x) { return 2 * a * x + b; };
    double x = 0;
    int iteration = 0;
    while (fabs(f(x)) > EPSILON && iteration++ < MAX_ITERATION) {
        x = x - f(x) / df(x);
    }
    return std::make_pair(x, NAN);
}

