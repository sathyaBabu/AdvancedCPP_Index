//
//  main.cpp
//  17_Word_SB_View_1
//
//  Created by Sathya Babu on 08/05/23.
//
#include <iostream>
using namespace std;

// Interface for the view
class IWordView {
public:
    virtual void updateView(int newPosition) = 0;
};

// Interface for the scroll bar
class IScrollBarView {
public:
    virtual void updateScrollBar(int newPosition) = 0;
};

// Implementation of the view
class View : public IWordView {
public:
    void updateView(int newPosition) override {
        std::cout << "\t \t View updated to position: " << newPosition << std::endl;
    }
};

// Implementation of the scroll bar
class ScrollBar : public IScrollBarView {
public:
    void updateScrollBar(int newPosition) override {
        std::cout << "\t \t SB updated to position: " << newPosition << std::endl;
    }
};

// Word application class that manages the view and scroll bar
class WordApp {
    
private:
    IWordView* view_;
    IScrollBarView* scrollBar_;
    
public:
    WordApp(IWordView* view, IScrollBarView* scrollBar) : view_(view), scrollBar_(scrollBar) {}

    void setViewPosition( int newPosition ) {
        view_->updateView( newPosition );
        scrollBar_->updateScrollBar( newPosition );
    }

    void setScrollBarPosition( int newPosition ) {
        scrollBar_->updateScrollBar( newPosition );
        view_->updateView( newPosition );
    }
};

int main() {
    View view;
    ScrollBar scrollBar;

    WordApp wordApp(&view, &scrollBar);

    
    // When scroll bar changes, update view
    for(int drag = 0 ; drag <= 3 ; drag++){
        std::cout << "SB is dragged  to :  " <<  drag << std::endl;
        wordApp.setScrollBarPosition( drag );  // 50
    }
          

    // When view changes, update scroll bar
    // view changes as the user types in
    
    cout << endl << endl ;
    
   
    
    for(int addingLine = 0 ; addingLine <= 3 ; addingLine++){
        std::cout << "Adding line  :  " <<  addingLine << std::endl;
        wordApp.setViewPosition( addingLine );   // 100
    }
   

    return 0;
}
/*
 SB is dragged  to :  0
           SB updated to position: 0
           View updated to position: 0
 SB is dragged  to :  1
           SB updated to position: 1
           View updated to position: 1
 SB is dragged  to :  2
           SB updated to position: 2
           View updated to position: 2
 SB is dragged  to :  3
           SB updated to position: 3
           View updated to position: 3


 Adding line  :  0
           View updated to position: 0
           SB updated to position: 0
 Adding line  :  1
           View updated to position: 1
           SB updated to position: 1
 Adding line  :  2
           View updated to position: 2
           SB updated to position: 2
 Adding line  :  3
           View updated to position: 3
           SB updated to position: 3
 Program ended with exit code: 0
 */
