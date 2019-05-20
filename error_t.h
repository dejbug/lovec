#pragma once
#include <stdexcept>
#include <stdarg.h>
#include <stdio.h>

struct error_t : public std::runtime_error
{
	int code;

	error_t(int code, char const * msg) throw() : runtime_error{msg}, code{code}
	{
		try
		{
			if (code)
				fprintf(stderr, "error[%d](%s)\n", code, msg);
		}
		catch(...)
		{
		}
	}

	error_t(int code, char const * msg, char const * format, ...) throw() : runtime_error{msg}, code{code}
	{
		try
		{
			if (code)
				fprintf(stderr, "error[%d](%s): ", code, msg);

			va_list list;
			va_start(list, format);
			vfprintf(stderr, format, list);
			va_end(list);

			fputs("\n", stderr);
		}
		catch(...)
		{
		}
	}

	int exit() const throw()
	{
		return code;
	}
};
