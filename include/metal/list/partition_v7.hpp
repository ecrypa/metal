#ifndef METAL_LIST_PARTITION_V7_HPP
#define METAL_LIST_PARTITION_V7_HPP

#include "../config.hpp"
#include "../detail/sfinae.hpp"

namespace metal {
namespace v7 {
    /// \cond
    namespace detail {
    using namespace metal::detail;
        template<class lbd>
        struct _partition;
    }
    /// \endcond

    /// \ingroup list
    ///
    /// ### Description
    /// Splits a \list in two according to a predicate.
    ///
    /// ### Usage
    /// For any \list `l` and \lambda `lbd`
    /// \code
    ///     using result = metal::partition<l, lbd>;
    /// \endcode
    ///
    /// \pre: For any element `l[i]` contained in `l`,
    /// `metal::invoke<lbd, l[i]>` returns a \number
    /// \returns: \pair
    /// \semantics:
    ///     Equivalent to
    ///     \code
    ///         using result = metal::pair<l_1, l_2>;
    ///     \endcode
    ///     where `l_1` contains all and only the elements `l[i]` in `l` for
    ///     which `metal::invoke<lbd, l[i]>{} != false` and `l_2` contains the
    ///     remaining elements.
    ///
    /// ### Example
    /// \snippet list.cpp partition
    ///
    /// ### See Also
    /// \see list, copy_if, remove_if
    template<class seq, class lbd>
    using partition = detail::call<detail::_partition<lbd>::template type, seq>;
}
}

#include "../lambda/lambda.hpp"
#include "../list/join.hpp"
#include "../list/list.hpp"
#include "../number/if.hpp"
#include "../number/number.hpp"
#include "../pair/pair.hpp"

namespace metal {
namespace v7 {
    /// \cond
    namespace detail {
        template<class...>
        struct _partition_joiner {};

        template<class... left, class... right>
        struct _partition_joiner<list<left, right>...> {
            using type = pair<join<left...>, join<right...>>;
        };

    template<class cond, class val>
    struct _partition_filter {
      using type = list<list<val>, list<>>;
    };

    template<class val>
    struct _partition_filter<false_, val> {
      using type = list<list<>, list<val>>;
    };

        template<class seq>
        struct _partition_impl {};

        template<>
        struct _partition_impl<list<>> {
            template<template<class...> class>
            using type = pair<list<>, list<>>;
        };

        template<class... vals>
        struct _partition_impl<list<vals...>> {
            template<template<class...> class expr>
            using type =
              _partition_joiner<typename _partition_filter<expr<vals>, vals>::type...>;
        };

        template<class lbd>
        struct _partition {};

        template<template<class...> class expr>
        struct _partition<lambda<expr>> {
            template<class seq>
            using type = forward<_partition_impl<seq>::template type, expr>;
        };
    }
    /// \endcond
}
}

#endif
