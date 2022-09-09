/*
* 数独が正しいかチェックする
*/

bool checkSudokuSolution(const Vector<int> puzzle);

int main()
{
	Vector<int> values;
	
	values += 3, 9, 2, 4, 6, 5, 8, 1, 7;
	values += 7, 4, 1, 8, 9, 3, 6, 2, 5;
	values += 6, 8, 5, 2, 7, 1, 4, 3, 9;

	values += 2, 5, 4, 1, 3, 8, 7, 9, 6;
	values += 8, 3, 9, 6, 2, 7, 1, 5, 4;
	values += 1, 7, 6, 9, 5, 4, 2, 8, 3;

	values += 9, 6, 7, 5, 8, 2, 3, 4, 1;
	values += 4, 2, 3, 7, 1, 9, 5, 6, 8;
	values += 5, 1, 8, 3, 4, 6, 9, 7, 2;

	std::cout << std::boolalpha << checkSudokuSolution(values) << std::endl;
}


bool checkSudokuSolution(const Vector<int> puzzle)
{
	const int SIZE = 9;
	if (std::sqrt(puzzle.size()) != SIZE)
	{
		return false;
	}

	//	各行、各列が1 ~ 9で構成されているかどうか
	for (int i = 0; i < SIZE; ++i)
	{
		Vector<bool> vec(SIZE, false);
		for (int j = 0; j < SIZE; ++j)
		{
			int n = puzzle[i * SIZE + j] - 1;
			if (!vec[n])
			{
				vec[n] = true;
			}
			else
			{
				return false;
			}
		}
	}

	//	各3x3のブロックが1 ~ 9で構成されているかどうか
	const int DELTA = 27;
	const int MINI_SIZE = 3;
	for (int i = 0; i < MINI_SIZE; ++i)
	{
		for (int j = 0; j < MINI_SIZE; ++j)
		{
			//	一つの3x3ブロックについての処理
			Vector<bool> vec(SIZE, false);
			for (int x = 0; x < MINI_SIZE; ++x)
			{
				for (int y = 0; y < MINI_SIZE; ++y)
				{
					int startIdx = DELTA * i + MINI_SIZE * j;
					int n = puzzle[startIdx + SIZE * x + y] - 1;
					if (!vec[n])
					{
						vec[n] = true;
					}
					else
					{
						return false;
					}

				}
			}
		}
	}

	return true;
}
