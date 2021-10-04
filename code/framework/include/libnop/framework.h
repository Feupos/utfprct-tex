/*
C++ Framework NOP 4.0

Copyright (c) 2020 - present, Felipe dos Santos Neves

The contents of this file are subject to the UTFPR NOP IMPLEMENTATION PUBLIC
LICENSE (the "License"); you may not use this file except in compliance with the
License.

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied.  See the License for
the specific language governing rights and limitations under the License.

The Original Source Code is NOP FRAMEWORK CPP 4.0, released July 22, 2021. IT
WAS AN UTFPR SERVER accessible just with given login and password. This code is
based on other previous NOP Frameworks, being the Notification Oriented Paradigm
(NOP) research project managed by Prof. Jean Marcelo Simão and other professors,
namely Prof. Paulo Cézar Stadzisz as one of them.

The Original Source Code was developed by Felipe dos Santos Neves, in the
Federal University of Technology - Paraná / Brazil (UTFPR - Universidade
Tecnológica Federal do Paraná / Brasil), in the context of his Master in Science
research effort at PPGCA/UTFPR, under the advice of Prof. Robson Ribeiro
Linhares and Prof. Jean Marcelo Simão.

Portions created by UNIVERSITY are Copyright (C) 2020/2021, based upon previous
works of Federal University of Technology - Paraná (UTFPR - Universidade
Tecnológica Federal do Paraná). All Rights Reserved.
*/

#pragma once

#include "libnop/action.h"
#include "libnop/attribute.h"
#include "libnop/condition.h"
#include "libnop/fbe.h"
#include "libnop/instigation.h"
#include "libnop/logger.h"
#include "libnop/premise.h"
#include "libnop/rule.h"
#include "libnop/scheduler.h"

namespace NOP
{
template <typename T>
using SharedAttribute = std::shared_ptr<Attribute<T>>;
using SharedPremise = std::shared_ptr<Premise>;
using SharedCondition = std::shared_ptr<Condition>;
using SharedRule = std::shared_ptr<Rule>;
using SharedInstigation = std::shared_ptr<Instigation>;
using SharedAction = std::shared_ptr<Action>;
}  // namespace NOP
