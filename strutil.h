#pragma once
#include <string>
#include <vector>

namespace strutil {

void split(std::vector<char *> & ptrs, std::string & text, char const * seps)
{
	std::string::size_type pos = -1;

	while (true)
	{
		pos = text.find_first_not_of(seps, pos+1);
		if (text.npos == pos) break;
		ptrs.push_back(&text[pos]);

		pos = text.find_first_of(seps, pos+1);
		if (text.npos == pos) break;
		text[pos] = '\0';
	}
}

void split(std::vector<std::string> & ptrs, std::string const & text, char const * seps)
{
	std::string::size_type beg{0}, end{text.npos};

	do {
		beg = text.find_first_not_of(seps, end+1);
		if (text.npos == beg) break;

		end = text.find_first_of(seps, beg+1);
		ptrs.push_back(text.substr(beg, end-beg));
	}
	while(text.npos != end);
}

std::string rstrip(char * text_, char const * seps)
{
	std::string text{text_};
	auto pos = text.find_last_not_of(seps);
	if (text.npos != pos) text[pos+1] = '\0';
	else text[0] = '\0';
	return std::move(text);
}

std::string & rstrip(std::string & text, char const * seps)
{
	auto pos = text.find_last_not_of(seps);
	if (text.npos != pos) text[pos+1] = '\0';
	else text[0] = '\0';
	return text;
}

std::string lstrip(char * text_, char const * seps)
{
	std::string text{text_};
	auto pos = text.find_first_not_of(seps);
	if (text.npos == pos) return std::move(text);
	return std::string(text.begin() + pos, text.end());
}

} // !namespace utils
