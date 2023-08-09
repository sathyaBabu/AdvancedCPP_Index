//
//  main.cpp
//  2_20_Observer
//
//  Created by Sathya Babu on 02/08/23.
//

#include <iostream>
#include<vector>

using namespace std ;

class Observer ;

class Subject {
    public :
    
    void attach( Observer* obs ){
        views.emplace_back( obs );
    }
    void detach( Observer* obs){
        views.erase( std::remove( views.begin(),views.end(), obs), views.end());
    }
    
    void setVal( int val ) {
        value = val ;
        notify();
    }
    
    int getVal() { return value ; }
    
    void notify();
    
    private :
    
    std::vector< class Observer* > views ;
    int value ;
    
};

class Observer {
    private :
    
    Subject* model ;
    int denom ;
    
    public :
    Observer( Subject* mod , int div){
        
        model = mod ;
        denom = div ;
        
        model->attach( this );
        
    }
    
    
    
    virtual void update() = 0 ;
    
    
    protected :
    
    Subject* getSubject() {
        return  model ;
    }
    int getDivisor() {
        return denom ;;
    }
    
};

void Subject::notify(){
    
    for( int i = 0 ; i < views.size(); i++){
        views[ i ] -> update();
    }
}

class DivObserver : public Observer {
    public :
    DivObserver( Subject* mod , int div ) : Observer( mod,div) {}
    
    void update(){
        
        int v = getSubject()->getVal() , d = getDivisor() ;
        cout << v << " / " << d << " is " << v / d << endl ;
    }
     
};

class MulObserver : public Observer {
    public :
    MulObserver( Subject* mod , int div ) : Observer( mod,div) {}
    
    void update(){
        
        int v = getSubject()->getVal() , d = getDivisor() ;
        cout << v << " * " << d << " is " << v * d << endl ;
    }
     
};



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Observer DP !\n";
    
    Subject subj ;
    DivObserver divObs1( &subj, 4 );
    DivObserver divObs2( &subj, 3 );
    MulObserver mulObs1( &subj, 3 );
    
    
    subj.setVal( 44 ) ;
    
    
    
    return 0;
}
/*
 
 Observer DP !
 44 / 4 is 11
 44 / 3 is 14
 44 * 3 is 132
 */
