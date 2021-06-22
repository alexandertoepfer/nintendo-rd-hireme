/*  ooo,    .---.                       ____  ____ ___  _ ____  _____  ____    ____  _     ____  _     _     _____ _      _____ _____
 *  o`  o   /    |\________________    /   _\/  __\\  \///  __\/__ __\/  _ \  /   _\/ \ /|/  _ \/ \   / \   /  __// \  /|/  __//  __/
 *  o`   'oooo()  | ________   _   _)  |  /  |  \/| \  / |  \/|  / \  | / \|  |  /  | |_||| / \|| |   | |   |  \  | |\ ||| |  _|  \
 *  `oo   o` \    |/        | | | |    |  \__|    / / /  |  __/  | |  | \_/|  |  \_ | | ||| |-||| |_/\| |_/\|  /_ | | \||| |_//|  /_
 *  `ooo'   `---'         "-" |_| hjw  \____/\_/\_\/_/   \_/     \_/  \____/  \____/\_/ \|\_/ \|\____/\____/\____\\_/  \|\____\\____\
 * Alexander
 * Töpfer
 * 2020
 */
#include <cstring>
#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <memory>
#include "utils.hpp"

void partA(u8 input[32], u8 output[32], u8 confusion[512])
{
    for(u8 j = 0; j < 32; j++)
        // The full confusion isn't made use of
        output[j] = confusion[input[j]];
    utl::arrZero(input);
}

void partB(u8 input[32], u8 output[32], u32 diffusion[32])
{
    utl::arrZero(output);
    for(u8 j = 0; j < 32; j++)
        for(u8 k = 0; k < 32; k++)
            output[j] = output[j] ^ input[k] * ((diffusion[j] >> k) & 1);
    utl::arrZero(input);
}

void partC(u8 input[32], u8 output[32], u8 confusion[512])
{
    for(u8 i = 0; i < 16; i++)
        // Second parameter encloses range 256, 512
        output[i] = confusion[input[i * 2]] ^ confusion[input[i * 2 + 1] + 256];
    utl::arrZero(input);
}

void forwardOneRound(u8 input[32], u8 output[32], u8 confusion[512], u32 diffusion[32])
{
    partA(input, output, confusion);
    partB(output, input, diffusion);
    partC(input, output, confusion);
}

void forwardVerbose(u8 input[32], u8 output[32], u8 confusion[512] = utl::confusion, u32 diffusion[32] = utl::diffusion)
{
    for(u32 i = 0; i < 256; i++)
    {
        // Part A: S-box
        for(u8 j = 0; j < 32; j++)
        {
            output[j] = utl::confusion[input[j]];
            input[j] = 0;
        }
        std::cout << "partA: " << utl::pasteArr(output, 32) << std::endl;
        // Part B: 32x32 Matrix
        for(u8 j = 0; j < 32; j++)
            for(u8 k = 0; k < 32; k++)
                input[j] = input[j] ^ output[k] * ((utl::diffusion[j] >> k) & 1);
        std::cout << "partB: " << utl::pasteArr(input, 32) << std::endl;
    }
    // Part C: Odd-Even-Merge
    for(u8 i = 0; i < 16; i++)
        output[i] = utl::confusion[input[i * 2]] ^ utl::confusion[input[i * 2 + 1] + 256];
    std::cout << "partC: " << utl::pasteArr(output, 16) << std::endl << std::endl;
}

void partAReverse(u8 input[32], u8 output[32])
{
    std::vector<int> tmp;
    for(u8 j = 0; j < 32; j++)
    {
        tmp = utl::confusion_reverse256A_opt[input[j]];
        if(!tmp.empty())
            // Honestly i can't be bothered building 8923549253 strings
            // when all we need is just to find one anyway
            output[j] = tmp[0];
        else
            std::cout << utl::base16 << (int) input[j] << ' ' << "at"
            << ' ' << utl::base10 << (int) j << ' ' << "is not reversible!" << std::endl;
    }
}

void partBReverse(u8 input[32], matrix& iterative, matrix& irregular, matrix& eliminated)
{
    size_t begin = -1;
    for(size_t i = 0; i < iterative.size() - 1; i++)
    {
        begin = i + 1;
        for(size_t j = i + 1; j < iterative.size(); j++)
        {
            if(j == begin)
                for(size_t k = 0; k < irregular[i + 1].size(); k++)
                    input[i] = input[i] ^ (input[k] * irregular[i + 1][k]);
            input[j] = input[j] ^ (input[i] * iterative[i][j]);
        }
    }
    for(int i = eliminated.size() - 1; i >= 0; i--)
        for(size_t j = i + 1; j < eliminated.size(); j++)
            input[i] = input[i] ^ (input[j] * eliminated[i][j]);
}

void partCReverse(u8 input[32], u8 output[32])
{
    int matched = 0;
    bool next = false;
    for(int h = 0; h < 16; h++)
        for(int i = 0; i < 16; i++)
        {
            for(int j = 0; j < 16; j++)
            {
                int candidate_even = utl::safe256AComplete[i], candidate_odd = utl::safe256AComplete[j];
                if(input[h] == (utl::confusion[candidate_even] ^ utl::confusion[candidate_odd + 256]))
                {
                    output[h * 2] = candidate_even;
                    output[h * 2 + 1] = candidate_odd;
                    ++matched;
                    next = true;
                    break;
                }
            }
            if(next)
            {
                next = false;
                break;
            }
        }
    if(matched < 16)
    {
        std::cout << "Couldn't find XOR tuples for all inputs!" << std::endl;
    }
    utl::arrZero(input);
}

void backwardOneRound(u8 input[32], u8 output[32])
{
    partCReverse(input, output);
    partBReverse(output, utl::gaussian_iterative, utl::gaussian_irregular, utl::gaussian_eliminated);
    partAReverse(output, input);
}

void backwardVerbose(u8 input[32], u8 output[32])
{
    partCReverse(input, output);
    std::cout << "partC^-1: " << utl::pasteArr(output, 32) << ' ' << '(' << utl::isWithin(output, utl::safe256AComplete, 16) << ')' << std::endl;
    for(int j = 0; j < 256; j++)
    {
        partBReverse(output, utl::gaussian_iterative, utl::gaussian_irregular, utl::gaussian_eliminated);
        std::cout << "partB^-1: " << utl::pasteArr(output, 32) << ' ' << '(' << utl::isWithin(output, utl::safe256AComplete, 16) << ')' << std::endl;
        partAReverse(output, input);
        std::cout << "partA^-1: " << utl::pasteArr(input, 32) << ' ' << '(' << utl::isWithin(input, utl::safe256AComplete, 16) << ')' << std::endl;
        utl::arrCopy(input, output);
        utl::arrZero(input);
    }
    std::cout << std::endl;
}

int main()
{
    // * Stage 1 * Complete
    //testA(input, output);

    // * Stage 2 * Complete
    //testB(input, output);

    // * Stage 3 * Complete
    //testC(input, output);

    // * Stage 4 * Complete
    /* Verify Integrity of forward */
    //testIntegrityForward(input);

    // * Stage 5 * Complete
    /* One round backwards */
    /*u8 outputForward[] =
    {
        ...
    };
    testBackward(outputForward);
    u8 inputForward[] =
    {
        ...
    };
    testForward(inputForward);*/

    // * Stage 6 * Complete
    /* All rounds backwards */
    /*char out[] = {'A','l','e','x',' ','T','o','e','p','f','e','r',' ',':',')','\0'};
    utl::printU8Array(out);*/

    u8 outputBackward[32] =
    {
        0x41, 0x6c, 0x65, 0x78, 0x20, 0x54, 0x6f, 0x65,
        0x70, 0x66, 0x65, 0x72, 0x20, 0x3a, 0x29, 0x00, 
    };
    u8 inputBackward[32];
    backwardVerbose(outputBackward, inputBackward);
    
    u8 inputForward[32] =
    {
        0x07, 0xf2, 0x7d, 0x07, 0x88, 0xc3, 0xec, 0x88, 0x07, 0x4c, 0xc3, 0x4c, 0x19, 0x4c, 0xc3, 0xf2,
        0xec, 0xb9, 0xb9, 0x88, 0xf2, 0x28, 0x52, 0x88, 0xb9, 0xc3, 0xa7, 0x63, 0x7d, 0x63, 0xc3, 0x63
    };
    u8 outputForward[32];
    forwardVerbose(inputForward, outputForward);
    
    // Use output in challenge to create "Alex Toepfer :)" =>
    return 0;
}
