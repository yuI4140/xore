#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include<array>
#include <unordered_map>
#include <initializer_list>
namespace gc
{
    class Color {
    public:
        std::array<std::string, 14> mh_Red = {
          "#ffebee","#ffcdd2","#ef9a9a",
          "#e57373","#ef5350","#f44336",
          "#e53935","#d32f2f","#c62828",
          "#b71c1c","#ff8a80","#ff5252",
          "#ff1744","#d50000"
        };
        std::array<std::string, 14> mh_Pink = {
        "#fce4ec", "#f8bbd0", "#f48fb1",
        "#f06292", "#ec407a", "#e91e63",
        "#d81b60", "#c2185b", "#ad1457",
        "#880e4f", "#ff80ab", "#ff4081",
        "#f50057", "#c51162"
        };

        std::array<std::string, 14> mh_Purple = {
            "#f3e5f5","#e1bee7","#ce93d8",
            "#ba68c8","#ab47bc","#9c27b0",
            "#8e24aa","#7b1fa2","#6a1b9a",
            "#4a148c","#ea80fc","#e040fb",
            "#d500f9","#aa00ff"
        };
        std::array<std::string, 14> mh_deepPurple = {
            "#ede7f6","#d1c4e9","#b39ddb",
            "#9575cd","#7e57c2","#673ab7",
            "#5e35b1","#512da8","#4527a0",
            "#311b92","#b388ff","#7c4dff",
            "#651fff","#6200ea"
        };
        std::array<std::string, 14> mh_Indigo = {
            "#e8eaf6","#c5cae9","#9fa8da",
            "#7986cb","#5c6bc0","#3f51b5",
            "#3949ab","#303f9f","#283593",
            "#1a237e","#8c9eff","#536dfe",
            "#3d5afe","#304ffe"
        };
        std::array<std::string, 14> mh_Blue = {
            "#e3f2fd","#bbdefb","#90caf9",
            "#64b5f6","#42a5f5","#2196f3",
            "#1e88e5","#1976d2","#1565c0",
            "#0d47a1","#82b1ff","#448aff",
            "#2979ff","#2962ff"
        };

        std::array<std::string, 14> mh_lightBlue = {
        "#e1f5fe","#b3e5fc","#81d4fa",
        "#4fc3f7","#29b6f6","#03a9f4",
        "#039be5","#0288d1","#0277bd",
         "#01579bl","#80d8ff","#40c4ff",
         "#00b0ffl3","#0091ea"
        };
        std::array<std::string, 14> mh_Cyan = {
        "#e0f7fa","#b2ebf2","#80deea",
        "#4dd0e1","#26c6da","#00bcd4",
        "##00acc1","#0097a7","#00838f",
         "#006064","#84ffff","#18ffff",
         "#00e5ff","#00b8d4"
        };
        // from here to below are not set
        std::array<std::string, 14> mh_Teal = {
        "#fce4ec","f8bbd0","f48fb1",
        "#f06292","#ec407a","#e91e63",
        "#d81b60","#c2185b","#ad1457",
         "#880e4f","#ff80ab","#ff4081",
         "#f50057","#c51162"
        };
        std::array<std::string, 14> mh_Green = {
        "#fce4ec","f8bbd0","f48fb1",
        "#f06292","#ec407a","#e91e63",
        "#d81b60","#c2185b","#ad1457",
         "#880e4f","#ff80ab","#ff4081",
         "#f50057","#c51162"
        };
        std::array<std::string, 14> mh_lightGreen = {
        "#fce4ec","f8bbd0","f48fb1",
        "#f06292","#ec407a","#e91e63",
        "#d81b60","#c2185b","#ad1457",
         "#880e4f","#ff80ab","#ff4081",
         "#f50057","#c51162"
        };
        std::array<std::string, 14> mh_Lime = {
        "#fce4ec","f8bbd0","f48fb1",
        "#f06292","#ec407a","#e91e63",
        "#d81b60","#c2185b","#ad1457",
         "#880e4f","#ff80ab","#ff4081",
         "#f50057","#c51162"
        };
        std::array<std::string, 14> mh_Yellow = {
        "#fce4ec","f8bbd0","f48fb1",
        "#f06292","#ec407a","#e91e63",
        "#d81b60","#c2185b","#ad1457",
         "#880e4f","#ff80ab","#ff4081",
         "#f50057","#c51162"
        };
        std::array<std::string, 14> mh_Amber = {
            "#fce4ec","f8bbd0","f48fb1",
        "#f06292","#ec407a","#e91e63",
        "#d81b60","#c2185b","#ad1457",
         "#880e4f","#ff80ab","#ff4081",
         "#f50057","#c51162"
        };
        std::array<std::string, 14> mh_Orange = {
        "#fce4ec","f8bbd0","f48fb1",
        "#f06292","#ec407a","#e91e63",
        "#d81b60","#c2185b","#ad1457",
         "#880e4f","#ff80ab","#ff4081",
         "#f50057","#c51162"
        };
        std::array<std::string, 14> mh_deepOrange = {
        "#fce4ec","f8bbd0","f48fb1",
        "#f06292","#ec407a","#e91e63",
        "#d81b60","#c2185b","#ad1457",
         "#880e4f","#ff80ab","#ff4081",
         "#f50057","#c51162"
        };
        std::array<std::string, 14> mh_Brown = {
        "#fce4ec","f8bbd0","f48fb1",
        "#f06292","#ec407a","#e91e63",
        "#d81b60","#c2185b","#ad1457",
         "#880e4f","#ff80ab","#ff4081",
         "#f50057","#c51162"
        };
        std::array<std::string, 14> mh_Grey = {
        "#fce4ec","f8bbd0","f48fb1",
        "#f06292","#ec407a","#e91e63",
        "#d81b60","#c2185b","#ad1457",
         "#880e4f","#ff80ab","#ff4081",
         "#f50057","#c51162"
        };
        std::array<std::string, 14> mh_blueGrey = {
        "#fce4ec","f8bbd0","f48fb1",
        "#f06292","#ec407a","#e91e63",
        "#d81b60","#c2185b","#ad1457",
         "#880e4f","#ff80ab","#ff4081",
         "#f50057","#c51162"
        };
        void hex2rgb(std::string hex) {
            hex.erase(0, 1);
            r = strtoul(hex.substr(0, 2).c_str(), nullptr, 16);
            g = strtoul(hex.substr(2, 2).c_str(), nullptr, 16);
            b = strtoul(hex.substr(4, 2).c_str(), nullptr, 16);
        }
        int r, g, b;
    };
    class Graphics {
    public:
        Graphics(int width, int height): m_width(width), m_height(height) {
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