#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sstream>
#include "utils.hpp"

using namespace utl;

bool is2Pow1AndNot2Pow3(int val)
{
    return (toBin((u8) val)[1] && !toBin((u8) val)[3]);
}
bool isNot2Pow1And2Pow3(int val)
{
    return (!toBin((u8) val)[1] && toBin((u8) val)[3]);
}

void printNotReverseable()
{
    printBin(missing256AB[0], missing256AB[1], missing256AB[2], missing256AB[3],
             missing256AB[4], missing256AB[5], missing256AB[6], missing256AB[7],
             missing256AB[8], missing256AB[9], missing256AB[10], missing256AB[11],
             missing256AB[12], missing256AB[13], missing256AB[14], missing256AB[15]);
    std::cout << std::endl;
    for(int i = 0; i < 16; i++)
        std::cout << "0x" << base16 << (int) missing256AB[i] << ':' << ' ' << "0000"
        << toBin(missing256AB[i])[3] << '0'
        << toBin(missing256AB[i])[1] << '0' << std::endl;
}

void printAvoidDiffusion()
{
    // Odd number of XOR operations 3
    std::cout << "0x02:" << ' ' << pasteArr(toBin((u8) 0x02))
    << ' ' << "OK number" << std::endl;
    std::cout << "0x08:" << ' ' << pasteArr(toBin((u8) 0x08))
    << ' ' << "(XOR)" << ' ' << "OK number" << std::endl;
    std::cout << "0x05:" << ' ' << pasteArr(toBin((u8) 0x05))
    << ' ' << "(XOR)" << ' ' << "<-- Problem" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "0x0f:" << ' ' << pasteArr(toBin((u8)(0x02 ^ 0x08 ^ 0x05)))
    << std::endl << std::endl;
    std::cout << "0x05: 00000101 Needs to have either 2^1 or 2^3 set" << std::endl;
    std::cout << "          ^ ^ " << std::endl;
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
        std::cout << "0x" << base16 << (int) safe[i] << ',' << ' ';
    }
    std::cout << std::endl << base10 << "Count: " << safe.size();
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
              (toBin((u8) tmp[0])[1] == toBin((u8) tmp[0])[3])))
                break;
            lookup = (u8) tmp[0];
            if(j == 255)
                success = true;
        }
        if(success)
        {
            if(!(k % 8))
                std::cout << std::endl;
            std::cout << "0x" << base16 << (int) values[i] << ',' << ' ';
            success = false;
            ++k;
        }
    }
    std::cout << std::endl;
    std::cout << "Count: " << base10 << k << std::endl;
}

void printRestoreable(u8 input[16], u8 set1[], int size1, u8 set2[] = safe256AComplete, int size2 = 16)
{
    int matched = 0;
    bool next = false;
    for(int h = 0; h < 16; h++)
        for(int i = 0; i < size1; i++)
        {
            for(int j = 0; j < size2; j++)
            {
                if(input[h] == (confusion[(int) set1[i]] ^ confusion[(int) (set2[j]) + 256]))
                {
                    if(!(h % 4) && h > 0)
                        std::cout << std::endl;
                    std::cout << "0x" << base16 << (int) set1[i] << ',' << ' '
                    << "0x" << base16 << (int) set2[j] << ',' << ' ';
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
    std::cout << std::endl << "Characters restored: " << base10 << matched << std::endl;
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
    printValues(is2Pow1AndNot2Pow3);
    std::cout << std::endl;
    printValues(isNot2Pow1And2Pow3);
    std::cout << std::endl;

    // Which of these don't land on a hole when looked up
    // 64 Values
    std::cout << "Values not producing holes in first round" << std::endl;
    printSafeReverseLookup(v2Pow1AndNot2Pow3, confusion_reverse256A, false);
    std::cout << std::endl;
    printSafeReverseLookup(vNot2Pow1And2Pow3, confusion_reverse256A, false);
    std::cout << std::endl;

    // Which of these don't land on a hole when looked up
    // 16 Values
    std::cout << "Values never producing any holes in any round" << std::endl;
    printSafeReverseLookup(v2Pow1AndNot2Pow3, confusion_reverse256A_opt, true);
    std::cout << std::endl;
    printSafeReverseLookup(vNot2Pow1And2Pow3, confusion_reverse256A_opt, true);
    std::cout << std::endl;

    // Test whether we can restore valid XORs values to be picked
    // "Reverse me fast" as test
    u8 restoreme[] =
    {
        0x52, 0x65, 0x76, 0x65, 0x72, 0x73, 0x65, 0x20,
        0x6d, 0x65, 0x20, 0x66, 0x61, 0x73, 0x74, 0x00
    };
    printRestoreable(restoreme, safe256AComplete, 16);
    u8 testme[] =
    {
        0x28, 0x4c, 0xa7, 0xb9, 0x63, 0x19, 0xa7, 0xb9,
        0xa7, 0x52, 0x07, 0xec, 0xa7, 0xb9, 0x19, 0xf2,
        0x63, 0xec, 0xa7, 0xb9, 0x19, 0xf2, 0x7d, 0x36,
        0x63, 0x96, 0x07, 0xec, 0x52, 0x28, 0x7d, 0x07
    };
    std::cout << "All characters in subset: " << std::boolalpha << isWithin(testme, safe256AComplete, 16) << std::endl;
    return 0;
}
