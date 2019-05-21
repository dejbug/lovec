#include "err.h"
#include <stdarg.h>
#include <stdio.h> // _vsnprintf

constexpr size_t capacity{64};

// File-global, to ensure that we have this much memory at program start.
// TODO: Is thread safety an issue?
static char buffer[capacity]{0};

std::runtime_error err::make(char const * msg, ...) noexcept
{
	try
	{
		va_list list;
		va_start(list, msg);
		_vsnprintf(buffer, sizeof(buffer), msg, list);
		buffer[sizeof(buffer)-1] = 0;
		va_end(list);
		return std::move(std::runtime_error{buffer});
	}
	catch (...) {}

	return std::move(std::runtime_error{"unknown error (exception during formatting!)"});
}
