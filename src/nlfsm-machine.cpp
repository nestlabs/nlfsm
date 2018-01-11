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
 *      This file implements a class for managing a finite state
 *      machine (FSM) which is effectively a collection of current
 *      state, event and next state transition tuples and a current,
 *      starting state.
 *
 */

#include <nlassert.h>

#include <nestlabs/fsm/nlfsm-transition.hpp>
#include <nestlabs/fsm/nlfsm-machine.hpp>

namespace nl {

namespace Fsm {

// Type Definitions

/**
 *
 *  @class FindTransitionPredicate
 *
 *  @brief
 *   STL find_if algorithm predicate object that matches a state and
 *   event tuple in a state machine transition arc.
 *
 */
class FindTransitionPredicate
{
 public:
    /**
     *
     *  @brief
     *    This routine is a class constructor. It instantiates the
     *    object with the specified state and events which will be
     *    used as search criteria as transition arcs are iterated over
     *    for a match.
     *
     *  @param[in]  inState  A reference to the starting state to find a
     *                       transition for.
     *  @param[in]  inEvent  A reference to the event associated with the
     *                       starting state to find a transition for.
     *
     */
    FindTransitionPredicate(const State &inState, const Event &inEvent) :
        mState(inState),
        mEvent(inEvent)
    {
        return;
    }

    /**
     *
     *  @brief
     *    This routine is a class function operator. It attempts to
     *    match the specified transition to the class state and event
     *    data members.
     *
     *  @param[in]  inTransition  A pointer to the current transition
     *                            being iterated upon for a match.
     *
     *  @return  \c true if the specified transition matches the state and
     *           event tuple data members; otherwise, \c false.
     *
     */
    bool operator ()(const Transition * const inTransition) const
    {
        bool status;

        status = ((mState == inTransition->mStart) &&
                  (mEvent == inTransition->mEvent));

        return (status);
    }

 private:
    const State &   mState;
    const Event &   mEvent;
};

/**
 *
 *  @brief
 *    This routine is the class default (i.e. void) constructor. It
 *    instantiates the machine with the no transitions and a NULL
 *    state.
 *
 */
Machine::Machine(void) :
    mCurrentState(0),
    mCount(0),
    mFirstTransition(NULL)
{
    return;
}

/**
 *
 *  @brief
 *    This routine is a class constructor. It instantiates the machine
 *    with the specified transitions and starts the machine at the
 *    specified starting state.
 *
 *  @param[in]  inTransitions   An array of pointers to transitions to
 *                              instantiate the machine with.
 *  @param[in]  inCount         The number of transitions in the specified
 *                              array.
 *  @param[in]  inCurrentState  A reference to the state to start the machine
 *                              at.
 *
 */
Machine::Machine(const Transition inTransitions[],
                 size_t inCount,
                 const State &inCurrentState)
{
    SetTransitions(inTransitions, inCount, inCurrentState);
}

/**
 *
 *  @brief
 *    This routine sets the transition table with the specified
 *    transitions and starts the machine at the specified starting
 *    state.
 *
 *  @param[in]  inTransitions   An array of pointers to transitions to
 *                              instantiate the machine with.
 *  @param[in]  inCount         The number of transitions in the specified
 *                              array.
 *  @param[in]  inCurrentState  A reference to the state to start the machine
 *                              at.
 *
 */
void
Machine::SetTransitions(const Transition inTransitions[],
                        size_t inCount,
                        const State &inCurrentState)
{
    mCurrentState    = inCurrentState;
    mCount           = inCount;
    mFirstTransition = inTransitions;
}

/**
 *
 *  @brief
 *    This routine gets the current state of the machine.
 *  
 *  @return  A reference to the current state.
 *
 */
const State &
Machine::GetCurrentState(void) const
{
    return mCurrentState;
}

/**
 *
 *  @brief
 *    This routine sets the machine current state to the specified
 *    state.
 *
 *  @param[in]  inState  A reference to the state to set as the current
 *                       state.
 *
 */
void
Machine::SetCurrentState(const State &inState)
{
    mCurrentState = inState;
}

/**
 *
 *  @brief
 *    This routine attempts to find a transition in the state machine
 *    matching the specified starting state and event tuple.
 *
 *  @param[in]  inState  A reference to the starting state to find a
 *                       transition for.
 *  @param[in]  inEvent  A reference to the event associated with the
 *                       starting state to find a transition for.
 *
 *  @return  A pointer to the transition matching the specified state and
 *           event if successful; otherwise, NULL.
 *
 */
const Transition *
Machine::FindTransition(const State & inState, const Event & inEvent) const
{
    const Transition * start = mFirstTransition;
    const Transition * end = mFirstTransition + mCount;
    const FindTransitionPredicate theFinder(inState, inEvent);

    nlCHECK(&inState != NULL);
    nlCHECK(&inEvent != NULL);

    while ((start != end) && !bool(theFinder(start))) {
        ++start;
    }

    return ((start != end) ? start : NULL);
}

}; // namespace Fsm

}; // namespace nl
