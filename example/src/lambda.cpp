// Copyright Bruno Dutra 2015-2016
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt

#include <metal.hpp>

#include "example.hpp"

HIDE(
/// [lbd1]
using lbd = metal::lambda<std::add_pointer_t>;
/// [lbd1]

static_assert(metal::is_lambda<lbd>::value, "");
)
