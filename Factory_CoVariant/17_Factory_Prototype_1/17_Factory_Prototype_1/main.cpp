//
//  main.cpp
//  17_Factory_Prototype_1
//
//  Created by Sathya Babu on 18/02/23.
//
/*
 
 In this example, we have an abstract Shape class and concrete implementations of it for a circle and a rectangle. Each implementation provides its own implementation of the draw() method to draw the corresponding shape. Additionally, each implementation provides a clone() method to create a new instance of the same type of shape.

 We then define an abstract ShapeFactory class that has a single virtual method createShape(). Each concrete factory implementation (PrototypeShapeFactory) takes a prototype Shape object and returns a new instance of the same type of Shape object by calling its clone() method.

 In the main() function, we create prototype Shape objects for both the circle and the rectangle. We then instantiate concrete ShapeFactory objects based on these prototypes and use them to create multiple instances of each shape. We can then call the draw() method on each of these shapes to draw them to the screen.





 
 
 Drawing a circle.
 Drawing a circle.
 Drawing a rectangle.
 Drawing a rectangle.
 Program ended with exit code: 0
 */
#include <iostream>
#include <memory>

// Abstract product interface
class Shape {
public:
    virtual void draw() = 0;
    virtual std::unique_ptr<Shape> clone() = 0;
    virtual ~Shape() {}
};

// Concrete product implementation for a circle
class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a circle." << std::endl;
    }

    std::unique_ptr<Shape> clone() override {
        return std::make_unique<Circle>(*this);
    }
};

// Concrete product implementation for a rectangle
class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a rectangle." << std::endl;
    }

    std::unique_ptr<Shape> clone() override {
        return std::make_unique<Rectangle>(*this);
    }
};

// Abstract factory interface
class ShapeFactory {
public:
    virtual std::unique_ptr<Shape> createShape() = 0;
    virtual ~ShapeFactory() {}
};

// Concrete factory implementation
class PrototypeShapeFactory : public ShapeFactory {
public:
    PrototypeShapeFactory(std::unique_ptr<Shape> prototype) : prototype_(std::move(prototype)) {}

    std::unique_ptr<Shape> createShape() override {
        return prototype_->clone();
    }

private:
    std::unique_ptr<Shape> prototype_;
};

int main() {
    std::unique_ptr<Shape> circle_prototype = std::make_unique<Circle>();
    std::unique_ptr<Shape> rectangle_prototype = std::make_unique<Rectangle>();

    std::unique_ptr<ShapeFactory> circle_factory = std::make_unique<PrototypeShapeFactory>(std::move(circle_prototype));
    std::unique_ptr<ShapeFactory> rectangle_factory = std::make_unique<PrototypeShapeFactory>(std::move(rectangle_prototype));

    std::unique_ptr<Shape> circle1 = circle_factory->createShape();
    std::unique_ptr<Shape> circle2 = circle_factory->createShape();
    std::unique_ptr<Shape> rectangle1 = rectangle_factory->createShape();
    std::unique_ptr<Shape> rectangle2 = rectangle_factory->createShape();

    circle1->draw();
    circle2->draw();
    rectangle1->draw();
    rectangle2->draw();

    return 0;
}
/*
 Drawing a circle.
 Drawing a circle.
 Drawing a rectangle.
 Drawing a rectangle.
 Program ended with exit code: 0
 */
