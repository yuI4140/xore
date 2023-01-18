#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <unordered_map>
#include <initializer_list>
namespace gc
{
 class Color {
         public:
        std::unordered_map<std::string, std::string> mh_Red = {
          {"r0","#ffebee"},{"r1","#ffcdd2"},{"r2","#ef9a9a"},
          {"r3","#e57373"},{"r4","#ef5350"},{"r5","#f44336"},
          {"r6","#e53935"},{"r7","#d32f2f"},{"r8","#c62828"},
          {"r9","#b71c1c"},{"r10","#ff8a80"}    ,{"r11","#ff5252"},
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
        std::unordered_map<std::string, std::string> mh_deepPurple = {
        {"dp0","#ede7f6"},{"dp1","#d1c4e9"},{"dp2","#b39ddb"},
        {"dp3","#9575cd"},{"dp4","#7e57c2"},{"dp5","#673ab7"},
        {"dp6","#5e35b1"},{"dp7","#512da8"},{"dp8","#4527a0"},
         {"dp9","#311b92"},{"dp10","#b388ff"},{"dp11","#7c4dff"},
         {"dp12","#651fff"},{"dp13","#6200ea"}
        };
        std::unordered_map<std::string, std::string> mh_Indigo = {
        {"i0","#e8eaf6"},{"i1","#c5cae9"},{"i2","#9fa8da"},
        {"i3","#7986cb"},{"i4","#5c6bc0"},{"i5","#3f51b5"},
        {"i6","#3949ab"},{"i7","#303f9f"},{"i8","#283593"},
         {"i9","#1a237e"},{"i10","#8c9eff"},{"i11","#536dfe"},
         {"i12","#3d5afe"},{"i13","#304ffe"}
        };
        std::unordered_map<std::string, std::string> mh_Blue = {
        {"b0","#e3f2fd"},{"b1","#bbdefb"},{"b2","#90caf9"},
        {"b3","#64b5f6"},{"b4","#42a5f5"},{"b5","#2196f3"},
        {"b6","#1e88e5"},{"b7","#1976d2"},{"b8","#1565c0"},
         {"b9","#0d47a1"},{"b10","#82b1ff"},{"b11","#448aff"},
         {"b12","#2979ff"},{"b13","#2962ff"}
        };
        std::unordered_map<std::string, std::string> mh_lightBlue = {
        {"lb0","#e1f5fe"},{"lb1","#b3e5fc"},{"lb2","#81d4fa"},
        {"lb3","#4fc3f7"},{"lb4","#29b6f6"},{"lb5","#03a9f4"},
        {"lb6","#039be5"},{"lb7","#0288d1"},{"lb8","#0277bd"},
         {"lb9","#01579b"},{"lb10","#80d8ff"},{"lb11","#40c4ff"},
         {"lb12","#00b0ff"},{"lb13","#0091ea"}
        };
        // from here to below are not set
        std::unordered_map<std::string, std::string> mh_Cyan = {
        {"c0","#fce4ec"},{"c1","f8bbd0"},{"c2","f48fb1"},
        {"c3","#f06292"},{"c4","#ec407a"},{"c5","#e91e63"},
        {"c6","#d81b60"},{"c7","#c2185b"},{"c8","#ad1457"},
         {"c9","#880e4f"},{"c10","#ff80ab"},{"c11","#ff4081"},
         {"c12","#f50057"},{"c13","#c51162"}
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
    void hex2rgb(std::string hex) {
    hex.erase(0, 1);
    r = strtoul(hex.substr(0, 2).c_str(), nullptr, 16);
    g = strtoul(hex.substr(2, 2).c_str(), nullptr, 16);
    b = strtoul(hex.substr(4, 2).c_str(), nullptr, 16);
}
int r,g,b;};
class Graphics {
    public:
        Graphics(int width, int height) : m_width(width), m_height(height) {
            m_pixels.resize(width * height);
        }
     void setColor(const Color& color) {
            m_color = color;
        } 
        void DrawLine(int x1, int y1, int x2, int y2) {
            // use m_color to set the color for the line
            int dx = abs(x2 - x1);
            int dy = abs(y2 - y1);
            int sx = x1 < x2 ? 1 : -1;
            int sy = y1 < y2 ? 1 : -1;
            int err = dx - dy;

            while (true) {
                SetPixel(x1, y1, m_color.r, m_color.g, m_color.b);
                if (x1 == x2 && y1 == y2) break;
                int e2 = 2 * err;
                if (e2 > -dy) {
                    err -= dy;
                    x1 += sx;
                }
                if (e2 < dx) {
                    err += dx;
                    y1 += sy;
                }
            }
        }

        void SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
            if (x < 0 || x >= m_width || y < 0 || y >= m_height) return;
            int index = y * m_width + x;
            m_pixels[index] = (r << 16) | (g << 8) | b;
        }

        void Clear(unsigned char r, unsigned char g, unsigned char b) {
            for (int i = 0; i < m_width * m_height; i++) {
                m_pixels[i] = (r << 16) | (g << 8) | b;
            }
        }

        void DrawLine(int x1, int y1, int x2, int y2, const Color& color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    while (true) {
        SetPixel(x1, y1, color.r, color.g, color.b);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}


        void SaveToFile(const std::string& filename) {
            std::ofstream file(filename, std::ios::binary);
            file << "P6" << std::endl;
            file << m_width << " " << m_height << std::endl;
            file << "255" << std::endl;
            for (int i = 0; i < m_width * m_height; i++) {
                unsigned char r = (m_pixels[i] >> 16) & 0xff;
                unsigned char g = (m_pixels[i] >> 8) & 0xff;
                unsigned char b = m_pixels[i] & 0xff;
                file << r << g << b;
            }
            file.close();
        }

    private:
        int m_width;
        int m_height;
        std::vector<int> m_pixels;
        Color m_color;
};
} 