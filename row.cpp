#include "row.hpp"

// Default constructor
row::row() : row(0) {}

// Constructs row with all of its elements set to 0
row::row(int n) : row(n, rational(0, 1)) {}

// Explicit constructor
row::row(int n, rational r) : n(n), pivot(0) {
    for (int i = 0; i < n; i++) {
        R.push_back(r);
    }
}

// Adds integer to the end of the row
void row::append(int m) {
    R.push_back(rational(m, 1));
    n++;
}

// Adds rational to the end of the row
void row::append(rational rat) {
    R.push_back(rat);
    n++;
}

// Returns the position of the pivot of the row
// Increments the value of the variable pivot
int row::getPivotPos() {
    while(pivot < n) {
        if (R[pivot] != rational(0)) return pivot;
        pivot++;
    }
    return -1;
}

rational row::operator[](int i) const {
    return R[i];
}

rational& row::operator[](int i) {
    return R[i];
}

ostream& operator<<(ostream& os, const row& r) {
    for (int i = 0; i < r.n; i++) os << r[i] << "\t";
    return os;
}

row operator+(const row& r1, const row& r2) {
    row r3;
    if (r1.n != r2.n) return row();
    for (int i = 0; i < r1.n; i++) r3.append(r1[i] + r2[i]);
    return r3;
}

row operator*(const rational& rat, const row& r1) {
    row r2;
    for (int i = 0; i < r1.n; i++) r2.append(rat*r1[i]);
    return r2;
}

row operator/(const row& r, const rational& rat) {
    return (1/rat)*r;
}

bool operator==(const row& r1, const row& r2) {
    if (r1.n != r2.n) return false;
    for (int i = 0; i < r1.n; i++) {
        if (r1[i] != r2[i]) return false;
    }
    return true;
}

bool operator!=(const row& r1, const row& r2) {
    return not (r1 == r2);
}
