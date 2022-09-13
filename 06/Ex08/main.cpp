
#include <iostream>
#include "Rational.h"

const std::string HEADER = "CS106B Programming Abstractions in C++: Ex 6.8\n";
const std::string DETAIL = "Extending Rational Numbers Class";
const std::string BANNER = HEADER + DETAIL;

int main(int argc, char* argv[])
{

    std::cout << BANNER << std::endl << std::endl;

    Rational oneHalf(1, 2);
    Rational oneHalfPrime(1, 2);

    Rational oneThird(1, 3);
    Rational oneSixth(1, 6);

    Rational sum = oneHalf + oneThird + oneSixth;

    std::cout << oneHalf << " + " << oneThird << " + " << oneSixth << " = ";
    std::cout << sum << std::endl;

    bool same = (oneHalf == oneThird);
    std::cout << "Is " << oneHalf << " == " << oneThird << " ? " << same;
    std::cout << std::endl;

    same = (oneHalf == oneHalfPrime);
    std::cout << "Is " << oneHalf << " == " << oneHalfPrime << " ? " << same;
    std::cout << std::endl;

    bool different = (oneHalf != oneThird);
    std::cout << "Is " << oneHalf << " != " << oneThird << " ? " << different;
    std::cout << std::endl;

    different = (oneHalf != oneHalfPrime);
    std::cout << "Is " << oneHalf << " != " << oneHalfPrime << " ? " << different;
    std::cout << std::endl;

    std::cout << (sum += ++oneHalf) << std::endl;
    std::cout << oneHalf++ << std::endl;
    std::cout << oneHalf-- << std::endl;
    std::cout << oneHalf << std::endl;
    std::cout << --oneHalf << std::endl;
    std::cout << oneHalf << std::endl;

    return 0;
}
