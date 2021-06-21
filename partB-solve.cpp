#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include "utils.hpp"

int diffusionValue(int i, int j, matrix unused)
{
    return (utl::diffusion[i] >> j) & 1;
}

int matrixValue(int i, int j, matrix inverse)
{
    return inverse[i][j];
}

int zeroValue(int i, int j, matrix unused)
{
    return 0;
}

// Print equation system for given function
void printEquationSystem(int (*getValue)(int, int, matrix), matrix inverse = {})
{
    std::vector<int> con1, con2;
    int sum1 = 0, sum2 = 0;
    char del = '^';
    bool init = false;
    // Print all equations from the matrix
    for(u8 j = 0; j < 32; j++)
    {
        sum1 = 0; sum2 = 0;
        // For what index values are drawn
        std::cout << "input" << '[' << utl::base10 << (int) j << ']' << ' ' << '=' << ' ';
        for(u8 k = 0; k < 32; ++k)
	{
            if(getValue(j, k, inverse))
	    {
                // From which confusion is drawn
                if(!(k % 2))
		{
                    ++sum1;
                    std::cout << (init ? (utl::pasteChr(' ', del, ' ')) : std::string(""))
                    << "cA[" << utl::base10 << (int) k << ']';
                }
		else
		{
                    ++sum2;
                    std::cout << (init ? (utl::pasteChr(' ', del, ' ')) : std::string(""))
                    << "cB[" << utl::base10 << (int) k << ']';
                }
                init = true;
            }
        }
        init = false;
        std::cout << ';' << std::endl;
        // Conclusion to dertermine amount of XOR operations
        // for each confusion for each index value
        con1.push_back(sum1);
        con2.push_back(sum2);
    }
    // Print sum of XOR operations for each confusion per row
    for(size_t i = 0; i < con1.size(); i++)
    {
      if(!(i % 4) && (i > 0))
	      std::cout << std::endl;
      std::cout << '{' << utl::base10 << i << ' ' << "cA:" << ' ' << con1[i] << ' '
      << "cB:" << ' ' << con2[i] << '}' << ',' << ' ';
    }
    std::cout << std::endl;
}

matrix inverseDiffusion(u32 diffusion[32])
{
    matrix gaussian, iterative, irregular;
    utl::fillMatrix(gaussian, diffusionValue);
    utl::fillMatrix(iterative, zeroValue);
    utl::fillMatrix(irregular, zeroValue);

    // Original which can also be deduced by the draw rules
    std::cout << utl::pasteMat(gaussian) << std::endl;

    // Elimination https://en.wikipedia.org/wiki/Gaussian_elimination
    for(size_t i = 0; i < gaussian.size() - 1; i++)
    {
	for(size_t j = i + 1; (j < gaussian.size()) && (gaussian[i][i] == 0); ++j)
	{
            gaussian[i] = utl::vectorXor(gaussian[i], gaussian[j], gaussian[i], gaussian[j][i]);
            irregular[i + 1][j] = gaussian[j][i];
	}
	for(size_t j = i + 1; j < gaussian.size(); j++)
	{
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

int main()
{
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
