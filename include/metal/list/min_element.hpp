#ifndef METAL_LIST_MIN_ELEMENT_HPP
#define METAL_LIST_MIN_ELEMENT_HPP

#include "../config.hpp"
#include "../list/find.hpp"
#include "../list/min_element_val.hpp"

namespace metal {

template<typename seq, typename lbd>
using min_element = metal::find<seq, metal::min_element_val<seq, lbd>>;

}

#endif
