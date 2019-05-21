#include "file_t.h"

file_t::~file_t() noexcept
{
	if (!handle) return;
	fclose(handle); // TODO: Wrap this in try/catch(...) ?
	handle = nullptr;
}

file_t::file_t(char const * path, char const * mode) : handle(fopen(path, mode))
{
}

bool file_t::operator!() const
{
	return !handle;
}

bool file_t::exists(char const * path)
{
	FILE * f = fopen(path, "rb");
	if (!f) return false;
	fclose(f);
	return true;
}
