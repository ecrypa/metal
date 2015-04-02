// Copyright Bruno Dutra 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL2_CORE_ARITHMETIC_NEGATE_HPP
#define BOOST_MPL2_CORE_ARITHMETIC_NEGATE_HPP

#include <boost/mpl2/core/integral.hpp>

namespace boost
{
    namespace mpl2
    {
        template<typename n>
        using negate = integral<
            typename n::value_type,
            static_cast<typename n::value_type>(-n::value)
        >;
    }
}

#endif
