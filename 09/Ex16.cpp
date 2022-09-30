#define _USE_MATH_DEFINES

#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"

void findBoggleWords(const Vector<char>& board,
	Vector<std::string>& wordsFound, const Vector<std::string>& english);
void findBoggleWords(int x, int y, const int nEdge, std::string word, Vector<int>& isUsed, const Vector<char>& board,
	Vector<std::string>& wordsFound, const Vector<std::string>& english);

bool isValid(int x, int y, int nEdge, const Vector<int>& isUsed);

int main()
{
	std::ifstream ifs;
	ifs.open("EnglishWords.txt");
	if (ifs.fail())
	{
		std::cerr << "ファイルが読み込めません" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	Vector<std::string> english;
	std::string word;
	while (std::getline(ifs, word))
		english += word;

	Vector<char> board;
	board += 'X', 'C', 'E', 'R';
	board += 'I', 'M', 'G', 'A';
	board += 'N', 'O', 'M', 'L';
	board += 'G', 'Z', 'R', 'P';
	//board += 'R', 'C', 'E';
	//board += 'O', 'G', 'L';
	//board += 'N', 'O', 'A';
	Vector<std::string> wordsFound;
	findBoggleWords(board, wordsFound, english);

	//	apple以外表示されればOK
	for (int i = 0; i < wordsFound.size(); ++i)
	{
		std::cout << wordsFound[i] << " ";
	}
	std::cout << std::endl;
}

void findBoggleWords(const Vector<char>& board,
	Vector<std::string>& wordsFound, const Vector<std::string>& english)
{
	int n = (int)std::sqrt(board.size());
	if (n * n != board.size())return;

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			Vector<int> isUsed(n * n, 0);	//	-1のとき使用済み
			findBoggleWords(i, j, n, "", isUsed, board, wordsFound, english);
		}
}

void findBoggleWords(int x, int y, const int nEdge, std::string word, Vector<int>& isUsed, const Vector<char>& board,
	Vector<std::string>& wordsFound, const Vector<std::string>& english)
{
	//	TODO　:　計算量を減らすために、wordの文字数が、englishの単語の文字数の最大値を超えた場合は探索を停止する処理の実装
	if (!isValid(x, y, nEdge, isUsed))
	{
		//	単語検索
		for (int i = 0; i < english.size(); ++i)
		{
			if (word == english[i])
			{
				if (wordsFound.isEmpty() || wordsFound[wordsFound.size() - 1] != word)wordsFound += word;

				break;
			}
		}

		return;
	}

	int idx = x + nEdge * y;
	char ch = tolower(board[idx]);
	isUsed[idx] = -1;
	findBoggleWords(x + 1, y, nEdge, word + ch, isUsed, board, wordsFound, english);
	findBoggleWords(x, y + 1, nEdge, word + ch, isUsed, board, wordsFound, english);
	findBoggleWords(x - 1, y, nEdge, word + ch, isUsed, board, wordsFound, english);
	findBoggleWords(x, y - 1, nEdge, word + ch, isUsed, board, wordsFound, english);
	findBoggleWords(x + 1, y + 1, nEdge, word + ch, isUsed, board, wordsFound, english);
	findBoggleWords(x + 1, y - 1, nEdge, word + ch, isUsed, board, wordsFound, english);
	findBoggleWords(x - 1, y + 1, nEdge, word + ch, isUsed, board, wordsFound, english);
	findBoggleWords(x - 1, y - 1, nEdge, word + ch, isUsed, board, wordsFound, english);
	isUsed[idx] = 0;
}

bool isValid(int x, int y, int nEdge, const Vector<int>& isUsed)
{
	if (x < 0 || nEdge <= x || y < 0 || nEdge <= y)return false;
	
	return isUsed[x + nEdge * y] != -1;
}
