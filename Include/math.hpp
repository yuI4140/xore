#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <initializer_list>
namespace math {
    class Matrix {
    public:
        Matrix():rows(2), cols(2) { data = new double* [rows]; }
        Matrix(int rows, int cols, int matrix[][2]): rows(rows), cols(cols) {
            data = new double* [rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new double[cols];
                for (int j = 0; j < cols; j++)
                    data[i][j] = matrix[i][j];
            }
        }
        Matrix(int rows, int cols): rows(rows), cols(cols) {
            data = new double* [rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new double[cols];
            }
        }
        void print() const {
            if (data!=nullptr) {
                for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    std::cout << data[i][j]<<" ";
                }
            }
                std::cout <<'\n';
            }
            else{
                std::cerr << "Error:Data pointers is empty or null " <<"\n";
            }
            }
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

        int getRows() const {
            return rows;
        }

        int getCols() const {
            return cols;
        }

        double get(int row, int col) const {
            return data[row][col];
        }

        void set(int row, int col, double value) {
            data[row][col] = value;
        }

        void fill(double value) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    data[i][j] = value;
                }
            }
        }
        int getMaxn() {
            return MAXN;
        }
        std::vector<std::vector<double>> getData() const {
            std::vector<std::vector<double>> res(rows, std::vector<double>(cols));
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    res[i][j] = data[i][j];
                }
            }
            return res;
        }
        double* operator[](int row) {
            return data[row];
        }
        const double* operator[](int row) const {
            return data[row];
        }
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
            math::Matrix new_matrix = { {d / x,c / x}, {b / x, a / x} };
            return new_matrix;
        }
    private:
        int rows;
        int cols;
        int MAXN = rows + cols;
        double** data;
    };
    void Solver2x2Matrix(Matrix& matrix,Matrix& equal) {
        using math::Matrix;
        try {
            auto m = matrix.inverse();
            auto datam = m.getData();
            auto eData = equal.getData();
            auto first=eData[0][0];
            auto second=eData[0][1];
            auto row1 = m[0][0] * (int)first + m[0][1] * (int)second;
            auto row2 = m[1][0] * (int)first + m[1][1] * (int)second;
            Matrix result = { {round(row1) + 1}, {round(row2)} };
            result.print();
        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
        }
    }
     
}