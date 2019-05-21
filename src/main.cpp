#include <string>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "error_t.h"
#include "file_t.h"
#include "args_t.h"
#include "lua_dll_t.h"
#include "lua_handle_t.h"

#include "error_id.h"

#include "crc32.h"

void compile_lua_file(lua_dll_t & dll, char const * inpath, char const * outpath)
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

int main(int argc, char ** argv)
{
	try
	{
		std::vector<std::string> lua_dll_paths;
		args_t::enum_lua_dlls_in_path(lua_dll_paths);
		return 0;

		args_t args(argc, argv);
		lua_dll_t dll(args.dllpath);

		compile_lua_file(dll, args.inpath, args.outpath);
	}

	catch (error_t & e)
	{
		return e.exit();
	}

	return error_id::E_OK;
}
