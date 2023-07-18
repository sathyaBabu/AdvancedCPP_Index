//
//  main.cpp
//  FactoryAbs
//
//  Created by Sathya Babu on 06/10/21.
//


#include <iostream>

// 1
class Button
{
public:
    virtual void OnClickButton() = 0;
};
 
// 2
class ScrollBar
{
public:
    virtual void OnClickScrollBar() = 0;
};

// 3
class GUIFactory
{
public:
    virtual Button*       createButton () = 0;
    virtual ScrollBar* createScrollBar () = 0;
};
 

// 4
class WinButton : public Button
{
public:
    void OnClickButton(){
        std::cout << " Window Button \n";
       }
};
 
class MacButton : public Button
{
public:
    void OnClickButton(){
        std::cout << " Mac Button \n";
       }
};


// 5
class WinScrollBar : public ScrollBar
{
public:
    void OnClickScrollBar(){
        std::cout << " Window ScrollBar \n";
       }
};
 
/*
   Scroll Bar : Size , Min MAx level
   USer( View )  should set the scroll bar by 12%
   When Sb chnges ( moved mouse dragged it by 50%  )  level 50%
    Sb should report View to change itself to level
 
 
 
 call back on scroll change will work well with two known obj..
 Visitor comes in which can callback unknown object
 
 
 STEP I : call back
 set the relation ship :
 Sb COMPONENT :  container  : call back on scroll change
 
 Third party you have no say in him
 View :          call back on scroll change
 ListBox
 Combow
 EditControll
 
 What kind of Callback interface will you develop????
 
 Observer : ??
 Mediator overrulled!!
 
 STEP II
 What kind of an obj it will be given it as to the user???
 : Singletone - Single Object / factory Protype ?????
 
 ANS : VISITOR
 
 */
//   factory Protype   --> Cloning of the object( Deep copy )
class MacScrollBar : public ScrollBar {
public:

    void OnClickScrollBar(){
        std::cout << " Mac ScrollBar \n";
       }
};


// 6 FACTORY

class WinFactory : public GUIFactory
{
public:
    Button* createButton (){
        return new WinButton;
    }
    ScrollBar* createScrollBar (){
        return new WinScrollBar;
    }
};
 
class MacFactory : public GUIFactory
{
public:
    Button* createButton (){
        return new MacButton;
    }
    ScrollBar* createScrollBar (){
        return new MacScrollBar;
    }
};
 
// Let the user use all the abstraction layer through FactoryProducerOS
// To add delete the sub abstraction layers...
class FactoryProducerOS {
    public :
    
    
};


int main()
{
    GUIFactory* guiFactory;
    Button    *btn;
    ScrollBar *sb;

    guiFactory = new MacFactory;
    btn = guiFactory->createButton();
    btn -> OnClickButton();
    sb = guiFactory->createScrollBar();
    sb -> OnClickScrollBar();

    guiFactory = new WinFactory;   // returns as a prototype..
    btn = guiFactory->createButton();
    btn ->OnClickButton();
    sb = guiFactory->createScrollBar();
    sb ->OnClickScrollBar();
    
    return 0;
}
/*
 Mac Button
 Mac ScrollBar
 Window Button
 Window ScrollBar
Program ended with exit code: 0
 */
