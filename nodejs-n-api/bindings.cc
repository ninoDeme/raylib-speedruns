#define NAPI_VERSION 3
#include <node_api.h>

#include <assert.h>
#include <stdlib.h>
#include "raylib.h"

static Color GetColorFromJsObj(napi_env env, napi_value obj) {
  napi_valuetype valuetype0;
  napi_status status;
  status = napi_typeof(env, obj, &valuetype0);
  assert(status == napi_ok);

  if (valuetype0 != napi_object) {
    napi_throw_type_error(env, NULL, "Value must be a object");
    assert(false);
  }

  napi_value key;

  status = napi_create_string_utf8(env, "r", 1, &key);
  assert(status == napi_ok);
  napi_value r_value;
  status = napi_get_property(env, obj, key, &r_value);
  assert(status == napi_ok);

  status = napi_create_string_utf8(env, "g", 1, &key);
  assert(status == napi_ok);
  napi_value g_value;
  status = napi_get_property(env, obj, key, &g_value);
  assert(status == napi_ok);

  status = napi_create_string_utf8(env, "b", 1, &key);
  assert(status == napi_ok);
  napi_value b_value;
  status = napi_get_property(env, obj, key, &b_value);
  assert(status == napi_ok);

  status = napi_create_string_utf8(env, "a", 1, &key);
  assert(status == napi_ok);
  napi_value a_value;
  status = napi_get_property(env, obj, key, &a_value);
  assert(status == napi_ok);

  int32_t r;
  int32_t g;
  int32_t b;
  int32_t a;
  status = napi_get_value_int32(env, r_value, &r);
  assert(status == napi_ok);
  status = napi_get_value_int32(env, g_value, &g);
  assert(status == napi_ok);
  status = napi_get_value_int32(env, b_value, &b);
  assert(status == napi_ok);
  status = napi_get_value_int32(env, a_value, &a);
  assert(status == napi_ok);

  return (Color) {
    (unsigned char) r,
    (unsigned char) b,
    (unsigned char) g,
    (unsigned char) a,
  };
}

static napi_value initWindow(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 3;
  napi_value args[3];
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  assert(status == napi_ok);

  if (argc < 2) {
    napi_throw_type_error(env, NULL, "Wrong number of arguments");
    return NULL;
  }

  napi_valuetype valuetype0;
  status = napi_typeof(env, args[0], &valuetype0);
  assert(status == napi_ok);

  napi_valuetype valuetype1;
  status = napi_typeof(env, args[1], &valuetype1);
  assert(status == napi_ok);

  napi_valuetype valuetype2;
  status = napi_typeof(env, args[2], &valuetype2);
  assert(status == napi_ok);

  if (valuetype0 != napi_number || valuetype1 != napi_number || valuetype2 != napi_string) {
    napi_throw_type_error(env, NULL, "Invalid argument types");
    return NULL;
  }

  int32_t width;
  status = napi_get_value_int32(env, args[0], &width);
  assert(status == napi_ok);

  int32_t height;
  status = napi_get_value_int32(env, args[1], &height);
  assert(status == napi_ok);

  size_t size;
  status = napi_get_value_string_utf8(env, args[2], NULL, NULL, &size);
  assert(status == napi_ok);
  char* title = (char*) malloc(size + sizeof(char));
  size_t sizeR;
  status = napi_get_value_string_utf8(env, args[2], title, size + sizeof(char), &sizeR);
  assert(status == napi_ok);

  InitWindow(width, height, title);
  free(title);
  return NULL;
}

static napi_value windowShouldClose(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  status = napi_get_boolean(env, WindowShouldClose(), &result);
  assert(status == napi_ok);

  return result;
}

static napi_value beginDrawing(napi_env env, napi_callback_info info) {
  BeginDrawing();
  return NULL;
}

static napi_value endDrawing(napi_env env, napi_callback_info info) {
  EndDrawing();
  return NULL;
}

static napi_value clearBackground(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1;
  napi_value args[1];
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  assert(status == napi_ok);

  if (argc < 1) {
    napi_throw_type_error(env, NULL, "Wrong number of arguments");
    return NULL;
  }

  Color color = GetColorFromJsObj(env, args[0]);

  ClearBackground(color);
  return NULL;
}

static napi_value getFrameTime(napi_env env, napi_callback_info info) {
  float frameTime = GetFrameTime();
  napi_status status;
  napi_value result;

  status = napi_create_double(env, (double) frameTime, &result);
  assert(status == napi_ok);

  return result;
}

static napi_value getScreenWidth(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;

  status = napi_create_int32(env, GetScreenWidth(), &result);
  assert(status == napi_ok);

  return result;
}

static napi_value getScreenHeight(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;

  status = napi_create_int32(env, GetScreenHeight(), &result);
  assert(status == napi_ok);

  return result;
}

static napi_value drawRectangle(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 5;
  napi_value args[5];
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  assert(status == napi_ok);

  if (argc < 5) {
    napi_throw_type_error(env, NULL, "Wrong number of arguments");
    return NULL;
  }

  napi_valuetype valuetype0;
  status = napi_typeof(env, args[0], &valuetype0);
  assert(status == napi_ok);                    
                                                
  napi_valuetype valuetype1;                    
  status = napi_typeof(env, args[1], &valuetype1);
  assert(status == napi_ok);                    
                                                
  napi_valuetype valuetype2;                    
  status = napi_typeof(env, args[2], &valuetype2);
  assert(status == napi_ok);                    
                                                
  napi_valuetype valuetype3;                    
  status = napi_typeof(env, args[3], &valuetype3);
  assert(status == napi_ok);                    
                                                
  napi_valuetype valuetype4;                    
  status = napi_typeof(env, args[4], &valuetype4);
  assert(status == napi_ok);

  if (valuetype0 != napi_number || valuetype1 != napi_number || valuetype2 != napi_number || valuetype3 != napi_number || valuetype4 != napi_object) {
    napi_throw_type_error(env, NULL, "Invalid argument types");
    return NULL;
  }

  int32_t posX;
  status = napi_get_value_int32(env, args[0], &posX);
  assert(status == napi_ok);

  int32_t posY;
  status = napi_get_value_int32(env, args[1], &posY);
  assert(status == napi_ok);

  int32_t width;
  status = napi_get_value_int32(env, args[2], &width);
  assert(status == napi_ok);

  int32_t height;
  status = napi_get_value_int32(env, args[3], &height);
  assert(status == napi_ok);

  Color color = GetColorFromJsObj(env, args[4]);

  DrawRectangle(posX, posY, width, height, color);
  return NULL;
}

static napi_value drawFPS(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 2;
  napi_value args[2];
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  assert(status == napi_ok);

  if (argc < 2) {
    napi_throw_type_error(env, NULL, "Wrong number of arguments");
    return NULL;
  }

  napi_valuetype valuetype0;
  status = napi_typeof(env, args[0], &valuetype0);
  assert(status == napi_ok);                    
                                                
  napi_valuetype valuetype1;                    
  status = napi_typeof(env, args[1], &valuetype1);
  assert(status == napi_ok);                    
                                                
  if (valuetype0 != napi_number || valuetype1 != napi_number) {
    napi_throw_type_error(env, NULL, "Invalid argument types");
    return NULL;
  }

  int32_t posX;
  status = napi_get_value_int32(env, args[0], &posX);
  assert(status == napi_ok);

  int32_t posY;
  status = napi_get_value_int32(env, args[1], &posY);
  assert(status == napi_ok);

  DrawFPS(posX, posY);
  return NULL;
}

static napi_value isMouseButtonDown(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;

  size_t argc = 1;
  napi_value args[1];
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  assert(status == napi_ok);

  if (argc < 1) {
    napi_throw_type_error(env, NULL, "Wrong number of arguments");
    return NULL;
  }

  napi_valuetype valuetype0;
  status = napi_typeof(env, args[0], &valuetype0);
  assert(status == napi_ok);                    
                                                
  if (valuetype0 != napi_number) {
    napi_throw_type_error(env, NULL, "Invalid argument types");
    return NULL;
  }

  int32_t button;
  status = napi_get_value_int32(env, args[0], &button);
  assert(status == napi_ok);

  status = napi_get_boolean(env, IsMouseButtonDown(button), &result);
  assert(status == napi_ok);

  return result;
}

static napi_value getMousePosition(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  Vector2 vec = GetMousePosition();
  status = napi_create_object(env, &result);
  assert(status == napi_ok);

  napi_value key;
  napi_value value;

  status = napi_create_string_utf8(env, "x", 1, &key);
  assert(status == napi_ok);
  status = napi_create_double(env, (double) vec.x, &value);
  status = napi_set_property(env, result, key, value);
  assert(status == napi_ok);

  status = napi_create_string_utf8(env, "y", 1, &key);
  assert(status == napi_ok);
  status = napi_create_double(env, (double) vec.y, &value);
  status = napi_set_property(env, result, key, value);
  assert(status == napi_ok);

  return result;
}

#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

static napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor desc[] = {
    DECLARE_NAPI_METHOD("InitWindow", initWindow),
    DECLARE_NAPI_METHOD("WindowShouldClose", windowShouldClose),
    DECLARE_NAPI_METHOD("BeginDrawing", beginDrawing),
    DECLARE_NAPI_METHOD("EndDrawing", endDrawing),
    DECLARE_NAPI_METHOD("ClearBackground", clearBackground),
    DECLARE_NAPI_METHOD("GetScreenWidth", getScreenWidth),
    DECLARE_NAPI_METHOD("GetScreenHeight", getScreenHeight),
    DECLARE_NAPI_METHOD("GetFrameTime", getFrameTime),
    DECLARE_NAPI_METHOD("DrawRectangle", drawRectangle),
    DECLARE_NAPI_METHOD("IsMouseButtonDown", isMouseButtonDown),
    DECLARE_NAPI_METHOD("GetMousePosition", getMousePosition),
    DECLARE_NAPI_METHOD("DrawFPS", drawFPS)
  };
  status = napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
