//
//  main.cpp
//  17_Observer_DivAdd
//
//  Created by Sathya Babu on 05/05/22.
//

#include <iostream>
#include <vector>
using namespace std;

class Observer ;

class Subject {
    // 1. "independent" functionality
    vector < Observer * > views; // 3. Coupled only to "interface"
    int value;
    
  public:
    
    void attach(Observer *obs) {
        views.push_back(obs);
    }
     void detach(Observer *obs)
    {
        views.erase(std::remove(views.begin(),views.end(),obs),views.end());

    }
    
    void setVal(int val) {
        value = val;
        notify();
    }
    
    int getVal() {
        return value;
    }
    
    void notify();
};

class Observer {
    
    // 2. "dependent" functionality
    Subject *model;
    int     denom;
    
  public:
    
    Observer(Subject *mod, int div) {
        model = mod;
        denom = div;
        
        // 4. Observers register themselves with the Subject
        model->attach(this);
    }
    virtual void update() = 0;
    
  protected:
    
    Subject *getSubject() {
        return model;
    }
    
    int getDivisor() {
        return denom;
    }
};

void Subject::notify() {
    
  // 5. Publisher broadcasts
  for (int i = 0; i < views.size(); i++)
    views[i]->update();
}

class DivObserver: public Observer {
    
  public:
    
    DivObserver(Subject *mod, int div): Observer(mod, div){}
    
    void update() {
        // 6. "Pull" information of interest
        int v = getSubject()->getVal(), d = getDivisor();
        cout << v << " / " << d << " is " << v / d << '\n';
    }
};

class MulObserver: public Observer {
  public:
    MulObserver(Subject *mod, int div): Observer(mod, div){}
    void update() {
        int v = getSubject()->getVal(), d = getDivisor();
        cout << v << " * " << d << " is " << v * d << '\n';
    }
};

int main() {
  Subject subj;
  DivObserver divObs1(&subj, 4); // 7. Client configures the number and
  DivObserver divObs2(&subj, 3); //    type of Observers
  MulObserver modObs3(&subj, 3);
    
    // When setVal changes notify is called
  subj.setVal(14);
}
/*
 
 14 / 4 is 3
 14 / 3 is 4
 14 * 3 is 42
 Program ended with exit code: 0
 
 */
