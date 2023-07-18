//
//  main.cpp
//  S12_Factory
//
//  Created by Sathya Babu on 12/05/23.
//

#include <iostream>
using namespace std;

enum   OS{ mac, windows, linux };
//          0     1         2

enum day{monday= 10 , tuesday, wed, thu, fri, sat,sun };

// Declare the interface - abstraction

class Button {
    public :
    virtual void OnClickButton() = 0 ;
};

class MACButton :public Button{
    
    public :
    void OnClickButton() override {
        std::cout << "MAC button clicked...!\n";
    }
};

class WindowButton :public Button{
    
    public :
    void OnClickButton() override {
        std::cout << "Windows button clicked...!\n";
    }
};

// create a query interface..

class GUIFactory{
    public :
    
    virtual Button* askForTheButton( OS os ) = 0 ;
    
};
// factory -> is the provider of the various objects which is queried for


class Factory : public GUIFactory
{
    public :
    Button* askForTheButton( OS os ){
        
        if( os == windows ){
            return  new WindowButton;   // from a DLL  // server // lib..
        }
        if( os ==  mac ){
            return  new MACButton;
        }
        
        return nullptr ;   // use nullptr instead..
        
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Factory !\n";
    
    GUIFactory* guiFactory ;
    Button*     btn ;
    
    guiFactory = new Factory;
    btn = guiFactory->askForTheButton( mac);
    btn->OnClickButton();
    
    btn = guiFactory->askForTheButton( windows );
    btn->OnClickButton();
    
    
    
    return 0;
}
/*
 Factory !
 MAC button clicked...!
 Windows button clicked...!
 Program ended with exit code: 0
 */
