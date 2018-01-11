/*
 *
 *    Copyright (c) 2012-2017 Nest Labs, Inc. All Rights Reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *
 */

/**
 *    @file
 *      This file implements a unit test for a the Nest Labs Finite
 *      State Machine library.
 *
 *                                 Skip
 *               .----------------------------------------.
 *               |                                        |
 *               |                 Stay                   |
 *               |                 .---.                  |
 *               |                 V   |                  |
 *               |               .-------.                |
 *               |   .-----------|       |<------------.  |
 *               |   |    .----->|   A   |-------.     |  |
 *               |   |   B| .----!_______!<----. |B    |  |
 *               |   |   a| |F       |        F| |a    |  |
 *               |   |   c| |o       |Error   o| |c    |  |
 *               |   |   k| |r       V        r| |k    |  |
 *               |   |   w| |w   .-------.    w| |w    |  |
 *               |   |   a| |a   |   D   |    a| |a    |  |
 *               |   |   r| |r   '-------'    r| |r    |  |
 *               |   |   d| |d  __/\   /\__   d| |d    |  |
 *               |   |    | V  /           \   | V     |  |
 *               |   |  .-------. Forward   .-------.  |  |
 *               |   |  |       |---------->|       |  |  |
 *               '----->|   B   |           |   C   |-----'
 *                   |  !_______!<----------!_______!  |
 *                   |   |  |  ^   Backward  ^  |  ^   |
 *                   |   |  '--'             |  '--'   |
 *                   |   |  Stay             |  Stay   |
 *                   |   |                   |         |
 *                   '---|-------------------'         |
 *                       |      Skip                   |
 *                       |                             |
 *                       '-----------------------------'
 *                                    Skip
 */

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#include <nestlabs/fsm/nlfsm.hpp>

using namespace nl;

#include "nlunit-test.h"

/* Preprocessor Definitions */

#define ARRAY_SIZE(array)		(sizeof(array) / sizeof(array[0]))

#define AssignEvent(id) id
#define AssignState(id) id

#define DeclareEvent(event) \
    nl::Fsm::Event sEvent##event(AssignEvent(kEvent##event))

#define DeclareState(state) \
    nl::Fsm::State sState##state(AssignState(kState##state))

#define DeclareTransition(name, current, event, next)   \
    { current, event, next }

/* Type Definitions */

enum Event {
    kEventFirst        = 0,

    kEventForward      = kEventFirst,
    kEventStay,
    kEventBackward,
    kEventSkip,
    kEventError,

    kEventLast         = kEventError
};

typedef Event Event;

enum State {
    kStateFirst       = 0,

    kStateA           = kStateFirst,
    kStateB,
    kStateC,
    kStateD,

    kStateLast        = kStateD
};

typedef State State;

/* Function Prototypes */

/* Global Variables */

static void TestEvent(nlTestSuite *inSuite, void *inContext)
{
    // Test construction

    nl::Fsm::Event event1(kEventForward);
    nl::Fsm::Event event2(event1);

    // Test destruction

    {
        // this test is now pointless
        // because we refactored events
        // to be integers instead of classes
        nl::Fsm::Event event3 = kEventForward;
        (void) event3;
    }

    // Test assignment

    nl::Fsm::Event event4(kEventForward);
    nl::Fsm::Event event5 = event4;
    nl::Fsm::Event event6 = kEventForward;

    // Test equality

    NL_TEST_ASSERT(inSuite, event1 == event2);
    NL_TEST_ASSERT(inSuite, event4 == event5);
    NL_TEST_ASSERT(inSuite, event1 == event4);
    NL_TEST_ASSERT(inSuite, event5 == event6);

    // Test accessors

    NL_TEST_ASSERT(inSuite, event1 == kEventForward);
    NL_TEST_ASSERT(inSuite, event2 == kEventForward);
    NL_TEST_ASSERT(inSuite, event4 == kEventForward);
    NL_TEST_ASSERT(inSuite, event5 == kEventForward);
    NL_TEST_ASSERT(inSuite, event6 == kEventForward);
}

static void TestState(nlTestSuite *inSuite, void *inContext)
{
    // Test construction

    nl::Fsm::State state1(kStateA);
    nl::Fsm::State state2(state1);

    // Test destruction

    {
        nl::Fsm::State state3 = kStateA;
        (void) state3;
    }

    // Test assignment

    nl::Fsm::State state4 = kStateA ;
    nl::Fsm::State state5 = state4;
    nl::Fsm::State state6 = kStateA;

    // Test equality

    NL_TEST_ASSERT(inSuite, state1 == state2);
    NL_TEST_ASSERT(inSuite, state4 == state5);
    NL_TEST_ASSERT(inSuite, state1 == state4);
    NL_TEST_ASSERT(inSuite, state5 == state6);

    // Test accessors

    NL_TEST_ASSERT(inSuite, state1 == kStateA);
    NL_TEST_ASSERT(inSuite, state2 == kStateA);
    NL_TEST_ASSERT(inSuite, state4 == kStateA);
    NL_TEST_ASSERT(inSuite, state5 == kStateA);
    NL_TEST_ASSERT(inSuite, state6 == kStateA);
}

static void TestTransition(nlTestSuite *inSuite, void *inContext)
{
    // Test construction
    nl::Fsm::State stateA(kStateA);
    nl::Fsm::State stateB(kStateB);
    nl::Fsm::Event eventForward(kEventForward);
    nl::Fsm::Transition transition1 = {stateA, eventForward, stateB};
    nl::Fsm::Transition transition2 = {stateA, eventForward, stateB};

    // Test destruction

    {
        nl::Fsm::Transition transition3 = {stateA, eventForward, stateB};
        (void) transition3;
    }

    // Test equality

    NL_TEST_ASSERT(inSuite, transition1 == transition2);

    // Test accessors

    NL_TEST_ASSERT(inSuite, transition1.mStart == stateA);
    NL_TEST_ASSERT(inSuite, transition1.mEvent == eventForward);
    NL_TEST_ASSERT(inSuite, transition1.mEnd == stateB);
}

static void GetTransitions(const nl::Fsm::Transition * &outFirst, size_t &outSize)
{
    /* Static Data Members */

    /*
     * State machine events
     */
    static const DeclareEvent(Forward);
    static const DeclareEvent(Stay);
    static const DeclareEvent(Backward);
    static const DeclareEvent(Skip);
    static const DeclareEvent(Error);

    /*
     * State machine states
     */
    static const DeclareState(A);
    static const DeclareState(B);
    static const DeclareState(C);
    static const DeclareState(D);

    /*
     * State machine transitions
     */

#if 0


    static const DeclareTransition(sTransitionB_Stay,
                                   sStateB,
                                   sEventStay,
                                   sStateB);
    static const DeclareTransition(sTransitionB_Forward,
                                   sStateB,
                                   sEventForward,
                                   sStateC);
    static const DeclareTransition(sTransitionB_Backward,
                                   sStateB,
                                   sEventBackward,
                                   sStateA);
    static const DeclareTransition(sTransitionB_Skip,
                                   sStateB,
                                   sEventSkip,
                                   sStateA);
    static const DeclareTransition(sTransitionB_Error,
                                   sStateB,
                                   sEventError,
                                   sStateD);

    // Transitions arcs from C

    static const DeclareTransition(sTransitionC_Stay,
                                   sStateC,
                                   sEventStay,
                                   sStateC);
    static const DeclareTransition(sTransitionC_Forward,
                                   sStateC,
                                   sEventForward,
                                   sStateA);
    static const DeclareTransition(sTransitionC_Backward,
                                   sStateC,
                                   sEventBackward,
                                   sStateB);
    static const DeclareTransition(sTransitionC_Skip,
                                   sStateC,
                                   sEventSkip,
                                   sStateB);
    static const DeclareTransition(sTransitionC_Error,
                                   sStateC,
                                   sEventError,
                                   sStateD);
#endif

    /*
     * Transition array/table for the service state machine
     */
    static const nl::Fsm::Transition sTransitions[] = {
        // Transitions arcs from A
        DeclareTransition(sTransitionA_Stay, sStateA, sEventStay, sStateA),
        DeclareTransition(sTransitionA_Forward, sStateA, sEventForward, sStateB),
        DeclareTransition(sTransitionA_Backward, sStateA, sEventBackward, sStateC),
        DeclareTransition(sTransitionA_Skip, sStateA, sEventSkip, sStateC),
        DeclareTransition(sTransitionA_Error, sStateA, sEventError, sStateD),

        // Transitions arcs from B
        DeclareTransition(sTransitionB_Stay, sStateB, sEventStay, sStateB),
        DeclareTransition(sTransitionB_Forward, sStateB, sEventForward, sStateC),
        DeclareTransition(sTransitionB_Backward, sStateB, sEventBackward, sStateA),
        DeclareTransition(sTransitionB_Skip, sStateB, sEventSkip, sStateA),
        DeclareTransition(sTransitionB_Error, sStateB, sEventError, sStateD),

        // Transitions arcs from C
        DeclareTransition(sTransitionC_Stay, sStateC, sEventStay, sStateC),
        DeclareTransition(sTransitionC_Forward, sStateC, sEventForward, sStateA),
        DeclareTransition(sTransitionC_Backward, sStateC, sEventBackward, sStateB),
        DeclareTransition(sTransitionC_Skip, sStateC, sEventSkip, sStateB),
        DeclareTransition(sTransitionC_Error, sStateC, sEventError, sStateD)
    };

    outFirst = sTransitions;
    outSize = ARRAY_SIZE(sTransitions);
}

static void TestMachine(nlTestSuite *inSuite, void *inContext)
{
    const nl::Fsm::Transition * first = 0;
    size_t size = 0;
    const nl::Fsm::State stateA(kStateA);
    const nl::Fsm::State stateB(kStateB);

    GetTransitions(first, size);

    NL_TEST_ASSERT(inSuite, first != 0);
    NL_TEST_ASSERT(inSuite, size != 0);

    // Test construction

    nl::Fsm::Machine machine1(first, size, stateA);
    
    // Test destruction

    {
        nl::Fsm::Machine machine3(first, size, stateA);
    }

    // Test observers

    NL_TEST_ASSERT(inSuite, machine1.GetCurrentState() == stateA);

    // Find expected transitions for current state A.

    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateA, kEventStay) != NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateA, kEventForward) != NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateA, kEventBackward) != NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateA, kEventSkip) != NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateA, kEventError) != NULL);

    // Find expected transitions for current state B.

    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateB, kEventStay) != NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateB, kEventForward) != NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateB, kEventBackward) != NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateB, kEventSkip) != NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateB, kEventError) != NULL);

    // Find expected transitions for current state C.

    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateC, kEventStay) != NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateC, kEventForward) != NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateC, kEventBackward) != NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateC, kEventSkip) != NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateC, kEventError) != NULL);

    // Find expected transitions for current state D.

    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateD, kEventStay) == NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateD, kEventForward) == NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateD, kEventBackward) == NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateD, kEventSkip) == NULL);
    NL_TEST_ASSERT(inSuite, machine1.FindTransition(kStateD, kEventError) == NULL);

    // Test modifiers

    machine1.SetCurrentState(stateB);

    NL_TEST_ASSERT(inSuite, machine1.GetCurrentState() == stateB);
}

static void TestDelegate(nlTestSuite *inSuite, nl::Fsm::Delegate::Base &inDelegate, bool (nl::Fsm::Delegate::Base::*inMethod)(const nl::Fsm::Event &inEvent,
                                                                                                                              const nl::Fsm::State &inState), size_t inIterations, bool inExpect)
{
    const nl::Fsm::Event eventStay(kEventStay);
    const nl::Fsm::State stateA(kStateA);
    bool result = !inExpect;
    size_t i;

    for (i = 0; i < inIterations; i++) {
        result = (inDelegate.*inMethod)(eventStay, stateA);

        if (result == inExpect)
            break;
    }

    NL_TEST_ASSERT(inSuite, result == inExpect && i < inIterations);
}

static void TestDelegate(nlTestSuite *inSuite, nl::Fsm::Delegate::Base &inDelegate, bool (nl::Fsm::Delegate::Base::*inMethod)(const nl::Fsm::Event &inEvent,
                                           const nl::Fsm::Transition &inTransition), size_t inIterations, bool inExpect)
{
    const nl::Fsm::Event eventStay(kEventStay);
    const nl::Fsm::State stateA(kStateA);
    const nl::Fsm::Transition transitionA_Stay = {stateA, eventStay, stateA};
    bool result = !inExpect;
    size_t i;

    for (i = 0; i < inIterations; i++) {
        result = (inDelegate.*inMethod)(eventStay, transitionA_Stay);

        if (result == inExpect)
            break;
    }

    NL_TEST_ASSERT(inSuite, (result == inExpect) && (i < inIterations));
}

static void TestDelegate(nlTestSuite *inSuite, nl::Fsm::Delegate::Base &inDelegate, size_t inIterations, bool inExpect)
{
    TestDelegate(inSuite, inDelegate, &nl::Fsm::Delegate::Base::WillHandleEvent, inIterations, inExpect);
    TestDelegate(inSuite, inDelegate, &nl::Fsm::Delegate::Base::DidHandleEvent, inIterations, inExpect);
    
    TestDelegate(inSuite, inDelegate, &nl::Fsm::Delegate::Base::WillExitState, inIterations, inExpect);
    TestDelegate(inSuite, inDelegate, &nl::Fsm::Delegate::Base::DidExitState, inIterations, inExpect);

    TestDelegate(inSuite, inDelegate, &nl::Fsm::Delegate::Base::WillTransition, inIterations, inExpect);
    TestDelegate(inSuite, inDelegate, &nl::Fsm::Delegate::Base::DidTransition, inIterations, inExpect);

    TestDelegate(inSuite, inDelegate, &nl::Fsm::Delegate::Base::WillEnterState, inIterations, inExpect);
    TestDelegate(inSuite, inDelegate, &nl::Fsm::Delegate::Base::DidEnterState, inIterations, inExpect);
}

static void TestDelegates(nlTestSuite *inSuite, void *inContext)
{
    // Test construction

    nl::Fsm::Delegate::Always always1;
    nl::Fsm::Delegate::Never never1;
    nl::Fsm::Delegate::Random random1;
    nl::Fsm::Delegate::Random random2(0x235A);

    // Test destruction

    {
        nl::Fsm::Delegate::Always always2;
        nl::Fsm::Delegate::Never never2;
        nl::Fsm::Delegate::Random random3;
    }

    // Test delegations

    TestDelegate(inSuite, always1, 1, true);
    TestDelegate(inSuite, never1, 1, false);
    TestDelegate(inSuite, random1, 100, true);
    TestDelegate(inSuite, random1, 100, false);
}

static void TestDriver(nlTestSuite *inSuite, void *inContext)
{
    const nl::Fsm::Transition * first = 0;
    size_t size = 0;
    const nl::Fsm::State stateA(kStateA);
    nl::Fsm::Delegate::Always always;
    nl::Fsm::Delegate::Never never;

    GetTransitions(first, size);

    NL_TEST_ASSERT(inSuite, first != 0);
    NL_TEST_ASSERT(inSuite, size != 0);

    nl::Fsm::Machine machine1(first, size, stateA);

    // Test construction

    nl::Fsm::Driver driver1(machine1, &always);
    nl::Fsm::Driver driver2(machine1, &never);
    nl::Fsm::Driver driver3;

    // Test destruction

    {
        nl::Fsm::Driver driverToDestruct(machine1, &always);
    }

    // Test event handling

    NL_TEST_ASSERT(inSuite, machine1.GetCurrentState() == kStateA);
    
    NL_TEST_ASSERT(inSuite, driver3.HandleEvent(kEventStay) == false);
    NL_TEST_ASSERT(inSuite, driver3.HandleEvent(kEventStay, kStateA) == false);
    
    NL_TEST_ASSERT(inSuite, driver1.HandleEvent(kEventStay) == true);
    NL_TEST_ASSERT(inSuite, driver2.HandleEvent(kEventStay) == false);
    NL_TEST_ASSERT(inSuite, machine1.GetCurrentState() == kStateA);

    NL_TEST_ASSERT(inSuite, driver1.HandleEvent(kEventForward) == true);
    NL_TEST_ASSERT(inSuite, driver2.HandleEvent(kEventForward) == false);
    NL_TEST_ASSERT(inSuite, machine1.GetCurrentState() == kStateB);

    NL_TEST_ASSERT(inSuite, driver1.HandleEvent(kEventBackward) == true);
    NL_TEST_ASSERT(inSuite, driver2.HandleEvent(kEventBackward) == false);
    NL_TEST_ASSERT(inSuite, machine1.GetCurrentState() == kStateA);

    NL_TEST_ASSERT(inSuite, driver1.HandleEvent(kEventSkip) == true);
    NL_TEST_ASSERT(inSuite, driver2.HandleEvent(kEventSkip) == false);
    NL_TEST_ASSERT(inSuite, machine1.GetCurrentState() == kStateC);

    NL_TEST_ASSERT(inSuite, driver1.HandleEvent(kEventError) == true);
    NL_TEST_ASSERT(inSuite, driver2.HandleEvent(kEventError) == false);
    NL_TEST_ASSERT(inSuite, machine1.GetCurrentState() == kStateD);

    NL_TEST_ASSERT(inSuite, driver1.HandleEvent(kEventStay) == false);
    NL_TEST_ASSERT(inSuite, driver2.HandleEvent(kEventStay) == false);
    NL_TEST_ASSERT(inSuite, machine1.GetCurrentState() == kStateD);

    NL_TEST_ASSERT(inSuite, driver1.HandleEvent(kEventForward) == false);
    NL_TEST_ASSERT(inSuite, driver2.HandleEvent(kEventForward) == false);
    NL_TEST_ASSERT(inSuite, machine1.GetCurrentState() == kStateD);

    NL_TEST_ASSERT(inSuite, driver1.HandleEvent(kEventBackward) == false);
    NL_TEST_ASSERT(inSuite, driver2.HandleEvent(kEventBackward) == false);
    NL_TEST_ASSERT(inSuite, machine1.GetCurrentState() == kStateD);

    NL_TEST_ASSERT(inSuite, driver1.HandleEvent(kEventSkip) == false);
    NL_TEST_ASSERT(inSuite, driver2.HandleEvent(kEventSkip) == false);
    NL_TEST_ASSERT(inSuite, machine1.GetCurrentState() == kStateD);
}

static const nlTest sTests[] = {
    NL_TEST_DEF("event",      TestEvent),
    NL_TEST_DEF("state",      TestState),
    NL_TEST_DEF("transition", TestTransition),
    NL_TEST_DEF("machine",    TestMachine),
    NL_TEST_DEF("delegates",  TestDelegates),
    NL_TEST_DEF("driver",     TestDriver),
    NL_TEST_SENTINEL()
};

int main(void)
{
    nlTestSuite theSuite = {
        "nlfsm",
        &sTests[0]
    };

    nlTestRunner(&theSuite, NULL);

    return nlTestRunnerStats(&theSuite);
}
