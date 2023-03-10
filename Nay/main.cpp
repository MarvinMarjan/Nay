#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
	ut::set_mouse_visible(false);

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

	system.set_editor(&editor);

	ist::cursor cur;
	char ch;

	editor.print();

	while (system.is_on())
	{
		cur = editor.get_cursor();

		if ((ch = ist::get_ch())) {
			std::cout << ist::cursor_pos(cur._row) << ist::clear_line(2);

			std::cout << ist::clear_line(2);

			editor.update(ch);
			
			if (editor.get_cursor_mov() != ist::None)
				editor.add_update_item(cur.row);
		}

		editor.print(true);
		system.update(ch);	
	}
	
	return EXIT_SUCCESS;
}