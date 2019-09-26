#ifndef METAL_LIST_NTH_ELEMENT_VAL_RANDPIVOT_ERASE_HPP
#define METAL_LIST_NTH_ELEMENT_VAL_RANDPIVOT_ERASE_HPP

#include "../config.hpp"
#include "../detail/sfinae.hpp"
#include "../lambda/lambda.hpp"
#include "../list/at.hpp"
#include "../list/drop.hpp"
#include "../list/join.hpp"
#include "../list/list.hpp"
#include "../list/size.hpp"
#include "../list/take.hpp"
#include "../number/add.hpp"
#include "../number/if.hpp"
#include "../number/inc.hpp"
#include "../number/less.hpp"
#include "../number/mod.hpp"
#include "../number/number.hpp"
#include "../number/or.hpp"
#include "../number/sub.hpp"

namespace metal {
namespace nth_element_val_complicated {
namespace detail {

// left               | piv | right
// left_loeq left_hi  | piv | right_lo right_eqhi
// left_loeq right_lo | piv | left_hi right_eqhi

template<class seq>
using _quickselect_pivot_index =
  mod<number<4678930447522229821>, size<seq>>;

template<class seq, class piv>
struct _make_loeq_partition {};

template<class... vals, class piv>
struct _make_loeq_partition<list<vals...>, piv> {
  template<template<class...> class comp>
  using type = join<
    if_<comp<piv, vals>, list<>, list<vals>>...
  >;
};

template<class seq, class piv>
struct _make_lo_partition {};

template<class... vals, class piv>
struct _make_lo_partition<list<vals...>, piv> {
  template<template<class...> class comp>
  using type = join<
    if_<comp<vals, piv>, list<vals>, list<>>...
  >;
};

template<
  class prev_left,
  class num,
  class prev_piv = void,
  class prev_right = list<>,
  class left_loeq = prev_left,
  class right_lo = list<>,
  class tag_lo = less<num, add<size<left_loeq>, size<right_lo>>>,
  class tag_done = same<num, add<size<left_loeq>, size<right_lo>>>>
struct _quickselect {};

template<class prev_left, class num, class prev_piv, class prev_right,
	 class left_loeq, class right_lo>
struct _quickselect<
  prev_left, num, prev_piv, prev_right,
  left_loeq, right_lo, true_, false_> {
  using seq = join<left_loeq, right_lo>;
  using piv_idx = _quickselect_pivot_index<seq>;

  using left = take<seq, piv_idx>;
  using piv = at<seq, piv_idx>;
  using right = drop<seq, inc<piv_idx>>;

  template<template<class...> class comp>
  using type = ::metal::detail::forward<
    _quickselect<
      left,
      num,
      piv,
      right,
      ::metal::detail::forward<_make_loeq_partition<left, piv>::template type, comp>,
      ::metal::detail::forward<_make_lo_partition<right, piv>::template type, comp>
    >::template type,
    comp>;
};

template<class prev_left, class num, class prev_piv, class prev_right,
	 class left_loeq, class right_lo>
struct _quickselect<
  prev_left, num, prev_piv, prev_right,
  left_loeq, right_lo, false_, true_> {
  template<template<class...> class comp>
  using type = prev_piv;
};

template<class prev_left, class num, class prev_piv, class prev_right,
	 class left_loeq, class right_lo>
struct _quickselect<
  prev_left, num, prev_piv, prev_right,
  left_loeq, right_lo, false_, false_> {
  using left_hi = drop<prev_left, size<left_loeq>>;
  using right_eqhi = drop<prev_right, size<right_lo>>;

  using seq = join<left_hi, right_eqhi>;
  using piv_idx = _quickselect_pivot_index<seq>;

  using left = take<seq, piv_idx>;
  using piv = at<seq, piv_idx>;
  using right = drop<seq, inc<piv_idx>>;

  using next_num = sub<num, add<size<left_loeq>, size<right_lo>>, number<1>>;

  template<template<class...> class comp>
  using type = ::metal::detail::forward<
    _quickselect<
      left,
      next_num,
      piv,
      right,
      ::metal::detail::forward<_make_loeq_partition<left, piv>::template type, comp>,
      ::metal::detail::forward<_make_lo_partition<right, piv>::template type, comp>
    >::template type,
    comp>;
};

template<class seq, class num, class = true_>
struct _nth_element_impl {};

template<class... vals, int_ n>
struct _nth_element_impl<
  list<vals...>, number<n>, number<(n >= 0 && n < sizeof...(vals))>> {
  using num = number<n>;

  template<template<class...> class comp>
  using type = ::metal::detail::forward<
    _quickselect<list<vals...>, num>::template type,
    comp>;
};

template<class lbd>
struct _nth_element {};

template<template<class...> class comp>
struct _nth_element<lambda<comp>> {
  template<class seq, class num>
  using type = ::metal::detail::forward<
    _nth_element_impl<seq, num>::template type, comp>;
};

} // detail

template<class seq, class num, class lbd>
using nth_element = ::metal::detail::call<
  detail::_nth_element<lbd>::template type, seq, num>;
}
} // metal

#endif
