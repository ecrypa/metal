#ifndef METAL_DETAIL_SFINAE_HPP
#define METAL_DETAIL_SFINAE_HPP

#include "../config.hpp"
#include "../detail/declptr.hpp"
#include "../value/eval.hpp"
#include "../value/value.hpp"

#include <type_traits>

namespace metal {
    /// \cond
    namespace detail {
        template<
            template<template<typename...> class...> class,
            template<typename...> class...>
        struct forwarder;

        template<
            template<template<typename...> class...> class tmpl,
            template<typename...> class... exprs,
            eval<std::enable_if<is_value<tmpl<exprs...>>::value>>* = nullptr>
        value<tmpl<exprs...>> sfinae(forwarder<tmpl, exprs...>*);

        template<template<typename...> class expr, typename... vals>
        struct caller;

        template<
            template<typename...> class expr, typename... vals,
            eval<std::enable_if<is_value<expr<vals...>>::value>>* = nullptr>
        value<expr<vals...>> sfinae(caller<expr, vals...>*);

        value<> sfinae(...);

        template<
            template<template<typename...> class...> class tmpl,
            template<typename...> class... exprs>
        struct forwarder
            : decltype(sfinae(declptr<forwarder<tmpl, exprs...>>())) {};

        template<template<typename...> class expr, typename... vals>
        struct caller : decltype(sfinae(declptr<caller<expr, vals...>>())) {};

#if defined(METAL_WORKAROUND)
        template<
            template<template<typename...> class...> class tmpl,
            template<typename...> class... exprs>
        using forward = typename forwarder<tmpl, exprs...>::type;

        template<template<typename...> class expr, typename... vals>
        using call = typename caller<expr, vals...>::type;
#else
        template<
            template<template<typename...> class...> class tmpl,
            template<typename...> class... exprs>
        using forward = tmpl<exprs...>;

        template<template<typename...> class expr, typename... vals>
        using call = expr<vals...>;
#endif
        namespace v12 {
            template<class... vals>
            struct _dcaller {
                template<template<class...> class expr>
                using type = expr<vals...>;
            };

            template<template<class...> class expr, class... vals>
            using dcall = typename _dcaller<vals...>::template type<expr>;
        }
        namespace v14 {
            template<bool>
            struct _dcaller {
                template<template<class...> class expr, class... vals>
                using type = expr<vals...>;
            };

            template<template<class...> class expr, class... vals>
            using dcall = typename _dcaller<!sizeof...(
                vals)>::template type<expr, vals...>;
        }
    }
    /// \endcond
}

#endif
