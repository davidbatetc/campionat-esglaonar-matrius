#include "console.hpp"

namespace console {
    const int CLEAR_SCREEN_LINES = 50;  // Number of blank lines in clear()
    const int MIN_ROWS_ALLOWED = 1;  // Minimum number of rows of a matrix
    const int MAX_ROWS_ALLOWED = 15;
    const int MIN_COLS_ALLOWED = 1;
    const int MAX_COLS_ALLOWED = 15;
    const int HEADER_BAR_LENGTH = 28;  // Length of the bar of the submenus

    // Outputs blank lines to clear the screen
    void clear() {
        for (int i = 0; i < CLEAR_SCREEN_LINES; ++i) cout << endl;
    }

    void cleanIstream(istream& is) {
        is.clear();
        is.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Waits for the user to press enter
    void wait() {
        cout << endl << "Press ENTER";
        cleanIstream(cin);
        string waitingString;
        getline(cin, waitingString);
        if (cin.eof()) exit(0);
    }

    // Welcomes the user to the program. Make sure you write your name if
    // you have been part of the development!
    void welcome() {
        cout << "═══════════════════════════════════════════════════"
            "══════════════════════" << endl;
        cout << " Welcome to the official program of the \"CAMPIONAT "
            "D'ESGLAONAR MATRIUS\"! " << endl;
        cout << "═══════════════════════════════════════════════════"
            "══════════════════════" << endl;
        cout << endl;

        // Make sure to add your name if you were part of it as well!
        cout << "This program has been developed by David Batet." << endl;
        cout << "Please report any bugs found to him." << endl;
        cout << "Source code available at https://github.com/davidbatetc/campionat-esglaonar-matrius" << endl;
        cout << endl;

        wait();
        clear();
    }

    // Checks if a string ends with ".mt"
    bool endsWithMT(const string& fileName) {
        int len = fileName.size();
        if (len < 3 or fileName[len - 3] != '.' or fileName[len - 2] != 'm' or
            fileName[len - 1] != 't') {

            cout << "Due to safety reasons, the file extension must always be \".mt\"." << endl;
            return false;
        }
        return true;
    }

    // Tries to get an integer between two integers
    // Returns false if unsuccessful
    bool getInput(int& n, int min, int max) {
        cin >> n;
        if (cin.eof()) exit(0);
        else if (cin.fail()) {
            cleanIstream(cin);
            return false;
        }
        else if (n < min or n > max) return false;
        return true;
    }

    // Tries to get a string equal to one of the strings in options
    // Returns false if unsuccessful
    bool getInput(string& s, const vector<string> options = {"y", "n"}) {
        cin >> s;
        if (cin.eof()) exit(0);
        else if (cin.fail()) {
            cleanIstream(cin);
            return false;
        }

        auto it = find(options.begin(), options.end(), s);
        if (it != options.end()) return true;
        return false;
    }

    // Tries to get the name of a file that can send data
    // Returns false if unsuccessful
    bool getFileForInput(string& fileName) {
        cin >> fileName;
        if (cin.eof()) exit(0);
        else if (cin.fail()) {
            cleanIstream(cin);
            return false;
        }

        if (not endsWithMT(fileName)) return false;

        ifstream is(fileName);
        if (is.is_open()) {
            int n;
            is >> n;
            if (is.fail()) {
                cleanIstream(is);
                cout << "\"" << fileName << "\"" << " is empty or invalid." << endl;
                return false;
            }
            return true;
        }

        cout << "Couldn't open \"" << fileName << "\"." << endl;
        return false;
    }

    // Tries to get the name of a file that can receive data
    // Returns false if unsuccessful
    bool getFileForOutput(string& fileName) {
        cin >> fileName;
        if (cin.eof()) exit(0);
        else if (cin.fail()) {
            cleanIstream(cin);
            return false;
        }

        if (not endsWithMT(fileName)) return false;

        ifstream is(fileName);
        if (is.is_open()) {
            string s;
            if (is >> s) {
                cout <<  "The file \"" << fileName << "\" already exists. Do"
                    " you want to overwrite it? (y/n): ";
                while (not getInput(s)) {
                    cout << "Invalid answer. Please try again." << endl << endl;
                    cout <<  "The file \"" << fileName << "\" already exists. Do"
                        " you want to overwrite it? (y/n): ";
                }

                if (s == "y") return true;
                else return false;
            }

            else return true;
        }

        ofstream os(fileName);
        if (os.is_open()) return true;
        return false;
    }

    // Reads a matrix and stores it in mat
    // mat is set to an empty matrix if unsuccessful
    bool getMatrixFromInput(matrix& mat) {
        string fileName;
        cout << "Name of the file with the matrix: ";
        while (not getFileForInput(fileName)) {
            cout << "Invalid file. Please try again." << endl << endl;
            cout << "Name of the file with the matrix: ";
        }

        ifstream is(fileName);
        mat = matrix(is, fileName);
        if (mat.getColSize() != 0) return true;
        return false;
    }

    // Saves a matrix in a file if the user agrees
    void saveMatrixInFile(const matrix& mat) {
        string s;
        cout << "Save matrix? (y/n): ";
        while (not getInput(s)) {
            cout << "Invalid answer. Please try again." << endl;
            cout << "Save matrix (y/n): ";
        }

        if (s == "y") {
            string fileName;
            cout << "Name of the output file: ";
            while (not getFileForOutput(fileName)) {
                cout << "Couldn't create or overwrite \"" << fileName << "\". Please try again." << endl << endl;
                cout << "Name of the output file: ";
            }

            ofstream os(fileName);
            os << mat.getColSize() << " " << mat.getRowSize() << endl << endl;
            os << mat << endl;
            cout << "Matrix successfully saved in \"" << fileName << "\"." << endl;
        }
    }

    // Displays the main menu of the program
    void displayMenu() {
        cout << "═══════════════════════" << endl;
        cout << "       MAIN MENU       " << endl;
        cout << "═══════════════════════" << endl;
        cout << endl;
        cout << "1. Generate matrix" << endl;
        cout << "2. Generate matrix with integer solutions" << endl;
        cout << "3. Input matrix to file" << endl;
        cout << "4. Reduce matrix" << endl;
        cout << "5. Compare matrices" << endl;
        cout << "6. Display matrix" << endl;
        cout << "7. Exit" << endl;        
        cout << endl;
        cout << "───────────────────────" << endl;
        cout << "Option: ";
    }

    // Displays the header of a submenu
    void displayHeader(const string& header) {
        clear();
        int len = header.size();
        int space = (HEADER_BAR_LENGTH - len)/2;
        if (space < 3) space = 3;

        for (int i = 0; i < HEADER_BAR_LENGTH; ++i) cout << "═";
        cout << endl;
        for (int i = 0; i < space; ++i) cout << ' ';
        cout << header;
        for (int i = 0; i < space; ++i) cout << ' ';
        cout << endl;
        for (int i = 0; i < HEADER_BAR_LENGTH; ++i) cout << "═";
        cout << endl;
    }

    // Handles the choice of submenu by the user
    void menu() {
        int option;

        displayMenu();
        while (not getInput(option, 1, 7)) {
            clear();
            displayMenu();
        }

        if (option == 1) genMatrix();
        else if (option == 2) genIntMatrix();
        else if (option == 3) inputMatrixToFile();
        else if (option == 4) reduceMatrix();
        else if (option == 5) compMatrices();
        else if (option == 6) displayMatrix();
        else if (option == 7) exit(0);
    }

    // Generates a random matrix with integer solutions and saves it the user wants to
    void genIntMatrix() {
        int m, n, z;
        displayHeader("Generate matrix");

        cout << "Number of rows = ";
        while (not getInput(m, MIN_ROWS_ALLOWED, MAX_ROWS_ALLOWED)) {
            cout << "Invalid input. Please try again." << endl << endl;
            cout << "Number of rows = ";
        }

        cout << "Number of columns " << "(min. " << m + 1 << ") = ";
        while (not getInput(n, m + 1, MAX_ROWS_ALLOWED)) {
            cout << "Invalid input. Please try again." << endl << endl;
            cout << "Number of columns " << "(min. " << m + 1 << ") = ";
        }

        cout << "Number of zeros " << "(max. " << m*(m + 1)/2 - 1 << ") = ";
        while (not getInput(z, 0, m*(m + 1)/2 - 1)) {
            cout << "Invalid input. Please try again." << endl << endl;
            cout << "Number of zeros " << "(max. " << m*(m + 1)/2 - 1 << ") = ";
        }

        cout << endl;
        matrix mat(m, n, z);

        cout << endl;
        cout << "Matrix:" << endl;
        cout << mat << endl;

        saveMatrixInFile(mat);

        wait();
        clear();
    }
	
    // Generates a random matrix and saves it the user wants to
    void genMatrix() {
        int m, n;
        displayHeader("Generate matrix");

        cout << "Number of rows = ";
        while (not getInput(m, MIN_ROWS_ALLOWED, MAX_ROWS_ALLOWED)) {
            cout << "Invalid input. Please try again." << endl << endl;
            cout << "Number of rows = ";
        }

        cout << "Number of columns = ";
        while (not getInput(n, MIN_ROWS_ALLOWED, MAX_ROWS_ALLOWED)) {
            cout << "Invalid input. Please try again." << endl << endl;
            cout << "Number of columns = ";
        }

        cout << endl;
        matrix mat(m, n);

        cout << endl;
        cout << "Matrix:" << endl;
        cout << mat << endl;

        saveMatrixInFile(mat);

        wait();
        clear();
    }
    
    void inputMatrixToFile() {
        displayHeader("Input matrix to file");

        cout << "Input the matrix in the correct format: " << endl << endl;
        matrix mat(cin);
        if (mat.getColSize() == 0) cleanIstream(cin);
        else {
            cout << endl;
            cout << mat << endl;
            saveMatrixInFile(mat);
        }

        wait();
        clear();
    }

    // Computes the reduced row echelon form of a matrix and
    // saves it if the user wants to
    void reduceMatrix() {
        displayHeader("Reduce matrix");

        matrix mat;
        getMatrixFromInput(mat);
        cout << endl;
        cout << "Original matrix: " << endl;
        cout << mat << endl;
        cout << "Reduced row echelon form of the matrix: " << endl;
        mat.reduce();
        cout << mat << endl;

        saveMatrixInFile(mat);

        wait();
        clear();
    }

    // Compares the reduced echelon form of two matrices from files
    void compMatrices() {
        displayHeader("Compare matrices");

        matrix mat1, mat2;
        getMatrixFromInput(mat1);
        getMatrixFromInput(mat2);

        cout << endl;
        cout << "Original matrix 1: " << endl;
        cout << mat1 << endl;
        cout << "Original matrix 2: " << endl;
        cout << mat2 << endl;
        cout << endl;

        mat1.reduce();
        mat2.reduce();
        if (mat1 == mat2) {
            cout << "The matrices have the same reduced row echelon form:" << endl;
            cout << mat1 << endl;
        }

        else {
            cout << "The matrices have different reduced row echelon forms: " << endl;
            cout << endl;
            cout << "Reduced row echelon form of matrix 1: " << endl;
            cout << mat1 << endl;
            cout << "Reduced row echelon form of matrix 2: " << endl;
            cout << mat2 << endl;
        }

        wait();
        clear();
    }

    // Displays the matrix in a file
    void displayMatrix() {
        displayHeader("Display matrix");

        matrix mat;
        getMatrixFromInput(mat);
        cout << mat << endl;

        wait();
        clear();
    }
}
