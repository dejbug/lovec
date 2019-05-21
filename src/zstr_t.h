#pragma once
#include <stdio.h>  // strlen
#include "cmp.h"

struct zstr_t
{
	static size_t len(char const * text)
	{
		return text && *text ? strlen(text) : 0;
	}

	static char * lstrip(char * text, char const * seps);
	static char * rstrip(char * text, char const * seps);
	static char * strip(char * text, char const * seps);

	template<typename ... Args>
	static char * lstrip(char * text, char c, Args ... args)
	{
		while (*text && cmp::is(*text, c, args ...)) ++text;
		return text;
	}

	template<typename ... Args>
	static char * rstrip(char * text, char c, Args ... args)
	{
		char * ptr = text + len(text);
		while (ptr > text && cmp::is(*--ptr, c, args ...)) *ptr = '\0';
		return text;
	}

	template<typename ... Args>
	static char * strip(char * text, char c, Args ... args)
	{
		return lstrip(rstrip(text, c, args ...), c, args ...);
	}
};

char * zstr_t::lstrip(char * text, char const * seps)
{
	while (*text && cmp::is_one_of(*text, seps)) ++text;
	return text;
}

char * zstr_t::rstrip(char * text, char const * seps)
{
	char * ptr = text + len(text);
	while (--ptr >= text && cmp::is_one_of(*ptr, seps));
	*(ptr+1) = '\0';
	return text;
}

char * zstr_t::strip(char * text, char const * seps)
{
	return lstrip(rstrip(text, seps), seps);
}
