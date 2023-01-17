#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <initializer_list>
namespace core {
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
            auto f0 = NULL;
            //result.print();
        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    class Color {
        std::unordered_map<std::string, std::string> mh_Red = {
          {"r0","#ffebee"},{"r1","#ffcdd2"},{"r2","#ef9a9a"},
          {"r3","#e57373"},{"r4","#ef5350"},{"r5","#f44336"},
          {"r6","#e53935"},{"r7","#d32f2f"},{"r8","#c62828"},
          {"r9","#b71c1c"},{"r10","#ff8a80"},{"r11","#ff5252"},
          {"r12","#ff1744"},{"r13","#d50000"} };
        std::unordered_map<std::string, std::string> mh_Pink = {
           {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
           {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
           {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
           {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
           {"p12","#f50057"},{"p13","#c51162"} };
        std::unordered_map<std::string, std::string> mh_Purple = {
        {"p0","#f3e5f5"},{"p1","#e1bee7"},{"p2","#ce93d8"},
        {"p3","#ba68c8"},{"p4","#ab47bc"},{"p5","#9c27b0"},
        {"p6","#8e24aa"},{"p7","#7b1fa2"},{"p8","#6a1b9a"},
         {"p9","#4a148c"},{"p10","#ea80fc"},{"p11","#e040fb"},
         {"p12","#d500f9"},{"p13","#aa00ff"}
        };
        // from here to below are not set
        // dp is done up to dp3
        std::unordered_map<std::string, std::string> mh_deepPurple = {
        {"dp0","#ede7f6"},{"dp1","#d1c4e9"},{"dp2","#b39ddb"},
        {"dp3","#9575cd"},{"dp4","#ec407a"},{"dp5","#e91e63"},
        {"dp6","#d81b60"},{"dp7","#c2185b"},{"dp8","#ad1457"},
         {"dp9","#880e4f"},{"dp10","#ff80ab"},{"dp11","#ff4081"},
         {"dp12","#f50057"},{"dp13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_Indigo = {
        {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_Blue = {
        {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_lightBlue = {
        {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_Cyan = {
        {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_Teal = {
        {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_Green = {
        {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_lightGreen = {
        {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_Lime = {
        {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_Yellow = {
        {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_Amber = {
            {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_Orange = {
        {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_deepOrange = {
        {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_Brown = {
        {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_Grey = {
        {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        std::unordered_map<std::string, std::string> mh_blueGrey = {
        {"p0","#fce4ec"},{"p1","f8bbd0"},{"p2","f48fb1"},
        {"p3","#f06292"},{"p4","#ec407a"},{"p5","#e91e63"},
        {"p6","#d81b60"},{"p7","#c2185b"},{"p8","#ad1457"},
         {"p9","#880e4f"},{"p10","#ff80ab"},{"p11","#ff4081"},
         {"p12","#f50057"},{"p13","#c51162"}
        };
        
        
    };

}