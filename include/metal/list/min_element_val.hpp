#ifndef METAL_LIST_MIN_ELEMENT_VAL_HPP
#define METAL_LIST_MIN_ELEMENT_VAL_HPP

#include "../config.hpp"
#include "../lambda/apply.hpp"
#include "../lambda/arg.hpp"
#include "../lambda/bind.hpp"
#include "../lambda/lambda.hpp"
#include "../number/if.hpp"
#include "../value/fold_left.hpp"

namespace metal {

namespace detail {

template<typename lbd>
struct _min_element_val {};

template<template<typename...> class expr>
struct _min_element_val<lambda<expr>> {
  template<typename... vals>
  using type = fold_left<
    bind<lambda<if_>, bind<lambda<expr>, _1, _2>, _1, _2>,
    vals...
  >;
};

}// detail

template<typename seq, typename lbd>
using min_element_val = apply<
  lambda<detail::_min_element_val<lbd>::template type>,
  seq
>;

}

#endif
