#ifndef METAL_LIST_NTH_ELEMENT_LIST_BACKPIVOT_HPP
#define METAL_LIST_NTH_ELEMENT_LIST_BACKPIVOT_HPP

#include "../config.hpp"
#include "../detail/sfinae.hpp"
#include "../lambda/lambda.hpp"
#include "../list/at.hpp"
#include "../list/join.hpp"
#include "../list/list.hpp"
#include "../list/size.hpp"
#include "../number/if.hpp"
#include "../number/less.hpp"
#include "../number/mod.hpp"
#include "../number/number.hpp"
#include "../number/or.hpp"
#include "../number/sub.hpp"

namespace metal {
namespace nth_element_list_backpivot {
    namespace detail {
        template<typename seq>
        using _quickselect_pivot = back<seq>;

        template<
            typename piv, template<typename...> class comp, typename... vals>
        using _make_lo_partition =
            join<if_<comp<vals, piv>, list<vals>, list<>>...>;

        template<
            typename piv, template<typename...> class comp, typename... vals>
        using _make_eq_partition = join<
            if_<or_<comp<vals, piv>, comp<piv, vals>>, list<>, list<vals>>...>;

        template<
            typename piv, template<typename...> class comp, typename... vals>
        using _make_hi_partition =
            join<if_<comp<piv, vals>, list<vals>, list<>>...>;

        template<
            typename lo, typename eq, typename hi, typename num,
            typename recurse_tag_lo =
                less<metal::sub<num, size<lo>>, number<0>>,
            typename recurse_tag_eq = less<metal::sub<num, size<lo>>, size<eq>>>
        struct _quickselect {};

        template<typename... lo, typename eq, typename hi, typename num>
        struct _quickselect<list<lo...>, eq, hi, num, true_, true_> {
            using piv = _quickselect_pivot<list<lo...>>;
            using num_in_lo = num;

            template<template<typename...> class comp>
            using type = join<
	      ::metal::detail::forward<
                _quickselect<
                    _make_lo_partition<piv, comp, lo...>,
                    _make_eq_partition<piv, comp, lo...>,
                    _make_hi_partition<piv, comp, lo...>,
                    num_in_lo>::template type,
                comp>,
	      eq, hi>;
        };

        template<typename lo, typename eq, typename hi, typename num>
        struct _quickselect<lo, eq, hi, num, false_, true_> {
            template<template<typename...> class comp>
            using type = join<lo, eq, hi>;
        };

        template<typename lo, typename eq, typename... hi, typename num>
        struct _quickselect<lo, eq, list<hi...>, num, false_, false_> {
            using num_in_hi = metal::sub<num, size<lo>, size<eq>>;
            using piv = _quickselect_pivot<list<hi...>>;

            template<template<typename...> class comp>
            using type = join<
	      lo, eq,
	      ::metal::detail::forward<
                _quickselect<
                    _make_lo_partition<piv, comp, hi...>,
                    _make_eq_partition<piv, comp, hi...>,
                    _make_hi_partition<piv, comp, hi...>,
                    num_in_hi>::template type,
                comp>>;
        };

        template<typename seq, typename num, typename = true_>
        struct _nth_element_impl {};

        template<typename... vals, int_ n>
        struct _nth_element_impl<
            list<vals...>, number<n>, number<(n >= 0 && n < sizeof...(vals))>> {
            using num_in_lo = number<n>;
            using piv = _quickselect_pivot<list<vals...>>;

            template<template<typename...> class comp>
            using type = ::metal::detail::forward<
                _quickselect<
                    _make_lo_partition<piv, comp, vals...>,
                    _make_eq_partition<piv, comp, vals...>,
                    _make_hi_partition<piv, comp, vals...>,
                    num_in_lo>::template type,
                comp>;
        };

        template<typename lbd>
        struct _nth_element {};

        template<template<typename...> class comp>
        struct _nth_element<lambda<comp>> {
            template<typename seq, typename num>
            using type =
                ::metal::detail::forward<_nth_element_impl<seq, num>::template type, comp>;
        };

    } // detail

    template<typename seq, typename num, typename lbd>
    using nth_element =
      ::metal::detail::call<detail::_nth_element<lbd>::template type, seq, num>;
}
} // metal

#endif
