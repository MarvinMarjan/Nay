#pragma once

#include <string>
#include <vector>
#include <fstream>

namespace ut
{
	std::vector<std::string> read_vec(std::string path) {
		std::ifstream file(path.c_str());
		std::vector<std::string> content;
		std::string aux;

		while (std::getline(file, aux))
			content.push_back(aux);

		file.close();
		return content;
	}

	std::string read_str(std::string path) {
		std::ifstream file(path.c_str());
		std::string content = "";
		std::string aux;

		while (std::getline(file, aux))
			content += aux + ((file.eof()) ? "" : "\n");

		file.close();
		return content;
	}

	inline void write(std::string path, std::string content, std::ios::open_mode mode = std::ios::out) {
		if (mode != std::ios::out || mode != std::ios::app) 
			mode = std::ios::out;
		
		std::fstream file(path.c_str(), mode);
		file << content;
		file.close();
	}

	inline bool file_exist(std::string path) {
		std::fstream file;
		file.open(path.c_str(), std::ios::in);

		return (!file.fail());
	}
}