
/*
    入力した摂氏温度に対して、華氏温度を出力するプログラム
*/

#include <iostream>

double calcFahrenheit(double celsius);

int main()
{
    double celsius = 0.0;

    while (true)
    {
        std::cout << "摂氏温度を入力：";
        std::cin >> celsius;

        std::cout << calcFahrenheit(celsius) << std::endl;
    }
}

double calcFahrenheit(double celsius)
{
    return (1.8 * celsius + 32.0);
}

