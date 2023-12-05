#include "EventStack.h"

namespace PTOS {
    void EventStack::pushEvent(const std::string& event) {
        stack.push(event);
    }

    void EventStack::popEvent() {
        if (!stack.empty()) {
            stack.pop();
        }
        else {
            std::cout << "event stack is empty" << std::endl;
        }
    }

    void EventStack::displayStack() const {
        std::cout << "EventStack contents:" << std::endl;
        std::stack<std::string> tempStack = stack;

        while (!tempStack.empty()) {
            std::cout << tempStack.top() << std::endl;
            tempStack.pop();
        }
    }
}