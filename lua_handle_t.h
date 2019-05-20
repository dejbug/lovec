#pragma once
#include "lua_dll_t.h"

struct lua_handle_t
{
	lua_dll_t::lua_State * handle;
	lua_dll_t::lua_close_t lua_close;

	lua_handle_t(lua_dll_t::lua_State * handle, lua_dll_t::lua_close_t lua_close=nullptr) : handle(handle), lua_close(lua_close)
	{
	}

	~lua_handle_t()
	{
		if (!handle || !lua_close) return;

		lua_close(handle);
		handle = nullptr;
	}

	bool operator!() const { return !handle; }

	operator lua_State *() const { return handle; }
};
