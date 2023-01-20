#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <unordered_map>
#include <initializer_list>
namespace core {
    // a matrix dataType that replace the classic C-style matrix
    class Matrix {
    public:
        // matrix constructor
        Matrix():rows(2), cols(2) { data = new double* [rows]; }
        Matrix(int rows, int cols, int matrix[][2]): rows(rows), cols(cols) {
            data = new double* [rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new double[cols];
                for (int j = 0; j < cols; j++)
                    data[i][j] = matrix[i][j];
            }
        }
        // overloading the matrix constructor
        Matrix(int rows, int cols): rows(rows), cols(cols) {
            data = new double* [rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new double[cols];
            }
        }
        // print matrix 
        void print() const {
            if (data != nullptr) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        std::cout << data[i][j] << " ";
                    }
                }
                std::cout << '\n';
            }
            else {
                std::cerr << "Error:Data pointers is empty or null " << "\n";
            }
        }
        // overloading matrix construction with initializer_list
        Matrix(std::initializer_list<std::initializer_list<double>> lst):
            rows(lst.size()), cols(lst.begin()->size()) {
            data = new double* [rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new double[cols];
            }

            int row = 0;
            for (auto& x : lst) {
                int col = 0;
                for (auto& y : x) {
                    data[row][col] = y;
                    col++;
                }
                row++;
            }
        }

        ~Matrix() {
            for (int i = 0; i < rows; i++) {
                delete[] data[i];
            }
            delete[] data;
        }
        // get rows
        int getRows() const {
            return rows;
        }
        // get columns
        int getCols() const {
            return cols;
        }
        // get total data of matrix
        double get(int row, int col) const {
            return data[row][col];
        }
        // set the total data of matrix
        void set(int row, int col, double value) {
            data[row][col] = value;
        }
        // fill the matrix with values
        void fill(double value) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    data[i][j] = value;
                }
            }
        }
        // get the max of matrix
        // the max of matrix is the sum of rows and cols
        int getMaxn() {
            return MAXN;
        }
        // get the current data of matrix
        std::vector<std::vector<double>> getData() const {
            std::vector<std::vector<double>> res(rows, std::vector<double>(cols));
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    res[i][j] = data[i][j];
                }
            }
            return res;
        }
        // override the '[]' operator for support matrix indexing
        double* operator[](int row) {
            return data[row];
        }
        // override (with const)the '[]' operator for support matrix indexing
        const double* operator[](int row) const {
            return data[row];
        }
        // inverse the matrix 
        Matrix inverse() {
            if (getRows() != 2 || getCols() != 2) {
                throw std::invalid_argument("Error: This function is only for 2x2 matrices");
            }
            // x=ad-bc
            // {{a,b},{c,d}}^-1={{d/x,c/x},{d/x,a/x}}
            auto val = getData();
            auto a = val[0][0];
            auto b = val[0][1];
            auto c = val[1][0];
            auto d = val[1][1];
            const double x = a * d - b * c;
            if (x == 0) {
                throw std::invalid_argument("Error: The matrix is not invertible");
            }
            core::Matrix new_matrix = { {d / x,c / x}, {b / x, a / x} };
            return new_matrix;
        }
    private:
        int rows;
        int cols;
        int MAXN = rows + cols;
        double** data;
    };
    void Sm2x2(Matrix& matrix, Matrix& equal) {
        using core::Matrix;
        try {
            auto m = matrix.inverse();
            auto datam = m.getData();
            auto eData = equal.getData();
            auto first = eData[0][0];
            auto second = eData[0][1];
            auto row1 = m[0][0] * (int)first + m[0][1] * (int)second;
            auto row2 = m[1][0] * (int)first + m[1][1] * (int)second;
            auto f0 = nullptr;
            //result.print();
        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    //A class that serves as an alternative to the built-in const char* 
    //data type, offering a variety of functions and transformations for
    // const char* and char* data types. This class can be used to manipulate
    //and operate on string data with more flexibility and efficiency. 
    //It also provides a more user-friendly interface for working with strings 
    //and characters. Additionally, this class has built-in memory management 
    //and error handling capabilities, making it a safer option 
    //for string manipulation in comparison to using raw pointers.
    class xchar {
    public:
        // costructor
        xchar(): data("\x00") {}
        // overload the constructor for support const char* dataType
        xchar(const char* ch): data(ch) {}
        // overload the constructor for support int dataType
        xchar(int i) {
            char buffer[10];
            snprintf(buffer, sizeof(buffer), "%d", i);
            data = buffer;
        }
        // support '<<' operator
        friend std::ostream& operator<<(std::ostream& os, const xchar& xc) {
            os << xc.data;
            return os;
        }
        // support '>>' operator
        friend std::istream& operator>>(std::istream& is, xchar& xc) {
            std::string temp;
            is >> temp;
            xc.data = new char[temp.length() + 1];
            std::strcpy(xc.to_char(xc.data), temp.c_str());
            return is;
        }
        // remove a character of xchar
        const char* remove(int index) {
            if (index < 0 || index > strlen(data)) return data;
            std::string str(data);
            str.erase(index, 1);
            return str.c_str();
        }
        // return the begin of xchar
        const char* begin() {
            return data;
        }
        // length of the xchar
        size_t charlen(const char* str) {
            size_t length = 0;
            while (*str++) {
                length++;
            }
            return length;
        }
        // override '+' operator for concatenation of xchars
        template<typename... Args>
        xchar operator+(const Args&... args) const {
            std::string result = std::string(data);
            (result += ... += std::string(args.data));
            return xchar(result.c_str());
        }
        xchar operator+(const xchar& rhs) const {
            std::string newString = data;
            newString += rhs.data;
            return xchar(newString.c_str());
        }
        xchar operator+(const char* rhs) const {
            std::string newString = data;
            newString += rhs;
            return xchar(newString.c_str());
        }
        // returns the end of the xchar
        const char* end() {
            return data + strlen(data);
        }
        // transform xchar to char
        char* Xcchar() {
            int len = charlen(data);
            char* cstr = new char[len + 1];
            strncpy(cstr, data, len);
            cstr[len] = '\0';
            return cstr;
        }//transform xchar to char(with param)
        char* Xcchar(xchar& xc) {
            int len = charlen(xc.data);
            char* cstr = new char[len + 1];
            strncpy(cstr, xc.data, len);
            cstr[len] = '\0';
            return cstr;
        }
        // const char* to char*
        char* to_char(const char* c_str) {
            int len = strlen(c_str);
            char* str = new char[len + 1];
            strcpy(str, c_str);
            return str;
        }
        // replace a character with another character 
        void replace(const char* new_data) {
        int len = charlen(data);
        char* temp = new char[len + 1];
        for (int i = 0; i < len; i++) {
            temp[i] = data[i];
        }
        temp[len] = '\0';
        data = temp;
        delete[] temp;
    }
    private:
        const char* data;
    };
}