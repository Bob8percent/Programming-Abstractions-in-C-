//	gridをnRow*nColumnに成形する
//	新しく作った要素のデフォルト値は0とする＋行優先の成形
void reshape(Vector<int>& grid, int nRow, int nColumn, int defaultVal = 0);

int main()
{
	Vector<int> vec;
	vec += 1, 2, 3, 4;
	vec += 5, 6, 7, 8;
	vec += 9, 10, 11, 12;
	int defaultNRow = 3;
	int defaultNColumn = 4;
	for (int i = 0; i < defaultNRow; ++i)
	{
		for (int j = 0; j < defaultNColumn; ++j)
		{
			std::cout << std::setw(3) << vec[i * defaultNColumn + j];
		}
		std::cout << std::endl;
	}

	std::cout << ">>>" << std::endl;

	int nRow = 10;
	int nColumn = 15;
	reshape(vec, nRow, nColumn);

	for (int i = 0; i < nRow; ++i)
	{
		for (int j = 0; j < nColumn; ++j)
		{
			std::cout <<std::setw(3)<< vec[i * nColumn + j];
		}
		std::cout << std::endl;
	}
}

void reshape(Vector<int>& grid, int nRow, int nColumn, int defaultVal)
{
	if (grid.size() > nRow * nColumn)
	{
		for (int i = grid.size() - 1; i >= nRow * nColumn; --i)
		{
			grid.remove(i);
		}
		return;
	}

	for (int i = 0; i < nRow * nColumn; ++i)
	{
		if (grid.size() - 1 >= i)
		{
			grid += defaultVal;	//	デフォルト値を挿入
		}
	}
}
