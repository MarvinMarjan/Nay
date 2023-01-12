#pragma once

namespace ist
{
	enum KeyCode
	{
		enter = 13,
		backspace = 8,
		space = 32,

		arrow_l = 75,
		arrow_r = 77,
		arrow_u = 72,
		arrow_d = 80
	};

	bool is_in_keycode(char ch)
	{
		switch ((int)ch)
		{
		case enter: 
			return true;
			break;

		case backspace:
			return true;
			break;

		case space:
			return true;
			break;

		case arrow_l:
			return true;
			break;

		case arrow_r:
			return true;
			break;

		case arrow_u:
			return true;
			break;

		case arrow_d:
			return true;
			break;

		default:
			return false;
		}
	}
}