#pragma once

#include "file_util.h"

#include <fstream>
#include <string>
#include <vector>

namespace file
{
	class Fileobj
	{
	public:
		Fileobj(std::string filepath, std::ios_base::open_mode mode = std::ios::in) {
			this->obj.open(filepath.c_str(), mode);
			this->obj_path = filepath;
		}

		~Fileobj() { this->obj.close(); }
		
		Fileobj() {}

		inline void open(std::string filepath, std::ios_base::open_mode mode = std::ios::in) {
			if (file_exist(filepath)) 
				this->obj.open(filepath.c_str(), mode);

			this->obj_path = filepath;
		}

		std::vector<std::string> read() {
			std::vector<std::string> content;
			std::string line = "";

			while (!this->obj.eof()) {
				std::getline(this->obj, line);
				content.push_back(line);
			}

			return content;
		}

		std::string read_str() {
			std::string content = "";
			std::string line = "";

			while (!this->obj.eof()) {
				std::getline(this->obj, line);
				content += line;
			}

			return content;
		}

	private:
		std::fstream obj;

		std::string obj_path;
	};
}