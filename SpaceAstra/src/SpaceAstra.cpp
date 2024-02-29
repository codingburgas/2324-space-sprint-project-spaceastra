#include "raylib.h"
#include "space_rendering.cpp"
#include "Ball.cpp"

const int MainWindowHeight = Defaults::WindowHeight;
const int MainWindowWidth = Defaults::WindowWidth;

int main() {
    afgcSolarSystem::Canvas _canvas;
    _canvas.WindowWidth = MainWindowWidth;
    _canvas.WindowHeight = MainWindowHeight;

    int Middle = _canvas.WindowHeight / 2;
    int Center = _canvas.WindowWidth / 2;

    _canvas.AddBall(99, 25, Center, Middle, -0.0, 0.0, YELLOW, "Sun");

    _canvas.AddBall(0.01, 1, Center + 100 + 0, Middle, -0.06, +1.80, DARKBROWN, "Mercury");
    _canvas.AddBall(0.02, 3, Center + 100 + 50, Middle, -0.36, +1.35, GREEN, "Venus");
    _canvas.AddBall(0.02, 4, Center + 100 + 100, Middle, -0.36, +1.10, BLUE, "Earth");
    _canvas.AddBall(0.01, 2, Center + 100 + 150, Middle, -0.36, +1.00, RED, "Mars");
    _canvas.AddBall(0.09, 9, Center + 100 + 300, Middle, -0.20, +0.90, MAROON, "Jupiter");
    _canvas.AddBall(0.08, 8, Center + 100 + 400, Middle, -0.15, +0.70, SKYBLUE, "Saturn");
    _canvas.AddBall(0.06, 6, Center + 100 + 500, Middle, -0.13, +0.60, BROWN, "Uranus");
    _canvas.AddBall(0.05, 5, Center + 100 + 600, Middle, -0.08, +0.48, LIME, "Neptune");
    // Pluto is no longer a planet!
    //_canvasManager.AddBall(0.01, 1, Center + 100 + 900, Middle, -0.07, +0.07, PURPLE);

    InitWindow(_canvas.WindowWidth, _canvas.WindowHeight, "RLSolarSystem");
    SetTargetFPS(Defaults::FPS); // Comment/uncomment this line to get a less chaotic animation

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        _canvas.Render();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}