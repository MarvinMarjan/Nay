#pragma once

#include "../util/file_ut.h"

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

		Fileobj() {}

		~Fileobj() {
			this->obj.close();
		}

		inline void open(std::string filepath, std::ios_base::open_mode mode = std::ios::in) {
			if (ut::file_exist(filepath)) 
				this->obj.open(filepath.c_str(), mode);

			this->obj_path = filepath;
		}
		
		inline std::string get_obj_path() const {
			return this->obj_path;
		}

		inline bool is_null() const { 
			return (!this->obj.is_open());
		}

	private:
		std::fstream obj;

		std::string obj_path;
	};
}