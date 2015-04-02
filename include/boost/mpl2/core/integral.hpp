// Copyright Bruno Dutra 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL2_CORE_INTEGRAL_HPP
#define BOOST_MPL2_CORE_INTEGRAL_HPP

#include <type_traits>

namespace boost
{
    namespace mpl2
    {
        template<typename value_type, value_type value>
        using integral = std::integral_constant<value_type, value>;
    }
}

#include <boost/mpl2/core/integral/boolean.hpp>
#include <boost/mpl2/core/integral/character.hpp>
#include <boost/mpl2/core/integral/integer.hpp>
#include <boost/mpl2/core/integral/size_t.hpp>

#endif
