// Copyright Bruno Dutra 2015-2016
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt

#include <metal/list/remove_if.hpp>
#include <metal/list/list.hpp>
#include <metal/lambda/lambda.hpp>
#include <metal/lambda/invoke.hpp>
#include <metal/number/number.hpp>
#include <metal/pair/pair.hpp>

#include "test.hpp"

#define MATRIX(M, N) \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, VAL(M), VAL(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, VAL(M), NUM(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, VAL(M), PAIR(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, VAL(M), LIST(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, VAL(M), MAP(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, VAL(M), LBD(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, VAL(M), LBD(_)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, NUM(M), VAL(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, NUM(M), NUM(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, NUM(M), PAIR(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, NUM(M), LIST(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, NUM(M), MAP(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, NUM(M), LBD(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, NUM(M), LBD(_)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, PAIR(M), VAL(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, PAIR(M), NUM(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, PAIR(M), PAIR(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, PAIR(M), LIST(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, PAIR(M), MAP(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, PAIR(M), LBD(N)>), (BOOL(N == 1))); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, PAIR(M), LBD(_)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LIST(M), VAL(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LIST(M), NUM(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LIST(M), PAIR(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LIST(M), LIST(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LIST(M), MAP(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LIST(M), LBD(N)>), (BOOL(!M || N == 1))); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LIST(M), LBD(_)>), (BOOL(!M))); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, MAP(M), VAL(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, MAP(M), NUM(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, MAP(M), PAIR(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, MAP(M), LIST(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, MAP(M), MAP(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, MAP(M), LBD(N)>), (BOOL(!M || N == 1))); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, MAP(M), LBD(_)>), (BOOL(!M))); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LBD(M), VAL(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LBD(M), NUM(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LBD(M), PAIR(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LBD(M), LIST(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LBD(M), MAP(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LBD(M), LBD(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LBD(M), LBD(_)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LBD(_), VAL(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LBD(_), NUM(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LBD(_), PAIR(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LBD(_), LIST(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LBD(_), MAP(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LBD(_), LBD(N)>), (FALSE)); \
    CHECK((metal::is_invocable<metal::lambda<metal::remove_if>, LBD(_), LBD(_)>), (FALSE)); \
    CHECK((metal::remove_if<metal::list<ENUM(M, FWD, NUM, PAIR, LBD)>, metal::lambda<metal::is_number>>), (metal::list<ENUM(M, FWD, PAIR, LBD)>)); \
    CHECK((metal::remove_if<metal::list<ENUM(M, FWD, NUM, PAIR, LBD)>, metal::lambda<metal::is_pair>>), (metal::list<ENUM(M, FWD, NUM, LBD)>)); \
    CHECK((metal::remove_if<metal::list<ENUM(M, FWD, NUM, PAIR, LBD)>, metal::lambda<metal::is_lambda>>), (metal::list<ENUM(M, FWD, NUM, PAIR)>)); \
/**/

GEN(MATRIX)
