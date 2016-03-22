#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED
#include <cstdint>
#include <climits>

//#include "../float/ConsoleIO.h"

namespace Generic
{

	typedef std::uint8_t uint8;
	typedef std::uint32_t uint32;
	typedef unsigned int uint;

	// basically a poor man's bitset... great job me from 2013 -_-
	template <typename Container>
	class Flags
	{
		Container flags;
		public:
		Flags(const Container& flags = 0) : flags(flags) {}

		bool operator[](uint8 number){return flags & (1ULL << number);}

		void set(uint8 number){flags |= (1ULL << number);}
		void clear(uint8 number){flags &= ~(1ULL << number);}
		void swtch(uint8 number){flags ^= (1ULL << number);}
	};

	typedef Flags<uint8> FLAGS;

	// TODO: make tiny_rand a template class
	typedef uint32 TinyrandType;
	static TinyrandType temp_rand1 = 0, temp_rand2 = 0;
	static void stiny_rand(TinyrandType seed, TinyrandType seed2 = 0)
	{
		temp_rand1 = seed;
		temp_rand2 = seed2;
	}

	static TinyrandType tiny_rand(TinyrandType lucky = 13)  // hihii... 13
	{
		static const uint size_in_bits = sizeof(TinyrandType) * CHAR_BIT;
		// static_assert( (size_in_bits&1) == 0,  "The size of the underlying datatype must be even.");
		static const uint half_bits = size_in_bits >> 1;
		static const uint remnant_bits = size_in_bits - half_bits;

		temp_rand2 += temp_rand1<<half_bits | temp_rand1>>remnant_bits;
		temp_rand1 += temp_rand2 + lucky;
		return temp_rand2;
	}

}
#endif // GENERAL_H_INCLUDED
