
/*
    0が入力されるまで読み取り続け、
    入力されたときに一番目と二番目の最大値を表示し終了するプログラム
*/

#include <iostream>
#include <climits>

int main()
{
    const int sentinel = 0;

    int* maxFirst = nullptr;
    int* maxSecond = nullptr;

    while (1)
    {
        int n = INT_MIN;
        std::cout << "入力：";
        std::cin >> n;

        //  最初のステップ
        if (!maxFirst)
        {
            maxFirst = new int;
            *maxFirst = n;
        }

        //  考えられるパターンは
        //  1. *maxFirst < n
        //  2. *maxSecond < n < *maxFirst
        //  3. それ以外(更新必要ない)
        if (*maxFirst < n)
        {
            if (!maxSecond)
            {
                maxSecond = new int;
            }
            *maxSecond = *maxFirst;

            *maxFirst = n;
        }
        else if (n < *maxFirst)
        {
            if (maxSecond)
            {
                if (*maxSecond < n)
                {
                    *maxSecond = n;
                }
            }
            else
            {
                maxSecond = new int;
                *maxSecond = n;
            }
        }

        //  終了
        if (n == sentinel)
        {
            if (maxFirst)
            {
                std::cout << "1番目に大きい数：" << *maxFirst << "\n";
            }
            if (maxSecond)
            {
                std::cout << "2番目に大きい数：" << *maxSecond << "\n";
            }
            break;
        }
    }

}
