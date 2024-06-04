//
// Created by redeb on 27.05.2024.
//

#ifndef INPUT_H
#define INPUT_H

#define INITGUID
#include <cstdint>
#include <unordered_map>
#include <dinput.h>
#include <iostream>

#include "Window.h"

#define KEY_COUNT 256

enum class KeyCode : int32_t {
    MouseLeft = 0x01,
    MouseRight = 0x02,
    Cancel = 0x03,
    MouseMiddle = 0x04,
    MouseXButton1 = 0x05,
    MouseXButton2 = 0x06,
    Back = 0x08,
    Tab = 0x09,
    Clear = 0x0C,
    Return = 0x0D,
    Shift = 0x10,
    Control = 0x11,
    Menu = 0x12,
    Pause = 0x13,
    Capital = 0x14,
    Esc = 0x1B,
    Space = 0x20,
    PageUp = 0x21,
    PageDown = 0x22,
    End = 0x23,
    Home = 0x24,
    Left = 0x25,
    Up = 0x26,
    Right = 0x27,
    Down = 0x28,
    Select = 0x29,
    Print = 0x2A,
    Execute = 0x2B,
    PrtScr = 0x2C,
    Insert = 0x2D,
    Delete = 0x2E,
    LWin = 0x5B,
    RWin = 0x5C,
    Numpad0 = 0x60,
    Numpad1 = 0x61,
    Numpad2 = 0x62,
    Numpad3 = 0x63,
    Numpad4 = 0x64,
    Numpad5 = 0x65,
    Numpad6 = 0x66,
    Numpad7 = 0x67,
    Numpad8 = 0x68,
    Numpad9 = 0x69,
    Multiply = 0x6A,
    Add = 0x6B,
    Separator = 0x6C,
    Subtract = 0x6D,
    Decimal = 0x6E,
    Divide = 0x6F,
    F1 = 0x70,
    F2 = 0x71,
    F3 = 0x72,
    F4 = 0x73,
    F5 = 0x74,
    F6 = 0x75,
    F7 = 0x76,
    F8 = 0x77,
    F9 = 0x78,
    F10 = 0x79,
    F11 = 0x7A,
    F12 = 0x7B,
    NumLock = 0x90,
    ScrollLock = 0x91,
    LShift = 0xA0,
    RShift = 0xA1,
    LControl = 0xA2,
    RControl = 0xA3,
    LAlt = 0xA4,
    RAlt = 0xA5,
    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,
    Alpha0 = 48,
    Alpha1 = 49,
    Alpha2 = 50,
    Alpha3 = 51,
    Alpha4 = 52,
    Alpha5 = 53,
    Alpha6 = 54,
    Alpha7 = 55,
    Alpha8 = 56,
    Alpha9 = 57
};

class Input final {
    std::unordered_map<KeyCode, bool> m_currentKeyboardState;
    std::unordered_map<KeyCode, bool> m_lastKeyboardState;

    POINT m_currentMousePosition {};
    POINT m_deltaMousePosition {};

    Window* m_wndHandle;

    LPDIRECTINPUT8 m_directInputHandle {};
    LPDIRECTINPUTDEVICE8 m_mouseDevice {};
    DIMOUSESTATE m_mouseState;

public:
    explicit Input(Window* wndHandle) : m_wndHandle(wndHandle), m_mouseState() {
        if (FAILED(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8,
                                reinterpret_cast<void **>(&m_directInputHandle), nullptr))) {
            std::cerr << "Failed to create DirectInput8 instance" << std::endl;
        }

        if (FAILED(m_directInputHandle->CreateDevice(GUID_SysMouse, &m_mouseDevice, nullptr))) {
            std::cerr << "Failed to create mouse device instance" << std::endl;
        }

        if (FAILED(m_mouseDevice->SetDataFormat(&c_dfDIMouse))) {
            std::cerr << "Failed to set device data format" << std::endl;
        }

        if (FAILED(m_mouseDevice->SetCooperativeLevel(wndHandle->getHandle(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) {
            std::cerr << "Failed to set device cooperative level" << std::endl;
        }

        if (FAILED(m_mouseDevice->Acquire())) {
            std::cerr << "Failed to acquire mouse device" << std::endl;
        }
    }

    ~Input() {
        if (FAILED(m_mouseDevice->Unacquire())) {
            std::cerr << "Failed to unacquire mouse device" << std::endl;
        }
        m_mouseDevice->Release();
        m_directInputHandle->Release();
    }

    int32_t getMousePositionX() const {
        return m_currentMousePosition.x;
    }

    int32_t getMousePositionY() const {
        return m_currentMousePosition.y;
    }

    int32_t getDeltaMousePositionX() const {
        return m_deltaMousePosition.x;
    }

    int32_t getDeltaMousePositionY() const {
        return m_deltaMousePosition.y;
    }

    bool getKeyDown(KeyCode key);
    bool getKeyUp(KeyCode key);
    bool getKey(KeyCode key);

    void init();

    void begin();
    void end();
};



#endif //INPUT_H
