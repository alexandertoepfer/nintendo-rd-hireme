/*      __      __________ __________ ____  __. .___ _______    ____________________ ________    _____________________________ _________ _________
 *      /  \    /  \_____  \\______   \    |/ _| |   |\      \   \______   \______   \\_____  \  /  _____/\______   \_   _____//   _____//   _____/
 *      \   \/\/   //   |   \|       _/      <   |   |/   |   \   |     ___/|       _/ /   |   \/   \  ___ |       _/|    __)_ \_____  \ \_____  \
 *      \        //    |    \    |   \    |  \  |   /    |    \  |    |    |    |   \/    |    \    \_\  \|    |   \|        \/        \/        \
 *       \__/\  / \_______  /____|_  /____|__ \ |___\____|__  /  |____|    |____|_  /\_______  /\______  /|____|_  /_______  /_______  /_______  /
 *            \/          \/       \/        \/             \/                    \/         \/        \/        \/        \/        \/        \/
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

u8 confusion[512] = {
0xac,0xd1,0x25,0x94,0x1f,0xb3,0x33,0x28,0x7c,0x2b,0x17,0xbc,0xf6,0xb0,0x55,0x5d,
0x8f,0xd2,0x48,0xd4,0xd3,0x78,0x62,0x1a,0x02,0xf2,0x01,0xc9,0xaa,0xf0,0x83,0x71,
0x72,0x4b,0x6a,0xe8,0xe9,0x42,0xc0,0x53,0x63,0x66,0x13,0x4a,0xc1,0x85,0xcf,0x0c,
0x24,0x76,0xa5,0x6e,0xd7,0xa1,0xec,0xc6,0x04,0xc2,0xa2,0x5c,0x81,0x92,0x6c,0xda,
0xc6,0x86,0xba,0x4d,0x39,0xa0,0x0e,0x8c,0x8a,0xd0,0xfe,0x59,0x96,0x49,0xe6,0xea,
0x69,0x30,0x52,0x1c,0xe0,0xb2,0x05,0x9b,0x10,0x03,0xa8,0x64,0x51,0x97,0x02,0x09,
0x8e,0xad,0xf7,0x36,0x47,0xab,0xce,0x7f,0x56,0xca,0x00,0xe3,0xed,0xf1,0x38,0xd8,
0x26,0x1c,0xdc,0x35,0x91,0x43,0x2c,0x74,0xb4,0x61,0x9d,0x5e,0xe9,0x4c,0xbf,0x77,
0x16,0x1e,0x21,0x1d,0x2d,0xa9,0x95,0xb8,0xc3,0x8d,0xf8,0xdb,0x34,0xe1,0x84,0xd6,
0x0b,0x23,0x4e,0xff,0x3c,0x54,0xa7,0x78,0xa4,0x89,0x33,0x6d,0xfb,0x79,0x27,0xc4,
0xf9,0x40,0x41,0xdf,0xc5,0x82,0x93,0xdd,0xa6,0xef,0xcd,0x8d,0xa3,0xae,0x7a,0xb6,
0x2f,0xfd,0xbd,0xe5,0x98,0x66,0xf3,0x4f,0x57,0x88,0x90,0x9c,0x0a,0x50,0xe7,0x15,
0x7b,0x58,0xbc,0x07,0x68,0x3a,0x5f,0xee,0x32,0x9f,0xeb,0xcc,0x18,0x8b,0xe2,0x57,
0xb7,0x49,0x37,0xde,0xf5,0x99,0x67,0x5b,0x3b,0xbb,0x3d,0xb5,0x2d,0x19,0x2e,0x0d,
0x93,0xfc,0x7e,0x06,0x08,0xbe,0x3f,0xd9,0x2a,0x70,0x9a,0xc8,0x7d,0xd8,0x46,0x65,
0x22,0xf4,0xb9,0xa2,0x6f,0x12,0x1b,0x14,0x45,0xc7,0x87,0x31,0x60,0x29,0xf7,0x73,
0x2c,0x97,0x72,0xcd,0x89,0xa6,0x88,0x4c,0xe8,0x83,0xeb,0x59,0xca,0x50,0x3f,0x27,
0x4e,0xae,0x43,0xd5,0x6e,0xd0,0x99,0x7b,0x7c,0x40,0x0c,0x52,0x86,0xc1,0x46,0x12,
0x5a,0x28,0xa8,0xbb,0xcb,0xf0,0x11,0x95,0x26,0x0d,0x34,0x66,0x22,0x18,0x6f,0x51,
0x9b,0x3b,0xda,0xec,0x5e,0x00,0x2a,0xf5,0x8f,0x61,0xba,0x96,0xb3,0xd1,0x30,0xdc,
0x33,0x75,0xe9,0x6d,0xc8,0xa1,0x3a,0x3e,0x5f,0x9d,0xfd,0xa9,0x31,0x9f,0xaa,0x85,
0x2f,0x92,0xaf,0x67,0x78,0xa5,0xab,0x03,0x21,0x4f,0xb9,0xad,0xfe,0xf3,0x42,0xfc,
0x17,0xd7,0xee,0xa3,0xd8,0x80,0x14,0x2e,0xa0,0x47,0x55,0xc4,0xff,0xe5,0x13,0x3f,
0x81,0xb6,0x7a,0x94,0xd0,0xb5,0x54,0xbf,0x91,0xa7,0x37,0xf1,0x6b,0xc9,0x1b,0xb1,
0x3c,0xb6,0xd9,0x32,0x24,0x8d,0xf2,0x82,0xb4,0xf9,0xdb,0x7d,0x44,0xfb,0x1e,0xd4,
0xea,0x5d,0x35,0x69,0x23,0x71,0x57,0x01,0x06,0xe4,0x55,0x9a,0xa4,0x58,0x56,0xc7,
0x4a,0x8c,0x8a,0xd6,0x6a,0x49,0x70,0xc5,0x8e,0x0a,0x62,0xdc,0x29,0x4b,0x42,0x41,
0xcb,0x2b,0xb7,0xce,0x08,0xa1,0x76,0x1d,0x1a,0xb8,0xe3,0xcc,0x7e,0x48,0x20,0xe6,
0xf8,0x45,0x93,0xde,0xc3,0x63,0x0f,0xb0,0xac,0x5c,0xba,0xdf,0x07,0x77,0xe7,0x4e,
0x1f,0x28,0x10,0x6c,0x59,0xd3,0xdd,0x2d,0x65,0x39,0xb2,0x74,0x84,0x3d,0xf4,0xbd,
0xc7,0x79,0x60,0x0b,0x4d,0x33,0x36,0x25,0xbc,0xe0,0x09,0xcf,0x5b,0xe2,0x38,0x9e,
0xc0,0xef,0xd2,0x16,0x05,0xbe,0x53,0xf7,0xc2,0xc6,0xa2,0x24,0x98,0x1c,0xad,0x04
};

u32 diffusion[32] = {
0xf26cb481,0x16a5dc92,0x3c5ba924,0x79b65248,0x2fc64b18,0x615acd29,0xc3b59a42,0x976b2584,
0x6cf281b4,0xa51692dc,0x5b3c24a9,0xb6794852,0xc62f184b,0x5a6129cd,0xb5c3429a,0x6b978425,
0xb481f26c,0xdc9216a5,0xa9243c5b,0x524879b6,0x4b182fc6,0xcd29615a,0x9a42c3b5,0x2584976b,
0x81b46cf2,0x92dca516,0x24a95b3c,0x4852b679,0x184bc62f,0x29cd5a61,0x429ab5c3,0x84256b97
};

u8 input[32] = {
0x66,0xd5,0x4e,0x28,0x5f,0xff,0x6b,0x53,0xac,0x3b,0x34,0x14,0xb5,0x3c,0xb2,0xc6,
0xa4,0x85,0x1e,0x0d,0x86,0xc7,0x4f,0xba,0x75,0x5e,0xcb,0xc3,0x6e,0x48,0x79,0x8f
};

void forward( u8 input[ 32 ], u8 output[ 32 ], u8 confusion[ 512 ], u32 diffusion[ 32 ] ) {
    // Rounds
    for( u32 i = 0; i < 256; i++ ) {
        // part A: S-box
        for( u8 j = 0; j < 32; j++ ) {
            output[ j ] = confusion[ input[ j ] ];
            input[ j ] = 0;
        }
        // part B: 32x32 Matrix
        for( u8 j = 0; j < 32; j++ ) {
            for( u8 k = 0; k < 32; k++ ) {
                input[ j ] = input[ j ] ^ output[ k ] * ( ( diffusion[ j ] >> k ) & 1 );
            }
        }
    }
    // part C: Two make One
    for( u8 i = 0; i < 16; i++ )
        output[ i ] = confusion[ input[ i * 2 ] ] ^ confusion[ input[ i * 2 + 1 ] + 256 ];
}

void forwardNoRounds( u8 input[32], u8 output[32], u8 confusion[512], u32 diffusion[32] ) {
    // part A: S-box
    for( u8 j = 0; j < 32; j++ ) {
        output[ j ] = confusion[ input[ j ] ];
        input[ j ] = 0;
    }
    // part B: 32x32 Matrix
    for( u8 j = 0; j < 32; j++ )
        for( u8 k = 0; k < 32; k++ )
            input[ j ] = input[ j ] ^ output[ k ] * ( ( diffusion[ j ] >> k ) & 1 );
    // part C: Two make One
    for( u8 i = 0; i < 16; i++ )
        output[ i ] = confusion[ input[ i * 2 ] ] ^ confusion[ input[ i * 2 + 1 ] + 256 ];
}

// input 0, output mod
void partA( u8 input[32], u8 output[32], u8 confusion[512] ) {
    for( u8 j = 0; j < 32; ++j ) {
        // The full confusion isn't made use of:
        // Maximum input value 0xFF is 255
        output[ j ] = confusion[ input[ j ] ];
        input[ j ] = 0;
    }
}

void partB( u8 input[32], u8 output[32], u32 diffusion[32] ) {
    for( u8 j = 0; j < 32; ++j ) {
        output[ j ] = 0;
    }
    for( u8 j = 0; j < 32; j++ ) {
        for( u8 k = 0; k < 32; k++ ) {
            output[ j ] = output[ j ] ^ input[ k ] * ( ( diffusion[ j ] >> k ) & 1 );
        }
    }
    for( u8 j = 0; j < 32; ++j ) {
        input[ j ] = 0;
    }
}

void partC( u8 input[32], u8 output[32], u8 confusion[512] ) {
    for( u8 i = 0; i < 16; i++ ) {
        // Second parameter encloses confusion_2's range 256 -> 512
        output[ i ] = confusion[ input[ i * 2 ] ] ^ confusion[ input[ i * 2 + 1 ] + 256 ];
    }
    for( u8 j = 0; j < 32; ++j ) {
        input[ j ] = 0;
    }
}

void forwardAsParts( u8 input[32], u8 output[32], u8 confusion[512], u32 diffusion[32] ) {
    partA( input, output, confusion );
    partB( output, input, diffusion );
    partC( input, output, confusion );
}

/* Playground */
void partCNoSubstitution( u8 input[32], u8 output[32] ) {
    for( u8 i = 0; i < 16; i++ ) {
        output[ i ] = input[ i * 2 ] ^ input[ i * 2 + 1 ];
    }
}
void solveXorPairs( u8 input[32], u8 output[32] ) {
    bool next = false;
    for( int k = 0; k < 16; ++k ) {
        for( u8 i = 0; i < 256; ++i ) {
            for( u8 j = 0; j < 256; ++j ) {
                if( ( ( i ^ j ) == input[ k ] ) ) {
                    std::cout << utl::base10 << "input[" << ( int )k << ']' << ' ' << '=' << ' ';
                    std::cout << utl::base16 << ( int )input[ k ] << ' ' << '=' << ' ' << utl::base16 << ( int )i;
                    std::cout << ' ' << '^' << ' ' << utl::base16 << ( int )j << ';' << std::endl;
                    next = true;
                    break;
                }
            }
            if( next ) {
                next = false;
                break;
            }
        }
    }
}

/* Reverse */
void partAReverse( u8 input[32], u8 output[32], matrix& confusion_reverse ) {
    std::vector< int > tmp;
    for( u8 j = 0; j < 32; j++ ) {
        tmp = confusion_reverse[ input[ j ] ];
        if( !tmp.empty() ) {
            // Honestly i can't be bother building 8923549253 strings
            // when all we need is just to find one anyway
            output[ j ] = tmp[ 0 ];
        } else {
            std::cout << utl::base16 << ( int )input[ j ] << ' ' << "at"
            << ' ' << utl::base10 << ( int )j << ' ' << "is not reversible!" << std::endl;
        }
    }
}

void partBReverse( u8 input[32], std::vector< matrix >& iterative, matrix& gaussian ) {
    size_t begin = -1;
    for( size_t i = 0; i < iterative[ 0 ].size() - 1; i++ ) {
        begin = i + 1;
        for( size_t j = i + 1; j < iterative[ 0 ].size(); j++ ) {
            if( j == begin ) {
                for( size_t k = 0; k < iterative[ 1 ][ i + 1 ].size(); k++ )
                    input[ i ] = input[ i ] ^ ( input[ k ] * iterative[ 1 ][ i + 1 ][ k ] );
            }
            input[ j ] = input[ j ] ^ ( input[ i ] * iterative[ 0 ][ i ][ j ] );
        }
    }
    for( int i = gaussian.size() - 1; i >= 0; i-- )
		for( int j = i + 1; j < gaussian.size(); j++ )
            input[ i ] = input[ i ] ^ ( input[ j ] * gaussian[ i ][ j ] );
}

void partCReverse( u8 input[32], u8 output[32], std::vector< matrix >& confusion_reverse ) {
    int matched = 0;
    bool next = false;
    for( int h = 0; h < 16; ++h ) {
        for( int i = 0; i < 32; ++i ) {
            for( int j = 0; j < 32; ++j ) {
                if( ( confusion[ utl::safe01[ i ] ] ^ confusion[ ( int )( utl::safe10[ j ] ) + 256 ] ) == input[ h ] ) {
                    output[ h * 2 ] = utl::safe01[ i ];
                    output[ h * 2 + 1 ] = utl::safe10[ j ];
                    ++matched;
                    next = true;
                    break;
                    // Next h
                }
            }
            if( next ) { next = false; break; }
        }
    }
    if( matched < 16 ) {
        std::cout << "Couldn't find XOR tuples for all inputs!" << std::endl;
    }
    for( u8 j = 0; j < 32; ++j ) {
        input[ j ] = 0;
    }
}

void backwardAsParts( u8 input[32], u8 output[32] ) {
    partCReverse( input, output, utl::confusion_reverse );
    std::cout << "partCReverse: " << utl::pasteArr( output, 32 ) << std::endl;
    partBReverse( output, utl::iterative_diffusion, utl::gaussian_diffusion );
    std::cout << "partBReverse: " << utl::pasteArr( output, 32 ) << std::endl;
    partAReverse( output, input, utl::confusion_reverse[ 0 ] );
    std::cout << "partAReverse: " << utl::pasteArr( input, 32 ) << std::endl;
}

void testA( u8 input[32], u8 output[32] ) {
    std::cout << "Before Input: " << utl::pasteArr( input ) << std::endl;

    std::cout << "partA( ... )" << std::endl;
    partA( input, output, confusion );

    std::cout << "After Output: " << utl::pasteArr( output ) << std::endl;
    std::cout << "Before Input: " << utl::pasteArr( input ) << std::endl;

    std::cout << "partAReverse( ... )" << std::endl;
    partAReverse( output, input, utl::confusion_reverse[ 0 ] );

    std::cout << "After  Input: " << utl::pasteArr( input ) << std::endl;

    std::cout << "partA( ... )" << std::endl;
    partA( input, output, confusion );

    std::cout << "After  Output: " << utl::pasteArr( output ) << std::endl;

    std::cout << std::endl;
}

void testB( u8 input[32], u8 output[32] ) {
    std::cout << "Before Input: " << utl::pasteArr( input ) << std::endl;

    std::cout << "partB( ... )" << std::endl;
    partB( input, output, diffusion );

    std::cout << "After  Input: " << utl::pasteArr( input ) << std::endl;
    std::cout << "After Output: " << utl::pasteArr( output ) << std::endl;

    std::cout << "partBReverse( ... )" << std::endl;
    partBReverse( output, utl::iterative_diffusion, utl::gaussian_diffusion );

    std::cout << "After  Input: " << utl::pasteArr( output ) << std::endl;
    std::cout << std::endl;
}

void testC( u8 input[32], u8 output[32] ) {
    std::cout << "Before  Input:  " << utl::pasteArr( input, 32 ) << std::endl;

    std::cout << "partC( ... )" << std::endl;
    partC( input, output, confusion );

    std::cout << "After  Output:  " << utl::pasteArr( output, 16 ) << std::endl;

    std::cout << "partCReverse( ... )" << std::endl;
    partCReverse( output, input, utl::confusion_reverse );

    std::cout << "Restored Input: " << utl::pasteArr( input, 32 ) << std::endl;
    std::fill_n( output, 32, 0 );
    std::cout << "Reset Output:   " << utl::pasteArr( output, 32 ) << std::endl;

    std::cout << "partC( ... )" << std::endl;
    partC( input, output, confusion );

    std::cout << "After  Output:  " << utl::pasteArr( output, 16 ) << std::endl;
}

void testIntegrityForward( u8 input[ 32 ] ) {
    u8 input1[ 32 ], input2[ 32 ], output[ 32 ], output1[ 32 ], output2[ 32 ];
    utl::arrCopy( input, input1, input2 );

    std::cout << "Input:    " << utl::pasteArr( input, 32 ) << std::endl;

    std::cout << "forwardNoRounds( ... )" << std::endl;
    forwardNoRounds( input1, output1, confusion, diffusion );
    std::cout << "Result:   " << utl::pasteArr( output1, 16 ) << std::endl;

    std::cout << "forwardAsParts( ... )" << std::endl;
    forwardAsParts( input2, output2, confusion, diffusion );
    std::cout << "Result:   " << utl::pasteArr( output2, 16 ) << std::endl << std::endl;
}

void testBackward( u8 input[ 32 ] ) {
    u8 input1[ 32 ], output[ 32 ];
    utl::arrCopy( input, input1 );

    std::cout << "Input:  " << utl::pasteArr( input1, 16 ) << std::endl;

    std::cout << "backwardAsParts( ... )" << std::endl;
    backwardAsParts( input1, output );
}

int main() {
    u8 target[] = "Hire me!!!!!!!!", output[ 32 ];

    // * Stage 1 * Complete
    //testA( input, output );

    // * Stage 2 * Complete
    //testB( input, output );

    // * Stage 3 * Complete
    //testC( input, output );

    // * Stage 4 * Complete
    /* Verify Integrity of forward */
    //testIntegrityForward( input );

    // partC - YAY!
    u8 test[ 32 ] = {
        0x46, 0x59, 0x07, 0x8c, 0x82, 0x8c, 0x07, 0x0d,
        0x03, 0x88, 0x23, 0xe8, 0x07, 0x69, 0x82, 0x8c,
        0x07, 0x9d, 0x63, 0x0d, 0x82, 0x8c, 0x63, 0x8c,
        0x22, 0xad, 0x22, 0xad, 0x22, 0xad, 0x12, 0xbd
    };
    partC( test, output, confusion );
    std::cout << "Test  Output:  " << utl::pasteArrChr( output, 16 ) << std::endl;

    // * Stage 5 * NEXT
    /* One full round backwards */
    //u8 outputForward[] = { {0x72}, {0x6e}, {0x28}, {0x70}, {0x58}, {0x60}, {0xa8}, {0x81}, {0x14}, {0x50}, {0x23}, {0xe7}, {0xe0}, {0xbd}, {0x07}, {0x41} };
    //testBackward( outputForward );

    // * Stage 6 *
    // All rounds backwards

    //forward( input, output, confusion, diffusion );

    //std::cout << memcmp( output, target, 16 ); // => contact jobs(at)nerd.nintendo.com
    return 0;
}
