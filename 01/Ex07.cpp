
/*
* 入力された点数の平均値を求めるプログラム
*/

#include <iostream>
#include <climits>

double calcAverage(int sum, int num);

int main()
{
    const int sentinel = -1;    //  点数は0以上なので、不適なそれ以外の値を使う

    int sumScore = 0;
    int count = 0;

    while (1)
    {
        int score = -1;
        std::cout << "入力：";
        std::cin >> score;

        //  sentinelである-1以外の負の値は入力されない(点数データが正当である)と仮定する
        if (score == sentinel)
        {
            break;
        }

        ++count;
        sumScore += score;
    }

    std::cout << "これらの平均値：" << calcAverage(sumScore, count) << "\n";

}

double calcAverage(int sum, int num)
{
    return sum / (num * 1.0);
}
