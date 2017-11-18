#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <fstream>
#include <cctype>
#include <algorithm>

#include "row.hpp"

class matrix {
private:
    vector<row> M_;
    int numberOfRows_, numberOfColumns_;
    bool linear_comb(vector<row>& mat, const vector<row>& sol, int x, int y, rational n);

public:
    matrix();
    matrix(int m, int n);
    matrix(int m, int n, int z);
    matrix(istream& is, const string& fileName = "terminal");
    int getColSize() const;
    int getRowSize() const;
    void reduce();
    row operator[](int i) const;
    row& operator[](int i);
    friend ostream& operator<<(ostream& os, const matrix& mat);
    friend bool operator==(const matrix& mat1, const matrix& mat2);
};

#endif  // __MATRIX_HPP__
