#include "ApplicationEvent.h"

namespace PTOS {
	ApplicationEvent::ApplicationEvent(ApplicationEventType type) :
		Event((EventType)type) { }
}