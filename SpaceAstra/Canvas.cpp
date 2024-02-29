#include <iostream>
#include <vector>
#include "physics_calculation3.cpp"
#include "physics_calculation2.cpp"
#include "src/space_rendering.cpp"

namespace afgcSolarSystem {
    class Canvas {
    private:
        int WindowHeight = 600;
        int WindowWidth = 800;
        std::vector<Ball> Balls;
        std::vector<Ball> BallsInitialValues;
        Physics::InertialFrameReference Engine;
        afgcCamera Camera;
        Physics::Vector CameraTarget;
        int FontSize = Defaults::FontSize;
        bool IsPaused = false;
        int Margin = Defaults::Margin;
        Ball* SelectedBall = nullptr;
        bool SelectedFocus = false;
        Color TextColor = Defaults::colC64BackColor;
        int TextLocationY;

    public:
        Canvas() {
            TextLocationY = FontSize + (Margin / 2);
            Camera = afgcCamera(WindowWidth, WindowHeight);
        }

        void AddBall(double mass, double radius, double x, double y, double vx, double vy, Color color, std::string name) {
            Ball ball = Ball(Physics::BallMass::BallMass(mass, radius, Physics::Vector::Vector(x, y), Physics::Vector::Vector(vx, vy)), color, name);
            Balls.push_back(ball);
            BallsInitialValues.push_back(ball);
            Engine.AddBallMass(ball.GetBallMass());
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
            // Draw interface elements when camera finishes
            DrawText(IsPaused ? "Paused" : "", Defaults::Margin, Defaults::Margin, Defaults::FontSize, Defaults::colC64BackColor);
            DrawText("[Spacebar - Pause][H - Show/Hide Name][F - Planet Focus]", Defaults::Margin, Defaults::WindowHeight - ((TextLocationY + Defaults::Margin) * 2), Defaults::FontSize, Defaults::colC64BackColor);
            DrawText("[R - Planet Reset][N - Next Planet][Mouse Wheel - Zoom]", Defaults::Margin, Defaults::WindowHeight - (TextLocationY + Defaults::Margin), Defaults::FontSize, Defaults::colC64BackColor);
            if (SelectedBall != nullptr) {
                DrawText("Name: " + SelectedBall->GetName(), Margin, TextLocationY * 2, FontSize, TextColor);
                DrawText("Mass: " + std::to_string(SelectedBall->GetBallMass().Mass), Margin, TextLocationY * 3, FontSize, TextColor);
                DrawText("Position: " + SelectedBall->GetBallMass().Position.ToString(), Margin, TextLocationY * 4, FontSize, TextColor);
                DrawText("Velocity: " + SelectedBall->GetBallMass().Velocity.ToString(), Margin, TextLocationY * 5, FontSize, TextColor);
                DrawText("Acceleration: " + SelectedBall->GetBallMass().Acceleration.ToString(), Margin, TextLocationY * 6, FontSize, TextColor);
            }
        }

        void HandleInputs() {
            if (IsKeyPressed(KeyboardKey::KEY_F)) {
                SelectedFocus = !SelectedFocus;
            }
            if (IsKeyPressed(KeyboardKey::KEY_SPACE)) {
                IsPaused = !IsPaused;
            }

            if (IsKeyPressed(KeyboardKey::KEY_N)) {
                int Index = 0;
                auto it = std::find_if(Balls.begin(), Balls.end(), [](const Ball& ball) { return ball.IsSelected(); });
                if (it != Balls.end()) {
                    Index = std::distance(Balls.begin(), it) + 1;
                    it->SetSelected(false);
                }
                Index = Index > Balls.size() - 1 ? 0 : Index;
                Balls[Index].SetSelected(true);
                SelectedBall = &Balls[Index];
            }

            if (SelectedBall != nullptr && !SelectedBall->GetName().empty()) {
                if (IsKeyPressed(KeyboardKey::KEY_H)) {
                    SelectedBall->SetShowName(!SelectedBall->IsShowName());
                }
                if (IsKeyPressed(KeyboardKey::KEY_R)) {
                    auto it = std::find_if(BallsInitialValues.begin(), BallsInitialValues.end(), [selectedBallName = SelectedBall->GetName()](const Ball& ball) { return ball.GetName() == selectedBallName; });
                    if (it != BallsInitialValues.end()) {
                        SelectedBall->GetBallMass().SetPosition(it->GetBallMass().Position);
                        SelectedBall->GetBallMass().SetVelocity(Physics::Vector::Vector(0, 0));
                        SelectedBall->GetBallMass().SetAcceleration(Physics::Vector::Vector(0, 0));
                    }
                }
                if (SelectedFocus) {
                    CameraTarget = Physics::Vector::Vector(SelectedBall->GetPosition()[SelectedBall->GetCurrentIndex()].X, SelectedBall->GetPosition()[SelectedBall->GetCurrentIndex()].Y);
                    Camera.SetOffset(Physics::Vector::Vector(WindowWidth / 2, WindowHeight / 2));
                }
                else {
                    CameraTarget = Physics::Vector::Vector(0, 0);
                    Camera.SetOffset(Physics::Vector::Vector(0, 0));
                }
            }
        }
    };
}