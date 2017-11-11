#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <fstream>
#include <cctype>
#include <algorithm>

#include "row.hpp"

class matrix {
private:
    vector<row> M;
    int m, n;

public:
    matrix();
    matrix(int m, int n);
    matrix(const string& fileName);
    int getColSize() const;
    int getRowSize() const;
    void reduce();
    row operator[](int i) const;
    row& operator[](int i);
    friend ostream& operator<<(ostream& os, const matrix& mat);
    friend bool operator==(const matrix& mat1, const matrix& mat2);
};

#endif //MATRIX_HPP
