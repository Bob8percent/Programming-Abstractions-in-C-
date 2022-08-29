
/*
* ライブニッツ級数を第n項まで計算するプログラム
*/

#include <iostream>
#include <climits>

double leibniz(int n);

int main()
{
    const int sentinel = 0;

    int count = 0;

    while (1)
    {
        int n = 0;
        do
        {
            std::cout << "入力：";
            std::cin >> n;
        } while (n <= 0);

        std::cout << "値：" << leibniz(n) << "\n";
    }
}

double leibniz(int n)
{
    double result = 0.0;
    for (int i = 0; i < n; ++i)
    {
        int coefficient = (i % 2) ? -1 : 1;

        result += coefficient / (2 * i + 1.0);
    }
    
    return result;
}
