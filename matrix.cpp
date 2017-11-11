#include <cstdlib>
#include <ctime>

#include "matrix.hpp"

// Maximum absolute value of the random elements of the matrix
const int MAX_INT_ABS_VAL = 9;

// Default constructor
matrix::matrix() : m(0), n(0) {}

// Constructs matrix with random elements
matrix::matrix(int m, int n) : m(m), n(n) {
    srand(time(0));
    for (int i = 0; i < m; i++) {
        row r;
        for (int j = 0; j < n; j++) {
            r.append(rand() % (MAX_INT_ABS_VAL*2 + 1) - MAX_INT_ABS_VAL);
        }
        M.push_back(r);
    }
    cout << m << " x " << n << " matrix successfully generated." << endl;
}

// Constructs matrix from file
// Pre: file exists and can be accessed
matrix::matrix(const string& fileName) {
    ifstream in(fileName);
    if (not (in >> m >> n)) {
        cout << "Couldn't read matrix from \"" << fileName << "\"." << endl;
        m = 0;
        n = 0;
        return;
    }

    rational r;
    for (int i = 0; i < m; i++) {
        row s;
        for (int j = 0; j < n; j++) {
            in >> r;
            if (in.eof()) {
                in.clear();
                in.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Unexpected end of file while reading matrix in \""
                    << fileName << "\"." << endl;

                M = vector<row>();
                m = 0;
                n = 0;
                return;
            }
            else if (in.fail()) {
                in.clear();
                in.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "The matrix in \"" << fileName
                    << "\" is invalid. Please check the format of the input." << endl;

                M = vector<row>();
                m = 0;
                n = 0;
                return;
            }
            s.append(r);
        }
        M.push_back(s);
    }
}

// Returns the size of the columns
int matrix::getColSize() const {
    return m;
}

// Returs the size of the rows
int matrix::getRowSize() const {
    return n;
}

// Computes reduced row echelon form
void matrix::reduce() {
    int pRP = 0;  // pivotRowPosition
    for (int k = 0; k < n; k++) {
        int j = pRP - 1;
        while (++j < m and M[j][k] == rational(0));
        if (j < m) {
            swap(M[pRP], M[j]);
            M[pRP] = M[pRP]/M[pRP][k];
            for (int i = pRP + 1; i < m; i++) {
                M[i] = M[i] + (-M[i][k])*M[pRP];
            }
            pRP++;
        }
    }

    for (int k = m - 1; k >= 0; k--) {
        int pos = M[k].getPivotPos();
        for (int i = 0; i < k; i++) {
            M[i] = M[i] + (-M[i][pos])*M[k];
        }
    }
}

row matrix::operator[](int i) const {
    return M[i];
}

row& matrix::operator[](int i) {
    return M[i];
}

ostream& operator<<(ostream& os, const matrix& mat) {
    for (int i = 0; i < mat.m; i++) {
        os << mat[i] << endl;
    }
    return os;
}

bool operator==(const matrix& mat1, const matrix& mat2) {
    if (mat1.m != mat2.m) return false;
    for (int i = 0; i < mat1.m; i++) {
        if (mat1[i] != mat2[i]) return false;
    }
    return true;
}
