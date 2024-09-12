#include "raylib.h"
#include <jni.h>

Color JavaColorToRaylibColor(JNIEnv *env, jobject color) {
  jclass colorClass = (*env)->GetObjectClass(env, color);

  jfieldID rFieldID = (*env)->GetFieldID(env, colorClass, "r", "B");
  jfieldID gFieldID = (*env)->GetFieldID(env, colorClass, "g", "B");
  jfieldID bFieldID = (*env)->GetFieldID(env, colorClass, "b", "B");
  jfieldID aFieldID = (*env)->GetFieldID(env, colorClass, "a", "B");

  return (Color) {
    (*env)->GetByteField(env, color, rFieldID),
    (*env)->GetByteField(env, color, gFieldID),
    (*env)->GetByteField(env, color, bFieldID),
    (*env)->GetByteField(env, color, aFieldID),
  };
}

JNIEXPORT void JNICALL Java_App_InitWindow
  (JNIEnv *env, jobject obj, jint width, jint height, jstring title) {
  InitWindow(width, height, (*env)->GetStringUTFChars(env, title, 0));
};

JNIEXPORT jboolean JNICALL Java_App_WindowShouldClose
  (JNIEnv *env, jobject obj) {
  return WindowShouldClose();
};

JNIEXPORT jboolean JNICALL Java_App_BeginDrawing
  (JNIEnv *env, jobject obj) {
  BeginDrawing();
};

JNIEXPORT jboolean JNICALL Java_App_EndDrawing
  (JNIEnv *env, jobject obj) {
  EndDrawing();
};

JNIEXPORT jfloat JNICALL Java_App_GetFrameTime
  (JNIEnv *env, jobject obj) {
  return GetFrameTime();
};

JNIEXPORT void JNICALL Java_App_ClearBackground
  (JNIEnv *env, jobject obj, jobject jcolor) {
  Color color = JavaColorToRaylibColor(env, jcolor);
  ClearBackground(color);
};

JNIEXPORT void JNICALL Java_App_DrawRectangle
  (JNIEnv *env, jobject obj, jint posX, jint posY, jint width, jint height, jobject jcolor) {

  Color color = JavaColorToRaylibColor(env, jcolor);

  DrawRectangle(posX, posY, width, height, color);
};

JNIEXPORT jboolean JNICALL Java_App_IsMouseButtonDown
  (JNIEnv *env, jobject obj, jint button) {
  return IsMouseButtonDown(button);
};

JNIEXPORT jobject JNICALL Java_App_GetMousePosition
  (JNIEnv *env, jobject obj) {
  jclass cls = (*env)->FindClass(env, "Vector2");

  jmethodID init = (*env)->GetMethodID(env, cls, "<init>", "(FF)V");

  Vector2 pos = GetMousePosition();

  return (*env)->NewObject(env, cls, init, pos.x, pos.y);
};

JNIEXPORT jint JNICALL Java_App_GetScreenWidth
  (JNIEnv *env, jobject obj) {
  return GetScreenWidth();
};

JNIEXPORT jint JNICALL Java_App_GetScreenHeight
  (JNIEnv *env, jobject obj) {
  return GetScreenHeight();
};
