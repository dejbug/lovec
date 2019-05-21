#include "file_find_t.h"
#include <errno.h>
#include "err.h"

file_find_t::~file_find_t()
{
	if (handle >= 0) _findclose(handle);
}

file_find_t::file_find_t(char const * file) : handle{_findfirst(file, &fd)}
{
	if (handle >= 0) _set_errno(0);
	else if (EINVAL == errno)
		throw err::make("invalid filespec for file_find_t");
}

file_find_t::file_find_t(file_find_t && that)
{
	that.handle = handle;
	handle = -1;
	memcpy(&that.fd, &fd, sizeof(struct _finddata_t));
}

file_find_t & file_find_t::operator=(file_find_t && that)
{
	that.handle = handle;
	handle = -1;
	memcpy(&that.fd, &fd, sizeof(struct _finddata_t));
	return *this;
}

bool file_find_t::found() const
{
	return ENOENT != errno;
}

bool file_find_t::next()
{
	if (ENOENT == errno) return false;
	return !_findnext(handle, &fd);
}
