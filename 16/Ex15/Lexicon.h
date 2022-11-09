#pragma once
#include <string>

const int ALPHA_NUM = 26;

class Lexicon
{
public:
	struct Cell {
		char ch;	//	-1のときは文字なしとする
		Cell* link;
	};

	Lexicon() {
		root = nullptr;
	}

	~Lexicon() {
		clear();
	}

	//	小文字、大文字を区別しない
	void add(const std::string& word) {
		Cell** cp = &root;
		for (int i = 0; i <= word.length(); ++i) {
			if (!(*cp)) {
				*cp = new Cell[ALPHA_NUM + 1];	//	配列の末尾はyes/no(たどってきた文字列がその時点で存在するか)
				for (int k = 0; k <= ALPHA_NUM; ++k) {
					(*cp)[k].ch = -1;
					(*cp)[k].link = nullptr;
				}
			}
			if (i == word.length()) {
				(*cp)[ALPHA_NUM].ch = 1;
				break;
			}
			char ch = tolower(word.at(i));
			(*cp)[ch - 'a'].ch = ch;
			cp = &(*cp)[ch - 'a'].link;
		}
	}

	bool find(const std::string& word) const {
		Cell* cp = root;
		for (int i = 0; i <= word.length(); ++i) {
			if (!cp)return false;

			if (i == word.length()) {
				return cp[ALPHA_NUM].ch == 1;
			}

			char ch = tolower(word.at(i));
			if (ch == cp[ch - 'a'].ch) {
				cp = cp[ch - 'a'].link;
			}
			else return false;
		}
	}

	void clear() {
		clear(root);
	}

private:
	Cell* root;

	void clear(Cell* node) {

		for (int i = 0; i < ALPHA_NUM; ++i) {
			Cell* link = node[i].link;
			if (link) {
				clear(link);
			}
		}

		delete[] node;
		node = nullptr;
	}
};
