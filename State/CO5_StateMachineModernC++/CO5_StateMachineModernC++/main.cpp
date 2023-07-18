//
//  main.cpp
//  CO5_StateMachineModernC++
//
//  Created by Sathya Babu on 19/01/22.
//
#include <iostream>
#include<string>
#include <variant>
#include <vector>
#include <optional>
using namespace std;
/* ---------------------------------  Events ------------------------------------------
 A classical approach is not loosely coupled between events & states
  The changes in the sequence of events or adding
  new events will impact the condition part of states implemented in on_event()
   which violates the Open-Closed Principle.
 *** --->
  But in the case of Functional approach events & states are not related or coupled.
   Rather it works in combination defined in the transition class.
   This gives a lot of flexibility along with preserving the Single Responsibility
   Principle & Open-Closed Principle.

 
 */
struct EventConnect { string m_address; };
struct EventConnected { };
struct EventDisconnect { };
struct EventTimeout { };

using Event = variant<EventConnect, EventConnected, EventDisconnect, EventTimeout>;
/* ------------------------------------------------------------------------------------- */


/* ---------------------------------  States ------------------------------------------ */
struct Idle { };
struct Connecting {
    string                      m_address;
    uint32_t                    m_trial = 0;
    static constexpr uint8_t    m_max_trial = 3;
};
struct Connected { };

using State = variant<Idle, Connecting, Connected>;
/* ------------------------------------------------------------------------------------- */


/* -----NOTE ---> -***** Transitions  Bring in Lambda with Overload here.. Assignment ---------------------------------------- */
struct Transitions {
    optional<State> operator()(Idle &, const EventConnect &e) {
        
        cout << "Idle -> Connect" << endl;
        
        return Connecting{e.m_address};
    }

    optional<State> operator()(Connecting &, const EventConnected &) {
        cout << "Connecting -> Connected" << endl;
        return Connected{};
    }

    optional<State> operator()(Connecting &s, const EventTimeout &) {
        cout << "Connecting -> Timeout" << endl;
        return ++s.m_trial < Connecting::m_max_trial ? nullopt : optional<State>(Idle{});
    }

    optional<State> operator()(Connected &, const EventDisconnect &) {
        cout << "Connected -> Disconnect" << endl;
        return Idle{};
    }

    template <typename State_t, typename Event_t>
    optional<State> operator()(State_t &, const Event_t &) const {
        cout << "Unkown" << endl;
        return nullopt;
    }
};

/* ------------------------------------------------------------------------------------- */
template <typename StateVariant, typename EventVariant, typename Transitions>
struct Bluetooth {
    StateVariant m_curr_state;

    void dispatch(const EventVariant &Event)
    {
        optional<StateVariant> new_state = visit(Transitions{}, m_curr_state, Event);
        if (new_state)
            m_curr_state = *move(new_state);
    }

    template <typename... Events>
    void establish_connection(Events... e) { (dispatch(e), ...); }
};

int main() {
    Bluetooth<State, Event, Transitions> bl;

    bl.establish_connection(EventConnect{"107.100.109.116"},
                            EventTimeout{},
                            EventConnected{},
                            EventDisconnect{});
    return EXIT_SUCCESS;
}
/*
Idle -> Connect
Connecting -> Timeout
Connecting -> Connected
Connected -> Disconnect
*/
