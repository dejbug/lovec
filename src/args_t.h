#pragma once
#include <string>
#include <vector>
#include "err.h"
#include "file_t.h"
#include "path_t.h"
#include "cwd_t.h"
#include "file_find_t.h"

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
			throw err::make("usage error: fewer than 3 arguments passed", "usage: %s DLLPATH INPATH [OUTPATH]", argv[0]);

		if (!file_t::exists(dllpath = argv[1]))
			throw err::make("lua DLL not found at '%s'; please use the one that shipped with Love2D", argv[1]);

		if (!file_t::exists(inpath = argv[2]))
			throw err::make("input *.lua file not found at '%s'", argv[2]);

		if (argc < 4)
			derive_outpath(inpath);
		else
			outpath = argv[3];

		if (file_t::exists(outpath))
			throw err::make("output file exists at '%s'; please delete it manually first", outpath);
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

void args_t::enum_lua_dlls_in_path(std::vector<std::string> & paths)
{
	// _searchenv

	char const * const file = "lua*.dll";

	std::string env;
	std::vector<char *> dirs;

	path_t::get_env_paths(env, dirs);

	if (dirs.empty())
	{
		// std::cout << " no paths found in PATH.\n";
		return;
	}

	cwd_t cwd;

	for (auto const dir : dirs)
	{
		if (!cwd.cd(dir))
		{
			// std::cerr << "* path not found: \"" << dir << "\".\n";
			continue;
		}

		// std::cout << "* looking for \"" << file << "\" in path \"" << dir << "\".\n";

		file_find_t ff(file);

		if (ff.found()) do
		{
			// std::cout << "\"" << dir << "\\" << ff.name() << "\"\n";
			std::string path = dir;
			path += '\\';
			path += ff.name();
			paths.push_back(path);
		}
		while (ff.next());
	}
}
