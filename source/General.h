#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED
#include <cstdint>

//#include "../float/ConsoleIO.h"

namespace Generic
{

	typedef uint8_t uint8;
	typedef uint32_t uint32;
	typedef unsigned int uint;

	template <typename Container>
	class Flags
	{
		Container flags;
		public:
		Flags(const Container& flags = 0) : flags(flags) {}

		bool flag(uint8 number){return flags & (1ULL << number);}
		bool operator[](uint8 number){return flags & (1ULL << number);}

		void set(uint8 number){flags |= (1ULL << number);}
		void clear(uint8 number){flags &= ~(1ULL << number);}
		void swtch(uint8 number){flags ^= (1ULL << number);}
	};

	typedef Flags<uint8> FLAGS;

	static uint32 temp_rand1 = 0, temp_rand2 = 0;
	// hmmm... inlineing also helps avoid multiple definitions
	static void stiny_rand(uint32 seed, uint32 seed2 = 0)
	{
		temp_rand1 = seed;
		temp_rand2 = seed2;
	}

	static uint32 tiny_rand(uint32 lucky = 13)  // hihii... 13
	{
		temp_rand2 += temp_rand1<<16 | temp_rand1>>16;
		temp_rand1 += temp_rand2 + lucky;
		return temp_rand2;
	}

}
#endif // GENERAL_H_INCLUDED
