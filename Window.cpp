//
// Created by redeb on 12.05.2024.
//

#include "Window.h"

LRESULT __attribute__((__stdcall__)) WndMsgCb(HWND wndHandle, uint32_t msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CLOSE:
        {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(wndHandle, msg, wParam, lParam);
    }

    return NULL;
}

HWND InitWnd(const LPCSTR wndTitle, const int32_t wndWidth, const int32_t wndHeight, const LONG_PTR wndLPtr) {
    constexpr WNDCLASSEX wndClass = {
        .cbSize = sizeof(WNDCLASSEX),
        .lpszClassName = WND_CLASSNAME,
        .lpfnWndProc = &WndMsgCb,
        .style = CS_OWNDC,
    };

    const ATOM wndClassRegResult = RegisterClassEx(&wndClass);
    if (!wndClassRegResult) {
        ERR_MSG(WINAPIMSG, L"Failed to register window class!");
        FAIL_EXIT;
    }

    RECT wndRect = {
        .left = 0,
        .top = 0,
        .right = wndWidth,
        .bottom = wndHeight
    };

    AdjustWindowRect(&wndRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

    HWND wndHandle = CreateWindowEx(
        NULL,
        MAKEINTATOM(wndClassRegResult),
        wndTitle,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
        wndRect.right - wndRect.left, wndRect.bottom - wndRect.top,
        nullptr,
        nullptr,
        nullptr,
        nullptr);

    if (!wndHandle) {
        ERR_MSG(WINAPIMSG, L"Failed to create window instance!");
        FAIL_EXIT;
    }

    SetWindowLongPtr(wndHandle, GWLP_USERDATA, wndLPtr);

    ShowWindow(wndHandle, SW_SHOW);
    UpdateWindow(wndHandle);

    return wndHandle;
}

WindowShell::WindowShell(HWND wndHandle, HGLRC glContextHandle, WndUpdPtrt* updPtrt) :
m_wndHandle(wndHandle),
m_glContextHandle(glContextHandle),
m_updPtrt(updPtrt) {
    while (m_running)
    {
        auto currentTime = std::chrono::system_clock::now();
        auto elapsedSeconds = std::chrono::duration<double>();

        if (m_previousTime.time_since_epoch().count())
            elapsedSeconds = currentTime - m_previousTime;

        m_previousTime = currentTime;

        MSG msg = {};
        if (PeekMessage(&msg, HWND(), NULL, NULL, PM_REMOVE))
        {
            if (msg.message != WM_QUIT)
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                m_running = false;
                continue;
            }
        }

        updPtrt(elapsedSeconds.count());
    }
}

WindowShell::~WindowShell() {
    wglDeleteContext(m_glContextHandle);
    DestroyWindow(m_wndHandle);
}
