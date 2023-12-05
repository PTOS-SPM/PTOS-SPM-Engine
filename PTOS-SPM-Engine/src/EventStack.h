#pragma once

#include <iostream>
#include <stack>
#include <string>

namespace PTOS {
	class EventStack {
	private:
		std::stack<std::string> stack;

	public:
		void pushEvent(const std::string& event) {
			stack.push(event);
		}

		void popEvent() {
			if (!stack.empty()) {
				stack.pop();
			} else {
				std::cout << "event stack is empty" << std::endl;
			}
		}

		void displayStack() const {
			std::cout << "EventStack contents:" << std::endl;
			std::stack<std::string> tempStack = stack;

			while (!tempStack.empty()) {
				std::cout << tempStack.top() << std::endl;
				tempStack.pop();
			}

		}
	};
};

