#ifndef METAL_LIST_PARTITION_V3_HPP
#define METAL_LIST_PARTITION_V3_HPP

#include "../config.hpp"
#include "../detail/sfinae.hpp"

namespace metal {
    namespace v3 {
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
        using partition =
            detail::call<detail::_partition<lbd>::template type, seq>;
    }
}

#include "../lambda/lambda.hpp"
#include "../list/join.hpp"
#include "../list/list.hpp"
#include "../number/not.hpp"
#include "../number/number.hpp"
#include "../pair/pair.hpp"

#include <type_traits>

namespace metal {
    namespace v3 {
        /// \cond
        namespace detail {
            template<class cond>
            struct _partition_filter {
                template<class val>
                using type = list<val>;
            };

            template<>
            struct _partition_filter<false_> {
                template<class val>
                using type = list<>;
            };

            template<class cond, class val>
            using _partition_filter_t =
                call<_partition_filter<cond>::template type, val>;

            template<class conds, class seq>
            struct _partitioner {};

            template<>
            struct _partitioner<list<>, list<>> {
                using type = pair<list<>, list<>>;
            };

            template<int_... ns, class... vals>
            struct _partitioner<list<number<ns>...>, list<vals...>> {
                using type = pair<
                    join<_partition_filter_t<number<ns>, vals>...>,
                    join<_partition_filter_t<not_<number<ns>>, vals>...>>;
            };

            template<class seq>
            struct _partition_impl {};

            template<class... vals>
            struct _partition_impl<list<vals...>> {
                template<template<class...> class expr>
                using type = typename _partitioner<
                    list<expr<vals>...>, list<vals...>>::type;
            };

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
