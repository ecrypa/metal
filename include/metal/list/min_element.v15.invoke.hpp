#ifndef METAL_LIST_MIN_ELEMENT_V15_HPP
#define METAL_LIST_MIN_ELEMENT_V15_HPP

#include "../config.hpp"
#include "../detail/sfinae.hpp"
#include "../lambda/apply.hpp"
#include "../lambda/lambda.hpp"
#include "../number/if.hpp"
#include "../number/number.hpp"
#include "../value/fold_left.hpp"

namespace metal {
    namespace v15 {
        namespace detail {
            template<class lbd, class = true_>
            struct _min_element {};

            template<class lbd>
            struct _min_element<lbd, is_lambda<lbd>> {
                template<class x, class y>
                using combiner = if_<invoke<lbd, y, x>, y, x>;

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
