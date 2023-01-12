#include <iostream>
#include <conio.h>

#include "src/system/system.h"
#include "src/stream/in/editor.h"

inline std::ostream& operator<<(std::ostream& os, ist::Line line)
{
	return (os << line.content);
}

inline std::ostream& operator<<(std::ostream& os, ist::Line* line)
{
	return (os << line->content);
}

int main(int argc, char* argv[])
{
	sys::set_mouse_visible(false);

	sys::sysargs args;
	sys::set_sysargs(args, argc, argv);

	sys::System system;

	ist::Editor editor;

	if (system.is_using_a_file()) {
		ist::Editor _editor(system.get_initial_file());
		editor = _editor;
	}

	else {
		ist::Editor _editor;
		editor = _editor;
	}


	char ch;

	// while system state is on
	while (system.is_on())
	{
		editor.print();

		if ((ch = ist::get_ch())) {
			editor.update(ch);

			std::cout << ist::cursor_pos() << ist::clear_display() << ist::clear_display(3);

			//std::cout << std::endl << editor.get_cursor().col << " - " << editor.get_cursor().row << std::endl;
		}
	}

	return 0;
}