#include "graphics.h"
using namespace gc;
class GameCore {
public:
GameCore(int width, int height) : m_graphics(width, height) {}

    void Run() {
        // Initialize game state, load assets, etc
        while (m_isRunning) {
            // Handle input
            // Update game state
            // Render graphics
            m_graphics.Clear(0, 0, 0);
            m_graphics.DrawLine(10, 10, 50, 50);
            m_graphics.SaveToFile("screenshot.ppm");
        }
    }

    void HandleInput() {
        // Handle input from user
    }

    void Update() {
        // Update game state
    }

private:
    bool m_isRunning = true;
    Graphics m_graphics;
};