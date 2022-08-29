
/*
* 偶数の場合2で割り、奇数の場合3をかけて1を足す操作を、1になるまで繰り返すプログラム
*/

#include <iostream>
#include <climits>

int hailstoneSequence(int num);

int main()
{
    const int sentinel = 0;

    int count = 0;

    while (1)
    {
        int num = -1;
        do
        {
            std::cout << "入力：";
            std::cin >> num;
        } while (num < 0);

        if (num == sentinel)
        {
            break;
        }

        do
        {
            count++;
            num = hailstoneSequence(num);
        } while (num > 1);


        //  問題とは関係ないが…
        std::cout << "プロセスの回数：" << count << "\n";
        count = 0;
    }
}

int hailstoneSequence(int num)
{
    int result;

    if (num % 2)
    {
        //  奇数
        result = 3 * num + 1;
        std::cout << num << "は奇数なので、3をかけて1を足して" << result << "\n";
    }
    else
    {
        result = num / 2;
        std::cout << num << "は偶数なので、2で割って" << result << "\n";

    }

    return result;
}


