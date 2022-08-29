
/*
* 素因数分解
*/

#include <iostream>
#include <climits>

int main()
{
    const int sentinel = 0;

    while (1)
    {
        int num = -1;
        std::cout << "入力：";
        std::cin >> num;

        if (num < sentinel)
        {
            continue;
        }
        else if (num == 1)
        {
            std::cout << num << "\n";
            continue;
        }
        else if (num == 0)
        {
            break;
        }

        bool isFirst = true;
        int dividend = num;

        for (int divisor = 2; divisor <= num; ++divisor)
        {
            while (dividend % divisor == 0)
            {
                if (!isFirst)   //  出力文字列をstd::string型変数に格納して、この条件式を"文字数0の時"とする方針もよさそう
                {
                    std::cout << " x ";
                }
                isFirst = false;

                std::cout << divisor;
                dividend /= divisor;
            }
        }

        std::cout << "\n";
    }

}

