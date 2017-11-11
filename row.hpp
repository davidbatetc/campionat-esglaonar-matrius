#ifndef ROW_HPP
#define ROW_HPP

#include <vector>
#include <sstream>

#include "rational.hpp"

class row {
private:
    vector<rational> R;
    int n, pivot;

public:
    row();
    row(int n);
    row(int n, rational rat);
    int getPivotPos();
    void append(int m);
    void append(rational rat);
    rational operator[](int i) const;
    rational& operator[](int i);
    friend ostream& operator<<(ostream& os, const row& r);
    friend row operator+(const row& r1, const row& r2);
    friend row operator*(const rational& rat, const row& r);
    friend row operator/(const row& r, const rational& rat);
    friend bool operator==(const row& r1, const row& r2);
    friend bool operator!=(const row& r1, const row& r2);
};

#endif //ROW_HPP
