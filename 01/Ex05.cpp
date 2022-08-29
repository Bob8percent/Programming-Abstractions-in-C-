
/*
    0が入力されるまで読み取り続け、入力されたときに最大値を表示し終了するプログラム
*/

#include <iostream>


int main()
{
    const int sentinel = 0;
     
  　int max = -1;   //  最大値は必ず0以上

    while (1)
    {
        int n = -1;
        std::cout << "入力：";
        std::cin >> n;

        if (max < n)
        {
            max = n;
        }

        if (n == sentinel)
        {
            std::cout << "最大値：" << max << "\n";
            break;
        }
    }

}
