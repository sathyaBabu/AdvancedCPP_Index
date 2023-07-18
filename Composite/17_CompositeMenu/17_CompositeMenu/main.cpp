//
//  main.cpp
//  17_CompositeMenu
//
//  Created by Sathya Babu on 24/06/22.
//
//
//  main.cpp
//  CompositeMenu
//
//  Created by Sathya Babu on 29/01/20.
//  Copyright © 2020 Sathya Babu. All rights reserved.

//
/*
 Design Trade-Offs
 • The Composite Pattern violates one of our design principles
 • The Single Responsibility Principle
 • In particular, the design of Composite is handling two responsibilities, tree related methods and
    component-related methods
 • Menu IS-A Menu AND Menu IS-A Node
 • MenuItem IS-A MenuItem AND MenuItem IS-A Leaf
 • Even worse, both Composite and Leaf inherit methods that they don’t use!
 • BUT, we gain transparency! Our client code can treat nodes and leaves in the
 same way… it doesn’t care which one its pointing at!
 • And sometimes that characteristic is worth violating other principles
 • As with all trade-offs, you have to evaluate the benefits you are
 receiving and decide if they are worth the cost
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Interface
{
    public:
        char* GetName(){return name;}

        virtual void ls()=0;
        
    protected:
        char name[20];    // name is used to store the name of the objects.
        
        static int indent;
          
};

int Interface::indent=0; // indent is initialized to 0.


class Leaf:public Interface
{

    public:

        Leaf(char *n)
        {
            strcpy(name,n);
        }

         void ls()
        {
            for(int i=0;i<indent;i++)
                cout<<' ';
            cout<<name<<endl;
        }
};// End of Leaf
/*
 Design Principles
 • Producing your own iterator for a composite is straightforward
 • Add a createIterator() to Composite( node : combo )
 • Have Leaf return a NullIterator
 • a NullIterator’s hasNext() method always returns false
 • Implement the traversal semantics that you want for your Composite’s
 iterator
 • The code will be different depending on whether you want an in-order,
 pre-order, or post-order traversal of the tree
 
 Reffer Algorithm :
 https://en.wikipedia.org/wiki/Tree_traversal#:~:text=In%2Dorder%20traversal%20is%20very,free%20an%20entire%20binary%20tree.
 
 In-order traversal is very commonly used on binary search trees because it returns values from the underlying set in order, according to the comparator that set up the binary search tree.
 Post-order traversal while deleting or freeing nodes and values can delete or free an entire binary tree.
 Pre-order traversal while duplicating nodes and values can make a complete duplicate of a binary tree. It can also be used to make a prefix expression (Polish notation) from expression trees: traverse the expression tree pre-orderly.
 
 • Iterator: separate the management of a collection from the traversal of a
 collection
 
 • Composite: allow individual objects and groups of objects to be treated
 uniformly. Note: Caching
 • if the purpose of a shared operation is to calculate some value based on
 information stored in the node’s children
 • then a composite pattern can add a field to each node that ensures that
 the value is only calculated once.
 • the first time the operation is called, we traverse the children, compute the
 value, and store it in the root
 • thereafter, we return the cached value.
 • this technique requires monitoring changes to the tree to clear out cached
 values that are stale.
 
 • Iterator can be used within the context of the Composite Pattern for In-Order Post-Order and
    Pre-Order traversal
 */
class Composite:public Interface
{
    public:
    
        Composite(char *n)
        {
            strcpy(name,n);
        }

         void ls()
        {
            for(int i=0;i<indent;i++)
                cout<<' ';
//            cout<<files.size()<<" Composite found \n "<<name<<":"<<endl; // ':' is used to distinguish between the
            
            cout<<name<<":"<<endl; // ':' is used to
                           // composite and leaf object.
            indent+=5;
            
           
            for(int i=0;i<files.size();i++){
            //cout<<name<<"\n IN side Composite size :"<<files.size()<<"\n"<<endl;
                // new InOrdeer_ConcreteAgr( this )
                files[i]->ls(); // If the child object is a composite one then
                // FIFO change this to fifo
                        // this function will be invoked again.If it is
                        // a leaf one then it will call the ls() of
                        // Leaf class.
            }
            indent-=5;
        }
        
        void Display()
        {
            cout<<name<<"xxxx:"<<endl;
            for(int i=0;i<files.size();i++)
            {
                for(int j=0;j<3;j++)
                     cout<<' ';
                cout<<files[i]->GetName()<<endl; // calls getname() to display
                                        // the name .
            }
        }
    protected:
        vector<Interface*> files; // This is an vector of pointers to Interface objects.
                      // This vector holds the address of the Composite as well
                      //  as Leaf objects.
        
}; // End of Composite.

// Concreete class...
class Menu:public Composite
{
    public:
        Menu(char *s):Composite(s){}

        void Add(Interface* f)
                {
                    
                        files.push_back(f);
                    
                }

        void AddComp(char* s)
                {
                        Add(new Composite(s));
                }

        void AddLeaf(char* s)
                {
                        Add(new Leaf(s));
                }

        Menu* GetHandle(char* s)
                {
                        for(int i=0;i<files.size();i++)
                        {
                                if(strcmp(s,files[i]->GetName())==0)
                                    return (Menu*)files[i];
                    }
            cout<<"Directory "<<s<<" not found in "<<name<<endl;
            exit(1);
        }
         void remove(char* s)
        {
            vector<Interface*>::iterator p = files.begin();
            // Points to the 1st element of the vector.
            for(int i=0;i<files.size();i++,p++)
            {
                if(strcmp(s,files[i]->GetName())==0)
                    files.erase(p);
            }
        }
        
};// End of Menu

// main begins her
int main()
{
    Menu m("Menu");     // First the main menu is created.
    
    m.AddComp("File"); // One composite object is inserted into the main menu.
    m.AddLeaf("Edit"); // One leaf object is inserted.
    m.AddLeaf("Search");// One leaf object is inserted.

    m.GetHandle("File")->AddLeaf("New");
    m.GetHandle("File")->AddLeaf("Open");
    m.GetHandle("File")->AddComp("Run");
    m.GetHandle("File")->GetHandle("Run")->AddLeaf("compile");
    m.GetHandle("File")->GetHandle("Run")->AddLeaf("build");
    m.GetHandle("File")->remove("Open");
    
    m.AddComp("Combo");
   
    m.GetHandle("Combo")->AddComp("Burger");
    
//
//    m.GetHandle("Combo")->GetLeftHandle("Burger")->AddLeaf("Bun");
//    m.GetHandle("Combo")->GetRightHandle("Burger")->AddLeaf("Bun");
    
    m.GetHandle("Combo")->GetHandle("Burger")->AddLeaf("Bun");
    m.GetHandle("Combo")->GetHandle("Burger")->AddLeaf("Chicken");
    m.GetHandle("Combo")->GetHandle("Burger")->AddLeaf("Onion");
   
    // WATCH the traversal here..
    // If we have to use  inOrder postOrder preOrder traversal of the tree
    // NOTE Add such traversal to Composite
    Composite *mGetHandle =  m.GetHandle("Combo");
    mGetHandle->ls();
   
    
//    m.GetHandle("Combo")->AddLeaf("Bun");
//    m.GetHandle("Combo")->AddLeaf("Chicken");
//    m.GetHandle("Combo")->AddLeaf("Cheese");
    
    m.GetHandle("Combo")->AddComp("Coke");
    
    m.GetHandle("Combo")->GetHandle("Coke")->AddLeaf("250ml");
    
    m.GetHandle("Combo")->AddComp("Nuggets");
    m.GetHandle("Combo")->GetHandle("Nuggets")->AddLeaf("Medium");
    m.GetHandle("Combo")->AddLeaf("Take away Box");
  
    m.ls(); // displays all the children of object m with their hierarchies.
    
//    m.GetHandle("File")->Display(); // displays all the children of the object named "File"
                    // without their hierarchies.
}

// End of main

/*
 
 Combo:
      Burger:
           Bun
           Chicken
           Onion
 Menu:
      File:
           New
           Run:
                compile
                build
      Edit
      Search
      Combo:
           Burger:
                Bun
                Chicken
                Onion
           Coke:
                250ml
           Nuggets:
                Medium
           Take away Box
 Program ended with exit code: 0
 
 */
