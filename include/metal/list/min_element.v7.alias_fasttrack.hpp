#ifndef METAL_LIST_MIN_ELEMENT_V7_HPP
#define METAL_LIST_MIN_ELEMENT_V7_HPP

#include "../config.hpp"
#include "../detail/sfinae.hpp"
#include "../lambda/lambda.hpp"
#include "../list/list.hpp"
#include "../number/if.hpp"

namespace metal {
    namespace v7 {
        namespace detail {
            constexpr std::size_t _min_element_fastrack(std::size_t n) {
                return (n >= 99) ? 100 : (n >= 9) ? 10 : (1 + (n >= 1));
            }

            template<std::size_t n>
            struct _min_element_worker {};

            template<>
            struct _min_element_worker<100> {
                template<
		    template<template<class...> class, class, class> class c,
		    template<class...> class e,
                    /* clang-format off */
		    class _00, class _01, class _02, class _03,
		    class _04, class _05, class _06, class _07,
		    class _08, class _09, class _10, class _11,
		    class _12, class _13, class _14, class _15,
		    class _16, class _17, class _18, class _19,
		    class _20, class _21, class _22, class _23,
		    class _24, class _25, class _26, class _27,
		    class _28, class _29, class _30, class _31,
		    class _32, class _33, class _34, class _35,
		    class _36, class _37, class _38, class _39,
		    class _40, class _41, class _42, class _43,
		    class _44, class _45, class _46, class _47,
		    class _48, class _49, class _50, class _51,
		    class _52, class _53, class _54, class _55,
		    class _56, class _57, class _58, class _59,
		    class _60, class _61, class _62, class _63,
		    class _64, class _65, class _66, class _67,
		    class _68, class _69, class _70, class _71,
		    class _72, class _73, class _74, class _75,
		    class _76, class _77, class _78, class _79,
		    class _80, class _81, class _82, class _83,
		    class _84, class _85, class _86, class _87,
		    class _88, class _89, class _90, class _91,
		    class _92, class _93, class _94, class _95,
		    class _96, class _97, class _98, class _99,
                    /* clang-format on */
		    class... tail>
                using type = typename _min_element_worker<
	            _min_element_fastrack(sizeof...(tail))>::template type<
		    c, e,
                    /* clang-format off */
		    c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e,
		    c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e,
		    c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e,
		    c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e,
		    c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e,
		    c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e,
		    c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e,
		    c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e,
		    c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e,
		    c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e,
		    _00, _01>, _02>, _03>, _04>, _05>, _06>, _07>, _08>, _09>,
		    _10>, _11>, _12>, _13>, _14>, _15>, _16>, _17>, _18>, _19>,
		    _20>, _21>, _22>, _23>, _24>, _25>, _26>, _27>, _28>, _29>,
		    _30>, _31>, _32>, _33>, _34>, _35>, _36>, _37>, _38>, _39>,
		    _40>, _41>, _42>, _43>, _44>, _45>, _46>, _47>, _48>, _49>,
		    _50>, _51>, _52>, _53>, _54>, _55>, _56>, _57>, _58>, _59>,
		    _60>, _61>, _62>, _63>, _64>, _65>, _66>, _67>, _68>, _69>,
		    _70>, _71>, _72>, _73>, _74>, _75>, _76>, _77>, _78>, _79>,
		    _80>, _81>, _82>, _83>, _84>, _85>, _86>, _87>, _88>, _89>,
		    _90>, _91>, _92>, _93>, _94>, _95>, _96>, _97>, _98>, _99>,
		    /* clang-format on */
		    tail...>;
            };

            template<>
            struct _min_element_worker<10> {
                template<
                    template<template<class...> class, class, class> class c,
                    template<class...> class e,
                    /* clang-format off */
		    class _00, class _01, class _02, class _03, class _04,
		    class _05, class _06, class _07, class _08, class _09,
                    /* clang-format on */
                    class... tail>
                using type = typename _min_element_worker<_min_element_fastrack(
                    sizeof...(tail))>::
                    template type<
                        c, e,
                        /* clang-format off */
		    c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e, c<e,
		    _00, _01>, _02>, _03>, _04>, _05>, _06>, _07>, _08>, _09>,
                        /* clang-format on */
                        tail...>;
            };

            template<>
            struct _min_element_worker<2> {
                template<
                    template<template<class...> class, class, class> class c,
                    template<class...> class e, class _00, class _01,
                    class... tail>
                using type = typename _min_element_worker<_min_element_fastrack(
                    sizeof...(
                        tail))>::template type<c, e, c<e, _00, _01>, tail...>;
            };

            template<>
            struct _min_element_worker<1> {
                template<
                    template<template<class...> class, class, class> class,
                    template<class...> class, class _00>
                using type = _00;
            };

            template<class seq>
            struct _min_element_impl {};

            template<class v0, class... vals>
            struct _min_element_impl<list<v0, vals...>> {
                template<template<class...> class comp, class x, class y>
                using combiner = if_<comp<y, x>, y, x>;

                static constexpr std::size_t n = sizeof...(vals);

                template<template<class...> class comp>
                using type = typename _min_element_worker<_min_element_fastrack(
                    sizeof...(
                        vals))>::template type<combiner, comp, v0, vals...>;
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
    } // v7
} // metal

#endif
