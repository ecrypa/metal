#ifndef METAL_LIST_MIN_ELEMENT_V17_HPP
#define METAL_LIST_MIN_ELEMENT_V17_HPP

#include "../config.hpp"
#include "../detail/sfinae.hpp"
#include "../lambda/apply.hpp"
#include "../lambda/invoke.hpp"
#include "../lambda/lambda.hpp"
#include "../lambda/partial.hpp"
#include "../list/find.hpp"
#include "../list/list.hpp"
#include "../number/if.hpp"
#include "../number/number.hpp"
#include "../value/fold_left.hpp"

namespace metal {
    namespace v17 {
        namespace detail {
            template<class lbd, class is_empty>
            struct _min_element {};

            template<class lbd>
            struct _min_element<lbd, true_> {
                template<class...>
                using type = number<0>;
            };

            template<class lbd>
            struct _min_element<lbd, false_> {
                template<class x, class y>
                using custom_min = if_<invoke<lbd, y, x>, y, x>;

                template<class seq>
                using type = find<
                    seq,
                    apply<partial<lambda<fold_left>, lambda<custom_min>>, seq>>;
            };
        }

        template<class seq, class lbd>
        using min_element = metal::detail::call<
            detail::_min_element<
                if_<is_lambda<lbd>, lbd>, // TODO: is this good for empty case?
                if_<is_list<seq>, empty<seq>>>::template type,
            seq>;
    }
}

#endif
