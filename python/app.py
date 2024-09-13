from ctypes import *
import pathlib

class COLOR(Structure):
    _fields_ = [
        ('r', c_ubyte),
        ('g', c_ubyte),
        ('b', c_ubyte),
        ('a', c_ubyte),
    ]

class VECTOR2(Structure):
    _fields_ = [
        ('x', c_float),
        ('y', c_float),
    ]

if __name__ == "__main__":
    libname = pathlib.Path().absolute() / "raylib-5.0_linux_amd64/lib/libraylib.so"
    raylib = CDLL(libname)
    raylib.GetFrameTime.restype = c_float
    raylib.GetMousePosition.restype = VECTOR2
    bgColor = COLOR(20, 27, 30, 255) 
    invertX = False
    invertY = False
    x = 0
    y = 0
    red = COLOR(255, 0, 0, 255) 
    raylib.InitWindow(500, 400, b"Hello from Python3!")
    while not raylib.WindowShouldClose():
        raylib.BeginDrawing()
        raylib.ClearBackground(bgColor)
        x += 50 * (invertX and -1 or 1) * raylib.GetFrameTime();
        if x > raylib.GetScreenWidth() - 50:
          invertX = True
          x = 450
        elif x < 0:
          invertX = False
          x = 0
        y += 50 * (invertY and -1 or 1) * raylib.GetFrameTime();
        if y > raylib.GetScreenHeight() - 50:
          invertY = True
          y = 350
        elif y < 0:
          invertY = False
          y = 0
        if raylib.IsMouseButtonDown(0):
            pos = raylib.GetMousePosition()
            x = pos.x
            y = pos.y

        raylib.DrawRectangle(int(x), int(y), 50, 50, red)
        raylib.DrawFPS(10, 10)
        raylib.EndDrawing()
