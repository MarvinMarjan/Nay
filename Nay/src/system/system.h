#pragma once

#include <iostream>
#include <Windows.h>
#include <strsafe.h>

#include "../fileobj/fileobj.h"
#include "../fileobj/file_util.h"

#include "system_args.h"
#include "system_exceptions.h"

#include "src/stream/out/colors.h"

#include "../util/string_ut.h"

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

			set_console_title(L"Nay - Untitled");
		}

		System(std::string initial_file_path) {
			this->state = SysState::On;

			if (file::file_exist(initial_file_path))
				this->initial_file.open(initial_file_path);

			else
				this->abort(FileNotFound, initial_file_path);

			std::wstring wstr_path = ut::to_wstring(initial_file_path);
			std::wstring title = L"Nay - " + wstr_path;

			set_console_title(title.c_str());
		}

		System(sysargs args) {
			this->state = SysState::On;
			
			if (args.initial_file_path != "") {
				if (file::file_exist(args.initial_file_path))
					this->initial_file.open(args.initial_file_path);

				else
					this->abort(FileNotFound, args.initial_file_path);
			}

			else
				this->using_a_file = false;

			std::wstring wstr_path = ut::to_wstring(args.initial_file_path);
			std::wstring title = L"Nay - " + wstr_path;

			set_console_title(title.c_str());
		}

		inline void throw_exception(Exception exception) const {
			std::cout << ost::clr(exception.name + "> ", ost::red);
			std::cout << exception.msg << ((exception.complement != "") ? ": " : "");
			std::cout << ost::clr('\"' + exception.complement + '\"', ost::wt_green);
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

		bool using_a_file = true;
	};

	inline void set_mouse_visible(bool state) {
		const CONSOLE_CURSOR_INFO c_info = { 1, state };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c_info);
	}

	inline void set_console_title(LPCWSTR title) {
		TCHAR console_title[MAX_PATH];
		TCHAR current_title[MAX_PATH];


		StringCchPrintf(console_title, MAX_PATH, title, current_title);

		SetConsoleTitle(console_title);
	}
}