
/*
    入力したmeterをinchとfeetに変換
*/

#include <iostream>

const double METERS_PER_INCH = 0.0254;
const double INCHES_PER_FOOT = 12.0;

double calcInches(double meters);
double calcFeet(double meters);

int main()
{
    double meters = 0.0f;

    while (1)
    {
        std::cout << "メートル距離を入力：";
        std::cin >> meters;

        std::cout << calcInches(meters) << "インチ\n";
        std::cout << calcFeet(meters) << "フィート\n";
    }

}

double calcInches(double meters)
{
    return meters / METERS_PER_INCH;
}

double calcFeet(double meters)
{
    return calcInches(meters) / INCHES_PER_FOOT;
}
