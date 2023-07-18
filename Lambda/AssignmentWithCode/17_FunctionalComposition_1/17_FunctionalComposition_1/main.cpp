#include <iostream>
#include <functional>

/*
 
 Event handling :
 
 Functional composition is beneficial in event-driven programming where you need to handle multiple events or callbacks.
 You can create separate event handlers for different types of events
 and then compose them together to form a single handler that can handle multiple events.

 */

// Event handler for event A
void handleEventA(int value) {
    std::cout << "Handling event A: " << value << std::endl;
}

// Event handler for event B
void handleEventB(float value) {
    std::cout << "Handling event B: " << value << std::endl;
}

// Event handler for event C
void handleEventC(const std::string& value) {
    std::cout << "Handling event C: " << value << std::endl;
}

// Function to compose event handlers
template <typename... EventHandlers>
auto composeEventHandlers(EventHandlers... handlers) {
    return [=](auto&&... args) {
        (handlers(std::forward<decltype(args)>(args)), ...);
    };
}

int main() {
    // Create individual event handlers
    // ASSIGNMENT : think about overide
    auto eventHandlerA = [](int value) { handleEventA(value); };
    auto eventHandlerB = [](float value) { handleEventB(value); };
    auto eventHandlerC = [](const std::string& value) { handleEventC(value); };

    // Compose event handlers together
    auto composedEventHandler = composeEventHandlers(eventHandlerA, eventHandlerB, eventHandlerC);

    // Simulate events
    int eventAValue = 10;
    float eventBValue = 3.14f;
    std::string eventCValue = "Hello";

    // Handle multiple events using the composed event handler
    // returns the lambda fun handle lets pass argument to it now
    composedEventHandler(eventAValue, eventBValue, eventCValue);

    return 0;
}
