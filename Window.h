//
// Created by redeb on 12.05.2024.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <chrono>
#include "GLAPI.h"

#define F32(I32) static_cast<float>(I32)

#define WND_CLASSNAME "_WND"

using WindowMessageCallback = LRESULT CALLBACK(HWND__ *wndHandle, uint32_t msg, WPARAM wParam, LPARAM lParam);
using TimePt = std::chrono::time_point<std::chrono::system_clock>;

class Window {
    HWND m_wndHandle;
    HDC m_wndDCHandle;
    HGLRC m_glContextHandle;
    bool m_running = true;
    TimePt m_previousTime;

    static WindowMessageCallback WndProc;
public:
    Window(
        LPCSTR wndTitle,
        int32_t wndWidth,
        int32_t wndHeight,
        int32_t glMajor,
        int32_t glMinor);
    ~Window();

    [[nodiscard]] HWND__* getHandle() const {
        return m_wndHandle;
    }

    const int32_t width, height;

    [[nodiscard]] bool running() const {
        return m_running;
    }

    void beginFrame(float& deltaTime);
    void endFrame() const;

    static void vsync(bool activeState);
};

#endif //WINDOW_H
