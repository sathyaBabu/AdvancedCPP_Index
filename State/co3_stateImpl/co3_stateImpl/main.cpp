//
//  main.cpp
//  co3_stateImpl
//
//  Created by Sathya Babu on 01/12/21.
//
#include <iostream>
#include <tuple>
#include <variant>
#include <functional>

// State pattern in modern c++ Prerequsite Legacy state pattern

template <typename... States>  // receives closedState OpenState
class StateMachine
{
public:
    template <typename State>  // we will receive a toggled state here..
    void transitionTo()
    {   // return type of  TOGGLED STATE :  TransitionTo<OpenState>     or ClosedState                                                         // handle(const OpenEvent&) const
        currentState = &std::get<State>(states);  // states->receives closedState OpenState
        //                      event    state
        /*
         Now is time to add a method to change the current state of the machine. Once again, since we distinguish states by their type, it has to be a template method.
         */
    }

    template <typename Event>
    void handle(const Event& event)  //receives :OpenEvent{}  Closedevent
    {
        auto passEventToState = [this, &event] (auto statePtr) { // statePtr is currentState  openState or closedState
           
            // current state -> execute->??????
            statePtr->handle(event).execute(*this);// this * is open Closed address
        // closedState->handle( OpenEvent ).execute(*this);
        };
        std::visit(passEventToState, currentState);  // currentState tuple state will visit passEventToState
    }

private:
    std::tuple<States...> states;  //  A variadic template containing a std::tuple
    std::variant<States*...> currentState{ &std::get<0>(states) };// 0: represents ClosedState
    // CHECK THE DOC BELOW******** OpenEvent CloseEvent dummy
};
/*************
 Next on our todo list is to keep track which state is currently selected. Normally a plain pointer or a
 reference would suffice, but that’s not going to work in this case, because it’s impossible to select a
 single type that would accept all possible state types (besides void*, but that would be useless for us).
 As we’re trying to store heterogeneous data types we can use the std::variant (C++17) for that task. Since
 std::variant disallows using it with references, we have to use plain pointers. Additionally, we assume that
 the first state type provided to the state machine is the initial state.
 */

// Here is where we notofy Machine of state changes
/*
 Now is time to add a method to change the current state of the machine. Once again,
 since we distinguish states by their type, it has to be a template method.
 */

// loose couple the object..

template <typename State>
struct TransitionTo
{
    template <typename Machine>
    void execute(Machine& machine)
    {
        machine.template transitionTo<State>();  // This calls StateMachine to set new state
        
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
    TransitionTo<OpenState> handle(const OpenEvent&) const
    {
        std::cout << "Opening the door..." << std::endl;
        return {};
    }

    Nothing handle(const CloseEvent&) const
    {
        std::cout << "Cannot close. The door is already closed!" << std::endl;
        return {};
    }
};

// Here is where state changes OpenState will return Closedstate
//to the struct TransitionTo so that it calls the state machine to change the state

struct OpenState  //  // returning ClosedState  TransitionTo<ClosedState>
{
    Nothing handle(const OpenEvent&) const
    {
        std::cout << "Cannot open. The door is already open!" << std::endl;
        return {};
    }

    TransitionTo<ClosedState> handle(const CloseEvent&) const
    {
        std::cout << "Closing the door..." << std::endl;
        return {};
    }
};

using Door = StateMachine<ClosedState, OpenState>;  // receives States..

int main()
{
    Door door;

    door.handle(OpenEvent{});  // closed state..dummy event struct OpenEvent  ( sent as a state - > event )
    door.handle(CloseEvent{});  // open state..// dummy event struct CloseEvent

    door.handle(CloseEvent{});
    door.handle(OpenEvent{});

    return 0;
}
/*
 
 Opening the door...
 Closing the door...
 Cannot close. The door is already closed!
 Opening the door...
 Program ended with exit code: 0
 
 
 */
