const CColor = { struct: ["u8", "u8", "u8", "u8"] };
const CVector2 = { struct: ["f32", "f32"] };

const raylib = Deno.dlopen("./raylib-5.0_linux_amd64/lib/libraylib.so", {
  InitWindow: { parameters: ["i32", "i32", "buffer"], result: "void" },
  WindowShouldClose: { parameters: [], result: "i32" },
  BeginDrawing: { parameters: [], result: "void" },
  EndDrawing: { parameters: [], result: "void" },
  ClearBackground: { parameters: [CColor], result: "void" },
  GetFrameTime: { parameters: [], result: "f32" },
  GetScreenWidth: { parameters: [], result: "i32" },
  GetScreenHeight: { parameters: [], result: "i32" },
  DrawRectangle: {
    parameters: ["i32", "i32", "i32", "i32", CColor],
    result: "void",
  },
  DrawFPS: { parameters: ["i32", "i32"], result: "void" },
  IsMouseButtonDown: { parameters: ["i32"], result: "i32" },
  GetMousePosition: { parameters: [], result: CVector2 },
});

const encoder = new TextEncoder();
function stringToBuffer(str: string): ArrayBufferLike {
  return encoder.encode(str + "\0").buffer;
}

raylib.symbols.InitWindow(500, 400, stringToBuffer("Hello from Deno!"));

const bgColor = Uint8ClampedArray.from([20, 27, 30, 255]);
const red = Uint8ClampedArray.from([255, 0, 0, 255]);
let invertX = false;
let x = 0;
let invertY = false;
let y = 0;

while (!raylib.symbols.WindowShouldClose()) {
  raylib.symbols.BeginDrawing();
  raylib.symbols.ClearBackground(bgColor);
  x += 50 * (invertX ? -1 : 1) * raylib.symbols.GetFrameTime();
  if (x > raylib.symbols.GetScreenWidth() - 50) {
    invertX = true;
    x = 450;
  } else if (x < 0) {
    invertX = false;
    x = 0;
  }
  y += 50 * (invertY ? -1 : 1) * raylib.symbols.GetFrameTime();
  if (y > raylib.symbols.GetScreenHeight() - 50) {
    invertY = true;
    y = 350;
  } else if (y < 0) {
    invertY = false;
    y = 0;
  }
  if (raylib.symbols.IsMouseButtonDown(0)) {
    // deno always converts struct returns to Uint8Array
    // so we have to manually convert them to the desired type
    let res: Uint8Array = raylib.symbols.GetMousePosition();
    let buffer = new Float32Array(res.buffer);
    x = buffer[0];
    y = buffer[1];
  }
  raylib.symbols.DrawRectangle(Math.round(x), Math.round(y), 50, 50, red);
  raylib.symbols.DrawFPS(10, 10);
  raylib.symbols.EndDrawing();
}
