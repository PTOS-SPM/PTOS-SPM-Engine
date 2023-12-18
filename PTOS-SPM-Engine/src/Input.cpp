#include "EventLayer.h"
#include "Input.h"
#include "WindowEvent.h"
#include "WindowRenderer.h"

//TODO convert windowevents and renderers to use InputCode instead of navtive keycodes
#define _PTOS_INPUT_HANDLE_EVENT(codeMethod, state) \
	WindowEvent* event = (WindowEvent*)ctx.event; \
	WindowRenderer* renderer = event->getRenderer(); \
	statemap[renderer][(InputCode)event-> codeMethod ()] = InputState(state, true); \
	event->stopHandle();

//DEBUG
#include "Log.h"
namespace PTOS {

	InputState::InputState(long long count, bool setFrame) {
		this->count = count;
		this->setFrame = setFrame;
	}

	InputStateMap Input::statemap;

	Input::Input(WindowRenderer* renderer) {
		this->renderer = renderer;
	}

	WindowInputStateMap Input::getHoldAll() {
		WindowInputStateMap rtv;
		if (!statemap.count(renderer)) return rtv;
		for (auto &pair : statemap[renderer])
			if (pair.second.count > 1)
				rtv[pair.first] = pair.second;
		return rtv;
	}

	WindowInputStateMap Input::getDownAll() {
		WindowInputStateMap rtv;
		if (!statemap.count(renderer)) return rtv;
		for (auto &pair : statemap[renderer])
			if (pair.second.count == 1)
				rtv[pair.first] = pair.second;
		return rtv;
	}

	WindowInputStateMap Input::getUpAll() {
		WindowInputStateMap rtv;
		if (!statemap.count(renderer)) return rtv;
		for (auto &pair : statemap[renderer])
			if (pair.second.count == -1)
				rtv[pair.first] = pair.second;
		return rtv;
	}

	void Input::onWindowUpdate(EventContext& ctx) {
		WindowEvent* event = (WindowEvent*)ctx.event;
		WindowRenderer* renderer = event->getRenderer();

		if (!Input::statemap.count(renderer)) return;

		for (auto &pair : Input::statemap[renderer]) {
			if (pair.second.setFrame)
				Input::statemap[renderer][pair.first].setFrame = false;
			else if (pair.second.count != 0)
				Input::statemap[renderer][pair.first].count += 1;
		}
	}

	void Input::onWindowKeyDown(EventContext& ctx) {
		_PTOS_INPUT_HANDLE_EVENT(getKeyCode, 1)
	}

	void Input::onWindowKeyUp(EventContext& ctx) {
		_PTOS_INPUT_HANDLE_EVENT(getKeyCode, -1)
	}

	void Input::onWindowMouseDown(EventContext& ctx) {
		_PTOS_INPUT_HANDLE_EVENT(getMouseButton, 1)
	}

	void Input::onWindowMouseUp(EventContext& ctx) {
		_PTOS_INPUT_HANDLE_EVENT(getMouseButton, -1)
	}

	void Input::addEventListeners(EventLayer* layer) {
		//NOTE: add any new Input event listeners to this array

		void(*listeners[])(EventContext&) = { onWindowUpdate, onWindowKeyDown, onWindowKeyUp, onWindowMouseDown, onWindowMouseUp };
		size_t listener_count = sizeof(listeners) / sizeof(listeners[0]);

		//do not add listeners if they have already been added
		for (size_t i = 0; i < listener_count; i++)
			if (layer->hasListener(listeners[i])) return;

		layer->addListener(WINDOW_UPDATE, onWindowUpdate);
		layer->addListener(WINDOW_KEY_DOWN, onWindowKeyDown);
		layer->addListener(WINDOW_KEY_UP, onWindowKeyUp);
		layer->addListener(WINDOW_MOUSE_DOWN, onWindowMouseDown);
		layer->addListener(WINDOW_MOUSE_UP, onWindowMouseUp);
	}
}