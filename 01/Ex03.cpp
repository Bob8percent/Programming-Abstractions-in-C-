
/*
    1から入力した数までの和を求めるプログラム
*/

#include <iostream>

int calcSum(int n);

int main()
{
    while (1)
    {
        int n = 0;
        std::cout << "入力：";
        std::cin >> n;

        std::cout << "1から" << n << "までの和：" << calcSum(n) << "\n";
    }

}

int calcSum(int n)
{
    return (n * (n + 1)) / 2;
}
