#
#    Copyright 2017-2018 Nest Labs Inc. All Rights Reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

#
#    Description:
#      This file is the GNU automake template for the Nest Labs Finite State
#      Machine library.
#

include $(abs_top_nlbuild_autotools_dir)/automake/pre.am

nlfsm_dirstem                                       = \
    nestlabs/fsm

nlfsm_includedir                                    = \
    $(includedir)/$(nlfsm_dirstem)

nlfsm_include_HEADERS                               = \
    $(nlfsm_dirstem)/nlfsm-driver.hpp                 \
    $(nlfsm_dirstem)/nlfsm-event.hpp                  \
    $(nlfsm_dirstem)/nlfsm.hpp                        \
    $(nlfsm_dirstem)/nlfsm-machine.hpp                \
    $(nlfsm_dirstem)/nlfsm-state-delegate-always.hpp  \
    $(nlfsm_dirstem)/nlfsm-state-delegate-base.hpp    \
    $(nlfsm_dirstem)/nlfsm-state-delegate-boolean.hpp \
    $(nlfsm_dirstem)/nlfsm-state-delegate-never.hpp   \
    $(nlfsm_dirstem)/nlfsm-state-delegate-random.hpp  \
    $(nlfsm_dirstem)/nlfsm-state.hpp                  \
    $(nlfsm_dirstem)/nlfsm-transition.hpp             \
    $(NULL)

install-headers: install-data

include $(abs_top_nlbuild_autotools_dir)/automake/post.am
