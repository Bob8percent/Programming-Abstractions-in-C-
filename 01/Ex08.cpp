
/*
* 入力された数の桁数を逆順にしたものを表示するプログラム
*/

#include <iostream>
#include <climits>

int reverseDigit(int num);

int main()
{
    const int sentinel = -1;    //  点数は0以上なので、不適なそれ以外の値を使う

    while (1)
    {
        int num = -1;
        std::cout << "入力：";
        std::cin >> num;

        //  sentinelである-1以外の負の値は入力されない(点数データが正当である)と仮定する
        if (num == sentinel)
        {
            break;
        }

        std::cout << "逆：" << reverseDigit(num) << "\n";
    }

}

int reverseDigit(int num)
{
    int result = 0;
    while (num > 0)
    {
        result = result * 10 + (num % 10);
        num /= 10;
    }

    return result;
}
