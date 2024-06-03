//
// Created by redeb on 27.05.2024.
//

#include "Input.h"

bool Input::getKeyDown(const KeyCode key) {
    return getKey(key) && !m_lastKeyboardState[key];
}

bool Input::getKeyUp(const KeyCode key) {
    return !getKey(key) && m_lastKeyboardState[key];
}

bool Input::getKey(const KeyCode key) {
    return m_currentKeyboardState[key];
}

void Input::init() {
    for (int32_t i = 0; i <= 165; ++i) {
        auto key = static_cast<KeyCode>(i);
        m_currentKeyboardState[key] = m_lastKeyboardState[key] = false;
    }

    RECT windowRect;
    GetWindowRect(m_wndHandle->getHandle(), &windowRect);

    const int32_t centerX = (windowRect.left + windowRect.right) / 2;
    const int32_t centerY = (windowRect.top + windowRect.bottom) / 2;

    SetCursorPos(centerX, centerY);
    ClipCursor(&windowRect);
}

void Input::begin() {
    for (int32_t i = 0; i <= 165; ++i) {
        auto key = static_cast<KeyCode>(i);
        m_currentKeyboardState[key] = (GetAsyncKeyState(i) & 0x8000) != 0;
    }

    GetCursorPos(&m_currentMousePosition);
    ScreenToClient(m_wndHandle->getHandle(), &m_currentMousePosition);

    if (FAILED(m_mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState))) {
        std::cerr << "Failed to get mouse device state" << std::endl;
    }
    m_deltaMousePosition = {m_mouseState.lX, m_mouseState.lY};
}

void Input::end() {
    for (int32_t i = 0; i <= 165; ++i) {
        auto key = static_cast<KeyCode>(i);
        m_lastKeyboardState[key] = m_currentKeyboardState[key];
    }
}
