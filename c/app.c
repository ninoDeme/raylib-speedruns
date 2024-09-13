#include "raylib.h"

int main(int argc, char *argv[])
{
  InitWindow(500, 400, "Hello from C!");
  Color bgColor = {20, 27, 30, 255};
  Color red = {255, 0, 0, 255};
  int invertX = 0;
  float x = 0;
  int invertY = 0;
  float y = 0;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(bgColor);
    x += 50 * (invertX ? -1 : 1) * GetFrameTime();
    if (x > GetScreenWidth() - 50) {
      invertX = 1;
      x = 450;
    } else if (x < 0) {
      invertX = 0;
      x = 0;
    }
    y += 50 * (invertY ? -1 : 1) * GetFrameTime();
    if (y > GetScreenHeight() - 50) {
      invertY = 1;
      y = 350;
    } else if (y < 0) {
      invertY = 0;
      y = 0;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 pos = GetMousePosition();
      x = pos.x;
      y = pos.y;
    }
    DrawRectangle((int)x, (int)y, 50, 50, red);
    DrawFPS(10, 10);
    EndDrawing();
  }
}
