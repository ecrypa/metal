// Copyright Bruno Dutra 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL2_METAFUNCTIONAL_EVAL_HPP
#define BOOST_MPL2_METAFUNCTIONAL_EVAL_HPP

#include <boost/mpl2/core/identity.hpp>

namespace boost
{
    namespace mpl2
    {
        namespace detail
        {
            template<template<typename...> class expr, typename... args>
            struct eval_impl
            {
            private:
                struct empty {};

                template<template<typename...> class>
                static empty impl(...);
                template<template<typename...> class e>
                static identity<typename e<args...>::type> impl(int);

            public:
                using type = decltype(impl<expr>(0));
            };
        }

        template<template<typename...> class expr, typename... args>
        struct eval :
                detail::eval_impl<expr, args...>::type
        {};
    }
}

#endif