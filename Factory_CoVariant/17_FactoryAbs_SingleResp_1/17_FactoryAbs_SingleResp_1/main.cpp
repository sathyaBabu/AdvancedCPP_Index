//
//  main.cpp
//  17_FactoryAbs_SingleResp_1
//
//  Created by Sathya Babu on 18/02/23.
//
/*
 
 The Single Responsibility Principle (SRP) states that a class should have only one reason to change. This means that a class should have only one responsibility, and that responsibility should be encapsulated within the class.

 In the case of the GUIFactory class in the previous example, it has two responsibilities: creating Button and Checkbox objects. In order to apply the SRP to this class, we could split it into two separate classes, each responsible for creating one type of object.

 Here's an updated implementation of the GUIFactory and related classes that demonstrates this:


 
 In this updated implementation, we have split the creation of Button and Checkbox objects into two separate classes: ButtonFactory and CheckboxFactory, respectively. Each factory class has a single responsibility of creating one type of object.

 We then update the GUIFactory class to take instances of ButtonFactory and CheckboxFactory as constructor parameters, and use them to create the Button and Checkbox objects in the createButton() and createCheckbox() methods, respectively.

 This separation of concerns allows each class to focus on its own responsibility and
 
 
 
 n this example, we have an abstract Button class and concrete implementations of it for both Mac and Windows operating systems. Similarly, we have an abstract Checkbox class and concrete implementations of it for both Mac and Windows.

 We then define an abstract GUIFactory class that has two virtual methods: createButton() and createCheckbox(). Each concrete factory implementation (MacGUIFactory and WindowsGUIFactory) provides its own implementation of these methods to create the corresponding Button and Checkbox objects.

 In the main() function, we instantiate the appropriate concrete GUIFactory based on the operating system and use it to create Button and Checkbox objects. We can then call the render() method on each of these objects to render them to the screen.
 Rendering Windows button.
 Rendering Windows checkbox.
 Program ended with exit code: 0
 */

#include <iostream>
#include <memory>

// Abstract product interface
class Button {
public:
    virtual void render() = 0;
    virtual ~Button() {}
};

// Concrete product implementation for Mac
class MacButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Mac button." << std::endl;
    }
};

// Concrete product implementation for Windows
class WindowsButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Windows button." << std::endl;
    }
};

// Abstract product interface
class Checkbox {
public:
    virtual void render() = 0;
    virtual ~Checkbox() {}
};

// Concrete product implementation for Mac
class MacCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Rendering Mac checkbox." << std::endl;
    }
};

// Concrete product implementation for Windows
class WindowsCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Rendering Windows checkbox." << std::endl;
    }
};

// Abstract factory interface
class GUIFactory {
public:
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
    virtual ~GUIFactory() {}
};

// Concrete factory implementation for Mac
class MacGUIFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacButton>();
    }

    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<MacCheckbox>();
    }
};

// Concrete factory implementation for Windows
class WindowsGUIFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }

    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<WindowsCheckbox>();
    }
};

int main() {
    std::unique_ptr<GUIFactory> factory;
    std::string os = "Windows"; // or "Mac"
    if (os == "Windows") {
        factory = std::make_unique<WindowsGUIFactory>();
    } else if (os == "Mac") {
        factory = std::make_unique<MacGUIFactory>();
    } else {
        std::cerr << "Unknown operating system." << std::endl;
        return 1;
    }

    std::unique_ptr<Button> button = factory->createButton();
    std::unique_ptr<Checkbox> checkbox = factory->createCheckbox();

    button->render();
    checkbox->render();

    return 0;
}
/*
 Rendering Windows button.
 Rendering Windows checkbox.
 Program ended with exit code: 0
 */
