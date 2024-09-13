class Color {
  public byte r;
  public byte g;
  public byte b;
  public byte a;

  public Color(int R, int G, int B, int A) {
    this.r = (byte)R;
    this.g = (byte)G;
    this.b = (byte)B;
    this.a = (byte)A;
  }
  public Color(byte R, byte G, byte B, byte A) {
    this.r = R;
    this.g = G;
    this.b = B;
    this.a = A;
  }
}

class Vector2 {
  public float x, y;
  public Vector2(float X, float Y) {
    x = X;
    y = Y;
  }
}

public class App {

  static {
    System.loadLibrary("raylibjava");
  }

  public static void main(String[] args) {
    new App().main();
  }

  public void main() {
    InitWindow(500, 400, "Hello from Java!");
    Color bgColor = new Color(20, 27, 30, 255);
    Color red = new Color(255, 0, 0, 255);
    boolean invertX = false;
    float x = 0;
    boolean invertY = false;
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
      DrawRectangle((int)x, (int)y, 50, 50, red);
      DrawFPS(10, 10);
      EndDrawing();
    }
  }

  private native void InitWindow(int width, int height, String title);
  private native boolean WindowShouldClose();
  private native void BeginDrawing();
  private native void EndDrawing();
  private native float GetFrameTime();
  private native void DrawRectangle(int posX, int posY, int width, int height, Color color);
  private native void ClearBackground(Color color);
  private native boolean IsMouseButtonDown(int button);
  private native Vector2 GetMousePosition();
  private native int GetScreenWidth();
  private native int GetScreenHeight();
  private native int DrawFPS(int posX, int posY);
}
