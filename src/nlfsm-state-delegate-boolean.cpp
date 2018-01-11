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
 *    Copyright (c) 2008-2012 Nuovation System Designs, LLC
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
 *      This file implements a derived delegate object that returns
 *      either one of true or false for all of the delegate methods.
 *
 */

#include <nestlabs/fsm/nlfsm-state-delegate-boolean.hpp>

namespace nl {

namespace Fsm {

namespace Delegate {

/**
 *
 *  @brief
 *    This routine is a class constructor. It initializes the value
 *    that will be returned by all delegate methods overridden by the
 *    class (i.e., all of them).
 *
 *  @param[in]  inBoolean  The Boolean that will be returned by all
 *                         delegate methods.
 *
 */
Boolean::Boolean(bool inBoolean) :
    mBoolean(inBoolean)
{
    return;
}

/**
 *
 *  @brief
 *    This routine is called by an associated finite state machine
 *    (FSM) before a newly-posted event is handled and allows the
 *    delegate receiver to decide whether the event processing should
 *    continue.
 *
 *  @param[in]  inEvent  A reference to the event being handled.
 *  @param[in]  inState  A reference to the current state.
 *
 *  @return  The Boolean the class was instantiated with.
 *
 */
bool
Boolean::WillHandleEvent(const Event &inEvent,
                         const State &inState)
{
    return (mBoolean);
}

/**
 *
 *  @brief
 *    This routine is called by an associated finite state machine
 *    (FSM) after a newly-posted event is handled and allows the
 *    delegate receiver to decide whether the event processing should
 *    continue.
 *
 *  @param[in]  inEvent  A reference to the event being handled.
 *  @param[in]  inState  A reference to the current state.
 *
 *  @return  The Boolean the class was instantiated with.
 *
 */
bool
Boolean::DidHandleEvent(const Event &inEvent,
                        const State &inState)
{
    return (mBoolean);
}

/**
 *
 *  @brief
 *    This routine is called by an associated finite state machine
 *    (FSM) before the current state is exited in response to a
 *    newly-posted event and allows the delegate receiver to decide
 *    whether the event processing should continue.
 *
 *  @param[in]  inEvent       A reference to the event being handled.
 *  @param[in]  inTransition  A reference to the transition being taken in
 *                            response to the event.
 *
 *  @return  The Boolean the class was instantiated with.
 *
 */
bool
Boolean::WillExitState(const Event &inEvent,
                       const Transition &inTransition)
{
    return (mBoolean);
}

/**
 *
 *  @brief
 *    This routine is called by an associated finite state machine
 *    (FSM) after the current state is exited in response to a
 *    newly-posted event and allows the delegate receiver to decide
 *    whether the event processing should continue.
 *
 *  @param[in]  inEvent       A reference to the event being handled.
 *  @param[in]  inTransition  A reference to the transition being taken in
 *                            response to the event.
 *
 *  @return  The Boolean the class was instantiated with.
 *
 */
bool
Boolean::DidExitState(const Event &inEvent,
                      const Transition &inTransition)
{
    return (mBoolean);
}

/**
 *
 *  @brief
 *    This routine is called by an associated finite state machine
 *    (FSM) before the specified transition arc is taken in response
 *    to a newly-posted event and allows the delegate receiver to
 *    decide whether the event processing should continue.
 *
 *  @param[in]  inEvent       A reference to the event being handled.
 *  @param[in]  inTransition  A reference to the transition being taken in
 *                            response to the event.
 *
 *  @return  The Boolean the class was instantiated with.
 *
 */
bool
Boolean::WillTransition(const Event &inEvent,
                        const Transition &inTransition)
{
    return (mBoolean);
}

/**
 *
 *  @brief
 *    This routine is called by an associated finite state machine
 *    (FSM) after the specified transition arc is taken in response
 *    to a newly-posted event and allows the delegate receiver to
 *    decide whether the event processing should continue.
 *
 *  @param[in]  inEvent       A reference to the event being handled.
 *  @param[in]  inTransition  A reference to the transition being taken in
 *                            response to the event.
 *
 *  @return  The Boolean the class was instantiated with.
 *
 */
bool
Boolean::DidTransition(const Event &inEvent,
                       const Transition &inTransition)
{
    return (mBoolean);
}

/**
 *
 *  @brief
 *    This routine is called by an associated finite state machine
 *    (FSM) before the next state is entered in response to a
 *    newly-posted event and allows the delegate receiver to decide
 *    whether the event processing should continue.
 *
 *  @param[in]  inEvent       A reference to the event being handled.
 *  @param[in]  inTransition  A reference to the transition being taken in
 *                            response to the event.
 *
 *  @return  The Boolean the class was instantiated with.
 *
 */
bool
Boolean::WillEnterState(const Event &inEvent,
                        const Transition &inTransition)
{
    return (mBoolean);
}

/**
 *
 *  @brief
 *    This routine is called by an associated finite state machine
 *    (FSM) after the next state is entered in response to a
 *    newly-posted event and allows the delegate receiver to decide
 *    whether the event processing should continue.
 *
 *  @param[in]  inEvent       A reference to the event being handled.
 *  @param[in]  inTransition  A reference to the transition being taken in
 *                            response to the event.
 *
 *  @return  The Boolean the class was instantiated with.
 *
 */
bool
Boolean::DidEnterState(const Event &inEvent,
                       const Transition &inTransition)
{
    return (mBoolean);
}

}; // namespace Delegate

}; // namespace Fsm

}; // namespace nl
