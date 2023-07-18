//
//  main.cpp
//  17_deligate_2
//
//  Created by Sathya Babu on 10/10/22.
// https://waqqas.medium.com/delegation-pattern-in-c-5af7496ad268#:~:text=A%20delegation%20pattern%20is%20a%20way%20to%20extend%20the%20functionality,is%20called%20the%20%E2%80%9Creceiver%E2%80%9D.

// https://en.wikipedia.org/wiki/Delegation
/*
 There are a number of reasons someone may decide to delegate. These include:

 To free themselves up to do other tasks in the pace of their own
 To have the most qualified person making the decisions
 To seek another qualified person's perspective on an issue
 To develop someone else's ability to handle the additional assignments judiciously and successfully.[3]
 
 The process of delegation does not always follow a conformed structure, nor is it straightforward, however there are a number of key aspects which are generally involved. The generalised process of delegation involves some combination of the following:

 Allocation of duties: the delegator communicates to their subordinate the task which is to be performed. Resources are provided and a time limit is informed.
 Delegation of authority: In order for the subordinate to perform the task, authority is required. The required authority is granted to the employee when the task is delegated.
 Assignment of responsibilities: When authority is delegated, the subordinate is assigned with the responsibility of this task. When someone is given the rights to complete a task, they are assigned with the corresponding obligation to perform. Responsibility itself cannot be entirely delegated; a manager must still operate under equal responsibility to the delegated authority.
 Creation of accountability: At the completion of the delegation process, it is essential that the manager creates accountability, meaning that subordinates must be answerable for the tasks which they have been authorised to carry out.[7]
 */

#include <iostream>

#include <string>
//Bad practice

/*
 
 
    If you want to extend the View using inheritance,
    you have the receiver from the View. You have to expose the details of the View class.
    This might not be good idea. In contrast,
    the receiver needs to know only about the “interface” class.
 
     ***  Hide the implementatiuon by its interface  ***
 
 
   In delegation we controll the composoble object using interface.
   We are not exposing the complete class

 
 */

// in case of Bridge we are composing the complete class so the user can get access to

class View
{
    
public:
  virtual void onClickListener(void){}
  std::string id(void);
    
};

class Button : public View
{
  void onClickListener(void) override
  {
    std::cout << "Doing actual work for View: " << id() << std::endl;
  }
};
//  Good practice


namespace delegator
{
    class View;

    class ireceiver
    {
    public:
        virtual void onClickListener(const View &) = 0;
    };
}
namespace delegator
{

    class View
    {
//        ireceiver &_delegate;
    private:
        const std::string _id;
       ireceiver &_delegate;
        
        // all the other default property of the button has to be declared here..
        // like color , text  so on

    public:
        View(const std::string &id, ireceiver &delegate) : _id(id), _delegate(delegate) {}

        void do_work()
        {
            _delegate.onClickListener(*this);
        }

        std::string id() const
        {
            return _id;
        }
        // in case of a protocol stack reuse following will be the base protocol stack
        
    };
} // namespace delegator

namespace user_defined
{
    class Button : public delegator::ireceiver
    {
        void onClickListener(const delegator::View &View) override
        {
            std::cout << "Clicked on a Button : delegated from  View : " << View.id() << std::endl;
            //  re use the protocol stack here ... execute your business logic from here
          
        }
    };
}

namespace user_defined
{
    class RadioButton : public delegator::ireceiver
    {
        void onClickListener(const delegator::View &View) override
        {
           // View._delegate  check if its a button or radio button
            // switch( View )  case View.Button... View.radioButton...
            
            // so we can generalize Various Button to One Button..
            
          
            std::cout << "Clicked on aRadio Button : delegated from  View :" << View.id() << std::endl;
            //  execute your business logic from here
        }
    };
}



int main(int argc, char *argv[])
{
    // delegation is a kind of dependency injection / composition
    
      user_defined::Button rButton;
      delegator::View button{"View 1", rButton};
    
    user_defined::RadioButton radioButton;
    delegator::View radio_Button{" View 2", radioButton};

    button.do_work();
    radio_Button.do_work();
    

  return 0;
}


/*
 Clicked on a Button : delegated from  View : Parent Sender 1
 Clicked on aRadio Button : delegated from  View :Parent View 2
 Program ended with exit code: 0
 */
