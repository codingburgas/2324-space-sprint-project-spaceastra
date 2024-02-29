#include "raylib.h"
#include <cmath>

namespace afgc {
    class AfgcCamera {
    public:
        int Width;
        int Height;
        Camera2D camera;

        AfgcCamera() {
            Initialize(GetScreenWidth(), GetScreenHeight());
        }

        AfgcCamera(int w, int h) {
            Initialize(w, h);
        }

        void Initialize(int w, int h) {
            Width = w;
            Height = h;
            camera.target = { static_cast<float>(Width) / 2, static_cast<float>(Height) / 2 };
            camera.offset = { 0, 0 };
            camera.rotation = 0.0f;
            camera.zoom = GetCamera2D().zoom;
        }

        void Start() {
            BeginMode2D(camera);
        }

        void End() {
            EndMode2D();
            Input();
        }

        void Input() {
            // Camera2D zoom controls
            camera.zoom += static_cast<float>(GetMouseWheelMove()) * GetCamera2D().zoom * 0.1f;

            if (camera.zoom > GetCamera2D().zoom * 3) camera.zoom = GetCamera2D().zoom * 3;
            else if (camera.zoom < GetCamera2D().zoom / 3) camera.zoom = GetCamera2D().zoom / 3;

            // Camera2D reset (zoom and rotation)
            if (IsKeyPressed(KEY_R)) {
                camera.zoom = GetCamera2D().zoom;
                camera.rotation = GetCamera2D().rotation;
            }
        }
    };
}