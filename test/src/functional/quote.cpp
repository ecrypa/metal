// Copyright Bruno Dutra 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

#include <metal/functional/quote.hpp>
#include <metal/functional/apply.hpp>

#include "test.hpp"

using namespace metal;

METAL_TEST_ASSERT((std::is_same<quote_t<void>::type, void>::value));
METAL_TEST_ASSERT((std::is_same<apply_t<quote_t<void>>, void>::value));

METAL_TEST_ASSERT((std::is_same<quote_t<_1>::type, _1>::value));
METAL_TEST_ASSERT((std::is_same<apply_t<quote_t<_1>>, _1>::value));

METAL_TEST_ASSERT((std::is_same<quote_t<test::e1<_1>>::type, test::e1<_1>>::value));
METAL_TEST_ASSERT((std::is_same<apply_t<quote_t<test::e1<_1>>>, test::e1<_1>>::value));
