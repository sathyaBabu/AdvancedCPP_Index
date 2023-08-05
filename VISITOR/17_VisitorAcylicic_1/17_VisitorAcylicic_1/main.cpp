//
//  main.cpp
//  17_VisitorAcylicic_1
//
//  Created by Sathya Babu on 29/11/21.
//http://www.cplusplus.com/forum/general/136902/
/*
 dynamic_cast
 `dynamic_cast` is useful when you don't know what the dynamic type of the object is. It returns a null pointer if the object referred to doesn't contain the type casted to as a base class (when you cast to a reference, a `bad_cast` exception is thrown in that case).
 if (JumpStm *j = dynamic_cast<JumpStm*>(&stm)) {
   ...
 } else if (ExprStm *e = dynamic_cast<ExprStm*>(&stm)) {
   ...
 }
 */
#include <iostream>
#include <string>

struct A
{
    struct visitor {
        virtual ~visitor() = default ;
        virtual bool accept( A* ) { return false ; }
        
    };
    
    virtual ~A() = default ;
    
    virtual bool accept( visitor& ) = 0 ;
    
    bool accept( visitor&& v ) // rvalue
            { return accept( v ) ; }
};

template < typename BASE > struct base : BASE
{
    struct visitor { virtual ~visitor() = default ;
        virtual bool accept( base* ) = 0 ; };
    
    virtual bool accept( A::visitor& av ) override
    {
        auto dv = dynamic_cast< base::visitor* >( std::addressof(av) ) ;
        return dv ? dv->accept(this) : av.accept(this) ;
    }
};

struct B : base<A> {};
struct C : base<A> {};
struct D : base<B> {};
struct E : base<C> {};
struct F : base<D> {};

template < typename T >
struct counting_visitor : A::visitor
{
    virtual bool accept( A* p ) { return dynamic_cast< T* >(p) ? ++cnt : false ; }
    operator int () const { return cnt ; }
    private: int cnt = 0 ;
};

int main()
{
    A* seq[] { new B, new C, new D, new E, new F, new C, new B, new F, new E, new B } ;

    counting_visitor<B> cvb ;
    counting_visitor<C> cvc ;
    counting_visitor<D> cvd ;
    for( A* p : seq ) { p->accept(cvb) ; p->accept(cvc) ; p->accept(cvd) ; }

    std::cout << "B: " << cvb // 6
              << "\nC: " << cvc // 4
              << "\nD: " << cvd << '\n' ; // 3
}
