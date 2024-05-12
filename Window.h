//
// Created by redeb on 12.05.2024.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <chrono>

#include "GLAPI.h"

#define WND_CLASSNAME "_WND"

typedef void WndUpdPtrt(double delta);

static HWND InitWnd();

class WindowShell {
    HWND m_wndHandle;
    HGLRC m_glContextHandle;
    WndUpdPtrt* m_updPtrt;
    bool m_running = true;
    std::chrono::time_point<std::chrono::system_clock> m_previousTime;

public:
    WindowShell(HWND wndHandle, HGLRC glContextHandle, WndUpdPtrt* updPtrt);
    ~WindowShell();
};

#endif //WINDOW_H
