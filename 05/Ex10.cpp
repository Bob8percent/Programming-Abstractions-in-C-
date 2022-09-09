/*
* マインスイーパーの数字のチャート作成
*/

void fixCounts(const Vector<bool>& mines, const int raw, const int column, Vector<int>& counts);

int main()
{
	Vector<bool> mines;
	
	const bool T = true;
	const bool F = false;
	mines += T, F, F, F, F, T;
	mines += F, F, F, F, F, T;
	mines += T, T, F, T, F, T;
	mines += T, F, F, F, F, F;
	mines += F, F, T, F, F, F;
	mines += F, F, F, F, F, F;

	Vector<int> counts(mines.size(), 0);
	
	fixCounts(mines, 6, 6, counts);
}

void fixCounts(const Vector<bool>& mines, const int raw, const int column, Vector<int>& counts)
{
	if (raw * column != mines.size() || counts.size() != mines.size())
	{
		std::cout << "ERROR : void fixCounts(const Vector<bool>& mines, const int raw, const int column, Vector<int>& counts)"
			<< "引数が不適です" << std::endl;
		return;
	}

	for (int i = 0; i < raw; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			int sum = 0;
			int centerIdx = i * column + j;
			//	中央のグリッド
			sum += mines[centerIdx];
			//	左上
			if (i != 0 && j != 0)					sum += mines[centerIdx - column - 1];
			//	上
			if (i != 0)								sum += mines[centerIdx - column];
			//	右上
			if (i != 0 && j != (column - 1))		sum += mines[centerIdx - column + 1];
			//	左
			if (j != 0)								sum += mines[centerIdx - 1];
			//	右
			if (j != (column - 1))					sum += mines[centerIdx + 1];
			//	左下
			if (i != (raw - 1) && j != 0)			sum += mines[centerIdx + column - 1];
			//	下
			if (i != (raw - 1))						sum += mines[centerIdx + column];
			//	右下
			if (i != (raw - 1) && j != (column - 1))sum += mines[centerIdx + column + 1];

			counts[centerIdx] = sum;
		}
	}


	//	画面出力
	for (int i = 0; i < raw; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			std::cout << counts[i * column + j];
		}
		std::cout << std::endl;
	}
}
