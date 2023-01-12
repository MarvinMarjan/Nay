#pragma once

#include <string>

namespace ist
{
	struct cursor {
		size_t row;
		size_t col;
	};

	inline char get_ch() { return _getch(); }

	// 0 - clear from cursor to end of screen
	// 1 - clear from cursor to beggining of the screen
	// 2 - clear entire screen

	inline std::string clear_display(size_t mode = 0) { return "\033[" + std::to_string(mode) + 'J'; }
	
	inline std::string cursor_pos(size_t row = 0, size_t col = 0) { return "\033[" + std::to_string(row) + ';' + std::to_string(col) + 'H'; }
	
	inline std::string cursor_prev(size_t lines = 1) { return "\033[" + std::to_string(lines) + 'F'; }
	inline std::string cursor_next(size_t lines = 1) { return "\033[" + std::to_string(lines) + 'G'; }

	inline std::string cursor_up(size_t times = 1) { return "\033[" + std::to_string(times) + 'A'; }
	inline std::string cursor_dw(size_t times = 1) { return "\033[" + std::to_string(times) + 'B'; }
	inline std::string cursor_fw(size_t times = 1) { return "\033[" + std::to_string(times) + 'C'; }
	inline std::string cursor_bk(size_t times = 1) { return "\033[" + std::to_string(times) + 'D'; }
}