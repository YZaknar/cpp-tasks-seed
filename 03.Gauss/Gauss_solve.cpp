#include "Gauss_solve.h"
#include <cmath>
#include <stdexcept>

GaussVector Gauss_solve(GaussMatrix &ab)
{
    Eigen::Index n = ab.rows();
    Eigen::Index cols = ab.cols();
    const double EPSILON = 1e-12;

    for (Eigen::Index i = 0; i < n; ++i)
    {
        Eigen::Index max_row = i;
        double max_val = std::abs(ab(i, i));
        for (Eigen::Index k = i + 1; k < n; ++k)
        {
            if (std::abs(ab(k, i)) > max_val)
            {
                max_val = std::abs(ab(k, i));
                max_row = k;
            }
        }

        if (max_val < EPSILON)
        {
            throw std::runtime_error("Matrix is degenerate. No unique solution.");
        }

        if (max_row != i)
        {
            ab.row(i).swap(ab.row(max_row));
        }

        for (Eigen::Index j = i + 1; j < n; ++j)
        {
            double factor = ab(j, i) / ab(i, i);
            ab.row(j) -= factor * ab.row(i);
        }
    }

    GaussVector x(n);
    for (Eigen::Index i = n - 1; i >= 0; --i)
    {
        double sum = 0.0;
        for (Eigen::Index j = i + 1; j < n; ++j)
        {
            sum += ab(i, j) * x(j);
        }
        x(i) = (ab(i, cols - 1) - sum) / ab(i, i);
    }

    return x;
}