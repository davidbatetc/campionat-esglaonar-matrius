#ifndef __RATIONAL_HPP__
#define __RATIONAL_HPP__

#include <iostream>
#include <string>

using namespace std;

class rational {
public:
    static long long gcd(long long a, long long b);

private:
    long long num, den;

public:
    rational();
    rational(long long n);
    rational(long long n, long long d);
    rational reduce();
    friend istream& operator>>(istream& is, rational& rat);
    friend ostream& operator<<(ostream& os, const rational& rat);
    friend rational operator+(const rational& rat1, const rational& rat2);
    friend rational operator-(const rational& rat);
    friend rational operator*(const rational& rat1, const rational& rat2);
    friend rational operator/(const rational& rat1, const rational& rat2);
    friend bool operator==(const rational& rat1, const rational& rat2);
    friend bool operator!=(const rational& rat1, const rational& rat2);
    friend bool operator>(const rational& rat1, const rational& rat2);
    friend bool operator<(const rational& rat1, const rational& rat2);
};

#endif  // __RATIONAL_HPP__
