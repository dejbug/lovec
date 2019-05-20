#pragma once
#include <stdio.h>

struct file_t
{
	FILE * handle = nullptr;

	file_t(char const * path, char const * mode) : handle(fopen(path, mode))
	{
	}

	~file_t()
	{
		if (!handle) return;
		fclose(handle);
		handle = nullptr;
	}

	bool operator!() const
	{
		return !handle;
	}

	static bool exists(char const * path);
};


bool file_t::exists(char const * path)
{
	FILE * f = fopen(path, "rb");
	if (!f) return false;
	fclose(f);
	return true;
}
