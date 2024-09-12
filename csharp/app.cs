using System;
using System.Runtime.InteropServices;

struct Color {
  public byte R, G, B, A;
  public Color(byte r, byte g, byte b, byte a) {
    R = r;
    G = g;
    B = b;
    A = a;
  }
}

public class App
{
  [DllImport ("./raylib-5.0_linux_amd64/lib/libraylib.so")]
  private static extern void InitWindow(int width, int height, string title);
  [DllImport ("./raylib-5.0_linux_amd64/lib/libraylib.so")]
  private static extern bool WindowShouldClose();
  [DllImport ("./raylib-5.0_linux_amd64/lib/libraylib.so")]
  private static extern void BeginDrawing();
  [DllImport ("./raylib-5.0_linux_amd64/lib/libraylib.so")]
  private static extern void EndDrawing();
  [DllImport ("./raylib-5.0_linux_amd64/lib/libraylib.so")]
  private static extern float GetFrameTime();
  [DllImport ("./raylib-5.0_linux_amd64/lib/libraylib.so")]
  private static extern void ClearBackground(Color color);
  [DllImport ("./raylib-5.0_linux_amd64/lib/libraylib.so")]
  private static extern void DrawRectangle(int posX, int posY, int width, int height, Color color);

  static int Main(string[] args)
  {
    InitWindow(500, 400, "Hello World!");
    bool inverteX = false;
    float x = 0;
    bool inverteY = false;
    float y = 0;
    while (!WindowShouldClose()) {
      BeginDrawing();
      ClearBackground(new Color(10, 10, 10, 255));
      x += 50 * (inverteX ? -1 : 1) * GetFrameTime();
      if (x > 450) {
        inverteX = true;
        x = 450;
      } else if (x < 0) {
        inverteX = false;
        x = 0;
      }
      y += 50 * (inverteY ? -1 : 1) * GetFrameTime();
      if (y > 350) {
        inverteY = true;
        y = 350;
      } else if (y < 0) {
        inverteY = false;
        y = 0;
      }
      DrawRectangle((int)x, (int)y, 50, 50, new Color(255, 0, 0, 255));
      EndDrawing();
    }
    return 0;
  }
}
