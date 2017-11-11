#include "rational.hpp"

long long rational::gcd(long long a, long long b) {
    if (b != 0) return gcd(b, a%b);
    else return a;
}

// Default constructor
rational::rational() : num(0), den(1) {}

// Integer constructor
rational::rational(long long n) : num(n), den(1) {}

// Explicit constructor
rational::rational(long long n, long long d) {
    long long gcd_ = gcd(n, d);
    num = n/gcd_;
    den = d/gcd_;
    if (den < 0 and num >= 0) {
        num = -num;
        den = -den;
    }
}

// Sets rational to its irreducible fraction
rational rational::reduce() {
    if (num == 0) {
        den = 1;
        return rational(num, den);
    }

    int gcd_ = gcd(num, den);
    num /= gcd_;
    den /= gcd_;
    return rational(num, den);
}

istream& operator>>(istream& is, rational& rat) {
    string s;
    if (is >> s) {
        size_t pos = s.find("/");

        if(pos == string::npos) {
            try {
                rat.num = stoll(s);
            }

            catch (...) {
                cout << "\"" << s << "\" is not a valid rational number." << endl;
                is.setstate(std::ios_base::failbit);
                return is;
            }

            rat.den = 1;
        }
        else {
            try {
                rat.num = stoll(s.substr(0, pos));
                rat.den = stoll(s.substr(pos + 1, string::npos));
            }

            catch (...) {
                cout << "\"" << s << "\" is not a valid rational number." << endl;
                is.setstate(std::ios_base::failbit);
            }

            rat.reduce();
        }
    }

    return is;
}

ostream& operator<<(ostream& os, const rational& rat) {
    if (rat.den == 1) {
        os << rat.num;
    }
    else {
        os << rat.num << "/" << rat.den;
    }
    return os;
}

rational operator+(const rational& rat1, const rational &rat2) {
    return rational(rat1.num*rat2.den + rat2.num*rat1.den,
        rat1.den*rat2.den);
}

rational operator-(const rational& rat) {
    return rational(-rat.num, rat.den);
}

rational operator*(const rational& rat1, const rational& rat2) {
    return rational(rat1.num*rat2.num, rat1.den*rat2.den);
}

rational operator/(const long long& z, const rational& rat) {
    return rational(rational(z)/rat);
}

rational operator/(const rational& rat1, const rational& rat2) {
    return rational(rat1.num*rat2.den, rat1.den*rat2.num);
}

bool operator==(const rational &rat1, const rational &rat2) {
    if(rat1.num == rat2.num and rat1.den == rat2.den) return true;
    return false;
}

bool operator!=(const rational &rat1, const rational &rat2) {
    return not (rat1 == rat2);
}
