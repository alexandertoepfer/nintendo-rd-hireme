#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sstream>
#include "utils.hpp"

// Simplified version of missing values
// from the confusion box 0,256
u8 simplified[ 16 ] = {
    0x0f, 0x01, 0x00, 0x0e, 0x04, 0x0a, 0x0b, 0x05,
    0x00, 0x0e, 0x0f, 0x01, 0x0b, 0x05, 0x04, 0x0a
};

// Binary field spanning all 128 values which
// are expected to not be affected by diffusion
u8 values01[ 64 ] = {
    0x02, 0x03, 0x06, 0x07, 0x12, 0x13, 0x16, 0x17,
    0x22, 0x23, 0x26, 0x27, 0x32, 0x33, 0x36, 0x37,
    0x42, 0x43, 0x46, 0x47, 0x52, 0x53, 0x56, 0x57,
    0x62, 0x63, 0x66, 0x67, 0x72, 0x73, 0x76, 0x77,
    0x82, 0x83, 0x86, 0x87, 0x92, 0x93, 0x96, 0x97,
    0xa2, 0xa3, 0xa6, 0xa7, 0xb2, 0xb3, 0xb6, 0xb7,
    0xc2, 0xc3, 0xc6, 0xc7, 0xd2, 0xd3, 0xd6, 0xd7,
    0xe2, 0xe3, 0xe6, 0xe7, 0xf2, 0xf3, 0xf6, 0xf7
};

u8 values10[ 64 ] = {
    0x08, 0x09, 0x0c, 0x0d, 0x18, 0x19, 0x1c, 0x1d,
    0x28, 0x29, 0x2c, 0x2d, 0x38, 0x39, 0x3c, 0x3d,
    0x48, 0x49, 0x4c, 0x4d, 0x58, 0x59, 0x5c, 0x5d,
    0x68, 0x69, 0x6c, 0x6d, 0x78, 0x79, 0x7c, 0x7d,
    0x88, 0x89, 0x8c, 0x8d, 0x98, 0x99, 0x9c, 0x9d,
    0xa8, 0xa9, 0xac, 0xad, 0xb8, 0xb9, 0xbc, 0xbd,
    0xc8, 0xc9, 0xcc, 0xcd, 0xd8, 0xd9, 0xdc, 0xdd,
    0xe8, 0xe9, 0xec, 0xed, 0xf8, 0xf9, 0xfc, 0xfd
};

void printNotReverseable() {
    utl::printBin( simplified[ 0 ], simplified[ 1 ], simplified[ 2 ], simplified[ 3 ],
                   simplified[ 4 ], simplified[ 5 ], simplified[ 6 ], simplified[ 7 ],
                   simplified[ 8 ], simplified[ 9 ], simplified[ 10 ], simplified[ 11 ],
                   simplified[ 12 ], simplified[ 13 ], simplified[ 14 ], simplified[ 15 ] );
    std::cout << std::endl;
    for( int i = 0; i < 16; i++ )
        std::cout << "0x" << utl::base16 << ( int )simplified[ i ] << ':' << ' ' << "0000"
        << utl::toBin( simplified[ i ] )[ 3 ] << '0'
        << utl::toBin( simplified[ i ] )[ 1 ] << '0' << std::endl;
}

void printAvoidDiffusion() {
    // Odd number of XOR operations 3
    std::cout << "0x02:" << ' ' << utl::pasteArr( utl::toBin( ( u8 )( 0x02 ) ) )
    << ' ' << "OK number" << std::endl;
    std::cout << "0x08:" << ' ' << utl::pasteArr( utl::toBin( ( u8 )( 0x08 ) ) )
    << ' ' << "(XOR)" << ' ' << "OK number" << std::endl;
    std::cout << "0x05:" << ' ' << utl::pasteArr( utl::toBin( ( u8 )( 0x05 ) ) )
    << ' ' << "(XOR)" << ' ' << "<-- Problem" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "0x0f:" << ' ' << utl::pasteArr( utl::toBin( ( u8 )( 0x02 ^ 0x08 ^ 0x05 ) ) )
    << std::endl << std::endl;
    std::cout << "0x05: 00000101 Needs to have either 2^1 or 2^3 set" << std::endl;
    std::cout << "          ^ ^ " << std::endl;
}

bool is01( int val ) {
    return ( utl::toBin( ( u8 )val )[ 1 ] && !utl::toBin( ( u8 )val )[ 3 ] );
}
bool is10( int val ) {
    return ( !utl::toBin( ( u8 )val )[ 1 ] && utl::toBin( ( u8 )val )[ 3 ] );
}

void printValues( bool( *isSafe )( int ) ) {
    std::vector< u8 > safe;
    for( int i = 0; i < 256; i++ ) {
      if( isSafe( i ) ) {
        safe.push_back( ( u8 )i );
      }
    }
    for( size_t i = 0; i < safe.size(); i++ ) {
        if( !( i % 8 ) && i > 0 )
            std::cout << std::endl;
        std::cout << "0x" << utl::base16 << ( int )safe[ i ] << ',' << ' ';
    }
    std::cout << std::endl << utl::base10 << "Count: " << safe.size();
    std::cout << std::endl;
}

void printSafeReverseLookup( u8 values[ 64 ], std::vector< int >* confusion_reverse, bool enclose = false ) {
    u8 lookup;
    bool success = false;
    int k = 0;
    for( int i = 0; i < 64; i++ ) {
        lookup = values[ i ];
      for( int j = 0; j < 256; j++ ) {
          std::vector< int > tmp = confusion_reverse[ ( int )lookup ];
          if( tmp.empty() ||
            ( enclose && ( utl::toBin( ( u8 )tmp[ 0 ] )[ 1 ] ==
            utl::toBin( ( u8 )tmp[ 0 ] )[ 3 ] ) ) )
                break;
          lookup = ( u8 )tmp[ 0 ];
          if( j == 255 ) success = true;
      }
      if( success ) {
          if( !( k % 8 ) )
            std::cout << std::endl;
          std::cout << "0x" << utl::base16 << ( int )values[ i ] << ',' << ' ';
          success = false;
          ++k;
      }
    }
    std::cout << std::endl;
    std::cout << "Count: " << utl::base10 << k << std::endl;
}

void printRestoreable( u8 input[ 16 ], u8 set01[], int size01, u8 set10[] = utl::safe256A_0110, int size10 = 16 ) {
    int matched = 0;
    bool next = false;
    for( int h = 0; h < 16; h++ ) {
        for( int i = 0; i < size01; i++ ) {
            for( int j = 0; j < size10; j++ ) {
                if( input[ h ] == ( utl::confusion[ ( int )set01[ i ] ] ^
                    utl::confusion[ ( int )( set10[ j ] ) + 256 ] ) ) {
                    if( !( h % 4 ) && ( h > 0 ) )
                        std::cout << std::endl;
                    std::cout << "0x" << utl::base16 << ( int )set01[ i ] << ',' << ' '
                    << "0x" << utl::base16 << ( int )set10[ j ] << ',' << ' ';
                    ++matched;
                    next = true;
                    break;
                }
            }
            if( next ) { next = false; break; }
        }
    }
    std::cout << std::endl << "Characters restored: " << utl::base10 << matched << std::endl;
}

int main() {
    // Values to avoid in the entire process
    /*printNotReverseable();
    std::cout << std::endl;*/

    // Accomplish guaranteed lookup-able values after matrix
    /*printAvoidDiffusion();
    std::cout << std::endl;*/

    // Safe values when combined in odd XORs
    // 128 Values
    std::cout << "Values within binary field not affected by XOR" << std::endl;
    printValues( is01 );
    std::cout << std::endl;
    printValues( is10 );
    std::cout << std::endl;

    // Which of these don't land on a hole when looked up
    // 64 Values
    std::cout << "Values not producing holes in first round" << std::endl;
    printSafeReverseLookup( values01, utl::confusion_reverse256A, false );
    std::cout << std::endl;
    printSafeReverseLookup( values10, utl::confusion_reverse256A, false );
    std::cout << std::endl;

    // Which of these don't land on a hole when looked up
    // 16 Values
    std::cout << "Values never producing any holes in any round" << std::endl;
    printSafeReverseLookup( values01, utl::confusion_reverse256A_opt, true );
    std::cout << std::endl;
    printSafeReverseLookup( values10, utl::confusion_reverse256A_opt, true );
    std::cout << std::endl;

    // Test whether we can restore valid XORs values to be picked
    // "Reverse me fast" as test
    u8 restoreme[] = {
        0x52, 0x65, 0x76, 0x65, 0x72, 0x73, 0x65, 0x20,
        0x6d, 0x65, 0x20, 0x66, 0x61, 0x73, 0x74, 0x00
    };
    printRestoreable( restoreme, utl::safe256A_0110, 16 );
    u8 testme[] = {
        0x28, 0x4c, 0xa7, 0xb9, 0x63, 0x19, 0xa7, 0xb9,
        0xa7, 0x52, 0x07, 0xec, 0xa7, 0xb9, 0x19, 0xf2,
        0x63, 0xec, 0xa7, 0xb9, 0x19, 0xf2, 0x7d, 0x36,
        0x63, 0x96, 0x07, 0xec, 0x52, 0x28, 0x7d, 0x07
    };
    std::cout << "All characters in subset: " << std::boolalpha << utl::isWithin( testme, utl::safe256A_0110, 16 ) << std::endl;

    return 0;
}
