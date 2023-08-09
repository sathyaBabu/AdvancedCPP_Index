//
//  main.cpp
//  6_1_Intrepreter_Calc
//
//  Created by Sathya Babu on 01/08/23.
// Code is not complete : we need to bring in unique_ptr , std::move , std::forward..

 /*
  
  infix notations
  
  ( 5 + 3 ) * ( 8 - 2 ) = 48
  5 3 + 8 2 - *         = 48
  
  
  
  
                                    2 l
             3 l                    8 r               6 l
             5 r                    8                 8 r               48
           ------                 ------            ------            ------
           values                    +                 -                 *
  
  
            Terminal             (  NON Terminal  + * / -  )
            Number               Add/Mul/Div/Sub
  
  */
 
#include <iostream>
#include <stack>
#include <sstream>

using namespace std;


class Expression
{
    public :
    virtual int interpret() = 0 ;
    
    
};

class Number : public Expression {
    
    public :
    Number( int value ) : value_( value) {}
        
        int  interpret()  override {
            return value_;
        }
    
    private :
    int value_ ;
    
};

class Add : public  Expression {
    public :
    
    Add( Expression* left , Expression* right ) : left_(left) , right_(right){}
    
    int interpret() override
    {
        return  left_->interpret() + right_->interpret();
    }
   
    
    private :
    Expression* left_;
    Expression* right_ ;
};



class Subtract : public Expression {
    public :
    
    Subtract ( Expression* left , Expression* right ) : left_(left) , right_(right){}
    
    int interpret() override
    {
        return  left_->interpret() + right_->interpret();
    }
   
    
    private :
    Expression* left_;
    Expression* right_ ;
};


class Multiply: public Expression {
    public :
    
    Multiply( Expression* left , Expression* right ) : left_(left) , right_(right){}
    
    int interpret() override
    {
        return  left_->interpret() + right_->interpret();
    }
   
    
    private :
    Expression* left_;
    Expression* right_ ;
};


class Divide : public  Expression {
    public :
    
    Divide( Expression* left , Expression* right ) : left_(left) , right_(right){}
    
    int interpret() override
    {
        return  left_->interpret() + right_->interpret();
    }
   
    
    private :
    Expression* left_;
    Expression* right_ ;
};


Expression* add( Expression* left ,Expression* right ) { return  new Add( left,right);  }

Expression* mul( Expression* left ,Expression* right ) { return  new Multiply( left,right);  }


Expression* sub( Expression* left ,Expression* right ) { return  new Subtract( left,right);  }


Expression* divid( Expression* left ,Expression* right ) { return  new Divide( left,right);  }


class Calculator
{
    public :
    Calculator() {
        
        operators_["+"] = &add ;
        operators_["*"] = &mul ;
        operators_["-"] = &sub ;
        operators_["/"] = &divid ;
        
    }
    
    Expression* parse( const std::string& expression){
        
        std::stack< Expression* > stack ;
        std::basic_stringstream< char > ss ( expression);
        std::string token ;
        
        while (getline(ss, token, ' ')) {  // '  ' delimiter
            if( operators_.count( token)) {  // 0
            
            Expression* right = stack.top();
            stack.pop();
            
            Expression* left= stack.top();
            stack.pop();
            
            stack.push( operators_[ token ]( left,right )); // push mul *
            
        }else {
            stack.push( new Number( std::stoi( token)) );
        }
    }
    return stack.top();
}
    

    
    
    private :
    
    std::unordered_map< std::string , std::function< Expression* ( Expression*, Expression*) > > operators_ ;
    
};

//  interpreter   <--- interface -->  varadic /fold component

// concrete class...

// Varadic / fold  calls the interpreter..
//
template<typename ... Args>
int evaluateExpression( Calculator& calculator , const std::string& input , Args&&... args)
{
    cout << " Input String ... " << input << endl ;
    
    // perfect forwarding...
   // std::vector< std::string> expressions{ args... };
    std::vector< std::string> expressions{ std::forward<Args>( args)... };
    int result = 0 ;
    int argsCount  = 0 ;
    
    for( auto& expr : expressions){
        argsCount++;
        cout << " Arg count " << argsCount << endl ;
        
        auto expression = calculator.parse( expr );
        cout << " Result : " << expression->interpret() << " " << endl ;
        
        result += expression->interpret();
    }
    return result ;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Calculator calculator ;
    
    int result = evaluateExpression( calculator , "Using POLISHED notations.","2 3 4 * +" );
    cout << " Result " << result << endl ;
    
    
//    Expression* expression = calculator.parse( "2 3 4 * +") ; //  = 9
//    cout << expression->interpret() << endl ;
//
//    delete expression ;
    return 0;
}
