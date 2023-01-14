#pragma once

#include "../../fileobj/fileobj.h"
#include "../../util/vector_ut.h"
#include "../../util/string_ut.h"
#include "../in/input_handling.h"
#include "../in/keymap.h"
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
			//std::cout << ist::cursor_pos(this->curs.row, this->curs.col);

			switch ((int)ch) {
				case ist::arrow:
					ch = ist::get_ch();

					if ((int)ch == ist::arrow_l) {
						if (this->curs.col > 0)
							this->curs.col--;
					}

					else if ((int)ch == ist::arrow_r) {
						if (this->curs.col < this->lines[this->curs.row].size())
							this->curs.col++;
					}
		

					else if ((int)ch == ist::arrow_u) {
						if (this->curs.row > 0) {
							this->curs.row--;
							this->curs._row--;

							if (this->curs.col >= this->lines[this->curs.row].size())
								this->curs.col = this->lines[this->curs.row].size();
						}

						this->cursor_mov = Up;
					}

					if ((int)ch == ist::arrow_d) {
						if (this->curs.row + 1 < this->lines.size()) {
							this->curs.row++;
							this->curs._row++;

							if (this->curs.col >= this->lines[this->curs.row].size())
								this->curs.col = this->lines[this->curs.row].size();
						}

						this->cursor_mov = Down;
					}

					if ((int)ch != ist::arrow_u && (int)ch != ist::arrow_d)
						this->cursor_mov = None;

					break;

				case ist::backspace:
					if (!this->lines[this->curs.row].size())
						break;

					this->lines[this->curs.row] = ut::erase(this->lines[this->curs.row].content, this->curs.col - 1);
					this->curs.col--;
					break;

				default:
					this->lines[this->curs.row] = ut::insert(this->lines[this->curs.row].content, ch, this->curs.col);
					this->curs.col++;
			}
		}

		void print(bool smart_update = false)
		{
			std::cout << ist::cursor_pos();

			for (size_t i = 0; i < this->size(); i++) {
				if (i == this->curs.row) {
					std::cout << i + 1 << ". ";

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
					std::cout << i + 1 << ". " << this->lines[i].content;

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
		inline std::vector<size_t> get_update_queue() const { return this->update_queue; }

		inline Line* operator[](size_t index) { return &this->lines[index]; }

		inline size_t size() const { return this->lines.size(); }

	private:
		inline void setup() {
			this->lines = std::vector<Line>({ Line("") });

			this->curs.row = 0;
			this->curs.col = 0;
		}

		inline void setup(file::Fileobj* file) {
			this->lines = to_line_obj(file->read());

			this->curs.row = this->size() - 1;
			this->curs._row = this->size();
			this->curs.col = this->lines[this->size() - 1].size();
		}

		std::vector<Line> lines;
		std::vector<size_t> update_queue;
		ist::cursor curs;

		CursorMovement cursor_mov;
	};
}