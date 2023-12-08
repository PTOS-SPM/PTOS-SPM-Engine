#include "EventSystem.h"
#include "Log.h"

#include "Contexts.h"

#include <ostream>

namespace PTOS {

    EventSystem::EventSystem(Application* app) {
        this->app = app;
        layers = std::vector<EventLayer*>();
    }

    EventSystem::~EventSystem() {
        for (EventLayer* layer : layers)
            delete layer;
        EventTypeLL* iter = types;
        EventTypeLL* todel = types;
        while (iter != nullptr) {
            iter = todel->next;
            delete todel;
        }
        layers.clear();
    }

    bool EventSystem::addLayer(EventLayer* layer) {
        for (size_t i = 0; i < layer->getTypeCount(); i++)
            if (hasType(layer->getTypes()[i])) {
                //PTOS_CORE_ERR("EventType collision on layer {0}: {1}", *layer, layer->getTypes()[i]); //TODO: (C2338) static_assert failed: 'Cannot format an argument. To make type T formattable provide a formatter<T> specialization: https://fmt.dev/latest/api.html#udt
                return false;
            }
        for (size_t i = 0; i < layer->getTypeCount(); i++)
            addType(layer->getTypes()[i]);
        layers.push_back(layer);
        return true;
    }

    bool EventSystem::removeLayer(EventLayer* layer) {
        for (auto lyr = layersBegin(); lyr != layersEnd(); lyr++) {
            if (*lyr == layer) {
                for (size_t i = 0; i < layer->getTypeCount(); i++)
                    removeType(layer->getTypes()[i]);
                layers.erase(lyr);
                return true;
            }
        }
        return false;
    }

    bool EventSystem::removeLayer(size_t index) {
        if (index >= layers.size()) return false;
        EventLayer* layer = layers.at(index);
        for (size_t i = 0; i < layer->getTypeCount(); i++)
            removeType(layer->getTypes()[i]);
        layers.erase(layersBegin() + index);
        return true;
    }

    std::vector<EventLayer*>::const_iterator EventSystem::findLayer(EventLayer* layer) {
        for (auto lyr = layersBegin(); lyr != layersEnd(); lyr++)
            if (*lyr == layer) return lyr;
        return layersEnd();
    }

    bool EventSystem::addType(EventType type) {
        if (types == nullptr) {
            types = new EventTypeLL{ type, nullptr };
            return true;
        }

        EventTypeLL* iter = types;
        EventTypeLL* prev;
        while (iter != nullptr) {
            if (iter->type == type) return false;
            else if (iter->type > type) {
                EventTypeLL* next = iter->next;
                iter->next = new EventTypeLL{ type, next };
                return true;
            }
            else {
                prev = iter;
                iter = iter->next;
            }
        }
        //add to end
        prev->next = new EventTypeLL{ type, nullptr };
    }

    void EventSystem::removeType(EventType type) {
        if (types == nullptr) return;
        else if (types->type == type) {
            delete types;
            types = nullptr;
            return;
        }
        else if (types->next == nullptr) return;

        EventTypeLL* iter = types->next;
        EventTypeLL* prev = types;
        while (iter != nullptr) {
            if (iter->type == type) {
                delete iter;
                prev->next = nullptr;
                return;
            }
            else if (iter->type > type) return;
            else {
                prev = iter;
                iter = iter->next;
            }
        }
    }

    bool EventSystem::hasType(EventType type) {
        EventTypeLL* iter = types;
        while (iter != nullptr) {
            if (iter->type == type)
                return true;
            else if (iter->type > type)
                return false;
            else iter = iter->next;
        }
        return false;
    }

    void EventSystem::handle() {
        std::vector<Event*> propagate;
        std::vector<Event*> propagateNext;
        for (auto lyr = layersBegin(); lyr != layersEnd(); lyr++) {
            EventLayer* layer = *lyr;

            //copy queue and clear original, allow for current events to dispatch events which will be handled on next call to EventSystem::handle

            std::vector<Event*> copyQueue;
            copyQueue.insert(copyQueue.end(), layer->queueBegin(), layer->queueEnd());
            layer->clearQueue();

            for (Event* event : copyQueue)
                handleEvent(event, layer, propagateNext);
            copyQueue.clear();

            for (Event* event : propagate)
                handleEvent(event, layer, propagateNext);

            //reset current and next
            propagate = propagateNext;
            propagateNext.clear();
        }
        //clear remaining events
        for (auto evt : propagate)
            delete evt;
        propagate.clear();
    }

    void EventSystem::handleEvent(Event* event, EventLayer* layer, std::vector<Event*>& pg) {
        EventType type = event->getType();
        auto end = layer->getListenerEnd(type);
        for (auto lst = layer->getListenerBegin(type); lst != end && event->shouldHandle(); lst++) {
            (*lst)(EventContext{this, layer, *lst, event, app});
        }
        if (event->shouldPropagate())
            pg.push_back(event);
        else
            delete event;
    }
}

std::ostream& operator<< (std::ostream& os, PTOS::EventSystem& eventSystem) {
    return os << "<EventSystem at " << &eventSystem << ">";
}
