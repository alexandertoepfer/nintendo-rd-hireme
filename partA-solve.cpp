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
 * Invert the confusion array look-up with given bounds. (0 < start < end)
 *
 * @param confusion The array which maps f(a) -> b to inverse f^-1(b) -> a.
 * @param start The lower bound from which the inversion begins.
 * @param end The upper bound which marks the last index of inversable entry.
 * @param optimize Flag for removing unwanted values which are part of a binary field.
 *                 (this is explored in depth at part C, not yet required)
 */
void inverseConfusion(u8 confusion[512], size_t start, size_t end, bool optimize = false) {
    std::unique_ptr<std::vector<int>[]> confusion_inverse =
    std::make_unique<std::vector<int>[]>(end - start);
    // Find matches within the confusion box and
    // mirror them inside confusion_inverse
    for(size_t i = 0; i < (end - start); i++)
        for(size_t j = start; j < end; j++)
            if(i == confusion[j])
                confusion_inverse[i].push_back(j - start);
    // Optimization to remove values outside the binary field as well as
    // choose values to stay within the field when multiple options
    if(optimize) {
        for(size_t i = 0; i < (end - start); i++) {
            for(int& val : confusion_inverse[i])
                if(utl::toBin((u8) val)[1] == utl::toBin((u8) val)[3])
                    val = -1;
            confusion_inverse[i].erase(
                std::remove(confusion_inverse[i].begin(), confusion_inverse[i].end(), -1),
                confusion_inverse[i].end()
            );
        }
    }
    // Find the end of vector array, in case entries were removed
    size_t new_end = 0;
    for(int i = (end - start) - 1; i > 0; i--) {
        if(!confusion_inverse[i].empty()) {
            new_end = i + 1;
            break;
        }
    }
    // Print generated reverse lookup once (inserted at utils.hpp)
    for(size_t i = 0; i < new_end; i++) {
        if(!(i % 8))
            std::cout << std::endl;
        std::cout << utl::pasteVec(confusion_inverse[i]) << ',';
    }
    std::cout << std::endl;
}

int main() {
    // Normal reverse lookups bound to ranges
    inverseConfusion(utl::confusion, 0, 256);
    std::cout << std::endl;
    inverseConfusion(utl::confusion, 256, 512);
    std::cout << std::endl;

    // Optimized normal reverse lookups
    inverseConfusion(utl::confusion, 0, 256, true);
    std::cout << std::endl;
    inverseConfusion(utl::confusion, 256, 512, true);
    std::cout << std::endl;
    return 0;
}
