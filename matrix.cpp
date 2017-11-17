#include <cstdlib>
#include <ctime>

#include "matrix.hpp"

// Maximum absolute value of the random elements of the matrix
const int MAX_INT_ABS_VAL = 9;

// Default constructor
matrix::matrix() : numberOfRows_(0), numberOfColumns_(0) {}

// Constructs matrix with random elements
matrix::matrix(int numberOfRows, int numberOfColumns) : numberOfRows_(numberOfRows), numberOfColumns_(numberOfColumns) {
    srand(time(0));
    for (int i = 0; i < numberOfRows_; i++) {
        row r;
        for (int j = 0; j < numberOfColumns_; j++) {
            r.append(rand() % (MAX_INT_ABS_VAL*2 + 1) - MAX_INT_ABS_VAL);
        }
        M_.push_back(r);
    }
    cout << numberOfRows_ << " x " << numberOfColumns_ << " matrix successfully generated." << endl;
}

// Constructs matrix from input stream
matrix::matrix(istream &is, const string& fileName) {
    int times = 1;
    while (times <= 2) {
        if (times == 1) is >> numberOfRows_;
        else is >> numberOfColumns_;

        if (is.eof()) {
            if (fileName == "terminal") exit(0);
            cout << "Unexpected end of input while reading matrix from \""
                << fileName << "\"." << endl;

            numberOfRows_ = 0;
            numberOfColumns_ = 0;
            return;
        }

        else if (is.fail()) {
            cout << "Couldn't read matrix from \"" << fileName << "\"." << endl;

            numberOfRows_ = 0;
            numberOfColumns_ = 0;
            return;
        }

        times++;
    }

    rational r;
    for (int i = 0; i < numberOfRows_; i++) {
        row s;
        for (int j = 0; j < numberOfColumns_; j++) {
            is >> r;
            if (is.eof()) {
                cout << "Unexpected end of input while reading matrix from \""
                    << fileName << "\"." << endl;

                if (fileName == "terminal") exit(0);

                M_ = vector<row>();
                numberOfRows_ = 0;
                numberOfColumns_ = 0;

                return;
            }

            else if (is.fail()) {
                M_ = vector<row>();
                numberOfRows_ = 0;
                numberOfColumns_ = 0;
                return;
            }

            s.append(r);
        }
        
        M_.push_back(s);
    }
}

// Returns the size of the columns
int matrix::getColSize() const {
    return numberOfRows_;
}

// Returs the size of the rows
int matrix::getRowSize() const {
    return numberOfColumns_;
}

// Computes reduced row echelon form
void matrix::reduce() {
    int pRP = 0;  // pivotRowPosition
    for (int k = 0; k < numberOfColumns_; k++) {
        int j = pRP - 1;
        while (++j < numberOfRows_ and M_[j][k] == 0);
        if (j < numberOfRows_) {
            swap(M_[pRP], M_[j]);
            M_[pRP] = M_[pRP]/M_[pRP][k];
            for (int i = pRP + 1; i < numberOfRows_; i++) {
                M_[i] = M_[i] + (-M_[i][k])*M_[pRP];
            }
            pRP++;
        }
    }

    for (int k = numberOfRows_ - 1; k >= 0; k--) {
        int pos = M_[k].getPivotPos();
        for (int i = 0; i < k; i++) {
            M_[i] = M_[i] + (-M_[i][pos])*M_[k];
        }
    }
}

row matrix::operator[](int i) const {
    return M_[i];
}

row& matrix::operator[](int i) {
    return M_[i];
}

ostream& operator<<(ostream& os, const matrix& mat) {
    for (int i = 0; i < mat.numberOfRows_; i++) {
        os << mat[i] << endl;
    }
    return os;
}

bool operator==(const matrix& mat1, const matrix& mat2) {
    if (mat1.numberOfRows_ != mat2.numberOfRows_) return false;
    for (int i = 0; i < mat1.numberOfRows_; i++) {
        if (mat1[i] != mat2[i]) return false;
    }
    return true;
}
