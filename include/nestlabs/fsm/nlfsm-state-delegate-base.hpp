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
 *      This file defines an abstract base class for handling various
 *      finite state machine (FSM) management events.
 *
 *      Each of the delegate method pairs is invoked before and
 *      after the corresponding FSM events. If the delegate receiver
 *      returns false, the FSM ignores the "in flight" event and holds
 *      at the current state. Otherwise, the FSM continues event
 *      processing.
 */

#ifndef NLFSM_DELEGATE_BASE_HPP
#define NLFSM_DELEGATE_BASE_HPP

#include <nestlabs/fsm/nlfsm-event.hpp>
#include <nestlabs/fsm/nlfsm-state.hpp>
#include <nestlabs/fsm/nlfsm-transition.hpp>

namespace nl {

    namespace Fsm {

        namespace Delegate {

            /**
             *  @class Base
             *
             *  @brief
             *    This class defines an abstract base class following the
             *    delegate pattern for observing and handling various finite
             *    state machine (FSM) management events.
             *
             *  Each of the delegate method pairs is invoked before
             *  and after the corresponding FSM events. If the
             *  delegate receiver returns false, the FSM ignores the
             *  "in flight" event and holds at the current
             *  state. Otherwise, the FSM continues event processing.
             *
             */
            class Base
            {
            public:
                /**
                 *  @name Event Reception
                 *
                 *  Event reception delegate methods
                 *
                 */

                //@{

                /**
                 *  @brief
                 *    This routine is called by an associated finite
                 *    state machine (FSM) before a newly-posted event
                 *    is handled and allows the delegate receiver to
                 *    decide whether the event processing should
                 *    continue.
                 *
                 *  @param[in]  inEvent  A reference to the event being
                 *                       handled.
                 *  @param[in]  inState  A reference to the current state.
                 *
                 *  @return  \c true if the FSM should continue processing
                 *           the event; otherwise, \c false.
                 *
                 */
                virtual bool WillHandleEvent(const Event &inEvent,
                                             const State &inState) = 0;

                /**
                 *  @brief
                 *    This routine is called by an associated finite
                 *    state machine (FSM) after a newly-posted event
                 *    is handled and allows the delegate receiver to
                 *    decide whether the event processing should
                 *    continue.
                 *
                 *  @param[in]  inEvent  A reference to the event being
                 *                       handled.
                 *  @param[in]  inState  A reference to the current state.
                 *
                 *  @return  \c true if the FSM should continue processing
                 *           the event; otherwise, \c false.
                 *
                 */
                virtual bool DidHandleEvent(const Event &inEvent,
                                            const State &inState) = 0;

                //@}

                /**
                 *
                 *  @name Current State Exit
                 *
                 *  Current state exit delegate methods
                 *
                 */

                //@{

                /**
                 *  @brief
                 *    This routine is called by an associated finite
                 *    state machine (FSM) before the current state is
                 *    exited in response to a newly-posted event and
                 *    allows the delegate receiver to decide whether
                 *    the event processing should continue.
                 *
                 *  @param[in]  inEvent       A reference to the event being
                 *                            handled.
                 *  @param[in]  inTransition  A reference to the transition
                 *                            being taken in response to the
                 *                            event.
                 *
                 *  @return  \c true if the FSM should continue processing
                 *           the event; otherwise, \c false.
                 *
                 */
                virtual bool WillExitState(const Event &inEvent,
                                           const Transition &inTransition) = 0;

                /**
                 *  @brief
                 *    This routine is called by an associated finite
                 *    state machine (FSM) after the current state is
                 *    exited in response to a newly-posted event and
                 *    allows the delegate receiver to decide whether
                 *    the event processing should continue.
                 *
                 *  @param[in]  inEvent       A reference to the event being
                 *                            handled.
                 *  @param[in]  inTransition  A reference to the transition
                 *                            being taken in response to the
                 *                            event.
                 *
                 *  @return  \c true if the FSM should continue processing
                 *           the event; otherwise, \c false.
                 *
                 */
                virtual bool DidExitState(const Event &inEvent,
                                          const Transition &inTransition) = 0;

                //@}

                /**
                 *
                 *  @name Current State to Next State Transition
                 *
                 *  Current state to next state transition delegate methods
                 *
                 */

                //@{

                /**
                 *  @brief
                 *    This routine is called by an associated finite
                 *    state machine (FSM) before the specified
                 *    transition arc is taken in response to a
                 *    newly-posted event and allows the delegate
                 *    receiver to decide whether the event processing
                 *    should continue.
                 *
                 *  @param[in]  inEvent       A reference to the event being
                 *                            handled.
                 *  @param[in]  inTransition  A reference to the transition
                 *                            being taken in response to the
                 *                            event.
                 *
                 *  @return  \c true if the FSM should continue processing
                 *           the event; otherwise, \c false.
                 *
                 */
                virtual bool WillTransition(const Event &inEvent,
                                            const Transition &inTransition) = 0;

                /**
                 *  @brief
                 *    This routine is called by an associated finite
                 *    state machine (FSM) after the specified
                 *    transition arc is taken in response to a
                 *    newly-posted event and allows the delegate
                 *    receiver to decide whether the event processing
                 *    should continue.
                 *
                 *  @param[in]  inEvent       A reference to the event being
                 *                            handled.
                 *  @param[in]  inTransition  A reference to the transition
                 *                            being taken in response to the
                 *                            event.
                 *
                 *  @return  \c true if the FSM should continue processing
                 *           the event; otherwise, \c false.
                 *
                 */
                virtual bool DidTransition(const Event &inEvent,
                                           const Transition &inTransition) = 0;

                //@}

                /**
                 *
                 *  @name Next State Entry
                 *
                 *  Next state entry delegate methods
                 *
                 */

                //@{

                /**
                 *  @brief
                 *    This routine is called by an associated finite
                 *    state machine (FSM) before the next state is
                 *    entered in response to a newly-posted event and
                 *    allows the delegate receiver to decide whether
                 *    the event processing should continue.
                 *
                 *  @param[in]  inEvent       A reference to the event being
                 *                            handled.
                 *  @param[in]  inTransition  A reference to the transition
                 *                            being taken in response to the
                 *                            event.
                 *
                 *  @return  \c true if the FSM should continue processing
                 *           the event; otherwise, \c false.
                 *
                 */
                virtual bool WillEnterState(const Event &inEvent,
                                            const Transition &inTransition) = 0;

                /**
                 *  @brief
                 *    This routine is called by an associated finite
                 *    state machine (FSM) after the next state is
                 *    entered in response to a newly-posted event and
                 *    allows the delegate receiver to decide whether
                 *    the event processing should continue.
                 *
                 *  @param[in]  inEvent       A reference to the event being
                 *                            handled.
                 *  @param[in]  inTransition  A reference to the transition
                 *                            being taken in response to the
                 *                            event.
                 *
                 *  @return  \c true if the FSM should continue processing
                 *           the event; otherwise, \c false.
                 *
                 */
                virtual bool DidEnterState(const Event &inEvent,
                                           const Transition &inTransition) = 0;

                //@}

            protected:
                // Constructor - Protected to ensure that no
                // instances of this object can be directly
                // instantiated outside of derived classes.

                Base(void);
            };

        }; // namespace Delegate

    }; // namespace Fsm

}; // namespace nl

#endif // NLFSM_DELEGATE_BASE_HPP
