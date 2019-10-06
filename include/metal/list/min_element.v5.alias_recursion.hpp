#ifndef METAL_LIST_MIN_ELEMENT_V5_HPP
#define METAL_LIST_MIN_ELEMENT_V5_HPP

#include "../config.hpp"
#include "../detail/sfinae.hpp"
#include "../lambda/lambda.hpp"
#include "../list/list.hpp"
#include "../number/if.hpp"

namespace metal {
    namespace v5 {
        namespace detail {

            template<bool done = false>
            struct _min_element_worker;

            template<>
            struct _min_element_worker<false> {
                template<
                    template<class...> class comp, class v0, class v1,
                    class... tail>
                using type = typename _min_element_worker<!sizeof...(tail)>::
                    template type<comp, if_<comp<v1, v0>, v1, v0>, tail...>;
            };

            template<>
            struct _min_element_worker<true> {
                template<template<class...> class comp, class v0>
                using type = v0;
            };

            template<class seq>
            struct _min_element_impl {};

            template<class v0, class... tail>
            struct _min_element_impl<list<v0, tail...>> {
                template<template<class...> class comp>
                using type = typename _min_element_worker<!sizeof...(
                    tail)>::template type<comp, v0, tail...>;
            };

            template<class lbd>
            struct _min_element {};

            template<template<class...> class comp>
            struct _min_element<lambda<comp>> {
                template<class seq>
                using type = metal::detail::forward<
                    _min_element_impl<seq>::template type, comp>;
            };

        } // detail

        template<class seq, class lbd>
        using min_element =
            metal::detail::call<detail::_min_element<lbd>::template type, seq>;
    } // v5
} // metal

#endif
