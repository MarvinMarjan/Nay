#pragma once

#include <string>
#include <fstream>

namespace file
{
	inline bool file_exist(std::string path) {
		std::fstream file;
		file.open(path.c_str(), std::ios::in);

		return (!file.fail());
	}
}