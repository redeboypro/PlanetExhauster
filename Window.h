//
// Created by redeb on 12.05.2024.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <chrono>
#include "GLAPI.h"

#define WND_CLASSNAME "_WND"

using WndUpdPtrt = void(double delta);

using TimePt = std::chrono::time_point<std::chrono::system_clock>;

class Window {
    HWND m_wndHandle;
    HDC m_wndDCHandle;
    HGLRC m_glContextHandle;
    WndUpdPtrt* m_updPtrt;
    bool m_running = true;
    TimePt m_previousTime;

public:
    Window(
        LPCSTR wndTitle,
        int32_t wndWidth,
        int32_t wndHeight,
        WndUpdPtrt* updPtrt,
        int32_t glMajor,
        int32_t glMinor);
    ~Window();

    void run();

    static void vsync(bool activeState);
};

#endif //WINDOW_H
