#ifndef METAL_LIST_MIN_ELEMENT_VAL_HPP
#define METAL_LIST_MIN_ELEMENT_VAL_HPP

#include "../config.hpp"
#include "../lambda/apply.hpp"
#include "../lambda/lambda.hpp"
#include "../number/if.hpp"
#include "../value/fold_left.hpp"

namespace metal {

namespace detail {

template<typename lbd>
struct _min_element_val {};

template<template<typename...> class expr>
struct _min_element_val<lambda<expr>> {
  template<typename x, typename y>
  using combiner = if_<expr<x, y>, x, y>;

  template<typename... vals>
  using type = fold_left<lambda<combiner>, vals...>;
};

}// detail

template<typename seq, typename lbd>
using min_element_val = apply<
  lambda<detail::_min_element_val<lbd>::template type>,
  seq
>;

}

#endif
