
/*
* 横軸を気温(華氏)、縦軸を風の強さ(mph)としたwindChill(=風の冷たさ)を計算するプログラム
*/

#include <iostream>
#include <iomanip>

int windChill(int t, int v);

int main()
{
	std::cout << "横軸を気温(華氏)、縦軸を風の強さ(mph)としたときのwindChill(=風の冷たさ)\n\n";

	std::cout << " Calm";
	for (int v = 0; v <= 60; v += 5)
	{
		//	縦軸ラベルの表示
		if (v != 0)
		{
			std::cout << std::setw(5) << v;
		}

		for (int t = 40; t >= -45; t -= 5)
		{
			if (v == 0)
			{
				//	横軸ラベルの表示
				std::cout << std::setw(5) << t;
			}
			else
			{
				std::cout << std::setw(5) << windChill(t, v);
			}
		}

		std::cout << "\n";
	}

}

//	t:気温, v：風の強さ
int windChill(int t, int v)
{
	//	風がない場合
	if (v <= 0)
	{
		return t;
	}

	//	気温が40℉を超えるとき
	if (t > 40)
	{
		std::cout << "気温が40℉を超えているので入力しなおしてください\n";
		return 0;
	}

	double k = std::pow(double(v), 0.16);
	double result = 35.74 + 0.6215 * t - 35.75 * k + 0.4275 * t * k;
	
	return int(result);
}
