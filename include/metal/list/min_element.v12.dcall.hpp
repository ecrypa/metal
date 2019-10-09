#ifndef METAL_LIST_MIN_ELEMENT_V12_HPP
#define METAL_LIST_MIN_ELEMENT_V12_HPP

#include "../config.hpp"
#include "../detail/sfinae.hpp"
#include "../lambda/apply.hpp"
#include "../lambda/lambda.hpp"
#include "../number/if.hpp"
#include "../value/fold_left.hpp"

namespace metal {
    namespace v12 {
        namespace detail {
            using metal::detail::v12::dcall;
            template<class lbd>
            struct _min_element {};

            template<template<class...> class expr>
            struct _min_element<lambda<expr>> {
                template<class x, class y, class... _>
                using combiner = if_<dcall<expr, y, x, _...>, y, x>;

                template<class... vals>
                using type = fold_left<lambda<combiner>, vals...>;
            };
        }

        template<class seq, class lbd>
        using min_element =
            apply<lambda<detail::_min_element<lbd>::template type>, seq>;
    }
}

#endif
