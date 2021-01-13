#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <limits>
#include <locale>
#include <iterator>
#include <algorithm>

typedef unsigned char u8;
typedef std::vector< std::vector< int > > matrix;

namespace utl {

    class PasteCharClass {
        public:
            PasteCharClass() = default;

            std::string operator()() {
                std::string tmp = this->sstream.str();
                this->sstream.str( "" );
                return tmp;
            }

            template < typename T, typename... Types >
            std::string operator()( T var, Types... args ) {
                this->sstream << var;
                return this->operator()( args... ) ;
            }

        private:
            std::stringstream sstream;
    };

    PasteCharClass pasteChr;

    template< class chars, class traits >
    std::basic_ostream< chars, traits >& base16( std::basic_ostream< chars, traits >& os ) {
        os << std::setfill( '0' ) << std::setw( 2 ) << std::right << std::hex;
        return os;
    }

    template< class chars, class traits >
    std::basic_ostream< chars, traits >& base10( std::basic_ostream< chars, traits >& os ) {
        os << std::setfill( ' ' ) << std::setw( 0 ) << std::left << std::dec;
        return os;
    }

    template< typename T, size_t size = 32 >
    void arrCopy( T source[ size ], T destination[ size ] ) {
        std::copy( source, source + size, destination );
    }

    template< typename T, typename ... Args, size_t size = 32 >
    void arrCopy( T source[ size ], T destination[ size ], Args... args ) {
        std::copy( source, source + size, destination );
        arrCopy( source, args... );
    }

    std::string pasteVec( std::vector< int >& vector ) {
        std::stringstream vector_string;
        const char* del = ",";
        vector_string << '{';
        if( !vector.empty() ) {
            std::copy( vector.begin(), vector.end() - 1, std::ostream_iterator< int >( vector_string, del ) );
            vector_string << vector.back();
        }
        vector_string << '}';
        return vector_string.str();
    }

    std::string pasteMat( matrix& matrix ) {
        std::stringstream matrix_string;
        for( size_t i = 0; i < matrix.size(); i++ ) {
            matrix_string << pasteVec( matrix[ i ] ) << ',' << std::endl;
        }
        return matrix_string.str();
    }

    std::string pasteArr( u8* array, size_t length = 32 ) {
        std::stringstream array_string;
        array_string << "0x" << ' ';
        for( size_t i = 0; i < length; i++ ) {
            array_string << base16 << ( int )array[ i ] << ' ';
        }
        return array_string.str();
    }

    std::string pasteArrChr( u8* array, size_t length = 32 ) {
        std::stringstream array_string;
        for( size_t i = 0; i < length; i++ ) {
            array_string << ( char )array[ i ];
        }
        return array_string.str();
    }


    std::string pasteArr( bool* array, int size = 8 ) {
        std::stringstream binary_string;
        for( size_t i = size - 1; ; --i ) {
            binary_string << array[ i ];
            if( !i ) break;
        }
        return binary_string.str();
    }

    bool* toBin( u8 var ) {
        bool* binary = new bool[ 8 ];
        for( int n = 0; n < 8; ++n )
            binary[ n ] = ( var >> n ) & 1;
        return binary;
    }

    void printBin( u8& var ) {
        std::cout << std::bitset< 8 >( ( int )var ).to_string() << std::endl;
    }

    template< class ... Args >
    void printBin( u8& var, Args... args ) {
        std::cout << std::bitset< 8 >( ( int )var ).to_string() << std::endl;
        printBin( args... );
    }

};
