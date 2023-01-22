#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <regex>
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
    //class that serves as an alternative to the built-in const char* 
    //data type offering a variety of functions and transformations 
    //for const char* and char* data typess.
    class xchar {
    public:
        // costructor
        xchar(): data("\x00") {}
        xchar(const xchar& other) {
            // Get the length of the data from the other xchar
            size_t len = charlen(other._data.get());
            // Allocate memory for the new data
            auto new_data = std::make_unique<const char[]>(len + 1);
            // Copy the data from the other xchar
            charncpy(new_data.get(), other._data.get(), len);
            // Add null terminator
            xchar xd1=new_data.get();
            xd1[len] = '\0';
            // Move the new data into the unique_ptr
            _data = std::move(xd1);
        }
          xchar& operator=(const xchar& other) {
        // Get the length of the data from the other xchar
        size_t len = charlen(other._data.get());
        // Allocate memory for the new data
        auto new_data = std::make_unique<const char*>(new char[len + 1]);
        // Copy the data from the other xchar
        charncpy(new_data.get(), other._data.get(), len);
        // Add null terminator
        new_data.get()[len] = '\0';
        // Move the new data into the unique_ptr
        _data = std::move(new_data);
        return *this;
    }
        void charncpy(const char* src, const char** dest, size_t n) {
            // Allocate memory for the new data
            *dest = new char[n + 1];
            // Copy the data from the source
            std::strncpy(*dest, src, n);
            // Add null terminator
            (*dest)[n] = '\0';
        }
        void charncpy(char* dest, const char* src, size_t num) {
            strncpy(dest, src, num);
        }

        void charncpy(const char** dest, const char* src, size_t num) {
            strncpy(*dest, src, num);
        }
        //Transform std::unique_ptr<char> into const char**
        const char** charptrToccharptr(std::unique_ptr<char>& ptr) {
            return const_cast<const char**>(&ptr.get());
        }
        // do the same as strncpy but with const char **
        void charncpy(const char** dest, const char** src, size_t num)
        {
            for (size_t i = 0; i < num; i++)
            {
                dest[i] = src[i];
            }
        }
        size_t charlen(const char** str) {
            size_t length = 0;
            while (**str++) {
                length++;
            }
            return length;
        }
        xchar(std::string str): _data(std::make_unique<const char*>(str.c_str())) {}
        // overload the constructor for support const char* dataType
        xchar(const char* ch):_data(std::make_unique<const char*>(ch)) {}
        // move assignment operator
        xchar& operator=(xchar&& other) noexcept {
            data = std::move(other.data);
            return *this;
        }
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
        // get the length of a const char*
        size_t charlen(const char* str) {
            size_t length = 0;
            while (*str++) {
                length++;
            }
            return length;
        }
        // get the length of the direct from xchar
        size_t xcharlen() {
            size_t length = 0;
            while (*data++) {
                length++;
            }
            return length;
        }
        template<typename... Args>
        // override '+' operator for concatenation of xchars
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
        // get the data/to const char* with noexcept
        const char* to_cchar()const noexcept { return data; }
        // returns the end of the xchar
        const char* end() {
            return data + strlen(data);
        }
        // transform xchar to char
        char* xcchar() {
            int len = charlen(data);
            char* cstr = new char[len + 1];
            strncpy(cstr, data, len);
            cstr[len] = '\0';
            return cstr;
        }//transform xchar to char(with param)
        char* xcchar(xchar& xc) {
            int len = charlen(xc.data);
            char* cstr = new char[len + 1];
            strncpy(cstr, xc.data, len);
            cstr[len] = '\0';
            return cstr;
        }
        // const char* to char*
        char* to_char(const char* c_str) noexcept {
            int len = strlen(c_str);
            char* str = new char[len + 1];
            strcpy(str, c_str);
            return str;
        }
        // transform xchar to string
        std::string to_string() noexcept {
            std::string str = data;
            return str;
        }
        // apend const char* to a specific index of the current xchar object's data
        void append(const char* str, int index) {
            if (index < 0 || index > charlen(data)) return;
            int len = charlen(str);
            int lenData = charlen(data);
            char* temp = new char[lenData + len + 1];
            strncpy(temp, data, index);
            strncpy(temp + index, str, len);
            strncpy(temp + index + len, data + index, lenData - index);
            temp[lenData + len] = '\0';
            data = temp;
        }
        // transform xchar to const char*
        const char* xconstchar() const {
            return data;
        }
        bool operator==(const xchar& rhs) const {
            return strcmp(data, rhs.data) == 0;
        }
        bool operator==(const char* rhs) const {
            return strcmp(data, rhs) == 0;
        }
        void replace(const char* willfind, const char* _new) {
            // Check if the input is valid
            if (willfind == nullptr || _new == nullptr) {
                std::cerr << "Error: Invalid input for replace()" << std::endl;
                return;
            }

            // Calculate the length of the old and new strings
            size_t oldlen = strlen(willfind);
            size_t newlen = strlen(_new);

            // Find the location of the old string in the data
            const char* found = std::strstr(data, willfind);
            if (found == nullptr) {
                std::cerr << "Error: String '" << willfind << "' not found in the data" << std::endl;
                return;
            }

            // Create a new char array to store the modified data
            char* new_data = new char[strlen(data) - oldlen + newlen + 1];
            char* current = new_data;

            // Copy the data before the found old string
            const char* before = data;
            while (before != found) {
                *current++ = *before++;
            }

            // Copy the new string
            for (size_t i = 0; i < newlen; i++) {
                *current++ = _new[i];
            }

            // Copy the data after the found old string
            const char* after = found + oldlen;
            while (*after) {
                *current++ = *after++;
            }

            // Add null terminator
            *current = '\0';

            // Delete the old data and set the data to the new modified data
            delete[] data;
            data = new_data;
        }
        // find the length of 'X' in the xchar data
        size_t find_len_of(const char* SEARCH) {
            size_t len = 0;
            xchar xdata = data;
            xchar xsearch = SEARCH;
            for (size_t i = 0; i < xdata.xcharlen(); i++) {
                if (xdata.data[i] == xsearch.data[i]) {
                    return i;
                }
            }
            return -1;
        }
        // find a const char* into data
        bool find(const char* regex) {
            std::regex pattern(regex);
            std::cmatch match;
            if (std::regex_search(data, match, pattern)) {
                return true;
            }
            return false;
        }
        //  remove a character from original xchar
        xchar subxchar(size_t start, size_t length) {
            if (start + length > strlen(data)) return xchar("");
            char* temp = new char[length + 1];
            strncpy(temp, data + start, length);
            temp[length] = '\0';
            return xchar(temp);
        }
        // override the operator '[]' for modify the string
        std::unique_ptr<char[]> operator[](size_t index) {
            if (index >= charlen(data)) {
                throw std::out_of_range("Index out of range");
            }
            else {
                std::unique_ptr<char[]> val(new char[1]);
                val[0] = data[index];
                return val;
            }
        }
        // insert from xchar
        void xinsert(int pos, const xchar& xdata) {
            int len = charlen(data);
            char* temp = new char[len + 2]; // + 2 to account for the additional character and the null terminator
            for (int i = 0; i < pos; i++) {
                temp[i] = data[i];
            }
            temp[pos] = xdata.data[0];
            for (int i = pos + 1; i <= len; i++) {
                temp[i] = data[i - 1];
            }
            data = temp;
            delete[] temp;
        }
    private:
        const char* data;
        std::unique_ptr<const char*> _data;
    };
    class fera {

    };
}