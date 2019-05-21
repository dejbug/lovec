#pragma once

namespace cmp {

static inline bool is(char)
{
	return false;
}

template<typename ... Args>
static inline bool is(char a, char b, Args ... args)
{
	return a == b || is(a, args ...);
}

static bool is_one_of(char c, char const * seps)
{
	for (; *seps; ++seps)
		if (*seps == c)
			return true;
	return false;
}

}
