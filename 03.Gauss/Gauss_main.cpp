#include <iostream>
#include <exception>

#include "Gauss_solve.h"

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_matrix.csv>\n";
        return 1;
    }

    try
    {
        GaussMatrix ab = load_csv_to_matrix(argv[1]);

        GaussVector x = Gauss_solve(ab);

        GaussMatrix x_mat(x.rows(), 1);
        x_mat.col(0) = x;

        print_matrix_as_csv(std::cout, x_mat, 6);

    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
    }

    return 0;
}