#pragma once

#include "pch.h"

struct ThICC_InputData {
	std::unique_ptr<DirectX::GamePad> m_gamepad;
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;

	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;
	DirectX::Mouse::ButtonStateTracker m_mouseButtonTracker;
	DirectX::GamePad::ButtonStateTracker m_gamepadButtonTracker[4];
	DirectX::Mouse::State m_mouseState;

	int TEST = 0;
};