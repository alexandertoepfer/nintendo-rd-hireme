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

u8 input[ 32 ] = {
    0x66,0xd5,0x4e,0x28,0x5f,0xff,0x6b,0x53,0xac,0x3b,0x34,0x14,0xb5,0x3c,0xb2,0xc6,
    0xa4,0x85,0x1e,0x0d,0x86,0xc7,0x4f,0xba,0x75,0x5e,0xcb,0xc3,0x6e,0x48,0x79,0x8f
};

/* Forward */
void partA( u8 input[ 32 ], u8 output[ 32 ], u8 confusion[ 512 ] ) {
    for( u8 j = 0; j < 32; j++ ) {
        // The full confusion isn't made use of
        output[ j ] = confusion[ input[ j ] ];
    }
    utl::arrZero( input );
}

void partB( u8 input[ 32 ], u8 output[ 32 ], u32 diffusion[ 32 ] ) {
    utl::arrZero( output );
    for( u8 j = 0; j < 32; j++ ) {
        for( u8 k = 0; k < 32; k++ ) {
            output[ j ] = output[ j ] ^ input[ k ] * ( ( diffusion[ j ] >> k ) & 1 );
        }
    }
    utl::arrZero( input );
}

void partC( u8 input[ 32 ], u8 output[ 32 ], u8 confusion[ 512 ] ) {
    for( u8 i = 0; i < 16; i++ ) {
        // Second parameter encloses range 256, 512
        output[ i ] = confusion[ input[ i * 2 ] ] ^ confusion[ input[ i * 2 + 1 ] + 256 ];
    }
    utl::arrZero( input );
}

void forwardAsParts( u8 input[ 32 ], u8 output[ 32 ], u8 confusion[ 512 ], u32 diffusion[ 32 ] ) {
    partA( input, output, confusion );
    partB( output, input, diffusion );
    partC( input, output, confusion );
}

void forward( u8 input[ 32 ], u8 output[ 32 ], u8 confusion[ 512 ], u32 diffusion[ 32 ] ) {
    // Rounds
    for( u32 i = 0; i < 256; i++ ) {
        // part A: S-box
        for( u8 j = 0; j < 32; j++ ) {
            output[ j ] = utl::confusion[ input[ j ] ];
            input[ j ] = 0;
        }
        // part B: 32x32 Matrix
        for( u8 j = 0; j < 32; j++ ) {
            for( u8 k = 0; k < 32; k++ ) {
                input[ j ] = input[ j ] ^ output[ k ] * ( ( utl::diffusion[ j ] >> k ) & 1 );
            }
        }
    }
    // part C: Odd-Even-Merge
    for( u8 i = 0; i < 16; i++ )
        output[ i ] = utl::confusion[ input[ i * 2 ] ] ^ utl::confusion[ input[ i * 2 + 1 ] + 256 ];
}

/* Reverse */
void partAReverse( u8 input[ 32 ], u8 output[ 32 ] ) {
    std::vector< int > tmp;
    for( u8 j = 0; j < 32; j++ ) {
        tmp = utl::confusion_reverse256A_opt[ input[ j ] ];
        if( !tmp.empty() ) {
            // Honestly i can't be bothered building 8923549253 strings
            // when all we need is just to find one anyway
            output[ j ] = tmp[ 0 ];
        } else {
            std::cout << utl::base16 << ( int )input[ j ] << ' ' << "at"
            << ' ' << utl::base10 << ( int )j << ' ' << "is not reversible!" << std::endl;
        }
    }
}

void partBReverse( u8 input[ 32 ], matrix& iterative, matrix& irregular, matrix& eliminated ) {
    size_t begin = -1;
    for( size_t i = 0; i < iterative.size() - 1; i++ ) {
        begin = i + 1;
        for( size_t j = i + 1; j < iterative.size(); j++ ) {
            if( j == begin ) {
                for( size_t k = 0; k < irregular[ i + 1 ].size(); k++ )
                    input[ i ] = input[ i ] ^ ( input[ k ] * irregular[ i + 1 ][ k ] );
            }
            input[ j ] = input[ j ] ^ ( input[ i ] * iterative[ i ][ j ] );
        }
    }
    for( int i = eliminated.size() - 1; i >= 0; i-- )
        for( size_t j = i + 1; j < eliminated.size(); j++ )
            input[ i ] = input[ i ] ^ ( input[ j ] * eliminated[ i ][ j ] );
}

void partCReverse( u8 input[ 32 ], u8 output[ 32 ] ) {
    int matched = 0;
    bool next = false;
    for( int h = 0; h < 16; h++ ) {
        for( int i = 0; i < 16; i++ ) {
            for( int j = 0; j < 16; j++ ) {
                if( input[ h ] == ( utl::confusion[ ( int )utl::safe256A_0110[ i ] ] ^ utl::confusion[ ( int )( utl::safe256A_0110[ j ] ) + 256 ] ) ) {
                    output[ h * 2 ] = utl::safe256A_0110[ i ];
                    output[ h * 2 + 1 ] = utl::safe256A_0110[ j ];
                    ++matched;
                    next = true;
                    break;
                }
            }
            if( next ) { next = false; break; }
        }
    }
    if( matched < 16 ) {
        std::cout << "Couldn't find XOR tuples for all inputs!" << std::endl;
    }
    utl::arrZero( input );
}

void backwardAsParts( u8 input[ 32 ], u8 output[ 32 ] ) {
    partCReverse( input, output );
    partBReverse( output, utl::gaussian_iterative, utl::gaussian_irregular, utl::gaussian_eliminated );
    partAReverse( output, input );
}

void backward( u8 input[ 32 ], u8 output[ 32 ] ) {
    partCReverse( input, output );
    std::cout << utl::isWithin( output, utl::safe256A_0110, 16 )
    << " partCReverse: " << utl::pasteArr( output, 32 ) << std::endl;
    for( int j = 0; j < 256; j++ ) {
        partBReverse( output, utl::gaussian_iterative, utl::gaussian_irregular, utl::gaussian_eliminated );
        std::cout << utl::isWithin( output, utl::safe256A_0110, 16 )
        << " partBReverse: " << utl::pasteArr( output, 32 ) << std::endl;
        partAReverse( output, input );
        std::cout << utl::isWithin( output, utl::safe256A_0110, 16 )
        << " partAReverse: " << utl::pasteArr( input, 32 ) << std::endl;
        utl::arrCopy( input, output );
        utl::arrZero( input );
    }
}

int main() {
    // * Stage 1 * Complete
    //testA( input, output );

    // * Stage 2 * Complete
    //testB( input, output );

    // * Stage 3 * Complete
    //testC( input, output );

    // * Stage 4 * Complete
    /* Verify Integrity of forward */
    //testIntegrityForward( input );

    // * Stage 5 * Complete
    /* One round backwards */
    /*u8 outputForward[] = {
        0x72, 0x6e, 0x28, 0x70, 0x58, 0x60, 0xa8, 0x81,
        0x14, 0x50, 0x23, 0xe7, 0xe0, 0xbd, 0x07, 0x41
    };
    testBackward( outputForward );
    std::cout << std::endl;
    u8 inputForward[] = {
        0x37, 0xaa, 0x64, 0x83, 0xbe, 0xb4, 0x2a, 0x87,
        0x31, 0x4d, 0x25, 0x7a, 0xd2, 0x2f, 0xaf, 0x3b,
        0x8f, 0x85, 0x41, 0x6e, 0x16, 0xaa, 0x41, 0xe4,
        0x80, 0x6c, 0xe3, 0xd5, 0x16, 0x07, 0xac, 0x1b
    };
    testForward( inputForward );*/

    // * Stage 6 * Complete
    /* All rounds backwards */
    /*char myout[] = {'A','l','e','x',' ','T','o','e','p','f','e','r','!','!','!','\0'};
    utl::printU8Array( myout ); */

    u8 inputReverse[ 32 ] = {
        0x41, 0x6c, 0x65, 0x78, 0x20, 0x54, 0x6f, 0x65,
        0x70, 0x66, 0x65, 0x72, 0x21, 0x21, 0x21, 0x00
    };
    u8 outputReverse[ 32 ];
    backward( inputReverse, outputReverse );

    return 0;
}
