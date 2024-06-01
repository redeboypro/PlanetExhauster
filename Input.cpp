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
    for (int32_t i = 0; i < 256; ++i) {
        auto key = static_cast<KeyCode>(i);
        m_currentKeyboardState[key] = m_lastKeyboardState[key] = false;
    }
}

void Input::begin() {
    for (int32_t i = 0; i < 256; ++i) {
        auto key = static_cast<KeyCode>(i);
        m_currentKeyboardState[key] = (GetAsyncKeyState(i) & 0x8000) != 0;
    }

    GetCursorPos(&m_currentMousePosition);
    ScreenToClient(m_wndHandle, &m_currentMousePosition);
    m_deltaMousePosition = {
        m_currentMousePosition.x - m_lastMousePosition.x,
        m_currentMousePosition.y - m_lastMousePosition.y
    };
}

void Input::end() {
    for (int32_t i = 0; i < 256; ++i) {
        auto key = static_cast<KeyCode>(i);
        m_lastKeyboardState[key] = m_currentKeyboardState[key];
    }
    m_lastMousePosition = m_currentMousePosition;
}
