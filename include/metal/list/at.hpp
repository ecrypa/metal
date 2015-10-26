// Copyright Bruno Dutra 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef METAL_LIST_AT_HPP
#define METAL_LIST_AT_HPP

namespace metal
{
    /// \ingroup list
    /// \brief ...
    template<typename list, typename n>
    struct at;

    /// \ingroup list
    /// \brief Eager adaptor for \ref at.
    template<typename list, typename n>
    using at_t = typename at<list, n>::type;
}

#include <metal/list/indices.hpp>
#include <metal/list/transpose.hpp>
#include <metal/lambda/invoke.hpp>
#include <metal/lambda/quote.hpp>
#include <metal/map/at_key.hpp>
#include <metal/number/number.hpp>
#include <metal/pair/pair.hpp>

#include <cstddef>

namespace metal
{
    template<typename list, typename t, t v>
    struct at<list, number<t, v>> :
        invoke<
            at_key<
                transpose<pair<indices<quote_t<list>>, quote_t<list>>>,
                number<std::size_t, static_cast<std::size_t>(v)>
            >
        >
    {};
}

#endif
