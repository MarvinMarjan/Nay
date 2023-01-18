#pragma once

#include <iostream>

#include "../fileobj/fileobj.h"

#include "system_args.h"
#include "system_exceptions.h"

#include "../stream/out/colors.h"
#include "../stream/in/editor.h"

#include "../util/string_ut.h"
#include "../util/file_ut.h"
#include "../util/system_ut.h"


namespace sys
{
	enum SysState {
		On = 1,
		Off = 0
	};

	inline void set_console_title(LPCWSTR title);

	class System
	{
	public:
		System() {
			this->state = SysState::On;
			this->using_a_file = false;

			ut::set_console_title(L"Nay - Untitled");
		}

		System(std::string initial_file_path) {
			this->state = SysState::On;

			if (ut::file_exist(initial_file_path))
				this->initial_file.open(initial_file_path);

			else
				this->abort(FileNotFound, initial_file_path);

			this->full_file_str = ut::read_str(this->initial_file.get_obj_path());

			std::wstring wstr_path = ut::to_wstring(initial_file_path);
			std::wstring title = L"Nay - " + wstr_path;

			ut::set_console_title(title.c_str());
		}

		System(sysargs args) {
			this->state = SysState::On;
			this->initial_file_path = args.initial_file_path;

			if (args.initial_file_path != "") {
				if (ut::file_exist(args.initial_file_path))
					this->initial_file.open(args.initial_file_path);

				else
					this->abort(FileNotFound, args.initial_file_path);
			}

			else
				this->using_a_file = false;

			this->full_file_str = ut::read_str(this->initial_file.get_obj_path());

			std::wstring wstr_path = ut::to_wstring(args.initial_file_path);
			std::wstring title = L"Nay - " + wstr_path;

			ut::set_console_title(title.c_str());
		}
		
		inline void update(char ch)
		{
			this->current_str = ut::concat_str_vec(
				ut::map<ist::Line, std::string>(this->editor->lines, [] (ist::Line line) -> std::string {
					return line.content;
				})
			);

			if ((char)ch == ist::ctrl_s)
				this->save_file();

			this->is_unsaved = (this->current_str != this->full_file_str);

			std::wstring wstr_path = ((this->is_using_a_file()) ? ut::to_wstring(this->initial_file_path) : ut::to_wstring(this->current_str));
			std::wstring title;

			if (this->is_unsaved)
				title = L"Nay - " + wstr_path + L"*";

			else
				title = L"Nay - " + wstr_path;

			ut::set_console_title(title.c_str());
		}

		inline void save_file() {
			std::string file_path;

			if (!this->is_using_a_file()) {
				file_path = this->get_user_input("File path");

				file_path = ((file_path[file_path.size() - 1] == '/' || file_path[file_path.size() - 1] == '\\') ? file_path : file_path + '/');
			}

			ut::write((!this->is_using_a_file()) ? file_path + this->current_str : this->initial_file_path, this->current_str);
			this->full_file_str = this->current_str;

			if (!this->is_using_a_file()) {
				this->using_a_file = true;
				this->initial_file_path = file_path + this->current_str;
			}
		}

		inline std::string get_user_input(std::string title = "") {
			ut::set_mouse_visible(true);
			std::string user_input = "";

			std::cout << ist::clear_display(2) << ist::cursor_pos();
			std::cout << title << ost::clr(" -> ", ost::wt_yellow);
			
			std::getline(std::cin, user_input);
			ut::set_mouse_visible(false);

			this->editor->editor_lines_update();

			return user_input;
		}

		inline void throw_exception(Exception exception) const {
			std::cout << ost::clr(exception.name + "> ", ost::red);
			std::cout << exception.msg << ((exception.complement != "") ? ": " : "");
			std::cout << ost::clr('\"' + exception.complement + '\"', ost::wt_green);
		}

		inline void set_editor(ist::Editor* editor) {
			this->editor = editor;
		}

		inline SysState get_state() const {
			return this->state;
		}

		inline bool is_on() const {
			return this->state;
		}

		inline void quit() {
			this->state = SysState::Off;
		}

		inline file::Fileobj* get_initial_file() {
			if (this->using_a_file)
				return &this->initial_file;

			else
				return nullptr;
		}

		inline bool is_using_a_file() const { return this->using_a_file; }

	private:
		inline void abort(ExceptionList excp, std::string complement = "") {
			this->throw_exception(exception(excp, complement));
			this->state = SysState::Off;
		}

		SysState state;
		file::Fileobj initial_file;
		ist::Editor* editor;
		std::string initial_file_path;

		std::string full_file_str;
		std::string current_str;

		bool using_a_file = true;
		bool is_unsaved = false;
	};
}