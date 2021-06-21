#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sstream>
#include "utils.hpp"

void printNotReverseable()
{
    utl::printBin(simplified[0], simplified[1], simplified[2], simplified[3],
                  simplified[4], simplified[5], simplified[6], simplified[7],
                  simplified[8], simplified[9], simplified[10], simplified[11],
                  simplified[12], simplified[13], simplified[14], simplified[15]);
    std::cout << std::endl;
    for(int i = 0; i < 16; i++)
        std::cout << "0x" << utl::base16 << (int) simplified[i] << ':' << ' ' << "0000"
        << utl::toBin(simplified[i])[3] << '0'
        << utl::toBin(simplified[i])[1] << '0' << std::endl;
}

void printAvoidDiffusion()
{
    // Odd number of XOR operations 3
    std::cout << "0x02:" << ' ' << utl::pasteArr(utl::toBin((u8) 0x02))
    << ' ' << "OK number" << std::endl;
    std::cout << "0x08:" << ' ' << utl::pasteArr(utl::toBin((u8) 0x08))
    << ' ' << "(XOR)" << ' ' << "OK number" << std::endl;
    std::cout << "0x05:" << ' ' << utl::pasteArr(utl::toBin((u8) 0x05))
    << ' ' << "(XOR)" << ' ' << "<-- Problem" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "0x0f:" << ' ' << utl::pasteArr(utl::toBin((u8)(0x02 ^ 0x08 ^ 0x05)))
    << std::endl << std::endl;
    std::cout << "0x05: 00000101 Needs to have either 2^1 or 2^3 set" << std::endl;
    std::cout << "          ^ ^ " << std::endl;
}

bool is01(int val)
{
    return (utl::toBin((u8) val)[1] && !utl::toBin((u8) val)[3]);
}
bool is10(int val)
{
    return (!utl::toBin((u8) val)[1] && utl::toBin((u8) val)[3]);
}

void printValues(bool (*isSafe)(int))
{
    std::vector<u8> safe;
    for(int i = 0; i < 256; i++)
      if(isSafe(i))
        safe.push_back((u8) i);
    for(size_t i = 0; i < safe.size(); i++)
    {
        if(!(i % 8) && i > 0)
            std::cout << std::endl;
        std::cout << "0x" << utl::base16 << (int) safe[i] << ',' << ' ';
    }
    std::cout << std::endl << utl::base10 << "Count: " << safe.size();
    std::cout << std::endl;
}

void printSafeReverseLookup(u8 values[64], std::vector<int>* confusion_reverse, bool enclose = false)
{
    u8 lookup;
    bool success = false;
    int k = 0;
    for(int i = 0; i < 64; i++)
    {
        lookup = values[i];
        for(int j = 0; j < 256; j++)
        {
            std::vector<int> tmp = confusion_reverse[(int) lookup];
            if(tmp.empty() || (enclose &&
              (utl::toBin((u8) tmp[0])[1] == utl::toBin((u8) tmp[0])[3])))
                break;
            lookup = (u8) tmp[0];
            if(j == 255)
                success = true;
        }
        if(success)
        {
            if(!(k % 8))
                std::cout << std::endl;
            std::cout << "0x" << utl::base16 << (int) values[i] << ',' << ' ';
            success = false;
            ++k;
        }
    }
    std::cout << std::endl;
    std::cout << "Count: " << utl::base10 << k << std::endl;
}

void printRestoreable(u8 input[16], u8 set01[], int size01, u8 set10[] = utl::safe256A_0110, int size10 = 16)
{
    int matched = 0;
    bool next = false;
    for(int h = 0; h < 16; h++)
        for(int i = 0; i < size01; i++)
        {
            for(int j = 0; j < size10; j++)
            {
                if(input[h] == (utl::confusion[(int) set01[i]] ^ utl::confusion[(int) (set10[j]) + 256]))
                {
                    if(!(h % 4) && h > 0)
                        std::cout << std::endl;
                    std::cout << "0x" << utl::base16 << (int) set01[i] << ',' << ' '
                    << "0x" << utl::base16 << (int) set10[j] << ',' << ' ';
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
    std::cout << std::endl << "Characters restored: " << utl::base10 << matched << std::endl;
}

int main()
{
    // Values to avoid in the entire process
    /*printNotReverseable();
    std::cout << std::endl;*/

    // Accomplish guaranteed lookup-able values after matrix
    /*printAvoidDiffusion();
    std::cout << std::endl;*/

    // Safe values when combined in odd XORs
    // 128 Values
    std::cout << "Values within binary field not affected by XOR" << std::endl;
    printValues(is01);
    std::cout << std::endl;
    printValues(is10);
    std::cout << std::endl;

    // Which of these don't land on a hole when looked up
    // 64 Values
    std::cout << "Values not producing holes in first round" << std::endl;
    printSafeReverseLookup(values01, utl::confusion_reverse256A, false);
    std::cout << std::endl;
    printSafeReverseLookup(values10, utl::confusion_reverse256A, false);
    std::cout << std::endl;

    // Which of these don't land on a hole when looked up
    // 16 Values
    std::cout << "Values never producing any holes in any round" << std::endl;
    printSafeReverseLookup(values01, utl::confusion_reverse256A_opt, true);
    std::cout << std::endl;
    printSafeReverseLookup(values10, utl::confusion_reverse256A_opt, true);
    std::cout << std::endl;

    // Test whether we can restore valid XORs values to be picked
    // "Reverse me fast" as test
    u8 restoreme[] =
    {
        0x52, 0x65, 0x76, 0x65, 0x72, 0x73, 0x65, 0x20,
        0x6d, 0x65, 0x20, 0x66, 0x61, 0x73, 0x74, 0x00
    };
    printRestoreable(restoreme, utl::safe256A_0110, 16);
    u8 testme[] =
    {
        0x28, 0x4c, 0xa7, 0xb9, 0x63, 0x19, 0xa7, 0xb9,
        0xa7, 0x52, 0x07, 0xec, 0xa7, 0xb9, 0x19, 0xf2,
        0x63, 0xec, 0xa7, 0xb9, 0x19, 0xf2, 0x7d, 0x36,
        0x63, 0x96, 0x07, 0xec, 0x52, 0x28, 0x7d, 0x07
    };
    std::cout << "All characters in subset: " << std::boolalpha << utl::isWithin(testme, utl::safe256A_0110, 16) << std::endl;
    return 0;
}
