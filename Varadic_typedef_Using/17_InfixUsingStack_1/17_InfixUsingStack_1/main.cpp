//
//  main.cpp
//  17_InfixUsingStack_1
//
//  Created by Sathya Babu on 22/04/23.
//
/*
 
 In this example, we evaluate an infix expression using a stack. The evaluate_infix function takes a string containing an infix expression as input and returns the result of the expression as an integer.

 We use two stacks: operand_stack to store the operands and operator_stack to store the operators. We scan the input expression from left to right and perform the following actions depending on the type of the character:

 If the character is a digit, we parse the operand and push it onto the operand_stack.
 If the character is a left parenthesis, we push it onto the operator_stack.
 If the character is a right parenthesis, we pop operators
 */
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }
}

int evaluate(int operand1, int operand2, char op) {
    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        default:
            return 0;
    }
}

int evaluate_infix(string expression) {
    stack<int> operand_stack;
    stack<char> operator_stack;

    for (int i = 0; i < expression.length(); i++) {
        char ch = expression[i];
        if (isdigit(ch)) {
            int operand = ch - '0';
            while (i + 1 < expression.length() && isdigit(expression[i+1])) {
                operand = operand * 10 + (expression[i+1] - '0');
                i++;
            }
            operand_stack.push(operand);
        } else if (ch == '(') {
            operator_stack.push(ch);
        } else if (ch == ')') {
            while (!operator_stack.empty() && operator_stack.top() != '(') {
                char op = operator_stack.top();
                operator_stack.pop();
                int operand2 = operand_stack.top();
                operand_stack.pop();
                int operand1 = operand_stack.top();
                operand_stack.pop();
                operand_stack.push(evaluate(operand1, operand2, op));
            }
            operator_stack.pop(); // Pop the left parenthesis
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!operator_stack.empty() && operator_stack.top() != '(' &&
                   precedence(ch) <= precedence(operator_stack.top())) {
                char op = operator_stack.top();
                operator_stack.pop();
                int operand2 = operand_stack.top();
                operand_stack.pop();
                int operand1 = operand_stack.top();
                operand_stack.pop();
                operand_stack.push(evaluate(operand1, operand2, op));
            }
            operator_stack.push(ch);
        }
    }

    while (!operator_stack.empty()) {
        char op = operator_stack.top();
        operator_stack.pop();
        int operand2 = operand_stack.top();
        operand_stack.pop();
        int operand1 = operand_stack.top();
        operand_stack.pop();
        operand_stack.push(evaluate(operand1, operand2, op));
    }

    return operand_stack.top();
}

int main() {
    string expression = "2*(3+4)-5/(6-1)";
    int result = evaluate_infix(expression);
    cout << expression << " = " << result << endl;
    return 0;
}
