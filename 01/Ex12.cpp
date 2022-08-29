
/*
* 四分円の面積を長方形の集合に近似してpiの近似値を求めるプログラム
*/

#include <iostream>
#include <climits>

double quadrantArea(int n); //  n:分割回数

const double radius = 2.0;

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

        if (n == sentinel)
        {
            break;
        }

        std::cout << "値：" << quadrantArea(n) << "\n";
    }
}

double quadrantArea(int n)
{
    double x = 1.0 / n;         //  長方形のx座標(円の中心を原点とする)
    double sumArea = 0.0;
    const double w = 2.0 / n;   //  長方形の幅
    
    for (int i = 0; i < n; ++i)
    {
        double h = std::sqrt(radius * radius - x * x);
        sumArea += h * w;
        x += w;
    }

    return sumArea;
}
