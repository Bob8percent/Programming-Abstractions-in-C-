
void chainReactionSimulation();

int main()
{
	chainReactionSimulation();
}

void chainReactionSimulation()
{
	const int nRow = 25;
	const int nColumn = 25;
	Vector<bool> traps(nRow * nColumn, false);
	const int minDelta = 1;
	const int maxDelta = 4;
	const int nBalls = 2;

	int time = 0;
	int maxAirBalls = 0;
	Vector<int> balls;

	int startPos = randInteger(0, nRow - 1) * nColumn + randomInteger(0, nColumn - 1);
	traps[startPos] = true;
	balls.add(randInteger(minDelta, maxDelta));
	balls.add(randInteger(minDelta, maxDelta));
	while (1)
	{
		if (maxAirBalls < balls.size())	maxAirBalls = balls.size();
		if (balls.isEmpty())break;

		Vector<int> nextBalls;
		for (int i = balls.size()-1; i >=0; --i)
		{
			if (--balls[i] <= 0)
			{
				//	着地
				int landPos = randInteger(0, nRow - 1) * nColumn + randomInteger(0, nColumn - 1);
				if (!traps[landPos])
				{
					//	未発射のネズミ捕りに当たった場合
					nextBalls.add(randInteger(minDelta, maxDelta));
					nextBalls.add(randInteger(minDelta, maxDelta));
					traps[landPos] = true;
				}
				balls.remove(i);
			}
		}
		balls += nextBalls;

		++time;
	}

	int count = 0;
	for (int i = 0; i < traps.size(); ++i)
	{
		if (traps[i])++count;
	}
	std::cout << "単位時間数：" << time << std::endl
		<< "跳ね上げられたトラップの割合：" << count / double(traps.size()) << std::endl
		<< "空中ボールの最大数：" << maxAirBalls << std::endl;
}
