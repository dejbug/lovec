#include <string>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "error_t.h"
#include "args_t.h"
#include "lua.h"
#include "lua_dll_t.h"

#include "error_id.h"


int main(int argc, char ** argv)
{
	try
	{
		std::vector<std::string> lua_dll_paths;
		args_t::enum_lua_dlls_in_path(lua_dll_paths);
		return 0;

		args_t args(argc, argv);
		lua_dll_t dll(args.dllpath);

		lua::compile(dll, args.inpath, args.outpath);
	}

	catch (error_t & e)
	{
		return e.exit();
	}

	return error_id::E_OK;
}
