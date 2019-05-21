#pragma once
#include <io.h>

struct file_find_t
{
	long handle;
	struct _finddata_t fd;

	~file_find_t();
	file_find_t(char const * file);
	
	file_find_t(file_find_t &&);
	file_find_t & operator=(file_find_t &&);

	bool found() const;
	bool next();

	char const * name() const { return fd.name; }
	size_t size() const { return fd.size; }
	long ctime() const { return fd.time_create; }
	long atime() const { return fd.time_access; }
	long wtime() const { return fd.time_write; }
};
