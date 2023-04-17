#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>

#include "utils.hpp"

/*
 * Nintendo Research and Development Cryptography Challenge
 *
 *    ooo,    .---.
 *   o`  o   /    |\________________
 *  o`   'oooo()  | ________   _   _)
 *  `oo   o` \    |/        | | | |
 *    `ooo'   `---'         "-" |_| hjw
 * Step by step reversal of their forward hash function,
 * this solution does not require brute force to solve
 * the last step, making calculations of solutions instant.
 *
 * Author: Alexander Töpfer (https://github.com/alexandertoepfer)
 * Artwork by (https://www.asciiart.eu/)
 */

 /**
  * Set functions for fast population of matrices. (See void fillMatrix(matrix& m, ...) at utils.hpp)
  *
  * @param i The first dimension to access the row.
  * @param j The second dimension to access the column.
  * @param matrix
  */
int diffusionValue(int i, int j, matrix unused) {
    return (utl::diffusion[i] >> j) & 1;
}
int matrixValue(int i, int j, matrix inverse) {
    return inverse[i][j];
}
int zeroValue(int i, int j, matrix unused) {
    return 0;
}

/**
 * Print equation system for given matrix multiplication.
 *
 * @param getValue The first dimension to access the row.
 * @param j The second dimension to access the column.
 * @param matrix Used to find the equation system.
 */
void printEquationSystem(int (*getValue)(int, int, matrix), matrix matrix = {}) {
    std::vector<int> con1, con2;
    int sum1 = 0, sum2 = 0;
    char del = '^';
    bool init = false;
    // Print all equations from the multiplication
    for(u8 j = 0; j < 32; j++) {
        sum1 = 0; sum2 = 0;
        // For what index values are drawn
        std::cout << "input" << '[' << utl::base10 << (int) j << ']' << ' ' << '=' << ' ';
        for(u8 k = 0; k < 32; ++k) {
            if(getValue(j, k, matrix)) {
                // Whether from an odd or even index is drawn
                if(!(k % 2)) {
                    ++sum1;
                    std::cout << (init ? (utl::pasteChr(' ', del, ' ')) : std::string(""))
                    << "c1[" << utl::base10 << (int) k << ']';
                }
                else {
                    ++sum2;
                    std::cout << (init ? (utl::pasteChr(' ', del, ' ')) : std::string(""))
                    << "c2[" << utl::base10 << (int) k << ']';
                }
                init = true;
            }
        }
        init = false;
        std::cout << ';' << std::endl;
        // Conclusion to dertermine amount of XOR operations
        // for each odd and even index value
        con1.push_back(sum1);
        con2.push_back(sum2);
    }
    // Print sum of XOR operations for each odd/even value per row
    for(size_t i = 0; i < con1.size(); i++) {
      if(!(i % 4) && (i > 0))
        std::cout << std::endl;
      std::cout << '{' << utl::base10 << i << ' ' << "c1:" << ' ' << con1[i] << ' '
      << "c2:" << ' ' << con2[i] << '}' << ',' << ' ';
    }
    std::cout << std::endl;
}

/**
 * Inverse diffusion matrix multiplication by finding M^-1.
 *
 * @param diffusion The array representing 32x32 matrix.
 * @return j The second dimension to access the column.
 */
matrix inverseDiffusion(u32 diffusion[32]) {
    matrix gaussian, iterative, irregular;
    utl::fillMatrix(gaussian, diffusionValue);
    utl::fillMatrix(iterative, zeroValue);
    utl::fillMatrix(irregular, zeroValue);

    // Original which can also be deduced by the draw rules
    std::cout << utl::pasteMat(gaussian) << std::endl;

    // Elimination https://en.wikipedia.org/wiki/Gaussian_elimination
    for(size_t i = 0; i < gaussian.size() - 1; i++) {
      for(size_t j = i + 1; (j < gaussian.size()) && (gaussian[i][i] == 0); ++j) {
        gaussian[i] = utl::vectorXor(gaussian[i], gaussian[j], gaussian[i], gaussian[j][i]);
        irregular[i + 1][j] = gaussian[j][i];
      }
      for(size_t j = i + 1; j < gaussian.size(); j++) {
        iterative[i][j] = gaussian[j][i];
        gaussian[j] = utl::vectorXor(gaussian[i], gaussian[j], gaussian[j], gaussian[j][i]);
      }
    }

    // Resulting matrices used to reverse the original matrix
    // it is to be noted the original matrix is involutory
    // but equation system of this result is easier to handle
    std::cout << utl::pasteMat(iterative) << std::endl
    << utl::pasteMat(irregular) << std::endl
    << utl::pasteMat(gaussian) << std::endl;
    return gaussian;
}

int main() {
    // 32 Equations from diffusion
    printEquationSystem(diffusionValue);
    std::cout << std::endl;
    // Inverse matrix split up in different parts
    matrix inverse = inverseDiffusion(utl::diffusion);
    std::cout << std::endl;
    // 32 Equations from inverse matrix
    printEquationSystem(matrixValue, inverse);
    std::cout << std::endl;
    return 0;
}
