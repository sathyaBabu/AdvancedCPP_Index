//
//  main.cpp
//  17_StateMachineTupleLambda
//
//  Created by Sathya Babu on 01/11/21.
// https://sii.pl/blog/implementing-a-state-machine-in-c17/

// https://sii.pl/blog/implementing-a-state-machine-in-c17-part-2/
// part 1  2 3 4  source
// https://github.com/AdamsPL/state-machine

#include <iostream>
#include <tuple>
#include <variant>
#include <functional>


// sathyahelp123@gmail.com
// State pattern in modern c++ Prerequsite Legacy state pattern

template <typename... States>  // receives closedState OpenState  : First time received  ClosedState
class StateMachine
{
public:
    template <typename State>  // we will receive a toggled state here..
    void transitionTo()
    {   // return type of  TOGGLED STATE :  TransitionTo<OpenState>     or ClosedState                                                         // handle(const OpenEvent&) const
        currentState = &std::get<State>(states);  // states->receives closedState OpenState
        //                      event    state
        std::cout << " current state  : "<< typeid( currentState ).name() << std::endl ;
        /*
         Now is time to add a method to change the current state of the machine. Once again, since we distinguish states by their type, it has to be a template method.
         */
    }

    template <typename Event>
    void handle(const Event& event)  //receives :OpenEvent{}  Closedevent
    {
        std::cout << " handle( Object tpye )  : "<< typeid( event ).name() << std::endl ; // 9OpenEvent
        
        
        auto passEventToState = [this, &event] (auto statePtr) { // statePtr is currentState  closedState
            std::cout << " event ( statePtr  )  : "<< typeid( event ).name() <<  " : "<<typeid( statePtr ).name()  <<std::endl ; // 9OpenEvent : P11ClosedState
            statePtr->handle(event).execute(*this);// event : OpenEvent : this * is open Closed address
        // closedState->handle( OpenEvent ).execute(*this);
        };
        std::cout << " current state  from handle  : "<< typeid( currentState ).name() << std::endl ;
        // ClosedStateP9OpenStateEEE
        std::visit(passEventToState, currentState);  // currentState tuple state will visit passEventToState
    }

private:
    std::tuple<States...> states;  //  A variadic template containing a std::tuple
    std::variant<States*...> currentState{ &std::get<0>(states) };// 0: represents ClosedState
    // CHECK THE DOC BELOW******** OpenEvent CloseEvent dummy
};
/*************
 Next on our todo list is to keep track which state is currently selected. Normally a plain pointer or a reference would suffice, but that’s not going to work in this case, because it’s impossible to select a single type that would accept all possible state types (besides void*, but that would be useless for us). As we’re trying to store heterogeneous data types we can use the std::variant (C++17) for that task. Since std::variant disallows using it with references, we have to use plain pointers. Additionally, we assume that the first state type provided to the state machine is the initial state.
 */
// Here is where we notofy Machine of state changes
/*
 Now it's time to add a method to change the current state of the machine. Once again, since we distinguish states by their type, it has to be a template method.
 */
template <typename State>
struct TransitionTo
{
    template <typename Machine>
    void execute(Machine& machine)
    {
        std::cout << "  TransitionTo.execute(*this )state :  : "<< typeid( State ).name() << " machine "
        << typeid( machine ).name() <<std::endl ; // 9OpenEvent
        
        machine.template transitionTo< State >();  // This calls StateMachine to set new state : OpenState
        // calls StateMachine.TransitionTo
        // changes :  currentState = &std::get<State>(states);  // states->receives closedState OpenState
        //  TransitionTo.execute(*this )state :  : 9OpenState machine 12StateMachineIJ11ClosedState9OpenStateEE
        
    }
};

struct Nothing
{
    template <typename Machine>
    void execute(Machine&)
    {
    }
};

struct OpenEvent
{
};

struct CloseEvent
{
};

struct ClosedState;
struct OpenState;


// Here is where state changes ClosedState will return OPen state
//to the struct TransitionTo so that it calls the state machine to change the state

struct ClosedState  // returning  OpenState : TransitionTo<OpenState>
{
    TransitionTo< OpenState > handle( const OpenEvent& ) const
    {
        std::cout << "Opening the door..." << std::endl;
        return {}; // points to TransitionTo execute...
        //  TransitionTo.execute(*this )state :  : 9OpenState machine 12StateMachineIJ11ClosedState9OpenStateEE
    }

    Nothing handle( const CloseEvent& ) const
    {
        std::cout << "Cannot close. The door is already closed!" << std::endl;
        return {};
    }
};

// Here is where state changes OpenState will return Closedstate
// to the struct TransitionTo so that it calls the state machine to change the state

struct OpenState  //  // returning ClosedState  TransitionTo<ClosedState>
{
    Nothing handle(const OpenEvent&) const
    {
        std::cout << "Cannot open. The door is already open!" << std::endl;
        return {};
    }

    TransitionTo< ClosedState > handle(const CloseEvent&) const
    {
        std::cout << "Closing the door..." << std::endl;
        return {};
    }
};
//                            2           1
using Door = StateMachine<ClosedState, OpenState>;  // receives States... as var number of args ClosedState, OpenState

int main()
{
    Door door; // 12 StateMachine IJ11 ClosedState 9OpenState EE

    
    std::cout << " Default Object tpye : "<< typeid( door).name() << std::endl ; // 12 StateMachine IJ11 ClosedState 9OpenState EE
    // openState.handle( OpenEvent{});
    door.handle( OpenEvent{}  );  // dummy event struct OpenEvent  ( sent as a state - > event )
    door.handle( CloseEvent{} );  //  // dummy event struct CloseEvent

    door.handle( CloseEvent{} );
    door.handle( OpenEvent{}  );

    return 0;
}

/*
 Opening the door...
 Closing the door...
 Cannot close. The door is already closed!
 Opening the door...
 Program ended with exit code: 0
 */
/*
 // pre requsite to understand
 //   --------->  machine.template transitionTo<State>();
 
 //
 //  main.cpp
 //  17_State_Prerequsite_1
 //
 //  Created by Sathya Babu on 29/06/23.
 //
 #include <iostream>
 #include <typeinfo>
 /*
  the TransitionTo struct is defined with a single template parameter State. Inside the struct, there is a member function named execute that takes a reference to a Machine object and transitions it to the specified State.

 The execute function uses the template keyword to indicate that transitionTo is a dependent template member function and should be treated as such by the compiler. This allows the compiler to correctly parse and instantiate the function.

 To use this TransitionTo struct, you can create an instance and call the execute function, passing a Machine object as an argument
  
  we define a Machine struct that has a member function transitionTo template. We also define a MyState struct as an example state. In the main function, we create a Machine object and a TransitionTo<MyState> object. We then call the execute function of the TransitionTo object, passing the Machine object as an argument. This will invoke the transitionTo member function of the Machine object, transitioning it to the MyState state.

  Note that the example code uses std::cout to print the name of the state. Make sure to include the appropriate headers (<iostream>, <typeinfo>) for the code to compile successfully.
  
  ------------
  
  n this code, the TransitionTo struct is defined with a single template parameter State, and it contains a member function execute that takes a reference to a Machine object and transitions it to the specified State using the transitionTo member function of the Machine object.

  The Machine struct represents a hypothetical state machine and contains the transitionTo member function template. In this example, the transitionTo function simply prints the name of the state using typeid.

  In the main function, we create a Machine object named machine and a TransitionTo<MyState> object named transition. We then call the execute function of the transition object, passing the machine object as an argument. This will invoke the transitionTo member function of the Machine object, transitioning it to the MyState state.
  
  --------->  machine.template transitionTo<State>();
  
  In the line machine.template transitionTo<State>();, the template keyword is used to indicate that transitionTo is a dependent template member function.

  In C++, when a dependent name is followed by a dot (.) or arrow (->) operator, the compiler doesn't know whether the member is a variable, function, or template. To resolve this ambiguity, the template keyword is used to explicitly tell the compiler that transitionTo is a template member function.

  In the given code, transitionTo is a member function template of the Machine struct. By using template before transitionTo, it informs the compiler that transitionTo is a template function and that it should perform template argument deduction for the <State> template parameter.

  This syntax is required when accessing dependent names that are member function templates in templates or when using a dependent name as a member function pointer.

  In summary, machine.template transitionTo<State>(); tells the compiler that transitionTo is a template member function and allows it to perform template argument deduction for the <State> template parameter.
  
  */
/*
 // < YourState >
 template < typename State >
 struct TransitionTo
 {
     template <typename Machine>
     void execute(Machine& machine)
     {
         // call the following class template  :  machine.template
         machine.template   transitionTo< State >();  // passing YourStater
     }
 };

 struct Machine
 {
     template <typename State>
     void transitionTo()
     {
         std::cout << "Transitioning to state: " << typeid(State).name() << std::endl;
     }
 };

 struct MyState {};
 struct YourState {};

 int main()
 {
     Machine machine;
     TransitionTo< YourState > transition;
     transition.execute( machine );

     return 0;
 }
 // Transitioning to state: 9YourState


 
 
 */
