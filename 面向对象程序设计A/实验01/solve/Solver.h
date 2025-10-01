//
// Created by 邱姜铭 on 2023/8/30.
//

#ifndef SOLVE_SOLVER_H
#define SOLVE_SOLVER_H

#include <utility>

class Solver {
public:
    virtual std::pair<double, double> solve(double a, double b, double c) = 0;
};

class RootFormula : public Solver {
public:
    std::pair<double, double> solve(double a, double b, double c) override;
};

#define EPSILON 1e-6
#define LEFT_BEGIN (-100)
#define RIGHT_BEGIN 100

class Dichotomy : public Solver {
public:
    std::pair<double, double> solve(double a, double b, double c) override;
};

#define MAX_ITERATION 1000

class Newton : public Solver {
public:
    std::pair<double, double> solve(double a, double b, double c) override;
};


#endif //SOLVE_SOLVER_H
