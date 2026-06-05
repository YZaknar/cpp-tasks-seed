#include <gtest/gtest.h>
#include <random>
#include "Gauss_solve.h"

TEST(GaussSolve, SimpleSystem)
{
    GaussMatrix ab(3, 4);
    ab << 2, 1, -1,  8,
    -3, -1, 2, -11,
    -2,  1, 2, -3;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 2.0, 1e-9);
    EXPECT_NEAR(x(1), 3.0, 1e-9);
    EXPECT_NEAR(x(2), -1.0, 1e-9);
}

TEST(GaussSolve, DegenerateMatrixThrows)
{
    GaussMatrix ab(2, 3);
    ab << 1, 1, 5,
    2, 2, 10;

    EXPECT_THROW(Gauss_solve(ab), std::runtime_error);
}

TEST(GaussSolve, RequiresPivoting)
{
    GaussMatrix ab(2, 3);
    ab << 0, 1, 1,
    1, 0, 2;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 2.0, 1e-9);
    EXPECT_NEAR(x(1), 1.0, 1e-9);
}

TEST(GaussSolve, LargeRandomSystem)
{
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    int n = 100;
    GaussMatrix ab(n, n + 1);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
        {
            ab(i, j) = dist(gen);
        }
        ab(i, i) += 200.0;
    }

    EXPECT_NO_THROW(
    {
        GaussVector x = Gauss_solve(ab);
    });
}