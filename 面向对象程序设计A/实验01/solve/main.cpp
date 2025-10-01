#include <iostream>
#include "Solver.h"

using namespace std;


template<typename Solver>
void test(Solver solver) {
    double a[][3] = {{1, 2, -3},
                     {1, 2, 1},
                     {1, 2, 3}};
    int n = sizeof(a) / sizeof(*a);
    for (int i = 0; i < n; ++i) {
        auto result = solver->solve(a[i][0], a[i][1], a[i][2]);
        auto f = [a, i](double x) -> double { return a[i][0] * x * x + a[i][1] * x + a[i][2]; };
        cout << "  x1 = " << result.first << (f(result.first) < EPSILON ? " is a root" : " is not a root")
             << ", x2 = " << result.second << (f(result.second) < EPSILON ? " is a root" : " is not a root")
             << endl;
    }
}

int main() {
    cout << "一元二次方程求解" << endl;
    test(new RootFormula());
    cout << "二分法求解" << endl;
    test(new Dichotomy());
    cout << "牛顿法求解" << endl;
    test(new Newton());
}