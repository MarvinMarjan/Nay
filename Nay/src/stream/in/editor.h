#pragma once

#include "../../fileobj/fileobj.h"
#include "../in/input_handling.h"
#include "../in/keymap.h"
#include "line.h"

namespace ist
{
	class Editor
	{
	public:
		Editor(file::Fileobj file) {
			this->lines = to_line_obj(file.read());

			this->curs.row = this->size() - 1;
			this->curs.col = this->lines[this->size() - 1].size() - 1;
		}

		Editor(file::Fileobj* file) {
			this->lines = to_line_obj(file->read());

			this->curs.row = this->size() - 1;
			this->curs.col = this->lines[this->size() - 1].size() - 1;
		}

		Editor() {
			this->lines = std::vector<Line>({ Line("") });
			
			this->curs.row = 0;
			this->curs.col = 0;
		}

		inline void update(char ch)
		{
			std::cout << ist::cursor_pos(this->curs.row, this->curs.col);

			switch ((int)ch)
			{
			case ist::arrow_l:
				if (this->curs.col > 0) 
					this->curs.col--;
				break;

			case ist::arrow_r:
				if (this->curs.col < this->lines[this->curs.row].size())
					this->curs.col++;
				break;

			case ist::arrow_u:
				if (this->curs.row > 0) {
					this->curs.row--;

					if (this->curs.col >= this->lines[this->curs.row].size())
						this->curs.col = this->lines[this->curs.row].size();
				}

				break;

			case ist::arrow_d:
				if (this->curs.row + 1 < this->lines.size()) {
					this->curs.row++;

					if (this->curs.col >= this->lines[this->curs.row].size())
						this->curs.col = this->lines[this->curs.row].size();
				}

				break;
			}
		}

		void print()
		{
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

				else
					std::cout << i + 1 << ". " << this->lines[i].content;

				if (i + 1 < this->size())
					std::cout << std::endl;
			}
		}

		inline ist::cursor get_cursor() const { return this->curs; }

		inline Line* operator[](size_t index) { return &this->lines[index]; }

		inline size_t size() const { return this->lines.size(); }

	private:
		std::vector<Line> lines;
		ist::cursor curs;
	};
}