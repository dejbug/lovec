#pragma once
#include <string>
#include <vector>
#include "error_t.h"
#include "file_t.h"
#include "path_t.h"

#include "error_id.h"

// lovec x.lua -> lovec compile -o x.clua x.lua
// lovec x.love -> lovec fuse -o x.love main.lua *.clua {dirs}

// lovec compile [-o {dst.clua}] [-i {lua.dll}] {src.lua}
// lovec build [-o {dst.love}] {src} [{src}...]
// lovec fuse [-o {dst.love}] [-i {love.exe}] {src.love}
// lovec which {all|dll|exe}


struct args_t
{
	std::string outpath_;

	char const * dllpath = nullptr;
	char const * inpath = nullptr;
	char const * outpath = nullptr;

	args_t(int argc, char ** argv)
	{
		if (argc < 3)
			throw error_t(error_id::E_USAGE, "usage error: fewer than 3 arguments passed", "usage: %s DLLPATH INPATH [OUTPATH]", argv[0]);

		if (!file_t::exists(dllpath = argv[1]))
			throw error_t(error_id::E_ARG_DLLPATH, "", "lua DLL not found at '%s'; please use the one that shipped with Love2D", argv[1]);

		if (!file_t::exists(inpath = argv[2]))
			throw error_t(error_id::E_ARG_INPATH, "", "input *.lua file not found at '%s'", argv[2]);

		if (argc < 4)
			derive_outpath(inpath);
		else
			outpath = argv[3];

		if (file_t::exists(outpath))
			throw error_t(error_id::E_ARG_OUTPATH, "", "output file exists at '%s'; please delete it manually first", outpath);
	}

	void derive_outpath(char const * path)
	{
	   char fname[_MAX_FNAME];
		_splitpath(path, nullptr, nullptr, fname, nullptr);

		outpath_.reserve(MAX_PATH);
		outpath_ = fname;
		outpath_ += ".clua";

		outpath = outpath_.c_str();
	}

	static void enum_lua_dlls_in_path(std::vector<std::string> & list);
};

// #include "utils.h"

void args_t::enum_lua_dlls_in_path(std::vector<std::string> & list)
{
	// _searchenv

	std::string env;
	std::vector<char *> ptrs;
	path_t::get_env_paths(env, ptrs);

	for (auto path : ptrs)
		printf("'%s'\n", path);
}
