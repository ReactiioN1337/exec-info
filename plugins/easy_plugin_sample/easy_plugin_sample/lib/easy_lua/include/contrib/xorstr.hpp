#pragma once
#include <array>

namespace xor_compile_time {

constexpr auto time = __TIME__;
constexpr auto seed = static_cast<int32_t>( time[ 7 ] ) +
                      static_cast<int32_t>( time[ 6 ] ) * 10 +
                      static_cast<int32_t>( time[ 4 ] ) * 60 +
                      static_cast<int32_t>( time[ 3 ] ) * 600 +
                      static_cast<int32_t>( time[ 1 ] ) * 3600 +
                      static_cast<int32_t>( time[ 0 ] ) * 36000;

/// 1988, Stephen Park and Keith Miller
/// "Random Number Generators: Good Ones Are Hard To Find", considered as "minimal standard"
/// Park-Miller 31 bit pseudo-random number generator, implemented with G. Carta's optimisation:
/// with 32-bit math and without division
template<int32_t N>
struct RandomGenerator
{
private:
    static constexpr unsigned a     = 16807;                           /// 7^5
    static constexpr unsigned m     = 2147483647;                      /// 2^31 - 1

    static constexpr unsigned s     = RandomGenerator< N - 1 >::value;
    static constexpr unsigned lo    = a * ( s & 0xFFFF );              /// Multiply lower 16 bits by 16807
    static constexpr unsigned hi    = a * ( s >> 16 );                 /// Multiply higher 16 bits by 16807
    static constexpr unsigned lo2   = lo + ( ( hi & 0x7FFF ) << 16 );  /// Combine lower 15 bits of hi with lo's upper bits
    static constexpr unsigned hi2   = hi >> 15;                        /// Discard lower 15 bits of hi
    static constexpr unsigned lo3   = lo2 + hi;

public:
    static constexpr unsigned max   = m;
    static constexpr unsigned value = lo3 > m ? lo3 - m : lo3;
};

template<>
struct RandomGenerator<0>
{
    static constexpr unsigned value = seed;
};

template<int32_t N, int32_t M>
struct RandomInt
{
    static constexpr auto value = RandomGenerator<N + 1>::value % M;
};

template<int32_t N>
struct RandomChar
{
    static const char value = static_cast<char>( 1 + RandomInt<N, 0x7F - 1>::value );
};

template<size_t N, int32_t K>
struct XorString
{
private:
    const char _key;
    std::array<char, N + 1> _encrypted;

    constexpr char enc( char c ) const
    {
        return c ^ _key;
    }

    char dec( char c ) const
    {
        return c ^ _key;
    }

public:
    template<size_t... Is>
    constexpr __forceinline XorString( const char* str, std::index_sequence<Is...> ) :
        _key( RandomChar< K >::value ),
        _encrypted{ enc( str[ Is ] )... }
    {
    }

    __forceinline const char* decrypt()
    {
        for( size_t i = 0; i < N; ++i ) {
            _encrypted[ i ] = dec( _encrypted[ i ] );
        }
        _encrypted[ N ] = '\0';
        return _encrypted.data();
    }
};
}

#ifdef _DEBUG
#define XORS(s)(s)
#else
#define XORS(s)(xor_compile_time::XorString<sizeof(s)-1, __COUNTER__>(s, std::make_index_sequence<sizeof(s)-1>()).decrypt())
#endif

///-------------------------------------------------------------------------------------------------
/// End of xorstr.hpp
///-------------------------------------------------------------------------------------------------
