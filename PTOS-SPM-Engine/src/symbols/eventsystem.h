#pragma once

#include "Core.h"

namespace PTOS {
	class PTOS_API Event;
	class PTOS_API EventLayer;
	class PTOS_API EventSystem;
	struct PTOS_API EventContext;
	typedef unsigned short EventType;
	typedef void (*EventListenerFunc)(EventContext&);
}