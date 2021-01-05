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

typedef unsigned char                       u8;
typedef unsigned int                        u32;
typedef std::vector< std::vector< int > >   matrix;

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
// change to generate specific string
0x66,0xd5,0x4e,0x28,0x5f,0xff,0x6b,0x53,0xac,0x3b,0x34,0x14,0xb5,0x3c,0xb2,0xc6,
0xa4,0x85,0x1e,0x0d,0x86,0xc7,0x4f,0xba,0x75,0x5e,0xcb,0xc3,0x6e,0x48,0x79,0x8f
//
};

void forward( u8 input[32], u8 output[32], u8 confusion[512], u32 diffusion[32] ) {
    // Rounds
    for( u32 i = 0; i < 256; i++ ) {
        // part A: S-box
        for( u8 j = 0; j < 32; j++ ) {
            output[ j ] = confusion[ input[ j ] ];
            input[ j ] = 0;
        }
        // part B: 32x32 Matrix
        for( u8 j = 0; j < 32; j++ )
            for( u8 k = 0; k < 32; k++ )
                input[ j ] = input[ j ] ^ output[ k ] * ( ( diffusion[ j ] >> k ) & 1 );
    }
    // part C: Two make One
    for( u8 i = 0; i < 16; i++ )
        output[ i ] = confusion[ input[ i * 2 ] ] ^ confusion[ input[ i * 2 + 1 ] + 256 ];
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

namespace utl {
    template< class chars, class traits >
    std::basic_ostream< chars, traits >& base16( std::basic_ostream< chars, traits >& os ) {
        os << std::setfill('0') << std::setw(2) << std::right << std::hex;
        return os;
    }

    template< class chars, class traits >
    std::basic_ostream< chars, traits >& base10( std::basic_ostream< chars, traits >& os ) {
        os << std::setfill(' ') << std::setw(0) << std::left << std::dec;
        return os;
    }

    std::string paste( std::vector< int >& vector ) {
        std::stringstream vector_string;
        const char* delimiter = ", ";
        vector_string << '{' << ' ';
        if( !vector.empty() ) {
            std::copy( vector.begin(), vector.end() - 1, std::ostream_iterator< int >( vector_string, delimiter ) );
            vector_string << vector.back();
        }
        vector_string << ' ' << '}';
        return vector_string.str();
    }

    std::string paste( matrix& matrix ) {
        std::stringstream matrix_string;
        for( size_t i = 0; i < matrix.size(); i++ ) {
            matrix_string << utl::paste( matrix[ i ] ) << ',' << std::endl;
        }
        return matrix_string.str();
    }

    std::string paste( u8* array, size_t length = 32 ) {
        std::stringstream array_string;
        array_string << "(hex)";
        for( int i = 0; i < length; i++ ) {
            array_string << utl::base16 << ( int )array[ i ];
        }
        return array_string.str();
    }
};

// Inverse confusion 0, 256 and 256, 512
std::vector< matrix > confusion_reverse =
{
    {
        {106},{26},{24,94},{89},{56},{86},{227},{195},
        {228},{95},{188},{144},{47},{223},{70},{},
        {88},{},{245},{42},{247},{191},{128},{10},
        {204},{221},{23},{246},{83,113},{131},{129},{4},
        {},{130},{240},{145},{48},{2},{112},{158},
        {7},{253},{232},{9},{118},{132,220},{222},{176},
        {81},{251},{200},{6,154},{140},{115},{99},{210},
        {110},{68},{197},{216},{148},{218},{},{230},
        {161},{162},{37},{117},{},{248},{238},{100},
        {18},{77,209},{43},{33},{125},{67},{146},{183},
        {189},{92},{82},{39},{149},{14},{104},{184,207},
        {193},{75},{},{215},{59},{15},{123},{198},
        {252},{121},{22},{40},{91},{239},{41,181},{214},
        {196},{80},{34},{},{62},{155},{51},{244},
        {233},{31},{32},{255},{119},{},{49},{127},
        {21,151},{157},{174},{192},{8},{236},{226},{103},
        {},{60},{165},{30},{142},{45},{65},{250},
        {185},{153},{72},{205},{71},{137,171},{96},{16},
        {186},{116},{61},{166,224},{3},{134},{76},{93},
        {180},{213},{234},{87},{187},{122},{},{201},
        {69},{53},{58,243},{172},{152},{50},{168},{150},
        {90},{133},{28},{101},{0},{97},{173},{},
        {13},{},{85},{5},{120},{219},{175},{208},
        {135},{242},{66},{217},{11,194},{178},{229},{126},
        {38},{44},{57},{136},{159},{164},{55,64},{249},
        {235},{27},{105},{},{203},{170},{102},{46},
        {73},{1},{17},{20},{19},{},{143},{52},
        {111,237},{231},{63},{139},{114},{167},{211},{163},
        {84},{141},{206},{107},{},{179},{78},{190},
        {35},{36,124},{79},{202},{54},{108},{199},{169},
        {29},{109},{25},{182},{241},{212},{12},{98,254},
        {138},{160},{},{156},{225},{177},{74},{147}
    },
    {
        {53},{151},{},{87},{255},{244},{152},{204},
        {180},{234},{169},{227},{26},{41},{},{198},
        {210},{38},{31},{110},{102},{},{243},{96},
        {45},{},{184},{126},{253},{183},{142},{208},
        {190},{88},{44},{148},{132,251},{231},{40},{15},
        {33,209},{172},{54},{177},{0},{215},{103},{80},
        {62},{76},{131},{64,229},{42},{146},{230},{122},
        {238},{217},{70},{49},{128},{221},{71},{14,111},
        {25},{175},{94,174},{18},{140},{193},{30},{105},
        {189},{165},{160},{173},{7},{228},{16,207},{89},
        {13},{47},{27},{246},{118},{106,154},{158},{150},
        {157},{11,212},{32},{236},{201},{145},{52},{72},
        {226},{57},{170},{197},{},{216},{43},{83},
        {},{147},{164},{124},{211},{67},{20},{46},
        {166},{149},{2},{},{219},{65},{182},{205},
        {84},{225},{114},{23},{24},{139},{188},{},
        {101},{112},{135},{9},{220},{79},{28},{},
        {6},{4},{162},{},{161},{133},{168},{56},
        {},{120},{81},{194},{115},{39},{59},{1},
        {252},{22},{155},{48},{},{73},{239},{77},
        {104},{69,181},{250},{99},{156},{85},{5},{121},
        {34},{75},{78},{86},{200},{91,254},{17},{82},
        {199},{127},{218},{60},{136},{117},{113,129},{178},
        {185},{90},{58,202},{35},{232},{223},{245},{119},
        {240},{29},{248},{196},{107},{167},{249},{159,224},
        {68},{125},{12},{36,176},{187},{3},{179},{235},
        {21,116},{61},{242},{213},{143},{19},{163},{97},
        {100},{130},{50},{138},{63,171},{214},{195},{203},
        {233},{},{237},{186},{153},{109},{191},{206},
        {8},{66},{144},{10},{51},{},{98},{241},
        {37},{123},{134},{93},{222},{55},{},{247},
        {192},{137},{},{141},{95},{74},{92},{108}
    }
};

// Part-reversal of diffusion
std::vector< matrix > iterative_diffusion =
{
    {
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1 },
        { 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    }
};

// Last part of diffusion reversal
matrix gaussian_diffusion = {
{ 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1 },
{ 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0 },
{ 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0 },
{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0 },
{ 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0 },
{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1 },
{ 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }
};

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
        output[ j ] = input[ j ];
        input[ j ] = 0;
    }
    for( u8 j = 0; j < 32; j++ ) {
        for( u8 k = 0; k < 32; k++ ) {
            input[ j ] = input[ j ] ^ output[ k ] * ( ( diffusion[ j ] >> k ) & 1 );
        }
    }
}

void partC( u8 input[32], u8 output[32], u8 confusion[512] ) {
    for( u8 i = 0; i < 16; i++ ) {
        // Second parameter encloses confusion_b's range 256 -> 512
        output[ i ] = confusion[ input[ i * 2 ] ] ^ confusion[ input[ i * 2 + 1 ] + 256 ];
    }
}

void partCNoSubstitution( u8 input[32], u8 output[32] ) {
    for( u8 i = 0; i < 16; i++ ) {
        output[ i ] = input[ i * 2 ] ^ input[ i * 2 + 1 ];
    }
}

void partAReverse( u8 input[32], u8 output[32], matrix& confusion_reverse ) {
    std::vector< int > tmp;
    for( u8 j = 0; j < 32; j++ ) {
        tmp = confusion_reverse[ input[ j ] ];
        if( !tmp.empty() ) {
            // Pick first value that fits
            output[ j ] = tmp[ 0 ];
        } else {
            output[ j ] = 0;
        }
    }
}

void partBReverse( u8 input[32], std::vector< matrix >& iterative, matrix& gaussian ) {
    size_t begin = -1;
    for( size_t i = 0; i < iterative[ 0 ].size() - 1; i++ ) {
        begin = i + 1;
        std::vector< int > second = iterative[ 1 ][ i + 1 ];
        for( size_t j = i + 1; j < iterative[ 0 ].size(); j++ ) {
            auto applicable = std::find( second.begin(), second.end(), 1 );
            if( ( j == begin ) && ( applicable != second.end() ) ) {
                for( size_t k = 0; k < second.size(); k++ )
                    input[ i ] = input[ i ] ^ ( input[ k ] * second[ k ] );
            }
            input[ j ] = input[ j ] ^ ( input[ i ] * iterative[ 0 ][ i ][ j ] );
        }
    }
    // Apply gaussian backwards
    for( int i = gaussian.size() - 1; i >= 0; i-- )
		for( int j = i + 1; j < gaussian.size(); j++ )
            input[ i ] = input[ i ] ^ ( input[ j ] * gaussian[ i ][ j ] );
}

void partCReverse( u8 input[32], u8 output[32], std::vector< matrix >& confusion_reverse ) {
    bool next = false;
    for( int k = 0; k < 16; ++k ) {
        for( int i = 0; i < 256; ++i ) {
            for( int j = 256; j < 512; ++j ) {
                if( input[ k ] == ( confusion[ i ] ^ confusion[ j ] ) ) {
                    std::vector< int > first = confusion_reverse[ 0 ][ confusion[ i ] ],
                    second = confusion_reverse[ 1 ][ confusion[ j ] ];
                    if( first.empty() || second.empty() ) continue;
                    output[ k * 2 ] = first[ 0 ];
                    output[ k * 2 + 1 ] = second[ 0 ];
                    next = true;
                    break;
                }
            }
            if( next ) { next = false; break; }
        }
    }
    for( u8 j = 0; j < 32; ++j ) {
        input[ j ] = 0;
    }
}

void solveXorPairs( u8 input[32], u8 output[32] ) {
    bool next = false;
    for( int k = 0; k < 16; ++k ) {
        for( u8 i = 0; i < 256; ++i ) {
            for( u8 j = 256; j < 512; ++j ) {
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

void inverseConfusion( u8 confusion[512], size_t start, size_t end ) {
    std::unique_ptr< std::vector< int >[] > confusion_inverse =
    std::make_unique< std::vector< int >[] >( end - start );

    for( size_t i = 0; i < ( end - start ); ++i ) {
        for( size_t j = start; j < end; ++j )
            if( i == confusion[ j ] )
                confusion_inverse[ i ].push_back( j - start );
    }

    for( size_t i = 0; i < ( end - start ); ++i ) {
        if( !( i % 8 ) ) std::cout << std::endl;
        std::cout << utl::paste( confusion_inverse[ i ] ) << ',';
    }
    std::cout << std::endl;
}

void inverseDiffusion( u32 diffusion[32] ) {
    auto vectorXor = []( std::vector< int >& vector1, std::vector< int >& vector2, std::vector< int >& noop_return, int& noop ) {
        if ( !noop ) return noop_return;
    	std::vector< int > res;
    	for( size_t i = 0; i < vector1.size(); ++i )
    		res.push_back( vector1[ i ] ^ vector2[ i ] );
    	return res;
    };
    auto fillMatrix = [ & ]( matrix& matrix1, unsigned int ( *set )( u32*, int, int ) ) {
        for( size_t i = 0; i < 32; i++ ) {
            std::vector< int > row;
            for( size_t j = 0; j < 32; j++ ) {
                row.push_back( set( diffusion, i, j ) );
            }
            matrix1.push_back( row );
        }
    };
    auto diffusionValue = []( u32 diffusion[ 32 ], int i, int j )
    -> u32 {
        return ( diffusion[ i ] >> j ) & 1;
    };
    auto nullValue = []( u32*, int, int ) -> u32 { return 0; };

    matrix gaussian, iterative, irregular;
    fillMatrix( gaussian, diffusionValue );
    fillMatrix( iterative, nullValue );
    fillMatrix( irregular, nullValue );

    std::cout << utl::paste( gaussian ) << std::endl;

    for( size_t i = 0; i < gaussian.size() - 1; ++i ) {
		for( size_t j = i + 1; ( j < gaussian.size() ) && ( gaussian[ i ][ i ] == 0 ); ++j ) {
            gaussian[ i ] = vectorXor( gaussian[ i ], gaussian[ j ], gaussian[ i ], gaussian[ j ][ i ] );
            irregular[ i + 1 ][ j ] = gaussian[ j ][ i ];
		}
		for( size_t j = i + 1; j < gaussian.size(); ++j ) {
            iterative[ i ][ j ] = gaussian[ j ][ i ];
            gaussian[ j ] = vectorXor( gaussian[ i ], gaussian[ j ], gaussian[ j ], gaussian[ j ][ i ] );
		}
	}

    std::cout << utl::paste( iterative ) << std::endl
    << utl::paste( irregular ) << std::endl
    << utl::paste( gaussian ) << std::endl;
}

void testA( u8 input[32], u8 output[32] ) {
    std::cout << "Before Input: " << utl::paste( input ) << std::endl;

    std::cout << "partA( ... )" << std::endl;
    partA( input, output, confusion );

    std::cout << "After Output: " << utl::paste( output ) << std::endl;
    std::cout << "Before Input: " << utl::paste( input ) << std::endl;

    std::cout << "partAReverse( ... )" << std::endl;
    partAReverse( output, input, confusion_reverse[ 0 ] );

    std::cout << "After  Input: " << utl::paste( input ) << std::endl;
    std::cout << std::endl;
}

void testB( u8 input[32], u8 output[32] ) {
    std::cout << "Before Input: " << utl::paste( input ) << std::endl;

    std::cout << "partB( ... )" << std::endl;
    partB( input, output, diffusion );

    std::cout << "After  Input: " << utl::paste( input ) << std::endl;
    std::cout << "Before Input: " << utl::paste( input ) << std::endl;

    std::cout << "partBReverse( ... )" << std::endl;
    partBReverse( input, iterative_diffusion, gaussian_diffusion );

    std::cout << "After  Input: " << utl::paste( input ) << std::endl;
    std::cout << std::endl;
}

void testC( u8 input[32], u8 output[32] ) {
    std::cout << "Before  Input:  " << utl::paste( input, 32 ) << std::endl;

    std::cout << "partC( ... )" << std::endl;
    partC( input, output, confusion );

    std::cout << "After  Output:  " << utl::paste( output, 16 ) << std::endl;

    std::cout << "partCReverse( ... )" << std::endl;
    partCReverse( output, input, confusion_reverse );

    std::cout << "Restored Input: " << utl::paste( input, 32 ) << std::endl;
    std::fill_n( output, 32, 0 );
    std::cout << "Reset Output:   " << utl::paste( output, 32 ) << std::endl;

    std::cout << "partC( ... )" << std::endl;
    partC( input, output, confusion );

    std::cout << "After  Output:  " << utl::paste( output, 16 ) << std::endl;
}

int main() {
    u8 target[] = "Hire me!!!!!!!!", output[ 32 ];

    // * Stage 1 * Complete
    /*
    inverseConfusion( confusion, 0, 256 );
    std::cout << std::endl;
    inverseConfusion( confusion, 256, 512 );
    std::cout << std::endl;
    */
    //testA( input, output );

    // * Stage 2 * Complete
    /*
    inverseDiffusion( diffusion );
    std::cout << std::endl;
    */
    //testB( input, output );

    // * Stage 3 * Complete
    /*
    partCNoSubstitution( input, output );
    solveXorPairs( output, input );
    */
    //testC( input, output );

    //std::cout << memcmp( output, target, 16 ); // => contact jobs(at)nerd.nintendo.com
    return 0;
}
