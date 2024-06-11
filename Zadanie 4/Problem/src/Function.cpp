#include <cmath>

int countNextTemp(int temp, int iter, int tempN, int temp0, int maxIter)
{
    int t = temp0 / iter;
    double lambda = pow(static_cast<double>(tempN) / temp0, 1.0 / maxIter);
    return static_cast<int>(t * lambda);
}