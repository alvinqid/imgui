#include <jni.h>
#include <android/native_window_jni.h>
#include <android/log.h>
#include <GLES3/gl3.h>
#include <thread>
#include "imgui.h"
#include "backends/imgui_impl_android.h"
#include "backends/imgui_impl_opengl3.h"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "ImGuiDemo", __VA_ARGS__)

static bool g_Running = false;
static ANativeWindow* g_Window = nullptr;

void renderLoop() {
    LOGI("Render loop mulai");

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    ImGui_ImplAndroid_Init(g_Window);
    ImGui_ImplOpenGL3_Init("#version 300 es");

    while (g_Running) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplAndroid_NewFrame(g_Window);
        ImGui::NewFrame();

        // ---- Contoh UI ----
        ImGui::Begin("Hello from MainActivity!");
        ImGui::Text("FPS: %.1f", io.Framerate);
        ImGui::Button("Klik aku");
        ImGui::End();
        // -------------------

        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        eglSwapBuffers(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW));
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    LOGI("Render loop selesai");
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_imguidemo_MainActivity_nativeStart(JNIEnv* env, jobject thiz, jobject surface) {
    if (g_Running) return;
    g_Running = true;
    g_Window = ANativeWindow_fromSurface(env, surface);

    std::thread loopThread(renderLoop);
    loopThread.detach();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_imguidemo_MainActivity_nativeStop(JNIEnv* env, jobject thiz) {
    g_Running = false;
}
