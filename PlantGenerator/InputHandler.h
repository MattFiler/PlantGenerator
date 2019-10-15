#pragma once

#include <vector>

enum WindowsKey {
	BACKSPACE = 8,
	TAB = 9,
	ENTER = 13,
	SHIFT = 16,
	CTRL = 17,
	ALT = 18,
	PAUSE_BREAK = 19,
	CAPS_LOCK = 20,
	ESCAPE = 27,
	PAGE_UP = 33,
	PAGE_DOWN = 34,
	END = 35,
	HOME = 36,
	LEFT_ARROW = 37,
	UP_ARROW = 38,
	RIGHT_ARROW = 39,
	DOWN_ARROW = 40,
	INSERT = 45,
	//DELETE = 46,
	A0 = 48,
	A1 = 49,
	A2 = 50,
	A3 = 51,
	A4 = 52,
	A5 = 53,
	A6 = 54,
	A7 = 55,
	A8 = 56,
	A9 = 57,
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
	LEFT_WINDOW_KEY = 91,
	RIGHT_WINDOW_KEY = 92,
	SELECT_KEY = 93,
	NUMPAD_0 = 96,
	NUMPAD_1 = 97,
	NUMPAD_2 = 98,
	NUMPAD_3 = 99,
	NUMPAD_4 = 100,
	NUMPAD_5 = 101,
	NUMPAD_6 = 102,
	NUMPAD_7 = 103,
	NUMPAD_8 = 104,
	NUMPAD_9 = 105,
	MULTIPLY = 106,
	ADD = 107,
	SUBTRACT = 109,
	DECIMAL_POINT = 110,
	DIVIDE = 111,
	F1 = 112,
	F2 = 113,
	F3 = 114,
	F4 = 115,
	F5 = 116,
	F6 = 117,
	F7 = 118,
	F8 = 119,
	F9 = 120,
	F10 = 121,
	F11 = 122,
	F12 = 123,
	NUM_LOCK = 144,
	SCROLL_LOCK = 145,
	SEMI_COLON = 186,
	EQUAL_SIGN = 187,
	COMMA = 188,
	DASH = 189,
	PERIOD = 190,
	FORWARD_SLASH = 191,
	GRAVE_ACCENT = 192,
	OPEN_BRACKET = 219,
	BACK_SLASH = 220,
	CLOSE_BRAKET = 221,
	SINGLE_QUOTE = 222
};

struct InputState {
	InputState(WindowsKey _i) {
		index = _i;
	}
	WindowsKey index;
	bool isPressed = false;
};

class InputHandler
{
public:
	InputHandler();
	~InputHandler() = default;

	/* Populate the key list (this is super gross!!) */
	static void Setup()
	{
		if (allInputs.size() != 0) return;

		InputState BACKSPACE = InputState(WindowsKey::BACKSPACE);
		allInputs.push_back(BACKSPACE);
		InputState TAB = InputState(WindowsKey::TAB);
		allInputs.push_back(TAB);
		InputState ENTER = InputState(WindowsKey::ENTER);
		allInputs.push_back(ENTER);
		InputState SHIFT = InputState(WindowsKey::SHIFT);
		allInputs.push_back(SHIFT);
		InputState CTRL = InputState(WindowsKey::CTRL);
		allInputs.push_back(CTRL);
		InputState ALT = InputState(WindowsKey::ALT);
		allInputs.push_back(ALT);
		InputState PAUSE_BREAK = InputState(WindowsKey::PAUSE_BREAK);
		allInputs.push_back(PAUSE_BREAK);
		InputState CAPS_LOCK = InputState(WindowsKey::CAPS_LOCK);
		allInputs.push_back(CAPS_LOCK);
		InputState ESCAPE = InputState(WindowsKey::ESCAPE);
		allInputs.push_back(ESCAPE);
		InputState PAGE_UP = InputState(WindowsKey::PAGE_UP);
		allInputs.push_back(PAGE_UP);
		InputState PAGE_DOWN = InputState(WindowsKey::PAGE_DOWN);
		allInputs.push_back(PAGE_DOWN);
		InputState END = InputState(WindowsKey::END);
		allInputs.push_back(END);
		InputState HOME = InputState(WindowsKey::HOME);
		allInputs.push_back(HOME);
		InputState LEFT_ARROW = InputState(WindowsKey::LEFT_ARROW);
		allInputs.push_back(LEFT_ARROW);
		InputState UP_ARROW = InputState(WindowsKey::UP_ARROW);
		allInputs.push_back(UP_ARROW);
		InputState RIGHT_ARROW = InputState(WindowsKey::RIGHT_ARROW);
		allInputs.push_back(RIGHT_ARROW);
		InputState DOWN_ARROW = InputState(WindowsKey::DOWN_ARROW);
		allInputs.push_back(DOWN_ARROW);
		InputState INSERT = InputState(WindowsKey::INSERT);
		allInputs.push_back(INSERT);
		//InputState DELETE = InputState(WindowsKey::DELETE);
		//allInputs.push_back(DELETE);
		InputState A0 = InputState(WindowsKey::A0);
		allInputs.push_back(A0);
		InputState A1 = InputState(WindowsKey::A1);
		allInputs.push_back(A1);
		InputState A2 = InputState(WindowsKey::A2);
		allInputs.push_back(A2);
		InputState A3 = InputState(WindowsKey::A3);
		allInputs.push_back(A3);
		InputState A4 = InputState(WindowsKey::A4);
		allInputs.push_back(A4);
		InputState A5 = InputState(WindowsKey::A5);
		allInputs.push_back(A5);
		InputState A6 = InputState(WindowsKey::A6);
		allInputs.push_back(A6);
		InputState A7 = InputState(WindowsKey::A7);
		allInputs.push_back(A7);
		InputState A8 = InputState(WindowsKey::A8);
		allInputs.push_back(A8);
		InputState A9 = InputState(WindowsKey::A9);
		allInputs.push_back(A9);
		InputState A = InputState(WindowsKey::A);
		allInputs.push_back(A);
		InputState B = InputState(WindowsKey::B);
		allInputs.push_back(B);
		InputState C = InputState(WindowsKey::C);
		allInputs.push_back(C);
		InputState D = InputState(WindowsKey::D);
		allInputs.push_back(D);
		InputState E = InputState(WindowsKey::E);
		allInputs.push_back(E);
		InputState F = InputState(WindowsKey::F);
		allInputs.push_back(F);
		InputState G = InputState(WindowsKey::G);
		allInputs.push_back(G);
		InputState H = InputState(WindowsKey::H);
		allInputs.push_back(H);
		InputState I = InputState(WindowsKey::I);
		allInputs.push_back(I);
		InputState J = InputState(WindowsKey::J);
		allInputs.push_back(J);
		InputState K = InputState(WindowsKey::K);
		allInputs.push_back(K);
		InputState L = InputState(WindowsKey::L);
		allInputs.push_back(L);
		InputState M = InputState(WindowsKey::M);
		allInputs.push_back(M);
		InputState N = InputState(WindowsKey::N);
		allInputs.push_back(N);
		InputState O = InputState(WindowsKey::O);
		allInputs.push_back(O);
		InputState P = InputState(WindowsKey::P);
		allInputs.push_back(P);
		InputState Q = InputState(WindowsKey::Q);
		allInputs.push_back(Q);
		InputState R = InputState(WindowsKey::R);
		allInputs.push_back(R);
		InputState S = InputState(WindowsKey::S);
		allInputs.push_back(S);
		InputState T = InputState(WindowsKey::T);
		allInputs.push_back(T);
		InputState U = InputState(WindowsKey::U);
		allInputs.push_back(U);
		InputState V = InputState(WindowsKey::V);
		allInputs.push_back(V);
		InputState W = InputState(WindowsKey::W);
		allInputs.push_back(W);
		InputState X = InputState(WindowsKey::X);
		allInputs.push_back(X);
		InputState Y = InputState(WindowsKey::Y);
		allInputs.push_back(Y);
		InputState Z = InputState(WindowsKey::Z);
		allInputs.push_back(Z);
		InputState LEFT_WINDOW_KEY = InputState(WindowsKey::LEFT_WINDOW_KEY);
		allInputs.push_back(LEFT_WINDOW_KEY);
		InputState RIGHT_WINDOW_KEY = InputState(WindowsKey::RIGHT_WINDOW_KEY);
		allInputs.push_back(RIGHT_WINDOW_KEY);
		InputState SELECT_KEY = InputState(WindowsKey::SELECT_KEY);
		allInputs.push_back(SELECT_KEY);
		InputState NUMPAD_0 = InputState(WindowsKey::NUMPAD_0);
		allInputs.push_back(NUMPAD_0);
		InputState NUMPAD_1 = InputState(WindowsKey::NUMPAD_1);
		allInputs.push_back(NUMPAD_1);
		InputState NUMPAD_2 = InputState(WindowsKey::NUMPAD_2);
		allInputs.push_back(NUMPAD_2);
		InputState NUMPAD_3 = InputState(WindowsKey::NUMPAD_3);
		allInputs.push_back(NUMPAD_3);
		InputState NUMPAD_4 = InputState(WindowsKey::NUMPAD_4);
		allInputs.push_back(NUMPAD_4);
		InputState NUMPAD_5 = InputState(WindowsKey::NUMPAD_5);
		allInputs.push_back(NUMPAD_5);
		InputState NUMPAD_6 = InputState(WindowsKey::NUMPAD_6);
		allInputs.push_back(NUMPAD_6);
		InputState NUMPAD_7 = InputState(WindowsKey::NUMPAD_7);
		allInputs.push_back(NUMPAD_7);
		InputState NUMPAD_8 = InputState(WindowsKey::NUMPAD_8);
		allInputs.push_back(NUMPAD_8);
		InputState NUMPAD_9 = InputState(WindowsKey::NUMPAD_9);
		allInputs.push_back(NUMPAD_9);
		InputState MULTIPLY = InputState(WindowsKey::MULTIPLY);
		allInputs.push_back(MULTIPLY);
		InputState ADD = InputState(WindowsKey::ADD);
		allInputs.push_back(ADD);
		InputState SUBTRACT = InputState(WindowsKey::SUBTRACT);
		allInputs.push_back(SUBTRACT);
		InputState DECIMAL_POINT = InputState(WindowsKey::DECIMAL_POINT);
		allInputs.push_back(DECIMAL_POINT);
		InputState DIVIDE = InputState(WindowsKey::DIVIDE);
		allInputs.push_back(DIVIDE);
		InputState F1 = InputState(WindowsKey::F1);
		allInputs.push_back(F1);
		InputState F2 = InputState(WindowsKey::F2);
		allInputs.push_back(F2);
		InputState F3 = InputState(WindowsKey::F3);
		allInputs.push_back(F3);
		InputState F4 = InputState(WindowsKey::F4);
		allInputs.push_back(F4);
		InputState F5 = InputState(WindowsKey::F5);
		allInputs.push_back(F5);
		InputState F6 = InputState(WindowsKey::F6);
		allInputs.push_back(F6);
		InputState F7 = InputState(WindowsKey::F7);
		allInputs.push_back(F7);
		InputState F8 = InputState(WindowsKey::F8);
		allInputs.push_back(F8);
		InputState F9 = InputState(WindowsKey::F9);
		allInputs.push_back(F9);
		InputState F10 = InputState(WindowsKey::F10);
		allInputs.push_back(F10);
		InputState F11 = InputState(WindowsKey::F11);
		allInputs.push_back(F11);
		InputState F12 = InputState(WindowsKey::F12);
		allInputs.push_back(F12);
		InputState NUM_LOCK = InputState(WindowsKey::NUM_LOCK);
		allInputs.push_back(NUM_LOCK);
		InputState SCROLL_LOCK = InputState(WindowsKey::SCROLL_LOCK);
		allInputs.push_back(SCROLL_LOCK);
		InputState SEMI_COLON = InputState(WindowsKey::SEMI_COLON);
		allInputs.push_back(SEMI_COLON);
		InputState EQUAL_SIGN = InputState(WindowsKey::EQUAL_SIGN);
		allInputs.push_back(EQUAL_SIGN);
		InputState COMMA = InputState(WindowsKey::COMMA);
		allInputs.push_back(COMMA);
		InputState DASH = InputState(WindowsKey::DASH);
		allInputs.push_back(DASH);
		InputState PERIOD = InputState(WindowsKey::PERIOD);
		allInputs.push_back(PERIOD);
		InputState FORWARD_SLASH = InputState(WindowsKey::FORWARD_SLASH);
		allInputs.push_back(FORWARD_SLASH);
		InputState GRAVE_ACCENT = InputState(WindowsKey::GRAVE_ACCENT);
		allInputs.push_back(GRAVE_ACCENT);
		InputState OPEN_BRACKET = InputState(WindowsKey::OPEN_BRACKET);
		allInputs.push_back(OPEN_BRACKET);
		InputState BACK_SLASH = InputState(WindowsKey::BACK_SLASH);
		allInputs.push_back(BACK_SLASH);
		InputState CLOSE_BRAKET = InputState(WindowsKey::CLOSE_BRAKET);
		allInputs.push_back(CLOSE_BRAKET);
		InputState SINGLE_QUOTE = InputState(WindowsKey::SINGLE_QUOTE);
		allInputs.push_back(SINGLE_QUOTE);
	}

	/* Set a key's pressed state */
	static void SetKeyState(WindowsKey _key, bool _pressed) {
		for (int i = 0; i < allInputs.size(); i++) {
			if (allInputs[i].index == _key) {
				allInputs[i].isPressed = _pressed;
				return;
			}
		}
		//Debug::Log("Trying to SetKeyState for an unknown key!");
	}

	/* Get a key's pressed state */
	static bool KeyPressed(WindowsKey _key) {
		for (int i = 0; i < allInputs.size(); i++) {
			if (allInputs[i].index == _key) {
				return allInputs[i].isPressed;
			}
		}
		//Debug::Log("Trying to check KeyPressed for an unknown key!");
		return false;
	}

protected:
	static std::vector<InputState> allInputs;
};

