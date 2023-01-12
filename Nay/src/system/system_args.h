#pragma once

#include <string>

namespace sys
{
	struct sysargs {
		std::string initial_file_path;
	};

	void set_sysargs(sysargs& args, int argc, char* argv[]) {
		if (argc < 2) 
			args.initial_file_path = "";

		else 
			args.initial_file_path = argv[1];
	}
}