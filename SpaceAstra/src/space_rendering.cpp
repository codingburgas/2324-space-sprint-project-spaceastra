#include "raylib.h"
#include <ctime>
#include <iostream>
#include <vector>

struct Defaults {
    static int _id;
    static bool Autosize;
    static Color BackColor;
    static float BlockSize;
    static Color BorderColor;
    static int BorderSize;
    static float Camera2dRotation, Camera2dZoom, Camera2dZoomIncrement, Camera2dZoomMax, Camera2dZoomMin;
    static Color colAlphaGrey;
    static Color colAlphaRed;
    static Color colC64BackColor;
    static Color colC64FrontColor;
    static Color ControlFontColor;
    static int ControlFontSize, FontSize;
    static Font Font;
    static float FontSpacing;
    static int FPS;
    static Vector2 GravityVector;
    static bool IsDebugRecVisible;
    static int KeyCanRepeat[300];
    static int KeyRepeatThreshhold;
    static int Margin;
    static int Padding;
    static Vector2 StopVector;
    static int TextMaxChars;
    static int WindowHeight;
    static int WindowWidth;
    static int _tick;

    static int ControlId() {
        _id++;
        return _id;
    }

    static char Cursor() {
        char _ = std::time(nullptr) % 2 != 0 ? '_' : ' ';
        return _;
    }

    static bool IsNowOdd() {
        return std::time(nullptr) % 2 != 0;
    }

    static bool IsTickOdd() {
        return _tick % 2 != 0;
    }

    static int Tick() {
        _tick++;
        return _tick;
    }

    static bool IsKeyCanRepeat(KeyboardKey key) {
        int k = (int)key;
        if (KeyCanRepeat[k] > KeyRepeatThreshhold) {
            KeyCanRepeat[k] = 0;
        }
        else {
            KeyCanRepeat[k]++;
        }
        return KeyCanRepeat[k] == 0;
    }
};

// Initialization of static members
int Defaults::_id = 0;
bool Defaults::Autosize = false;
Color Defaults::BackColor = LIGHTGRAY;
float Defaults::BlockSize = 4;
Color Defaults::BorderColor = DARKGRAY;
int Defaults::BorderSize = 2;
float Defaults::Camera2dRotation = 0.0f;
float Defaults::Camera2dZoom = 1.0f;
float Defaults::Camera2dZoomIncrement = 0.05f;
float Defaults::Camera2dZoomMax = 20.0f;
float Defaults::Camera2dZoomMin = 0.1f;
Color Defaults::colAlphaGrey = Color{ 200, 200, 200, 250 };
Color Defaults::colAlphaRed = Color{ 255, 0, 0, 250 };
Color Defaults::colC64BackColor = Color{ 73, 73, 193, 255 };
Color Defaults::colC64FrontColor = Color{ 183, 183, 255, 255 };
Color Defaults::ControlFontColor = RED;
int Defaults::ControlFontSize = 20;
Font Defaults::Font = GetFontDefault();
int Defaults::FontSize = 20;
float Defaults::FontSpacing = 2.00f;
int Defaults::FPS = 120;
Vector2 Defaults::GravityVector = Vector2{ 0, 1.0f };
bool Defaults::IsDebugRecVisible = false;
int Defaults::KeyCanRepeat[300] = {};
int Defaults::KeyRepeatThreshhold = 10;
int Defaults::Margin = 1;
int Defaults::Padding = 0;
Vector2 Defaults::StopVector = Vector2{ 0, 0 };
int Defaults::TextMaxChars = 255;
int Defaults::WindowHeight = 900;
int Defaults::WindowWidth = 1600;
int Defaults::_tick = 0;