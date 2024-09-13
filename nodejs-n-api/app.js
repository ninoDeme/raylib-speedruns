let raylib = require("./build/Release/addon.node");

raylib.InitWindow(500, 400, "Hello from Node.js! (napi)");

let bgColor = {
  r: 20,
  g: 27,
  b: 30,
  a: 255,
};
let red = {
  r: 255,
  g: 0,
  b: 0,
  a: 255,
};
let invertX = false;
let x = 0;
let invertY = false;
let y = 0;

while (!raylib.WindowShouldClose()) {
  raylib.BeginDrawing();
  raylib.ClearBackground(bgColor);
  x += 50 * (invertX ? -1 : 1) * raylib.GetFrameTime();
  if (x > raylib.GetScreenWidth() - 50) {
    invertX = true;
    x = 450;
  } else if (x < 0) {
    invertX = false;
    x = 0;
  }
  y += 50 * (invertY ? -1 : 1) * raylib.GetFrameTime();
  if (y > raylib.GetScreenHeight() - 50) {
    invertY = true;
    y = 350;
  } else if (y < 0) {
    invertY = false;
    y = 0;
  }
  if (raylib.IsMouseButtonDown(0)) {
    let pos = raylib.GetMousePosition();
    x = pos.x;
    y = pos.y;
  }
  raylib.DrawRectangle(x, y, 50, 50, red);
 raylib.DrawFPS(10, 10)
  raylib.EndDrawing();
}
