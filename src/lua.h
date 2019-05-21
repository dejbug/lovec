#pragma once

#include "lua_dll_t.h"

namespace lua {

void compile(lua_dll_t & dll, char const * inpath, char const * outpath);

} // !namespace lua
