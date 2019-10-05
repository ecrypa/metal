#ifndef METAL_LIST_MIN_ELEMENT_SLOW_HPP
#define METAL_LIST_MIN_ELEMENT_SLOW_HPP

#include "../config.hpp"
#include "../lambda/apply.hpp"
#include "../lambda/arg.hpp"
#include "../lambda/bind.hpp"
#include "../lambda/lambda.hpp"
#include "../lambda/partial.hpp"
#include "../number/if.hpp"
#include "../value/fold_left.hpp"

namespace metal {
namespace slow {
    /// \ingroup list
    ///
    /// ### Description
    /// Retrieves a minimum element of a \list according to an ordering relation.
    ///
    /// \tip{The \em first  minimum element is chosen if the ordering relation is [strict].}
    /// [strict]: https://en.wikipedia.org/wiki/Weak_ordering#Strict_weak_orderings
    ///
    /// ### Usage
    /// For any \list `l` and \lambda `lbd`
    /// \code
    ///     using result = metal::min_element<l, lbd>;
    /// \endcode
    ///
    /// \pre: For any two \values `val_i` and `val_j` contained in `l`
    /// `metal::invoke<lbd, val_i, val_j>` returns a \number
    /// \returns: \value
    /// \semantics:
    ///     Equivalent to
    ///     \code
    ///         using result = metal::front<metal::sort<l, lbd>>;
    ///     \endcode
    ///     if the ordering relation is [strict].
    ///
    /// ### Example
    /// \snippet list.cpp min_element
    ///
    /// ### See Also
    /// \see list, sort
    template<typename seq, typename lbd>
    using min_element = apply<
        partial<
            lambda<fold_left>, bind<lambda<if_>, bind<lbd, _2, _1>, _2, _1>>,
        seq>;
}// slow
}

#endif
