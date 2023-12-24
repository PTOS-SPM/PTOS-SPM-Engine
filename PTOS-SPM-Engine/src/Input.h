#pragma once

#include <unordered_map>
#include <vector>

#include "symbols/eventsystem.h"
#include "symbols/input.h"
#include "symbols/window.h"

#define _PTOS_INPUT_NONE -1
#define _PTOS_INPUT_MOUSEBEGIN 0
#define _PTOS_INPUT_MOUSEEND 7
#define _PTOS_INPUT_KEYBEGIN 8
#define _PTOS_INPUT_KEYEND 166
#define _PTOS_INPUT_KEYPADBEGIN 12
#define _PTOS_INPUT_KEYPADEND 28
#define _PTOS_INPUT_MODBEGIN 155
#define _PTOS_INPUT_MODEND 162

//check if the Input Code is a mouse button
#define PTOS_INPUT_IS_MOUSE(code) code >= _PTOS_INPUT_MOUSEBEGIN && code <= _PTOS_INPUT_MOUSEEND
//check if the Input Code is a keyboard key
#define PTOS_INPUT_IS_KEY(code) code >= _PTOS_INPUT_KEYBEGIN && code <= _PTOS_INPUT_KEYEND
//check if the Input Code is a keyboard modifier key
#define PTOS_INPUT_IS_KEY_MOD(code) code >= _PTOS_INPUT_MODBEGIN && code <= _PTOS_INPUT_MODEND
//check if the Input Code is from a controller
#define PTOS_INPUT_IS_CONTROLLER(code)

namespace PTOS {

	//combined codes for all input (keyboard + mouse + controller)
	enum InputCode {

		INPUT_CODE_NONE = _PTOS_INPUT_NONE,
		
		//Mouse Codes

		INPUT_CODE_MOUSE_LEFT = _PTOS_INPUT_MOUSEBEGIN,
		INPUT_CODE_MOUSE_RIGHT,
		INPUT_CODE_MOUSE_MIDDLE,
		INPUT_CODE_MOUSE_FOUR,
		INPUT_CODE_MOUSE_FIVE,
		INPUT_CODE_MOUSE_SIX,
		INPUT_CODE_MOUSE_SEVEN,
		INPUT_CODE_MOUSE_EIGHT = _PTOS_INPUT_MOUSEEND,

		//Key Codes (loosely follows ascii)

		INPUT_CODE_KEY_BACKSPACE = _PTOS_INPUT_KEYBEGIN,
		INPUT_CODE_KEY_TAB,
		INPUT_CODE_KEY_ENTER,
		INPUT_CODE_KEY_ESC,

		//keypad keys, resumes ascii afterwards

		INPUT_CODE_KEY_KP_0 = _PTOS_INPUT_KEYPADBEGIN,
		INPUT_CODE_KEY_KP_1,
		INPUT_CODE_KEY_KP_2,
		INPUT_CODE_KEY_KP_3,
		INPUT_CODE_KEY_KP_4,
		INPUT_CODE_KEY_KP_5,
		INPUT_CODE_KEY_KP_6,
		INPUT_CODE_KEY_KP_7,
		INPUT_CODE_KEY_KP_8,
		INPUT_CODE_KEY_KP_9,
		INPUT_CODE_KEY_KP_PERIOD,
		INPUT_CODE_KEY_KP_DIVIDE,
		INPUT_CODE_KEY_KP_MULTIPLY,
		INPUT_CODE_KEY_KP_MINUS,
		INPUT_CODE_KEY_KP_PLUS,
		INPUT_CODE_KEY_KP_ENTER,
		INPUT_CODE_KEY_KP_EQUALS = _PTOS_INPUT_KEYPADEND,

		INPUT_CODE_KEY_SPACE = 32,
		INPUT_CODE_KEY_QUOTE = 39,
		INPUT_CODE_KEY_COMMA = 44,
		INPUT_CODE_KEY_MINUS,
		INPUT_CODE_KEY_PERIOD,
		INPUT_CODE_KEY_SLASH,
		INPUT_CODE_KEY_0,
		INPUT_CODE_KEY_1,
		INPUT_CODE_KEY_2,
		INPUT_CODE_KEY_3,
		INPUT_CODE_KEY_4,
		INPUT_CODE_KEY_5,
		INPUT_CODE_KEY_6,
		INPUT_CODE_KEY_7,
		INPUT_CODE_KEY_8,
		INPUT_CODE_KEY_9,
		INPUT_CODE_KEY_SEMICOLON = 59,
		INPUT_CODE_KEY_EQUAL = 61,
		INPUT_CODE_KEY_A = 65,
		INPUT_CODE_KEY_B,
		INPUT_CODE_KEY_C,
		INPUT_CODE_KEY_D,
		INPUT_CODE_KEY_E,
		INPUT_CODE_KEY_F,
		INPUT_CODE_KEY_G,
		INPUT_CODE_KEY_H,
		INPUT_CODE_KEY_I,
		INPUT_CODE_KEY_J,
		INPUT_CODE_KEY_K,
		INPUT_CODE_KEY_L,
		INPUT_CODE_KEY_M,
		INPUT_CODE_KEY_N,
		INPUT_CODE_KEY_O,
		INPUT_CODE_KEY_P,
		INPUT_CODE_KEY_Q,
		INPUT_CODE_KEY_R,
		INPUT_CODE_KEY_S,
		INPUT_CODE_KEY_T,
		INPUT_CODE_KEY_U,
		INPUT_CODE_KEY_V,
		INPUT_CODE_KEY_W,
		INPUT_CODE_KEY_X,
		INPUT_CODE_KEY_Y,
		INPUT_CODE_KEY_Z,
		INPUT_CODE_KEY_LEFT_SQUARE_BRACKET,
		INPUT_CODE_KEY_BACKSLASH,
		INPUT_CODE_KEY_RIGHT_SQUARE_BRACKET,
		INPUT_CODE_KEY_GRAVE = 96,
		INPUT_CODE_KEY_DEL = 127,

		//control keys

		INPUT_CODE_KEY_UP,
		INPUT_CODE_KEY_DOWN,
		INPUT_CODE_KEY_LEFT,
		INPUT_CODE_KEY_RIGHT,
		INPUT_CODE_KEY_INSERT,
		INPUT_CODE_KEY_HOME,
		INPUT_CODE_KEY_END,
		INPUT_CODE_KEY_PAGE_UP,
		INPUT_CODE_KEY_PAGE_DOWN,

		INPUT_CODE_KEY_F1,
		INPUT_CODE_KEY_F2,
		INPUT_CODE_KEY_F3,
		INPUT_CODE_KEY_F4,
		INPUT_CODE_KEY_F5,
		INPUT_CODE_KEY_F6,
		INPUT_CODE_KEY_F7,
		INPUT_CODE_KEY_F8,
		INPUT_CODE_KEY_F9,
		INPUT_CODE_KEY_F10,
		INPUT_CODE_KEY_F11,
		INPUT_CODE_KEY_F12,
		INPUT_CODE_KEY_F13,
		INPUT_CODE_KEY_F14,
		INPUT_CODE_KEY_F15,

		INPUT_CODE_KEY_NUM_LOCK,
		INPUT_CODE_KEY_CAPS_LOCK,
		INPUT_CODE_KEY_SCROLL_LOCK,
		INPUT_CODE_KEY_SHIFT_LEFT = _PTOS_INPUT_MODBEGIN,
		INPUT_CODE_KEY_SHIFT_RIGHT,
		INPUT_CODE_KEY_CONTROL_LEFT,
		INPUT_CODE_KEY_CONTROL_RIGHT,
		INPUT_CODE_KEY_ALT_LEFT,
		INPUT_CODE_KEY_ALT_RIGHT,
		INPUT_CODE_KEY_COMMAND_LEFT,
		INPUT_CODE_KEY_WINDOWS_LEFT = INPUT_CODE_KEY_COMMAND_LEFT, //alias for INPUT_CODE_KEY_COMMAND_LEFT
		INPUT_CODE_KEY_COMMAND_RIGHT = _PTOS_INPUT_MODEND,
		INPUT_CODE_KEY_WINDOWS_RIGHT = INPUT_CODE_KEY_COMMAND_RIGHT, //alias for INPUT_CODE_KEY_COMMAND_RIGHT
		INPUT_CODE_KEY_PRINT,
		INPUT_CODE_KEY_PAUSE = _PTOS_INPUT_KEYEND,

	};

	struct InputState {
		InputState() {}
		InputState(long long count, bool setFrame);

		long long count = 0;
		bool setFrame = false;
	};

	typedef std::unordered_map<InputCode, InputState> WindowInputStateMap;
	typedef std::unordered_map<WindowRenderer*, WindowInputStateMap> InputStateMap;

	class Input final {
	public:

		static void onWindowUpdate(EventContext& ctx);
		static void onWindowKeyDown(EventContext& ctx);
		static void onWindowKeyUp(EventContext& ctx);
		static void onWindowMouseDown(EventContext& ctx);
		static void onWindowMouseUp(EventContext& ctx);

		static void addEventListeners(EventLayer* layer);


		Input(WindowRenderer* renderer);

		inline long long getCount(InputCode code) { return statemap[renderer][code].count; }
		inline bool getHold(InputCode code) { return getCount(code) > 1; }
		inline bool getDown(InputCode code) { return getCount(code) == 1; }
		inline bool getUp(InputCode code) { return getCount(code) == -1; }
		inline bool getAny(InputCode code) { return getCount(code) != 0; }

		WindowInputStateMap getHoldAll();
		WindowInputStateMap getDownAll();
		WindowInputStateMap getUpAll();
		WindowInputStateMap getAnyAll();

		inline WindowRenderer* getRenderer() { return renderer; }

	private:
		static InputStateMap statemap;

		WindowRenderer* renderer;
	};
}