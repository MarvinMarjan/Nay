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
}