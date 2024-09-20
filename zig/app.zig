const raylib = @cImport({
    @cInclude("raylib.h");
});

pub fn main() void {
    raylib.InitWindow(500, 400, "Hello from Zig!");
    const bgColor: raylib.Color = raylib.Color{
        .r = 20,
        .g = 27,
        .b = 30,
        .a = 255,
    };
    const red: raylib.Color = raylib.Color{
        .r = 255,
        .g = 0,
        .b = 0,
        .a = 255,
    };
    var invertX: bool = true;
    var x: f32 = 0;
    var invertY: bool = false;
    var y: f32 = 0;
    while (!raylib.WindowShouldClose()) {
        raylib.BeginDrawing();
        raylib.ClearBackground(bgColor);
        var xDelta = 50.0 * raylib.GetFrameTime();
        if (invertX) {
            xDelta = xDelta * -1;
        }
        x += xDelta;
        if (x > @as(f32, @floatFromInt(raylib.GetScreenWidth())) - 50.0) {
            invertX = true;
            x = 450.0;
        } else if (x < 0.0) {
            invertX = false;
            x = 0.0;
        }
        var yDelta = 50.0 * raylib.GetFrameTime();
        if (invertY) {
            yDelta = yDelta * -1;
        }
        y += yDelta;
        if (y > @as(f32, @floatFromInt(raylib.GetScreenHeight())) - 50.0) {
            invertY = true;
            y = 350.0;
        } else if (y < 0.0) {
            invertY = false;
            y = 0.0;
        }
        if (raylib.IsMouseButtonDown(raylib.MOUSE_BUTTON_LEFT)) {
            const pos: raylib.Vector2 = raylib.GetMousePosition();
            x = pos.x;
            y = pos.y;
        }
        raylib.DrawRectangle(@as(c_int, @intFromFloat(x)), @as(c_int, @intFromFloat(y)), 50, 50, red);
        raylib.DrawFPS(10, 10);
        raylib.EndDrawing();
    }
}
