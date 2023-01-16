#pragma once

#include <iomanip>

#include "../../system/system.h"

#include "../../fileobj/fileobj.h"

#include "../../util/vector_ut.h"
#include "../../util/string_ut.h"
#include "../../util/file_ut.h"

#include "../in/input_handling.h"
#include "../in/keymap.h"

#include "../out/colors.h"

#include "line.h"

namespace ist
{
	enum CursorMovement {
		None,
		Up,
		Down
	};

	class Editor
	{
	public:
		friend sys::System;

		Editor(file::Fileobj* file) {
			if (!file->is_null())
				this->setup(file);

			else
				this->setup();
		}

		Editor() {
			this->setup();
		}

		inline void update(char ch)
		{
			switch ((int)ch) {
				case ist::arrow:
					ch = ist::get_ch();

					if ((int)ch == ist::arrow_l) {
						if (this->curs.col > 0)
							this->curs.col--;

						else if (this->curs.row > 0) {
							this->curs.row--;
							this->curs._row--;
							this->curs.col = this->lines[this->curs.row].size();

							this->editor_lines_update();
						}
					}

					else if ((int)ch == ist::arrow_r) {
						if (this->curs.col < this->lines[this->curs.row].size())
							this->curs.col++;

						else if (this->curs.row < this->size() - 1) {
							this->curs.row++;
							this->curs._row++;
							this->curs.col = 0;
							this->editor_lines_update();
						}
					}
		

					else if ((int)ch == ist::arrow_u) {
						if (this->curs.row > 0) {
							this->curs.row--;
							this->curs._row--;

							if (this->curs.col >= this->lines[this->curs.row].size())
								this->curs.col = this->lines[this->curs.row].size();

							this->cursor_mov = Up;
						}
					}

					if ((int)ch == ist::arrow_d) {
						if (this->curs.row + 1 < this->lines.size()) {
							this->curs.row++;
							this->curs._row++;

							if (this->curs.col >= this->lines[this->curs.row].size())
								this->curs.col = this->lines[this->curs.row].size();

							this->cursor_mov = Down;
						}
					}

					if ((int)ch != ist::arrow_u && (int)ch != ist::arrow_d)
						this->cursor_mov = None;

					break;

				case ist::enter: {
					std::string aux1 = this->lines[this->curs.row].content.substr(this->curs.col);
					std::string aux2 = this->lines[this->curs.row].content.substr(0, this->curs.col);

					this->lines.insert(this->lines.begin() + this->curs.row, Line(aux2));

					this->curs.row++;
					this->curs._row++;
					this->curs.col = 0;

					this->lines[this->curs.row] = aux1;
					
					this->editor_lines_update();
					break;
				}

				case ist::backspace:
					if (!this->curs.col && this->curs.row > 0) {
						std::string aux = this->lines[this->curs.row];

						this->lines.erase(this->lines.begin() + this->curs.row, this->lines.begin() + this->curs.row + 1);

						this->curs.row--;
						this->curs._row--;
						this->curs.col = this->lines[this->curs.row].size();

						this->lines[this->curs.row] += aux;

						this->editor_lines_update();
						break;
					}
					
					if (this->curs.row <= 0 && !this->curs.col) 
						break;

					this->lines[this->curs.row] = ut::erase(this->lines[this->curs.row].content, this->curs.col - 1);
					this->curs.col--;
					break;

				case ist::ctrl_s: break;

				default:
					this->lines[this->curs.row] = ut::insert(this->lines[this->curs.row].content, ch, this->curs.col);
					this->curs.col++;
			}
		}

		void print(bool smart_update = false)
		{
			std::cout << ist::cursor_pos();

			for (size_t i = 0; i < this->size(); i++) {
				std::cout << std::setw(5);

				if (i == this->curs.row) {
					std::cout << std::right << i + 1 << "  ";

					for (size_t o = 0; o < this->lines[i].size(); o++) {
						if (o == this->curs.col)
							std::cout << ost::clr(this->lines[i].content[o], ost::red, ost::underline);

						else
							std::cout << this->lines[i].content[o];
					}

					if (this->curs.col == this->lines[i].size())
						std::cout << ost::clr("_", ost::red, ost::underline);
				}

				else if (!smart_update || ut::exist(this->update_queue, i)) {
					std::cout << std::right << i + 1 << "  " << this->lines[i].content;

					if (ut::exist(this->update_queue, i))
						this->update_queue.erase(this->update_queue.begin() + ut::find(this->update_queue, i));
				}

				if (i + 1 < this->size())
					std::cout << std::endl;
			}
		}

		inline void add_update_item(size_t line) { this->update_queue.push_back(line); }

		inline ist::cursor get_cursor() const { return this->curs; }
		inline CursorMovement get_cursor_mov() const { return this->cursor_mov; }

		inline Line* operator[](size_t index) { return &this->lines[index]; }

		inline size_t size() const { return this->lines.size(); }

	private:
		inline std::vector<size_t> get_update_queue() const { return this->update_queue; }

		inline void setup() {
			this->lines = std::vector<Line>({ Line("") });

			this->curs.row = 0;
			this->curs._row = 1;
			this->curs.col = 0;
		}

		inline void setup(file::Fileobj* file) {
			if (ut::read_str(file->get_obj_path()) == "")
				this->lines = std::vector<Line>({ Line("") });

			else 
				this->lines = to_line_obj(ut::read_vec(file->get_obj_path()));

			this->curs.row = this->size() - 1;
			this->curs._row = this->size();
			this->curs.col = this->lines[this->size() - 1].size();
		}

		inline void editor_lines_update() {
			std::cout << ist::cursor_pos() << ist::clear_display();
			this->print();
		}

		std::vector<Line> lines;
		std::vector<size_t> update_queue;
		ist::cursor curs;

		CursorMovement cursor_mov;
	};
}