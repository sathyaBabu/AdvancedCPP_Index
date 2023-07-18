//
//  main.cpp
//  17_Intrpreter_In _VariadicExpressions
//
//  Created by Sathya Babu on 17/06/23.
//
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

// Base Expression class
class Expression {
public:
    virtual int interpret() const = 0;
   // virtual ~Expression() {}
};

// NumberExpression class
class NumberExpression : public Expression {
private:
    int number;

public:
    explicit NumberExpression(int num) : number(num) {}

    int interpret() const override {
        return number;
    }
};

// AddExpression class
class AddExpression : public Expression {
private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:
    AddExpression(std::unique_ptr<Expression> leftExp, std::unique_ptr<Expression> rightExp)
        : left(std::move(leftExp)), right(std::move(rightExp)) {}

    int interpret() const override {
        return left->interpret() + right->interpret();
    }
};

// MultiplyExpression class
class MultiplyExpression : public Expression {
private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:
    MultiplyExpression(std::unique_ptr<Expression> leftExp, std::unique_ptr<Expression> rightExp)
        : left(std::move(leftExp)), right(std::move(rightExp)) {}

    int interpret() const override {
        return left->interpret() * right->interpret();
    }
};

// Calculator class
class Calculator {
public:
    std::unique_ptr<Expression> parse(const std::string& input) {
        std::istringstream iss(input);
        std::vector<std::unique_ptr<Expression>> expressions;

        std::string token;
        while (iss >> token) {
            if (token == "+") {
                auto right = std::move(expressions.back());
                expressions.pop_back();
                auto left = std::move(expressions.back());
                expressions.pop_back();
                expressions.emplace_back(std::make_unique<AddExpression>(std::move(left), std::move(right)));
            } else if (token == "*") {
                auto right = std::move(expressions.back());
                expressions.pop_back();
                auto left = std::move(expressions.back());
                expressions.pop_back();
                expressions.emplace_back(std::make_unique<MultiplyExpression>(std::move(left), std::move(right)));
            } else {
                //*************
                try {
                                int number = std::stoi(token);
                                expressions.emplace_back(std::make_unique<NumberExpression>(number));
                            } catch (const std::invalid_argument& e) {
                                std::cerr << "Invalid input token! / - etc..: " << token << std::endl;
                            }
                //*************
            }
        }

        return std::move(expressions.back());
    }
};

/*
// Phase II
template<typename... Args>
void pickString(Args&&... args) {
    
    ((std::cout << "Picked string: " << std::forward<Args>(args) << std::endl), ...);
}

/// under main

  pickString("Hi" ,"there", "how", "are", "you."); // Args &&args...

*/

// Helper function to evaluate expressions
template <typename... Args>
int evaluateExpressions( Calculator& calculator, const std::string& input, Args&&... args) {
    std::cout <<"... " << input  << " ... " << std::endl; ;
    std::vector<std::string> expressions{ std::forward<Args>(args)... }; // refer Phase II
    int result = 0;
    int argsCount = 0 ;

    for ( auto& expr : expressions) {
        argsCount++;
        std::cout << argsCount << " args... " << expr << " " ;
        
        std::unique_ptr<Expression> expression = calculator.parse(expr);
        std::cout <<" Result :  " <<expression->interpret() << " "  << std::endl;
        
        result += expression->interpret();
    }

    return result;
}

int main() {
    Calculator calculator;
    // remember we just have * + as tokens..
    int result = evaluateExpressions(calculator, "Working on Polished Postfix notationa",
                                                    "2 3 4 * +", "5 6 +", "8 2 *");
       //                                            (2 + ( 3 * 4 ) ( 5 + 6 ) (8 * 2 )
    std::cout << " Sum  ->  " << result << std::endl;

    return 0;
}
// 27
/*
 ... Working on Polished Postfix notationa ...
 1 args... 2 3 4 * +  Result :  14
 2 args... 5 6 +  Result :  11
 3 args... 8 2 *  Result :  16
  Sum  ->  41
 Program ended with exit code: 0
 
 */
