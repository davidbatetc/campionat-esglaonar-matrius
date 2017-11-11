#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <limits>

#include "matrix.hpp"

namespace console {
    void clear();
    void wait();
    bool endsWithMT(const string& fileName);
    bool getInput(int& n, int min, int max);
    bool getInput(string& c, const vector<string>& options);
    bool getFileForInput(string& fileName);
    bool getFileForOutput(string& fileName);
    bool getMatrixFromInput(matrix& mat);
    void saveMatrixInFile(const matrix& mat);
    void welcome();
    void displayMenu();
    void menu();
    void genMatrix();
    void reduceMatrix();
    void compMatrices();
    void displayMatrix();
}

#endif // CONSOLE_HPP
