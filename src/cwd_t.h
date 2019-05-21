#pragma once
#include <direct.h>

struct cwd_t
{
	char * path{nullptr};

	~cwd_t()
	{
		cd();
		if (path) free(path);
	}

	cwd_t()
	{
		if (!_getcwd(nullptr, _MAX_PATH))
			throw err::make("unable to query CWD");
	}

	bool cd(char const * path) const
	{
		return (path && *path) ? !_chdir(path) : false;
	}

	bool cd() const
	{
		return cd(path);
	}
};
