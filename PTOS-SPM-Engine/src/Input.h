#pragma once

#pragma once

#include <unordered_map>
#include <vector>

#include "predefines.h"

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
	namespace Inputs {
		enum Code {

			CODE_NONE = _PTOS_INPUT_NONE,

			//Mouse Codes

			CODE_MOUSE_LEFT = _PTOS_INPUT_MOUSEBEGIN,
			CODE_MOUSE_RIGHT,
			CODE_MOUSE_MIDDLE,
			CODE_MOUSE_FOUR,
			CODE_MOUSE_FIVE,
			CODE_MOUSE_SIX,
			CODE_MOUSE_SEVEN,
			CODE_MOUSE_EIGHT = _PTOS_INPUT_MOUSEEND,

			//Key Codes (loosely follows ascii)

			CODE_KEY_BACKSPACE = _PTOS_INPUT_KEYBEGIN,
			CODE_KEY_TAB,
			CODE_KEY_ENTER,
			CODE_KEY_ESC,

			//keypad keys, resumes ascii afterwards

			CODE_KEY_KP_0 = _PTOS_INPUT_KEYPADBEGIN,
			CODE_KEY_KP_1,
			CODE_KEY_KP_2,
			CODE_KEY_KP_3,
			CODE_KEY_KP_4,
			CODE_KEY_KP_5,
			CODE_KEY_KP_6,
			CODE_KEY_KP_7,
			CODE_KEY_KP_8,
			CODE_KEY_KP_9,
			CODE_KEY_KP_PERIOD,
			CODE_KEY_KP_DIVIDE,
			CODE_KEY_KP_MULTIPLY,
			CODE_KEY_KP_MINUS,
			CODE_KEY_KP_PLUS,
			CODE_KEY_KP_ENTER,
			CODE_KEY_KP_EQUALS = _PTOS_INPUT_KEYPADEND,

			CODE_KEY_SPACE = 32,
			CODE_KEY_QUOTE = 39,
			CODE_KEY_COMMA = 44,
			CODE_KEY_MINUS,
			CODE_KEY_PERIOD,
			CODE_KEY_SLASH,
			CODE_KEY_0,
			CODE_KEY_1,
			CODE_KEY_2,
			CODE_KEY_3,
			CODE_KEY_4,
			CODE_KEY_5,
			CODE_KEY_6,
			CODE_KEY_7,
			CODE_KEY_8,
			CODE_KEY_9,
			CODE_KEY_SEMICOLON = 59,
			CODE_KEY_EQUAL = 61,
			CODE_KEY_A = 65,
			CODE_KEY_B,
			CODE_KEY_C,
			CODE_KEY_D,
			CODE_KEY_E,
			CODE_KEY_F,
			CODE_KEY_G,
			CODE_KEY_H,
			CODE_KEY_I,
			CODE_KEY_J,
			CODE_KEY_K,
			CODE_KEY_L,
			CODE_KEY_M,
			CODE_KEY_N,
			CODE_KEY_O,
			CODE_KEY_P,
			CODE_KEY_Q,
			CODE_KEY_R,
			CODE_KEY_S,
			CODE_KEY_T,
			CODE_KEY_U,
			CODE_KEY_V,
			CODE_KEY_W,
			CODE_KEY_X,
			CODE_KEY_Y,
			CODE_KEY_Z,
			CODE_KEY_LEFT_SQUARE_BRACKET,
			CODE_KEY_BACKSLASH,
			CODE_KEY_RIGHT_SQUARE_BRACKET,
			CODE_KEY_GRAVE = 96,
			CODE_KEY_DEL = 127,

			//control keys

			CODE_KEY_UP,
			CODE_KEY_DOWN,
			CODE_KEY_LEFT,
			CODE_KEY_RIGHT,
			CODE_KEY_INSERT,
			CODE_KEY_HOME,
			CODE_KEY_END,
			CODE_KEY_PAGE_UP,
			CODE_KEY_PAGE_DOWN,

			CODE_KEY_F1,
			CODE_KEY_F2,
			CODE_KEY_F3,
			CODE_KEY_F4,
			CODE_KEY_F5,
			CODE_KEY_F6,
			CODE_KEY_F7,
			CODE_KEY_F8,
			CODE_KEY_F9,
			CODE_KEY_F10,
			CODE_KEY_F11,
			CODE_KEY_F12,
			CODE_KEY_F13,
			CODE_KEY_F14,
			CODE_KEY_F15,

			CODE_KEY_NUM_LOCK,
			CODE_KEY_CAPS_LOCK,
			CODE_KEY_SCROLL_LOCK,
			CODE_KEY_SHIFT_LEFT = _PTOS_INPUT_MODBEGIN,
			CODE_KEY_SHIFT_RIGHT,
			CODE_KEY_CONTROL_LEFT,
			CODE_KEY_CONTROL_RIGHT,
			CODE_KEY_ALT_LEFT,
			CODE_KEY_ALT_RIGHT,
			CODE_KEY_COMMAND_LEFT,
			CODE_KEY_WINDOWS_LEFT = CODE_KEY_COMMAND_LEFT, //alias for INPUT_CODE_KEY_COMMAND_LEFT
			CODE_KEY_COMMAND_RIGHT = _PTOS_INPUT_MODEND,
			CODE_KEY_WINDOWS_RIGHT = CODE_KEY_COMMAND_RIGHT, //alias for INPUT_CODE_KEY_COMMAND_RIGHT
			CODE_KEY_PRINT,
			CODE_KEY_PAUSE = _PTOS_INPUT_KEYEND,

		};
	}

	struct InputState {
		InputState() {}
		InputState(long long count, bool setFrame);

		long long count = 0;
		bool setFrame = false;
	};

	typedef std::unordered_map<Inputs::Code, InputState> WindowInputStateMap;
	typedef std::unordered_map<WindowRenderer*, WindowInputStateMap> InputStateMap;

	class Input final {
	public:

		static EventResult onWindowUpdate(const EventContext& ctx);
		static EventResult onWindowKeyDown(const EventContext& ctx);
		static EventResult onWindowKeyUp(const EventContext& ctx);
		static EventResult onWindowMouseDown(const EventContext& ctx);
		static EventResult onWindowMouseUp(const EventContext& ctx);

		static void addEventListeners(EventLayer* layer);


		Input(WindowRenderer* windowRenderer);

		inline long long getCount(Inputs::Code code) { return statemap[windowRenderer][code].count; }
		inline bool getHold(Inputs::Code code) { return getCount(code) > 1; }
		inline bool getDown(Inputs::Code code) { return getCount(code) == 1; }
		inline bool getUp(Inputs::Code code) { return getCount(code) == -1; }
		inline bool getAny(Inputs::Code code) { return getCount(code) != 0; }

		WindowInputStateMap getHoldAll();
		WindowInputStateMap getDownAll();
		WindowInputStateMap getUpAll();
		WindowInputStateMap getAnyAll();

		inline WindowRenderer* getWindowRenderer() { return windowRenderer; }

	private:
		static InputStateMap statemap;

		WindowRenderer* windowRenderer;
	};
}