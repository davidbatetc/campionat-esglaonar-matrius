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

// Constructs matrix from input stream
matrix::matrix(istream &is, const string& fileName) {
    int times = 1;
    while (times <= 2) {
        if (times == 1) is >> m;
        else is >> n;

        if (is.eof()) {
            if (fileName == "terminal") exit(0);
            cout << "Unexpected end of input while reading matrix from \""
                << fileName << "\"." << endl;

            m = 0;
            n = 0;
            return;
        }

        else if (is.fail()) {
            cout << "Couldn't read matrix from \"" << fileName << "\"." << endl;

            m = 0;
            n = 0;
            return;
        }

        times++;
    }

    rational r;
    for (int i = 0; i < m; i++) {
        row s;
        for (int j = 0; j < n; j++) {
            is >> r;
            if (is.eof()) {
                cout << "Unexpected end of input while reading matrix from \""
                    << fileName << "\"." << endl;

                if (fileName == "terminal") exit(0);

                M = vector<row>();
                m = 0;
                n = 0;

                return;
            }

            else if (is.fail()) {
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
        //Set j in initial position after pivot
        int j = pRP + 1; 
        
        //If j element is not a zero, go down until its found
        while (j < m and M[j][k] == rational(0)) j++;
        
        if (j < m) {
        	//Permute rows of pivot and j
            swap(M[pRP], M[j]);
            //Get a 1 at the left-most position of row
            M[pRP] = M[pRP]/M[pRP][k]; 
            
            //Iterate in all the rows below the pivot row
            for (int i = pRP + 1; i < m; i++) {
            	//Substract the new pivot row in the rows below
                M[i] = M[i] + (-M[i][k])*M[pRP];
            }
            
            //Set the pivot row the next one
            pRP++;
        }
    }
	
	//Now that we have 1s at the left-most position of each row,
	//we can go upward erasing all numbers above the ones
	//Example of row: 0 0 0 1 2 384/17 12 9 -12 -2
    for (int k = m - 1; k >= 0; k--) {
        //Get the position of the pivot
        int pos = M[k].getPivotPos();
        
        for (int i = 0; i < k; i++) {
        	//Change all the numbers above the ones to zeros
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
