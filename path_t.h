#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h> // getenv
#include "strutil.h"
#include "zstr_t.h"

struct path_t
{
	static bool get_env(std::string & env, char const * key="PATH");
	static bool get_env_paths(std::string & env, std::vector<char *> & list);
	static bool get_env_paths_raw(std::string & env, std::vector<char *> & list);
};

bool path_t::get_env(std::string & env, char const * key)
{
	if (!key) return false;
	char const * const env_ptr = getenv(key);
	if (!env_ptr) return env = "", false;
	return env = env_ptr, true;
}

bool path_t::get_env_paths(std::string & env, std::vector<char *> & list)
{
	if (!get_env_paths_raw(env, list)) return false;
	std::transform(list.begin(), list.end(), list.begin(),
		[&](char * item){ return zstr_t::strip(item, '/', '\\', ' '); });
	return true;
}

bool path_t::get_env_paths_raw(std::string & env, std::vector<char *> & list)
{
	return get_env(env) ? strutil::split(list, env, ";"), true : false;
}
