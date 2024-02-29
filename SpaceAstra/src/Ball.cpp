#include "raylib.h"
#include <vector>
#include <string>
#include "space_rendering.cpp"
#include "../physics_calculation2.cpp"
#include "../space_rendering2.cpp"

namespace afgcSolarSystem {
    class Canvas {
    public:
        int WindowHeight = 600;
        int WindowWidth = 800;

        std::vector<Ball> Balls;
        std::vector<Ball> BallsInitialValues;
        Physics::InertialFrameReference Engine;
        afgc::AfgcCamera Camera;
        Vector2 CameraTarget;
        int FontSize = Defaults::FontSize;
        bool IsPaused = false;
        int Margin = Defaults::Margin;
        Ball* SelectedBall = nullptr;
        bool SelectedFocus = false;
        Color TextColor = Defaults::colC64BackColor;
        int TextLocationY;

        Canvas() {
            TextLocationY = FontSize + (Margin / 2);
            Engine = Physics::InertialFrameReference();
            Camera = afgc::AfgcCamera(WindowWidth, WindowHeight);
        }

        void AddBall(double mass, double radius, double x, double y, double vx, double vy, Color color, std::string name) {
            Ball ball(Physics::BallMass{ mass, radius, Physics::Vector{ x, y }, Physics::Vector{ vx, vy } }, color, name);
            Balls.push_back(ball);
            BallsInitialValues.push_back(ball);
            Engine.AddBallMass(ball.BallMass);
        }

        void Render() {
            HandleInputs();

            if (!IsPaused) {
                Engine.DoPhysics();
            }

            Camera.Start();

            for (auto& ball : Balls) {
                ball.Render();
            }

            Camera.Target = CameraTarget;
            Camera.End();

            DrawInterface();
        }

    private:
        void DrawInterface() {
            DrawText(IsPaused ? "Paused" : "", Defaults::Margin, Defaults::Margin, Defaults::FontSize, Defaults::colC64BackColor);
            DrawText("[Spacebar - Pause][H - Show/Hide Name][F - Planet Focus]", Defaults::Margin, Defaults::WindowHeight - ((TextLocationY + Defaults::Margin) * 2), Defaults::FontSize, Defaults::colC64BackColor);
            DrawText("[R - Planet Reset][N - Next Planet][Mouse Wheel - Zoom]", Defaults::Margin, Defaults::WindowHeight - (TextLocationY + Defaults::Margin), Defaults::FontSize, Defaults::colC64BackColor);

            if (SelectedBall != nullptr) {
                DrawText(("Name: " + SelectedBall->Name).c_str(), Margin, TextLocationY * 2, FontSize, TextColor);
                DrawText(("Mass: " + std::to_string(SelectedBall->BallMass.Mass)).c_str(), Margin, TextLocationY * 3, FontSize, TextColor);
                DrawText(("Position: " + std::to_string(SelectedBall->BallMass.Position.x) + ", " + std::to_string(SelectedBall->BallMass.Position.y)).c_str(), Margin, TextLocationY * 4, FontSize, TextColor);
                DrawText(("Velocity: " + std::to_string(SelectedBall->BallMass.Velocity.x) + ", " + std::to_string(SelectedBall->BallMass.Velocity.y)).c_str(), Margin, TextLocationY * 5, FontSize, TextColor);
                DrawText(("Acceleration: " + std::to_string(SelectedBall->BallMass.Acceleration.x) + ", " + std::to_string(SelectedBall->BallMass.Acceleration.y)).c_str(), Margin, TextLocationY * 6, FontSize, TextColor);
            }
        }

        void HandleInputs() {
            if (IsKeyPressed(KEY_F)) {
                SelectedFocus = !SelectedFocus;
            }
            if (IsKeyPressed(KEY_SPACE)) {
                IsPaused = !IsPaused;
            }

            if (IsKeyPressed(KEY_N)) {
                int Index = 0;
                auto it = std::find_if(Balls.begin(), Balls.end(), [](const Ball& ball) { return ball.IsSelected == true; });
                if (it != Balls.end()) {
                    Index = std::distance(Balls.begin(), it) + 1;
                    it->IsSelected = false;
                }
                Index = Index > Balls.size() - 1 ? 0 : Index;
                Balls[Index].IsSelected = true;
                SelectedBall = &Balls[Index];
            }

            if (SelectedBall != nullptr && SelectedBall->Name.length() > 0) {
                if (IsKeyPressed(KEY_H)) {
                    SelectedBall->IsShowName = !SelectedBall->IsShowName;
                }
                if (IsKeyPressed(KEY_R)) {
                    auto it = std::find_if(BallsInitialValues.begin(), BallsInitialValues.end(), [&SelectedBall](const Ball& ball) { return ball.Name == SelectedBall->Name; });
                    if (it != BallsInitialValues.end()) {
                        SelectedBall->BallMass.Position = it->BallMass.Position;
                        SelectedBall->BallMass.Velocity = { 0, 0 };
                        SelectedBall->BallMass.Acceleration = { 0, 0 };
                    }
                }
                if (SelectedFocus) {
                    Camera.Target = { SelectedBall->Position[SelectedBall->CurrentIndex].x, SelectedBall->Position[SelectedBall->CurrentIndex].y };
                    Camera.Offset = { static_cast<float>(WindowWidth / 2), static_cast<float>(WindowHeight / 2) };
                }
                else {
                    Camera.Target = { 0, 0 };
                    Camera.Offset = { 0, 0 };
                }
            }
        }
    };
}
