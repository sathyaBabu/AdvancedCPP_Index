//
//  main.cpp
//  17_Intrepreter_Calculator_PostFix
//
//  Created by Sathya Babu on 02/05/23.
//
#include <iostream>
#include <stack>
#include <string>
#include <sstream>

class Expression {
public:
    virtual int interpret() = 0;
};

class Number : public Expression {
public:
    Number(int value) : value_(value) {}
    int interpret() override {
        return value_;
    }
private:
    int value_;
};

class Add : public Expression {
public:
    Add(Expression* left, Expression* right)
        : left_(left), right_(right) {}
    int interpret() override {
        return left_->interpret() + right_->interpret();
    }
private:
    Expression* left_;
    Expression* right_;
};

class Subtract : public Expression {
public:
    Subtract(Expression* left, Expression* right)
        : left_(left), right_(right) {}
    int interpret() override {
        return left_->interpret() - right_->interpret();
    }
private:
    Expression* left_;
    Expression* right_;
};

class Multiply : public Expression {
public:
    Multiply(Expression* left, Expression* right)
        : left_(left), right_(right) {}
    int interpret() override {
        return left_->interpret() * right_->interpret();
    }
private:
    Expression* left_;
    Expression* right_;
};

class Divide : public Expression {
public:
    Divide(Expression* left, Expression* right)
        : left_(left), right_(right) {}
    int interpret() override {
        return left_->interpret() / right_->interpret();
    }
private:
    Expression* left_;
    Expression* right_;
};

Expression*  add(Expression* left, Expression* right){  return new Add(left, right); }
Expression*  mul(Expression* left, Expression* right){  return new Multiply(left, right); }

Expression*  divid(Expression* left, Expression* right){  return new Divide(left, right); }

Expression*  sub(Expression* left, Expression* right){  return new Subtract(left, right); }

class Calculator {
public:
    Calculator() {
        //   un ordered map
        operators_["+"] = &add;
        
       operators_["*"] = &mul;
        operators_["-"] = &sub;
        operators_["/"] = &divid;
    

    
    /*
     operators_["-"] = [](Expression* left, Expression* right) {
         return new Subtract(left, right);
     };
     operators_["*"] = [](Expression* left, Expression* right) {
         return new Multiply(left, right);
     };
     operators_["/"] = [](Expression* left, Expression* right) {
         return new Divide(left, right);
     };
     */
    }
    Expression* parse(const std::string& expression) {
        std::stack<Expression*> stack;
        
        std::basic_stringstream<char> ss(expression);
        std::string token;
      
        
        while (getline(ss, token, ' ')) {  // '  ' delimiter
        std::cout  << " token " << token << " count  "<< operators_.count(token) <<std::endl;
            if (operators_.count(token)) { // if count 0 goto else push it in stack LIFO
                // returns 0 for number( 2 3 4 ) 1 for ( * + ) operator
                std::cout << " count  "<< operators_.count(token) <<std::endl;
                Expression* right = stack.top();
                
                std::cout  << " right " << right->interpret() << std::endl ;
                stack.pop();
                Expression* left = stack.top();
               std::cout  << " Left" << left->interpret() << std::endl ;
                stack.pop();
                //  stack.push( Add(left, right));
                std::cout  << " token___ " << token << std::endl ;
                stack.push(operators_[token](left, right));  // pushing mul *
            } else {
                std::cout << " count at  else "<< operators_.count(token) <<std::endl;
                stack.push(new Number(std::stoi(token))); //  function to convert the string to an integer,  --> 4 3 2
            }
        }
        return stack.top();  //returning [ * ]( 4 , 3 )  : Multiply( 4 , 3 );
        // this will do the job of multiplication
    }
private:
  
    std::unordered_map<std::string, std::function< Expression* (Expression*, Expression*) > > operators_;
};

int main() {
    Calculator calculator;
    Expression* expression = calculator.parse("2 3 4 * +");  // ("2 3 4 * -")  = 10
    std::cout << expression->interpret() << std::endl; // Output: 14
    delete expression;
    
   
    return 0;
}
// Out Put 14
/*
 token 2 count  0
 count at  else 0
 token 3 count  0
 count at  else 0
 token 4 count  0
 count at  else 0
 token * count  1
 count  1
 right 4
 Left3
 token___ *
 token + count  1
 count  1
 right 12
 Left2
 token___ +
14
Program ended with exit code: 0
 */
