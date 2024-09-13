use std::ffi::{ CString, c_char };

#[repr(C)]
struct Color {
    r: u8,
    g: u8,
    b: u8,
    a: u8
}

#[repr(C)]
struct Vector2 {
    x: f32,
    y: f32
}

#[link(name = "raylib", kind = "static")]
extern "C" {
    fn InitWindow(width: i32, height: i32, title: *const c_char) -> ();
    fn WindowShouldClose() -> i32;
    fn BeginDrawing() -> ();
    fn EndDrawing() -> ();
    fn ClearBackground(color: Color) -> ();
    fn GetFrameTime() -> f32;
    fn GetScreenWidth() -> i32;
    fn GetScreenHeight() -> i32;
    fn DrawRectangle(posX: i32, posY: i32, width: i32, height: i32, color: Color) -> ();
    fn DrawFPS(posX: i32, posY: i32) -> ();
    fn IsMouseButtonDown(button: i32) -> i32;
    fn GetMousePosition() -> Vector2;
}

pub fn init_window(width: i32, height: i32, title: &str) -> () {
    let title_c = CString::new(title).expect("Invalid input string");
    unsafe {
        InitWindow(width, height, title_c.as_ptr());
    }
}

pub fn window_should_close() -> bool {
    unsafe {
        return WindowShouldClose() == 1;
    }
}

pub fn begin_drawing() -> () {
    unsafe {
        BeginDrawing();
    }
}

pub fn end_drawing() -> () {
    unsafe {
        EndDrawing();
    }
}

pub fn clear_background(color: Color) -> () {
    unsafe {
        return ClearBackground(color);
    }
}

pub fn get_frame_time() -> f32 {
    unsafe {
        return GetFrameTime();
    }
}

pub fn get_screen_width() -> i32 {
    unsafe {
        return GetScreenWidth();
    }
}

pub fn get_screen_height() -> i32 {
    unsafe {
        return GetScreenHeight();
    }
}

pub fn draw_rectangle(posX: i32, posY: i32, width: i32, height: i32, color: Color) {
    unsafe {
        return DrawRectangle(posX, posY, width, height, color);
    }
}

pub fn draw_fps(posX: i32, posY: i32) {
    unsafe {
        return DrawFPS(posX, posY);
    }
}

pub fn is_mouse_button_down(button: i32) -> bool {
    unsafe {
        return IsMouseButtonDown(button) == 1;
    }
}

pub fn get_mouse_position() -> Vector2 {
    unsafe {
        return GetMousePosition();
    }
}

const BG_COLOR: Color = Color { r: 20, g: 27, b: 30, a: 255 };
const RED: Color = Color { r: 255, g: 0, b: 0, a: 255 };

fn main() {
    init_window(500, 400, "Hello from Rust!");
    let mut x: f32 = 0.0;
    let mut y: f32 = 0.0;
    let mut invertX: bool = false;
    let mut invertY: bool = false;
    while !window_should_close() {
        begin_drawing();
        clear_background(BG_COLOR);

        x = x + 50.0 * (if invertX {-1.0} else  {1.0}) * get_frame_time();
        if x > get_screen_width() as f32 - 50.0 {
            invertX = true;
            x = 450.0;
        } else if x < 0.0 {
            invertX = false;
            x = 0.0;
        }
        y = y + 50.0 * (if invertY {-1.0} else {1.0}) * get_frame_time();
        if y > get_screen_height() as f32 - 50.0 {
            invertY = true;
            y = 350.0;
        } else if y < 0.0 {
            invertY = false;
            y = 0.0;
        }
        if is_mouse_button_down(0) {
            let pos: Vector2 = get_mouse_position();
            x = pos.x;
            y = pos.y;
        }
        draw_rectangle(x as i32, y as i32, 50, 50, RED);
        draw_fps(10, 10);
        end_drawing();
    };
}
