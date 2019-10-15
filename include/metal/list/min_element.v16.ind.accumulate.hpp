#ifndef METAL_LIST_MIN_ELEMENT_V16_HPP
#define METAL_LIST_MIN_ELEMENT_V16_HPP

#include "../config.hpp"
#include "../detail/sfinae.hpp"
#include "../lambda/lambda.hpp"
#include "../list/accumulate.hpp"
#include "../list/indices.hpp"
#include "../list/list.hpp"
#include "../number/if.hpp"
#include "../number/number.hpp"
#include "../pair/pair.hpp"

namespace metal {
    namespace v16 {
        namespace detail {
            template<class lbd, class is_empty>
            struct _min_element {};

            template<class lbd>
            struct _min_element<lbd, true_> {
                template<class>
                using type = number<0>;
            };

            template<class lbd>
            struct _min_element<lbd, false_> {
                template<class state, class num, class val>
                using custom_min =
                    if_<invoke<lbd, val, back<state>>, pair<num, val>, state>;

                template<class seq> // TODO: avoid `lbd<v0, v0>` (bootstrap)
                using type = front<accumulate<
                    lambda<custom_min>, pair<number<0>, front<seq>>,
                    indices<seq>, seq>>;
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
