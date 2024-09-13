#include <node.h>
#include <assert.h>
#include "raylib.h"

namespace raylib {

Color jsColorToCColor(v8::Isolate* isolate, v8::Local<v8::Object> color) {
  auto r_v8 = color->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "r").ToLocalChecked()).ToLocalChecked();
  assert(r_v8->IsNumber());
  auto g_v8 = color->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "g").ToLocalChecked()).ToLocalChecked();
  assert(g_v8->IsNumber());
  auto b_v8 = color->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "b").ToLocalChecked()).ToLocalChecked();
  assert(b_v8->IsNumber());
  auto a_v8 = color->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "a").ToLocalChecked()).ToLocalChecked();
  assert(a_v8->IsNumber());

  return (Color) {
    (unsigned char) r_v8.As<v8::Number>()->Value(),
    (unsigned char) g_v8.As<v8::Number>()->Value(),
    (unsigned char) b_v8.As<v8::Number>()->Value(),
    (unsigned char) a_v8.As<v8::Number>()->Value()
  };
}

void initWindow(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* parent_isolate = args.GetIsolate();

  assert(args[0]->IsNumber());
  auto width = args[0].As<v8::Number>();
  assert(args[1]->IsNumber());
  auto height = args[1].As<v8::Number>();
  assert(args[2]->IsString());

  v8::String::Utf8Value title(parent_isolate, args[2]);
  assert(*title != nullptr);

  InitWindow((int) width->Value(), (int) height->Value(), *title);
}

void drawFPS(const v8::FunctionCallbackInfo<v8::Value>& args) {
  assert(args[0]->IsNumber());
  auto posX = args[0].As<v8::Number>();
  assert(args[1]->IsNumber());
  auto posY = args[1].As<v8::Number>();

  DrawFPS((int) posX->Value(), (int) posY->Value());
}

void windowShouldClose(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(v8::Boolean::New(isolate, WindowShouldClose()));
}

void beginDrawing(const v8::FunctionCallbackInfo<v8::Value>& args) {
  BeginDrawing();
}

void endDrawing(const v8::FunctionCallbackInfo<v8::Value>& args) {
  EndDrawing();
}

void clearBackground(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();

  assert(args[0]->IsObject());

  Color bg = jsColorToCColor(isolate, args[0].As<v8::Object>());

  ClearBackground(bg);
}

void drawRectangle(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();

  assert(args[0]->IsNumber());
  auto posX = args[0].As<v8::Number>();
  assert(args[1]->IsNumber());
  auto posY = args[1].As<v8::Number>();
  assert(args[2]->IsNumber());
  auto width = args[2].As<v8::Number>();
  assert(args[3]->IsNumber());
  auto height = args[3].As<v8::Number>();

  assert(args[4]->IsObject());
  Color color = jsColorToCColor(isolate, args[4].As<v8::Object>());

  DrawRectangle(posX->Value(), posY->Value(), width->Value(), height->Value(), color);
}

void getFrameTime(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(v8::Number::New(isolate, (double) GetFrameTime()));
}

void getScreenHeight(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(v8::Number::New(isolate, (double) GetScreenHeight()));
}

void getScreenWidth(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(v8::Number::New(isolate, (double) GetScreenWidth()));
}

void isMouseButtonDown(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();

  assert(args[0]->IsNumber());
  auto button = args[0].As<v8::Number>();

  args.GetReturnValue().Set(v8::Boolean::New(isolate, IsMouseButtonDown(button->Value())));
}

void getMousePosition(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();

  Vector2 vector2 = GetMousePosition();
  auto jsVector = v8::Object::New(isolate);
  jsVector->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "x").ToLocalChecked(), v8::Number::New(isolate, vector2.x)).Check();
  jsVector->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "y").ToLocalChecked(), v8::Number::New(isolate, vector2.y)).Check();
  args.GetReturnValue().Set(jsVector);
}

void Initialize(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "InitWindow", initWindow);
  NODE_SET_METHOD(exports, "WindowShouldClose", windowShouldClose);
  NODE_SET_METHOD(exports, "BeginDrawing", beginDrawing);
  NODE_SET_METHOD(exports, "EndDrawing", endDrawing);
  NODE_SET_METHOD(exports, "ClearBackground", clearBackground);
  NODE_SET_METHOD(exports, "GetFrameTime", getFrameTime);
  NODE_SET_METHOD(exports, "DrawRectangle", drawRectangle);
  NODE_SET_METHOD(exports, "GetScreenHeight", getScreenHeight);
  NODE_SET_METHOD(exports, "GetScreenWidth", getScreenWidth);
  NODE_SET_METHOD(exports, "IsMouseButtonDown", isMouseButtonDown);
  NODE_SET_METHOD(exports, "GetMousePosition", getMousePosition);
  NODE_SET_METHOD(exports, "DrawFPS", drawFPS);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}

