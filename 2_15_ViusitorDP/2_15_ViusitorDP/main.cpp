//
//  main.cpp
//  2_15_ViusitorDP
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
#include<vector>
using namespace std ;


class House ;
class StudentLoan ;

// Auditor's interface

class Visitor {
    public:
    
    virtual double visit( House& ) = 0 ;
    virtual double visit( StudentLoan& ) = 0 ;
    
};

// You

class Visitable
{
public:
    virtual double accept(Visitor& ) = 0 ;
    
};

class House : public Visitable
{
    
public:
    House( double v ) : value( v ){}
    
    double getValue() { return value ; }
    
    // we are letting the auditor to visit us Visitor
    double accept( Visitor& v ) override {
        
        // v taxVisitor.visit( *this )
        return  v.visit( *this ); // we are calling back the auditor with our address.
    }
    
    
    private :
    double value ;
};

class StudentLoan: public Visitable
{
    
public:
    StudentLoan( double v ) : value( v ){}
    
    double getValue() { return value ; }
    
    double accept( Visitor& v ) override {
        
        return  v.visit( *this ); // we are calling back the auditor with our address.
    }
    
    
    private :
    double value ;
};

// Auditor..
class TAxVisitor : public Visitor{
    
    public :
    
    virtual double visit( House& house ) override {
        cout << " Working upon Housing loan --> ";
        return  house.getValue() * 0.8 ;
    }
    virtual double visit( StudentLoan&  loan  ) override {
        cout << " Working upon Study  loan --> ";
        return  loan.getValue() * 0.02 ;
    }
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Visitor !\n";
    
    std::vector< Visitable* > visitable ;
    
    visitable.emplace_back( new House( 500000.0 ));
    visitable.emplace_back( new StudentLoan( 10000.0 ));
    
    
    TAxVisitor taxVisitor ;
    
    
    double totalTax = 0 ;
    for( auto asset : visitable)
    {
        //         house->accept  , StudentLoan->accept
        totalTax += asset->accept( taxVisitor );
        
    }
    
    cout << "Total payable For house + Study TAX Rs. " << totalTax << endl ;
    
    
    // variant and visit
    
    std::vector< std::variant< House, StudentLoan>> loans {
        House( 500000.0 ), StudentLoan( 10000.0 )
    };
    TAxVisitor taxVisitor2 ;
    
    for( auto& loan : loans){
        double tax = std::visit( [ &taxVisitor2 ]( auto&& s ) {  return  s.accept( taxVisitor2); } , loan );
        
        cout << "Variant visit TaxVisitor TAX : " << tax << endl ;
        
    }
    
    return 0;
}
/*
 
 Visitor !
  Working upon Housing loan -->  Working upon Study  loan --> Total payable For house + Study TAX Rs. 400200
  Working upon Housing loan --> Variant visit TaxVisitor TAX : 400000
  Working upon Study  loan --> Variant visit TaxVisitor TAX : 200
 Program ended with exit code: 0
 */
