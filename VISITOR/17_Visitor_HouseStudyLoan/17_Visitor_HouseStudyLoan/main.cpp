//
//  main.cpp
//  17_Visitor_HouseStudyLoan
//
//  Created by Sathya Babu on 26/04/23.
//
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class House;
class StudentLoan;

class Visitor {
public:
    virtual double visit( House& )     = 0;
    virtual double visit( StudentLoan&) = 0;
};


class Visitable {
public:
    virtual double accept(Visitor& v) = 0;
};


class House : public Visitable {
public:
    House(double v) : value(v) {}

    double getValue() {
        return value;
    }

    double accept(Visitor& v) override {
        return v.visit(*this);
    }

private:
    double value;
};

class StudentLoan : public Visitable {
public:
    StudentLoan(double a) : amount(a) {}

    double getAmount() {
        return amount;
    }

    double accept(Visitor& v) override {
        return v.visit(*this);
    }

private:
    double amount;
};
class TaxVisitor : public Visitor {
public:
    virtual double visit( House& house) override {
        cout<<" Housing Loan -> ";
        return house.getValue() * 0.1; // 10% tax on the value of the house
    }

    virtual double visit( StudentLoan& loan) override {
        cout<<" Study Loan -> ";
        return loan.getAmount() * 0.05; // 5% tax on the loan amount
    }
};


int main() {
    std::vector< Visitable* > visitable;
    visitable.push_back(new House(500000.0));
    visitable.push_back(new StudentLoan(10000.0));

    TaxVisitor taxVisitor;

    double totalTax = 0.0;
    for (auto asset : visitable) {
        totalTax += asset->accept(taxVisitor);
    }

    std::cout << "Total tax: Rs. " << totalTax << std::endl << std::endl;
    
    //////        // Phase II   Variant visit
    ///
    std::vector<std::variant< House,StudentLoan>> loans = {
        House(500000),
        StudentLoan(10000)
        
    };
    
    TaxVisitor taxVisitor2;
    for (auto& loan : loans) {
        double tax = std::visit([&taxVisitor2](auto&& s) { return s.accept(taxVisitor2); }, loan);
        std::cout << "Variant visit TaxVisitor TAX : " << tax << std::endl;
    }
    
  
    

    return 0;
}

/*
 THousing Loan ->  Study Loan -> Total tax: Rs. 50500
 
 Housing Loan -> Variant visit TaxVisitor TAX : 50000
 Study Loan -> Variant visit TaxVisitor TAX : 500
Program ended with exit code: 0
 */

// Total tax: Rs. 50500
