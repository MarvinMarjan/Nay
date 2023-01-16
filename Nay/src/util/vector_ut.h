#pragma once

#include <vector>

namespace ut
{
	template<typename T>
	inline bool exist(std::vector<T> vec, T item) {
		for (size_t i = 0; i < vec.size(); i++)
			if (vec[i] == item)
				return true;

		return false;
	};

	template<typename T>
	inline int find(std::vector<T> vec, T item) {
		for (size_t i = 0; i < vec.size(); i++)
			if (vec[i] == item)
				return (int) i;

		return -1;
	}

	template<typename T>
	inline void foreach(std::vector<T> arr, void (*func)(T)) {
		for (size_t i = 0; i < arr.size(); i++)
			func(arr[i]);
	}

	template<typename T1, typename T2>
	inline std::vector<T2> map(std::vector<T1> arr, T2 (*func)(T1)) {
		std::vector<T2> arr2;

		for (size_t i = 0; i < arr.size(); i++)
			arr2.push_back(func(arr[i]));

		return arr2;
	}

	inline std::string concat_str_vec(std::vector<std::string> arr, std::string separator = "\n") {
		std::string str = "";

		for (size_t i = 0; i < arr.size(); i++)
			str += arr[i] + ((i + 1 >= arr.size()) ? "" : separator);

		return str;
	}
}