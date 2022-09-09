/*
* 魔法陣かどうかを判断する
*/

bool isMagicSquare(const Vector<int> grid);

int main()
{
	Vector<int> values;
	//values += 16,	3,  2, 13;
	//values +=  5,  10, 11,  8;
	//values +=  9,   6,  7, 12;
	//values +=  4,  15, 14,  1;

	values += 8, 1, 6;
	values += 3, 5, 7;
	values += 4, 9, 2;

	std::cout << std::boolalpha << isMagicSquare(values) << std::endl;
}


bool isMagicSquare(const Vector<int> grid)
{
	int n = int(std::sqrt(grid.size()));
	if (n * n != grid.size())
	{
		return false;
	}

	//	行、列、対角線の数字の和
	Vector<int> rowSums(n, 0);
	Vector<int> columnSums(n, 0);
	Vector<int> diagonalSums(2, 0);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			rowSums[i] += grid[i * n + j];
			columnSums[i] += grid[j * n + i];
			if (i == j)
			{
				diagonalSums[0] += grid[i * n + j];
				diagonalSums[1] += grid[i * n + n - j - 1];
			}
		}
	}

	int sum = rowSums[0];
	for (int i = 0; i < n; ++i)
	{
		if (sum != rowSums[i] || sum != columnSums[i])
		{
			return false;
		}
	}
	if (sum != diagonalSums[0] || sum != diagonalSums[1])
	{
		return false;
	}

	return true;
}
