#pragma once

#include <string>
#include <codecvt>

namespace ut
{
	inline std::string erase_last(std::string src);

	inline std::string erase(std::string src, size_t index) {
		std::string aux = "";

		for (size_t i = 0; i < src.size(); i++)
			if (i != index)
				aux += src[i];

		if (index >= src.size())
			aux = erase_last(aux);

		return aux;
	}

	inline std::string erase_first(std::string src);

	inline std::string erase_last(std::string src) {
		std::string aux = "";

		for (size_t i = 0; i < src.size() - 1; i++)
			aux += src[i];

		return aux;
	}

	std::string insert(std::string src, char ch, size_t index)
	{
		std::string aux = "";

		if (index >= src.size())
			aux = src + ch;

		else
			for (size_t i = 0; i < src.size(); i++) {
				if (i == index) {
					aux += ch;
					aux += src[i];
					continue;
				}

				aux += src[i];
			}

		return aux;
	}

	inline std::wstring to_wstring(std::string src) {
		std::wstring wide_str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(src);

		return wide_str;
	}
}