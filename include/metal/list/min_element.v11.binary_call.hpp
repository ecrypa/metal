#ifndef METAL_LIST_MIN_ELEMENT_V11_HPP
#define METAL_LIST_MIN_ELEMENT_V11_HPP

#include "../config.hpp"
#include "../lambda/apply.hpp"
#include "../lambda/lambda.hpp"
#include "../number/if.hpp"
#include "../value/fold_left.hpp"

namespace metal {
    namespace v11 {
        namespace detail {

            template<class seq>
            struct _min_element_impl {};

            template<class... vals>
            struct _min_element_impl<list<vals...>> {
                template<class lbd>
                using type = fold_left<lbd, vals...>;
            };

            template<bool>
            struct _min_element_binary_call {
                template<template<class...> class expr, class a, class b>
                using type = expr<a, b>;
            };

            template<typename lbd>
            struct _min_element {};

            template<template<class...> class expr>
            struct _min_element<lambda<expr>> {
                template<class x, class y, class... empty>
                using combiner =
                    if_<typename _min_element_binary_call<!sizeof...(
                            empty)>::template type<expr, y, x>,
                        y, x>;

                template<class seq>
                using type = typename _min_element_impl<seq>::template type<
                    lambda<combiner>>;
            };

        } // detail

        template<typename seq, typename lbd>
        using min_element =
            typename detail::_min_element<lbd>::template type<seq>;

    }
}

#endif
