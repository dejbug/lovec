#pragma once
#include <windows.h>

struct dll_t
{
	HMODULE handle = nullptr;

	dll_t(char const * path) : handle(LoadLibrary(path))
	{
	}

	~dll_t()
	{
		if (!handle) return;
		FreeLibrary(handle);
		handle = nullptr;
	}

	bool operator!() const
	{
		return !handle;
	}

	template<class T>
	T get(char const * name) const
	{
		return reinterpret_cast<T>(GetProcAddress(handle, name));
	}
};
