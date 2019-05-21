#include "lua.h"

#include "error_t.h"
#include "file_t.h"
#include "lua_handle_t.h"

void lua::compile(lua_dll_t & dll, char const * inpath, char const * outpath)
{
	lua_handle_t lua(dll.luaL_newstate());

	if (!lua) throw error_t(error_id::E_LUA_OPEN, "unable to create lua state");

	if (dll.luaL_loadfile(lua, inpath)) throw error_t(error_id::E_LUA_LOADFILE, "unable to load file as chunk");

	file_t outfile(outpath, "wb");

	constexpr auto dump_cb = [](lua_State *, void const * p, size_t sz, void * ud) -> int
	{
		return fwrite(p, sizeof(char), sz, reinterpret_cast<FILE *>(ud)), 0;
	};

	if (dll.lua_dump(lua, dump_cb, static_cast<void *>(outfile.handle))) throw error_t(error_id::E_LUA_DUMPCHUNK, "error while dumping chunk");
}
