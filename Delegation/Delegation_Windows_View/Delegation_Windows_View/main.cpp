//
//  main.cpp
//  Delegation_Windows_View
//
//  Created by Sathya Babu on 13/07/23.
//  Hide the implementation by interface
#include <iostream>

// Interface for the view components
class WindowComponent {
public:
    virtual void renderViewComponent() const = 0;
};

// Button class implementing the WindowComponent interface
class Button : public WindowComponent {
public:
    void renderViewComponent() const override {
        std::cout << "Button: Drawn!" << std::endl;
    }
};

// Radio button class implementing the WindowComponent interface
class RadioButton : public WindowComponent {
public:
    void renderViewComponent() const override {
        std::cout << "Radio Button: Drawn!" << std::endl;
    }
};

// Scroll bar class implementing the WindowComponent interface
class ScrollBar : public WindowComponent {
public:
    void renderViewComponent() const override {
        std::cout << "Scroll Bar: Drawn!" << std::endl;
    }
};

// View class representing the parent view
class View {
private:
    WindowComponent* component;

public:
    View(WindowComponent* comp) : component(comp) {}

    void renderViewComponent() const {
        if (component) {
            component->renderViewComponent();
        }
    }
};

int main() {
    // Create the view components
    Button button;
    RadioButton radioButton;
    ScrollBar scrollBar;

    // Create the view and delegate the components
    View view(&button);
    view.renderViewComponent();

    view = View(&radioButton);
    view.renderViewComponent();

    view = View(&scrollBar);
    view.renderViewComponent();

    return 0;
}
