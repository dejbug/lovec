#include <stdio.h>
#include "../crc32.h"

struct {
	unsigned long crc;
	char const * text;
	size_t size;
} known_pairs[] =
{
	{0x83DCEFB7, "1", 1},
	{0xA684C7C6, "0123456789", 10},
	{0x60C5BD52, "abCdefGhij", 10},
};

int main(int argc, char ** argv)
{
	for(auto x : known_pairs)
	{
		unsigned long const crc = crc32(0, x.text, x.size);
		auto check = [=]{ return crc == x.crc ? "yes" : "no!"; };
		printf("%08X == %08lX ? (%s)\n", crc, x.crc, check());
	}
	return 0;
}
