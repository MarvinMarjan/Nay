#pragma once

#include <string>
#include <vector>

namespace ist
{
	class Line
	{
	public:
		Line(std::string str) {
			this->content = str;
		}

		inline void operator=(std::string str) { this->content = str; }
		inline char operator[](size_t index) const { 
			return this->content[index]; 
		}

		inline size_t size() const { return this->content.size(); }

		std::string content;
	};

	inline std::vector<Line> to_line_obj(std::vector<std::string> list)
	{
		std::vector<Line> lines;

		for (std::string str : list)
			lines.push_back(Line(str));

		return lines;
	}
}