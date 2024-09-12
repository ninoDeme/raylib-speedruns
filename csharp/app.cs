using System;
using System.Runtime.InteropServices;

struct Color {
  public byte r, g, b, a;
  public Color(byte R, byte G, byte B, byte A) {
    r = R;
    g = G;
    b = B;
    a = A;
  }
}

struct Vector2 {
  public float x, y;
  public Vector2(float X, float Y) {
    x = X;
    y = Y;
  }
}

public class App
{
  // Probably a good idea to put these in its own class...
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
  [DllImport ("./raylib-5.0_linux_amd64/lib/libraylib.so")]
  private static extern bool IsMouseButtonDown(int button);
  [DllImport ("./raylib-5.0_linux_amd64/lib/libraylib.so")]
  private static extern Vector2 GetMousePosition();
  [DllImport ("./raylib-5.0_linux_amd64/lib/libraylib.so")]
  private static extern int GetScreenWidth();
  [DllImport ("./raylib-5.0_linux_amd64/lib/libraylib.so")]
  private static extern int GetScreenHeight();

  static int Main(string[] args)
  {
    InitWindow(500, 400, "Hello from C#!");
    Color red = new Color(255, 0, 0, 255);
    Color bgColor = new Color(20, 27, 30, 255);
    bool invertX = false;
    float x = 0;
    bool invertY = false;
    float y = 0;
    while (!WindowShouldClose()) {
      BeginDrawing();
      ClearBackground(bgColor);
      x += 50 * (invertX ? -1 : 1) * GetFrameTime();
      if (x > GetScreenWidth() - 50) {
        invertX = true;
        x = 450;
      } else if (x < 0) {
        invertX = false;
        x = 0;
      }
      y += 50 * (invertY ? -1 : 1) * GetFrameTime();
      if (y > GetScreenHeight() - 50) {
        invertY = true;
        y = 350;
      } else if (y < 0) {
        invertY = false;
        y = 0;
      }
      if (IsMouseButtonDown(0)) {
        Vector2 pos = GetMousePosition();
        x = pos.x;
        y = pos.y;
      }
      DrawRectangle((int) x, (int) y, 50, 50, red);
      EndDrawing();
    }
    return 0;
  }
}
