//      __      __________ __________ ____  __. .___ _______    ____________________ ________    _____________________________ _________ _________
//      /  \    /  \_____  \\______   \    |/ _| |   |\      \   \______   \______   \\_____  \  /  _____/\______   \_   _____//   _____//   _____/
//      \   \/\/   //   |   \|       _/      <   |   |/   |   \   |     ___/|       _/ /   |   \/   \  ___ |       _/|    __)_ \_____  \ \_____  \
//      \        //    |    \    |   \    |  \  |   /    |    \  |    |    |    |   \/    |    \    \_\  \|    |   \|        \/        \/        \
//       \__/\  / \_______  /____|_  /____|__ \ |___\____|__  /  |____|    |____|_  /\_______  /\______  /|____|_  /_______  /_______  /_______  /
//            \/          \/       \/        \/             \/                    \/         \/        \/        \/        \/        \/        \/
// Alexander
// Töpfer
// 2020
#include <cstring>
#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <sstream>

typedef unsigned char u8;
typedef unsigned int u32;

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

// Inverse of s-box
std::vector< std::vector< int > > confusion_reverse = {
{106,309},{26,407},{24,94},{89,343},{56,511},{86,500},{227,408},{195,460},{228,436},{95,490},{188,425},{144,483},{47,282},{223,297},{70},{454},
{88,466},{294},{245,287},{42,366},{247,358},{191},{128,499},{10,352},{204,301},{221},{23,440},{246,382},{83,113,509},{131,439},{129,398},{4,464},
{446},{130,344},{240,300},{145,404},{48,388,507},{2,487},{112,296},{158,271},{7,289,465},{253,428},{232,310},{9,433},{118,256},{132,220,471},{222,359},{176,336},
{81,318},{251,332},{200,387},{6,154,320,485},{140,298},{115,402},{99,486},{210,378},{110,494},{68,473},{197,326},{216,305},{148,384},{218,477},{327},{230,270,367},
{161,281},{162,431},{37,350,430},{117,274},{396},{248,449},{238,286},{100,361},{18,445},{77,209,421},{43,416},{33,429},{125,263},{67,484},{146,272,463},{183,345},
{189,269},{92,303},{82,283},{39,502},{149,374},{14,362,410},{104,414},{184,207,406},{193,413},{75,267,468},{288},{215,492},{59,457},{15,401},{123,308},{198,328},
{252,482},{121,313},{22,426},{40,453},{91},{239,472},{41,181,299},{214,339},{196},{80,403},{34,420},{380},{62,467},{155,323},{51,276},{244,302},
{233,422},{31,405},{32,258},{255},{119,475},{321},{49,438},{127,461},{21,151,340},{157,481},{174,370},{192,279},{8,280},{236,395},{226,444},{103},
{357},{60,368},{165,391},{30,265},{142,476},{45,335},{65,284},{250},{185,262},{153,260},{72,418},{205},{71,417},{137,171,389},{96,424},{16,312},
{186},{116,376},{61,337},{166,224,450},{3,371},{134,295},{76,315},{93,257},{180,508},{213,278},{234,411},{87,304},{187},{122,329},{495},{201,333},
{69,360},{53,325,437},{58,243,506},{172,355},{152,412},{50,341},{168,261},{150,377},{90,290},{133,331},{28,334},{101,342},{0,456},{97,347,510},{173,273},{338},
{13,455},{383},{85,474},{5,316},{120,392},{219,373},{175,369,385},{208,434},{135,441},{242,346},{66,314,458},{217,291},{11,194,488},{178,479},{229,501},{126,375},
{38,496},{44,285},{57,504},{136,452},{159,363},{164,423},{55,64,505},{249,415,480},{235,324},{27,381},{105,268},{292,432},{203,443},{170,259},{102,435},{46,491},
{73,277,372},{1,317},{17,498},{20,469},{19,399},{275},{143,419},{52,353},{111,237,356},{231,386},{63,306},{139,394},{114,319,427},{167,470},{211,451},{163,459},
{84,489},{141},{206,493},{107,442},{409},{179,365},{78,447},{190,462},{35,264},{36,124,322},{79,400},{202,266},{54,307},{108},{199,354},{169,497},
{29,293},{109,379},{25,390},{182,349},{241,478},{212,311},{12},{98,254,503},{138,448},{160,393},{},{156,397},{225,351},{177,330},{74,348},{147,364}
};

// Matrix multiplication? A x A^(-1) = E
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
        // S-box first part
        for( u8 j = 0; j < 32; j++ ) {
            output[ j ] = confusion[ input[ j ] ];
            input[ j ] = 0;
        }

        // Second part (expandable?)
        for( u8 j = 0; j < 32; j++ ) {
            for( u8 k = 0; k < 32; k++ ) {
                input[ j ] = input[ j ] ^ output[ k ] * ( ( diffusion[ j ] >> k ) & 1 );
            }
        }
    }

    // XOR third part
    for( u8 i = 0; i < 16; i++ ) {
        output[ i ] = confusion[ input[ i * 2 ] ] ^ confusion[ input[ i * 2 + 1 ] + 256 ];
    }
}

std::string paste( std::vector< int >& vector ) {
    std::stringstream vector_string;
    if( !vector.empty() ) {
        std::copy( vector.begin(), vector.end() - 1, std::ostream_iterator< int >( vector_string, "," ) );
        vector_string << vector.back();
    }
    return vector_string.str();
}

void writeStdout( u8* array, size_t size ) {
    for( size_t i = 0; i < size; ++i ) {
        std::cout << array[i];
    }
    std::cout << std::endl;
}

void firstPart( u8 input[32], u8 output[32], u8 confusion[512] ) {
    // S-box
    for( u8 j = 0; j < 32; ++j ) {
        output[ j ] = confusion[ input[ j ] ];
        input[ j ] = 0;
    }
}

void secondPart( u8 input[32], u8 output[32], u32 diffusion[32] ) {
    //TODO
}

std::vector< int >* crackConfusion( u8 confusion[512], bool debug ) {
    std::vector< int >* confusion_crack = new std::vector< int > [512];
    for( int i = 0; i < 512; ++i ) {
        for( int j = 0; j < 512; ++j )
            if( confusion[ j ] == i )
                confusion_crack[ i ].push_back( j );
    }
    if( debug ) {
        for( int i = 0; i < 512; ++i ) {
            if( !(i % 8) ) std::cout << std::endl;
            std::cout << '{' << paste( confusion_crack[i] ) << '}' << (!( i - 511 ) ? ' ' : ',');
        }
        std::cout << std::endl;
    }
    return confusion_crack;
}

double verifyConfusionCrack( std::vector< int >* confusion_crack, u8 confusion[ 512 ] ) {
    int candidates = 512;
    for( int i = 0; i < 512; ++i ) {
        if ( std::find( confusion_crack[ confusion[ i ] ].begin(), confusion_crack[ confusion[ i ] ].end(), i ) != confusion_crack[ confusion[ i ] ].end() ) {}
        else --candidates;
    }
    return 100 * ( candidates / 512 );
}

void firstPartReverse( u8 input[32], u8 output[32], std::vector< int >* confusion_crack ) {
    std::vector< int > tmp;
    for( u8 j = 0; j < 32; j++ ) {
        tmp = confusion_crack[ input[ j ] ];
        if( !tmp.empty() ) {
            output[ j ] = tmp[0];
        } else {
            output[ j ] = 0;
        }
    }
}

int main() {
    u8 target[] = "Hire me!!!!!!!!", output[ 32 ];
    forward( input, output, confusion, diffusion );

    // Stage 1 complete
    std::vector< int >* confusion_test = crackConfusion( confusion, false );
    std::cout << verifyConfusionCrack( confusion_test, confusion ) << '%' << ' ' << "reversibility of substitution box" << std::endl;

    // Reverse confusion box
    u8 input_test[ 32 ], output_test[ 32 ];
    std::copy( std::begin( input ), std::end( input ), std::begin( input_test ) );
    writeStdout( input_test, 32 );
    firstPart( input_test, output_test, confusion );
    writeStdout( input_test, 32 );
    firstPartReverse( output_test, input_test,  confusion_test);
    writeStdout( input_test, 32 );

    // Stage 2 incomplete
    // Stage 3 incomplete

    std::cout << output << std::endl;
    std::cout << memcmp( output, target, 16 ); // => contact jobs(at)nerd.nintendo.com
    return 0;
}
