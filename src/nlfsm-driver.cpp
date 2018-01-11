/*
 *
 *    Copyright (c) 2011-2017 Nest Labs, Inc. All Rights Reserved.
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

/*
 *
 *
 *    Copyright (c) 2008-2013 Nuovation System Designs, LLC
 *    All rights reserved.
 *
 *    IMPORTANT: This software is supplied to you by Nuovation System
 *    Designs, LLC ("Nuovations"). in consideration of your agreement
 *    to the following terms, and your use, installation, modification
 *    or redistribution of this Nuovations software constitutes
 *    acceptance of these terms. If you do not agree with these terms,
 *    please do not use, install, modify or redistribute this
 *    Nuovations software.
 *
 *    In consideration of your agreement to abide by the following
 *    terms, and subject to these terms, Nuovations grants you a
 *    worldwide, non-exclusive license, under Nuovations' copyrights in
 *    this original Nuovations software (the "Nuovations Software"), to
 *    use, reproduce, modify and redistribute the Nuovations Software,
 *    with or without modifications, in source and/or binary forms;
 *    provided that if you redistribute the Nuovations Software in its
 *    entirety and without modifications, you must retain this notice
 *    and the following text and disclaimers in all such
 *    redistributions of the Nuovations Software. Neither the name,
 *    trademarks, service marks or logos of Nuovations may be used to
 *    endorse or promote products derived from the Nuovations Software
 *    without specific prior written permission from Nuovations. Except
 *    as expressly stated in this notice, no other rights or licenses,
 *    express or implied, are granted by Nuovations herein, including
 *    but not limited to any patent rights that may be infringed by
 *    your derivative works or by other works in which the Nuovations
 *    Software may be incorporated.
 *
 *    The Nuovations Software is provided by Nuovations on an "AS IS"
 *    basis. NUOVATIONS MAKES NO WARRANTIES, EXPRESS OR IMPLIED,
 *    INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF
 *    NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *    PURPOSE, REGARDING THE NUOVATIONS SOFTWARE OR ITS USE AND
 *    OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS.
 *
 *    IN NO EVENT SHALL NUOVATIONS BE LIABLE FOR ANY SPECIAL, INDIRECT,
 *    INCIDENTAL OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *    TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY
 *    OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF
 *    THE NUOVATIONS SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY
 *    OF CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR
 *    OTHERWISE, EVEN IF NUOVATIONS HAS BEEN ADVISED OF THE POSSIBILITY
 *    OF SUCH DAMAGE.
 *
 */

/**
 *    @file
 *      This file implements an event handler/driver for a finite
 *      state machine (FSM).
 *
 */

#include <nlassert.h>

#include <nestlabs/fsm/nlfsm-state-delegate-base.hpp>
#include <nestlabs/fsm/nlfsm-machine.hpp>
#include <nestlabs/fsm/nlfsm-transition.hpp>
#include <nestlabs/fsm/nlfsm-driver.hpp>

namespace nl {

namespace Fsm {

/**
 *
 *  @brief
 *    This routine is the class default (i.e. void) constructor. It
 *    instantiates the driver no state machine or event delegate
 *
 */
Driver::Driver(void) :
    mMachine(NULL),
    mDelegate(NULL)
{
    return;
}

/**
 *
 *  @brief
 *    This routine is a class constructor. It instantiates the driver
 *    with the specified state machine and event delegate.
 *
 *  @param[in]  inMachine   A reference to the state machine to instantiate
 *                          with.
 *  @param[in]  inDelegate  A pointer to the event delegate to instantiate
 *                          with.
 *
 */
Driver::Driver(Machine &inMachine, Delegate::Base *inDelegate) :
    mMachine(NULL),
    mDelegate(NULL)
{
    SetMachine(inMachine);
    SetDelegate(inDelegate);
}

/**
 *
 *  @brief
 *    This routine is the setter for the state machine
 *
 *  @param[in]  inMachine  A reference to the state machine to instantiate
 *                         with.
 *
 */
void
Driver::SetMachine(Machine &inMachine)
{
    nlCHECK(&inMachine != NULL);

    mMachine = &inMachine;
}

/**
 *
 *  @brief
 *    This routine is the getter for the state machine
 *
 *  @return  The currently set state machine
 *
 */
Machine *
Driver::GetMachine()
{
    return mMachine;
}

/**
 *
 *  @brief
 *    This routine is the setter for the delegate
 *
 *  @param[in]  inDelegate  A pointer to the event delegate to instantiate
 *                          with.
 *
 */
void
Driver::SetDelegate(Delegate::Base *inDelegate)
{
    mDelegate = inDelegate;
}

/**
 *
 *  @brief
 *    This routine is the getter for the state machine
 *
 *  @return  The currently set delegate
 *
 */
Delegate::Base *
Driver::GetDelegate()
{
    return mDelegate;
}

/**
 *
 *  @brief
 *    This routine handles the specified state machine excitiation
 *    event by finding an appropriate transition for the event, if
 *    any, and moving the state machine through the transition,
 *    triggering various event handlers and delegates along the way.
 *
 *  @param[in]  inEvent  A reference to the state machine excitation event
 *                       to handle.
 *
 *  @return  \c true if the event was handled successfully; otherwise,
 *           \c false.
 *
 */
bool
Driver::HandleEvent(const Event &inEvent)
{
    bool status = true;

    nlPRECONDITION_VALUE(mMachine != NULL, false);

    status = (HandleEvent(inEvent, mMachine->GetCurrentState()));

    return (status);
}

/**
 *
 *  @brief
 *    This routine handles the specified state machine excitiation
 *    event by moving the state machine through the appropriate
 *    transition, triggering various event handlers and delegates
 *    along the way.
 *
 *  @param[in]  inEvent          A reference to the state machine
 *                               excitation event to handle.
 *  @param[in]  inCurrentState   A reference to the current state.
 *
 *  @return  \c true if the event was handled successfully; otherwise,
 *           \c false.
 *
 */
bool
Driver::HandleEvent(const Event &inEvent, const State &inCurrentState)
{
    bool status = false;
    const Transition * theTransition = NULL;

    nlPRECONDITION_VALUE(mMachine != NULL, false);

    theTransition =
        mMachine->FindTransition(inCurrentState, inEvent);

    if (theTransition != NULL)
        status = HandleEvent(inEvent, inCurrentState, *theTransition);

    return (status);
}

/**
 *
 *  @brief
 *    This routine handles the specified state machine excitiation
 *    event by moving the state machine through the appropriate
 *    transition, triggering various event handlers and delegates
 *    along the way.
 *
 *  @param[in]  inEvent         A reference to the state machine excitation
 *                              event to handle.
 *  @param[in]  inCurrentState  A reference to the current state.
 *  @param[in]  inTransition    A reference to the transition being executed
 *                              in response to the specified event.
 *
 *  @return  \c true if the event was handled successfully; otherwise,
 *           \c false.
 *
 */
bool
Driver::HandleEvent(const Event &inEvent,
                    const State &inCurrentState,
                    const Transition &inTransition)
{
    bool status = false;
    const State & nextState = inTransition.mEnd;

    nlPRECONDITION_VALUE(mMachine != NULL, false);
    nlPRECONDITION_VALUE(mDelegate != NULL, false);

    // The general event handling recipe is:
    //
    //   1) Leave the current state.
    //   2) Make the state transition.
    //   3) Enter the next state.
    //
    // Where the delegate method or state and/or transition handlers
    // can override/defeat any of these actions, both before and
    // after, by returning false status.

    {
        status = mDelegate->WillHandleEvent(inEvent, inCurrentState);
        nlEXPECT(status == true, done);

        // Exit the starting state

        {
            status = mDelegate->WillExitState(inEvent, inTransition);
            nlEXPECT(status == true, done);

            status = mDelegate->DidExitState(inEvent, inTransition);
            nlEXPECT(status == true, done);
        }

        // Make the transition between states

        {
            status = mDelegate->WillTransition(inEvent, inTransition);
            nlEXPECT(status == true, done);

            status = mDelegate->DidTransition(inEvent, inTransition);
            nlEXPECT(status == true, done);
        }

        // Enter the ending state

        {
            status = mDelegate->WillEnterState(inEvent, inTransition);
            nlEXPECT(status == true, done);

                mMachine->SetCurrentState(nextState);

            status = mDelegate->DidEnterState(inEvent, inTransition);
            nlEXPECT(status == true, done);
        }

        status = mDelegate->DidHandleEvent(inEvent, inCurrentState);
        nlEXPECT(status == true, done);
    }

 done:
    return (status);
}

}; // namespace Fsm

}; // namespace nl
