#include "EventSystem.h"
#include "Input.h"
#include "Window.h"
#include "WindowRenderer.h"

#define _PTOS_INPUT_HANDLE_EVENT(state) \
	WindowEvent* event = (WindowEvent*)ctx.event.data; \
	statemap[event->windowRenderer][event->code] = InputState(state, true); \
	return {};


namespace PTOS {

	InputState::InputState(long long count, bool setFrame) {
		this->count = count;
		this->setFrame = setFrame;
	}

	InputStateMap Input::statemap;

	Input::Input(WindowRenderer* windowRenderer) {
		this->windowRenderer = windowRenderer;
	}

	WindowInputStateMap Input::getHoldAll() {
		WindowInputStateMap rtv;
		if (!statemap.count(windowRenderer)) return rtv;
		for (auto& pair : statemap[windowRenderer])
			if (pair.second.count > 1)
				rtv[pair.first] = pair.second;
		return rtv;
	}

	WindowInputStateMap Input::getDownAll() {
		WindowInputStateMap rtv;
		if (!statemap.count(windowRenderer)) return rtv;
		for (auto& pair : statemap[windowRenderer])
			if (pair.second.count == 1)
				rtv[pair.first] = pair.second;
		return rtv;
	}

	WindowInputStateMap Input::getUpAll() {
		WindowInputStateMap rtv;
		if (!statemap.count(windowRenderer)) return rtv;
		for (auto& pair : statemap[windowRenderer])
			if (pair.second.count == -1)
				rtv[pair.first] = pair.second;
		return rtv;
	}

	WindowInputStateMap Input::getAnyAll() {
		WindowInputStateMap rtv;
		if (!statemap.count(windowRenderer)) return rtv;
		for (auto& pair : statemap[windowRenderer])
			if (pair.second.count != 0)
				rtv[pair.first] = pair.second;
		return rtv;
	}

	EventResult Input::onWindowUpdate(const EventContext& ctx) {
		WindowEvent* event = (WindowEvent*)ctx.event.data;
		WindowRenderer* windowRenderer = event->windowRenderer;
		if (!Input::statemap.count(windowRenderer))
			return {};

		for (auto& pair : Input::statemap[windowRenderer]) {
			if (pair.second.setFrame)
				Input::statemap[windowRenderer][pair.first].setFrame = false;
			else if (pair.second.count != 0)
				Input::statemap[windowRenderer][pair.first].count += 1;
		}
		return {};
	}

	EventResult Input::onWindowKeyDown(const EventContext& ctx) {
		_PTOS_INPUT_HANDLE_EVENT(1)
	}

	EventResult Input::onWindowKeyUp(const EventContext& ctx) {
		_PTOS_INPUT_HANDLE_EVENT(-1)
	}

	EventResult Input::onWindowMouseDown(const EventContext& ctx) {
		_PTOS_INPUT_HANDLE_EVENT(1)
	}

	EventResult Input::onWindowMouseUp(const EventContext& ctx) {
		_PTOS_INPUT_HANDLE_EVENT(-1)
	}

	void Input::addEventListeners(EventLayer* layer) {
		//NOTE: add any new Input event listeners to this array

		EventType listenerTypes[] = {EventTypes::WINDOW_UPDATE, EventTypes::WINDOW_KEY_DOWN, EventTypes::WINDOW_KEY_UP, EventTypes::WINDOW_MOUSE_DOWN, EventTypes::WINDOW_MOUSE_UP};
		EventListenerFunc listeners[] = {onWindowUpdate, onWindowKeyDown, onWindowKeyUp, onWindowMouseDown, onWindowMouseUp};
		size_t listener_count = sizeof(listeners) / sizeof(listeners[0]);

		//do not add listeners if they have already been added
		for (size_t i = 0; i < listener_count; i++) {
			if (layer->hasListener(listenerTypes[i], listeners[i]))
				return;
		}
		for (size_t i = 0; i < listener_count; i++) {
			layer->addListener(listenerTypes[i], listeners[i]);
		}
	}
}