#pragma once
#include "err.h"
#include "dll_t.h"

struct lua_dll_t
{
	typedef struct lua_State lua_State;

	typedef int (* lua_Writer_t)(lua_State *, void const *, size_t, void *);

	typedef lua_State * (* luaL_newstate_t)(void);
	typedef void (* lua_close_t)(lua_State *);
	typedef int (* luaL_loadfile_t)(lua_State *, char const *);
	typedef int (* lua_dump_t)(lua_State *, lua_Writer_t, void *);

	dll_t dll;

	luaL_newstate_t luaL_newstate = nullptr;
	lua_close_t lua_close = nullptr;
	luaL_loadfile_t luaL_loadfile = nullptr;
	lua_dump_t lua_dump = nullptr;

	lua_dll_t(char const * path, bool need_close=false) : dll(path)
	{
		if (!dll) throw err::make("DLL load error", "please specify correct path to love2d's luaXX.dll");

		luaL_newstate = dll.get<luaL_newstate_t>("luaL_newstate");
		if (!luaL_newstate) throw err::make("luaL_newstate not found in DLL");

		lua_close = dll.get<lua_close_t>("lua_close");
		if (need_close && !lua_close) throw err::make("lua_close not found in DLL");

		luaL_loadfile = dll.get<luaL_loadfile_t>("luaL_loadfile");
		if (!luaL_loadfile) throw err::make("luaL_loadfile not found in DLL");

		lua_dump = dll.get<lua_dump_t>("lua_dump");
		if (!lua_dump) throw err::make("lua_dump not found in DLL");
	}
};
