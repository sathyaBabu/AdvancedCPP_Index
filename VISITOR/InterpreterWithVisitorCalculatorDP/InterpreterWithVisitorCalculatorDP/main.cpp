//
//  main.cpp
//  InterpreterWithVisitorCalculatorDP
//
//  Created by Sathya Babu on 01/08/23.
//
#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <vector>

// Forward declaration
class Expression;
class Number;
class Addition;
class Subtraction;
class Multiplication;
class Division;

// Visitor interface
class Visitor {
public:
    virtual void visit(Number& number) = 0;
    virtual void visit(Addition& addition) = 0;
    virtual void visit(Subtraction& subtraction) = 0;
    virtual void visit(Multiplication& multiplication) = 0;
    virtual void visit(Division& division) = 0;
};

// Expression base class
class Expression {
public:
    virtual ~Expression() = default;
    virtual void accept(Visitor& visitor) = 0;
};

// Concrete expression classes
class Number : public Expression {
public:
    Number(int value) : value(value) {}

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

    int getValue() const {
        return value;
    }

private:
    int value;
};

class Addition : public Expression {
public:
    Addition(Expression* left, Expression* right) : left(left), right(right) {}

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

    Expression* getLeft() const {
        return left;
    }

    Expression* getRight() const {
        return right;
    }

private:
    Expression* left;
    Expression* right;
};

class Subtraction : public Expression {
public:
    Subtraction(Expression* left, Expression* right) : left(left), right(right) {}

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

    Expression* getLeft() const {
        return left;
    }

    Expression* getRight() const {
        return right;
    }

private:
    Expression* left;
    Expression* right;
};

class Multiplication : public Expression {
public:
    Multiplication(Expression* left, Expression* right) : left(left), right(right) {}

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

    Expression* getLeft() const {
        return left;
    }

    Expression* getRight() const {
        return right;
    }

private:
    Expression* left;
    Expression* right;
};

class Division : public Expression {
public:
    Division(Expression* left, Expression* right) : left(left), right(right) {}

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

    Expression* getLeft() const {
        return left;
    }

    Expression* getRight() const {
        return right;
    }

private:
    Expression* left;
    Expression* right;
};

// Concrete visitor to evaluate expressions
class Evaluator : public Visitor {
public:
    void visit(Number& number) override {
        operandStack.push(number.getValue());
    }

    void visit(Addition& addition) override {
        addition.getLeft()->accept(*this);
        addition.getRight()->accept(*this);
        int right = operandStack.top();
        operandStack.pop();
        int left = operandStack.top();
        operandStack.pop();
        operandStack.push(left + right);
    }

    void visit(Subtraction& subtraction) override {
        subtraction.getLeft()->accept(*this);
        subtraction.getRight()->accept(*this);
        int right = operandStack.top();
        operandStack.pop();
        int left = operandStack.top();
        operandStack.pop();
        operandStack.push(left - right);
    }

    void visit(Multiplication& multiplication) override {
        multiplication.getLeft()->accept(*this);
        multiplication.getRight()->accept(*this);
        int right = operandStack.top();
        operandStack.pop();
        int left = operandStack.top();
        operandStack.pop();
        operandStack.push(left * right);
    }

    void visit(Division& division) override {
        division.getLeft()->accept(*this);
        division.getRight()->accept(*this);
        int right = operandStack.top();
        operandStack.pop();
        int left = operandStack.top();
        operandStack.pop();
        operandStack.push(left / right);
    }

    int getResult() const {
        return operandStack.top();
    }

private:
    std::stack<int> operandStack;
};

// Helper function to parse and evaluate the expression
int evaluateExpression(const std::string& expr) {
    std::istringstream iss(expr);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    std::stack<Expression*> expressionStack;
    for (const auto& token : tokens) {
        if (token == "+") {
            Expression* right = expressionStack.top();
            expressionStack.pop();
            Expression* left = expressionStack.top();
            expressionStack.pop();
            expressionStack.push(new Addition(left, right));
        } else if (token == "-") {
            Expression* right = expressionStack.top();
            expressionStack.pop();
            Expression* left = expressionStack.top();
            expressionStack.pop();
            expressionStack.push(new Subtraction(left, right));
        } else if (token == "*") {
            Expression* right = expressionStack.top();
            expressionStack.pop();
            Expression* left = expressionStack.top();
            expressionStack.pop();
            expressionStack.push(new Multiplication(left, right));
        } else if (token == "/") {
            Expression* right = expressionStack.top();
            expressionStack.pop();
            Expression* left = expressionStack.top();
            expressionStack.pop();
            expressionStack.push(new Division(left, right));
        } else {
            int value = std::stoi(token);
            expressionStack.push(new Number(value));
        }
    }

    Evaluator evaluator;
    expressionStack.top()->accept(evaluator);
    return evaluator.getResult();
}

int main() {
    std::string expr = "3 5 + 4 *"; // Equivalent to (3 + 5) * 4
    int result = evaluateExpression(expr);
    std::cout << "Result: " << result << std::endl; // Output: 32
    return 0;
}
// Result: 32
