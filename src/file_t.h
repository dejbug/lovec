#pragma once
#include <stdio.h>

struct file_t
{
	FILE * handle = nullptr;

	file_t(char const * path, char const * mode);

	~file_t() noexcept;

	file_t(file_t &&) = default;
	file_t& operator=(file_t &&) = default;

	bool operator!() const;

	static bool exists(char const * path);
};
