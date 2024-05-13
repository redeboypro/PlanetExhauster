//
// Created by redeb on 12.05.2024.
//

#include "Window.h"

LRESULT CALLBACK WndMsgCb(HWND wndHandle, uint32_t msg, WPARAM wParam, LPARAM lParam)
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

Window::Window(
    LPCSTR wndTitle,
    int32_t wndWidth,
    int32_t wndHeight,
    WndUpdPtrt* updPtrt,
    int32_t glMajor,
    int32_t glMinor) :
m_updPtrt(updPtrt) {
    glInitExtensions();

    const WNDCLASSEX wndClass = {
        .cbSize = sizeof(WNDCLASSEX),
        .style = CS_OWNDC,
        .lpfnWndProc = &WndMsgCb,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = GetModuleHandle(nullptr),
        .hIcon = LoadIcon(nullptr, IDI_APPLICATION),
        .hCursor = LoadCursor(nullptr, IDC_ARROW),
        .hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)),
        .lpszMenuName = nullptr,
        .lpszClassName = WND_CLASSNAME,
        .hIconSm = LoadIcon(nullptr, IDI_APPLICATION),
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

    m_wndHandle = CreateWindowEx(
        NULL,
        MAKEINTATOM(wndClassRegResult),
        wndTitle,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
        wndRect.right - wndRect.left, wndRect.bottom - wndRect.top,
        nullptr,
        nullptr,
        nullptr,
        nullptr);

    if (!m_wndHandle) {
        ERR_MSG(WINAPIMSG, L"Failed to create window instance!");
        FAIL_EXIT;
    }

    m_wndDCHandle = GetDC(m_wndHandle);

    SetWindowLongPtr(m_wndHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    ShowWindow(m_wndHandle, SW_SHOW);
    UpdateWindow(m_wndHandle);

    m_glContextHandle = glInit(m_wndDCHandle, glMajor, glMinor);
}

Window::~Window() {
    wglDeleteContext(m_glContextHandle);
    DestroyWindow(m_wndHandle);
}

void Window::run() {
    while (m_running) {
        MSG msg = {};
        if (PeekMessage(
            &msg,
            nullptr,
            NULL,
            NULL,
            PM_REMOVE)) {
            if (msg.message != WM_QUIT) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else {
                m_running = false;
                continue;
            }
        }

        TimePt currentTime = std::chrono::system_clock::now();
        auto elapsedSeconds = std::chrono::duration<double>();

        if (m_previousTime.time_since_epoch().count())
            elapsedSeconds = currentTime - m_previousTime;

        m_previousTime = currentTime;
        m_updPtrt(elapsedSeconds.count());

        wglSwapLayerBuffers(m_wndDCHandle, WGL_SWAP_MAIN_PLANE);
    }
}

void Window::vsync(const bool activeState) {
    wglSwapIntervalEXT(activeState);
}
