
/*
    入力した数だけ1から小さい順に奇数の和を計算するプログラム
*/

#include <iostream>

int calcSumOddNums(int n);

int main()
{
    while (1)
    {
        int n = 0;
        std::cout << "入力：";
        std::cin >> n;

        std::cout << n << "個の奇数の和：" << calcSumOddNums(n) << "\n";
    }

}

int calcSumOddNums(int n)
{
    int sum = 0;
    for (int i = 0, nextOdd = 1; nextOdd < 2 * n; ++i, nextOdd += 2)    //  可読性のためこの書き方("i","j"は基本的にカウンタであるべき)
    {
        sum += nextOdd;
    }

    return sum;
}
